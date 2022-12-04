// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/GrpTest1.h"
#include "frc2/command/WaitCommand.h"
#include "commands/CmdPrintAutoText.h"

#include "commands/CmdDriveStaight.h"

GrpTest1::GrpTest1() {
  // AddCommands(FooCommand(), BarCommand());

  AddCommands
  (

    CmdPrintAutoText("GrpTest1 Start"),
        
    frc2::WaitCommand(0.5_s),
    //---------------------------------------

    //             power, heading, distance, ramp,   stop,  timeout
    CmdDriveStaight(0.2,   0.0,     50,     false,  false,    5.0   ),

    CmdDriveStaight(0.2,  -90.0,    50,     false,  false,    5.0   ),

    CmdDriveStaight(0.2,  180.0,    50,     false,  false,    5.0   ),

    CmdDriveStaight(0.2,   90.0,    50,     false,  true,     5.0   ),

    //---------------------------------------
    //All Done
    CmdPrintAutoText("GrpTest1 Finished")

  );
}
