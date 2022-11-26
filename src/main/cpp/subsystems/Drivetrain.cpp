// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <math.h>
#include <iostream>

#include "subsystems\Drivetrain.h"
#include "frc/smartdashboard/SmartDashboard.h"


//         ^
//     FR  |  FR
//         .
//     RL     RR
//

//moduleListIndex
#define FR_INDEX 0
#define FL_INDEX 1
#define RL_INDEX 2
#define RR_INDEX 3


#define DRIVEBASE_WIDTH     32.0  // size in X-axis in inches
#define DRIVEBASE_HEIGHT    32.0  // size in Y-axis in inches

#define W_DIV_2  (DRIVEBASE_WIDTH/2.0)
#define H_DIV_2  (DRIVEBASE_HEIGHT/2.0)

#define C2M_D   sqrtf(W_DIV_2*W_DIV_2 + H_DIV_2*H_DIV_2 )       //Center-to-module distance 

#define MINIMUM_NEEDED_POWER 0.1        //minimum power needed to move



#define DEG2RAD(deg) ( deg*M_PI/180.0)
#define RAD2DEG(rad) ( rad*180.0/M_PI)

//*********************
//  Vector Init Stuff
//

//Storage for vector data
typedef struct
{
    float x;    //x component of vector 
    float y;    //y component of vector
} vector_t;

//Robot Unit Vectors for each module to calculate rotation effect on motion vector   
//Normal vectors are vectors of length 1, perpendicular to the line between center or robot to each module, in direction of positive rotation (CCW)
// Therefore, the values are simply a ratio of height/width and center-to-module distance
const vector_t moduleRotationUnitVector[] = {

    { -W_DIV_2/C2M_D,  W_DIV_2/C2M_D },      //[0] Front Right  -X  +Y
    { -W_DIV_2/C2M_D, -W_DIV_2/C2M_D },      //[1] Front Left   -X  -Y
    {  W_DIV_2/C2M_D, -W_DIV_2/C2M_D },      //[2] Rear  Left   +X  -Y
    {  W_DIV_2/C2M_D,  W_DIV_2/C2M_D },      //[3] Rear  Right  +X  +Y
};




Drivetrain::Drivetrain()
{

    //Testing
    frc::SmartDashboard::PutNumber("SetGyroAngle", 0.0);


    //Setup module list
    m_moduleList[FR_INDEX] = &m_frontRight;    
    m_moduleList[FL_INDEX] = &m_frontLeft;    
    m_moduleList[RL_INDEX] = &m_rearLeft;    
    m_moduleList[RR_INDEX] = &m_rearRight;    

}

// This method will be called once per scheduler run
void Drivetrain::Periodic() 
{




}




