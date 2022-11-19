// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems\Drivetrain.h"


Drivetrain::Drivetrain()
{

    m_motor.ConfigFactoryDefault();

    m_motor.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor,0,10);

    m_motor.SetInverted( false );

    m_motor.SetNeutralMode(NeutralMode::Brake);



}

// This method will be called once per scheduler run
void Drivetrain::Periodic() 
{

}


void Drivetrain::Drive( float power )
{
    m_motor.Set(ControlMode::PercentOutput, power);

}
