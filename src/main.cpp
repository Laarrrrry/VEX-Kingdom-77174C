/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       6045188512                                                */
/*    Created:      9/2/2024, 7:55:17 PM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/



#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
controller Controller1 = controller(controllerType::primary);

brain Brain;

motor Left1 = motor(PORT6);
motor Left2 = motor(PORT7);
motor Left3 = motor(PORT8);
motor Right1 = motor(PORT3, true);
motor Right2 = motor(PORT12, true);
motor Right3 = motor(PORT5, true);

motor Intake = motor(PORT19);
motor Belt = motor(PORT18, true);

motor_group Left = motor_group(Left1, Left2, Left3);
motor_group Right = motor_group(Right1, Right2, Right3);

digital_out Clamp = digital_out(Brain.ThreeWirePort.A);





/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  Right.spinFor(forward, 50, degrees, false);
  Left.spinFor(forward, 50, degrees, false);

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................


    if(Controller1.Axis3.position() > 5)
    {
      Left.setVelocity(Controller1.Axis3.position(), percent);
      Right.setVelocity(Controller1.Axis3.position(), percent);

      Left.spin(reverse);
      Right.spin(reverse);
    }
    //Backward
    else if(Controller1.Axis3.position() < -5)
    {
      Left.setVelocity(Controller1.Axis3.position(), percent);
      Right.setVelocity(Controller1.Axis3.position(), percent);
 
      Left.spin(reverse);
      Right.spin(reverse);
    }
    //Turn Right
    else if(Controller1.Axis1.position() > 5)
    {
      Left.setVelocity(Controller1.Axis1.position()/1.8, percent);
      Right.setVelocity(Controller1.Axis1.position()/1.8, percent);

      Left.spin(reverse);
      Right.spin(forward);
    }
    //Turn Left
    else if(Controller1.Axis1.position() < -5)
    {
      Left.setVelocity(Controller1.Axis1.position()/1.8, percent);
      Right.setVelocity(Controller1.Axis1.position()/1.8, percent);
      
      Left.spin(reverse);
      Right.spin(forward);
    }
    else
    {
      Left.stop();
      Right.stop();
    }

    if(Controller1.ButtonR1.PRESSED)
    {
      Intake.setVelocity(75, percent);
      Belt.setVelocity(95, percent);
      Intake.spin(forward);
      Belt.spin(forward);

    }
    else if(Controller1.ButtonR2.PRESSED)
    {
      Intake.setVelocity(75, percent);
      Belt.setVelocity(95, percent);
      Intake.spin(reverse);
      Belt.spin(reverse);
    }
    else if(Controller1.ButtonX.PRESSED)
    {
      Intake.stop();
      Belt.stop();
    }
    

    if(Controller1.ButtonL1.PRESSED)
    {
      Clamp.set(true);
    }
    else if(Controller1.ButtonL2.PRESSED)
    {
      Clamp.set(false);
    }
    
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
