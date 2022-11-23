// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>

#include "subsystems/SwerveModule.h"

#include "Constants.h"

class Drivetrain : public frc2::SubsystemBase {
 public:
  Drivetrain();


  void Periodic() override;

  void RobotcentricDrive( float fwdrev, float rightleft, float rotate );
  void FieldcentricDrive( float fwdrev, float rightleft, float rotate );


  //Encoders
  void HardResetDriveEncoders(void);
  void ResetDriveEncoders(void);
  void ResetSteerEncoders(void);



  //Absolute Encoder calibration
  void   CalibrateSteerEncoderAbsoutePositionStart(void);
  void   CalibrateSteerEncoderAbsoutePositionOffset(void);


 private:



  //Swerve Modules
  //    FL^FR
  //    RL RR
  SwerveModule m_frontRight{ FRONT_RIGHT_DRIVE_MOTOR_CAN_ID,  FRONT_RIGHT_STEER_MOTOR_CAN_ID,  FRONT_RIGHT_STEER_ENCODER_CAN_ID, "FR" };
  SwerveModule m_frontLeft { FRONT_LEFT_DRIVE_MOTOR_CAN_ID,   FRONT_LEFT_STEER_MOTOR_CAN_ID,   FRONT_LEFT_STEER_ENCODER_CAN_ID,  "FL" };
  SwerveModule m_rearLeft  { REAR_LEFT_DRIVE_MOTOR_CAN_ID,    REAR_LEFT_STEER_MOTOR_CAN_ID,    REAR_LEFT_STEER_ENCODER_CAN_ID,   "RL" };
  SwerveModule m_rearRight { REAR_RIGHT_DRIVE_MOTOR_CAN_ID,   REAR_RIGHT_STEER_MOTOR_CAN_ID,   REAR_RIGHT_STEER_ENCODER_CAN_ID,  "RR" };
 

  //Array of pointers to swerve modules, to make processing eeach module more convenient
  SwerveModule* m_moduleList[NUM_SWERVE_MODULES];


};
