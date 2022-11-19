// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdTestOne.h"
#include "Robot.h"

CmdTestOne::CmdTestOne() 
{

  //AddRequirements?
}


void CmdTestOne::Initialize() 
{
  std::cout<<"CmdTestOne"<<std::endl;

  m_container.m_drivetrain.m_frontRight.CalibratePivotAbsoutePositionOffset();


}
