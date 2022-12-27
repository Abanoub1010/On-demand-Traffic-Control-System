#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "TIMER_interface.h"
#include "TIMER_register.h"
#include "TIMER_private.h"
#include "TIMER_config.h"


static void (*TIMER0_pvCallBackFunc)(void)= NULL ;

void TIMER0_voidInit(void)
{
	/*Choose CTC mode*/
	CLR_BIT(TCCR0,TCCR0_WMG00);
	SET_BIT(TCCR0,TCCR0_WMG01);

	/*Output compare match interrupt enable*/
	SET_BIT(TIMSK,TIMSK_OCIE0);
	
	/*Set compare match value to 250*/
	OCR0=250;

	/*Prescaler: Division by 8*/
	CLR_BIT(TCCR0,TCCR0_CS00);
	SET_BIT(TCCR0,TCCR0_CS01);
	CLR_BIT(TCCR0,TCCR0_CS02);
}

u8 TIMER0_u8SetCallBack(void (*Copy_pvCallBackFunc)(void))
{
	u8 Local_u8ErrorStatus=OK ;
	if (Copy_pvCallBackFunc != NULL)
	{
		TIMER0_pvCallBackFunc= Copy_pvCallBackFunc;
	}
	else
	{
		Local_u8ErrorStatus = NULL_POINTER;
	}
return Local_u8ErrorStatus;
}

u8 TIMER0_voidGetOutputCompareFlag(void)
{
	u8 LocalCompareFlag = GET_BIT(TIFR,TIFR_TOV0);

	return LocalCompareFlag;
}


void TIMER0_voidDelayBusyWait (u16 Sec)
{
	u16 Counter=0;


	if (Sec==5000)
	{
	 	while (Counter <= 20000)
				{
					while(GET_BIT(TIFR,TIFR_TOV0)!=1);
					Counter++;
					SET_BIT(TIFR,TIFR_TOV0);
				}
				Counter=0;
	}
	else if (Sec==500)
	{
	 	while (Counter <= 2000)
				{
					while(GET_BIT(TIFR,TIFR_TOV0)!=1);
					Counter++;
					SET_BIT(TIFR,TIFR_TOV0);
				}
				Counter=0;

	}

}


void __vector_10 (void) __attribute__((signal));
void __vector_10 (void)
{

	if(TIMER0_pvCallBackFunc != NULL)
	{
		TIMER0_pvCallBackFunc();
	}

}


