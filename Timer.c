l//#define TEST
#ifdef TEST
static unsigned int delta;
#endif
/****************************************************************************
 Module
     c:\me218\timer.c

 Revision
     1.0.1

 Description
     This is a module implementing  8 16 bit timers all using the RTI
     timebase

 Notes
     Everything is done in terms of RTI Ticks, which can change from
     application to application.

 History
 When           Who     What/Why
 -------------- ---     --------
 02/20/99 14:11 jec     modified returns to use symbolic values
 02/24/97 17:13 jec      added new function TMR_SetTimer. This will allow one
             function to set up the time, while another function
             actually initiates the timing.
 02/24/97 13:34 jec      Began Coding
****************************************************************************/

/*----------------------------- Include Files -----------------------------*/
#define __HC11
#include <hc11defs.h>
#include <timer.h>

/*--------------------------- External Variables --------------------------*/
extern unsigned int time;  /* this is used by the default RTI routine */

/*----------------------------- Module Defines ----------------------------*/
#define TMR_RATE_MASK (_H11_RTR0 | _H11_RTR1)

/*------------------------------ Module Types -----------------------------*/

/*
   the size of Tflag sets the number of timers, char = 8, int =16 ...)
   to add more timers, you will need to change the data type and modify
   the initializaiton of TMR_TimerArray
*/

typedef unsigned char Tflag;

typedef struct timer_struc{
   Tflag Mask;
   unsigned int Time;
}Timer;


/*---------------------------- Module Functions ---------------------------*/
void TMR_RTI_Resp(void);

/*---------------------------- Module Variables ---------------------------*/
static Timer TMR_TimerArray[sizeof(Tflag)*8]=
                                            {{BIT0HI, 0xffff},
                                             {BIT1HI, 0xffff},
                                             {BIT2HI, 0xffff},
                                             {BIT3HI, 0xffff},
                                             {BIT4HI, 0xffff},
                                             {BIT5HI, 0xffff},
                                             {BIT6HI, 0xffff},
                                             {BIT7HI, 0xffff}};

static Tflag TMR_ActiveFlags;
static Tflag TMR_EventFlags;

/*------------------------------ Module Code ------------------------------*/
/****************************************************************************
 Function
     TMR_Init

 Parameters
     unsigned char Rate set to one of the TMR_RATE_XX defines to set the
     RTI rate

 Returns
     None.

 Description
     Initializes the timer module by attaching the RTI interrupt to
     the response routine.

 Notes
     None.

 Author
     J. Edward Carryer, 02/24/97 14:23
****************************************************************************/
void TMR_Init(unsigned char Rate)
{
   _H11PACTL &= ~TMR_RATE_MASK;
   _H11PACTL |= (TMR_RATE_MASK & Rate);   /* set RTI Rate */
	_ATTACH(TMR_RTI_Resp, INT_RTII);
   _H11TFLG2 = _H11_RTIF;   /* clear any pending int */
   _H11TMSK2 |= _H11_RTII;  /* enable the RTI int */
    enable();
}

/****************************************************************************
 Function
     TMR_SetTimer

 Parameters
     unsigned char Num, the number of the timer to set.

 Returns
     -1 if requested timer does not exist
     0 otherwise

 Description
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          ,     sets the time for a timer, but does not make it active.

 Notes
     None.

 Author
     J. Edward Carryer, 02/24/97 17:11
****************************************************************************/
signed char TMR_SetTimer(unsigned char Num, unsigned int NewTime)
{
   if( Num >= (sizeof(TMR_TimerArray)/sizeof(Timer)))
      return TMR_ERR;  /* tried to set a timer that doesn't exist */
   TMR_TimerArray[Num].Time = NewTime;
   return TMR_OK;
}

