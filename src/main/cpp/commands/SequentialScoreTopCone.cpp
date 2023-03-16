
#include "commands/SequentialScoreTopCone.h"
#include "commands/ExtendElevatorTopCone.h"
#include "commands/EndEffectorDown.h"
#include "commands/OpenGrabber.h"
#include "commands/StowElevator.h"
#include "commands/EndEffectorUp.h"
#include "commands/ElevatorHold.h"

SequentialScoreTopCone::SequentialScoreTopCone(Elevator* elevator, EndEffector* endEffector)
: m_elevator(elevator), m_endEffector(endEffector)
{
    SetName("SequentialScoreTopCone");
    AddRequirements({m_elevator});

    AddCommands(
        frc2::SequentialCommandGroup (
            // place cone (top)
            ExtendElevatorTopCone(m_elevator),
            frc2::ParallelCommandGroup (
                ElevatorHold(m_elevator),
                EndEffectorDown(m_endEffector)
            ),          
            // stow sequence
            StowElevator(m_elevator)
        )
    );
}

bool SequentialScoreTopCone::RunsWhenDisabled() const 
{
    return false;
}