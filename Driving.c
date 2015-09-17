/****************************************************************************
 Module
   d:\pwm.c

 Revision
   1.0.1

 Description
   This program sets three different pwm duty cycles for the lucky 13 droid.

 Notes

 History
 When           Who     What/Why
 -------------- ---     --------
 02/20/99 08:55 jec      built from template
****************************************************************************/
/*----------------------------- INCLUDE FILES -----------------------------*/
/* include header files for this state machine as well as any machines at the
   next lower level in the hierarchy that are sub-machines to this machine
*/
#include "pwm.h"


/*----------------------------- MODULE DEFINES ----------------------------*/
// define constants for the states and event for this machine
// event constants should start with 1 so that you can use 0 as 'No Events'
#define PWM_PORT H11PORTA
#define PWM_RIGHT  BIT_6
#define PWM_LEFT   BIT_5
#define PWM_TURRET BIT_4

//NUMBER OF CHANNELS
#define PMW_CHANNELS 3
#define PMW_INTITIAL_PERIOD 4000
/*------------------------------GLOBAL VARIABLES ---------------------------*/
static

/*----------------------------MODULE FUNCTIONS ---------------------------*/
/* prototypes for private functions for this machine, things like event
   checkers, entry & exit functions.they should be functions relevant to the
   behavior of this state machine
*/
static void PWM_Isr(void);


/*---------------------------- MODULE VARIABLES ---------------------------*/
// everybody needs a state variable, you may need others as well
static unsigned char CurrentState;
static unsigned char OnTapeLastTime;
static unsigned char LeqRLastTime;
static unsigned char LgtRLastTime;
static unsigned char RgtLLastTime;
static unsigned char TimerExpLastTime;

