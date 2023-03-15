// RobotBuilder Version: 5.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

// ROBOTBUILDER TYPE: Subsystem.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/XboxController.h>
#include <rev/SparkMaxRelativeEncoder.h>
#include <rev/CANSparkMax.h>
#include <rev/CANSparkMaxLowLevel.h>
#include<frc/DigitalOutput.h>
#include "Globals.h"

/**
 * Elevator class shall be used to extend and retract the elevator. 
 * This class will also preform the functions of the EndEffector.
 * 
 * @author 2826WaveRobotics
*/
class EndEffector: public frc2::SubsystemBase {
private:
  
    // The motor controller for the EndEffector intake motor
    rev::CANSparkMax *m_endEffectorMotor;

    // Pointer to the operator controller
    frc::XboxController *m_operatorJoystick;

    // Scoring object flag. True when scoring with Cone
    bool m_isCone;

    // LED
    frc::DigitalOutput *m_coneLED;
    frc::DigitalOutput *m_cubeLED;
    // frc::DigitalOutput::DigitalOutput m_coneLED{5}
    // frc::DigitalOutput::DigitalOutput m_cubeLED{6}
    // frc::DigitalOutput m_coneLED{7};
    // frc::DigitalOutput m_coneLED{8};
    // frc::DigitalOutput m_coneLED{9};

    uint16_t m_endEffectorTimer;

    // Command speed to the endEffector motor if speed is within range.
    void setEndEffectorRoller(double speed);

    // Constants used for Elevator functions
    static constexpr const double k_endEffectorSpeedFactor = 0.5;
    static constexpr const uint16_t k_endEffectorActiveTime = ONE_SECOND;

public:
    EndEffector();

    void Periodic() override;
    void SimulationPeriodic() override;

    // Initialize Elevatorobject
    void Initialize();

    // Elevator EndEffector operations.
    void runEndEffector();
    void setRoller(double speed);

    void setGrabber(bool open);
    // bool moveGrabber(bool open);
    // void moveEndEffector(bool down);

    bool openGrabber();
    bool closeGrabber();

    bool lowerEndEffector();
    bool raiseEndEffector();
};