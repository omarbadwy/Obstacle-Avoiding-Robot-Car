/* 
 *  Eng Omar Badwy
 *  Obstacle Avoiding Robot Car Project
 *  Last Update 15/12/2023
 */
#ifndef _AFMotor_h_
#define _AFMotor_h_

#include <inttypes.h>
#if defined(__AVR__)
    #include <avr/io.h>

    //#define MOTORDEBUG 1

    #define MICROSTEPS 16                       // 8 or 16

    #define MOTOR12_64KHZ _BV(CS20)             // no prescale
    #define MOTOR12_8KHZ _BV(CS21)              // divide by 8
    #define MOTOR12_2KHZ _BV(CS21) | _BV(CS20)  // divide by 32
    #define MOTOR12_1KHZ _BV(CS22)              // divide by 64

    #define MOTOR34_64KHZ _BV(CS00)             // no prescale
    #define MOTOR34_8KHZ _BV(CS01)              // divide by 8
    #define MOTOR34_1KHZ _BV(CS01) | _BV(CS00)  // divide by 64
    
    #define DC_MOTOR_PWM_RATE   MOTOR34_8KHZ    // PWM rate for DC motors
    #define STEPPER1_PWM_RATE   MOTOR12_64KHZ   // PWM rate for stepper 1
    #define STEPPER2_PWM_RATE   MOTOR34_64KHZ   // PWM rate for stepper 2
    
#elif defined(__PIC32MX__)
    //#define MOTORDEBUG 1
    
    // Uncomment the one of following lines if you have put a jumper from 
    // either pin 9 to pin 11 or pin 10 to pin 11 on your Motor Shield.
    // Either will enable PWM for M1
    //#define PIC32_USE_PIN9_FOR_M1_PWM
    //#define PIC32_USE_PIN10_FOR_M1_PWM

    #define MICROSTEPS 16       // 8 or 16

    // For PIC32 Timers, define prescale settings by PWM frequency
    #define MOTOR12_312KHZ  0   // 1:1, actual frequency 312KHz
    #define MOTOR12_156KHZ  1   // 1:2, actual frequency 156KHz
    #define MOTOR12_64KHZ   2   // 1:4, actual frequency 78KHz
    #define MOTOR12_39KHZ   3   // 1:8, acutal frequency 39KHz
    #define MOTOR12_19KHZ   4   // 1:16, actual frequency 19KHz
    #define MOTOR12_8KHZ    5   // 1:32, actual frequency 9.7KHz
    #define MOTOR12_4_8KHZ  6   // 1:64, actual frequency 4.8KHz
    #define MOTOR12_2KHZ    7   // 1:256, actual frequency 1.2KHz
    #define MOTOR12_1KHZ    7   // 1:256, actual frequency 1.2KHz

    #define MOTOR34_312KHZ  0   // 1:1, actual frequency 312KHz
    #define MOTOR34_156KHZ  1   // 1:2, actual frequency 156KHz
    #define MOTOR34_64KHZ   2   // 1:4, actual frequency 78KHz
    #define MOTOR34_39KHZ   3   // 1:8, acutal frequency 39KHz
    #define MOTOR34_19KHZ   4   // 1:16, actual frequency 19KHz
    #define MOTOR34_8KHZ    5   // 1:32, actual frequency 9.7KHz
    #define MOTOR34_4_8KHZ  6   // 1:64, actual frequency 4.8KHz
    #define MOTOR34_2KHZ    7   // 1:256, actual frequency 1.2KHz
    #define MOTOR34_1KHZ    7   // 1:256, actual frequency 1.2KHz
    
    // PWM rate for DC motors.
    #define DC_MOTOR_PWM_RATE   MOTOR34_39KHZ
    // Note: for PIC32, both of these must be set to the same value
    // since there's only one timebase for all 4 PWM outputs
    #define STEPPER1_PWM_RATE   MOTOR12_39KHZ
    #define STEPPER2_PWM_RATE   MOTOR34_39KHZ
    
#endif

// Bit positions in the 74HCT595 shift register output
#define MOTOR1_A 2
#define MOTOR1_B 3
#define MOTOR2_A 1
#define MOTOR2_B 4
#define MOTOR4_A 0
#define MOTOR4_B 6
#define MOTOR3_A 5
#define MOTOR3_B 7

// Constants that the user passes in to the motor calls
#define FORWARD 1
#define BACKWARD 2
#define BRAKE 3
#define RELEASE 4

// Constants that the user passes in to the stepper calls
#define SINGLE 1
#define DOUBLE 2
#define INTERLEAVE 3
#define MICROSTEP 4

/*
#define LATCH 4
#define LATCH_DDR DDRB
#define LATCH_PORT PORTB

#define CLK_PORT PORTD
#define CLK_DDR DDRD
#define CLK 4

#define ENABLE_PORT PORTD
#define ENABLE_DDR DDRD
#define ENABLE 7

#define SER 0
#define SER_DDR DDRB
#define SER_PORT PORTB
*/

// Arduino pin names for interface to 74HCT595 latch
#define MOTORLATCH 12
#define MOTORCLK 4
#define MOTORENABLE 7
#define MOTORDATA 8

class AFMotorController
{
  public:
    AFMotorController(void);
    void enable(void);
    friend class AF_DCMotor;
    void latch_tx(void);
    uint8_t TimerInitalized;
};

class AF_DCMotor
{
 public:
  AF_DCMotor(uint8_t motornum, uint8_t freq = DC_MOTOR_PWM_RATE);
  void run(uint8_t);
  void setSpeed(uint8_t);

 private:
  uint8_t motornum, pwmfreq;
};

class AF_Stepper {
 public:
  AF_Stepper(uint16_t, uint8_t);
  void step(uint16_t steps, uint8_t dir,  uint8_t style = SINGLE);
  void setSpeed(uint16_t);
  uint8_t onestep(uint8_t dir, uint8_t style);
  void release(void);
  uint16_t revsteps; // # steps per revolution
  uint8_t steppernum;
  uint32_t usperstep, steppingcounter;
 private:
  uint8_t currentstep;

};

uint8_t getlatchstate(void);

#endif
