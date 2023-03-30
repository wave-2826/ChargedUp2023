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
    // A = bottom , B = top
    m_rightTopMotor = new CANSparkMax(k_swerveRightTop, CANSparkMaxLowLevel::MotorType::kBrushless); // A
    m_rightBottomMotor = new CANSparkMax(k_swerveRightBottom, CANSparkMaxLowLevel::MotorType::kBrushless); // B
    // A = bottom , B = top
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

    // TODO: FIGURE OUT SOMETHING FOR AUTO
    // set initial offset angles from the smart dashboard
    leftOffset = frc::SmartDashboard::GetNumber("Left Offset", m_leftPodOffsetAngle);
    rightOffset = frc::SmartDashboard::GetNumber("Right Offset", m_rightPodOffsetAngle);
    pointOffset = frc::SmartDashboard::GetNumber("Point Offset", m_pointPodOffsetAngle);

    // set initial rotate multiplier from the smart dashboard
    leftRotate = frc::SmartDashboard::GetNumber("Left Rotate", m_leftRotate);
    rightRotate = frc::SmartDashboard::GetNumber("Right Rotate", m_rightRotate);
    pointRotate = frc::SmartDashboard::GetNumber("Point Rotate", m_pointRotate);

    // set initial p_PID values from the smart dashboard
    pLeft = frc::SmartDashboard::GetNumber("Left p_PID",   m_pLeft);
    pRight = frc::SmartDashboard::GetNumber("Right p_PID", m_pRight);
    pPoint = frc::SmartDashboard::GetNumber("Point p_PID", m_pPoint);

    // set initial i_PID values from the smart dashboard
    iLeft = frc::SmartDashboard::GetNumber("Left i_PID",   m_iLeft);
    iRight = frc::SmartDashboard::GetNumber("Right i_PID", m_iRight);
    iPoint = frc::SmartDashboard::GetNumber("Point i_PID", m_iPoint);
    
    // set initial d_PID values from the smart dashboard
    dLeft = frc::SmartDashboard::GetNumber("Left d_PID",   m_dLeft);
    dRight = frc::SmartDashboard::GetNumber("Right d_PID", m_dRight);
    dPoint = frc::SmartDashboard::GetNumber("Point d_PID", m_dPoint);

    // set initial motor scaling factors from the smart dashboard
    leftPodScaling = frc::SmartDashboard::GetNumber("Left Motor Scaling", m_leftPodScaling);
    rightPodScaling = frc::SmartDashboard::GetNumber("Right Motor Scaling", m_rightPodScaling);
    pointPodScaling = frc::SmartDashboard::GetNumber("Point Motor Scaling", m_pointPodScaling);

    // set initial aligned angles from the smart dashboard
    leftPodAlignedAngle = frc::SmartDashboard::GetNumber("Left Aligned Angle", m_leftPodAlignedAngle);
    rightPodAlignedAngle = frc::SmartDashboard::GetNumber("Right Aligned Angle", m_rightPodAlignedAngle);
    pointPodAlignedAngle = frc::SmartDashboard::GetNumber("Point Aligned Angle", m_pointPodAlignedAngle);

    // Individual swerve pod instances
    m_leftPod = new SwervePod(m_leftTopMotor, m_leftBottomMotor, pLeft, iLeft, dLeft, leftPodScaling, leftPodAlignedAngle, leftOffset, k_leftPodEncoder);
    m_rightPod = new SwervePod(m_rightTopMotor, m_rightBottomMotor, pRight, iRight, dRight, rightPodScaling, rightPodAlignedAngle, rightOffset, k_rightPodEncoder);
    m_pointPod = new SwervePod(m_pointTopMotor, m_pointBottomMotor, pPoint, iPoint, dPoint, pointPodScaling, pointPodAlignedAngle, pointOffset, k_pointPodEncoder);

    // Locations for the swerve drive modules relative to the robot center.
    frc::Translation2d m_rightLocation{(units::meter_t)-0.5*robotWidth, (units::meter_t)-0.5*robotHeight};
    frc::Translation2d m_leftLocation{(units::meter_t)0.5*robotWidth, (units::meter_t)-0.5*robotHeight};
    frc::Translation2d m_pointLocation{0.0_m, (units::meter_t)0.5*robotHeight};

    // 3 pod swerve kinematics object using module locations
    m_kinematics = new SwerveDriveKinematics<3> {
        m_rightLocation, m_leftLocation, m_pointLocation
    };

    // Set default gains for Yaw PID
    m_yawPGain = 1.0;
    m_yawIGain = 2.0;
    m_yawDGain = 0.5;
    m_yawTolerence = 2.0;
    m_yawTimer = 0;
    m_yawPID = new frc2::PIDController(m_yawPGain, m_yawIGain, m_yawDGain);

    SetName("SwerveDrive");
    SetSubsystem("SwerveDrive");
}