/*------------------------------ MODULE CODE ------------------------------*/
/****************************************************************************
 Function
    DrivingMachine

 Parameters
   None

 Returns
   None

 Description
   Implements the Driving To Tape state machine
 Notes
   uses nested switch/case to implement the machine.
 Author
   J. Edward Carryer, 2/20/99, 09:01AM
****************************************************************************/
void DrivingMachine( void )
{
   unsigned char CurrentEvent;
   unsigned char NextState;

   switch ( CurrentState )
   {
       case DRV_FORWARD :       // If current state is state one
                           //Execute During function for state one
         CurrentEvent = CheckEventsForward();   //Check for events
         if ( CurrentEvent != 0 )        //If an event is active
         {
            switch ( CurrentEvent)
            {
               case LT_GT_RT : //If event is event one
                  // Execute action function for state one : event one
                  TMR_StartTimer(TURN_TIMER);
                  NextState = TURN_LEFT;//Decide what the next state will be
                  break;
               case RT_GT_LT : //If event is event one
                  // Execute action function for state one : event one
                  TMR_StartTimer(TURN_TIMER);
                  NextState = TURN_RIGHT;//Decide what the next state will be
                  break;
               case HIT_TAPE : //If event is event one
                  // Execute action function for state one : event one
                  NextState = DRV_STOP;//Decide what the next state will be
                  break;
            }
            //   If next state is different from current state
            if ( NextState != CurrentState)
            {
               //   Execute exit function for current state
               CallEntryFunction(NextState);
               CurrentState = NextState; //Modify state variable
             }
         }
         return;

       case TURN_LEFT :       // If current state is state one
                           //Execute During function for state one
         CurrentEvent = CheckEventsTurning();   //Check for events
         if ( CurrentEvent != 0 )        //If an event is active
         {
            switch ( CurrentEvent)
            {
               case TIMER_EXP : //If event is event one
                  // Execute action function for state one : event one
                  NextState = SPIN_LEFT;//Decide what the next state will be
                  break;
               case LT_EQ_RT : //If event is event one
                  // Execute action function for state one : event one
                  NextState = DRV_FORWARD;//Decide what the next state will be
                  break;
               case HIT_TAPE : //If event is event one
                  // Execute action function for state one : event one
                  NextState = DRV_STOP;//Decide what the next state will be
                  break;
            }
            //   If next state is different from current state
            if ( NextState != CurrentState)
            {
               //   Execute exit function for current state
               CallEntryFunction(NextState);
               CurrentState = NextState; //Modify state variable
             }
         }
         return;

       case SPIN_LEFT :       // If current state is state one
                           //Execute During function for state one
         CurrentEvent = CheckEventsSpinning();   //Check for events
         if ( CurrentEvent != 0 )        //If an event is active
         {
            switch ( CurrentEvent)
            {
               case LT_EQ_RT : //If event is event one
                  // Execute action function for state one : event one
                  NextState = DRV_FORWARD;//Decide what the next state will be
                  break;
               case HIT_TAPE : //If event is event one
                  // Execute action function for state one : event one
                  NextState = DRV_STOP;//Decide what the next state will be
                  break;
            }
            //   If next state is different from current state
            if ( NextState != CurrentState)
            {
               //   Execute exit function for current state
               CallEntryFunction(NextState);
               CurrentState = NextState; //Modify state variable
             }
         }
         return;

       case TURN_RIGHT :       // If current state is state one
                           //Execute During function for state one
         CurrentEvent = CheckEventsTurning();   //Check for events
         if ( CurrentEvent != 0 )        //If an event is active
         {
            switch ( CurrentEvent)
            {
               case LT_EQ_RT : //If event is event one
                  // Execute action function for state one : event one
                  NextState = DRV_FORWARD;//Decide what the next state will be
                  break;
               case TIMER_EXP : //If event is event one
                  // Execute action function for state one : event one
                  NextState = SPIN_RIGHT;//Decide what the next state will be
                  break;
               case HIT_TAPE : //If event is event one
                  // Execute action function for state one : event one
                  NextState = DRV_STOP;//Decide what the next state will be
                  break;
            }
            //   If next state is different from current state
            if ( NextState != CurrentState)
            {
               //   Execute exit function for current state
               CallEntryFunction(NextState);
               CurrentState = NextState; //Modify state variable
             }
         }
         return;

       case SPIN_RIGHT :       // If current state is state one
                           //Execute During function for state one
         CurrentEvent = CheckEventsSpinning();   //Check for events
         if ( CurrentEvent != 0 )        //If an event is active
         {
            switch ( CurrentEvent)
            {
               case LT_EQ_RT : //If event is event one
                  // Execute action function for state one : event one
                  NextState = DRV_FORWARD;//Decide what the next state will be
                  break;
               case HIT_TAPE : //If event is event one
                  // Execute action function for state one : event one
                  NextState = DRV_STOP;//Decide what the next state will be
                  break;
            }
            //   If next state is different from current state
            if ( NextState != CurrentState)
            {
               //   Execute exit function for current state
               CallEntryFunction(NextState);
               CurrentState = NextState; //Modify state variable
             }
         }
         return;
   }
}
/****************************************************************************
 Function
     StartDrivingMachine

 Parameters
     None

 Returns
     None

 Description
     Does any required initialization for this state machine
 Notes

 Author
     J. Edward Carryer, 2/18/99, 10:38AM
****************************************************************************/
void StartDrivingMachine ( void )
{
   CurrentState = DRV_FORWARD;
// call the (optional) entry fucntion for the ENTRY_STATE
   CallEntryFunction(CurrentState);
// any other initialization necessary to re-start the state machine
   OnTapeLastTime = FALSE;
   LeqRLastTime = FALSE;
   LgtRLastTime = FALSE;
   RgtLLastTime = FALSE;
   TimerExpLastTime = FALSE;
}

/****************************************************************************
 Function
     IsTapeHit

 Parameters
     None

 Returns
     unsigned char

 Description
     tests to see if Tape has been hit by looking at the current state.
     if we are in the DRV_STOP state, then we hit tape
 Notes

 Author
     J. Edward Carryer, 2/20/99, 10:08AM
****************************************************************************/
unsigned char IsTapeHit( void )
{
   if ( CurrentState == DRV_STOP)
      return TRUE;
   else
      return FALSE;
}

