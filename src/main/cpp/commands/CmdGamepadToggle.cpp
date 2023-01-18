#include "commands/CmdGamepadToggle.h"

CmdGamepadToggle::CmdGamepadToggle(Drivetrain *drivetrain) 
{
  m_drivetrain = drivetrain;
}

void CmdGamepadToggle::Initialize() 
{
  if(m_drivetrain->IsJoystick())
  {
    m_drivetrain->SetJoystick(false);
  }
  else
  {
    m_drivetrain->SetJoystick(true);
  }
}

void CmdGamepadToggle::Execute() 
{

}

void CmdGamepadToggle::End(bool interrupted) 
{

}

bool CmdGamepadToggle::IsFinished() 
{
  return true;
}
