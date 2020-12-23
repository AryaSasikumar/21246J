
class PID_Controller{
  public:
    double Kp = 0.05;  //Ku = 0.245        0.245*0.6 = Kp = 0.147         Ki= 1.2*0.245/0.675=0.435     Kd= 0.075*0.245*0.675=0.0124
    double Ki = 0.0011;//0.0006   /0.000003    pU=0.675 seconds
    double Kd = 0.3;//0.0004    //0.001
    double turnKp = 0.7; //0.008
    double turnKi = 0.0006;
    double turnKd = 0.5;
    int Dt=15;
    double error;
    double speed;
    double integral;
    double derivative;
    double prevError;
    void pidDriveLoop(int setpoint);
    void pidDriveBackLoop(int setpoint);
    void pidTurnRightLoop(int setpoint);
    void pidTurnLeftLoop(int setpoint);
    bool pidRun;
};
