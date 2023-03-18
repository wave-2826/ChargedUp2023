// RobotBuilder Version: 5.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

// ROBOTBUILDER TYPE: Command.

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/CommandBase.h>
#include <frc2/command/WaitCommand.h>
#include <subsystems/SwerveDrive.h>
#include <ctre/phoenix/sensors/Pigeon2.h>
#include <units/time.h>

// Steps to balance on charging station
typedef enum
{
    Before_Balance,
    Tilted_Up
} BalanceState;

/**
 *
 *
 * @author 2826WaveRobotics
 */
class DriveToChargingStation: public frc2::CommandHelper<frc2::CommandBase, DriveToChargingStation> 
{

public:

    explicit DriveToChargingStation(SwerveDrive* swerveDrive);

    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End(bool interrupted) override;
    bool RunsWhenDisabled() const override;

private:

    SwerveDrive* m_swerveDrive;
    ctre::phoenix::sensors::Pigeon2* m_pigeon;
    BalanceState m_balanceState;
    bool m_isTilted;

    std::vector<double> previousPitches;

    double m_markiplier = -1.5;
};