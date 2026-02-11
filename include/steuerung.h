// include/steuerung.h
#ifndef STEUERUNG_H
#define STEUERUNG_H          

void steuerung_setup();
void DisplayText(int servo, int angle);
void RGBLED(int r, int g, int b);
void Gyroskop();
void Ultraschall(int sensor);
void UI_Mess();
void scanI2C(long frequency);

#endif // STEUERUNG_H