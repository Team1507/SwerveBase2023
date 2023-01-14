#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/Timer.h>

class CmdAutoBalance
    : public frc2::CommandHelper<frc2::CommandBase, CmdAutoBalance> {
 public:
  CmdAutoBalance(float power, float heading);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  private:

    frc::Timer m_timer;



};
