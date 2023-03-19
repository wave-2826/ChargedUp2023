#include "commands/ScoreMidConeBackout.h"
#include "commands/SequentialScoreMidCone.h"
#include "commands/DriveTimed.h"

/**
 * Autonomous command implementation to score a cone on the mid node and 
 * back out of the community
 *
 * @author 2826WaveRobotics
 */
ScoreMidConeBackout::ScoreMidConeBackout(Elevator* elevator, SwerveDrive* drive, EndEffector* endEffector)
: m_elevator(elevator), m_drive(drive), m_endEffector(endEffector)
{
    SetName("ScoreMidConeBackout");
    AddRequirements({m_elevator});

    AddCommands(
        frc2::SequentialCommandGroup (
            // score cone (mid)
            SequentialScoreMidCone(m_elevator, m_endEffector),       
            // back out of community
            DriveTimed(m_drive, 0.0, -0.7, 0.0, (units::time::second_t)1.0)
        )
    );
}

bool ScoreMidConeBackout::RunsWhenDisabled() const { return false; }