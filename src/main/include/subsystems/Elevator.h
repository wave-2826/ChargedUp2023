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
#include <frc/DigitalInput.h>
#include <frc/motorcontrol/PWMSparkMax.h>
#include <frc/XboxController.h>
#include <rev/SparkMaxRelativeEncoder.h>
#include <rev/CANSparkMax.h>
#include<rev/CANSparkMaxLowLevel.h>
#include "frc2/command/PIDSubsystem.h"
#include "frc/PneumaticHub.h"
#include "frc/Solenoid.h"
#include "frc/Compressor.h"

#include "Globals.h"

// Elevator functions used to deploy the elevator in auto mode
typedef enum 
{
    Elevator_Off,
    // Deploy elevator to a target
    Elevator_Deploy,
    Elevator_Hold
} ElevatorFunction;

/**
 * Elevator class shall be used to extend and retract the elevator. 
 * This class will also preform the functions of the EndEffector.
 * 
 * @author 2826WaveRobotics
*/
class Elevator: public frc2::SubsystemBase {
private:
    // It's desirable that everything possible is private except
    // for methods that implement subsystem capabilities

    frc::PneumaticHub m_pneumaticHub{k_pneumaticHub};
    frc::Compressor *m_compressor;

    // EndEffector solenoid to move up. Spring to down
    frc::Solenoid m_endEffectorSolenoid = m_pneumaticHub.MakeSolenoid(k_endEffectorOut);

    // EndEffector grabber solenoid to grab and release the cone
    frc::Solenoid m_endEffectorGrabberSolenoid = m_pneumaticHub.MakeSolenoid(k_endEffectorGrabber);

    // Current position of the elevator
    double m_elevatorPosition;

    // Elevator Home position
    double m_elevatorHomePosition;

    // Motor controller for the elevator
    rev::CANSparkMax *m_elevatorMotorB;
    rev::CANSparkMax *m_elevatorMotorA;

    // Internal incoders for the elevator motors
    rev::SparkMaxRelativeEncoder *m_elevatorEncoderA;
    rev::SparkMaxRelativeEncoder *m_elevatorEncoderB;

    // PID controller for the elevator auto deploy operations
    frc2::PIDController *m_elevatorPID; 

    // Pointer to the operator controller
    frc::XboxController *m_operatorJoystick;

    ElevatorFunction m_elevatorFunction;

    // Scoring object flag. True when scoring with Cone
    bool m_isCone;

    bool m_isStowing;

    bool m_targetSet;

    // Scoring target for the elevator
    double m_elevatorTarget;

    // Factor for the elevator position
    double m_distancePerRotation;

    // Limit where we use the fine gains
    double m_fineLimit;

    // Command speed to the elevator motors.
    void setElevator(double speed);

    // Command speed to the endEffector motor if speed is within range.
    void setEndEffectorRoller(double speed);

    double getPIDSpeed(double pidCommnd);

    // Constants used for Elevator functions
    static constexpr const double k_maxElevatorSpeed = 0.7;
    static constexpr const double k_elevatorHoldSpeed = 0.035;
    static constexpr const double k_endEffectorSpeedFactor = 0.5;

    // Tuning PID values
    double k_P = 4.0;
    double k_I = 0.0;
    double k_D = 1.0;
    double k_delta = 1.0;
    double k_rampPerLoop = 0.05;

    static constexpr const double k_PFine = 0.1;
    static constexpr const double k_IFine = 0.1;
    static constexpr const double k_DFine = 0.0;

    static constexpr const double k_fineLimit = 5.0;

    static constexpr const double k_numOfTeeth = 36.0;
    static constexpr const double k_teethSize = 0.25;  // in inches
    static constexpr const double k_gearRatio = 5; // Ratio 5:1

    static constexpr const double k_maxElevatorPosition = 56.0; // in inches
    
    // Pre-set elevator scoring position for the elevator
    static constexpr const double k_elevatorTargetTopCone = 51.5;
    static constexpr const double k_elevatorTargetMiddleCone = 31.0;
    static constexpr const double k_elevatorTargetTopCube = 54.5;
    static constexpr const double k_elevatorTargetMiddleCube = 36.0;
    static constexpr const double k_elevatorHumanStation = 34.65;

public:
    Elevator();

    void Periodic() override;
    void SimulationPeriodic() override;

    // Initialize Elevatorobject
    void Initialize();


    // Periodic operation for the elevator
    void runElevator();

    // Get current position of the elevator
    // Returns Pos A
    double getElevatorPosition();
    
    //Set scoring target
    void setCustomTarget(double target);
    void setBackoffTarget();
    void setTopConeTarget();
    void setMidConeTarget();
    void setTopCubeTarget();
    void setMidCubeTarget();
    void setHumanStationTarget();
    void setStowTarget();
    bool isTargetSet(){ return m_targetSet; }

    bool moveToCurrentTarget();
    bool moveElevatorToTargetManual(double target);
    bool stowElevator();
    bool stowElevatorAuto();
    bool backoffElevatorAuto();
};