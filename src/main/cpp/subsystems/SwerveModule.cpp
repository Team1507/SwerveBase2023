// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SwerveModule.h"
#include <iostream>

SwerveModule::SwerveModule(int driveMotorCanID, int pivotMotorCanID, int pivotEncoderCanID )
            : m_driveMotor(driveMotorCanID),
              m_pivotMotor(pivotMotorCanID),
              m_pivotEncoder(pivotEncoderCanID)
{

    //Initialize Drive Motor
    m_driveMotor.ConfigFactoryDefault();
    m_driveMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor,0,10);
    m_driveMotor.SetInverted( false );
    m_driveMotor.SetNeutralMode(NeutralMode::Brake);

    //Initialize pivot Motor
    m_pivotMotor.ConfigFactoryDefault();
    m_pivotMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor,0,10);
    m_pivotMotor.SetInverted( false );
    m_pivotMotor.SetNeutralMode(NeutralMode::Brake);

    //Initialise Pivot Encoder
    m_pivotEncoder.ConfigAbsoluteSensorRange(AbsoluteSensorRange::Signed_PlusMinus180 ); //Sets angle range as -180 to + 180

}

// This method will be called once per scheduler run
void SwerveModule::Periodic() {}



    //Test Methods for now....

    void SwerveModule::DriveMotor( float power )
    {
        m_driveMotor.Set(ControlMode::PercentOutput, power);
    }
    void SwerveModule::PivotMotor( float power )
    {
        m_pivotMotor.Set(ControlMode::PercentOutput, power);
    }


    // Get relative encoder position since reset.  Does not wrap, keep incrementing 
    double SwerveModule::GetPivotPosition(void)
    {
        return m_pivotEncoder.GetPosition();
    }

    // Get Absolute position, range [-180, 180]
    double SwerveModule::GetPivotAbsoutePosition(void)
    {
        return m_pivotEncoder.GetAbsolutePosition();    
    }




    //*********************************************
    // *** CANCoder Absolute Position Calibration
    //     **Note 1: Should only be done ONCE when calibrating swerve module
    //     **Note 2: Wheels must be aligned to 0 degree position before running this procedure
    //  Due to delay in the can bus, this must be done in 2 steps:
    //    1) Zero Magnet offet - clears out any previous calibration
    //   -delay-
    //    2) Get position error then set magnet offset to zero absolute encoder  
    void SwerveModule::CalibratePivotAbsoutePositionStart(void)
    {
        m_pivotEncoder.ConfigMagnetOffset( 0.0 );                           //Clear offset
    }
    void SwerveModule::CalibratePivotAbsoutePositionOffset(void)
    {
        double curr_abs_position = m_pivotEncoder.GetAbsolutePosition();    //Get Position, which is our offset error
        m_pivotEncoder.ConfigMagnetOffset( -curr_abs_position, 10);         //Set Magnetic offset with offset error
    }


