// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SwerveModule.h"
#include <iostream>

#define ENCODER_TICKS_PER_DEGREE    (44000.0/360.0)


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
    m_pivotMotor.SetSelectedSensorPosition(0.0);

    //Initialise Pivot Encoder
    m_pivotEncoder.ConfigAbsoluteSensorRange(AbsoluteSensorRange::Signed_PlusMinus180 );    //Sets angle range as -180 to + 180
    m_pivotEncoder.ConfigSensorDirection(true);                                             //+angle Clockwise turn



    //Init members
    m_desired_pivot_angle = 0.0;

}

// This method will be called once per scheduler run
void SwerveModule::Periodic() 
{

    //Manual control of Pivot motor
    float curr_pivot_angle = GetPivotEncoderPosition();

    float angle_error = m_desired_pivot_angle - curr_pivot_angle;

    float power = 0.0;

    if(angle_error >  0.9 ) power = (0.07 + angle_error * 0.005);
    if(angle_error < -0.9 ) power = (angle_error * 0.005 - 0.07);


    if( power >  0.2) power =  0.2;
    if( power < -0.2) power = -0.2;

    SetPivotMotor( power );


    //std::cout << "Error " << angle_error << "  Power " << power << std::endl;

}



//Set angle of module
void SwerveModule::SetPivotAngle( float angle )
{
    m_desired_pivot_angle = angle;
}


// Get relative encoder position since reset.  Does not wrap, keep incrementing 
double SwerveModule::GetPivotEncoderPosition(void)
{
    return m_pivotEncoder.GetPosition();
}

// Get Absolute position, range [-180, 180]
double SwerveModule::GetPivotEncoderAbsoutePosition(void)
{
    return m_pivotEncoder.GetAbsolutePosition();    
}

// Get relative position from motor
double SwerveModule::GetPivotMotorPosition(void)
{
    return m_pivotMotor.GetSelectedSensorPosition(0) / ENCODER_TICKS_PER_DEGREE;    
}

void SwerveModule::ResetPivotEncoders(void)
{
    //Align encoders to Absolute Encoder
    m_pivotEncoder.SetPosition( GetPivotEncoderAbsoutePosition() );             //Cancoder relative position encoder                          
    m_pivotMotor.SetSelectedSensorPosition( GetPivotEncoderAbsoutePosition() * ENCODER_TICKS_PER_DEGREE );  //Motor encoder
}

/*
    * Testing Methods Only!
    */
float SwerveModule::GetDriveMotor( void )
{
    return m_driveMotor.Get();
}
float SwerveModule::GetPivotMotor( void )
{
    return m_pivotMotor.Get();
}
void SwerveModule::SetDriveMotor( float power )
{
    m_driveMotor.Set(ControlMode::PercentOutput, power);
}
void SwerveModule::SetPivotMotor( float power )
{
    m_pivotMotor.Set(ControlMode::PercentOutput, power);
}



//*********************************************
// *** CANCoder Absolute Position Calibration
//     **Note 1: Should only be done ONCE when calibrating swerve module
//     **Note 2: Wheels must be aligned to 0 degree position before running this procedure
//  Due to delay in the can bus, this must be done in 2 steps:
//    1) Zero Magnet offet - clears out any previous calibration
//   -delay-
//    2) Get position error then set magnet offset to zero absolute encoder  
void SwerveModule::CalibratePivotEncoderAbsoutePositionStart(void)
{
    m_pivotEncoder.ConfigMagnetOffset( 0.0 );                           //Clear offset
}
void SwerveModule::CalibratePivotEncoderAbsoutePositionOffset(void)
{
    double curr_abs_position = m_pivotEncoder.GetAbsolutePosition();    //Get Position, which is our new offset error
    m_pivotEncoder.ConfigMagnetOffset( -curr_abs_position, 10);         //Set Magnetic offset with offset error
}


