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
int const k_swervePointBottom =     2;
int const k_swervePointTop =        3;
int const k_swerveLeftTop =         5;
int const k_swerveLeftBottom =      4;
int const k_swerveRightTop =        7;
int const k_swerveRightBottom =     6;

// IMU (pigeon 2.0) 
int const k_pigeonID =              21;
std::string const k_canbus =        "rio";

// Swerve Drive Pod Encoders
int const k_rightPodEncoder =       0;
int const k_leftPodEncoder =        1;
int const k_pointPodEncoder =       2;

// Elevator Motors
int const k_elevatorMotorA =        11;
int const k_elevatorMotorB =        12;
int const k_endofactorMotor =       13;

// EndEffector Solenoid
int const k_endEffectorOut =            1;
int const k_endEffectorGrabber =        0;
// int const k_elevatorAtHomeLimitSwitch = 5;
int const k_detectConeLimitSwitch =     5;

// Pneumatics
int const k_pneumaticHub =              8;

// Motor constants
double const max_motor_temp =           90.0;

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

#endif