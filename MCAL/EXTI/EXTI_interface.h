#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

#define 	LOW_LEVEL 			1
#define 	ON_CHANGE  			2
#define 	FALLING_EDGE 		3
#define 	RISING_EDGE 		4


void EXTI_voidInt0Init(void);

void EXTI_voidInt1Init(void);

void EXTI_voidInt2Init(void);





/*  Description: A function to set the required sense control of INT0 using post build configuration*/
/*  Input: Copy_u8Sense , Options are:  1- LOW_LEVEL
										2- ON_CHANGE
 										3- FALLING_EDGE
										4- RISING_EDGE
	Output: Error status with type u8
*/
u8 EXTI_u8Int0SetSenseControl(u8 Copy_u8Sense);

void EXTI_u8Int0Enable(void);

void EXTI_u8Int0Disable(void);

u8 EXTI_u8Int0SetCallBack (void (*Copy_pvFunc)(void));

#endif
