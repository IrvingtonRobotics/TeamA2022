#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor frontLeft = motor(PORT1, ratio18_1, false);
motor frontRight = motor(PORT5, ratio18_1, false);
motor backLeft = motor(PORT3, ratio18_1, false);
motor backRight = motor(PORT4, ratio18_1, false);
motor Intake = motor(PORT9, ratio18_1, false);
motor Flywheel = motor(PORT11, ratio6_1, false);
motor Pusher = motor(PORT8, ratio18_1, false);
motor Flywheel2 = motor(PORT2, ratio6_1, true);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}