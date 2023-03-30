// RobotBuilder Version: 4.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

// ROBOTBUILDER TYPE: Robot.

#include "Robot.h"
#include "Globals.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>
#include <iostream>
#include <fstream>
#include <cameraserver/CameraServer.h>
#include <cstdio>
#include <iomanip>
#include <ctime>

void Robot::RobotInit() {
  m_container = RobotContainer::GetInstance();
  m_container->m_swerveDrive.DrivePods(0.0, 0.0, 0.0, nullptr);

  if (TEST_STATE)
  {
    m_container->m_swerveDrive.SetVoltageCompensation();
  }
 

  m_container->m_elevator.Initialize();
  m_container->m_endEffector.Initialize();
  m_container->m_intake.Initialize();
  m_container->m_robotIntake.Initialize();

  // Get the USB camera from CameraServer
  // cs::UsbCamera camera = frc::CameraServer::StartAutomaticCapture();
  // camera.SetResolution(640,480);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want to run during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() 
{ 
  frc2::CommandScheduler::GetInstance().Run();

  // std::cout << "LEFT ENCODER ANGLE: " << m_container->m_swerveDrive.GetLeftPodEncoderPosition();
  // std::cout << "  RIGHT ENCODER ANGLE: " << m_container->m_swerveDrive.GetRightPodEncoderPosition();
  // std::cout << "  POINT ENCODER ANGLE: " << m_container->m_swerveDrive.GetPointPodEncoderPosition();
  // std::cout << std::endl;

  m_container->m_swerveDrive.DisplayPodPIDValues();

  frc::SmartDashboard::PutNumber("Recommend Offset L", -m_container->m_swerveDrive.GetLeftPodEncoderPosition()  + 90.0);
  frc::SmartDashboard::PutNumber("Recommend Offset R", -m_container->m_swerveDrive.GetRightPodEncoderPosition() + 90.0);
  frc::SmartDashboard::PutNumber("Recommend Offset P", -m_container->m_swerveDrive.GetPointPodEncoderPosition() + 90.0);


  if (TEST_STATE)
  {
    m_container->m_elevator.updateValues();

    // SmartDashboard Swerve Drive Motor Temperatures + indicators
    frc::SmartDashboard::PutNumber("Right Top Motor Temp", m_container->m_swerveDrive.GetMotorTemperature(RIGHT_POD, TOP_MOTOR));
    frc::SmartDashboard::PutBoolean("Right Top Temp Indicator", m_container->m_swerveDrive.GetMotorTemperature(RIGHT_POD, TOP_MOTOR) > max_motor_temp);
    frc::SmartDashboard::PutNumber("Right Bottom Motor Temp", m_container->m_swerveDrive.GetMotorTemperature(RIGHT_POD, BOTTOM_MOTOR));
    frc::SmartDashboard::PutBoolean("Right Bottom Temp Indicator", m_container->m_swerveDrive.GetMotorTemperature(RIGHT_POD, BOTTOM_MOTOR) > max_motor_temp);
    frc::SmartDashboard::PutNumber("Left Top Motor Temp", m_container->m_swerveDrive.GetMotorTemperature(LEFT_POD, TOP_MOTOR));
    frc::SmartDashboard::PutBoolean("Left Top Temp Indicator", m_container->m_swerveDrive.GetMotorTemperature(LEFT_POD, TOP_MOTOR) > max_motor_temp);
    frc::SmartDashboard::PutNumber("Left Bottom Motor Temp", m_container->m_swerveDrive.GetMotorTemperature(LEFT_POD, BOTTOM_MOTOR));
    frc::SmartDashboard::PutBoolean("Left Bottom Temp Indicator", m_container->m_swerveDrive.GetMotorTemperature(LEFT_POD, BOTTOM_MOTOR) > max_motor_temp);
    frc::SmartDashboard::PutNumber("Point Top Motor Temp", m_container->m_swerveDrive.GetMotorTemperature(POINT_POD, TOP_MOTOR));
    frc::SmartDashboard::PutBoolean("Point Top Temp Indicator", m_container->m_swerveDrive.GetMotorTemperature(POINT_POD, TOP_MOTOR) > max_motor_temp);
    frc::SmartDashboard::PutNumber("Point Bottom Motor Temp", m_container->m_swerveDrive.GetMotorTemperature(POINT_POD, BOTTOM_MOTOR));
    frc::SmartDashboard::PutBoolean("Point Bottom Temp Indicator", m_container->m_swerveDrive.GetMotorTemperature(POINT_POD, BOTTOM_MOTOR) > max_motor_temp);

    // SmartDashboard Swerve Drive Test Motor Speeds
    frc::SmartDashboard::PutNumber("Test Motor Speed", m_diagnosticSpeed);

  }
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

/**
 * This autonomous runs the autonomous command selected by your {@link
 * RobotContainer} class.
 */
void Robot::AutonomousInit() {
  m_autonomousCommand = m_container->GetAutonomousCommand();

  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Schedule();
  }
}

void Robot::AutonomousPeriodic() {

}

void Robot::TeleopInit() {
  // This makes sure that the autonomous stops running when
  // teleop starts running. If you want the autonomous to
  // continue until interrupted by another command, remove
  // this line or comment it out.
  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Cancel();
    m_autonomousCommand = nullptr;
  }
  fileOut = fopen("/home/lvuser/swerve-test.txt", "w");
}

