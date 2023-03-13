#include "subsystems/SwervePod.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "math.h"
#include <iostream>
#include <string>

/**
 * SwervePod implementation - including motors, absolute encoder, and offset angle of encoder ZERO
 * associated with each individual pod. Included functions contain the math to calculate individual 
 * pod behaviors based utilizing the wpilib kinematics library returning target angle and speed 
 *
 * @author 2826WaveRobotics
 */
SwervePod::SwervePod(rev::CANSparkMax *topMotor, rev::CANSparkMax *bottomMotor, double p_PID, double motorScaling, double alignedAngle, double offsetAngle, int encoderChannel) 
{
    m_topMotor = topMotor;
    m_bottomMotor = bottomMotor;
    m_topEncoder = new rev::SparkMaxRelativeEncoder(m_topMotor->GetEncoder());
    m_bottomEncoder = new rev::SparkMaxRelativeEncoder(m_bottomMotor->GetEncoder());

    m_p = p_PID;
    m_offsetAngle = offsetAngle;
    m_encoderChannel = encoderChannel;
    m_motorScaling = motorScaling;
    m_alignedAngle = alignedAngle;

    // convert encoder channel to pod designation
    switch(encoderChannel) {
        case 0:
            m_podName = "Right";
            break;
        case 1:
            m_podName = "Left";
            break;
        case 2:
            m_podName = "Point";
            break;
    }

    // DIO - returns val as a ratio of hi-time v low-time
    m_podEncoder = new frc::DutyCycleEncoder(encoderChannel);
    m_podEncoder->SetConnectedFrequencyThreshold(975.6);
}

// TODO: Move to a conversion/util file
// Convert from absolute encoder position to degrees
double ToDegree(double pos)
{
    // double deg_value = pos/1024.0*360.0;
    double deg_value = pos * 360.0;

    return deg_value;
}

// TODO: Move to a conversion/util file
// Convert degrees to radians
double ToRadian(double degrees)
{
    return degrees * (3.14159 / 180.0);
}

void SwervePod::Periodic()
{

}

// update offset angles using the smart dashboard inputs (used for quick optimization)
void SwervePod::UpdateOffsetAngle()
{
    switch(m_encoderChannel) {
        case 0:
            m_podName = "Right";
            m_offsetAngle = frc::SmartDashboard::GetNumber("Right Offset", 404.0);
            break;
        case 1:
            m_podName = "Left";
            m_offsetAngle = frc::SmartDashboard::GetNumber("Left Offset", 404.0);
            break;
        case 2:
            m_podName = "Point";
            m_offsetAngle = frc::SmartDashboard::GetNumber("Point Offset", 404.0);
            break;
    }
}

// update p_PID using the smart dashboard inputs (used for quick optimization)
void SwervePod::UpdatePPID()
{
    switch(m_encoderChannel) {
        case 0:
            m_podName = "Right";
            m_p = frc::SmartDashboard::GetNumber("Right p_PID", 1.0);
            break;
        case 1:
            m_podName = "Left";
            m_p = frc::SmartDashboard::GetNumber("Left p_PID", 1.0);
            break;
        case 2:
            m_podName = "Point";
            m_p = frc::SmartDashboard::GetNumber("Point p_PID", 1.0);
            break;
    }
}

// update d_PID using the smart dashboard inputs (used for quick optimization)
void SwervePod::UpdateDPID()
{
    switch(m_encoderChannel) {
        case 0:
            m_podName = "Right";
            m_d = frc::SmartDashboard::GetNumber("Right d_PID", 0.0);
            break;
        case 1:
            m_podName = "Left";
            m_d = frc::SmartDashboard::GetNumber("Left d_PID", 0.0);
            break;
        case 2:
            m_podName = "Point";
            m_d = frc::SmartDashboard::GetNumber("Point d_PID", 0.0);
            break;
    }
}

// update motor scaling using the smart dashboard inputs (used for quick optimization)
void SwervePod::UpdateMotorScaling()
{
    switch(m_encoderChannel) {
        case 0:
            m_podName = "Right";
            m_motorScaling = frc::SmartDashboard::GetNumber("Right Motor Scaling", 0.01);
            break;
        case 1:
            m_podName = "Left";
            m_motorScaling = frc::SmartDashboard::GetNumber("Left Motor Scaling", 0.01);
            break;
        case 2:
            m_podName = "Point";
            m_motorScaling = frc::SmartDashboard::GetNumber("Point Motor Scaling", 0.01);
            break;
    }
}

