// RobotBuilder Version: 5.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

// ROBOTBUILDER TYPE: Subsystem.

#include <iostream>
#include "subsystems/Elevator.h"
#include <frc/smartdashboard/SmartDashboard.h>

#include "RobotContainer.h"

Elevator::Elevator()
{
    SetName("Elevator");
    SetSubsystem("Elevator");

    m_elevatorMotorA = new rev::CANSparkMax(k_elevatorMotorA, rev::CANSparkMaxLowLevel::MotorType::kBrushless);
    m_elevatorMotorB = new rev::CANSparkMax(k_elevatorMotorB, rev::CANSparkMaxLowLevel::MotorType::kBrushless);
    m_elevatorMotorA->SetInverted(true);
    m_elevatorMotorB->SetInverted(true);
    m_elevatorMotorA->SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    m_elevatorMotorB->SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    m_elevatorEncoderA = new rev::SparkMaxRelativeEncoder(m_elevatorMotorA->GetEncoder());
    m_elevatorEncoderB = new rev::SparkMaxRelativeEncoder(m_elevatorMotorB->GetEncoder());

    m_elevatorPID = new frc2::PIDController(k_P, k_I, k_D);

    m_elevatorFunction = Elevator_Off;
    m_elevatorPosition = 0.0;
    m_elevatorHomePosition = 0.0;
    m_elevatorTarget = 0.0;
    m_targetSet = false;
    m_fineLimit = k_fineLimit;
    m_isCone = true;

    // May or may not use this
    m_distancePerRotation = (k_numOfTeeth * k_teethSize) /k_gearRatio;
}

void Elevator::setCustomTarget(double target)
{
    m_elevatorTarget = target;
    m_targetSet = true;
}

void Elevator::setTopConeTarget()
{
    m_elevatorTarget = k_elevatorTargetTopCone;
    m_targetSet = true;
}

void Elevator::setMidConeTarget()
{
    m_elevatorTarget = k_elevatorTargetMiddleCone;
    m_targetSet = true;
}

void Elevator::setTopCubeTarget()
{
    m_elevatorTarget = k_elevatorTargetTopCube;
    m_targetSet = true;
}

void Elevator::setMidCubeTarget()
{
    m_elevatorTarget = k_elevatorTargetMiddleCube;
    m_targetSet = true;
}

void Elevator::setHumanStationTarget()
{
    if(m_isCone)
    {
        m_elevatorTarget = k_elevatorHumanStationCone;
    }
    else
    {
        m_elevatorTarget = k_elevatorHumanStationCube;
    }
    m_targetSet = true;
}

void Elevator::setStowTarget()
{
    m_elevatorTarget = m_elevatorHomePosition;
    m_isStowing = true;
    m_targetSet = true;
}

void Elevator::updateValues()
{
    k_P = frc::SmartDashboard::GetNumber("Elevator P", 1.1);
    k_I = frc::SmartDashboard::GetNumber("Elevator I", 5.0);
    k_D = frc::SmartDashboard::GetNumber("Elevator D", 0.1);
    k_rampPerLoop = frc::SmartDashboard::GetNumber("Elevator Ramp", 0.0075);
}

double Elevator::getElevatorPosition() 
{
    // Get the number of rotation of the motor
    double numOfRotationA = m_elevatorEncoderA->GetPosition();

    return (m_distancePerRotation * numOfRotationA);
}

// TESTING
void Elevator::setElevator(double speed) 
{
    bool overrideLimit = m_operatorJoystick->GetRightBumper();

    if(!overrideLimit)
    {
        if (m_elevatorPosition >= k_maxElevatorPosition) {
            // CASE: at max height - only allow retracting elevator
            speed = speed > 0 ? 0 : speed;
        } else if (m_elevatorPosition <= 0) {
            // CASE: at min height - only allow extending elevator
            speed = speed < 0 ? 0 : speed;
        }
    }

    m_elevatorMotorA->Set(speed);
    m_elevatorMotorB->Set(speed);

    std::cout << "Pos: " << m_elevatorPosition << "   Target: " << m_elevatorTarget << "  ElevSpeed: " << speed << "   isCone: " << m_isCone << std::endl;
    // std::cout << "Pos: " << m_elevatorPosition << "   Target: " << m_elevatorTarget << " p=" << k_P << " i=" << k_I << " d=" << k_D << "  isCone: " << m_isCone << std::endl;
}

