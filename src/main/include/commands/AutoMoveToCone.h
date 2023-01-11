
#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>

class AutoMoveToCone
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 AutoMoveToCone> {
 public:
  AutoMoveToCone();
};
