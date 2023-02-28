#include <frc2/command/SubsystemBase.h>
#include <frc/Encoder.h>
#include <rev/CANSparkMax.h>
#include <frc/DutyCycleEncoder.h>
#include <frc/kinematics/SwerveModuleState.h>
#include <frc/controller/PIDController.h>
#include <frc2/command/PIDSubsystem.h>
#include <string>

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

        // The motor that drives the top gear.
        rev::CANSparkMax *m_topMotor;

        // The motor that drives the bottom gear.
        rev::CANSparkMax *m_bottomMotor;

        // The encoder for the wheel position.
        frc::DutyCycleEncoder *m_podEncoder;        

        static constexpr const double kP = 0.1;
        static constexpr const double kI = 0.0;
        static constexpr const double kD = 0.0;

        // Angles are measured counter-clockwise, with zero being "robot forward"
        double m_offsetAngle; 

        bool m_isReversed = false;       
        int m_encoderChannel;
        std::string m_podName = "";
        double m_turnTuningFactor;
        bool m_initialized;   

        // variable for testing printouts
        int m_counter;

    public:
    
        SwervePod(rev::CANSparkMax *topMotor, rev::CANSparkMax *bottomMotor, double turnTuningFactor, double offsetAngle, int encoderChannel);

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
        bool Drive(frc::SwerveModuleState state, bool allAligned);

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
        void FlipIsReversed(bool state);

        void UpdateOffsetAngle();
        void Periodic(); 
        void SimulationPeriodic();
};