// update aligned angle limit using the smart dashboard inputs (used for quick optimization)
void SwervePod::UpdateAlignedAngle()
{
    switch(m_encoderChannel) {
        case 0:
            m_podName = "Right";
            m_alignedAngle = frc::SmartDashboard::GetNumber("Right Aligned Angle", 404.0);
            break;
        case 1:
            m_podName = "Left";
            m_alignedAngle = frc::SmartDashboard::GetNumber("Left Aligned Angle", 404.0);
            break;
        case 2:
            m_podName = "Point";
            m_alignedAngle = frc::SmartDashboard::GetNumber("Point Aligned Angle", 404.0);
            break;
    }
}

void SwervePod::SimulationPeriodic()
{
    // This method will be called once per scheduler run when in simulation
}

void SwervePod::Initialize()
{
    // 0 is mechanical - offsets will have to be set in code
    m_initialized = true;
    m_counter = 0;
}

int SwervePod::GetCounter()
{
    return m_counter;
}

void SwervePod::SetCounter(int count)
{
    m_counter = count;
}

bool SwervePod::GetIsReversed()
{
    return m_isReversed;
}

void SwervePod::FlipIsReversed()
{
    m_isReversed = !m_isReversed;
}

std::string SwervePod::GetCurrentCase() {
    return m_currentCase;
}

// Track Position of Module
double SwervePod::GetPreviousAngle()
{
    return m_previousAngle;
}
void SwervePod::SetPreviousAngle(double angle)
{
    m_previousAngle = angle;
}
// Track delta D
double SwervePod::GetDeltaD()
{
    return m_deltaD;
}
void SwervePod::SetDeltaD(double delta)
{
    m_deltaD = delta;
}

