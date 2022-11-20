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

  void Drive( float lx, float ly, float rx  );


  //Encoders
  void HardResetDriveEncoders(void);
  void ResetDriveEncoders(void);
  void ResetPivotEncoders(void);


  //These should be private!!!!!
  SwerveModule m_frontRight{ FRONT_RIGHT_DRIVE_MOTOR_CAN_ID,  FRONT_RIGHT_PIVOT_MOTOR_CAN_ID,  FRONT_RIGHT_PIVOT_ENCODER_CAN_ID };

 private:





};
