#include "Robot.h"

Base myBase;



int rc_auto_loop_task() {
  while (true){
    myBase.userControl();
  }
  return 0;
}