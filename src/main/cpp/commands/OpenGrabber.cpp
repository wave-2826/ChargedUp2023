#include <iostream>
#include "commands/OpenGrabber.h"
#include "commands/WaveWaitCommand.h"

OpenGrabber::OpenGrabber(Elevator* elevator)//, units::second_t timeout)
                        :m_elevator(elevator)
{    
    SetName("OpenGrabber");
    AddRequirements({m_elevator});
    // m_waitCommand = new WaveWaitCommand(units::second_t(0.5));

}

// Called just before this Command runs the first time
void OpenGrabber::Initialize() 
{
    // WaitCommand::Initialize();
    // m_timerSet = false;
}

// Called repeatedly when this Command is scheduled to run
void OpenGrabber::Execute() 
{
    m_elevator->setGrabber(false);
    // std::cout << "EXECUTE grabber - WAIT: " << m_waitCommand->IsFinished() << std::endl;
    // if (!m_timerSet) {
    //     m_waitCommand->Initialize();
    //     m_timerSet = true; 
    // }
    // if (m_waitCommand->IsFinished()) {
    //     m_targetReached = true;
    // }
}

// Make this return true when this Command no longer needs to run execute()
bool OpenGrabber::IsFinished() 
{
    // std::cout << "FINISHED - Open Grabber: " << m_waitCommand->IsFinished() << std::endl;
    // m_timerSet = false;
    // if (m_targetReached) {
    //     std::cout << "open grabber" << std::endl;
    // }
    return true;
}

// Called once after isFinished returns true
void OpenGrabber::End(bool interrupted) 
{
    // WaitCommand::End(interrupted);
    // m_timerSet = false;
    // m_targetReached = false;
}

bool OpenGrabber::RunsWhenDisabled() const 
{
    return false;
}