// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdButtonY.h"
#include <iostream>


CmdButtonY::CmdButtonY(bool pressed) {
  m_pressed = pressed;
}


void CmdButtonY::Initialize() 
{

  if( m_pressed )
  {
    std::cout<<"Button Y Pressed"<<std::endl;


  }
  else
  {
    std::cout<<"Button Y Released"<<std::endl;


  }
}
