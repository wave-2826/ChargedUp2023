// RobotBuilder Version: 5.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

// ROBOTBUILDER TYPE: Command.

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

#include <iostream>
#include "commands/EndEffectorDown.h"
#include "commands/WaveWaitCommand.h"

EndEffectorDown::EndEffectorDown(Elevator* m_elevator)
:m_elevator(m_elevator), m_timerSet(false)
{

    // Use AddRequirements() here to declare subsystem dependencies
    // eg. AddRequirements(m_Subsystem);
    SetName("EndEffectorDown");
    AddRequirements({m_elevator});
    m_waitCommand = new WaveWaitCommand(units::second_t(0.5));
}

// Called just before this Command runs the first time
void EndEffectorDown::Initialize() 
{
    m_timerSet = false;
}

// Called repeatedly when this Command is scheduled to run
void EndEffectorDown::Execute() 
{
    m_elevator->moveEndEffector(true);
    if (!m_timerSet) {
        m_waitCommand->Initialize();
        m_timerSet = true; 
    }
    if (m_waitCommand->IsFinished()) {
        m_targetReached = true;
    }
}

// Make this return true when this Command no longer needs to run execute()
bool EndEffectorDown::IsFinished() 
{
    m_timerSet = false;
    return m_targetReached;
}

// Called once after isFinished returns true
void EndEffectorDown::End(bool interrupted) 
{
    m_timerSet = false;
    m_targetReached = false;
}

bool EndEffectorDown::RunsWhenDisabled() const 
{
    return false;
}
