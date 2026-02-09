#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>
#include "config.h"
#include "secrets.h"

LiquidCrystal_I2C lcd(DISPLAY_ADDR, 16, 2);
Adafruit_NeoPixel pixels(1, RGB_LED, NEO_GRB + NEO_KHZ800);


void steuerung_setup()
{
Serial.println("Steuerung initialisieren...");

Wire.begin(); // I2C-Bus initialisieren

// LCD initialisieren
lcd.init();       // initialize the LCD
lcd.clear();      // clear the LCD display
lcd.backlight();  // Make sure backlight is on

// Gyroskop initialisieren
Wire.beginTransmission(GYRO_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
Wire.write(0x6B);  // PWR_MGMT_1 register
Wire.write(0);     // set to zero (wakes up the MPU-6050)
Wire.endTransmission(true);

Serial.println("done.");
}

// Hilfsfunktion zur Umwandlung von int16_t in String mit fester Breite
char* toStr(int16_t value)
{
  char result[7];
  sprintf(result, "%6d", value);
  return result;
}

// Funktionen für die Steuerung des Displays, der RGB-LED, des Gyroskops, der Ultraschallsensoren und der UI-Messung

void DisplayText(int servo, int angle)
{
  lcd.setCursor(2, 0);  //Set cursor to character 2 on line 0
  lcd.print("Hello world!");

  lcd.setCursor(2, 1);  //Move cursor to character 2 on line 1
  lcd.print("LCD Tutorial");
}   

void RGBLED(int r, int g, int b)
{
pixels.clear(); 
pixels.setPixelColor(0, pixels.Color(r, g, b));
pixels.show();
}

void Gyroskop()
{
int16_t accX, accY, accZ, gyrX, gyrY, gyrZ, tVal;

Wire.beginTransmission(GYRO_ADDR);
Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
Wire.requestFrom(GYRO_ADDR, 7*2, true); // request a total of 7*2=14 registers

// "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
accX = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
accY = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
accZ = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
tVal = Wire.read()<<8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
gyrX = Wire.read()<<8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
gyrY = Wire.read()<<8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
gyrZ = Wire.read()<<8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)

Serial.print("aX = ");    
Serial.print(toStr(accX));
Serial.print(" | aY = "); 
Serial.print(toStr(accY));
Serial.print(" | aZ = "); 
Serial.print(toStr(accZ));
Serial.print(" | gX = "); 
Serial.print(toStr(gyrX));
Serial.print(" | gY = "); 
Serial.print(toStr(gyrY));
Serial.print(" | gZ = "); 
Serial.print(toStr(gyrZ));
Serial.println();
}

void Ultraschall(int sensor)
{
long dauer = 0;
long entfernung = 0;    

switch(sensor) {
  case 1: // linker Ultraschallsensor
    pinMode(US_LI_TR, OUTPUT);
    digitalWrite(US_LI_TR, LOW);
    delayMicroseconds(2);
    digitalWrite(US_LI_TR, HIGH);
    delayMicroseconds(10);
    digitalWrite(US_LI_TR, LOW);
    pinMode(US_LI_SE, INPUT);
    dauer = pulseIn(US_LI_SE, HIGH);
    entfernung = dauer * 0.034 / 2;
    Serial.print("Entfernung linker Sensor: ");
    Serial.print(entfernung);
    Serial.println(" cm");
    break;
  case 2: // rechter Ultraschallsensor
    pinMode(US_RE_TR, OUTPUT);
    digitalWrite(US_RE_TR, LOW);
    delayMicroseconds(2);
    digitalWrite(US_RE_TR, HIGH);
    delayMicroseconds(10);
    digitalWrite(US_RE_TR, LOW);
    pinMode(US_RE_SE, INPUT);
    dauer = pulseIn(US_RE_SE, HIGH);
    entfernung = dauer * 0.034 / 2;
    Serial.print("Entfernung rechter Sensor: ");
    Serial.print(entfernung);
    Serial.println(" cm");
    break;
  default:
    Serial.println("Ungültiger Sensor");
  }
}

void UI_Mess()
{
unsigned int rawVal = 0;
rawVal = analogRead(U_MESS);
float spannung = rawVal * (3.3 / 4095.0)*5; // Umrechnung in Spannung (3.3V Referenz, 12-bit ADC, Spannungsteiler 1:5)
Serial.print("Spannung: ");
Serial.print(spannung, 2); // Ausgabe mit 2 Dezimalstellen
Serial.println(" V");   

rawVal = analogRead(I_MESS);
float strom = rawVal * (3.3 / 4095.0); // Umrechnung in Strom (3.3V Referenz, 12-bit ADC)
Serial.print("Strom: ");
Serial.print(strom, 2); // Ausgabe mit 2 Dezimalstellen
Serial.println(" mA");   
}