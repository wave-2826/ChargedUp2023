
#include <iostream>
#include "commands/CloseGrabber.h"

CloseGrabber::CloseGrabber(Elevator* m_elevator)
:m_elevator(m_elevator)
{
    
    // Use AddRequirements() here to declare subsystem dependencies
    // eg. AddRequirements(m_Subsystem);
    SetName("CloseGrabber");
    AddRequirements({m_elevator});

}

// Called just before this Command runs the first time
void CloseGrabber::Initialize() 
{

}

// Called repeatedly when this Command is scheduled to run
void CloseGrabber::Execute() {
    m_elevator->setGrabber(true);
}

// Make this return true when this Command no longer needs to run execute()
bool CloseGrabber::IsFinished() 
{
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
void CloseGrabber::End(bool interrupted) 
{
    // m_targetReached = false;
}

bool CloseGrabber::RunsWhenDisabled() const 
{
    return false;
}