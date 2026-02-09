// include/kinematic.h
#ifndef KINEMATIC_H
#define KINEMATIC_H    

void kinematic_setup();
void InitLegs();
void Legs_Hi_Re(int servo, int angle);
void Legs_Hi_Li(int servo, int angle);
void Legs_Vo_Re(int servo, int angle);
void Legs_Vo_Li(int servo, int angle);

#endif // KINEMATIC_H