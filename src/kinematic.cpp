#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "config.h"
#include "secrets.h"

Adafruit_PWMServoDriver PWM1 = Adafruit_PWMServoDriver(PWM_SERVO_ADDR1);
Adafruit_PWMServoDriver PWM2 = Adafruit_PWMServoDriver(PWM_SERVO_ADDR2);

void kinematic_setup() {
Serial.println("Kinematik initialisieren...");

  PWM1.begin();
  PWM1.setPWMFreq(50);
  PWM2.begin();
  PWM2.setPWMFreq(50);

Serial.println("done.");
}  

void Legs_Hi_Re(int servo, int angle)
{
    int pulse = map(angle, SERVO_ANGLE_MIN, SERVO_ANGLE_MAX, SERVO_PULSE_MIN, SERVO_PULSE_MAX);
    pulse += KORREKTUR_RI_HI_0; // Korrektur für Servo 0 des rechten Hinterbeins
    PWM1.setPWM(servo + 4, 0, pulse); // Servo 0 des rechten Hinterbeins ansteuern  
}

void Legs_Hi_Li(int servo, int angle)
{
    int pulse = map(angle, SERVO_ANGLE_MIN, SERVO_ANGLE_MAX, SERVO_PULSE_MIN, SERVO_PULSE_MAX);
    pulse += KORREKTUR_LI_HI_0; // Korrektur für Servo 0 des linken Hinterbeins
    PWM1.setPWM(servo, 0, pulse); // Servo 0 des linken Hinterbeins ansteuern  
}

void Legs_Vo_Re(int servo, int angle)
{
    int pulse = map(angle, SERVO_ANGLE_MIN, SERVO_ANGLE_MAX, SERVO_PULSE_MIN, SERVO_PULSE_MAX);
    pulse += KORREKTUR_RI_VO_0; // Korrektur für Servo 0 des rechten Vorderbeins
    PWM2.setPWM(servo + 4, 0, pulse); // Servo 0 des rechten Vorderbeins ansteuern  
}

void Legs_Vo_Li(int servo, int angle)
{
    int pulse = map(angle, SERVO_ANGLE_MIN, SERVO_ANGLE_MAX, SERVO_PULSE_MIN, SERVO_PULSE_MAX);
    pulse += KORREKTUR_LI_VO_0; // Korrektur für Servo 0 des linken Vorderbeins
    PWM2.setPWM(servo, 0, pulse); // Servo 0 des linken Vorderbeins ansteuern  
}

void InitLegs()
{
    // Alle Servos auf Mittelstellung setzen
    // Hinterbeine links
    PWM1.setPWM(0, 0, SERVO_PULSE_MID+KORREKTUR_LI_HI_0); 
    PWM1.setPWM(1, 0, SERVO_PULSE_MID+KORREKTUR_LI_HI_1); 
    PWM1.setPWM(2, 0, SERVO_PULSE_MID+KORREKTUR_LI_HI_2); 
    // Hinterbeine rechts
    PWM1.setPWM(4, 0, SERVO_PULSE_MID+KORREKTUR_RI_HI_0); 
    PWM1.setPWM(5, 0, SERVO_PULSE_MID+KORREKTUR_RI_HI_1);       
    PWM1.setPWM(6, 0, SERVO_PULSE_MID+KORREKTUR_RI_HI_2);
    // Vorderbeine links    
    PWM2.setPWM(0, 0, SERVO_PULSE_MID+KORREKTUR_LI_VO_0);
    PWM2.setPWM(1, 0, SERVO_PULSE_MID+KORREKTUR_LI_VO_1);
    PWM2.setPWM(2, 0, SERVO_PULSE_MID+KORREKTUR_LI_VO_2);   
    // Vorderbeine rechts
    PWM2.setPWM(4, 0, SERVO_PULSE_MID+KORREKTUR_RI_VO_0);
    PWM2.setPWM(5, 0, SERVO_PULSE_MID+KORREKTUR_RI_VO_1);
    PWM2.setPWM(6, 0, SERVO_PULSE_MID+KORREKTUR_RI_VO_2); 
}  