/**
 * takes the swerve module state and calculates behavior based on 4 cases
 * (aligned, optimize > 90, optimize < -90, rotate)
 * 
 * @param SwerveModuleState state (speed, angle)
*/
void SwervePod::Drive(frc::SwerveModuleState state, bool allAligned, double *returnArray)
{
    // TODO: set max motor speeds
    double topMotorSpeed = 0.0;
    double bottomMotorSpeed = 0.0;

    // tracking angles
    // pod state angle (target) is -180 to 180
    // encoder angle (current) is 0 - 360
    // offsetAngle adjusts "forward" to align to position on robot
    double current_angle = m_offsetAngle + ToDegree(m_podEncoder->GetAbsolutePosition());
    // double current_angle = ToDegree(m_podEncoder->GetAbsolutePosition());
    double target_angle;
    if (!GetIsReversed()) {
        target_angle = state.angle.Degrees().value() + 180.0;
    } else {
        target_angle = state.angle.Degrees().value() + 360.0;
        if (target_angle >= 360) {
            target_angle -= 360.0;
        }
    }

    if (target_angle < 0) {
        target_angle += 360;
    }

    // calculate delta d
    SetDeltaD(current_angle - GetPreviousAngle());
    
    // std::cout << m_podName << "(rev? " << GetIsReversed() << ") -> current: " << current_angle << "   target: " << target_angle << std::endl;
    // std::cout << m_podName << "-> delta: " << GetDeltaD() << " current: " << current_angle << " prev: " << GetPreviousAngle() << std::endl;
    // std::cout << m_podName << "D: " << m_d * GetDeltaD() << "delta: " << GetDeltaD() << std::endl;
    
    // conversion from input state speed (rpm) to a motor power % val (0-1)
    double commanded_speed = (state.speed.value() / 5200.0);
    if (1 < commanded_speed)
    {
        commanded_speed = 1;
    }

    double angle_delta = target_angle - current_angle;
    if (angle_delta > 180.0)
    {
        angle_delta -= 360.0;
    }
    else if (angle_delta < -180.00)
    {
        angle_delta += 360.0;
    }
    double angle_delta_optimized = 0.0;
    double normalizer = 1 / 180.0;
    std::string swerveCase = "DID NOT ENTER";

    if (fabs(angle_delta) < m_alignedAngle)
    {
        // tuning factor is the P in PID (if we decide to use it)
        // double tunedAngleDelta = angle_delta * turnTuningFactor;

        // check aligned
        swerveCase = "ALIGNED";

        if (allAligned)
        {
            // station keep alg
            double stationKeepTop;
            double stationKeepBottom;
            double divisor;
            if (GetIsReversed())
            {
                stationKeepTop = (1.0 - m_p * angle_delta * normalizer + m_d * GetDeltaD());
                stationKeepBottom = (1.0 + m_p * angle_delta * normalizer + m_d * GetDeltaD());
            }
            else
            {            
                stationKeepTop = (1.0 + m_p * angle_delta * normalizer + m_d * GetDeltaD());                
                stationKeepBottom = (1.0 - m_p * angle_delta * normalizer + m_d * GetDeltaD());
            }
            if (fabs(stationKeepTop) > fabs(stationKeepBottom))
            {
                divisor = stationKeepTop / stationKeepBottom;
            }
            else
            {
                divisor = stationKeepBottom / stationKeepTop;
            }

            if (!GetIsReversed())
            {
                topMotorSpeed = -commanded_speed * (stationKeepTop / divisor);
                bottomMotorSpeed = -commanded_speed * (stationKeepBottom / divisor);
            }
            else
            {
                topMotorSpeed = commanded_speed * (stationKeepTop / divisor);
                bottomMotorSpeed = commanded_speed * (stationKeepBottom / divisor);
            }
        }
    }
    else if (angle_delta < -90.0)
    {
        // check optimal path
        swerveCase = "OPTIMIZE < -90";

        FlipIsReversed();
        if (!GetIsReversed())
        {
            angle_delta_optimized = (angle_delta - 180.0);
        }
        else
        {
            angle_delta_optimized = (angle_delta + 180.0);
        }

        topMotorSpeed = commanded_speed * angle_delta_optimized * normalizer;
        bottomMotorSpeed = -commanded_speed * angle_delta_optimized * normalizer;
    }
    else if (angle_delta > 90.0)
    {
        // check optimal path
        swerveCase = "OPTIMIZE > 90";

        FlipIsReversed();
        if (!GetIsReversed())
        {
            angle_delta_optimized = (angle_delta - 180.0);
        }
        else
        {
            angle_delta_optimized = (angle_delta + 180.0);
        }

        topMotorSpeed = -commanded_speed * angle_delta_optimized * normalizer;
        bottomMotorSpeed = commanded_speed * angle_delta_optimized * normalizer;
    }
    else
    {
        swerveCase = "ROTATE";

        // min max functions to add (P) of PID
        // if ( angle_delta < 0 ) {
        //     // angle delta is negative
        //     topMotorSpeed = -commanded_speed * (std::min(-turnTuningFactor, angle_delta * normalizer));
        //     bottomMotorSpeed = commanded_speed * (std::min(-turnTuningFactor, angle_delta * normalizer));
        // } else {
        //     // angle delta is positive
        //     topMotorSpeed = -commanded_speed * (std::max(turnTuningFactor, angle_delta * normalizer));
        //     bottomMotorSpeed = commanded_speed * (std::max(turnTuningFactor, angle_delta * normalizer));
        // }

        topMotorSpeed = -commanded_speed * angle_delta * normalizer;
        bottomMotorSpeed = commanded_speed * angle_delta * normalizer;   
    }

    // speed safety - ensure not commanding more than 100% motor speed
    // topMotorSpeed = std::clamp(topMotorSpeed, -1.0, 1.0);
    // bottomMotorSpeed = std::clamp(bottomMotorSpeed, -1.0, 1.0);

    // SCALE motor speeds
    double scaledTopMotorSpeed = LinearInterpolate(GetPreviousTopMotorSpeed(), topMotorSpeed, m_motorScaling);
    double scaledBottomMotorSpeed = LinearInterpolate(GetPreviousBottomMotorSpeed(), bottomMotorSpeed, m_motorScaling);
    m_topMotor->Set(scaledTopMotorSpeed);
    m_bottomMotor->Set(scaledBottomMotorSpeed);
    SetPreviousTopMotorSpeed(scaledTopMotorSpeed);
    SetPreviousBottomMotorSpeed(scaledBottomMotorSpeed);

    SetPreviousAngle(current_angle);
    m_currentCase = swerveCase;

    returnArray[0] = angle_delta;
    returnArray[1] = target_angle;

    // auto balance test printouts
    // std::cout << "drive pod - INITIALIZED" << std::endl;
    // std::cout << m_podName << " -> target: " << target_angle << "  cur: " << current_angle << "  offset: " << m_offsetAngle << std::endl;

    // assign motor speeds - NO SCALING
    // m_topMotor->Set(topMotorSpeed);
    // m_bottomMotor->Set(bottomMotorSpeed);
    
    // std::cout << "CASE: " << swerveCase << "         T: " << target_angle << " C: " << current_angle <<  std::endl;

    // return std::strcmp(swerveCase.c_str(), "ALIGNED") == 0;

    ///////////////////////////////// TESTING PRINTOUTS ///////////////////////////////////////////////

    // if (GetCounter() > 0)
    // {

        // TESTING
        // if (swerveCase == "ROTATE" && m_podName == "Right") {
        //     std::cout << m_podName << "   -->   T: " << topMotorSpeed << "   B: " << bottomMotorSpeed << std::endl; 
        // }  
        // std::cout << m_podName << "   -->   T: " << topMotorSpeed << "   B: " << bottomMotorSpeed << "   CMD: " << commanded_speed << std::endl; 
          

        // SWERVE CASE
        // std::cout << swerveCase << std::endl;
        // std::cout << "reversed? " << GetIsReversed() << std::endl; 

        // ANGLES
        // std::cout << "CASE: " << swerveCase << "         T: " << target_angle << " C: " << current_angle <<  std::endl;
        // std::cout << m_podName << " current angle: " << current_angle << std::endl;
        // std::cout << "target angle: " << target_angle << std::endl << std::endl;
        // std::cout << m_podName << " offset: " << m_offsetAngle << std::endl;
        // std::cout << "angle delta: " << angle_delta << std::endl;

        // MOTOR SPEEDS
        // std::cout << topMotorSpeed <<  std::endl;
        // std::cout << bottomMotorSpeed << std::endl <<  std::endl;
        // std::cout << "commanded: " << commanded_speed << std::endl << std::endl;
        
    //     SetCounter(0);
    //     return true;
    // }
    // else
    // {
    //     int current_count = GetCounter();
    //     SetCounter(current_count + 1);
    // }
    // return false;
}

