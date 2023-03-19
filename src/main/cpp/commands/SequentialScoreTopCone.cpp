
#include "commands/SequentialScoreTopCone.h"
#include "commands/ExtendElevatorTopCone.h"
#include "commands/EndEffectorDown.h"
#include "commands/StowElevator.h"
#include "commands/ElevatorHold.h"
#include "commands/DriveTimed.h"

SequentialScoreTopCone::SequentialScoreTopCone(Elevator* elevator, SwerveDrive* drive, EndEffector* endEffector)
: m_elevator(elevator), m_drive(drive), m_endEffector(endEffector)
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
            StowElevator(m_elevator),
            DriveTimed(m_drive, 0.0, -0.7, 0.0, (units::time::second_t)3.0)
        )
    );
}

bool SequentialScoreTopCone::RunsWhenDisabled() const { return false; }