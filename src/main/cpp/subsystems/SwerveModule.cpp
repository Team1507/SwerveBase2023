// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SwerveModule.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "Robot.h"
#include <iostream>


//Falcon steer ticks per degree
// MK4i steer ratio 150/7:1.   Integrated encoder = 2048 ticks/rotation
// Therefore 150/7 * 2048 =43885.7
#define ENCODER_TICKS_PER_DEGREE    (43885.7/360.0)


SwerveModule::SwerveModule(int driveMotorCanID, int steerMotorCanID, int steerEncoderCanID, std::string debugID )
            : m_driveMotor(driveMotorCanID),
              m_steerMotor(steerMotorCanID),
              m_steerEncoder(steerEncoderCanID),
              m_dbgID(debugID)
{

    //Initialize Drive Motor
    m_driveMotor.ConfigFactoryDefault();
    m_driveMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor,0,10);
    m_driveMotor.SetInverted( false );
    m_driveMotor.SetNeutralMode(NeutralMode::Brake);
    m_steerMotor.SetSelectedSensorPosition(0.0,0,10);

    //Initialize steer Motor
    m_steerMotor.ConfigFactoryDefault();
    m_steerMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor,0,10);
    m_steerMotor.SetInverted( true );
    m_steerMotor.SetNeutralMode(NeutralMode::Brake);
    m_steerMotor.SetSelectedSensorPosition(0.0,0,10);

    //Initialize steer PID
    m_steerMotor.Config_kF(0, 0.0, 10);
    m_steerMotor.Config_kP(0, 0.1, 10);
    m_steerMotor.Config_kI(0, 0.0, 10);
    m_steerMotor.Config_kD(0, 0.0, 10);

    //m_steerMotor.ConfigAllowableClosedloopError( 0, 1.0 * ENCODER_TICKS_PER_DEGREE, 10 );



    //Initialise Steer Encoder
    m_steerEncoder.ConfigAbsoluteSensorRange(AbsoluteSensorRange::Signed_PlusMinus180 );    //Sets angle range as -180 to + 180
    m_steerEncoder.ConfigSensorDirection(false);                                            //+angle CounterClockwise turn



    //Init members
    m_desired_steer_angle = 90.0;   //Steer Angle of 90 = forward

    std::cout << "Module Debug ID= " << m_dbgID << std::endl;

}

// This method will be called once per scheduler run
void SwerveModule::Periodic() 
{

    //Debug Output
    frc::SmartDashboard::PutNumber(m_dbgID + "-EncAbs",  GetSteerEncoderAbsoutePosition() ); 
    frc::SmartDashboard::PutNumber(m_dbgID + "-EncPos",  GetSteerEncoderPosition() ); 
    frc::SmartDashboard::PutNumber(m_dbgID + "-MotPos",  GetSteerMotorPosition() ); 
    frc::SmartDashboard::PutNumber(m_dbgID + "-AngReq",  m_desired_steer_angle ); 

    frc::SmartDashboard::PutNumber(m_dbgID + "-DrvPwr",  m_driveMotor.GetMotorOutputPercent() ); 


//
//    //Manual control of Steer motor
//    //float curr_steer_angle = GetSteerEncoderPosition();
//    float curr_steer_angle = GetSteerEncoderAbsoutePosition();
//
//    float angle_error = curr_steer_angle - m_desired_steer_angle;
//
//    if( angle_error >= 180.0 )
//        angle_error -= 360.0;  //flip direction
//
//    if( angle_error <= -180.0 )
//        angle_error += 360.0;  //flip direction
//
//    float power = 0.0;
//
//    if(angle_error >  0.9 ) power = (0.07 + angle_error * 0.005);
//    if(angle_error < -0.9 ) power = (angle_error * 0.005 - 0.07);
//
//
//    if( power >  0.2) power =  0.2;
//    if( power < -0.2) power = -0.2;
//
//    //Stop running if Y button pressed
//    if(m_container.m_xbox.GetYButton())
//    {
//        SetSteerMotor( 0.0 );
//        power= 0.0;
//    }
//
//    else
//        SetSteerMotor( power );
//
//
//    // //std::cout << "Error " << angle_error << "  Power " << power << std::endl;
//
//    // if( power != 0.0)
//    //     std::cout << curr_steer_angle << "    " << m_desired_steer_angle  << "   "  << angle_error << "  Power " << power << std::endl;
//
}



