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
#include <units/time.h>

/**
 *
 *
 * @author 2826WaveRobotics
 */
class DriveHeading: public frc2::WaitCommand 
{

public:

    explicit DriveHeading(SwerveDrive* swerveDrive, double inputLX, double inputLY, double inputRX, double targetYaw, 
                        units::second_t timeout = (units::second_t)0);

    void Initialize() override;
    void Execute() override;
    // bool IsFinished() override;
    void End(bool interrupted) override;
    bool RunsWhenDisabled() const override;

private:

    SwerveDrive* m_swerveDrive;
    double m_inputLX;
    double m_inputLY;
    double m_inputRX;
    double m_targetYaw;
    units::second_t m_timeout;

};
