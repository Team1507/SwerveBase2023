// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdDriveWithGamepad.h"

#include "Robot.h"

#include <iostream>

CmdDriveWithGamepad::CmdDriveWithGamepad() 
{
  AddRequirements({ &m_container.m_drivetrain });
}


void CmdDriveWithGamepad::Initialize() 
{
  std::cout<<"Starting CmdDriveWithGamepad"<<std::endl;
}


void CmdDriveWithGamepad::Execute() 
{
  m_container.m_drivetrain.Drive( m_container.m_xbox.GetLeftX(),  m_container.m_xbox.GetLeftY(),  m_container.m_xbox.GetRightX()  );
  


}


void CmdDriveWithGamepad::End(bool interrupted) 
{
  std::cout<<"End CmdDriveWithGamepad " << interrupted <<std::endl;
}


bool CmdDriveWithGamepad::IsFinished() 
{
  return false;
}
