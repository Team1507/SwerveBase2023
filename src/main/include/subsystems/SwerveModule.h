// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>

#include "ctre/Phoenix.h"

class SwerveModule : public frc2::SubsystemBase {
 public:
  SwerveModule(const int driveMotorCanID, const int pivotMotorCanID, const int pivotEncoderCanID);

  void Periodic() override;



  //Set Modes
  void SetPivotAngle( float angle );



  

  //Pivot Encoders
  double GetPivotEncoderPosition(void);
  double GetPivotEncoderAbsoutePosition(void);
  
  double GetPivotMotorPosition(void);
  void   ResetPivotEncoders(void);


  //Testing only!
  float  GetDriveMotor( void );
  float  GetPivotMotor( void );
  void   SetDriveMotor( float power );
  void   SetPivotMotor( float power );  



  //Absolute Encoder calibration
  void   CalibratePivotEncoderAbsoutePositionStart(void);
  void   CalibratePivotEncoderAbsoutePositionOffset(void);
 
 
 
 
 private:

  WPI_TalonFX   m_driveMotor;
  WPI_TalonFX   m_pivotMotor;
  WPI_CANCoder  m_pivotEncoder;

  float m_desired_pivot_angle;

};
