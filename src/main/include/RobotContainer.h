// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/Command.h>

#include "commands/ExampleCommand.h"
#include "subsystems/ExampleSubsystem.h"

#include <frc/XboxController.h>

#include "subsystems/Drivetrain.h"



class RobotContainer
{
 public:
  RobotContainer();

  //****************Controllers*******************
  frc::XboxController m_xbox {0};


  //****************Subsystems*******************
  Drivetrain m_drivetrain;



  //******************AUTO*************************
  frc2::Command* GetAutonomousCommand();

 private:
  // The robot's subsystems and commands are defined here...
  ExampleSubsystem m_subsystem;
  ExampleCommand m_autonomousCommand;

  void ConfigureButtonBindings();
};
