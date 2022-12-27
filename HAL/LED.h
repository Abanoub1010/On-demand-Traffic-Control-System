#ifndef LED_H_
#define LED_H_

#define ON 1
#define OFF 0

 void Project_Init(void);
 void INT0_ISR (void);
 void TIMER_5sec(void);

void LED_voidPedestrianRedLedON(void);
void LED_voidPedestrianRedLedOFF(void);

void LED_voidPedestrianGreenLedON(void);
void LED_voidPedestrianGreenLedOFF(void);

void LED_voidBothYellowLEDBlink(void);

void LED_voidCarRedLedON(void);
void LED_voidCarRedLedOFF(void);

void LED_voidCarGreenLedON(void);
void LED_voidCarGreenLedOFF(void);



#endif
