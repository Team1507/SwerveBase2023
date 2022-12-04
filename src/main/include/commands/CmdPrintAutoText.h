#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>

class CmdPrintAutoText
    : public frc2::CommandHelper<frc2::InstantCommand,
                                 CmdPrintAutoText> {
 public:
  CmdPrintAutoText(std::string text);

  void Initialize() override;

 private:
  std::string m_text;

};
