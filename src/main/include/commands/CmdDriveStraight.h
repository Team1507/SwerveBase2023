#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/Timer.h>

class CmdDriveStraight
    : public frc2::CommandHelper<frc2::CommandBase, CmdDriveStraight> {
 public:
  CmdDriveStraight(float power, float heading, float distance, bool ramp, bool stop, float timeout);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:

  frc::Timer m_timer;
  
  float m_power;
  float m_heading;
  float m_distance;
  bool  m_stop;
  bool  m_ramp;
  float m_timeout;   


  float m_initial_x;
  float m_initial_y;


};
