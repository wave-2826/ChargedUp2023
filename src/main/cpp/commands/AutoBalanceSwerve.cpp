// RobotBuilder Version: 5.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

// ROBOTBUILDER TYPE: Command.
#include <frc/smartdashboard/SmartDashboard.h>
#include "commands/AutoBalanceSwerve.h"
#include "Globals.h"

static const double k_maxBalancePidOut = 5.0;

AutoBalanceSwerve::AutoBalanceSwerve(SwerveDrive* swerveDrive)
: m_swerveDrive(swerveDrive)
{

    // Use AddRequirements() here to declare subsystem dependencies
    // eg. AddRequirements(m_Subsystem);
    SetName("AutoBalanceSwerve");
    m_balanceState = Balance_Off;
    // m_startingYaw = m_swerveDrive->GetRobotYaw();

    // Set default gains
    m_pGain = 1.0;
    m_iGain = 2.0;
    m_dGain = 0.5;
    m_pitchTolerence = 2.0;
    m_balancePID = new frc2::PIDController(m_pGain, m_iGain, m_dGain);
}

// Called just before this Command runs the first time
void AutoBalanceSwerve::Initialize() {
    m_balanceState = Balance_Off;
    m_isBalanced = false;
    m_swerveDrive->initHeading();
    while (!m_swerveDrive->InitialSwerve());
    // m_startingYaw = m_swerveDrive->GetRobotYaw();
}

void AutoBalanceSwerve::updatePID(double p, double i, double d, double delta)
{
    m_pGain = frc::SmartDashboard::GetNumber("Balance_P", 1.0);
    m_iGain = frc::SmartDashboard::GetNumber("Balance_I", 5.0);
    m_dGain = frc::SmartDashboard::GetNumber("Balance_D", 0.1);
    m_pitchTolerence = frc::SmartDashboard::GetNumber("Balance_Delta", 2.0);

    m_balancePID->SetPID(m_pGain, m_iGain, m_dGain);
}

// Called repeatedly when this Command is scheduled to run
void AutoBalanceSwerve::Execute() 
{
    double robotPitch = m_swerveDrive->GetRobotPitch();
    double moveCmd = 0.0;

    switch(m_balanceState) 
    {
        case Balance_Off:
            // Get latest from Smart Dash Board
            m_pGain = frc::SmartDashboard::GetNumber("Balance_P", 1.0);
            m_iGain = frc::SmartDashboard::GetNumber("Balance_I", 5.0);
            m_dGain = frc::SmartDashboard::GetNumber("Balance_D", 0.1);
            m_pitchTolerence = frc::SmartDashboard::GetNumber("Balance_Delta", 2.0);
            m_balancePID->SetPID(m_pGain, m_iGain, m_dGain);

            // CASE: before charging station ramp drive straight   
            m_isBalanced = false; 
            moveCmd = robotPitch < 2 ? 1.0 : 0.7;
            if (robotPitch > 1.0)
            {
                m_balancePID->Reset();
                m_balanceState = Balance_Active;
            }
            break;
        case Balance_Active:
            m_isBalanced = false;
            // Use PID to get inside pitch tolerence
            if(std::fabs(robotPitch) > m_pitchTolerence)
            {
                m_balanceTimer = 0;
                double pidOut = m_balancePID->Calculate(robotPitch, 0.0);
                std::cout << "PID Out: " << pidOut << std::endl;
                moveCmd = pidOut / k_maxBalancePidOut;
                if (moveCmd > 1.0)
                {
                    moveCmd = 1.0;
                }
                else if (moveCmd < -1.0)
                {
                    moveCmd = -1.0;
                }      
            }
            else
            {
                m_balanceTimer++;
                if(ONE_SECOND < m_balanceTimer)
                {
                    m_balanceState = Balance_Success;
                }
            }
            break;
        case Balance_Success:
            // // CASE: balanced on station
            // // stay put + end auto
            m_isBalanced = true;
            std::cout << "LEVEL BALANCE" << std::endl;
            break;
        default:
            break;
    }

    m_swerveDrive->HeadingSwerve(moveCmd);
    std::cout << "State: " << m_balanceState << " PITCH: " << robotPitch << " Move: " << moveCmd << std::endl;
}

// Make this return true when this Command no longer needs to run execute()
bool AutoBalanceSwerve::IsFinished() {
    if (m_isBalanced) {
        m_swerveDrive->HeadingSwerve(0);
        std::cout << "IS FINISHED: " << m_isBalanced << std::endl;
    }
    return m_isBalanced;
}

// Called once after isFinished returns true
void AutoBalanceSwerve::End(bool interrupted) {
    m_swerveDrive->initHeading();
    m_swerveDrive->HeadingSwerve(0.0);
}

bool AutoBalanceSwerve::RunsWhenDisabled() const {
    return false;
}
