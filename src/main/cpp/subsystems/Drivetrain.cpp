// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems\Drivetrain.h"


Drivetrain::Drivetrain()
{


}

// This method will be called once per scheduler run
void Drivetrain::Periodic() 
{

}


void Drivetrain::Drive( float lx, float ly, float rx )
{
    m_frontRight.DriveMotor( ly );

    m_frontRight.AngleMotor( rx );


}
