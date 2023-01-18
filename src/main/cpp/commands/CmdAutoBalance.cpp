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
  m_offDelayCount = 25;
  m_rev = false;
}

void CmdAutoBalance::Execute() 
{
    
    float currTilt = m_container.m_drivetrain.GetGyroRoll();
    if(m_container.m_drivetrain.GetGyroRoll() > 0 + ERROR && !m_rev)
    {
      m_container.m_drivetrain.RobotcentricDrive(m_speed ,0 ,0.0);   
      std::cout<<"Running f"<<std::endl;
    }



      if(prevTilt > 0 && currTilt < 0 )
      {
        m_container.m_drivetrain.RobotcentricDrive(-.5 ,0 ,0.0);
        m_rev = true;
      }

      if(m_rev)
      {
            m_offDelayCount--;
            if(m_offDelayCount <= 0)
            {
                m_container.m_drivetrain.RobotcentricDrive(0 ,0 ,0.0);
            }
      }


      
      prevTilt = currTilt;
}

void CmdAutoBalance::End(bool interrupted) {}

bool CmdAutoBalance::IsFinished() 
{


    
    return false;
    
    
}

