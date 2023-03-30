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
// #include <ctre/phoenix/sensors/Pigeon2.h>
#include <units/time.h>
#include "frc2/command/PIDSubsystem.h"

// Steps to balance on charging station
typedef enum
{
    Balance_Off,
    Balance_Active,
    Balance_Success
} BalanceStates;

/**
 *
 *
 * @author 2826WaveRobotics
 */
class AutoBalanceSwerve: public frc2::CommandHelper<frc2::CommandBase, AutoBalanceSwerve> 
{

public:

    explicit AutoBalanceSwerve(SwerveDrive* swerveDrive);

    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End(bool interrupted) override;
    bool RunsWhenDisabled() const override;

    void updatePID(double p, double i, double d, double delta);

private:

    SwerveDrive* m_swerveDrive;
    // ctre::phoenix::sensors::Pigeon2* m_pigeon;
    BalanceStates m_balanceState;
    uint16_t m_balanceTimer;
    bool m_isBalanced;

    double m_pGain = 1.0;
    double m_iGain = 2.0;
    double m_dGain = 0.5;
    double m_pitchTolerence = 2.0;
    
    // double m_startingYaw;
    frc2::PIDController *m_balancePID; 

    // std::vector<double> previousPitches;
};