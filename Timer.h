/****************************************************************************
 Module
         c:\me218\tmr218.h

 Revision
         1.0.1

 Description
         Header File for the ME218 Timer Module

 Notes


 History
 When           Who	What/Why
 -------------- ---	--------
 02/20/99 14:11 jec   added #defines for TMR_ERR, TMR_ACTIVE, TMR_EXPIRED
 02/24/97 14:28 jec   Began Coding
****************************************************************************/
/* these assume an 8MHz crystal, 2MHz E clock */
#define TMR_RATE_4MS  (0)							/* 4.1mS */
#define TMR_RATE_8MS  (H11_RTR0)					/* 8.19 mS */
#define TMR_RATE_16MS (_H11_RTR1)					/* 16.38mS */
#define TMR_RATE_32MS (_H11_RTR0 | _H11_RTR1)	/* 32.77mS */

 #define TMR_ERR     -1
 #define TMR_ACTIVE   1
 #define TMR_EXPIRED  1
 #define TMR_OK       0
 #define TMR_NOT_ACTIVE   0
 #define TMR_NOT_EXPIRED  0

void TMR_Init(unsigned char Rate);
signed char TMR_InitTimer(unsigned char Num, unsigned int NewTime);
signed char TMR_SetTimer(unsigned char Num, unsigned int NewTime);
signed char TMR_StartTimer(unsigned char Num);
signed char TMR_StopTimer(unsigned char Num);
signed char TMR_IsTimerActive(unsigned char Num);
signed char TMR_IsTimerExpired(unsigned char Num);
signed char TMR_ClearTimerExpired(unsigned char Num);

/*------------------------------ End of file ------------------------------*/