/****************************************************************************
 Function
     TMR_StartTimer

 Parameters
     unsigned char Num the number of the timer to start

 Returns
     signed char -1 for error 0 for success

 Description
     simply sets the active flag in TMR_ActiveFlags to resart a
     stopped timer.

 Notes
     None.

 Author
     J. Edward Carryer, 02/24/97 14:45
****************************************************************************/
signed char TMR_StartTimer(unsigned char Num)
{
   if( Num >= (sizeof(TMR_TimerArray)/sizeof(Timer)))
      return TMR_ERR;  /* tried to set a timer that doesn't exist */
   TMR_ActiveFlags |= TMR_TimerArray[Num].Mask; /* set timer as active */
   return TMR_OK;
}

/****************************************************************************
 Function
     TMR_StopTimer

 Parameters
     unsigned char Num the number of the timer to stop.

 Returns
     -1 for error (timer doesn't exist) 0 for success.

 Description
     simply clears the bit in TMR_ActiveFlags associated with this
     timer. This will cause it to stop counting.

 Notes
     None.

 Author
     J. Edward Carryer, 02/24/97 14:48
****************************************************************************/
signed char TMR_StopTimer(unsigned char Num)
{
   if( Num >= (sizeof(TMR_TimerArray)/sizeof(Timer)))
      return TMR_ERR;  /* tried to set a timer that doesn't exist */
   TMR_ActiveFlags &= ~TMR_TimerArray[Num].Mask; /* set timer as inactive */
   return TMR_OK;
}

/****************************************************************************
 Function
     TMR_InitTimer

 Parameters
     unsigned char Num, the number of the timer to start
     unsigned int NewTime, the number of tick to be counted

 Returns
     -1 if the requested timer does not exist, 0 otherwise.

 Description
     sets the NewTime into the chosen timer and clears any previous
     event flag and sets the timer actice to begin counting.

 Notes
     None.

 Author
     J. Edward Carryer, 02/24/97 14:51
****************************************************************************/
signed char TMR_InitTimer(unsigned char Num, unsigned int NewTime)
{
   if( Num >= (sizeof(TMR_TimerArray)/sizeof(Timer)))
      return TMR_ERR;  /* tried to set a timer that doesn't exist */
   TMR_TimerArray[Num].Time = NewTime;
   TMR_EventFlags &= ~TMR_TimerArray[Num].Mask; /* clear last event flag */
   TMR_ActiveFlags |= TMR_TimerArray[Num].Mask; /* set timer as active */
   return TMR_OK;
}

/****************************************************************************
 Function
     TMR_IsTimerActive

 Parameters
     unsigned char Num the number of the timer to check

 Returns
     -1 if requested timer is not valid
      0 if timer is not active
      1 if it is active

 Description
     used to determine if a timer is currently counting.

 Notes
     None.

 Author
     J. Edward Carryer, 02/24/97 14:53
****************************************************************************/
signed char TMR_IsTimerActive(unsigned char Num)
{
   if( Num >= (sizeof(TMR_TimerArray)/sizeof(Timer)))
      return TMR_ERR;  /* tried to set a timer that doesn't exist */
   else
      if (TMR_ActiveFlags & TMR_TimerArray[Num].Mask)
     return TMR_ACTIVE;
      else
     return TMR_NOT_ACTIVE;
}

/****************************************************************************
 Function
     TMR_IsTimerExpired

 Parameters
     unsigned char Num, the number of the timer to test.

 Returns
     -1 if reqiested timer does not exist
     0 if not expired
     1 if expired

 Description
     tests the flags to determine if the requested timer has expired.

 Notes
     None.

 Author
     J. Edward Carryer, 02/24/97 15:02
****************************************************************************/
signed char TMR_IsTimerExpired(unsigned char Num)
{
   if( Num >= (sizeof(TMR_TimerArray)/sizeof(Timer)))
      return TMR_ERR;  /* tried to set a timer that doesn't exist */
   else
      if (TMR_EventFlags & TMR_TimerArray[Num].Mask) /* and expired */
     return TMR_EXPIRED;
      else
     return TMR_NOT_EXPIRED;
}

