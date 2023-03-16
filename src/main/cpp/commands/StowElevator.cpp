#include <iostream>
#include "commands/StowElevator.h"

StowElevator::StowElevator(Elevator* m_elevator)
: m_elevator(m_elevator), m_targetReached(false)
{

    // Use AddRequirements() here to declare subsystem dependencies
    // eg. AddRequirements(m_Subsystem);
    SetName("StowElevator");
    AddRequirements({m_elevator});
}

// Called just before this Command runs the first time
void StowElevator::Initialize() 
{
    m_targetReached = false;
}

// Called repeatedly when this Command is scheduled to run
void StowElevator::Execute() 
{
    m_targetReached = m_elevator->stowElevatorAuto();
}

// Make this return true when this Command no longer needs to run execute()
bool StowElevator::IsFinished() 
{
    return m_targetReached;
}

// Called once after isFinished returns true
void StowElevator::End(bool interrupted) 
{
    m_targetReached = false;
}

bool StowElevator::RunsWhenDisabled() const 
{
    return false;
}