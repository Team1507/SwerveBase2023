#include "commands/AutoOverAndBack.h"

#include "frc2/command/WaitCommand.h"

#include "commands/CmdDriveStraightGyro.h"
#include "commands/CmdDriveTurn2Angle.h"
#include "commands/CmdAutoBalance.h"

AutoOverAndBack::AutoOverAndBack() 
{
    AddCommands
    (
      CmdDriveStraightGyro(.3, 90, 00, 160, false, false, 0),
      CmdDriveTurn2Angle(.3, -90),
      CmdDriveStraightGyro(.3, 90, -90, 44, false, true, 0.0 ),
      frc2::WaitCommand(1.0_s),
      CmdDriveStraightGyro(.3, -90, -90, 85, false, false, 0),
      CmdAutoBalance()
      
      
    );
}
