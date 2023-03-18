#include "commands/SequentialAutoBalance.h"
#include "commands/ExtendElevatorMidCone.h"
#include "commands/EndEffectorDown.h"
#include "commands/StowElevator.h"
#include "commands/ElevatorHold.h"
#include "commands/DriveTimed.h"
#include "commands/DriveToChargingStation.h"
// #include "commands/WavePIDCommand.h"

SequentialAutoBalance::SequentialAutoBalance(SwerveDrive* swerveDrive)
: m_swerveDrive(swerveDrive)
{
    SetName("SequentialAutoBalance");
    AddRequirements({m_swerveDrive});

    AddCommands(
        frc2::SequentialCommandGroup (
            // drive until charge station
            DriveToChargingStation(m_swerveDrive)

            // balance on charge station
            // use WavePIDCommand
        )
    );
}

bool SequentialAutoBalance::RunsWhenDisabled() const { return false; }