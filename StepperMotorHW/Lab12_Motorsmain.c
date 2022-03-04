// Lab12_Motorsmain.c
// Runs on MSP432
// Solution to Motors lab
// Daniel and Jonathan Valvano
// September 4, 2017

/* This example accompanies the books
   "Embedded Systems: Introduction to the MSP432 Microcontroller",
       ISBN: 978-1512185676, Jonathan Valvano, copyright (c) 2017
   "Embedded Systems: Real-Time Interfacing to the MSP432 Microcontroller",
       ISBN: 978-1514676585, Jonathan Valvano, copyright (c) 2017
   "Embedded Systems: Real-Time Operating Systems for ARM Cortex-M Microcontrollers",
       ISBN: 978-1466468863, , Jonathan Valvano, copyright (c) 2017
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/

Simplified BSD License (FreeBSD License)
Copyright (c) 2017, Jonathan Valvano, All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are
those of the authors and should not be interpreted as representing official
policies, either expressed or implied, of the FreeBSD Project.
*/


// Sever VCCMD=VREG jumper on Motor Driver and Power Distribution Board and connect VCCMD to 3.3V.
//   This makes P3.7 and P3.6 low power disables for motor drivers.  0 to sleep/stop.
// Sever nSLPL=nSLPR jumper.
//   This separates P3.7 and P3.6 allowing for independent control
// Left motor direction connected to P1.7 (J2.14)
// Left motor PWM connected to P2.7/TA0CCP4 (J4.40)
// Left motor enable connected to P3.7 (J4.31)
// Right motor direction connected to P1.6 (J2.15)
// Right motor PWM connected to P2.6/TA0CCP3 (J4.39)
// Right motor enable connected to P3.6 (J2.11)

#include "msp.h"
#include "..\inc\bump.h"
#include "..\inc\Clock.h"
#include "..\inc\SysTick.h"
#include "..\inc\LaunchPad.h"
#include "..\inc\MotorSimple.h"

#define SPEED1 0
#define SPEED2 50
#define SPEED3 100
#define INPERS 29

/*** Function Declarations ***/
void Pause(void);
void StraightLine1s_Speed1(void);
void StraightLine1s_Speed2(void);
void StraightLine1s_Speed3(void);
void StraightLine3s_Speed1(void);
void StraightLine3s_Speed2(void);
void StraightLine3s_Speed3(void);
void StraightLine5s_Speed1(void);
void StraightLine5s_Speed2(void);
void StraightLine5s_Speed3(void);
void PivotLeft45(void);
void PivotLeft90(void);
void PivotLeft180(void);
void PivotLeft270(void);
void PivotRight45(void);
void PivotRight90(void);
void PivotRight180(void);
void PivotRight270(void);
void PivotRight30(void);

void Question1(void);
void Question2(void);
void Question3(void);
void Question4(void);
void Question5(void);
void Question6(void);

/*** Main Functions ***/
int main(void) {

    // system initialization
    Clock_Init48MHz();
    LaunchPad_Init();
    Motor_InitSimple();

    // event loop
    while(1) {
        // wait for user input
        Pause();
        // start path
        Question4();
  }
}

/*** Function Definitions ***/

// Wait for user input
void Pause(void) {
  while(LaunchPad_Input() == 0);    // wait for touch
  while(LaunchPad_Input());         // wait for release
  Clock_Delay1ms(1000);             // 1s delay to allow user to take hand off
}

void StraightLine1s_Speed1(void) {
    Forward(SPEED1, 1000);
}
void StraightLine1s_Speed2(void) {
    Forward(SPEED2, 1000);
}
void StraightLine1s_Speed3(void) {
    Forward(SPEED3, 1000);
}
void StraightLine3s_Speed1(void) {
    Forward(SPEED1, 3000);
}
void StraightLine3s_Speed2(void) {
    Forward(SPEED2, 3000);
}
void StraightLine3s_Speed3(void) {
    Forward(SPEED3, 3000);
}
void StraightLine5s_Speed1(void) {
    Forward(SPEED1, 5000);
}
void StraightLine5s_Speed2(void) {
    Forward(SPEED2, 5000);
}
void StraightLine5s_Speed3(void) {
    Forward(SPEED3, 5000);
}

