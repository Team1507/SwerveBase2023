// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include "frc/smartdashboard/SmartDashboard.h"


#include "commands/CmdDriveWithGamepad.h"
#include "commands/CmdDriveWithJoystick.h"

#include "commands/CmdButtonA.h"
#include "commands/CmdButtonB.h"
#include "commands/CmdButtonX.h"
#include "commands/CmdButtonY.h"
#include "commands/CmdTestOne.h"
#include "commands/CmdTestTwo.h"
#include "commands/CmdCalibrateSwerveEncoders.h"
#include "commands/CmdDriveClearAll.h"
#include "commands/CmdDriveTypeToggle.h"
#include "commands/CmdDriveForceSteerAngle.h"
#include "commands/GrpTest1.h"
#include "commands/AutoMoveToCone.h"
#include "commands/CmdGamepadToggle.h"

RobotContainer::RobotContainer() : m_autonomousCommand(&m_subsystem) {
  // Initialize all of your commands and subsystems here


  //**************************** Subsystem Defaults****************************************
  m_drivetrain.SetDefaultCommand( CmdDriveWithJoystick() );


  //********************************Smart Dashboard Buttons**************************************
  frc::SmartDashboard::PutData( "CmdTestOne", new CmdTestOne());
  frc::SmartDashboard::PutData( "CmdTestTwo", new CmdTestTwo());

  frc::SmartDashboard::PutData( "CmdDriveClearAll", new CmdDriveClearAll());

  frc::SmartDashboard::PutData( "CmdDriveTypeToggle", new CmdDriveTypeToggle());

  frc::SmartDashboard::PutData( "SteerAngle=0",  new CmdDriveForceSteerAngle(0.0));
  frc::SmartDashboard::PutData( "SteerAngle=90", new CmdDriveForceSteerAngle(90.0));

  frc::SmartDashboard::PutData( "GrpTest1", new GrpTest1());
  frc::SmartDashboard::PutData( "AutoDriveToCone", new AutoMoveToCone());

  frc::SmartDashboard::PutData( "CmdCalSwerveEnc_1", new CmdCalibrateSwerveEncoders(1));
  frc::SmartDashboard::PutData( "CmdCalSwerveEnc_2", new CmdCalibrateSwerveEncoders(2));

  frc::SmartDashboard::PutData( "Cont. Toggle (Gr = G, R = J)", new CmdGamepadToggle(&m_drivetrain));

  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {

  m_btn_xbox_A.WhenPressed(new CmdButtonA(true)).WhenReleased(new CmdButtonA(false));
  m_btn_xbox_B.WhenPressed(new CmdButtonB(true)).WhenReleased(new CmdButtonB(false));
  m_btn_xbox_X.WhenPressed(new CmdButtonX(true)).WhenReleased(new CmdButtonX(false));
  m_btn_xbox_Y.WhenPressed(new CmdButtonY(true)).WhenReleased(new CmdButtonY(false));


}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &m_autonomousCommand;
}
