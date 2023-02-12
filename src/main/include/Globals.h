// Globals.h
//
// This file contains global constants, which are used in multiple classes.
//

#ifndef _GLOBALS_H
#define _GLOBALS_H

double const k_jsDeadband = 0.07;

// CANSparkMax Motor IDs

// Swerve Drive Motors
int const k_swervePointBottom = 2;
int const k_swervePointTop = 3;
int const k_swerveLeftTop = 4;
int const k_swerveLeftBottom = 5;
int const k_swerveRightTop = 6;
int const k_swerveRightBotton = 7;
// Swerve Drive Pod Encoders
int const k_rightPodEncoder = 0;
int const k_leftPodEncoder = 1;
int const k_pointPodEncoder = 2;

// Elevator Motors
int const k_elevatorMotorA = 58;
int const k_elevatorMotorB = 8;
int const k_endofactorMotor = 13;

// EndEffector Solenoid
int const k_endEffectorOut = 7;
int const k_elevatorAtHomeLimitSwitch = 5;
int const k_detectConeLimitSwitch = 9;
int const k_endEffectorGrabber = 8;

#endif