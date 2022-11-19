// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdButtonA.h"
#include <iostream>


CmdButtonA::CmdButtonA(bool pressed) {
  m_pressed = pressed;
}


void CmdButtonA::Initialize() 
{

  if( m_pressed )
  {
    std::cout<<"Button A Pressed"<<std::endl;


  }
  else
  {
    std::cout<<"Button A Released"<<std::endl;


  }
}
