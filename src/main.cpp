/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Benjamin Man                                              */
/*    Created:      Sun Aug 14 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE Controller1FIGURED DEVICES ----
// Robot Controller1figuration:
// [Name]               [Type]        [Port(s)]
// Controller1troller1          Controller1troller                    
// frontLeft            motor         1               
// frontRight           motor         2               
// backLeft             motor         3               
// backRight            motor         4               
// ---- END VEXCODE Controller1FIGURED DEVICES ----

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// frontLeft            motor         1               
// frontRight           motor         5               
// backLeft             motor         3               
// backRight            motor         4               
// Intake               motor         10              
// Flywheel             motor         11              
// Pusher               motor         8               
// Flywheel2            motor         2               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <algorithm>
#include <cmath>
using namespace vex;

void stop(){
  frontLeft.stop(); 
  frontRight.stop();
  backLeft.stop(); 
  backRight.stop();
}

void setPower(double power){
  frontLeft.setVelocity(power, percent);
  frontRight.setVelocity(power, percent);
  backLeft.setVelocity(power, percent);
  backRight.setVelocity(power, percent);
}

void move(std::string dir, double time) {
  if(dir == "forward"){
    frontLeft.spin(fwd); 
    frontRight.spin(reverse);
    backLeft.spin(fwd); 
    backRight.spin(reverse);
  } else if(dir == "right"){ // good
    frontLeft.spin(fwd); 
    frontRight.spin(fwd);
    backLeft.spin(reverse); 
    backRight.spin(reverse);
  } else if(dir == "left"){ // good
    frontLeft.spin(reverse); 
    frontRight.spin(reverse);
    backLeft.spin(fwd); 
    backRight.spin(fwd);
  } else if(dir == "backward"){
    frontLeft.spin(reverse); 
    frontRight.spin(fwd);
    backLeft.spin(reverse); 
    backRight.spin(fwd);
  }

  vex::task::sleep(time);
  stop();
}

void moveDiag(int dir, double time){
  /*
      1     2
    
      4     3
  */
  switch(dir){
    case 1:
      backLeft.spin(fwd);
      frontRight.spin(reverse);
      break;
    case 2:
      frontLeft.spin(fwd);
      backRight.spin(fwd);
      break;
    case 3:
      backLeft.spin(reverse);
      frontRight.spin(reverse);
      break;
    case 4:
      frontLeft.spin(reverse);
      backRight.spin(reverse);
      break;
  }

  vex::task::sleep(time);
  stop();
}

void spin(int dir, double time){
  // time=20 is 90 degrees
  if(dir == -1){
    frontLeft.spin(reverse); 
    frontRight.spin(reverse);
    backLeft.spin(reverse); 
    backRight.spin(reverse);
  }
  if(dir == 1){
    frontLeft.spin(fwd); 
    frontRight.spin(fwd);
    backLeft.spin(fwd); 
    backRight.spin(fwd);
  }

  vex::task::sleep(time);
  stop();
}

void autonomous(void) {
  move("forward", 2000); // this rotates counterclockwise 90 degrees
  move("backward", 2000);
  move("left", 2000);
  move("right", 2000);

  moveDiag(1, 2000);
  moveDiag(2, 2000);
  moveDiag(3, 2000);
  moveDiag(4, 2000);

  spin(1, 2000);
  spin(-1, 2000);
}

double flywheelPow = 100;


void drivercontrol() {
  // Initialize pusher position
  Pusher.setPosition(0, degrees);
  Pusher.setVelocity(100, velocityUnits::pct);
  
  // Driver control loop
  while(true) {
    // Get the raw sums of the X and Y joystick axes
    double front_left  = (double)Controller1.Axis1.position(pct);
    double back_left   = (double)Controller1.Axis1.position(pct);
    double front_right = (double)Controller1.Axis1.position(pct);
    double back_right  = (double)Controller1.Axis1.position(pct);
    
    // Find the largest possible sum of X and Y
    double max_raw_sum = (double)(abs(Controller1.Axis1.position(pct)) + abs(Controller1.Axis2.position(pct)));
    
    // Find the largest joystick value
    double max_XYstick_value = (double)(std::max(abs(Controller1.Axis1.position(pct)),abs(Controller1.Axis2.position(pct))));
    
    // The largest sum will be scaled down to the largest joystick value, and the others will be
    // scaled by the same amount to preserve directionality
    if (max_raw_sum != 0) {
      front_left  = front_left / max_raw_sum * max_XYstick_value;
      back_left   = back_left / max_raw_sum * max_XYstick_value;
      front_right = front_right / max_raw_sum * max_XYstick_value;
      back_right  = back_right / max_raw_sum * max_XYstick_value;
    }

    // Robot controller rotation 
    // Naively add the rotational axis
    front_left  += Controller1.Axis3.position(pct);
    back_left   += Controller1.Axis3.position(pct);
    front_right -= Controller1.Axis3.position(pct);
    back_right  -= Controller1.Axis3.position(pct);

    front_left  += Controller1.Axis4.position(pct);
    back_left   -= Controller1.Axis4.position(pct);
    front_right += Controller1.Axis4.position(pct);
    back_right  -= Controller1.Axis4.position(pct);

    // Determine max sum capped 100
    max_raw_sum = std::max(std::abs(front_left),std::max(std::abs(back_left),std::max(std::abs(front_right),std::max(std::abs(back_right),100.0))));
    
    //Scale everything down by the factor that makes the largest only 100, if it was over
    double maxpower = 80;
    front_left  = front_left  / max_raw_sum * maxpower;
    back_left   = back_left   / max_raw_sum * maxpower;
    front_right = front_right / max_raw_sum * maxpower;
    back_right  = back_right  / max_raw_sum * maxpower;

    //Write the manipulated values out to the motors
    frontLeft.spin(fwd,front_left, velocityUnits::pct);
    backLeft.spin(fwd,back_left,  velocityUnits::pct);
    frontRight.spin(fwd,front_right,velocityUnits::pct);
    backRight.spin(fwd,back_right, velocityUnits::pct);

    if(Controller1.ButtonL1.pressing()){
      Intake.spin(fwd, 100, velocityUnits::pct);
    } else if(Controller1.ButtonL2.pressing()){
      Intake.spin(reverse, 100, velocityUnits::pct);
    } else {
      Intake.stop();
    }


    if(Controller1.ButtonR1.pressing()){
      Flywheel.spin(reverse, flywheelPow, velocityUnits::pct);
      Flywheel2.spin(reverse, flywheelPow, velocityUnits::pct);
    } else{
      Flywheel.stop();
      Flywheel2.stop();
    }

    if(Controller1.ButtonY.pressing()) {
      Pusher.spinToPosition(180, degrees);
    } else {
      Pusher.spinToPosition(0, degrees);
    }
  }
}

vex::brain::lcd screen;
void printFlywheelPow(){
  screen.clearScreen();
  screen.setCursor(0, 0);
  screen.print(flywheelPow);
}
void incrementFlywheelPow(){
  flywheelPow += 10;
  printFlywheelPow();
}

void decrementFlywheelPow(){
  flywheelPow -= 10;
  printFlywheelPow();
}

competition Competition;
int main(void){
  Competition.autonomous(autonomous);
  Competition.drivercontrol(drivercontrol);
  Controller1.ButtonUp.pressed(incrementFlywheelPow);
  Controller1.ButtonDown.pressed(decrementFlywheelPow);
}