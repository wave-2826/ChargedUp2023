#include "commands/SequentialScoreMidCone.h"
#include "commands/ExtendElevatorMidCone.h"
#include "commands/EndEffectorDown.h"
#include "commands/StowElevator.h"
#include "commands/ElevatorHold.h"

/**
 * Autonomous command implementation to score a cone on the mid node
 *
 * @author 2826WaveRobotics
 */
SequentialScoreMidCone::SequentialScoreMidCone(Elevator* elevator, EndEffector* endEffector)
: m_elevator(elevator), m_endEffector(endEffector)
{
    SetName("SequentialScoreMidCone");
    AddRequirements({m_elevator});

    AddCommands(
        frc2::SequentialCommandGroup (
            // place cone (top)
            ExtendElevatorMidCone(m_elevator),
            frc2::ParallelCommandGroup (
                ElevatorHold(m_elevator),
                EndEffectorDown(m_endEffector)
            ),          
            // stow sequence
            StowElevator(m_elevator)
        )
    );
}

bool SequentialScoreMidCone::RunsWhenDisabled() const { return false; }