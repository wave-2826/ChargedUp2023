
#include "commands/ScoreTopConeBackout.h"
// #include "commands/ExtendElevatorTopCone.h"
// #include "commands/EndEffectorDown.h"
// #include "commands/OpenGrabber.h"
#include "commands/WaveWaitCommand.h"
// #include "commands/StowElevator.h"
#include "commands/DriveTimed.h"
// #include "commands/ScoreBackoff.h"
// #include "commands/EndEffectorUp.h"
#include "commands/SequentialScoreTopCone.h"

ScoreTopConeBackout::ScoreTopConeBackout(Elevator* m_elevator, SwerveDrive* m_drive)
:m_elevator(m_elevator), m_drive(m_drive)
{
    SetName("ScoreTopConeBackout");
    AddRequirements({m_elevator});

    AddCommands(
        frc2::SequentialCommandGroup
        (
            // ExtendElevatorTopCone(m_elevator),
            // EndEffectorDown(m_elevator),
            // OpenGrabber(m_elevator),
            // WaveWaitCommand(units::second_t(1.0)),
            // ScoreBackoff(m_elevator),
            // EndEffectorUp(m_elevator),
            // StowElevator(m_elevator),

            // score cone (top)
            SequentialScoreTopCone(m_elevator),
            // pause 1 sec
            WaveWaitCommand(units::second_t(1.0)),
            // exit community
            DriveTimed(m_drive, 0.0, 0.5, 0.0, units::second_t(1.5))
        )
    );
}

bool ScoreTopConeBackout::RunsWhenDisabled() const 
{
    return false;
}