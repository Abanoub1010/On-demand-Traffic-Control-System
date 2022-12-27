#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

void TIMER0_voidInit(void);

u8 TIMER0_u8SetCallBack(void (*Copy_pvCallBackFunc)(void));



u8 TIMER0_voidGetOutputCompareFlag(void);


void TIMER0_voidDelayBusyWait (u16 Sec) ;



#endif
