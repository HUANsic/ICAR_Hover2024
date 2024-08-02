#include "pid.h"
#include "huansic_motor.h"

int32_t err=0.0, derr=0.0;
float Kp=0.0003;
float Kd=0.0003;
float pwm=0.0;

float pid(int32_t now){
    derr = 0 - now - err;
    err = 0 - now;
    pwm = Kp * err + Kd * derr;
    if(pwm > 1) return 1;
    if(pwm < -1) return -1;
    return pwm;
}

float pid_prop_update(int32_t goal, int32_t now){
    derr = goal - now - err;
    err = goal - now;
    pwm = Kp * err + Kd * derr;
    if(pwm > 0.8) pwm = 0.8;
    if(pwm < -0.8) pwm = -0.8;
    if(pwm > 0){
        huansic_motor_set(LeftProp, 0.8);
        huansic_motor_set(RightProp, 0.8-pwm);
    }
    else{
        huansic_motor_set(LeftProp, 0.8+pwm);
        huansic_motor_set(RightProp, 0.8);
    }
}