/*------------------------------ Private Code ------------------------------*/
static void CallEntryFunction( unsigned char NewState )
{
   switch ( NewState)
   {
      case DRV_FORWARD :
         MotorDrive(FORWARD, MEDIUM);
         break;
      case TURN_LEFT :
         MotorDrive(TURN_RATE_L, MEDIUM);
         break;
      case TURN_RIGHT :
         MotorDrive(TURN_RATE_R, MEDIUM);
         break;
      case SPIN_LEFT :
         MotorDrive(SPIN_CCW, MEDIUM);
         break;
      case SPIN_RIGHT :
         MotorDrive(SPIN_CW, MEDIUM);
         break;
      case DRV_STOP :
         MotorDrive(FORWARD, STOP);
         break;
   }
   return;
}

static unsigned char CheckEventsSpinning(void)
{
   unsigned char ThisEvent;
   unsigned char ReturnVal;

// if input was in another state last time & in an active state this time
   if (((ThisEvent = ANY_TAPE_ON) == TRUE) &&
       (OnTapeLastTime == FALSE))       // Check for Tape Hit
   {
      ReturnVal = HIT_TAPE;
      OnTapeLastTime = TRUE;
   }
   else                               // this gives Tape priority over sensor
   {
      OnTapeLastTime = ThisEvent;
      if (((ThisEvent = LeftEqualRight()) == TRUE) &&
          (LeqRLastTime == FALSE))//Check for beacon centered
      {
         ReturnVal = LT_EQ_RT;
         LeqRLastTime = TRUE;
      }
      else
      {
         LeqRLastTime = ThisEvent;
         ReturnVal = NO_EVENT;
      }
   }
   return ReturnVal;
}

static unsigned char CheckEventsTurning(void)
{
   unsigned char ThisEvent;
   unsigned char ReturnVal;

// if input was in another state last time & in an active state this time
   if (((ThisEvent = ANY_TAPE_ON) == TRUE) &&
       (OnTapeLastTime == FALSE))        // Check for Tape Hit
   {
      ReturnVal = HIT_TAPE;
      OnTapeLastTime = TRUE;
   }
   else                               // this gives Tape priority over sensor
   {
      OnTapeLastTime = ThisEvent;
      if (((ThisEvent = LeftEqualRight()) == TRUE) &&
          (LeqRLastTime == FALSE))//Check for beacon centered
      {
         ReturnVal = LT_EQ_RT;
         LeqRLastTime = TRUE;
      }
      else                              // this give equal prioity over timer
      {
         LeqRLastTime = ThisEvent;
         if (((ThisEvent = TMR_IsTimerExpired(TURN_TIMER)) == TRUE) &&
             (TimerExpLastTime == FALSE)) //Check for timeout
         {
            ReturnVal = TIMER_EXP;
            TimerExpLastTime = TRUE;
         }
         else
         {
            TimerExpLastTime = ThisEvent;
            ReturnVal = NO_EVENT;
         }
      }
   }
   return ReturnVal;
}

static unsigned char CheckEventsForward(void)
{
   unsigned char ThisEvent;
   unsigned char ReturnVal;
   int SensorDiff;

// if input was in another state last time & in an active state this time
   if (((ThisEvent = ANY_TAPE_ON) == TRUE) &&
       (OnTapeLastTime == FALSE))     // Check for Tape Hit
   {
      ReturnVal = HIT_TAPE;
      OnTapeLastTime = TRUE;
   }
   else                               // this gives Tape priority over sensor
   {
      OnTapeLastTime = ThisEvent;
      if ((SensorDiff = GetSensorDiff()) > TURN_THRESH)  // we're gonna turn
      {
         if (((ThisEvent = (SensorDiff > 0)) == TRUE) &&  // Left gt Right ??
             (LgtRLastTime == FALSE))//Check for events
         {
            ReturnVal = LT_GT_RT;
            LgtRLastTime = TRUE;
            RgtLLastTime = FALSE;
         }
         else                           // must be Right gt Left
         {
            ReturnVal = RT_GT_LT;
            RgtLLastTime = TRUE;
            LgtRLastTime = FALSE;
         }
      }
      else                              // more or less equal, no turn
      {
            RgtLLastTime = FALSE;
            LgtRLastTime = FALSE;
            ReturnVal = NO_EVENT;
      }
   }
   return ReturnVal;
}

