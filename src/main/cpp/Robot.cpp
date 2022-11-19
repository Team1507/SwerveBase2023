
#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>
#include <frc/DriverStation.h>


//THIS IS A GLOBAL VARIABLE
RobotContainer m_container;

void Robot::RobotInit() 
{
  //*************************** INIT ******************************
  std::cout<<"RobotInit"<<std::endl;
  std::cout<<"FRC2022: SwerveDev"<<std::endl;
  std::cout<<"Version: " << __DATE__ <<"  "<<__TIME__<<std::endl<<std::endl; 


}


void Robot::RobotPeriodic() 
{
  frc2::CommandScheduler::GetInstance().Run();
  WriteToSmartDashboard();
}


void Robot::DisabledInit() 
{
  std::cout<<"Disabled Init"<<std::endl;
}

void Robot::DisabledPeriodic() {}


void Robot::AutonomousInit() 
{
  std::cout<<" **** Auto Init ******"<<std::endl;
  m_autonomousCommand = m_container.GetAutonomousCommand();

  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Schedule();
  }
}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() 
{
  std::cout<<"Teleop Init"<<std::endl;

  //Clean up any auto leftovers
  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Cancel();
    m_autonomousCommand = nullptr;
  }
}


void Robot::TeleopPeriodic() {}

void Robot::WriteToSmartDashboard(void)
{

  //XBox Controllers
  frc::SmartDashboard::PutNumber("Xbox Left-Y",   (double)m_container.m_xbox.GetLeftY() ); 
  frc::SmartDashboard::PutNumber("Xbox Left-X",   (double)m_container.m_xbox.GetLeftX() ); 
  frc::SmartDashboard::PutNumber("Xbox Right-X",  (double)m_container.m_xbox.GetRightX() ); 

  //Swerve Drive
  frc::SmartDashboard::PutNumber("FR-Pos",   m_container.m_drivetrain.m_frontRight.GetPivotEncoderPosition() ); 
  frc::SmartDashboard::PutNumber("FR-ABS",   m_container.m_drivetrain.m_frontRight.GetPivotEncoderAbsoutePosition() ); 


}




void Robot::TestPeriodic() {}
void Robot::SimulationInit() {}
void Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
