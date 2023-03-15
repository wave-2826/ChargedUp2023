#include <iostream>
#include "Globals.h"
#include "commands/OpenGrabber.h"

OpenGrabber::OpenGrabber(EndEffector* endEffector)
: m_endEffector(endEffector)
{    
    SetName("OpenGrabber");
    AddRequirements({m_endEffector});
}

// Called just before this Command runs the first time
void OpenGrabber::Initialize() 
{
    m_targetReached = false;
    // m_endEffector->setGrabber(true);
}

// Called repeatedly when this Command is scheduled to run
void OpenGrabber::Execute() 
{
    // std::cout << "EXECUTE grabber - WAIT: " << m_waitCommand->IsFinished() << std::endl;
    // if (!m_timerSet) {
    //     m_endEffector->setGrabber(true);
    //     m_timerSet = true; 
    // }
    // // m_targetReached = m_endEffector->openGrabber();
}

// Make this return true when this Command no longer needs to run execute()
bool OpenGrabber::IsFinished() 
{
    return m_targetReached;
}

// Called once after isFinished returns true
void OpenGrabber::End(bool interrupted) 
{
    m_timerSet = false;
    m_targetReached = false;
}

bool OpenGrabber::RunsWhenDisabled() const 
{
    return false;
}