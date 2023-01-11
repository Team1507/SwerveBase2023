
#include "commands/AutoMoveToCone.h"
#include "commands/CmdPrintAutoText.h"
#include "frc2/command/WaitCommand.h"

#include "commands/CmdDriveClearAll.h"
#include "commands/CmdDriveStraight.h"
#include "commands/CmdDriveStraightGyro.h"
#include "commands/CmdDriveTurn2Angle.h"

AutoMoveToCone::AutoMoveToCone() 
{
  AddCommands
  (
      CmdPrintAutoText("AutoMoveToCone Start"),

      CmdDriveClearAll(),
      frc2::WaitCommand(0.5_s),

      CmdDriveStraightGyro(.2, 0, 0, 224.0, false, true, 0.0),
      CmdDriveStraightGyro(.2, 180, 0, 224.0, false, true, 0.0)



  );
}
