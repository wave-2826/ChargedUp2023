#include <iostream>
#include "commands/ExtendElevatorMidCone.h"

ExtendElevatorMidCone::ExtendElevatorMidCone(Elevator* elevator)
:m_elevator(elevator)
{
    SetName("ExtendElevatorMidCone");
    AddRequirements({m_elevator});

    m_targetReached = false;
}

// Called just before this Command runs the first time
void ExtendElevatorMidCone::Initialize() 
{
    m_targetReached = false;
    m_elevator->setMidConeTarget();
}

// Called repeatedly when this Command is scheduled to run
void ExtendElevatorMidCone::Execute() {
    
    if(!m_elevator->isTargetSet())
    {
        m_elevator->setMidConeTarget();
    }

    m_targetReached = m_elevator->moveToCurrentTarget();
}

// Make this return true when this Command no longer needs to run execute()
bool ExtendElevatorMidCone::IsFinished() 
{
    return m_targetReached;
}

// Called once after isFinished returns true
void ExtendElevatorMidCone::End(bool interrupted) 
{
    // std::cout << "END - Mid Target Reached" << std::endl;
    m_targetReached = false;
}

bool ExtendElevatorMidCone::RunsWhenDisabled() const 
{
    return false;

}