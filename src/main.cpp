// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// frontLeft            motor         14              
// frontRight           motor         19              
// backLeft             motor         20              
// backRight            motor         17              
// Intake               motor         16              
// Flywheel             motor         5               
// Pusher               motor         18              
// Flywheel2            motor         4               
// Expansion            motor         11              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// frontLeft            motor         14              
// frontRight           motor         19              
// backLeft             motor         20              
// backRight            motor         17              
// Intake               motor         16              
// Flywheel             motor         5               
// Pusher               motor         18              
// Flywheel2            motor         4               
// Expansion            motor         15              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// frontLeft            motor         14              
// frontRight           motor         19              
// backLeft             motor         20              
// backRight            motor         17              
// Intake               motor         16              
// Flywheel             motor         5               
// Pusher               motor         18              
// Flywheel2            motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// frontLeft            motor         14              
// frontRight           motor         19              
// backLeft             motor         20              
// backRight            motor         17              
// Intake               motor         16              
// Flywheel             motor         5               
// Pusher               motor         18              
// Flywheel2            motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// frontLeft            motor         14              
// frontRight           motor         19              
// backLeft             motor         20              
// backRight            motor         17              
// Intake               motor         16              
// Flywheel             motor         5               
// Pusher               motor         18              
// Flywheel2            motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// frontLeft            motor         14              
// frontRight           motor         19              
// backLeft             motor         20              
// backRight            motor         17              
// Intake               motor         16              
// Flywheel             motor         11              
// Pusher               motor         18              
// Flywheel2            motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Benjamin Man and Abhay Harpalani                          */
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
// frontLeft            motor         14             
// frontRight           motor         19             
// backLeft             motor         20             
// backRight            motor         17             
// Intake               motor         16             
// Flywheel             motor         4              
// Pusher               motor         18             
// Flywheel2            motor         5              
// Controller1          controller                   
// ---- END VEXCODE CONFIGURED DEVICES ----
 
#include "vex.h"
#include <algorithm>
#include <cmath>
using namespace vex;
 
// vex::brain::lcd screen;
double flywheelPow = 75;
std::string forw = "forward";
std::string back = "backward";
std::string leff = "left";
std::string rigt = "right";
 
/**
double wheelRadius = 3.25 / 2;
// effective wheel radius since they are all at 45 degree angles
double effWheelRadius = (wheelRadius / sqrt(2));
double inchesPerDegree = (2 * M_PI * effWheelRadius) / 360;
**/


// general purpose functions
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
 

void sleepSeconds(double seconds){
 vex::task::sleep(seconds*1000);
}



// auton functions
void move(std::string dir, double seconds) {
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
 
 sleepSeconds(seconds);
 stop();
}


void moveDiag(int dir, double seconds){
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
     backRight.spin(reverse);
     break;
   case 3:
     backLeft.spin(reverse);
     frontRight.spin(fwd);
     break;
   case 4:
     frontLeft.spin(reverse);
     backRight.spin(fwd);
     break;
 }
 
 sleepSeconds(seconds);
 stop();
}
 
void rotate(std::string dir, double seconds){
 // seconds = 0.02 is 90 degrees
 if(dir == "left"){
   frontLeft.spin(reverse);
   frontRight.spin(reverse);
   backLeft.spin(reverse);
   backRight.spin(reverse);
 }
 if(dir == "right"){
   frontLeft.spin(fwd);
   frontRight.spin(fwd);
   backLeft.spin(fwd);
   backRight.spin(fwd);
 }
 
 sleepSeconds(seconds);
 stop();
}
 
void flywheelOn(){
  Flywheel.spin(fwd, flywheelPow, velocityUnits::pct);
  Flywheel2.spin(reverse, flywheelPow, velocityUnits::pct);
}
 
void flywheelOff(){
 Flywheel.stop();
 Flywheel2.stop();
}
 
void intakeOn(){
 Intake.spin(fwd, 100, velocityUnits::pct);
}
 
void intakeOff(){
 Intake.stop();
}
 
void shoot(int times = 1){
  Pusher.setVelocity(100, percent);
 flywheelOn();
 sleepSeconds(1);
 for(int i=0; i<times; i++){
   Pusher.spinToPosition(120, degrees);
   sleepSeconds(0.2);
   Pusher.spinToPosition(0, degrees);
   sleepSeconds(0.5);
 }
 flywheelOff();
}
 
void autonomous(void) {
  double deg90 = 0.55;
  double square1 = 1.1;
  setPower(80);
  
  flywheelPow = 50;
  shoot(2);

  rotate(rigt, deg90);
  intakeOn();
  move(forw, square1 + 0.2);
  sleepSeconds(0.5);
  intakeOff();

  rotate(leff, deg90 / 2);
  shoot(3);

  // return;



  flywheelPow = 75;
}



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
     Flywheel.spin(fwd, flywheelPow, velocityUnits::pct);
     Flywheel2.spin(reverse, flywheelPow, velocityUnits::pct);
   } else{
     Flywheel.stop();
     Flywheel2.stop();
   }
 
   if(Controller1.ButtonY.pressing()) {
     Pusher.spinToPosition(120, degrees);
   } else {
     Pusher.spinToPosition(0, degrees);
   }

    Expansion.setPosition(0, degrees);

   if(Controller1.ButtonX.pressing()) {
     Expansion.setPosition(90, degrees);
   } else {
     Expansion.setPosition(0, degrees);
   }
 }
}


void printFlywheelPow(){
 Controller1.Screen.clearScreen();
 Controller1.Screen.setCursor(0, 0);
 Controller1.Screen.print(flywheelPow);
}
void incrementFlywheelPow(){
 flywheelPow += 5;
 printFlywheelPow();
}
 
void decrementFlywheelPow(){
 flywheelPow -= 5;
 printFlywheelPow();
}
 
competition Competition;
int main(void){
 Competition.autonomous(autonomous);
 Competition.drivercontrol(drivercontrol);
 Controller1.ButtonUp.pressed(incrementFlywheelPow);
 Controller1.ButtonDown.pressed(decrementFlywheelPow);
}