/****************************************************************************
 Function
     TMR_ClearTimerExpired

 Parameters
     unsigned char Num, the timer whose event flag should be cleared.

 Returns
     -1 if requested timer does not exist
     0 otherwise

 Description
     simply clears the appropriate bit in TMR_EventFlags to show that
     the event has been serviced.

 Notes
     None.

 Author
     J. Edward Carryer, 02/24/97 15:04
****************************************************************************/
signed char TMR_ClearTimerExpired(unsigned char Num)
{
   if( Num >= (sizeof(TMR_TimerArray)/sizeof(Timer)))
      return TMR_ERR;  /* tried to set a timer that doesn't exist */
   else
      TMR_EventFlags &= ~TMR_TimerArray[Num].Mask;
   return (TMR_OK);
}

/****************************************************************************
 Function
     TMR_RTI_Resp

 Parameters
     None.

 Returns
     None.

 Description
     This is the new RTI response routine to support the timer module.
     It will increment time, to maintain the functionality of the
     GetTime() timer and it will check through the active timers,
     decrementing each active timers count, if the count goes to 0, it
     will set the associated event flag and clear the active flag to
     prevent further counting.

 Notes
     None.

 Author
     J. Edward Carryer, 02/24/97 15:06
****************************************************************************/
void TMR_RTI_Resp(void)
{
   unsigned char i;
#ifdef TEST
unsigned int Start = _H11TCNT;
#endif

   _H11TFLG2 = _H11_RTIF;   /* clear the source of the int */
   ++time;                 /* keep the GetTime() timer running */
   if (TMR_ActiveFlags != 0)
   {
      for(i=0; i<(sizeof(Tflag)*8); i++)
      {
     if ((TMR_ActiveFlags & TMR_TimerArray[i].Mask) != 0) /* if active */
        if(--TMR_TimerArray[i].Time == 0) /* if timed out */
        {
           TMR_EventFlags |= TMR_TimerArray[i].Mask; /* note the event */
           TMR_ActiveFlags &= ~TMR_TimerArray[i].Mask; /* stop counting */
        }
      }
#ifdef TEST
delta = _H11TCNT - Start;
#endif
   }
}
/*------------------------------- Footnotes -------------------------------*/
#ifdef TEST

#include <stdio.h>

#define TIME_OUT_DELAY 1220
char Message[]={31,32,33,34,35,36,37,38,0};


void main(void)
{
   unsigned int i;
   puts(Message);
   Message[0]='!';
   puts("Starting\n");
   TMR_Init(TMR_RATE_8MS);
   TMR_InitTimer(0, TIME_OUT_DELAY); /* TIME_OUT_DELAY  = 1S w/ 8mS interval */
   TMR_InitTimer(1, TIME_OUT_DELAY);
   TMR_InitTimer(2, TIME_OUT_DELAY);
   TMR_InitTimer(3, TIME_OUT_DELAY);
   TMR_InitTimer(4, TIME_OUT_DELAY);
   TMR_InitTimer(5, TIME_OUT_DELAY);
   TMR_InitTimer(6, TIME_OUT_DELAY);
   TMR_InitTimer(7, TIME_OUT_DELAY);
   while(TMR_IsTimerExpired(0) != 1)
      ;
   puts("Timed Out\a\n");
   TMR_InitTimer(7, TIME_OUT_DELAY);
   for (i=0;i<10,000 ;i++ )
   {/* kill some time */
   }
   TMR_StopTimer(7);
   if (TMR_IsTimerActive(7) != 0)
      puts("Timer Stop Failed\n");
   else
      puts("Timer Stop Succeded\n");
   TMR_StartTimer(7);
   while(TMR_IsTimerExpired(7) != 1)
      ;

   puts("Timed Out Again\a\n");

   disable();
printf("response time = %u\n", delta);
}
#endif
/*------------------------------ End of file ------------------------------*/

