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
SwervePod::SwervePod(rev::CANSparkMax *topMotor, rev::CANSparkMax *bottomMotor, double turnTuningFactor, double offsetAngle, int encoderChannel) 
{
    m_topMotor = topMotor;
    m_bottomMotor = bottomMotor;
    m_topEncoder = new rev::SparkMaxRelativeEncoder(m_topMotor->GetEncoder());
    m_bottomEncoder = new rev::SparkMaxRelativeEncoder(m_bottomMotor->GetEncoder());

    turnTuningFactor = turnTuningFactor;
    m_offsetAngle = offsetAngle;
    m_encoderChannel = encoderChannel;

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

void SwervePod::FlipIsReversed(bool state)
{
    if (state == true)
    {
        m_isReversed = false;
    }
    else
    {
        m_isReversed = true;
    }
}

/**
 * takes the swerve module state and calculates behavior based on 4 cases
 * (aligned, optimize > 90, optimize < -90, rotate)
 * 
 * @param SwerveModuleState state (speed, angle)
*/
bool SwervePod::Drive(frc::SwerveModuleState state)
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

    if (fabs(angle_delta) < 30.0)
    {
        // tuning factor is the P in PID (if we decide to use it)
        // double tunedAngleDelta = angle_delta * turnTuningFactor;

        // check aligned
        swerveCase = "ALIGNED";

        // station keep alg
        double stationKeepTop;
        double stationKeepBottom;
        double divisor;
        if (GetIsReversed())
        {
            stationKeepTop = (1.0 - angle_delta * normalizer);
            stationKeepBottom = (1.0 + angle_delta * normalizer);
        }
        else
        {            
            // stationKeepTop = (1 + tunedAngleDelta * normalizer);
            // stationKeepBottom = (1 - tunedAngleDelta * normalizer);
            stationKeepTop = (1.0 + angle_delta * normalizer);
            stationKeepBottom = (1.0 - angle_delta * normalizer);
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
    else if (angle_delta < -90.0)
    {
        // check optimal path
        swerveCase = "OPTIMIZE < -90";

        FlipIsReversed(m_isReversed);
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

        FlipIsReversed(m_isReversed);
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

    // assign motor speeds
    m_topMotor->Set(topMotorSpeed);
    m_bottomMotor->Set(bottomMotorSpeed);

    ///////////////////////////////// TESTING PRINTOUTS ///////////////////////////////////////////////

    if (GetCounter() > 50)
    {
        // SWERVE CASE
        // std::cout << swerveCase << std::endl;
        // std::cout << "reversed? " << GetIsReversed() << std::endl; 

        // ANGLES
        // std::cout << "CASE: " << swerveCase << "         T: " << target_angle << " C: " << current_angle <<  std::endl;
        // std::cout << m_podName << " current angle: " << current_angle << std::endl;
        // std::cout << "target angle: " << target_angle << std::endl << std::endl;
        // std::cout << m_podName << " offset: " << m_offsetAngle << std::endl;
        // std::cout << "angle delta " << angle_delta << std::endl;

        // MOTOR SPEEDS
        // std::cout << topMotorSpeed <<  std::endl;
        // std::cout << bottomMotorSpeed << std::endl <<  std::endl;
        
        SetCounter(0);
        return true;
    }
    else
    {
        int current_count = GetCounter();
        SetCounter(current_count + 1);
    }
    return false;
}
