#include "commands/ScoreTopConeBackout.h"
#include "commands/SequentialScoreTopCone.h"
#include "commands/DriveTimed.h"

/**
 * Autonomous command implementation to score a cone on the top node and 
 * back out of the community
 *
 * @author 2826WaveRobotics
 */
ScoreTopConeBackout::ScoreTopConeBackout(Elevator* elevator, SwerveDrive* drive, EndEffector* endEffector)
: m_elevator(elevator), m_drive(drive), m_endEffector(endEffector)
{
    SetName("ScoreTopConeBackout");
    AddRequirements({m_elevator});

    AddCommands(
        frc2::SequentialCommandGroup (
            // score cone (top)
            SequentialScoreTopCone(m_elevator, m_endEffector),       
            // back out of community
            DriveTimed(m_drive, 0.0, 0.75, 0.0, (units::time::second_t)2.5)
        )
    );
}

bool ScoreTopConeBackout::RunsWhenDisabled() const { return false; }