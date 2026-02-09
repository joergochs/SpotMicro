//***********
// SpotMicroTest - Testprogramm für die Servosteuerung eines Spot Micro Roboters
// Autor: [Dein Name]
// Datum: [Datum]
// Beschreibung: Dieses Programm steuert die Servos eines Spot Micro Roboters an, 
// um dieBeine zu bewegen. Es verwendet die Adafruit PWM Servo Driver Library, 
// um die Servos über  I2C anzusteuern. 
// Die Servowinkel und -pulse können in der config.h Datei angepasst werden.    
//************


#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "kinematic.h"
#include "steuerung.h"
#include "config.h"
#include "secrets.h"

void setup() {

  Serial.begin(9600);
  Serial.println();
  Serial.println("Spot Test");

  kinematic_setup();
  steuerung_setup();
  

  RGBLED(255, 0, 0); // rot
  delay(1000);
  InitLegs();
  DisplayText(0, 0);
  Gyroskop();
  RGBLED(0, 255, 0); // grün
  Ultraschall(1);
  Ultraschall(2);
  UI_Mess();

}

void loop() {

Legs_Hi_Li(1, -20);
delay(1000);
Legs_Hi_Li(0, -20);
delay(1000);
Legs_Hi_Li(1, 20);
delay(1000);  
Legs_Hi_Li(0, 20);
delay(1000); 


}