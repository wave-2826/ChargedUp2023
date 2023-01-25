// RobotBuilder Version: 4.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

// ROBOTBUILDER TYPE: Subsystem.

#include "subsystems/SwerveDrive.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <iostream>

using namespace rev;
using namespace frc;

/**
 * SwerveDrive implementation, schyncronizing individual swerve pods
 *
 * @author 2826WaveRobotics
 */
SwerveDrive::SwerveDrive() {
/*
    // All swerve module motors
    m_frontTopMotor = new CANSparkMax(58, CANSparkMaxLowLevel::MotorType::kBrushless);
    m_frontBottomMotor = new CANSparkMax(4, CANSparkMaxLowLevel::MotorType::kBrushless);
    m_rearTopMotor = new CANSparkMax(1, CANSparkMaxLowLevel::MotorType::kBrushless);
    m_rearBottomMotor = new CANSparkMax(2, CANSparkMaxLowLevel::MotorType::kBrushless);

    // Individual swerve pod instances
    //TODO: Fix this: object of abstract class type "SwervePod" is not allowed: -- pure virtual function "frc2::PIDSubsystem::GetMeasurement" has no overrider -- pure virtual function "frc2::PIDSubsystem::UseOutput" has no overriderC/C++(322)
    m_frontPod = new SwervePod(m_frontTopMotor, m_frontBottomMotor, 13.7, 45.0, 0);
    m_rearPod = new SwervePod(m_rearTopMotor, m_rearBottomMotor, 13.7, 45.0, 1);
    //m_backLeftPod = new SwervePod(m_leftBackTopMotor, m_leftBackBottomMotor, 1);
    //m_backRightPod = new SwervePod(m_rightBackTopMotor, m_rightBackBottomMotor, 2);

    // Locations for the swerve drive modules relative to the robot center.
    frc::Translation2d m_frontLocation{0.0_m, 0.0_m};
    frc::Translation2d m_rearLocation{0.0_m, 0.0_m};

    // Creating kinematics object using the module locations for 3 pod swerve
    // m_kinematics = new SwerveDriveKinematics<3>{
    //     m_frontLocation, m_backLeftLocation, m_backRightLocation
    // };

    // 2 pod swerve kinematics object using module locations
    m_kinematics = new SwerveDriveKinematics<2>{
        m_frontLocation, m_rearLocation
    };

*/
    SetName("SwerveDrive");
    SetSubsystem("SwerveDrive");

}

void SwerveDrive::initialize(){
    // m_frontPod->Initialize();
}

void SwerveDrive::Periodic() {
    // Put code here to be run every loop
    
}

void SwerveDrive::SimulationPeriodic() {
    // This method will be called once per scheduler run when in simulation

}

void SwerveDrive::DrivePods(double forward, double strafe, double rotation) {
    // const double k_gearRatioWheelSpeed = 3.2196;
    // const double k_wheelDiameterMeters = 0.0635;
    // const double k_wheelCircumferenceMeters = k_wheelDiameterMeters * (double)3.141592653;
    // const double k_maxMotorSpeed = 5200.0;

    // // transforming from pure joystick input into chassisspeeds
    // double transform = k_wheelCircumferenceMeters * k_gearRatioWheelSpeed * k_maxMotorSpeed;

    // // represents the velocity of the robot chassis
    // // ChassisSpeeds struct represents a velocity w.r.t to the robot frame of reference
    // // foward is negated to flip the axis of the LX input
    // frc::ChassisSpeeds speeds{(units::velocity::meters_per_second_t)(-forward*transform),
    //     (units::velocity::meters_per_second_t)(strafe*transform),
    //     (units::angular_velocity::radians_per_second_t)(rotation*transform)};
    
    // // returns each pods state (speed, angle)
    // // auto [front, backLeft, backRight] = m_kinematics->ToSwerveModuleStates(speeds);
    // auto [front, rear] = m_kinematics->ToSwerveModuleStates(speeds);

    // m_frontPod->Drive(front);

    // //m_frontPod->Drive(front);
    // //m_rearPod->Drive(rear);
    // //m_backLeftPod->Drive(backLeft);
    // //m_backRightPod->Drive(backRight);

}