void Elevator::holdElevator()
{
    setElevator(k_elevatorHoldSpeed);
}

// Put code here to be run every loop
void Elevator::Periodic() 
{ 
    m_elevatorPosition = getElevatorPosition();

    // Check cone or cube
    int checkConeOrCube = m_operatorJoystick->GetPOV();
    if ((checkConeOrCube >= 0 && checkConeOrCube <= 90) || (checkConeOrCube > 270))
    {
        m_isCone = true;
    }
    else if (checkConeOrCube > 90 && checkConeOrCube < 270)
    {
        m_isCone = false;
    }

    if(m_operatorJoystick->GetStartButton())
    {
        m_elevatorEncoderA->SetPosition(0.0);
        m_elevatorEncoderB->SetPosition(0.0);
        m_elevatorTarget = 0.0;

    }

    // std::cout << "Kp: " << m_elevatorPID->GetP() << "  Ki: " << m_elevatorPID->GetI() << "  Kd: " << m_elevatorPID->GetD() << "  Fine: " << m_fineLimit << std::endl;
}    

void Elevator::Initialize() 
{
    m_elevatorEncoderA->SetPosition(0.0);
    m_elevatorEncoderB->SetPosition(0.0);
    m_operatorJoystick = RobotContainer::GetInstance()->getOperator();
    m_elevatorFunction = Elevator_Off;
}

// This method will be called once per scheduler run when in simulation
void Elevator::SimulationPeriodic() {}

double Elevator::getPIDSpeed(double pidCommand)
{
    // Convert PID output to speed command between -1.0 to 1.0
    double speedOut = 0;

    speedOut = pidCommand / 20.0;    // temporary place holder

    if(k_maxElevatorSpeed <= speedOut)
    {
        speedOut = k_maxElevatorSpeed;
    }
    else if(-k_maxElevatorSpeed >= speedOut)
    {
        speedOut = -k_maxElevatorSpeed;
    }

    return speedOut;
}

void Elevator::runElevator() 
{
    //////////////  Routine ELEVATOR FUNCTIONS  /////////////////////
    double elevatorSpeedCmd = 0.0;
    bool elevatorOverride = m_operatorJoystick->GetLeftBumper();
    

    if(elevatorOverride) 
    {
        // Manual operation
        m_elevatorFunction = Elevator_Off;
        m_isStowing = false;
        elevatorSpeedCmd = m_operatorJoystick->GetRightY();
        if(k_jsDeadband > std::fabs(elevatorSpeedCmd))
        {
            elevatorSpeedCmd = 0.0;
        }

        setElevator(-0.45 * elevatorSpeedCmd);
    } 
    else 
    {
        // Get the target command
        if(m_operatorJoystick->GetYButton()) 
        {
            if(m_isCone) 
            {
                setTopConeTarget();
            } 
            else 
            {
                setTopCubeTarget();
            }
            m_elevatorFunction = Elevator_Deploy;
        } 
        else if(m_operatorJoystick->GetXButton()) 
        {
            if(m_isCone) 
            {
                setMidConeTarget();
            } 
            else 
            {
                setMidCubeTarget();
            }
            m_elevatorFunction = Elevator_Deploy;
        } 
        else if(m_operatorJoystick->GetBButton()) 
        {
            setHumanStationTarget();
            m_elevatorFunction = Elevator_Deploy;
        } 
        else if(m_operatorJoystick->GetAButton())
        {
            setStowTarget();
            m_elevatorFunction = Elevator_Deploy;
        }

        // Set the elevator function based on Joystick command
        switch(m_elevatorFunction) 
        {
            case Elevator_Off:
            default:
                m_elevatorPID->Reset();
                m_isStowing = false;
                break;

            case Elevator_Deploy:
                if(m_isStowing)
                {
                    if(stowElevatorAuto())
                    {
                        m_elevatorFunction = Elevator_Off;
                        m_isStowing = false;
                    }
                }
                else
                {
                    if(moveToCurrentTarget())
                    {
                        m_elevatorFunction = Elevator_Hold;
                    }
                }
                break;
            case Elevator_Hold:
                m_elevatorPID->Reset();
                setElevator(k_elevatorHoldSpeed);
                break;
        }
    }
}

