// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>

#include "ctre/Phoenix.h"
#include "Constants.h"

class Drivetrain : public frc2::SubsystemBase {
 public:
  Drivetrain();


  void Periodic() override;

  void Drive( float power );


 private:

  WPI_TalonFX m_motor{ FRONT_RIGHT_DRIVE_CAN_ID };



};
