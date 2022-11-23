// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>

#include "ctre/Phoenix.h"

class SwerveModule : public frc2::SubsystemBase {
 public:
  SwerveModule(const int driveMotorCanID, const int steerMotorCanID, const int steerEncoderCanID, const std::string debugID);

  void Periodic() override;



  //Set Modes
  void SetSteerAngle( float angle );



  

  //Steer Encoders
  double GetSteerEncoderPosition(void);
  double GetSteerEncoderAbsoutePosition(void);
  
  double GetSteerMotorPosition(void);
  void   ResetSteerEncoders(void);


  //Testing only!
  float  GetDriveMotor( void );
  float  GetSteerMotor( void );
  void   SetDriveMotor( float power );
  void   SetSteerMotor( float power );  



  //Absolute Encoder calibration
  void   CalibrateSteerEncoderAbsoutePositionStart(void);
  void   CalibrateSteerEncoderAbsoutePositionOffset(void);
 
 

 
 private:

  WPI_TalonFX   m_driveMotor;
  WPI_TalonFX   m_steerMotor;
  WPI_CANCoder  m_steerEncoder;
  std::string   m_dbgID;


  float m_desired_steer_angle; 
};
