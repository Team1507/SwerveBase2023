// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/GrpTest1.h"
#include "frc2/command/WaitCommand.h"
#include "commands/CmdPrintAutoText.h"


#include "commands/CmdDriveClearAll.h"
#include "commands/CmdDriveStraight.h"
#include "commands/CmdDriveStraightGyro.h"
#include "commands/CmdDriveTurn2Angle.h"


GrpTest1::GrpTest1() {
  // AddCommands(FooCommand(), BarCommand());

  AddCommands
  (

    CmdPrintAutoText("GrpTest1 Start"),
        

    CmdDriveClearAll(),
    frc2::WaitCommand(0.5_s),
    //---------------------------------------



  //                    power, gyroHeading,  gyroYaw, distance,   ramp,    stop,    timeout)
  CmdDriveStraightGyro(  0.2,      0.0,        0.0,     42,       false,   false,     5.0  ),
  CmdDriveStraightGyro(  0.2,    -90.0,        0.0,     42,       false,   false,     5.0  ),
  CmdDriveStraightGyro(  0.2,    180.0,        0.0,     42,       false,   false,     5.0  ),
  CmdDriveStraightGyro(  0.2,     90.0,        0.0,     42,       false,   true,      5.0  ),

  frc2::WaitCommand(0.5_s),

  //                    power, gyroHeading,  gyroYaw, distance,   ramp,    stop,    timeout)
  CmdDriveStraightGyro(  0.2,      0.0,        0.0,     42,       false,   false,     5.0  ),

  //                     power    angle) 
  CmdDriveTurn2Angle(    0.25,    -90.0 ),
  CmdDriveStraightGyro(  0.2,     -90.0,      -90.0,     42,       false,   false,     5.0  ),

  CmdDriveTurn2Angle(    0.25,   -90.0 ),
  CmdDriveStraightGyro(  0.2,     180.0,     -180.0,     42,       false,   false,     5.0  ),

  CmdDriveTurn2Angle(    0.25,    -90.0 ),
  CmdDriveStraightGyro(  0.2,      90.0,     -270.0,     42,       false,   false,     5.0  ),

  CmdDriveTurn2Angle(    0.25,    -90.0),


  //   // //             power, heading, distance, ramp,   stop,  timeout
  //   CmdDriveStraight(0.2,   0.0,     42,     false,  false,    5.0   ),

  //   CmdDriveStraight(0.2,  -90.0,    42,     false,  false,    5.0   ),

  //   CmdDriveStraight(0.2,  180.0,    42,     false,  false,    5.0   ),

  //   CmdDriveStraight(0.2,   90.0,    42,     false,  true,     5.0   ),


  //   //---------------------------------------

  //  CmdDriveClearAll(),
  // frc2::WaitCommand(0.1_s),


  //   //             power, heading, distance, ramp,   stop,  timeout
  //   CmdDriveStraight(0.2,   0.0,     42,     false,  false,    5.0   ),

  //   //                 power  angle) 
  //   CmdDriveTurn2Angle( 0.25,  -90.0),
  //   CmdDriveStraight(0.2,   0.0,    42,     false,  false,    5.0   ),


  //   CmdDriveTurn2Angle( 0.25,  -90.0),
  //   CmdDriveStraight(0.2,    0.0,    42,     false,  false,    5.0   ),


  //   CmdDriveTurn2Angle( 0.25,  -90.0),
  //   CmdDriveStraight(0.2,    0.0,    42,     false,  true,     5.0   ),

  //   CmdDriveTurn2Angle( 0.25,  -90.0),


    //---------------------------------------
    //All Done
    CmdPrintAutoText("GrpTest1 Finished")

  );
}
