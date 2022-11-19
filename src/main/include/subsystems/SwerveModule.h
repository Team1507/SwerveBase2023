// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>

#include "ctre/Phoenix.h"

class SwerveModule : public frc2::SubsystemBase {
 public:
  SwerveModule(const int driveMotorCanID, const int angleMotorCanID, const int angleEncoderCanID);

  void Periodic() override;


  void DriveMotor( float power );
  void AngleMotor( float power );


 private:

  WPI_TalonFX   m_driveMotor;
  WPI_TalonFX   m_angleMotor;
  WPI_CANCoder  m_angleEncoder;

  

};
