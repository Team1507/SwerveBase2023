// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdButtonB.h"
#include <iostream>


CmdButtonB::CmdButtonB(bool pressed) {
  m_pressed = pressed;
}


void CmdButtonB::Initialize() 
{

  if( m_pressed )
  {
    std::cout<<"Button B Pressed"<<std::endl;


  }
  else
  {
    std::cout<<"Button B Released"<<std::endl;


  }
}
