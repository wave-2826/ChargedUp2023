// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/WavePIDCommand.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
WavePIDCommand::WavePIDCommand()
    : CommandHelper{frc2::PIDController{0.05, 0, 0},
                    // This should return the measurement (GetRobotPitch)
                    [] { return 0.0; },
                    // This should return the setpoint (can also be a constant)
                    [] { return 0.0; },
                    // This uses the output
                    [](double output) {
                      // Use the output here (DrivePods - output = RY)
                    }} {}

// Returns true when the command should end.
bool WavePIDCommand::IsFinished() {
  return false;
}
