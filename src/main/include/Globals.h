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
int const k_swerveLeftTop = 5;
int const k_swerveLeftBottom = 4;
int const k_swerveRightTop = 7;
int const k_swerveRightBotton = 6;
// Swerve Drive Pod Encoders
int const k_rightPodEncoder = 0;
int const k_leftPodEncoder = 1;
int const k_pointPodEncoder = 2;

// Elevator Motors
int const k_elevatorMotorA = 58;
int const k_elevatorMotorB = 8;
int const k_endofactorMotor = 13;

#endif