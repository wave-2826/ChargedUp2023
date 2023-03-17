#include "commands/SequentialScoreMidCone.h"
#include "commands/ExtendElevatorMidCone.h"
#include "commands/EndEffectorDown.h"
#include "commands/OpenGrabber.h"
#include "commands/StowElevator.h"
#include "commands/EndEffectorUp.h"
#include "commands/ElevatorHold.h"
#include "commands/DriveTimed.h"

SequentialScoreMidCone::SequentialScoreMidCone(Elevator* elevator, SwerveDrive* drive, EndEffector* endEffector)
: m_elevator(elevator), m_drive(drive), m_endEffector(endEffector)
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
            StowElevator(m_elevator),
            DriveTimed(m_drive, 0.0, -0.7, 0.0, (units::time::second_t)1.0)
        )
    );
}

bool SequentialScoreMidCone::RunsWhenDisabled() const { return false; }