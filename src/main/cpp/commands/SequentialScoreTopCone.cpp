
#include "commands/SequentialScoreTopCone.h"
#include "commands/ExtendElevatorTopCone.h"
#include "commands/EndEffectorDown.h"
#include "commands/OpenGrabber.h"
#include "commands/StowElevator.h"
#include "commands/EndEffectorUp.h"

SequentialScoreTopCone::SequentialScoreTopCone(Elevator* elevator, EndEffector* endEffector)
: m_elevator(elevator), m_endEffector(endEffector)
{
    SetName("SequentialScoreTopCone");
    AddRequirements({m_elevator});

    AddCommands(
        frc2::SequentialCommandGroup (
            // place cone (top)
            ExtendElevatorTopCone(m_elevator),
            EndEffectorDown(m_endEffector),
            // open grabber
            OpenGrabber(m_endEffector),

            // stow sequence
            StowElevator(m_elevator)
            // EndEffectorUp(m_endEffector)
        )
    );
}

bool SequentialScoreTopCone::RunsWhenDisabled() const 
{
    return false;
}