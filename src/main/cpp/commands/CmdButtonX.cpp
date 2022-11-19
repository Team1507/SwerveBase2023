// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdButtonX.h"
#include <iostream>


CmdButtonX::CmdButtonX(bool pressed) {
  m_pressed = pressed;
}


void CmdButtonX::Initialize() 
{

  if( m_pressed )
  {
    std::cout<<"Button X Pressed"<<std::endl;


  }
  else
  {
    std::cout<<"Button X Released"<<std::endl;


  }
}
