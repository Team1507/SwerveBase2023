// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/Timer.h>

#include "ctre/Phoenix.h"

class SwerveModule : public frc2::SubsystemBase {
 public:
  SwerveModule(const int driveMotorCanID, const int steerMotorCanID, const int steerEncoderCanID, const std::string debugID);

  void Periodic() override;



  //Set Modes
  void SetSteerAngle( float angle );
  void SetSteerAngleV2( float angle );
  void SetDriveMotor( float power );

  

  //Steer Encoders
  double GetSteerEncoderPosition(void);
  double GetSteerEncoderAbsoutePosition(void);
  double GetSteerMotorPosition(void);
  void   ResetSteerEncoders(void);

  //Drive Encoders
  int  GetDriveEncoder(void);
  void HardResetDriveEncoder(void);
  void SoftResetDriveEncoder(void);


  //Motor Status
  float  GetDriveMotor( void );
  float  GetSteerMotor( void );
  bool   GetDriveInvertion( void );

  //Odometry
  void    ResetModuleOdometry(void);
  double  GetModuleOdometryX(void);           //inches
  double  GetModuleOdometryY(void);           //inches
  double  GetModuleOdometryVel(void);         //in/sec
  double  GetModuleOdometryLVel(void);        //in/sec
  double  GetModuleOdometryRVel(void);        //in/sec
  double  GetModuleOdometryHeading(void);     //degrees




  //Testing only!  
  void   SetSteerMotor( float power );  


  //Absolute Encoder calibration
  void   CalibrateSteerEncoderAbsoutePositionStart(void);
  void   CalibrateSteerEncoderAbsoutePositionOffset(void);
 
 

 
 private:

  WPI_TalonFX   m_driveMotor;
  WPI_TalonFX   m_steerMotor;
  WPI_CANCoder  m_steerEncoder;
  std::string   m_dbgID;
  frc::Timer    m_timer;

  float m_desired_steer_angle; 

  int   m_drive_encoder_zero;
  bool  m_invert_drive;       //invert drive direction



    //Module Odometry
    void   ModuleOdometryPeriodic(void);
    int    m_prev_drive_encoder;
    double m_prev_timestamp;

    double m_curr_x;  //inches
    double m_curr_y;  //inches
    double m_curr_v;  //inches/sec

};
