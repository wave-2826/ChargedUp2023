#include <iostream>
#include "commands/ExtendElevatorTopCone.h"

ExtendElevatorTopCone::ExtendElevatorTopCone(Elevator* m_elevator)
:m_elevator(m_elevator){

    // Use AddRequirements() here to declare subsystem dependencies
    // eg. AddRequirements(m_Subsystem);
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

    // Use this if we do not use PID (comment out if use PID operation)
    //m_targetReached = m_elevator->moveElevatorToTargetManual();
}

// Make this return true when this Command no longer needs to run execute()
bool ExtendElevatorTopCone::IsFinished() 
{
    // std::cout << "target reached: " << m_targetReached << std::endl;
    if(m_targetReached)
    {
        // Top Target reached
        // std::cout << "Top Target Reached" << std::endl;
        return true;
    }
    else
    {
        return false;
    }
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