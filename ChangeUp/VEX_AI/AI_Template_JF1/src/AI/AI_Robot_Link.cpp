/*---AI_ROBOT_LINK_CPP---*/
/*----------------------------------------------------------------------------*/
/*    Module:       AI_Robot_Link.cpp                                         */
/*    Author:       Jeffrey Fisher II                                         */
/*    Created:      23 Dec 2020                                               */
/*----------------------------------------------------------------------------*/
#include "vex.h"

#include "AI/AI_Robot_Link.h"

AI::Robot_Link::Robot_Link(int32_t index, const char *name, vex::linkType type) : vex::serial_link( index, name, type ) {
  // create threads as tx_task and rx_task are static class members, we pass
  // the class instance as an argument to the thread. A new thread is, however, created for each instance
  // An AI robot would usually only have one instance, but this is a generic solution.
  vex::thread t1 = vex::thread( tx_task, static_cast<void *>(this) );
  vex::thread t2 = vex::thread( rx_task, static_cast<void *>(this) );
}

AI::Robot_Link::~Robot_Link(){}// We don't expect the instance to be destroyed

int32_t AI::Robot_Link::get_packets(){ return packets; } //Get total # good received packets.

int32_t AI::Robot_Link::get_errors(){ return errors;} //Get # bad received packets.

int32_t AI::Robot_Link::get_timeouts(){ return timeouts; }//Get # of timeouts that have been triggered.

int32_t AI::Robot_Link::get_total(){ return total_data_received; }//Get # bytes received.

int32_t AI::Robot_Link::get_tx_packets(){ return tx_packets; }//Get # transmit packets.

int32_t AI::Robot_Link::get_tx_errors(){ return tx_errors; }//Get # bad transmit packets.

void AI::Robot_Link::set_remote_location( float x, float y, float heading){ //Set data to be sent to remote robot.
  txlock.lock();
  packet_tx_1.payload.loc_x = x;
  packet_tx_1.payload.loc_y = y;
  packet_tx_1.payload.heading = heading;
  txlock.unlock();
}

void AI::Robot_Link::get_local_location( float &x, float &y, float &heading){ //Get data to be sent to remote robot.
  txlock.lock();
  x = packet_tx_1.payload.loc_x;
  y = packet_tx_1.payload.loc_y;
  heading = packet_tx_1.payload.heading;
  txlock.unlock();
}

void AI::Robot_Link::get_remote_location( float &x, float &y, float &heading ){ //Get data received from the remote robot.
  rxlock.lock();
  x = packet_rx_1.payload.loc_x;
  y = packet_rx_1.payload.loc_y;
  heading = packet_rx_1.payload.heading;
  rxlock.unlock();
}


bool AI::Robot_Link::process( uint8_t data ){ //Process some received data.
  bool  bFinalize = false;

  // 250mS interbyte timeout
  if( state != comms_state::kStateSyncWait1 && timer.time() > 250 ) {
    timeouts++;
    state = comms_state::kStateSyncWait1;
  }
  
  timer.clear();//reset timeout

  switch( state ) {
    /*---------------------------------------------------------*/
    // crude two byte sync
    case comms_state::kStateSyncWait1:
      if( static_cast<sync_byte>(data) == sync_byte::kSync1 ) {
        state = comms_state::kStateSyncWait2;
      }
      break;
    case comms_state::kStateSyncWait2:
      state = comms_state::kStateSyncWait1;
      if( static_cast<sync_byte>(data) == sync_byte::kSync2 ) {
        state = comms_state::kStateLength;
        payload_length = 0;
      }
      break;
    /*---------------------------------------------------------*/
    // get payload length, 1 byte
    case comms_state::kStateLength:
      payload_length = data;
      state = comms_state::kStateType;
      payload_type = 0;
      break;
    /*---------------------------------------------------------*/
    // get packet type, 1 byte
    case comms_state::kStateType:
      payload_type = data;
      state = comms_state::kStateCrc;
      _index = 0;
      payload_crc = 0;
      break;
    /*---------------------------------------------------------*/
    // get payload crc
    case comms_state::kStateCrc:
      // data is 2 byte little endian
      payload_crc = (payload_crc >> 8) + ((uint32_t)data << 8);
      if( _index++ == 1 ) {
        state = comms_state::kStatePayload;
        _index = 0;
        calc_crc = 0;
      }
      break;
    /*---------------------------------------------------------*/
    // get payload data
    case comms_state::kStatePayload:
      if( _index < sizeof(payload) ) {
        // add byte to buffer
        payload.bytes[_index] = data;
        _index++;
        // keep runnint crc32, save calculating all at once later
        calc_crc =crc32( &data, 1, calc_crc  );
        // all data received ?
        if( _index == payload_length ) {
          // check crc32
          if( (uint16_t)payload_crc == (uint16_t)calc_crc ) {
            state = comms_state::kStateGoodPacket;
            bFinalize = true;
          }else{
            state = comms_state::kStateBadPacket;
            bFinalize = true;
          }
        }
      }else{
        // if we end up here then error
        state = comms_state::kStateBadPacket;
        bFinalize = true;
      }
      break;
    /*---------------------------------------------------------*/
    // We are finished parsing data here
    // either success or failure
    case comms_state::kStateGoodPacket:
      if( payload_type == RL_LOCATION_PACKET ){
        // lock access and copy data
        rxlock.lock();
        memcpy( &packet_rx_1.payload, &payload.pak_1, sizeof(packet_1_payload));
        rxlock.unlock();
      }else if( payload_type == 2 ){
        // perhaps other packet types
      }
      // timestamp this packet
      last_packet_time = timer.system();
      packets++;
      state = comms_state::kStateSyncWait1;
      break;
    case comms_state::kStateBadPacket:
      // bad packet
      errors++;
      state = comms_state::kStateSyncWait1;
      break;
    default:
      state = comms_state::kStateSyncWait1;
      break;
  }
  // if bFinalize is true we are called again to finish processing
  return( bFinalize );
}


