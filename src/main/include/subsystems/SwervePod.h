#include <frc2/command/SubsystemBase.h>
#include <frc/Encoder.h>
#include <rev/CANSparkMax.h>
#include <frc/DutyCycleEncoder.h>
#include <frc/kinematics/SwerveModuleState.h>
#include <frc/controller/PIDController.h>
#include <frc2/command/PIDSubsystem.h>
#include <string>
#include <vector>

/**
 * Swerve Pod encapsulating individual swerve pod functions + attributes
 * including absolute encoder capturing current angle
 * 
 * @author 2826WaveRobotics
 **/
class SwervePod {
    // It's desirable that everything possible is private except
    // for methods that implement subsystem capabilities
    private:

        rev::SparkMaxRelativeEncoder *m_topEncoder;
        rev::SparkMaxRelativeEncoder *m_bottomEncoder;

        std::string m_currentCase;

        // The motor that drives the top gear.
        rev::CANSparkMax *m_topMotor;

        // The motor that drives the bottom gear.
        rev::CANSparkMax *m_bottomMotor;

        // The encoder for the wheel position.
        frc::DutyCycleEncoder *m_podEncoder;        

        static constexpr const double kP = 0.1;
        static constexpr const double kI = 0.0;
        static constexpr const double kD = 0.0;

        // swerve tuning variables 
        double m_p;
        double m_i;
        double m_d;
        double m_alignedAngle;
        double m_motorScaling;

        std::vector<double> m_angleValues = { 0, 0, 0, 0, 0, 0, 0, 0 };
        int m_anglePointer = 0;

        // Angles are measured counter-clockwise, with zero being "robot forward"
        double m_offsetAngle;

        // track previous angle
        double m_previousAngle = 0;
        // track delta d_pid
        double m_deltaD = 0;

        bool m_isReversed = false;       
        int m_encoderChannel;
        std::string m_podName = "";
        double m_turnTuningFactor;
        bool m_initialized;   

        // variable for testing printouts
        int m_counter;

        double m_previousTopMotorSpeed;
        double m_previousBottomMotorSpeed;

    public:
    
        SwervePod(rev::CANSparkMax *topMotor, rev::CANSparkMax *bottomMotor, double p_PID, double i_PID, double d_PID, double motorScaling, double alignedAngle, double offsetAngle, int encoderChannel);

        // Initialize this module with the details provided by the robot-specific subclass.
        void Initialize(); 

        /**
         * Function to set a direction and speed for this swerve pod
         * 
         * @param state the Swerve Module state containing speed and angle,
         * with angle: -180 - 180, speed: -1.00 - 1.00
         * @param allAligned the boolean stating if all 3 pods are aligned,
         * if they are, pods can drive forward
         **/
        void Drive(frc::SwerveModuleState state, bool allAligned, double *returnArray);

        std::string GetCurrentCase();

        /**
         * Function to orientate swerve pod to a "locked" position
         * 
         * @param targetAngle angle at which the swerve pod should orientate to
        */
        void LockState(double target_angle);

        /**
         * Function to orientate swerve pod to an "initial" position (wheels aligned straight)
        */
        bool InitialState();

        /**
         * Function that gets the current counter
         * Used as a printout limit for testing/debugging 
         * 
         * @return int value of the cound
         **/ 
        int GetCounter();

        /**
         * Function that sets the current counter
         * Used as a printout limit for testing/debugging 
         * 
         * @param count int value to set the counter to
         **/ 
        void SetCounter(int count);

        /**
         * Function to get swerve pod reversed state, used in optimizing swerve logic to
         * determine if delta angle should be minimized and speed reversed
         **/ 
        bool GetIsReversed();
        /**
         * Function to flip swerve pod reversed state, used in optimizing swerve logic to
         * determine if delta angle should be minimized and speed reversed
         **/ 
        void FlipIsReversed();

        // Swerve Dashboard Live Update Functions
        void UpdateOffsetAngle();
        void UpdatePPID();
        void UpdateIPID();
        void UpdateDPID();
        void UpdateMotorScaling();
        void UpdateAlignedAngle();

        // Track Position of Module
        double GetPreviousAngle();
        void SetPreviousAngle(double angle);
        // Track delta D
        double GetDeltaD();
        void SetDeltaD(double delta);

        void Periodic(); 
        void SimulationPeriodic();

        // joystick input smoothing functions
        double LinearInterpolate(double speed, double targetSpeed, double movePercentage);
        double GetPreviousTopMotorSpeed();
        void SetPreviousTopMotorSpeed(double input);
        double GetPreviousBottomMotorSpeed();
        void SetPreviousBottomMotorSpeed(double input);
};