void PivotLeft45(void) {
    Left(75, 70);
}
void PivotLeft90(void) {
    Left(75, 130);
}
void PivotLeft180(void) {
    Left(75, 300);
}
void PivotLeft270(void) {
    Left(75, 575);
}
void PivotRight45(void) {
    Right(75, 60);
}
void PivotRight90(void) {
    Right(75, 120);
}
void PivotRight180(void) {
    Right(75, 290);
}
void PivotRight270(void) {
    Right(75, 550);
}
void PivotRight30(void) {
    Right(75, 40);
}

void Question1(void) {
    uint16_t i;
    for (i = 0; i < 5; i++) {
        StraightLine1s_Speed1();
        Pause();
        StraightLine1s_Speed2();
        Pause();
        StraightLine1s_Speed3();
        Pause();
        StraightLine3s_Speed1();
        Pause();
        StraightLine3s_Speed2();
        Pause();
        StraightLine3s_Speed3();
        Pause();
        StraightLine5s_Speed1();
        Pause();
        StraightLine5s_Speed2();
        Pause();
        StraightLine5s_Speed3();
        Pause();
    }
}

void Question2(void) {
    Forward(75, 12*INPERS);
    Pause();
    Forward(75, 36*INPERS);
    Pause();
    Forward(75, 60*INPERS);
}

void Question3(void) {
    PivotRight45();
    Pause();
    PivotRight90();
    Pause();
    PivotRight180();
    Pause();
    PivotRight270();
}

void Question4(void) {
    uint16_t delay = 750;
    Forward(75, 36*INPERS);
    Clock_Delay1ms(delay);
    PivotLeft90();
    Forward(75, 18*INPERS);
    Clock_Delay1ms(delay);
    PivotRight90();
    Clock_Delay1ms(delay);
    Forward(75, 60*INPERS);
    Clock_Delay1ms(delay);
    PivotRight90();
    Clock_Delay1ms(delay);
    Forward(75, 48*INPERS);
    Clock_Delay1ms(delay);
    PivotRight45();
    Clock_Delay1ms(delay);
    Forward(75, 48*INPERS);
    Clock_Delay1ms(delay);
    PivotRight45();
    Clock_Delay1ms(delay);
    Forward(75, 30*INPERS);
    Clock_Delay1ms(delay);
    // ???
    PivotRight90();
    Clock_Delay1ms(delay);
    Forward(75, 18*INPERS);
    Clock_Delay1ms(delay);
    PivotLeft90();
    Clock_Delay1ms(delay);
    Forward(75, 20*INPERS);
    Clock_Delay1ms(delay);
    PivotRight30();
    Clock_Delay1ms(delay);
    Forward(75, 24*INPERS);
}

void Question5(void) {

}

void Question6(void) {
     while(1){
    Pause(); // start on SW1 or SW2
    Motor_LeftSimple(4500);     // right turn 2 sec
    Motor_RightSimple(4000);     // right turn 2 sec
    Clock_Delay1ms(10600);
    Motor_LeftSimple(4000);     // right turn 2 sec
    Motor_RightSimple(4250);     // right turn 2 sec
    Clock_Delay1ms(10700);
    Motor_LeftSimple(4500);     // right turn 2 sec
    Motor_RightSimple(4000);     // right turn 2 sec
    Clock_Delay1ms(10600);
    Motor_LeftSimple(4000);     // right turn 2 sec
    Motor_RightSimple(4250);     // right turn 2 sec
    Clock_Delay1ms(10700);
    Motor_LeftSimple(4500);     // right turn 2 sec
    Motor_RightSimple(4000);     // right turn 2 sec
    Clock_Delay1ms(10600);
    Motor_LeftSimple(4000);     // right turn 2 sec
    Motor_RightSimple(4250);     // right turn 2 sec
    Clock_Delay1ms(10700);
    Motor_LeftSimple(4500);     // right turn 2 sec
    Motor_RightSimple(4000);     // right turn 2 sec
    Clock_Delay1ms(10600);
    Motor_LeftSimple(4000);     // right turn 2 sec
    Motor_RightSimple(4250);     // right turn 2 sec
    Clock_Delay1ms(10700);
    Motor_StopSimple();
  }
}
