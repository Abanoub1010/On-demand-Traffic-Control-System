#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/GIE/GIE_interface.h"
#include "../MCAL/TIMER/TIMER_interface.h"
#include "../MCAL/EXTI/EXTI_interface.h"
#include "LED.h"


u8 Global_YellowCheck;

void Project_Init(void)
{
	/*INT0 Enable*/
	EXTI_u8Int0SetSenseControl(FALLING_EDGE);
	EXTI_u8Int0Enable();
	EXTI_u8Int0SetCallBack(&INT0_ISR);

	/*TIMER0 Enable*/
	TIMER0_voidInit();
	GIE_voidEnable();

	//internal pull up
	DIO_u8SetPinDirection(DIO_u8PORTD,DIO_u8PIN2,DIO_u8PIN_INPUT);
	DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN2,DIO_u8PIN_HIGH);

	//Setting direction of the pedestrians' traffic LEDs
	DIO_u8SetPinDirection(DIO_u8PORTB,DIO_u8PIN2,DIO_u8PIN_OUTPUT); //Red LED for Pedestrians
	DIO_u8SetPinDirection(DIO_u8PORTB,DIO_u8PIN3,DIO_u8PIN_OUTPUT); //Yellow LED for Pedestrians
	DIO_u8SetPinDirection(DIO_u8PORTB,DIO_u8PIN4,DIO_u8PIN_OUTPUT); //Green LED for Pedestrians

	//Setting direction of the cars' traffic LEDs
	DIO_u8SetPinDirection(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_OUTPUT); //Red LED for Cars
	DIO_u8SetPinDirection(DIO_u8PORTC,DIO_u8PIN3,DIO_u8PIN_OUTPUT); //Yellow LED for Cars
	DIO_u8SetPinDirection(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_OUTPUT); //Green LED for Cars
}

void INT0_ISR (void)
{
	u8 CheckGreenLed=0;
	DIO_u8GetPinValue(DIO_u8PORTC,DIO_u8PIN4,&CheckGreenLed);
if (CheckGreenLed == ON) //Green LED of Cars is ON
{
	LED_voidCarGreenLedOFF();//Green LED for Cars OFF
	LED_voidPedestrianRedLedOFF(); //Red LED for Pedestrians OFF

	LED_voidPedestrianRedLedON();//Red LED for Pedestrians ON


	//Blinking Yellow LED for Pedestrians and Cars for 5 Seconds
	LED_voidBothYellowLEDBlink();
	LED_voidCarGreenLedOFF();//Green LED for Cars OFF
	LED_voidPedestrianRedLedOFF(); //Red LED for Pedestrians OFF

	LED_voidCarRedLedON();//Red LED for Cars ON
	LED_voidPedestrianGreenLedON(); //Green LED for Pedestrians ON
	TIMER0_voidDelayBusyWait(5000);


	LED_voidCarRedLedOFF(); //Red LED for Cars OFF
	LED_voidBothYellowLEDBlink();

	LED_voidPedestrianGreenLedOFF(); //Green LED for Pedestrians OFF
	LED_voidPedestrianRedLedON();//Red LED for Pedestrians ON
	LED_voidCarGreenLedON(); //Green LED for Cars ON


	}

	else if (Global_YellowCheck == ON)
	{
		LED_voidCarGreenLedOFF();//Green LED for Cars OFF
			LED_voidPedestrianRedLedOFF(); //Red LED for Pedestrians OFF

			LED_voidPedestrianRedLedON();//Red LED for Pedestrians ON


			//Blinking Yellow LED for Pedestrians and Cars for 5 Seconds
			LED_voidBothYellowLEDBlink();
			LED_voidCarGreenLedOFF();//Green LED for Cars OFF
			LED_voidPedestrianRedLedOFF(); //Red LED for Pedestrians OFF

			LED_voidCarRedLedON();//Red LED for Cars ON
			LED_voidPedestrianGreenLedON(); //Green LED for Pedestrians ON
			TIMER0_voidDelayBusyWait(5000);


			LED_voidCarRedLedOFF(); //Red LED for Cars OFF
			LED_voidBothYellowLEDBlink();

			LED_voidPedestrianGreenLedOFF(); //Green LED for Pedestrians OFF

			Global_YellowCheck=OFF;
	}
}

void TIMER_5sec(void)
{
	TIMER0_voidDelayBusyWait(5000);
}


void LED_voidPedestrianRedLedON(void)
{
	DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN2,DIO_u8PIN_HIGH);//Red LED for Pedestrians ON
}
void LED_voidPedestrianRedLedOFF(void)
{
	DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN2,DIO_u8PIN_LOW); //Red LED for Pedestrians OFF
}


void LED_voidPedestrianGreenLedON(void)
{
	DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN4,DIO_u8PIN_HIGH); //Green LED for Pedestrians ON
}
void LED_voidPedestrianGreenLedOFF(void)
{
	DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN4,DIO_u8PIN_LOW); //Green LED for Pedestrians OFF
}


void LED_voidBothYellowLEDBlink(void)
{
	u8 Counter;
	for (Counter=0;Counter<5;Counter++)
		{
		DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN3,DIO_u8PIN_HIGH); //Yellow LED for Cars ON
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN3,DIO_u8PIN_HIGH); //Yellow LED for Pedestrians ON
		TIMER0_voidDelayBusyWait(500);
		//_delay_ms(500);
		DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN3,DIO_u8PIN_LOW); //Yellow LED for Cars OFF
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN3,DIO_u8PIN_LOW); //Yellow LED for Pedestrians OFF
		TIMER0_voidDelayBusyWait(500);
		//_delay_ms(500);
		}
}



void LED_voidCarRedLedON(void)
{
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_HIGH); //Red LED for Cars ON
}
void LED_voidCarRedLedOFF(void)
{
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_LOW); //Red LED for Cars OFF
}


void LED_voidCarGreenLedON(void)
{
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_HIGH);//Green LED for Cars ON
}
void LED_voidCarGreenLedOFF(void)
{
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_LOW); //Green LED for Cars OFF
}
