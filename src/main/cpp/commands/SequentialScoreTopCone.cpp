
#include "commands/SequentialScoreTopCone.h"
#include "commands/ExtendElevatorTopCone.h"
#include "commands/EndEffectorDown.h"
#include "commands/OpenGrabber.h"
#include "commands/WaveWaitCommand.h"
#include "commands/StowElevator.h"
#include "commands/ScoreBackoff.h"
#include "commands/EndEffectorUp.h"
#include "commands/DelayedScoreBackoff.h"
// #include "frc2/command/SequentialCommandGroup.h"
// #include "frc2/command/ParallelCommandGroup.h"

SequentialScoreTopCone::SequentialScoreTopCone(Elevator* m_elevator)
:m_elevator(m_elevator)
{
    SetName("SequentialScoreTopCone");
    AddRequirements({m_elevator});

    AddCommands(
        frc2::SequentialCommandGroup(
            // place cone (top)
            ExtendElevatorTopCone(m_elevator),
            EndEffectorDown(m_elevator),
            // open grabber
            OpenGrabber(m_elevator),
            // retract 5 inches
            ScoreBackoff(m_elevator),

            // stow sequence
            EndEffectorUp(m_elevator),
            StowElevator(m_elevator)
        )
    );
}

bool SequentialScoreTopCone::RunsWhenDisabled() const 
{
    return false;
}