int AI::Robot_Link::rx_task(void *arg){ //Task to periodically receive data from partner robot.
  uint8_t buffer[128];
  int32_t buffer_length;
  if( arg == NULL){ return(0); }
  // get our robot_link instance
  AI::Robot_Link *instance = static_cast<AI::Robot_Link *>(arg);
  while( true ) {
    // check for received data, short timeout
    // we are expecting a full packet about every 50mS
    // but can check more often than that to reduce latency
    if( (buffer_length = instance->receive(buffer, sizeof(buffer), 10)) > 0 ){
      for(int i=0;i<buffer_length;i++){
        while( instance->process( buffer[i] ) ){ vex::this_thread::yield(); }
      }
      instance->total_data_received += buffer_length;
    }
    vex::this_thread::sleep_for(5);
  }
}


int AI::Robot_Link::tx_task(void *arg){ //Task to periodically send our data to partner robot.
  if( arg == NULL){return(0);}
  // get our robot_link instance
  AI::Robot_Link *instance = static_cast<AI::Robot_Link *>(arg);
  // initialize the tx packet
  instance->packet_tx_1 = { 
    .header = {
      .sync = {
        static_cast<uint8_t>(sync_byte::kSync1), 
        static_cast<uint8_t>(sync_byte::kSync2)
      },
      .type = RL_LOCATION_PACKET, 
      .length = sizeof(packet_1_payload)
    } 
  };

  // wait for initial connection
  while(!instance->isLinked()){ vex::this_thread::sleep_for(50); }

  // we periodically send the same packet to the partner robot
  // A RL_LOCATION_PACKET is 18 bytes, max bandwidth is approx 520 bytes/second (worker->manager)
  // so we can send at most 28 packets per second without loosing data
  // In practise this can be lowered to 15Hz (or lower) as that's the rate that the Jetson will update locations
  // We will use 10 packets/second in this example
  int loops_sec = 10;

  while(FOREVER){
    // mutex is not really need, but it's good practise for RTOS so we will keep it
    instance->txlock.lock();
    
    // create crc checksum so we can verify correct reception
    // serial_link class has crc32 generator included as protected member function
    // we can use as we are a sub class of serial_link
    // we truncate to 16 bit to save space in the packet
    instance->packet_tx_1.header.crc = (uint16_t)instance->crc32((uint8_t *)&instance->packet_tx_1.payload, sizeof(packet_1_payload), 0 );

    // send the data, check for success
    if( instance->send( (uint8_t *)&instance->packet_tx_1, sizeof(packet_1_t) ) > 0 ) { instance->tx_packets++; }
    else{ instance->tx_errors++; }
    instance->txlock.unlock(); // release the mutex
    vex::this_thread::sleep_for( 1000/loops_sec ); // loop rate approx 10Hz
  }
}

/*---AI_ROBOT_LINK_CPP---*/