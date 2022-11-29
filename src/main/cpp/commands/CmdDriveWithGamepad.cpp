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

  //Limiters
  const float xyScaleValue = 0.25;    //Translational scale (fwd/rev/strafe)
  const float rScaleValue  = 0.25;    //Rotational scale
  

  //Get Gamepad Inputs
  float yL = m_container.m_xbox.GetLeftY();
  float xL = m_container.m_xbox.GetLeftX();
  float xR = m_container.m_xbox.GetRightX();


  //m_container.m_drivetrain.Drive( m_container.m_xbox.GetLeftX(),  m_container.m_xbox.GetLeftY(),  m_container.m_xbox.GetRightX()  );
  


  //Scalers
  yL *= -xyScaleValue;    //Invert Axis, make positive forward
  xL *=  xyScaleValue;    
  xR *= -rScaleValue;     //Invert Axis, make positive CCW

  //Run depending on Mode:  

  if( m_container.m_drivetrain.GetDriveType() == Drivetrain::ROBOTCENTRIC )
    m_container.m_drivetrain.RobotcentricDrive( yL,  xL,  xR );
  else
    m_container.m_drivetrain.FieldcentricDrive( yL,  xL,  xR );


}


void CmdDriveWithGamepad::End(bool interrupted) 
{
  std::cout<<"End CmdDriveWithGamepad " << interrupted <<std::endl;
}


bool CmdDriveWithGamepad::IsFinished() 
{
  return false;
}
