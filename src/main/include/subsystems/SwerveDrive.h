// RobotBuilder Version: 4.0
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

#include <iostream>
#include <frc2/command/SubsystemBase.h>
#include "ctre/Phoenix.h"
#include <frc/Encoder.h>
#include <rev/CANSparkMax.h>
#include "subsystems/SwervePod.h"
#include <frc/kinematics/SwerveDriveKinematics.h>
#include <units/velocity.h>
#include <ctre/phoenix/sensors/Pigeon2.h>
#include <frc/XboxController.h>

typedef enum
{
    Heading_Init,
    Heading_Active
} SwerveHeadingState;

/**
 * SwerveDrive header file
 *
 * @author 2826WaveRobotics
 */
class SwerveDrive: public frc2::SubsystemBase {
    // It's desirable that everything possible is private except
    // for methods that implement subsystem capabilities
    private:        

        ctre::phoenix::sensors::Pigeon2 *m_pigeon;
        double m_gyroHeadings[3] = {0, 0, 0};

        rev::CANSparkMax *m_rightBottomMotor;
        rev::CANSparkMax *m_rightTopMotor;
        rev::CANSparkMax *m_leftBottomMotor;
        rev::CANSparkMax *m_leftTopMotor;
        rev::CANSparkMax *m_pointBottomMotor;
        rev::CANSparkMax *m_pointTopMotor;

        frc::SwerveDriveKinematics<3> *m_kinematics;

        SwervePod *m_rightPod;
        SwervePod *m_leftPod;
        SwervePod *m_pointPod;

        // const double k_gearRatioWheelSpeed = 3.2196;
        const double k_gearRatioWheelSpeed = 4.9659;
        const double k_wheelDiameterMeters = 0.0635;
        const double k_wheelCircumferenceMeters = k_wheelDiameterMeters * (double)3.141592653;
        const double k_maxMotorSpeed = 5200.0;

        // motor currents;
        double m_leftPodTopMotorCurrent = 0.0;
        double m_leftPodBottomMotorCurrent = 0.0;
        double m_rightPodTopMotorCurrent = 0.0;
        double m_rightPodBottomMotorCurrent = 0.0;
        double m_pointPodTopMotorCurrent = 0.0;
        double m_pointPodBottomMotorCurrent = 0.0;

        // Swerve smartdashboard inputs - offsets
        double m_leftPodOffsetAngle = 37.7;
        double m_rightPodOffsetAngle = -402;
        double m_pointPodOffsetAngle = 120.6;
        double leftOffset;
        double rightOffset;
        double pointOffset;

        // Swerve smartdashboard inputs - rotate
        double m_leftRotate = 1.0;
        double m_rightRotate = 1.0;
        double m_pointRotate = 1.0;
        double leftRotate;
        double rightRotate;
        double pointRotate;

        // Swerve smartdashboard inputs - p_PID
        double m_pLeft  = 2.0;
        double m_pRight = 2.0;
        double m_pPoint = 2.0;
        double pLeft;
        double pRight;
        double pPoint;

        // Swerve smartdashboard inputs - i_PID
        double m_iLeft  = 0.0;
        double m_iRight = 0.0;
        double m_iPoint = 0.0;
        double iLeft;
        double iRight;
        double iPoint;

        // Swerve smartdashboard inputs - d_PID
        double m_dLeft = 0.0;
        double m_dRight = 0.0;
        double m_dPoint = 0.0;
        double dLeft;
        double dRight;
        double dPoint;

        // Swerve smartdashboard inputs - scale top & bottom motor speeds
        double m_leftPodScaling = 1.0;
        double m_rightPodScaling = 1.0;
        double m_pointPodScaling = 1.0;
        double leftPodScaling;
        double rightPodScaling;
        double pointPodScaling;

        // Swerve smartdashboard inputs - scale top & bottom motor speeds
        double m_leftPodAlignedAngle = 5.0;
        double m_rightPodAlignedAngle = 5.0;
        double m_pointPodAlignedAngle = 5.0;
        double leftPodAlignedAngle;
        double rightPodAlignedAngle;
        double pointPodAlignedAngle;

        double m_lockedLeftAngle = 135.0; // 45 
        double m_lockedRightAngle = 225.0; // 315
        double m_lockedPointAngle = 90.0; // 0

        bool m_allAligned = false;

        frc2::PIDController *m_yawPID; 
        double m_yawPGain;
        double m_yawIGain;
        double m_yawDGain;
        double m_yawTolerence;
        double m_startingYaw;
        uint16_t m_yawTimer;
        SwerveHeadingState m_headingState;


    public:

