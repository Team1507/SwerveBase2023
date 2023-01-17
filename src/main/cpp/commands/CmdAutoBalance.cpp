#include "commands/CmdAutoBalance.h"
#include "Robot.h"
#include "frc2/command/WaitCommand.h"
#include <iostream>
#define ERROR 2

float prevTilt = 0;
CmdAutoBalance::CmdAutoBalance(float power, float heading) 
{
  AddRequirements({ &m_container.m_drivetrain });
  
}

void CmdAutoBalance::Initialize() 
{
  prevTilt = 0;
  m_speed = .2;
  m_timer.Reset();
}

void CmdAutoBalance::Execute() 
{
    
    float currTilt = m_container.m_drivetrain.GetGyroRoll();
    if(m_container.m_drivetrain.GetGyroRoll() > 0 + ERROR)
    {
      m_container.m_drivetrain.RobotcentricDrive(m_speed ,0 ,0.0);   
      std::cout<<"Running f"<<std::endl;
    }
    else if(m_container.m_drivetrain.GetGyroRoll() < 0 - ERROR )
    {
      m_container.m_drivetrain.RobotcentricDrive(-m_speed,0,0.0);   
      std::cout<<"Running b"<<std::endl;
    }

    std::cout<<m_speed<<std::endl;
      if(prevTilt < 0 && currTilt > 0)
      {   
        if(m_speed > .1)
        {
          m_speed = m_speed - .05;
        }
      }
      else if(prevTilt > 0 && currTilt < 0)
      {
        if(m_speed > .1)
        {
          m_speed = m_speed - .05;
        }
      }

      
      prevTilt = currTilt;
}

void CmdAutoBalance::End(bool interrupted) {}

bool CmdAutoBalance::IsFinished() 
{
    if(m_speed < .15)
    {

    
      if((m_container.m_drivetrain.GetGyroRoll() < ERROR) && (m_container.m_drivetrain.GetGyroRoll()  > -ERROR))
      {
          m_container.m_drivetrain.RobotcentricDrive(0,0,0.0);  
          m_timer.Start();
          if(m_timer.HasElapsed( units::second_t(1.5)))
          {
              m_timer.Stop();
              m_timer.Reset();
              std::cout<<"Timer done"<<std::endl;
          
            if((m_container.m_drivetrain.GetGyroRoll() < ERROR) && (m_container.m_drivetrain.GetGyroRoll()  > -ERROR)) 
              {
                m_container.m_drivetrain.RobotcentricDrive(0,0,0.0); 
                std::cout<<"Finished"<<std::endl;
                return true;  
                
              }
            else
              {
                return false;
              }
          }
      }
      else
      {
        return false;
      }
    
    
    }
    else
    {
      return false;
    }
}
