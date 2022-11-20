// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems\Drivetrain.h"
#include "frc/smartdashboard/SmartDashboard.h"


Drivetrain::Drivetrain()
{

    //Testing - Set Swerve Pivot Angle
    frc::SmartDashboard::PutNumber("SetPivotAngle", 0.0);

}

// This method will be called once per scheduler run
void Drivetrain::Periodic() 
{
    m_frontRight.SetPivotAngle( frc::SmartDashboard::GetNumber("SetPivotAngle", 0.0) );
}


void Drivetrain::Drive( float lx, float ly, float rx )
{
    //m_frontRight.SetDriveMotor( ly );

    //m_frontRight.SetPivotMotor( rx * 0.15 );


}


void Drivetrain::HardResetDriveEncoders(void)
{

}
void Drivetrain::ResetDriveEncoders(void)
{

}
void Drivetrain::ResetPivotEncoders(void)
{
    m_frontRight.ResetPivotEncoders();
}

