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
  m_offDelayCount = 45;
  m_speedDelayCount = 20;
  m_rev = false;
  m_initial = false;    
}

void CmdAutoBalance::Execute() 
{
    
    float currTilt = m_container.m_drivetrain.GetGyroRoll();

    if(m_container.m_drivetrain.GetGyroRoll() > 0 + ERROR && !m_rev)
    {
      m_container.m_drivetrain.RobotcentricDrive(m_speed ,0 ,0.0);   
      std::cout<<"Running"<<std::endl;
    }

    if(!m_initial)
    {
      m_speedDelayCount--;
      if(m_speedDelayCount <= 0)
      {
        m_initial = true;
      }
    }

    if(m_initial)
    {
      m_speed = .15;
    }

    //std::cout<<m_container.m_drivetrain.GetGyroRoll()<<std::endl;

      if(prevTilt > 0 && currTilt < 0 )
      {
        m_container.m_drivetrain.RobotcentricDrive(-.25 ,0 ,0.0);
        m_rev = true;
      }

      if(m_rev)
      {
            m_offDelayCount--;
            if(m_offDelayCount <= 0)
            {
                m_container.m_drivetrain.RobotcentricDrive(0 ,0 ,0.0);
                m_container.m_drivetrain.ForcePark();
            }
      }


      
      prevTilt = currTilt;
}

void CmdAutoBalance::End(bool interrupted) {}

bool CmdAutoBalance::IsFinished() 
{


    
    return false;
    
    
}