void SwerveDrive::Initialize()
{
    m_rightPod->Initialize();
    m_leftPod->Initialize();
    m_pointPod->Initialize();

    // TODO: configure pigeon (?)
    m_pigeon->ConfigMountPose(ctre::phoenix::sensors::AxisDirection::NegativeZ, ctre::phoenix::sensors::AxisDirection::PositiveY);

    // Initialize Yaw PID
    m_headingState = Heading_Init;
    m_yawPID->SetPID(m_yawPGain, m_yawIGain, m_yawDGain);
    m_yawPID->Reset();
}

void SwerveDrive::SetVoltageCompensation() {
    // TESTING: Voltage Compensation
    double rightVoltageCompensation = frc::SmartDashboard::GetNumber("Right Pod Voltage Comp.", 10.0);
    m_rightTopMotor->EnableVoltageCompensation(rightVoltageCompensation);
    m_rightBottomMotor->EnableVoltageCompensation(rightVoltageCompensation);
    double leftVoltageCompensation = frc::SmartDashboard::GetNumber("Left Pod Voltage Comp.", 10.0);
    m_leftTopMotor->EnableVoltageCompensation(leftVoltageCompensation);
    m_leftBottomMotor->EnableVoltageCompensation(leftVoltageCompensation);
    double pointVoltageCompensation = frc::SmartDashboard::GetNumber("point Pod Voltage Comp.", 10.0);
    m_pointTopMotor->EnableVoltageCompensation(pointVoltageCompensation);
    m_pointBottomMotor->EnableVoltageCompensation(pointVoltageCompensation);
}

// Put code here to be run every loop
void SwerveDrive::Periodic() 
{
    // // TESTING Pigeon 2.0 
    // #ifdef _TESTPIGEON
    // std::cout << "yaw: " << m_pigeon->GetYaw() << 
    //     "   pitch: " << m_pigeon->GetPitch() <<
    //     "   roll: " << m_pigeon->GetRoll() << std::endl;
    // #endif
}

void SwerveDrive::SimulationPeriodic() 
{
    // This method will be called once per scheduler run when in simulation
}

bool SwerveDrive::GetLeftPodReversed() {
    return m_leftPod->GetIsReversed();
}

bool SwerveDrive::GetRightPodReversed() {
    return m_rightPod->GetIsReversed();
}

bool SwerveDrive::GetPointPodReversed() {
    return m_pointPod->GetIsReversed();
}

double SwerveDrive::GetMotorTemperature(int pod, int motor)
{
    switch(pod) {
        case RIGHT_POD:
            if (motor == TOP_MOTOR) {
                return m_rightTopMotor->GetMotorTemperature();
            } else {
                return m_rightBottomMotor->GetMotorTemperature();
            }
            break;
        case LEFT_POD:
            if (motor == TOP_MOTOR) {
                return m_leftTopMotor->GetMotorTemperature();
            } else {
                return m_leftBottomMotor->GetMotorTemperature();
            }
            break;
        case POINT_POD:
            if (motor == TOP_MOTOR) {
                return m_pointTopMotor->GetMotorTemperature();
            } else {
                return m_pointBottomMotor->GetMotorTemperature();
            }
            break;
        default:
            return 0.0;
    }
    return 0.0;
}

double SwerveDrive::GetRobotPitch()
{
    return m_pigeon->GetPitch();
}

