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
#include "subsystems/EndEffector.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "Globals.h"
#include "RobotContainer.h"

EndEffector::EndEffector()
{
    SetName("EndEffector");
    SetSubsystem("EndEffector");

    m_endEffectorMotor = new rev::CANSparkMax(k_endofactorMotor, rev::CANSparkMaxLowLevel::MotorType::kBrushless);
    m_endEffectorMotor->SetInverted(true);

    m_coneLED = new frc::DigitalOutput(k_coneLED);
    m_cubeLED = new frc::DigitalOutput(k_cubeLED);
    m_alignedLED = new frc::DigitalOutput(k_alignedLED);
}

// Put code here to be run every loop
void EndEffector::Periodic() 
{ 
    if (m_allianceLEDID == -1)
    {
        bool isRed = frc::SmartDashboard::GetBoolean("FMSInfo/IsRedAlliance", false);
        m_allianceLEDID = isRed ? k_redLED : k_blueLED;
        m_allianceLED = new frc::DigitalOutput(m_allianceLEDID);
        m_allianceLED->Set(true);
    }
    
    runEndEffector();

    // Check cone or cube
    int checkConeOrCube = m_operatorJoystick->GetPOV();
    if ((checkConeOrCube >= 0 && checkConeOrCube <= 90) || (checkConeOrCube > 270))
    {
        m_isCone = true;
        m_cubeLED->Set(false);
        m_coneLED->Set(true);
    }
    else if (checkConeOrCube > 90 && checkConeOrCube < 270)
    {
        m_isCone = false;
        m_coneLED->Set(false);
        m_cubeLED->Set(true); 
    }
}    

void EndEffector::Initialize() 
{
    m_allianceLEDID = -1;
    m_operatorJoystick = RobotContainer::GetInstance()->getOperator();
    m_endEffectorTimer = (uint16_t)ONE_SECOND;
}

// This method will be called once per scheduler run when in simulation
void EndEffector::SimulationPeriodic() {}

//////////////// endEffector operation ////////////////////

void EndEffector::runEndEffector()
{
    double endEffectorRollerIn = m_operatorJoystick->GetRightTriggerAxis();
    double endEffectorRollerOut = m_operatorJoystick->GetLeftTriggerAxis();
    double endEffectorSpeed = 0.0;

    if(endEffectorRollerIn > k_jsDeadband)
    {
        if (m_isCone)
        {
            endEffectorSpeed = endEffectorRollerIn;
        }
        else
        {
            endEffectorSpeed = -endEffectorRollerIn; 
        }
    }
    else if (endEffectorRollerOut > k_jsDeadband)
    {
        if (m_isCone)
        {
            endEffectorSpeed = -endEffectorRollerOut;
        }
        else
        {
            endEffectorSpeed = endEffectorRollerOut; 
        }
    }
    setRoller(endEffectorSpeed);
}

void EndEffector::setRoller(double speed)
{
    m_endEffectorMotor->Set(speed);
}


