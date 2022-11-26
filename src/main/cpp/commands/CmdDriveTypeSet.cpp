// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdDriveTypeSet.h"
#include "Robot.h"

CmdDriveTypeSet::CmdDriveTypeSet( Drivetrain::driveType type ) 
{
  m_type = type;
}

// Called when the command is initially scheduled.
void CmdDriveTypeSet::Initialize() 
{
  m_container.m_drivetrain.SetDriveType( m_type );
}
