#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_register.h"
#include "EXTI_config.h"


/* Global pointer too function to hold ONT0 ISR address*/
void (*EXTI_pvInt0Func) (void)=NULL ;


void EXTI_voidInt0Init(void)
{
	/*Set sense control for INT0*/

#if INT0_SENSE == LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);

#elif INT0_SENSE == ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);

#elif INT0_SENSE == FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);

#elif INT0_SENSE == RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);

#else
#error "Wrong INT0_SENSE configuration option"

#endif



	/*Peripheral interrupt check for INT0*/
#if INT0_INITIAL_STATE == ENABLED
	SET_BIT(GICR,GICR_INT0);


#elif  INT0_INITIAL_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT0);


#else
#error "Wrong  INT0_INITIAL_STATE configuration option"

#endif


}



u8 EXTI_u8Int0SetSenseControl(u8 Copy_Sense)
{
	u8 Local_u8ErrorState = OK ;

	switch (Copy_Sense)
	{
	case LOW_LEVEL: CLR_BIT(MCUCR,MCUCR_ISC00); CLR_BIT(MCUCR,MCUCR_ISC01); break;

	case ON_CHANGE: SET_BIT(MCUCR,MCUCR_ISC00); CLR_BIT(MCUCR,MCUCR_ISC01); break;

	case RISING_EDGE: SET_BIT(MCUCR,MCUCR_ISC00); SET_BIT(MCUCR,MCUCR_ISC01); break;

	case FALLING_EDGE: CLR_BIT(MCUCR,MCUCR_ISC00); SET_BIT(MCUCR,MCUCR_ISC01); break;

	default: Local_u8ErrorState = NOK;
	}

	return Local_u8ErrorState;
}

void EXTI_u8Int0Enable(void)
{
	SET_BIT(GICR,GICR_INT0);
}


void EXTI_u8Int0Disable(void)
{
	CLR_BIT(GICR,GICR_INT0);
}

u8 EXTI_u8Int0SetCallBack (void (*Copy_pvFunc)(void))
{
	u8 Local_u8ErrorStatus= OK;
	if (Copy_pvFunc != NULL)
	{
		EXTI_pvInt0Func=Copy_pvFunc;
	}
	else
	{
		Local_u8ErrorStatus = NULL_POINTER;
	}
	return Local_u8ErrorStatus;
}
/*ISR for INT0*/
void __vector_1 (void) __attribute__((signal));
void __vector_1 (void)
{
	if(EXTI_pvInt0Func != NULL)
	{
		EXTI_pvInt0Func();
	}
	else
	{
		/*DO NOTHING*/
	}
}
