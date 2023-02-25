// RobotBuilder Version: 4.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

// ROBOTBUILDER TYPE: RobotContainer.
#include <iostream>
#include "RobotContainer.h"
#include <frc2/command/ParallelRaceGroup.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "commands/ExtendElevatorTopCone.h"
#include "commands/ExtendElevatorMidCone.h"
#include "commands/SequentialScoreTopCone.h"

RobotContainer* RobotContainer::m_robotContainer = NULL;

RobotContainer::RobotContainer() : m_autonomousCommand()
{
    // Smartdashboard Swerve Drive Offsets
    frc::SmartDashboard::PutNumber("Left Offset", m_swerveDrive.GetLeftPodOffsetAngle());
    frc::SmartDashboard::PutNumber("Right Offset", m_swerveDrive.GetRightPodOffsetAngle());
    frc::SmartDashboard::PutNumber("Point Offset", m_swerveDrive.GetPointPodOffsetAngle());

    // SmartDashboard Buttons
    frc::SmartDashboard::PutData("Extend Elevator Top Cone", new ExtendElevatorTopCone(&m_elevator));
    frc::SmartDashboard::PutData("Extend Elevator Mid Cone", new ExtendElevatorMidCone(&m_elevator));
    frc::SmartDashboard::PutData("Initialize Swerve", new SwerveInitializeCommand(&m_swerveDrive));

    // add options + setup auto chooser
     m_chooser.SetDefaultOption("Drive Timed", new DriveTimed(&m_swerveDrive, 0.50, 0.0, 0.0, units::second_t(1.0)));
   
    m_chooser.AddOption("Drive Timed", new DriveTimed(&m_swerveDrive, 0.50, 0.0, 0.0, units::second_t(1.0)));
    m_chooser.AddOption("Auto Balance", new AutoBalance(&m_swerveDrive, 0.0, 0.0, 0.0, units::second_t(1.0)));
    m_chooser.AddOption("Score Top Cone", new SequentialScoreTopCone(&m_elevator));
    m_chooser.AddOption("Initialize Swerve", new SwerveInitializeCommand(&m_swerveDrive));
    
    frc::SmartDashboard::PutData("Auto Mode", &m_chooser);

    ConfigureButtonBindings();
}

RobotContainer* RobotContainer::GetInstance() 
{
    if (m_robotContainer == NULL) {
        m_robotContainer = new RobotContainer();
    }
    return(m_robotContainer);
}

void RobotContainer::ConfigureButtonBindings() {}

// The selected command will be run in autonomous
frc2::Command* RobotContainer::GetAutonomousCommand() 
{
  return m_chooser.GetSelected();
}

// driver controller
frc::XboxController* RobotContainer::getDriver() 
{
   return &m_driver;
}

// operator controller
frc::XboxController* RobotContainer::getOperator() 
{
   return &m_operator;
}

double RobotContainer::LinearInterpolate(double currentSpeed, double targetSpeed, double movePercentage) 
{
    double newSpeed = currentSpeed;
    // current speed is less than target speed
    if (currentSpeed < targetSpeed)
    {
        newSpeed = currentSpeed + std::fabs(targetSpeed - currentSpeed) * movePercentage;
        // newSpeed = speed + std::pow(std::fabs(targetSpeed - speed), 2);
    }
    // current speed is greater than target speed
    else if (currentSpeed > targetSpeed)
    {
        newSpeed = currentSpeed - std::fabs(targetSpeed - currentSpeed) * movePercentage;
        // newSpeed = speed - std::pow(std::fabs(targetSpeed - speed), 2);
    }
    // adding a buffer between newSpeed and targetSpeed
    if (std::fabs(targetSpeed - newSpeed) < 0.01f) {
        newSpeed = targetSpeed;
    }
    // prevent newSpeed from going outside of physical boundaries
    return std::clamp(newSpeed, -1.0, 1.0);
}

double RobotContainer::GetPreviousJoystickInputLX() 
{
    return m_previousJoystickInputLX;
}

void RobotContainer::SetPreviousJoystickInputLX(double input) 
{
    m_previousJoystickInputLX = input;
}

double RobotContainer::GetPreviousJoystickInputLY() 
{
    return m_previousJoystickInputLY;
}

void RobotContainer::SetPreviousJoystickInputLY(double input) 
{
    m_previousJoystickInputLY = input;
}

double RobotContainer::GetPreviousJoystickInputRX() 
{
    return m_previousJoystickInputRX;
}

void RobotContainer::SetPreviousJoystickInputRX(double input) 
{
    m_previousJoystickInputRX = input;
}
