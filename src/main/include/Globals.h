// Globals.h
//
// This file contains global constants, which are used in multiple classes.
//

#ifndef _GLOBALS_H
#define _GLOBALS_H

#define _DEBUGME                    
#define _TESTJOYSTICK               
#define _TESTPIGEON                 
#define _TESTELEVATOR               

double const k_jsDeadband =      0.08;

// Swerve Drive Motors
int const k_swervePointBottom =         2;
int const k_swervePointTop =            3;
int const k_swerveLeftTop =             5;
int const k_swerveLeftBottom =          4;
int const k_swerveRightTop =            7;
int const k_swerveRightBottom =         6;

// IMU (pigeon 2.0) 
int const k_pigeonID =                  21;
std::string const k_canbus =            "rio";

// Swerve Drive Pod Encoders
int const k_rightPodEncoder =           0;
int const k_leftPodEncoder =            1;
int const k_pointPodEncoder =           2;

// Elevator Motors
int const k_elevatorMotorA =            11;
int const k_elevatorMotorB =            12;
int const k_endofactorMotor =           13;

// Intake Motors
int const k_intakeLeftDeployMotor =     14;
int const k_intakeRightDeployMotor =    15;
int const k_intakeRollerMotor =         16;

// Robot Intake Solenoids
int const k_robotIntakeDeploy =         1;
int const k_robotIntakeClamp =          0;

// Pneumatics
int const k_pneumaticHub =              8;

// Motor constants
double const max_motor_temp =           90.0;

// LED channel constants
int const k_coneLED =                   5;
int const k_cubeLED =                   6;
int const k_alignedLED =                7;
int const k_redLED =                    8;
int const k_blueLED =                   9;

// Sensor to detect a Cube
int const k_cubeSense =                 3;

typedef enum 
{
    RIGHT_POD,
    LEFT_POD,
    POINT_POD
} PodOrientation;

typedef enum
{
    TOP_MOTOR,
    BOTTOM_MOTOR
} PodMotor;


// Application Times based on loops (20 msec per loop)
#define ONE_SECOND      50
#define TWO_SECONDS     ONE_SECOND * 2
#define FIVE_SECONDS    ONE_SECOND * 5
#endif