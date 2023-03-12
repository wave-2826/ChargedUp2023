#include <iostream>
#include "commands/ExtendElevatorTopCone.h"

ExtendElevatorTopCone::ExtendElevatorTopCone(Elevator* elevator)
:m_elevator(elevator){
    SetName("ExtendElevatorTopCone");
    AddRequirements({m_elevator});

    m_targetReached = false;

}

// Called just before this Command runs the first time
void ExtendElevatorTopCone::Initialize() {
    m_targetReached = false;
    m_elevator->setTopConeTarget();
}

// Called repeatedly when this Command is scheduled to run
void ExtendElevatorTopCone::Execute() {
    
    if(!m_elevator->isTargetSet())
    {
        m_elevator->setTopConeTarget();
    }

    // Use this if we want to use PID (comment out if use manual operation)
    m_targetReached = m_elevator->moveToCurrentTarget();
}

// Make this return true when this Command no longer needs to run execute()
bool ExtendElevatorTopCone::IsFinished() 
{
    return m_targetReached;
}

// Called once after isFinished returns true
void ExtendElevatorTopCone::End(bool interrupted) 
{
    m_targetReached = false;
}

bool ExtendElevatorTopCone::RunsWhenDisabled() const 
{
    return false;
}