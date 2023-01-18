// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdDriveWithGamepad.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "Robot.h"

#include <iostream>

CmdDriveWithGamepad::CmdDriveWithGamepad()
{
  AddRequirements({ &m_container.m_drivetrain });

  frc::SmartDashboard::PutNumber("Comb the desert Translation Speed Max",0.2);
  frc::SmartDashboard::PutNumber("Comb the desert Rotational Speed Max",0.2);  

  frc::SmartDashboard::PutNumber("Normal Translation Speed Max",0.5);
  frc::SmartDashboard::PutNumber("Normal Rotational Speed Max",0.3);

  frc::SmartDashboard::PutNumber("Ludicrous Translation Speed Max",0.8);
  frc::SmartDashboard::PutNumber("Ludicrous Rotational Speed Max",0.4);
  
}


void CmdDriveWithGamepad::Initialize() 
{
  std::cout<<"Starting CmdDriveWithGamepad"<<std::endl;
}


void CmdDriveWithGamepad::Execute() 
{

  //Limiters

  float xyScaleValue;
  float rScaleValue;
  float combTranslation =  frc::SmartDashboard::GetNumber("Comb the desert Translation Speed Max",0.2);
  float combRotational  =  frc::SmartDashboard::GetNumber("Comb the desert Rotational Speed Max",0.2);  

  float normalTranslation =  frc::SmartDashboard::GetNumber("Normal Translation Speed Max",0.5);
  float normalRotational  =  frc::SmartDashboard::GetNumber("Normal Rotational Speed Max",0.3);

  float ludicrousTranslation =  frc::SmartDashboard::GetNumber("Ludicrous Translation Speed Max",0.8);
  float ludicrousRotational  =  frc::SmartDashboard::GetNumber("Ludicrous Rotational Speed Max",0.4);

  bool ludicrous = m_container.m_xbox.GetLeftTriggerAxis()>0.5;
  bool comb = m_container.m_xbox.GetRightTriggerAxis()>0.5;
  if(comb)
  {
    xyScaleValue = combTranslation;
    rScaleValue  = combRotational;
  }
  else if(ludicrous)
  {
    xyScaleValue = ludicrousTranslation;
    rScaleValue  = ludicrousRotational;
  }
  else
  {
    xyScaleValue = normalTranslation;
    rScaleValue  = normalRotational;
  }
  
  
  //Get Gamepad Inputs
  float yL = m_container.m_xbox.GetLeftY();
  float xL = m_container.m_xbox.GetLeftX();
  float xR = m_container.m_xbox.GetRightX();
  bool BrakeActivated = m_container.m_xbox.GetBackButton();
  bool BrakePressed = m_container.m_xbox.GetBButton();


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


  if(BrakeActivated)
  {
    if(BrakePressed)
      {
          m_container.m_drivetrain.ForcePark();
      }
    }

}


void CmdDriveWithGamepad::End(bool interrupted) 
{
  std::cout<<"End CmdDriveWithGamepad " << interrupted <<std::endl;
}


bool CmdDriveWithGamepad::IsFinished() 
{
  return false;
}