//Set angle of module
//Input Range[-180 to 180]
void SwerveModule::SetSteerAngle( float angle )
{
    m_desired_steer_angle = angle;

    //Crossover logic and PID loop

    //Get current position of the drive motor
    float curr_steer_angle    = GetSteerEncoderAbsoutePosition();               //return in degrees [-180:180]

    float angle_error = m_desired_steer_angle - curr_steer_angle;               //Calculate angle delta

    //if angle error is > 180, its faster to go the oppisite way
    if( angle_error >=  180.0 )  angle_error -= 360.0;
    if( angle_error <= -180.0 )  angle_error += 360.0;


    float curr_steer_position = m_steerMotor.GetSelectedSensorPosition(0);      //return in encoder counts

    float target_position = curr_steer_position + (angle_error* ENCODER_TICKS_PER_DEGREE);  

    m_steerMotor.Set(ControlMode::Position,  target_position );

}


// Get relative encoder position since reset.  Does not wrap, keep incrementing 
double SwerveModule::GetSteerEncoderPosition(void)
{
    return m_steerEncoder.GetPosition();
}

// Get Absolute position, range [-180, 180]
double SwerveModule::GetSteerEncoderAbsoutePosition(void)
{
    return m_steerEncoder.GetAbsolutePosition();    
}

// Get relative position from motor
double SwerveModule::GetSteerMotorPosition(void)
{
    return m_steerMotor.GetSelectedSensorPosition(0) / ENCODER_TICKS_PER_DEGREE;    
}

void SwerveModule::ResetSteerEncoders(void)
{
    //Align encoders to Absolute Encoder
    m_steerEncoder.SetPosition( GetSteerEncoderAbsoutePosition() );             //Cancoder relative position encoder                          
    m_steerMotor.SetSelectedSensorPosition( GetSteerEncoderAbsoutePosition() * ENCODER_TICKS_PER_DEGREE );  //Motor encoder
}

/*
    * Testing Methods Only!
    */
float SwerveModule::GetDriveMotor( void )
{
    return m_driveMotor.Get();
}
float SwerveModule::GetSteerMotor( void )
{
    return m_steerMotor.GetMotorOutputPercent();
}
void SwerveModule::SetDriveMotor( float power )
{
    m_driveMotor.Set(ControlMode::PercentOutput, power);
}
void SwerveModule::SetSteerMotor( float power )
{
    m_steerMotor.Set(ControlMode::PercentOutput, power);
}



//*********************************************
// *** CANCoder Absolute Position Calibration
//     **Note 1: Should only be done ONCE when calibrating swerve module
//     **Note 2: Wheels must be aligned to 0 degree position before running this procedure
//  Due to delay in the can bus, this must be done in 2 steps:
//    1) Zero Magnet offet - clears out any previous calibration
//   -delay-
//    2) Get position error then set magnet offset to zero absolute encoder  
void SwerveModule::CalibrateSteerEncoderAbsoutePositionStart(void)
{
    m_steerEncoder.ConfigFactoryDefault();
    m_steerEncoder.ConfigMagnetOffset( 0.0 );                           //Clear offset
}
void SwerveModule::CalibrateSteerEncoderAbsoutePositionOffset(void)
{
    double curr_abs_position = m_steerEncoder.GetAbsolutePosition();    //Get Position, which is our new offset error
    m_steerEncoder.ConfigMagnetOffset( -curr_abs_position, 10);         //Set Magnetic offset with offset error
}


