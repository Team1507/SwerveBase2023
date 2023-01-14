#include "commands/CmdAutoBalance.h"
#include "Robot.h"
#include "frc2/command/WaitCommand.h"

#define ERROR 2

CmdAutoBalance::CmdAutoBalance(float power, float heading) 
{

}

void CmdAutoBalance::Initialize() 
{

}

void CmdAutoBalance::Execute() 
{
    if(m_container.m_drivetrain.GetGyroRoll() > 0 + ERROR)
    {
      m_container.m_drivetrain.RobotcentricDrive(.2 ,0 ,0.0);   

    }
    else if(m_container.m_drivetrain.GetGyroRoll() < 0 - ERROR )
    {
      m_container.m_drivetrain.RobotcentricDrive(-.2,0,0.0);   
    }

}

void CmdAutoBalance::End(bool interrupted) {}

bool CmdAutoBalance::IsFinished() 
{
    
    return false;
    
    
  
 
}