double SwerveDrive::GetRobotRoll()
{
    return m_pigeon->GetRoll();
}

double SwerveDrive::GetRobotYaw() 
{
    return m_pigeon->GetYaw();
}

void SwerveDrive::UpdatePodOffsetAngles() 
{
    // UPDATE pod offset angles
    m_leftPod->UpdateOffsetAngle();
    m_rightPod->UpdateOffsetAngle();
    m_pointPod->UpdateOffsetAngle();
}

void SwerveDrive::UpdatePodRotate() 
{
    // UPDATE pod rotate multiplier
    m_leftPod->UpdateRotate();
    m_rightPod->UpdateRotate();
    m_pointPod->UpdateRotate();
}

void SwerveDrive::UpdatePodPPID() 
{
    // UPDATE pod p_PID vals
    m_leftPod->UpdatePPID();
    m_rightPod->UpdatePPID();
    m_pointPod->UpdatePPID();
}

void SwerveDrive::UpdatePodIPID() 
{
    // UPDATE pod p_PID vals
    m_leftPod->UpdateIPID();
    m_rightPod->UpdateIPID();
    m_pointPod->UpdateIPID();
}

void SwerveDrive::UpdatePodDPID()
{
    // UPDATE pod d_PID vals
    m_leftPod->UpdateDPID();
    m_rightPod->UpdateDPID();
    m_pointPod->UpdateDPID();
}

void SwerveDrive::UpdatePodMotorScaling()
{
    // UPDATE pod motor scaling vals
    m_leftPod->UpdateMotorScaling();
    m_rightPod->UpdateMotorScaling();
    m_pointPod->UpdateMotorScaling();
}

