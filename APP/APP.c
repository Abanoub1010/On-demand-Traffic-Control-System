/*
 * main.c
 *
 *  Created on: Nov 23, 2022
 *      Author: Abanoub
 */
/*
 * main.c
 *
 *  Created on: Sep 26, 2022
 *      Author: Abanoub
 */
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../HAL/LED.h"
#include "APP.h"

extern u8 Global_YellowCheck;

void APP_START(void)
{
	Project_Init();

while(1)
{
	//At Normal Mode
	
	LED_voidCarGreenLedON(); //Green LED for Cars ON
	LED_voidPedestrianRedLedON();//Red LED for Pedestrians ON
	TIMER_5sec();
	LED_voidCarGreenLedOFF(); //Green LED for Cars OFF
	LED_voidPedestrianRedLedOFF(); //Red LED for Pedestrians OFF


	LED_voidBothYellowLEDBlink(); //Both yellow Leds blink for five seconds


	LED_voidCarRedLedON(); //Red LED for Cars ON
	LED_voidPedestrianGreenLedON(); //Green LED for Pedestrians ON
	TIMER_5sec();
	LED_voidCarRedLedOFF(); //Red LED for Cars OFF
	LED_voidPedestrianGreenLedOFF(); //Green LED for Pedestrians OFF

	Global_YellowCheck=ON;
	LED_voidBothYellowLEDBlink(); //Both yellow Leds blink for five seconds
	Global_YellowCheck=OFF;
}

}






