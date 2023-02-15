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

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include <frc2/command/SubsystemBase.h>
#include <frc/DigitalInput.h>
#include <frc/DigitalOutput.h>
#include <frc/motorcontrol/PWMSparkMax.h>
#include <frc/XboxController.h>
#include <rev/SparkMaxRelativeEncoder.h>
#include <rev/CANSparkMax.h>
#include<rev/CANSparkMaxLowLevel.h>
#include "frc2/command/PIDSubsystem.h"
#include "frc/PneumaticHub.h"
#include "frc/Solenoid.h"

#include "Globals.h"


// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

/**
 *
 *
 * @author Wave Robotics 2826
 */

// Elevator functions used to deploy the elevator in auto mode
typedef enum 
{
    Elevator_Off,
    // Deploy elevator to a target
    Elevator_Deploy
} ElevatorFunction;

// EndEffector functions
typedef enum
{
    EF_Up,
    EF_Down
} EndEffectorFunction;

// Elevator class shall be used to extend and retract the elevator. 
// This class will also preform the functions of the EndEffector.
class Elevator: public frc2::SubsystemBase {
private:
    // It's desirable that everything possible is private except
    // for methods that implement subsystem capabilities

    // Limit switch to detect the elevator home position
    frc::DigitalInput m_elevatorAtHomeLimitSwitch{k_elevatorAtHomeLimitSwitch};

    // Limit swtch to detect if a cone is in range
    frc::DigitalInput m_detectConeLimitSwitch{k_detectConeLimitSwitch};

    frc::PneumaticHub m_pneumaticHub{k_pneumaticHub};

    // EndEffector solenoid to move up. Spring to down
    frc::Solenoid m_endEffectorSolenoid = m_pneumaticHub.MakeSolenoid(k_endEffectorOut);

    // EndEffector grabber solenoid to grab and release the cone
    frc::Solenoid m_endEffectorGrabberSolenoid = m_pneumaticHub.MakeSolenoid(k_endEffectorGrabber);

    // Current position of the elevator
    double m_elevatorPosition;

    // Elevator Home position
    double m_elevatorHomePosition;

    // The motor controller for the EndEffector intake motor
    rev::CANSparkMax *m_endEffectorMotor;

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
    
    EndEffectorFunction m_endEffectorFunction;

    // Scoring object flag. True when scoring with Cone
    bool m_isCone;

    // Flag for stowing the elevator
    bool m_isStowing;

    bool m_targetSet;

    // Scoring target for the elevator
    double m_elevatorTarget;

    // Factor for the elevator position
    double m_distancePerRotation;

    // Command speed to the elevator motors.
    void setElevator(double speed);

    // Command speed to the endEffector motor if speed is within range.
    void setEndEffectorRoller(double speed);

    double getPIDSpeed(double pidCommnd);

    // Constants used for Elevator functions
    static constexpr const double k_maxElevatorSpeed = 1.0;
    static constexpr const double k_endEffectorSpeedFactor = 0.5;
    static constexpr const double k_P = 0.5;
    static constexpr const double k_I = 0.0;
    static constexpr const double k_D = 0.0;
    static constexpr const double k_delta = 1.0;

    static constexpr const double k_numOfTeeth = 36.0;
    static constexpr const double k_teethSize = 0.25;  // in inches
    static constexpr const double k_gearRatio = 4; // Ratio 4:1

    static constexpr const double k_maxElevatorPosition = 100.0; // in inches
    static constexpr const double k_encoderPosConversionFactor = 0.5; // TBD: Need the conversion factor

    // Pre-set elevator scoing position for the elevator
    static constexpr const double k_elevatorTargetTopCone = 54.5;
    static constexpr const double k_elevatorTargetMiddleCone = 30.5;
    static constexpr const double k_elevatorTargetTopCube = 46.5;
    static constexpr const double k_elevatorTargetMiddleCube = 22.5;
    static constexpr const double k_elevatorHumanStation = 10.25;

public:
    Elevator();

    void Periodic() override;
    void SimulationPeriodic() override;

    // Initialize Elevatorobject
    void Initialize();

    // Periodic operation for the elevator
    void runElevator();

    // Elevator EndEffector operations.
    void runEndEffector();

    // Get current position of the elevator
    // Returns 0 if k_maxDelta < (Pos A ~ Pos B), otherwise return Pos A
    double getElevatorPosition();

    // Returns true when elevator is at home position
    bool isElevatorAtHome();
    
    //Set scoring target
    void setTopConeTarget();
    void setMidConeTarget();
    void setTopCubeTarget();
    void setMidCubeTarget();
    void setHumanStationTarget();
    void resetTarget();
    bool isTargetSet(){ return m_targetSet; }
    
    // Activate (open/close) grabber. Normally close
    void MoveGrabber(bool open);

    bool moveToCurrentTarget();
    void moveEndEffector(bool down);
};

