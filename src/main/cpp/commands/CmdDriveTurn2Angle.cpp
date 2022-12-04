// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdDriveTurn2Angle.h"
#include "Robot.h"

#include <iostream>
#include <math.h>

CmdDriveTurn2Angle::CmdDriveTurn2Angle(float power, float angle) 
{
  m_power = power;
  m_angle = angle;


  AddRequirements({ &m_container.m_drivetrain });
}


void CmdDriveTurn2Angle::Initialize() 
{

}


void CmdDriveTurn2Angle::Execute() 
{
  float delta_angle = m_angle - m_container.m_drivetrain.GetGyroYaw();


  if( delta_angle > 0)
    m_container.m_drivetrain.RobotcentricDrive(0,0,  -m_power);
  else
    m_container.m_drivetrain.RobotcentricDrive(0,0,   m_power);


}


void CmdDriveTurn2Angle::End(bool interrupted) 
{
  m_container.m_drivetrain.Stop();
}


bool CmdDriveTurn2Angle::IsFinished()
{
  float delta_angle = m_angle - m_container.m_drivetrain.GetGyroYaw();
  if(  abs(delta_angle) < 1.0 )
    return true;

  return false;
}
