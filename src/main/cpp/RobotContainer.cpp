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
#include "commands/AutonomousCommand.h"
#include "commands/AutoBalanceSwerve.h"
#include "commands/ScoreMidConeBackout.h"
#include "commands/ScoreTopConeBackout.h"
#include "Globals.h"

RobotContainer* RobotContainer::m_robotContainer = NULL;

RobotContainer::RobotContainer() : m_autonomousCommand()
{
    if (TEST_STATE) 
    {
        // Smartdashboard Joystick Inputs
        frc::SmartDashboard::PutNumber("LX", 0.0);
        frc::SmartDashboard::PutNumber("LY", 0.0);
        frc::SmartDashboard::PutNumber("RX", 0.0);

        // Smartdashboard Elevator values
        frc::SmartDashboard::PutNumber("Elevator P", 1.1);
        frc::SmartDashboard::PutNumber("Elevator I", 5.0);
        frc::SmartDashboard::PutNumber("Elevator D", 0.1);
        frc::SmartDashboard::PutNumber("Elevator Ramp", 0.0075);

        // Smartdashboard Balance Swerve PID values
        frc::SmartDashboard::PutNumber("Balance_P", 2.0);
        frc::SmartDashboard::PutNumber("Balance_I", 5.0);
        frc::SmartDashboard::PutNumber("Balance_D", 0.0);
        frc::SmartDashboard::PutNumber("Balance_Delta", 0.5);

        // PID vals for testing (just viewing)
        frc::SmartDashboard::PutNumber("Right P", 0.0);
        frc::SmartDashboard::PutNumber("Right I", 0.0);
        frc::SmartDashboard::PutNumber("Right D", 0.0);
        frc::SmartDashboard::PutNumber("Right StationKeep", 0.0);
        frc::SmartDashboard::PutNumber("Left P", 0.0);
        frc::SmartDashboard::PutNumber("Left I", 0.0);
        frc::SmartDashboard::PutNumber("Left D", 0.0);
        frc::SmartDashboard::PutNumber("Left StationKeep", 0.0);
        frc::SmartDashboard::PutNumber("Point P", 0.0);
        frc::SmartDashboard::PutNumber("Point I", 0.0);
        frc::SmartDashboard::PutNumber("Point D", 0.0);
        frc::SmartDashboard::PutNumber("Point StationKeep", 0.0);

        // Smartdashboard Swerve Drive Offsets
        frc::SmartDashboard::PutNumber("Left Offset", m_swerveDrive.GetLeftPodOffsetAngle());
        frc::SmartDashboard::PutNumber("Right Offset", m_swerveDrive.GetRightPodOffsetAngle());
        frc::SmartDashboard::PutNumber("Point Offset", m_swerveDrive.GetPointPodOffsetAngle());

        // Smartdashboard Swerve Drive rotate multiplier
        frc::SmartDashboard::PutNumber("Left Rotate", m_swerveDrive.GetLeftPodRotate());
        frc::SmartDashboard::PutNumber("Right Rotate", m_swerveDrive.GetRightPodRotate());
        frc::SmartDashboard::PutNumber("Point Rotate", m_swerveDrive.GetPointPodRotate());

        // Smartdashboard Swerve Drive p_PID
        frc::SmartDashboard::PutNumber("Left p_PID", m_swerveDrive.GetLeftPodPPID());
        frc::SmartDashboard::PutNumber("Right p_PID", m_swerveDrive.GetRightPodPPID());
        frc::SmartDashboard::PutNumber("Point p_PID", m_swerveDrive.GetPointPodPPID());

        // Smartdashboard Swerve Drive i_PID
        frc::SmartDashboard::PutNumber("Left i_PID", m_swerveDrive.GetLeftPodIPID());
        frc::SmartDashboard::PutNumber("Right i_PID", m_swerveDrive.GetRightPodIPID());
        frc::SmartDashboard::PutNumber("Point i_PID", m_swerveDrive.GetPointPodIPID());

        // Smartdashboard Swerve Drive d_PID
        frc::SmartDashboard::PutNumber("Left d_PID", m_swerveDrive.GetLeftPodDPID());
        frc::SmartDashboard::PutNumber("Right d_PID", m_swerveDrive.GetRightPodDPID());
        frc::SmartDashboard::PutNumber("Point d_PID", m_swerveDrive.GetPointPodDPID());

        // Smartdashboard Swerve Drive Motor Scaling
        frc::SmartDashboard::PutNumber("Left Motor Scaling", m_swerveDrive.GetLeftPodMotorScaling());
        frc::SmartDashboard::PutNumber("Right Motor Scaling", m_swerveDrive.GetRightPodMotorScaling());
        frc::SmartDashboard::PutNumber("Point Motor Scaling", m_swerveDrive.GetPointPodMotorScaling());

        // Smartdashboard Swerve Drive Aligned Angle
        frc::SmartDashboard::PutNumber("Left Aligned Angle", m_swerveDrive.GetLeftPodAlignedAngle());
        frc::SmartDashboard::PutNumber("Right Aligned Angle", m_swerveDrive.GetRightPodAlignedAngle());
        frc::SmartDashboard::PutNumber("Point Aligned Angle", m_swerveDrive.GetPointPodAlignedAngle());
        
        frc::SmartDashboard::PutString("Right Pod Case", m_swerveDrive.GetRightPodCase());
        frc::SmartDashboard::PutString("Left Pod Case", m_swerveDrive.GetLeftPodCase());
        frc::SmartDashboard::PutString("Point Pod Case", m_swerveDrive.GetPointPodCase());

        frc::SmartDashboard::PutNumber("Left Pod Voltage Comp.", 10.0);
        frc::SmartDashboard::PutNumber("Right Pod Voltage Comp.", 10.0);
        frc::SmartDashboard::PutNumber("Point Pod Voltage Comp.", 10.0);
    }

    // SmartDashboard Buttons
    // frc::SmartDashboard::PutData("Score Top Cone", new SequentialScoreTopCone(&m_elevator, &m_swerveDrive, &m_endEffector));

    // add options + setup auto chooser
    m_chooser.SetDefaultOption("Score Top Cone", new SequentialScoreTopCone(&m_elevator, &m_endEffector));
   
    m_chooser.AddOption("Drive Timed", new DriveTimed(&m_swerveDrive, 0.50, 0.0, 0.0, units::second_t(1.0)));
    m_chooser.AddOption("Balance Swerve", new AutoBalanceSwerve(&m_swerveDrive));
    m_chooser.AddOption("Score Top Cone", new SequentialScoreTopCone(&m_elevator, &m_endEffector));
    m_chooser.AddOption("Score Mid Cone", new SequentialScoreMidCone(&m_elevator, &m_endEffector));
    m_chooser.AddOption("Score Top Cone Backout", new ScoreTopConeBackout(&m_elevator, &m_swerveDrive, &m_endEffector));
    m_chooser.AddOption("Score Mid Cone Backout", new ScoreMidConeBackout(&m_elevator, &m_swerveDrive, &m_endEffector));
    // m_chooser.AddOption("Auto Balance", new AutoBalance(&m_swerveDrive));
    // m_chooser.AddOption("Score Top Cone Backout", new ScoreTopConeBackout(&m_elevator, &m_swerveDrive));
    // m_chooser.AddOption("Score Mid Cone Backout", new ScoreMidConeBackout(&m_elevator, &m_swerveDrive));
    // m_chooser.AddOption("Score Top Cone Balance", new ScoreTopConeWithBalance(&m_elevator, &m_endEffector, &m_swerveDrive));
    // m_chooser.AddOption("Score Mid Cone Balance", new ScoreMidConeWithBalance(&m_elevator, &m_swerveDrive));
    // m_chooser.AddOption("Custom - Experimental", new CustomCommand(&m_customCommandChoosers));
    frc::SmartDashboard::PutData("Auto Mode", &m_chooser);

    // "ah"
    // for (int i = 0; i < 5; i ++) {
    //     m_customCommandChoosers[i].SetDefaultOption("Do Nothing", new AutonomousCommand());
    //     m_customCommandChoosers[i].AddOption("Drive Timed", new DriveTimed(&m_swerveDrive, 0.50, 0.0, 0.0, units::second_t(1.0)));
    //     m_customCommandChoosers[i].AddOption("Auto Balance", new AutoBalance(&m_swerveDrive));
    //     m_customCommandChoosers[i].AddOption("Score Top Cone", new SequentialScoreTopCone(&m_elevator));
    //     m_customCommandChoosers[i].AddOption("Score Mid Cone", new SequentialScoreMidCone(&m_elevator));
    //     m_customCommandChoosers[i].AddOption("Score Top Cone Backout", new ScoreTopConeBackout(&m_elevator, &m_swerveDrive));
    //     m_customCommandChoosers[i].AddOption("Score Mid Cone Backout", new ScoreMidConeBackout(&m_elevator, &m_swerveDrive));
    //     m_customCommandChoosers[i].AddOption("Score Top Cone Balance", new ScoreTopConeWithBalance(&m_elevator, &m_swerveDrive));
    //     m_customCommandChoosers[i].AddOption("Score Mid Cone Balance", new ScoreMidConeWithBalance(&m_elevator, &m_swerveDrive));
    //     m_customCommandChoosers[i].AddOption("Initialize Swerve", new SwerveInitializeCommand(&m_swerveDrive));
    //     frc::SmartDashboard::PutData("Custom " + std::to_string(i + 1), &m_customCommandChoosers[i]);
    // }

    ConfigureButtonBindings();
}

RobotContainer* RobotContainer::GetInstance() 
{
    if (m_robotContainer == NULL) {
        m_robotContainer = new RobotContainer();
    }
    return m_robotContainer;
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
