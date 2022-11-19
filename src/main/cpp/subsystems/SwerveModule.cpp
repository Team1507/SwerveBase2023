// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SwerveModule.h"

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

  double SwerveModule::GetPivotPosition(void)
  {
    m_pivotEncoder.GetPosition();
  }
  double SwerveModule::GetPivotAbsoutePosition(void)
  {
    m_pivotEncoder.GetAbsolutePosition();
  }

