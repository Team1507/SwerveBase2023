#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/Timer.h>

class CmdAutoBalance
    : public frc2::CommandHelper<frc2::CommandBase, CmdAutoBalance> {
 public:
  CmdAutoBalance();

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  private:

    frc::Timer m_timer;

    float m_speed;

    int m_offDelayCount;
    int m_speedDelayCount;

    bool m_rev;

    bool m_initial;


};