//Robot Centric Drive
//  currently using raw inputs, no velocity or rotaional speed calculations
//  fwdrev:     + = forward    - = Reverse
//  rightleft:  + = right      - = left
//  rotate:     + = CCW        - = CW
void Drivetrain::RobotcentricDrive( float fwdrev, float rightleft, float rotate )
{

    vector_t robotVector = {rightleft, fwdrev };       

    vector_t moduleVectors[NUM_SWERVE_MODULES];     //Working vector calculations

    float    modulePower[NUM_SWERVE_MODULES];       //Module drive power
    float    moduleAngle[NUM_SWERVE_MODULES];       //Module drive angle

    float    maxPower = 0.0;

    //Create drive vectors and drive angles for each module
    for(int i=0; i<NUM_SWERVE_MODULES;i++)
    {

        //module_X_vector = robot_X_vector + rotate scalar * rotational normal vector
        moduleVectors[i].x = robotVector.x  +  ( rotate * moduleRotationUnitVector[i].x );

        //module_Y_vector = robot_Y_vector + rotate scalar * rotational normal vector
        moduleVectors[i].y = robotVector.y  +  ( rotate * moduleRotationUnitVector[i].y );


        //Calculate Power from X and Y vectors.  We can use pythagorean theorem here
        modulePower[i] = sqrtf( moduleVectors[i].x*moduleVectors[i].x +  moduleVectors[i].y*moduleVectors[i].y  );

        //Check if maxPower
        if( modulePower[i] > maxPower)
            maxPower = modulePower[i];

        //Steer angle is the arcTan of the module vector
        // Tan(Theta) = y/x,   Theta = arctan(y/x)
        //We use function arctan2 to account for the discontinuity with -x values
        //Note usage:  arctan2 (y,x), answer in radians [-pi to pi], converted to degrees [-180 to 180]
        moduleAngle[i] = RAD2DEG(  atan2f(moduleVectors[i].y,  moduleVectors[i].x)  );

    }

    //Check for normalization if maxPower > 1.0
    if( maxPower > 1.0 )
    {
        for(int i=0; i<NUM_SWERVE_MODULES; i++)
            modulePower[i] = modulePower[i] / maxPower;
    }

    //Check if max power is high enough to do anything.
    //Need even a minimum amount of power to turn the wheels
    if( maxPower < MINIMUM_NEEDED_POWER )
    {
        //Not high enough.  Tell everytning to stop!
        for(int i=0; i<NUM_SWERVE_MODULES; i++)
        {
            m_moduleList[i]->SetDriveMotor(0.0);
            m_moduleList[i]->SetSteerMotor(0.0);       
        }
        return;
    }


    //Update modues with new calculations
    for(int i=0; i<NUM_SWERVE_MODULES; i++)
    {
//      m_moduleList[i]->SetSteerAngle( moduleAngle[i] );       //Old style angle calculation
        m_moduleList[i]->SetSteerAngleV2( moduleAngle[i] );     //New style with motor inversion
        m_moduleList[i]->SetDriveMotor( modulePower[i] );       //Set Angle first in case drive motor inversion is active.

    }

}


//Field Centric Drive
// Rotate inputs around gyro angle
void Drivetrain::FieldcentricDrive( float fwdrev, float rightleft, float rotate )
{
    float gyro_angle = DEG2RAD( frc::SmartDashboard::GetNumber("SetGyroAngle", 0.0)  );         //Simulate for now

    float new_rightleft =  ( rightleft * cosf(gyro_angle) ) - ( fwdrev * sinf(gyro_angle) );    //New X-Axis after rotation
    float new_fwdrev    =  ( rightleft * sinf(gyro_angle) ) - ( fwdrev * cosf(gyro_angle) );    //New Y-Axis after rotation

    RobotcentricDrive( new_fwdrev, new_rightleft, rotate);
}

void Drivetrain::HardResetDriveEncoders(void)
{
    //** WARNING ***
    //It takes several cycles to perform a hard reset on the Falcons
    //Do not use encoders immediately after a reset
    std::cout<< "Hard Encoder Reset" << std::endl;
    for(int i=0;i<NUM_SWERVE_MODULES;i++)
        m_moduleList[i]->HardResetDriveEncoder();
}
void Drivetrain::ResetDriveEncoders(void)
{
    std::cout<< "Soft Encoder Reset" << std::endl;
    for(int i=0;i<NUM_SWERVE_MODULES;i++)
        m_moduleList[i]->SoftResetDriveEncoder();
}
void Drivetrain::ResetSteerEncoders(void)
{
    for(int i=0;i<NUM_SWERVE_MODULES;i++)
        m_moduleList[i]->ResetSteerEncoders();
}





//Absolute Encoder calibration
//All wheels must manually be set to 0 degrees before calling
//Due to CAN bus lag, these are split into 2 commands
void Drivetrain::CalibrateSteerEncoderAbsoutePositionStart(void)
{
    for(int i=0;i<NUM_SWERVE_MODULES;i++)
        m_moduleList[i]->CalibrateSteerEncoderAbsoutePositionStart();
}
void Drivetrain::CalibrateSteerEncoderAbsoutePositionOffset(void)
{
    for(int i=0;i<NUM_SWERVE_MODULES;i++)
        m_moduleList[i]->CalibrateSteerEncoderAbsoutePositionOffset();
}