double Joystick(double input, double deadzone) 
{ 
  return (std::fabs(input) < deadzone) ? 0 : input; 
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic() 
{
  if (TEST_STATE)
  {
    // updates pod angle offsets (on dashboard)
    m_container->m_swerveDrive.UpdatePodOffsetAngles();
    //update rotate multiplier
    m_container->m_swerveDrive.UpdatePodRotate();
    // updates pod p_PID vals (on dashboard)
    m_container->m_swerveDrive.UpdatePodPPID();
    // updates pod i_PID vals (on dashboard)
    m_container->m_swerveDrive.UpdatePodIPID();
    // updates pod d_PID vals (on dashboard)
    m_container->m_swerveDrive.UpdatePodDPID();
    // updates pod motor scaling vals (on dashboard)
    m_container->m_swerveDrive.UpdatePodMotorScaling();
    // updates pod aligned angles vals (on dashboard)
    m_container->m_swerveDrive.UpdatePodAlignedAngle();
  }

  // Controller Inputs - Driver Operations
  double targetJoystickLX = Joystick(m_container->getDriver()->GetLeftX(), k_jsDeadband);
  double targetJoystickLY = Joystick(m_container->getDriver()->GetLeftY(), k_jsDeadband);
  double targetJoystickRX = Joystick(m_container->getDriver()->GetRightX(), k_jsDeadband);
 
  if (TEST_STATE)
  {
    frc::SmartDashboard::PutNumber("LX", targetJoystickLX);
    frc::SmartDashboard::PutNumber("LY", targetJoystickLY);
    frc::SmartDashboard::PutNumber("RX", targetJoystickRX);
  }
  
  // Initial Swerve State
  bool initialSwerveState = m_container->getDriver()->GetStartButton();
  // Lock Swerve State
  bool lockSwerve = m_container->getDriver()->GetYButton();
  // Swerve Diagnostics State
  bool testRightPod = m_container->getDriver()->GetBButton();
  bool testLeftPod = m_container->getDriver()->GetXButton();
  bool testPointPod = m_container->getDriver()->GetAButton();
  int dPadValue = m_container->getDriver()->GetPOV();

  std::string driveCase = "NONE";
  double fileOutputs[6] = { 404, 404, 404, 404, 404, 404};

  if (!lockSwerve) 
  {
    if (
      std::fabs(targetJoystickLX) > k_jsDeadband ||
      std::fabs(targetJoystickLY) > k_jsDeadband ||
      std::fabs(targetJoystickRX) > k_jsDeadband
    ) 
    {
      // joystick inputs for swerve - NO scaling / ramp
      driveCase = "Drive No Scaling";
      m_container->m_swerveDrive.DrivePods(targetJoystickLX, targetJoystickLY, targetJoystickRX, fileOutputs);
      // std::cout << std::endl;
    }
    else if (initialSwerveState) 
    {
      // Initial Swerve State
      driveCase = "Initial state";
      m_container->m_swerveDrive.InitialSwerve();
    }
    else if (TEST_STATE && dPadValue != -1)
    {
      if ((testRightPod || testLeftPod || testPointPod) && (dPadValue == 0 || dPadValue == 180))
      {
        driveCase = "Pod diagnostic";
        std::string podInput;
        std::string motorInput; 
        podInput = testRightPod ? "RIGHT" : podInput;
        podInput = testLeftPod ? "LEFT" : podInput;
        podInput = testPointPod ? "POINT" : podInput;
        motorInput = dPadValue == 0 ? "TOP" : motorInput; 
        motorInput = dPadValue == 180 ? "BOTTOM" : motorInput;

        // set motors for testing
        m_container->m_swerveDrive.DiagonosticSwerveRotate(podInput, motorInput, 0.6);
      } else if ((!testRightPod && !testLeftPod && !testPointPod) && (dPadValue == 0 || dPadValue == 90 || dPadValue == 180 || dPadValue == 270)) {
        // TESTING FOR SWERVE ANGLE OFFSETS
        driveCase = "dpad offset testing";
        if (dPadValue == 180)
        {
          // forward
          m_container->m_swerveDrive.DrivePods(0.0, 0.2, 0.0, fileOutputs);
        } else if (dPadValue == 0)
        {
          // backward
          m_container->m_swerveDrive.DrivePods(0.0, -0.2, 0.0, fileOutputs);
        } else if (dPadValue == 90) {
          // right
          m_container->m_swerveDrive.DrivePods(0.2, 0.0, 0.0, fileOutputs);
        } else if (dPadValue == 270) {
          // left
          m_container->m_swerveDrive.DrivePods(-0.2, 0.0, 0.0, fileOutputs);
        } 
      } else {
        // stopped
        m_container->m_swerveDrive.DrivePods(0.0, 0.0, 0.0, fileOutputs);
      }
    }
    else {
      driveCase = "STOPPED";
      m_container->m_swerveDrive.DrivePods(0.0, 0.0, 0.0, fileOutputs);
    }
  } 
  else 
  {
    // lock swerve state
    driveCase = "lock state";
    m_container->m_swerveDrive.LockSwerve();
  }
  // std::cout << "CASE: " << driveCase << "  LX: " << targetJoystickLX << "     " << "LY: " << targetJoystickLY << "     " << "RX: " << targetJoystickRX << std::endl;
  
  for (int i = 0; i < 6; i++) {
    fputs(std::to_string(fileOutputs[i]).c_str(), fileOut);
    fputs(" ", fileOut);
    // std::cout << std::to_string(fileOutputs[i]).c_str() << " " << std::endl;
  }
  fputs("\n", fileOut);
  
  // Elevator Operations
  m_container->m_elevator.runElevator();

  // End Effector Operations
  m_container->m_endEffector.runEndEffector();

  // Intake Operations
  m_container->m_intake.runIntake();

  // Robot Intake Operations
  m_container->m_robotIntake.runRobotIntake();

  frc::SmartDashboard::PutString("Right Pod Case", m_container->m_swerveDrive.GetRightPodCase());
  frc::SmartDashboard::PutString("Left Pod Case", m_container->m_swerveDrive.GetLeftPodCase());
  frc::SmartDashboard::PutString("Point Pod Case", m_container->m_swerveDrive.GetPointPodCase());
  // frc::SmartDashboard::UpdateValues();
}

/**
 * This function is called periodically during test mode.
 */
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
