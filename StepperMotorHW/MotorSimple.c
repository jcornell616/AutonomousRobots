// MotorSimple.c
// Runs on MSP432
// Provide mid-level functions that initialize ports and
// set motor speeds to move the robot.
// Starter code for Lab 12, uses Systick software delay to create PWM
// Daniel Valvano
// July 7, 2017

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

#include <stdint.h>
#include "msp.h"

// *******Lab 12 solution*******

void Motor_InitSimple(void){
// Initializes the 6 GPIO lines and puts driver to sleep
// Returns right away
// initialize P1.6 and P1.7 and make them outputs
    P1->DIR |= 0xC0;
    P2->DIR |= 0xC0;
    P3->DIR |= 0xC0;
    P3->OUT |= 0xC0;
    P2->SEL0 |= 0xC0;              // P2.6/P2.7 Timer0A functions
    P2->SEL1 &= ~0xC0;             // P2.6/P2.7 Timer0A functions

  // write this as part of Lab 12

}

// PWM on P2.6 using TimerA0 TA0.CCR3
// PWM on P2.7 using TimerA0 TA0.CCR4

void Motor_StopSimple(void){
// Stops both motors, puts driver to sleep
// Returns right away
  P1->OUT &= ~0xC0;
  P2->OUT &= ~0xC0;   // off
  P3->OUT &= ~0xC0;   // low current sleep mode
  TIMER_A0->CCR[0] =  0;
}
void Motor_ForwardSimple(uint16_t duty){
// Drives both motors forward at duty (100 to 9900)
// Runs for time duration (units=10ms), and then stops
// Stop the motors and return if any bumper switch is active
// Returns after time*10ms or if a bumper switch is hit
    P1->OUT &= ~0xC0;               //makes wheels go backwards
    P3->OUT |= 0xC0;
    TIMER_A0->CCR[0] =  6000;
    TIMER_A0->EX0 = 0x0000;
    TIMER_A0->CCTL[3] = 0x0080;    // CCR3 toggle/reset
    TIMER_A0->CCR[3] = duty;       // CCR3 duty cycle is duty1/period
    TIMER_A0->CCTL[4] = 0x0080;    // CCR4 toggle/reset
    TIMER_A0->CCR[4] = duty+(-0.0681*duty+375);       // CCR4 duty cycle is duty1/period
    TIMER_A0->CTL = 0x0230;        // SMCLK=12MHz, divide by 1, up-down mode

  // write this as part of Lab 12
}
void Motor_BackwardSimple(uint16_t duty){
// Drives both motors backward at duty (100 to 9900)
// Runs for time duration (units=10ms), and then stops
// Runs even if any bumper switch is active
// Returns after time*10ms
    P1->OUT |= 0xC0;               //makes wheels go backwards
    P3->OUT |= 0xC0;
    TIMER_A0->CCR[0] =  6000;
    TIMER_A0->EX0 = 0x0000;
    TIMER_A0->CCTL[3] = 0x0080;    // CCR3 toggle/reset
    TIMER_A0->CCR[3] = duty;       // CCR3 duty cycle is duty1/period
    TIMER_A0->CCTL[4] = 0x0080;    // CCR4 toggle/reset
    TIMER_A0->CCR[4] = duty+(-0.0681*duty+375);       // CCR4 duty cycle is duty1/period
    TIMER_A0->CTL = 0x0230;        // SMCLK=12MHz, divide by 1, up-down mode

  // write this as part of Lab 12
}
void Motor_LeftSimple(uint16_t duty){
// Drives just the left motor forward at duty (100 to 9900)
// Right motor is stopped (sleeping)
// Runs for time duration (units=10ms), and then stops
// Stop the motor and return if any bumper switch is active
// Returns after time*10ms or if a bumper switch is hit
    P1->OUT &= ~0x80;               //makes wheels go backwards
    P3->OUT |= 0x80;
    TIMER_A0->CCR[0] =  6000;
    TIMER_A0->EX0 = 0x0000;
    TIMER_A0->CCTL[4] = 0x0080;    // CCR3 toggle/reset
    TIMER_A0->CCR[4] = duty;       // CCR3 duty cycle is duty1/period
    TIMER_A0->CTL = 0x0230;        // SMCLK=12MHz, divide by 1, up-down mode

  // write this as part of Lab 12
}
void Motor_RightSimple(uint16_t duty){
// Drives just the right motor forward at duty (100 to 9900)
// Left motor is stopped (sleeping)
// Runs for time duration (units=10ms), and then stops
// Stop the motor and return if any bumper switch is active
// Returns after time*10ms or if a bumper switch is hit
    P1->OUT &= ~0xC0;               //makes wheels go backwards
    P3->OUT |= 0xC0;
    TIMER_A0->CCR[0] =  6000;
    TIMER_A0->CCTL[3] = 0x0080;    // CCR4 toggle/reset
    TIMER_A0->CCR[3] = duty;       // CCR4 duty cycle is duty1/period
    TIMER_A0->CTL = 0x0230;        // SMCLK=12MHz, divide by 1, up-down mode

  // write this as part of Lab 12
}

void Forward(uint16_t speed, uint16_t time_ms) {
    uint16_t duty = 5500 - 54*speed;
    Motor_ForwardSimple(duty);
    Clock_Delay1ms(time_ms);
    Motor_StopSimple();
}

void Backward(uint16_t speed, uint16_t time_ms) {
    uint16_t duty = 5500 - 54*speed;
    Motor_BackwardSimple(duty);
    Clock_Delay1ms(time_ms);
    Motor_StopSimple();
}

void Right(uint16_t speed, uint16_t time_ms) {
    uint16_t duty = 5500 - 54*speed;
    Motor_LeftSimple(duty);
    Clock_Delay1ms(time_ms);
    Motor_StopSimple();
}

void Left(uint16_t speed, uint16_t time_ms) {
    uint16_t duty = 5500 - 54*speed;
    Motor_RightSimple(duty);
    Clock_Delay1ms(time_ms);
    Motor_StopSimple();
}
