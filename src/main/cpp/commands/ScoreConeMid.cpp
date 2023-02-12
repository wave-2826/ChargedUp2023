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
#include "commands/ScoreConeMid.h"

ScoreConeMid::ScoreConeMid(Elevator* m_elevator)
:m_elevator(m_elevator){

    // Use AddRequirements() here to declare subsystem dependencies
    // eg. AddRequirements(m_Subsystem);
    SetName("ScoreConeTop");
    AddRequirements({m_elevator});

    m_targetReached = false;

}

// Called just before this Command runs the first time
void ScoreConeMid::Initialize() {

    m_targetReached = false;
    m_elevator->setTopConeTarget();
}

// Called repeatedly when this Command is scheduled to run
void ScoreConeMid::Execute() {
    
    if(!m_elevator->isTargetSet())
    {
        m_elevator->setMidConeTarget();
    }

    m_targetReached = m_elevator->moveToCurrentTarget();
}

// Make this return true when this Command no longer needs to run execute()
bool ScoreConeMid::IsFinished() 
{
    if(m_targetReached)
    {
        // Top Target reached
        std::cout << "Top Target Reached" << std::endl;
        return true;
    }
    else
    {
        return false;
    }
}

// Called once after isFinished returns true
void ScoreConeMid::End(bool interrupted) 
{
    m_targetReached = false;
}

bool ScoreConeMid::RunsWhenDisabled() const {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DISABLED
    return false;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DISABLED
}