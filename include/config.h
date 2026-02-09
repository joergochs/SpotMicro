// include/config.h
#ifndef CONFIG_H
#define CONFIG_H    

// Pin definitions
// Ultraschallsensoren TR: senden, SE: empfangen    
#define US_LI_TR 4  
#define US_LI_SE 5
#define US_RE_TR 6
#define US_RE_SE 7
// LEDs 
#define LED_BI 38
#define RGB_LED 48
// Gyrosensor
#define GYRO_SDA 08
#define GYRO_SCL 09
#define GYRO_INT 17
// Servos   
#define SERVO_SDA 08
#define SERVO_SCL 09
// Display
#define DISPLAY_SDA 08
#define DISPLAY_SCL 09 
// Spannungs- und Stromssensoren
#define U_MESS 01    
#define I_MESS 02

// I2C Adressen
// Gyroskop
#define GYRO_ADDR 0x68
// Display  
#define DISPLAY_ADDR 0x27   
// Servos PWM Adressen
#define PWM_SERVO_ADDR1   0x40
#define PWM_SERVO_ADDR2   0x41

// Servowinkelgrenzen
#define SERVO_ANGLE_MIN -90
#define SERVO_ANGLE_MAX 90  
#define SERVO_PULSE_MIN 140
#define SERVO_PULSE_MAX 500
#define SERVO_PULSE_MID 320


// Servokorrekturfaktoren (-50 ... +50)
#define KORREKTUR_LI_VO_0 0
#define KORREKTUR_LI_VO_1 0
#define KORREKTUR_LI_VO_2 0
#define KORREKTUR_LI_HI_0 0
#define KORREKTUR_LI_HI_1 0
#define KORREKTUR_LI_HI_2 0
#define KORREKTUR_RI_VO_0 0
#define KORREKTUR_RI_VO_1 0
#define KORREKTUR_RI_VO_2 0
#define KORREKTUR_RI_HI_0 0
#define KORREKTUR_RI_HI_1 0
#define KORREKTUR_RI_HI_2 0 

// Kinematik-Werte 
#define L0 100.0
#define L1 50.0
#define L2 100.0


#endif // CONFIG_H