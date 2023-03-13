#include <iostream>
#include "commands/ExtendElevatorBackoff.h"

ExtendElevatorBackoff::ExtendElevatorBackoff(Elevator* m_elevator)
:m_elevator(m_elevator)
{

    // Use AddRequirements() here to declare subsystem dependencies
    // eg. AddRequirements(m_Subsystem);
    SetName("ExtendElevatorBackoff");
    AddRequirements({m_elevator});

    m_targetReached = false;

}

// Called just before this Command runs the first time
void ExtendElevatorBackoff::Initialize() 
{
    m_target = m_elevator->getElevatorPosition() - 5.0;
    if (m_target < 0.0) {
        m_target = 0.0;
    }
    m_targetReached = false;
    m_elevator->setCustomTarget(m_target);
}

// Called repeatedly when this Command is scheduled to run
void ExtendElevatorBackoff::Execute() {
    
    if(!m_elevator->isTargetSet())
    {
        m_elevator->setCustomTarget(m_target);
    }

    m_targetReached = m_elevator->moveToCurrentTarget();
}

// Make this return true when this Command no longer needs to run execute()
bool ExtendElevatorBackoff::IsFinished() 
{
    if(m_targetReached)
    {
        // std::cout << "FINISHED - Backoff Target Reached" << std::endl;
        // Top Target reached
        // std::cout << "Backoff Target Reached" << std::endl;
        return true;
    }
    else
    {
        return false;
    }
}

// Called once after isFinished returns true
void ExtendElevatorBackoff::End(bool interrupted) 
{
    // std::cout << "END - Backoff Target Reached" << std::endl;
    m_targetReached = false;
}

bool ExtendElevatorBackoff::RunsWhenDisabled() const 
{
    return false;

}