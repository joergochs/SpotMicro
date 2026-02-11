// include/steuerung.h
#ifndef STEUERUNG_H
#define STEUERUNG_H          

void steuerung_setup();
void DisplayText(const String &line1, const String &line2);
void RGBLED(int r, int g, int b);
void Gyroskop();
void Ultraschall(int sensor);
void UI_Mess();
void scanI2C(long frequency);

#endif // STEUERUNG_H