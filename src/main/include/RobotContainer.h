// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/Command.h>

#include "commands/ExampleCommand.h"
#include "subsystems/ExampleSubsystem.h"
#include <frc2/command/button/JoystickButton.h>

#include <frc/XboxController.h>

#include "subsystems/Drivetrain.h"
#include "GamepadMap.h"



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

  frc2::JoystickButton m_btn_xbox_A{&m_xbox, GAMEPADMAP_BUTTON_A};
  frc2::JoystickButton m_btn_xbox_B{&m_xbox, GAMEPADMAP_BUTTON_B};
  frc2::JoystickButton m_btn_xbox_X{&m_xbox, GAMEPADMAP_BUTTON_X};
  frc2::JoystickButton m_btn_xbox_Y{&m_xbox, GAMEPADMAP_BUTTON_Y};

};