void SwerveDrive::UpdatePodAlignedAngle()
{
    // UPDATE pod aligned angle vals
    m_leftPod->UpdateAlignedAngle();
    m_rightPod->UpdateAlignedAngle();
    m_pointPod->UpdateAlignedAngle();
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

// Offset Angle getters & setters
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

// Rotate multiplier getters & setters
double SwerveDrive::GetLeftPodRotate() 
{
    return m_leftRotate;
}
double SwerveDrive::GetRightPodRotate() 
{
    return m_rightRotate;
}
double SwerveDrive::GetPointPodRotate() 
{
    return m_pointRotate;
}
void SwerveDrive::SetLeftPodRotate(double rotate)
{
    m_leftRotate = rotate;
}
void SwerveDrive::SetRightPodRotate(double rotate)
{
    m_rightRotate = rotate;
}
void SwerveDrive::SetPointPodRotate(double rotate)
{
    m_pointRotate = rotate;
}

// p_PID getters & setters
double SwerveDrive::GetLeftPodPPID()
{
    return m_pLeft;
}
double SwerveDrive::GetRightPodPPID()
{
    return m_pRight;
}
double SwerveDrive::GetPointPodPPID()
{
    return m_pPoint;
}
void SwerveDrive::SetLeftPodPPID(double p)
{
    m_pLeft = p;
}
void SwerveDrive::SetRightPodPPID(double p)
{
    m_pRight = p;
}
void SwerveDrive::SetPointPodPPID(double p)
{
    m_pPoint = p;
}


// i_PID getters & setters
double SwerveDrive::GetLeftPodIPID()
{
    return m_iLeft;
}
double SwerveDrive::GetRightPodIPID()
{
    return m_iRight;
}
double SwerveDrive::GetPointPodIPID()
{
    return m_iPoint;
}
void SwerveDrive::SetLeftPodIPID(double i)
{
    m_iLeft = i;
}
void SwerveDrive::SetRightPodIPID(double i)
{
    m_iRight = i;
}
void SwerveDrive::SetPointPodIPID(double i)
{
    m_iPoint = i;
}

// d_PID getters & setters
double SwerveDrive::GetLeftPodDPID()
{
    return m_dLeft;
}
double SwerveDrive::GetRightPodDPID()
{
    return m_dRight;
}
double SwerveDrive::GetPointPodDPID()
{
    return m_dPoint;
}
void SwerveDrive::SetLeftPodDPID(double d)
{
    m_dLeft = d;
}
void SwerveDrive::SetRightPodDPID(double d)
{
    m_dRight = d;
}
void SwerveDrive::SetPointPodDPID(double d)
{
    m_dPoint = d;
}

// Show PID values for testing
void SwerveDrive::DisplayPodPIDValues()
{
    m_leftPod->DisplayPIDValues();
    m_rightPod->DisplayPIDValues();
    m_pointPod->DisplayPIDValues();
}

// motor scaling getters & setters
double SwerveDrive::GetLeftPodMotorScaling()
{
    return m_leftPodScaling;
}
double SwerveDrive::GetRightPodMotorScaling()
{
    return m_rightPodScaling;
}
double SwerveDrive::GetPointPodMotorScaling()
{
    return m_pointPodScaling;
}
void SwerveDrive::SetLeftPodMotorScaling(double scalingFactor) 
{
    m_leftPodScaling = scalingFactor;
}
void SwerveDrive::SetRightPodMotorScaling(double scalingFactor)
{
    m_rightPodScaling = scalingFactor;
}
void SwerveDrive::SetPointPodMotorScaling(double scalingFactor)
{
    m_pointPodScaling = scalingFactor;
}

// aligned angle getters & setters
double SwerveDrive::GetLeftPodAlignedAngle()
{
    return m_leftPodAlignedAngle;
}
double SwerveDrive::GetRightPodAlignedAngle()
{
    return m_rightPodAlignedAngle;
}
double SwerveDrive::GetPointPodAlignedAngle()
{
    return m_pointPodAlignedAngle;
}
void SwerveDrive::SetLeftPodAlignedAngle(double angle)
{
    m_leftPodAlignedAngle = angle;
}
void SwerveDrive::SetRightPodAlignedAngle(double angle)
{
    m_rightPodAlignedAngle = angle;
}
void SwerveDrive::SetPointPodAlignedAngle(double angle)
{
    m_pointPodAlignedAngle = angle;
}

double SwerveDrive::GetLeftPodEncoderPosition()
{
    return m_leftPod->GetEncoderPosition();
}

double SwerveDrive::GetRightPodEncoderPosition()
{
    return m_rightPod->GetEncoderPosition();
}

double SwerveDrive::GetPointPodEncoderPosition()
{
    return m_pointPod->GetEncoderPosition();
}

void SwerveDrive::DrivePods(double move, double strafe, double rotation, double *returnArray) 
{
    // transforming from pure joystick input into chassisspeeds
    double transform = k_wheelCircumferenceMeters * k_gearRatioWheelSpeed * k_maxMotorSpeed;

    // represents the velocity of the robot chassis
    // ChassisSpeeds struct represents a velocity w.r.t to the robot frame of reference
    // foward (LX) is considered the POINT
    frc::ChassisSpeeds speeds{(units::velocity::meters_per_second_t)((1.35)*move*transform),
        (units::velocity::meters_per_second_t)((-1.35)*strafe*transform),
        (units::angular_velocity::radians_per_second_t)((-4.5)*rotation*transform)};
    // frc::ChassisSpeeds speeds{(units::velocity::meters_per_second_t)(move*transform),
    //     (units::velocity::meters_per_second_t)(-strafe*transform),
    //     (units::angular_velocity::radians_per_second_t)((-2)*rotation*transform)};
    
    // returns each pods state (speed, angle)
    // Desired state -- velocity of wheel in RPM, angle in degrees
    auto [right, left, point] = m_kinematics->ToSwerveModuleStates(speeds);

    // TESTING SWERVE POD ALL ALIGNED ORCHESTRATION
    // bool rightAligned = m_rightPod->Drive(right, m_allAligned);
    // bool leftAligned = m_leftPod->Drive(left, m_allAligned);
    // bool pointAligned = m_pointPod->Drive(point, m_allAligned);
    double tempArray[2];
    m_rightPod->Drive(right, true, tempArray);
    if (returnArray != nullptr)
    {
        returnArray[0] = tempArray[0];
        returnArray[1] = tempArray[1];
    }
    double tempArray2[2];
    m_leftPod->Drive(left, true, tempArray2);
    if (returnArray != nullptr)
    {
        returnArray[2] = tempArray2[0];
        returnArray[3] = tempArray2[1];
    }
    double tempArray3[2];
    m_pointPod->Drive(point, true, tempArray3);
    if (returnArray != nullptr)
    {
        returnArray[4] = tempArray3[0];
        returnArray[5] = tempArray3[1];
    }
    
    // m_allAligned = rightAligned && leftAligned && pointAligned;
    
    // std::cout << "RIGHT POD ALIGNED: " << rightAligned<< std::endl;
    // std::cout << "LEFT POD ALIGNED:  " << leftAligned << std::endl;
    // std::cout << "POINT POD ALIGNED: " << pointAligned << std::endl;

    // Runs pod drives and prints out each pod's current
    // if (m_rightPod->Drive(right) || m_leftPod->Drive(left) || m_pointPod->Drive(point)) {
    //     // std::string s[] = {"Right", "Left", "Point"};
    //     // std::string tb[] = {"Bottom", "Top"};

    //     // for (int i = 0; i < 6; i++) {
    //     //     std::cout << tb[i % 2] << " "<< s[i / 3] << ": "<< GetPodCurrent(i / 3, i % 2) << std::endl;
    //     // }
    // }
}

std::string SwerveDrive::GetRightPodCase() {
    return m_rightPod->GetCurrentCase();
}

std::string SwerveDrive::GetLeftPodCase() {
    return m_leftPod->GetCurrentCase();
}

std::string SwerveDrive::GetPointPodCase() {
    return m_pointPod->GetCurrentCase();
}

void SwerveDrive::LockSwerve() 
{
    m_rightPod->LockState(m_lockedRightAngle);
    m_leftPod->LockState(m_lockedLeftAngle);
    m_pointPod->LockState(m_lockedPointAngle);
}

bool SwerveDrive::InitialSwerve() 
{
    bool rightPodInitialized = m_rightPod->InitialState();
    bool leftPodInitialized = m_leftPod->InitialState();
    bool pointPodInitialized = m_pointPod->InitialState();
    if (rightPodInitialized && leftPodInitialized && pointPodInitialized)
    {
        return true;
    }
    else 
    {
        return false;
    }
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

void SwerveDrive::initHeading()
{
    m_yawTimer = 0;
    m_yawPID->Reset();
    m_headingState = Heading_Init;
}

void SwerveDrive::HeadingSwerve(double targetSpeed)
{
    static const double k_maxYawPIDOutput = 5.0; // May need to adjust based on testing
    double moveCmd = 0.0;
    double strafeCmd = 0.0;
    double rotCmd = 0.0;
    double currentYaw = m_pigeon->GetYaw();
    
    switch (m_headingState)
    {
        case Heading_Init:
            m_startingYaw = currentYaw;
            if (targetSpeed > 0.0)
            {
                m_yawTimer = 0;
                m_yawPID->Reset();
                m_headingState = Heading_Active;
            }
            break;
        case Heading_Active:
            if (std::fabs(m_startingYaw - currentYaw) > m_yawTolerence)
            {
                double pidRotationOut = m_yawPID->Calculate(currentYaw, m_startingYaw);
                std::cout << "YawPID Out: " << pidRotationOut << std::endl;
                rotCmd = pidRotationOut / k_maxYawPIDOutput;
                if (rotCmd > 1.0)
                {
                    rotCmd = 1.0;
                }
                else if (rotCmd < -1.0)
                {
                    rotCmd = -1.0;
                }      
            }

            moveCmd = targetSpeed;
            // Turn off if no longer commanding to drive
            if(targetSpeed == 0)
            {
                m_yawTimer++;
                if (m_yawTimer > ONE_SECOND)
                {
                    m_headingState = Heading_Init;
                }                
            }
            else
            {
                m_yawTimer = 0;
            }
            break;
        
        default:
            break;
    }
    
    DrivePods(moveCmd, strafeCmd, rotCmd, nullptr);
    std::cout << "Yaw: " << currentYaw << " Target: " << m_startingYaw << " Rotation: " << rotCmd << std::endl;

}