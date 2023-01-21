#include "commands/AutoChargeStation.h"

#include "frc2/command/WaitCommand.h"

#include "commands/CmdDriveStraightGyro.h"
#include "commands/CmdDriveTurn2Angle.h"
#include "commands/CmdAutoBalance.h"


AutoChargeStation::AutoChargeStation() 
{
    AddCommands
    (
      CmdDriveStraightGyro(.3, 90, 00, 30, false, false, 0),
      CmdAutoBalance()

    );
}
