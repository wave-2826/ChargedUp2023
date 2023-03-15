#include <iostream>
#include "commands/EndEffectorUp.h"

EndEffectorUp::EndEffectorUp(EndEffector* endEffector)
:m_endEffector(endEffector), m_targetReached(false)
{

    // Use AddRequirements() here to declare subsystem dependencies
    // eg. AddRequirements(m_Subsystem);
    SetName("EndEffectorUp");
    AddRequirements({m_endEffector});

}

// Called just before this Command runs the first time
void EndEffectorUp::Initialize() 
{
    m_targetReached = false;

}

// Called repeatedly when this Command is scheduled to run
void EndEffectorUp::Execute() 
{
   // m_targetReached = m_endEffector->raiseEndEffector();
}

// Make this return true when this Command no longer needs to run execute()
bool EndEffectorUp::IsFinished() 
{
    std::cout << "FINISHED - End Effector Up" << std::endl;
    return m_targetReached;
}

// Called once after isFinished returns true
void EndEffectorUp::End(bool interrupted) 
{
    std::cout << "END - End Effector Up" << std::endl;
    m_targetReached = false;
}

bool EndEffectorUp::RunsWhenDisabled() const 
{
    return false;
}