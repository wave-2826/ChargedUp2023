#include <iostream>
#include "commands/EndEffectorUp.h"

EndEffectorUp::EndEffectorUp(Elevator* m_elevator)
:m_elevator(m_elevator)
{

    // Use AddRequirements() here to declare subsystem dependencies
    // eg. AddRequirements(m_Subsystem);
    SetName("EndEffectorUp");
    AddRequirements({m_elevator});

}

// Called just before this Command runs the first time
void EndEffectorUp::Initialize() 
{
    m_elevator->moveEndEffector(false);

}

// Called repeatedly when this Command is scheduled to run
void EndEffectorUp::Execute() {
    // if(!m_elevator->isTargetSet())
    // {
    //     m_elevator->setMidConeTarget();
    // }

    // m_targetReached = m_elevator->moveToCurrentTarget();
}

// Make this return true when this Command no longer needs to run execute()
bool EndEffectorUp::IsFinished() 
{
    std::cout << "FINISHED - End Effector Up" << std::endl;
    return true;
    // if(m_targetReached)
    // {
    //     return true
    // }
    // else
    // {
    //     return false;
    // }
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