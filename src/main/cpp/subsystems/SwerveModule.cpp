// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SwerveModule.h"

SwerveModule::SwerveModule(int driveMotorCanID, int angleMotorCanID, int angleEncoderCanID )
            : m_driveMotor(driveMotorCanID),
              m_angleMotor(angleMotorCanID),
              m_angleEncoder(angleEncoderCanID)
{

    //Initialize Drive Motor
    m_driveMotor.ConfigFactoryDefault();
    m_driveMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor,0,10);
    m_driveMotor.SetInverted( false );
    m_driveMotor.SetNeutralMode(NeutralMode::Brake);

    //Initialize Angle Motor
    m_angleMotor.ConfigFactoryDefault();
    m_angleMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor,0,10);
    m_angleMotor.SetInverted( false );
    m_angleMotor.SetNeutralMode(NeutralMode::Brake);



}

// This method will be called once per scheduler run
void SwerveModule::Periodic() {}



//Test Methods for now....
  void SwerveModule::DriveMotor( float power )
  {
    m_driveMotor.Set(ControlMode::PercentOutput, power);
  }
  void SwerveModule::AngleMotor( float power )
  {
    m_angleMotor.Set(ControlMode::PercentOutput, power);
  }