/**
 * Function that takes the target angle and calculates a rotate state to "lock" drivetrain
 * 
 * @param double target angle
*/
void SwervePod::LockState(double target_angle)
{
    double topMotorSpeed = 0.0;
    double bottomMotorSpeed = 0.0;

    // tracking angles
    // pod state angle (target) is -180 to 180
    // encoder angle (current) is 0 - 360
    // offsetAngle adjusts "forward" to align to position on robot
    double current_angle = m_offsetAngle + ToDegree(m_podEncoder->GetAbsolutePosition());
    
    // conversion from input state speed (rpm) to a motor power % val (0-1)
    double commanded_speed = 0.75;
    
    double angle_delta = target_angle - current_angle;
    if (angle_delta > 180.0)
    {
        angle_delta -= 360.0;
    }
    else if (angle_delta < -180.00)
    {
        angle_delta += 360.0;
    }
    double normalizer = 1 / 180.0;

    if (fabs(angle_delta) < 25) {
        topMotorSpeed = 0;
        bottomMotorSpeed = 0;
    } else {
        topMotorSpeed = -commanded_speed * angle_delta * normalizer;
        bottomMotorSpeed = commanded_speed * angle_delta * normalizer;
    }            

    // assign motor speeds
    m_topMotor->Set(topMotorSpeed);
    m_bottomMotor->Set(bottomMotorSpeed);
}

/**
 * Function that sets wheel orientation to straighten to "initialize" drivetrain
*/
bool SwervePod::InitialState()
{
    double topMotorSpeed = 0.0;
    double bottomMotorSpeed = 0.0;
    double initialAngle = 90.0;

    // tracking angles
    // pod state angle (target) is -180 to 180
    // encoder angle (current) is 0 - 360
    // offsetAngle adjusts "forward" to align to position on robot
    double current_angle = m_offsetAngle + ToDegree(m_podEncoder->GetAbsolutePosition());
    
    // conversion from input state speed (rpm) to a motor power % val (0-1)
    double commanded_speed = 1.0;
    
    double angle_delta = initialAngle - current_angle;
    if (angle_delta > 180.0)
    {
        angle_delta -= 360.0;
    }
    else if (angle_delta < -180.00)
    {
        angle_delta += 360.0;
    }
    double normalizer = 1 / 180.0;

    if (fabs(angle_delta) < 25) {
        topMotorSpeed = 0;
        bottomMotorSpeed = 0;
        m_topMotor->Set(topMotorSpeed);
        m_bottomMotor->Set(bottomMotorSpeed);
        return true;
    } else {
        topMotorSpeed = -commanded_speed * angle_delta * normalizer;
        bottomMotorSpeed = commanded_speed * angle_delta * normalizer;
    }            

    // assign motor speeds
    m_topMotor->Set(topMotorSpeed);
    m_bottomMotor->Set(bottomMotorSpeed);
    return false;
}

// MOTOR SCALING FUNCTIONS
double SwervePod::GetPreviousTopMotorSpeed()
{
    return m_previousTopMotorSpeed;
}
void SwervePod::SetPreviousTopMotorSpeed(double input)
{
    m_previousTopMotorSpeed = input;
}
double SwervePod::GetPreviousBottomMotorSpeed()
{
    return m_previousBottomMotorSpeed;
}
void SwervePod::SetPreviousBottomMotorSpeed(double input)
{
    m_previousBottomMotorSpeed = input;
}

double SwervePod::LinearInterpolate(double currentSpeed, double targetSpeed, double movePercentage) 
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