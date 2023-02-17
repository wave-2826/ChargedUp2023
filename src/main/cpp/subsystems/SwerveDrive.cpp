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
#include "Globals.h"

using namespace rev;
using namespace frc;

/**
 * SwerveDrive implementation, schyncronizing individual swerve pods
 *
 * @author 2826WaveRobotics
 */
SwerveDrive::SwerveDrive() 
{
    // inertial measurement unit (IMU) - senses acceleration, angular velocity, + magnetic fields
    m_pigeon = new ctre::phoenix::sensors::Pigeon2(k_pigeonID, k_canbus);

    // All swerve module motors
    // B = bottom , A = top
    m_rightTopMotor = new CANSparkMax(k_swerveRightTop, CANSparkMaxLowLevel::MotorType::kBrushless); // A
    m_rightBottomMotor = new CANSparkMax(k_swerveRightBottom, CANSparkMaxLowLevel::MotorType::kBrushless); // B
    // B = bottom , A = top
    m_leftTopMotor = new CANSparkMax(k_swerveLeftTop, CANSparkMaxLowLevel::MotorType::kBrushless); // A
    m_leftBottomMotor = new CANSparkMax(k_swerveLeftBottom, CANSparkMaxLowLevel::MotorType::kBrushless); // B
    // right = bottom , left = top
    m_pointTopMotor = new CANSparkMax(k_swervePointTop, CANSparkMaxLowLevel::MotorType::kBrushless); // L
    m_pointBottomMotor = new CANSparkMax(k_swervePointBottom, CANSparkMaxLowLevel::MotorType::kBrushless); // R

    // explicitly set all motors to coast
    m_rightTopMotor->SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    m_rightBottomMotor->SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    m_leftTopMotor->SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    m_leftBottomMotor->SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    m_pointTopMotor->SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    m_pointBottomMotor->SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);

    // set initial offset angles from the smart dashboard
    leftOffset = frc::SmartDashboard::GetNumber("Left Offset", 404.0);
    rightOffset = frc::SmartDashboard::GetNumber("Right Offset", 404.0);
    pointOffset = frc::SmartDashboard::GetNumber("Point Offset", 404.0);

    // Individual swerve pod instances
    m_leftPod = new SwervePod(m_leftTopMotor, m_leftBottomMotor, 0.01, leftOffset, k_leftPodEncoder);
    m_rightPod = new SwervePod(m_rightTopMotor, m_rightBottomMotor, 0.01, rightOffset, k_rightPodEncoder);
    m_pointPod = new SwervePod(m_pointTopMotor, m_pointBottomMotor, 0.01, pointOffset, k_pointPodEncoder);

    // Locations for the swerve drive modules relative to the robot center.
    frc::Translation2d m_rightLocation{(units::meter_t)-0.5*robotWidth, (units::meter_t)-0.5*robotHeight};
    frc::Translation2d m_leftLocation{(units::meter_t)0.5*robotWidth, (units::meter_t)-0.5*robotHeight};
    frc::Translation2d m_pointLocation{0.0_m, (units::meter_t)0.5*robotHeight};

    // 3 pod swerve kinematics object using module locations
    m_kinematics = new SwerveDriveKinematics<3> {
        m_rightLocation, m_leftLocation, m_pointLocation
    };

    SetName("SwerveDrive");
    SetSubsystem("SwerveDrive");
}

void SwerveDrive::Initialize()
{
    m_rightPod->Initialize();
    m_leftPod->Initialize();
    m_pointPod->Initialize();

    // TODO: configure pigeon (?)
    // m_pigeon->ConfigMountPosePitch();
}

// Put code here to be run every loop
void SwerveDrive::Periodic() 
{
    // TESTING Pigeon 2.0 
    #ifdef _TESTPIGEON
    // std::cout << "yaw: " << m_pigeon->GetYaw() << 
    //     "   pitch: " << m_pigeon->GetPitch() <<
    //     "   roll: " << m_pigeon->GetRoll() << std::endl;
    #endif

    // m_leftBottomMotor->Set(0.7);
    // m_pointBottomMotor->Set(0.7);
    // m_leftTopMotor->Set(0.1);
    // m_rightTopMotor->Set(0.1);
    // m_pointTopMotor->Set(0.1);
    // m_rightTopMotor->Set(0.7);
}

void SwerveDrive::SimulationPeriodic() 
{
    // This method will be called once per scheduler run when in simulation
}