bool Elevator::moveToCurrentTarget()
{
    double speedCmd = 0.0;
    bool retVal = false;
    static double lastSpeedCmd = 0.0;
    const double k_minSpeedCmd = 0.1;

    double delta = std::fabs(m_elevatorTarget - m_elevatorPosition);
    // Set the gain
    if(delta > m_fineLimit)
    {
        m_elevatorPID->SetPID(k_P, k_I, k_D);
    }
    else
    {
        m_elevatorPID->SetPID(k_PFine, k_IFine, k_DFine);
    }

    double pidOut = getPIDSpeed(m_elevatorPID->Calculate(m_elevatorPosition, m_elevatorTarget));
    // std::cout << "PID Out: " << pidOut << std::endl;

    if(k_delta < delta)
    {
        if(pidOut > 0.0)
        {
            if (lastSpeedCmd <= 0.0)
                lastSpeedCmd = k_minSpeedCmd;

            if(lastSpeedCmd < pidOut)
            {
                lastSpeedCmd += k_rampPerLoop;
            }
        }
        else if(pidOut < 0.0)
        {
            if (lastSpeedCmd >= 0.0)
                lastSpeedCmd = -k_minSpeedCmd;

            if(lastSpeedCmd > pidOut)
            {
                lastSpeedCmd -= k_rampPerLoop;
            }
        }
        speedCmd = lastSpeedCmd;
    }
    else
    {
        lastSpeedCmd = 0.0;
        m_elevatorPID->Reset();
        retVal = true;
    }

    setElevator(speedCmd);

    return retVal;
}


bool Elevator::moveElevatorToTargetManual(double target)
{
    bool retVal = false;
    double speedCmd = 0.0;
    const double k_manualElevatorCmd = 0.2; 
    double delta = std::fabs(target - m_elevatorPosition);

    if(4.0 <= delta)
    {
        // Move the Elevator
        if(target > m_elevatorPosition)
        {
            // Need to extend the elevator
            speedCmd = k_manualElevatorCmd;
        }
        else if(target < m_elevatorPosition)
        {
            // Need to retract the elevator
            speedCmd = -k_manualElevatorCmd;
        }
    }
    else if(0.1 <= delta)
    {
        // Move the Elevator
        if(target > m_elevatorPosition)
        {
            // Need to extend the elevator
            speedCmd = k_manualElevatorCmd/2.0;
        }
        else if(target < m_elevatorPosition)
        {
            // Need to retract the elevator
            speedCmd = -k_manualElevatorCmd/2.0;
        }
    }
    else
    {
        // Target reached
        retVal = true;
    }

    setElevator(speedCmd);

    return retVal;
}

//////////////////  STOW ELEVATOR  /////////////////////////////////
bool Elevator::stowElevator()
{
    m_elevatorFunction = Elevator_Off;
    if(m_operatorJoystick->GetAButton())
    {
        return (moveElevatorToTargetManual(m_elevatorHomePosition));
    }
    else
    {
        return true;
    }
}

bool Elevator::stowElevatorAuto()
{
    return (moveElevatorToTargetManual(m_elevatorHomePosition));
}