        SwerveDrive();
    
        // length of the intake side
        const double robotWidth = 0.717;
        // length of the point to the midpoint of the intake side
        const double robotHeight = 0.617;

        void Periodic() override;
        void SimulationPeriodic() override;

        double GetMotorTemperature(int pod, int motor);

        void DiagonosticSwerveRotate(std::string podInput, std::string motorInput, double speedIncrement);

        void SetVoltageCompensation();

        /**
         * Function that takes inputs from the joysticks and transforms
         * the inputs into states (speed, angle) that individual swerve modules will utilize
         * 
         * @param move joystick input from left y-axis (LY)
         * @param strafe joystick input from left x-axis (LX)
         * @param rotation joystick input from right x-axis (RX)
        */
        void DrivePods(double move, double strafe, double rotation, double *PP);

        /**
         * Function that orients the swerve drive into opposing angles for a "locked" position
        */
        void LockSwerve();

        /**
         * Function that orients the swerve drive into aligned angles for a "straight" position
        */
        bool InitialSwerve();

        double GetLeftPodEncoderPosition();
        double GetRightPodEncoderPosition();
        double GetPointPodEncoderPosition();

        // Swerve drive smartdashboard functions
        double GetLeftPodOffsetAngle();
        double GetRightPodOffsetAngle();
        double GetPointPodOffsetAngle();
        void SetLeftPodOffsetAngle(double offsetAngle);
        void SetRightPodOffsetAngle(double offsetAngle);
        void SetPointPodOffsetAngle(double offsetAngle);  
        // Function that updates a pod offset angle based on input from the smartdashboard
        void UpdatePodOffsetAngles();
        // Show PID values for testing
        void DisplayPodPIDValues();

        double GetLeftPodRotate();
        double GetRightPodRotate();
        double GetPointPodRotate();
        void SetLeftPodRotate(double rotate);
        void SetRightPodRotate(double rotate);
        void SetPointPodRotate(double rotate);  
        // Function that updates a pod rotate multiplier based on input from the smartdashboard
        void UpdatePodRotate();

        double GetLeftPodPPID();
        double GetRightPodPPID();
        double GetPointPodPPID();
        void SetLeftPodPPID(double p);
        void SetRightPodPPID(double p);
        void SetPointPodPPID(double p);
        // Function that updates a pod p_PID value based on input from the smartdashboard
        void UpdatePodPPID();

        double GetLeftPodIPID();
        double GetRightPodIPID();
        double GetPointPodIPID();
        void SetLeftPodIPID(double i);
        void SetRightPodIPID(double i);
        void SetPointPodIPID(double i);
        // Function that updates a pod p_PID value based on input from the smartdashboard
        void UpdatePodIPID();

        double GetLeftPodDPID();
        double GetRightPodDPID();
        double GetPointPodDPID();
        void SetLeftPodDPID(double d);
        void SetRightPodDPID(double d);
        void SetPointPodDPID(double d);
        // Function that updates a pod d_PID value based on input from the smartdashboard
        void UpdatePodDPID();

        double GetLeftPodMotorScaling();
        double GetRightPodMotorScaling();
        double GetPointPodMotorScaling();
        void SetLeftPodMotorScaling(double scalingFactor);
        void SetRightPodMotorScaling(double scalingFactor);
        void SetPointPodMotorScaling(double scalingFactor);
        // Function that updates a pod p_PID value based on input from the smartdashboard
        void UpdatePodMotorScaling();

        bool GetLeftPodReversed();
        bool GetRightPodReversed();
        bool GetPointPodReversed();

        double GetLeftPodAlignedAngle();
        double GetRightPodAlignedAngle();
        double GetPointPodAlignedAngle();
        void SetLeftPodAlignedAngle(double angle);
        void SetRightPodAlignedAngle(double angle);
        void SetPointPodAlignedAngle(double angle);
        // Function that updates a pod p_PID value based on input from the smartdashboard
        void UpdatePodAlignedAngle();

        std::string GetRightPodCase();
        std::string GetLeftPodCase();
        std::string GetPointPodCase();

        /**
         * Function that gets the current of a given pod and motor in amps
         * 
         * @param pod which pod you want to query
         * rght: 0
         * left: 1
         * point: 2
         * @param motor which motor you want to get the current from
         * bottom: 0
         * top: 1
        */
        double GetPodCurrent(int pod, bool motor);

        // pigeon gyro getters
        double GetRobotPitch();
        double GetRobotRoll();
        double GetRobotYaw();

        void Initialize();

        // Drive straight Features
        void HeadingSwerve(double targetSpeed);
        void initHeading();
        
};