void SwerveDrive::UpdatePodOffsetAngles() 
{
    // UPDATE pod offset angles
    m_leftPod->UpdateOffsetAngle();
    m_rightPod->UpdateOffsetAngle();
    m_pointPod->UpdateOffsetAngle();
}

double SwerveDrive::GetPodCurrent(int pod, bool motor) 
{
    switch (pod) {
        case 0: // right
            if (motor) // top
                return m_rightTopMotor->GetOutputCurrent();
            else
                return m_rightBottomMotor->GetOutputCurrent();
            break;
        case 1: // left
            if (motor) // top
                return m_leftTopMotor->GetOutputCurrent();
            else
                return m_leftBottomMotor->GetOutputCurrent();
            break;
        case 2: // point
            if (motor) // top
                return m_pointTopMotor->GetOutputCurrent();
            else
                return m_pointBottomMotor->GetOutputCurrent();
            break;
        default:
            return 0.0;
    }
}

double SwerveDrive::GetLeftPodOffsetAngle() 
{
    return m_leftPodOffsetAngle;
}

double SwerveDrive::GetRightPodOffsetAngle() 
{
    return m_rightPodOffsetAngle;
}

double SwerveDrive::GetPointPodOffsetAngle() 
{
    return m_pointPodOffsetAngle;
}

void SwerveDrive::SetLeftPodOffsetAngle(double offsetAngle)
{
    m_leftPodOffsetAngle = offsetAngle;
}

void SwerveDrive::SetRightPodOffsetAngle(double offsetAngle)
{
    m_rightPodOffsetAngle = offsetAngle;
}

void SwerveDrive::SetPointPodOffsetAngle(double offsetAngle)
{
    m_pointPodOffsetAngle = offsetAngle;
}

void SwerveDrive::DrivePods(double forward, double strafe, double rotation) 
{
    // transforming from pure joystick input into chassisspeeds
    double transform = k_wheelCircumferenceMeters * k_gearRatioWheelSpeed * k_maxMotorSpeed;

    // represents the velocity of the robot chassis
    // ChassisSpeeds struct represents a velocity w.r.t to the robot frame of reference
    // foward (LX) is considered the POINT
    frc::ChassisSpeeds speeds{(units::velocity::meters_per_second_t)(forward*transform),
        (units::velocity::meters_per_second_t)(-strafe*transform),
        (units::angular_velocity::radians_per_second_t)(-2*rotation*transform)};
    
    // returns each pods state (speed, angle)
    auto [right, left, point] = m_kinematics->ToSwerveModuleStates(speeds);

    m_rightPod->Drive(right);
    m_leftPod->Drive(left);
    m_pointPod->Drive(point);

    // if (m_rightPod->Drive(right) || m_leftPod->Drive(left) || m_pointPod->Drive(point)) {
    //     // std::string s[] = {"Right", "Left", "Point"};
    //     // std::string tb[] = {"Bottom", "Top"};

    //     // for (int i = 0; i < 6; i++) {
    //     //     std::cout << tb[i % 2] << " "<< s[i / 3] << ": "<< GetPodCurrent(i / 3, i % 2) << std::endl;
    //     // }
    // }
}

// TODO: TEST FUNCTION
void SwerveDrive::LockSwerve() 
{
    m_rightPod->LockState(m_lockedRightAngle);
    m_leftPod->LockState(m_lockedLeftAngle);
    m_pointPod->LockState(m_lockedPointAngle);
}

void SwerveDrive::DiagonosticSwerveRotate(std::string podInput, std::string motorInput, double speedIncrement)
{
    if (podInput == "RIGHT" && motorInput == "TOP") 
    {
        m_rightTopMotor->Set(speedIncrement);
    }
    else if (podInput == "RIGHT" && motorInput == "BOTTOM")
    {
        m_rightBottomMotor->Set(speedIncrement);
    }
    else if (podInput == "LEFT" && motorInput == "TOP")
    {
        m_leftTopMotor->Set(speedIncrement);
    }
    else if (podInput == "LEFT" && motorInput == "BOTTOM")
    {
        m_leftBottomMotor->Set(speedIncrement);
    }
    else if (podInput == "POINT" && motorInput == "TOP")
    {
        m_pointTopMotor->Set(speedIncrement);
    }
    else if (podInput == "POINT" && motorInput == "BOTTOM")
    {
        m_pointBottomMotor->Set(speedIncrement);
    }
}