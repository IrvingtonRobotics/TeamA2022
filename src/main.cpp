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
// Intake               motor         9               
// Flywheel             motor         11              
// Pusher               motor         8               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <algorithm>
#include <cmath>
using namespace vex;

/*
  Normalizes a value to smoothen acceleration of motor speed

  @param val motor power
  @return normalized value
*/
double normalize(double val){
  double x = std::pow(val, 2) / 100;
  if(val < 0) {
    x *= -1;
  }
  return x;
}

void autonomus(void) {
  
}

int main(void) {
  // Initialize pusher position
  Pusher.setPosition(0, degrees);
  Pusher.setVelocity(100, velocityUnits::pct);

  // Driver control loop
  while(true) {
    // Get the raw sums of the X and Y joystick axes
    double front_left  = (double)(Controller1.Axis1.position(pct) + Controller1.Axis2.position(pct));
    double back_left   = (double)(Controller1.Axis1.position(pct) - Controller1.Axis2.position(pct));
    double front_right = (double)(Controller1.Axis1.position(pct) - Controller1.Axis2.position(pct));
    double back_right  = (double)(Controller1.Axis1.position(pct) + Controller1.Axis2.position(pct));
    
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
    
    front_left = normalize(front_left);
    back_left = normalize(back_left);
    front_right = normalize(front_right);
    back_right = normalize(back_right);

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
      Flywheel.spin(reverse, 100, velocityUnits::pct);
    } else{
      Flywheel.stop();
    }

    if(Controller1.ButtonY.pressing()) {
      Pusher.spinToPosition(180, degrees);
    } else {
      Pusher.spinToPosition(0, degrees);
    }
  }
}
