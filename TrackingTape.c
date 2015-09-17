/****************************************************************************
 Module
   d:\me218b\Lectures\Lecture 29\TrackingTape.c

 Revision
   1.0.1

 Description
   This is the tape tracking machine for the nestedcase example.

 Notes

 History
 When           Who     What/Why
 -------------- ---     --------
 02/20/99 12:47 jec      built from template
****************************************************************************/
/*----------------------------- Include Files -----------------------------*/
/* include header files for this state machine as well as any machines at the
   next lower level in the hierarchy that are sub-machines to this machine
*/
#include "TrackingTape.h"
#include "Motor.h"
#include "TapeSense.h"
#include "Timer.h"
#include "sm_general.h"

/*----------------------------- Module Defines ----------------------------*/
// define constants for the states and event for this machine
// event constants should start with 1 so that you can use 0 as 'No Events'
#define DRV_FORWARD     0
#define GENT_LEFT       1
#define DRV_HARD_LEFT   2
#define GENT_RIGHT      3
#define DRV_HARD_RIGHT  4
#define DRV_STOP        5
// The Events
#define NO_EVENT        0
#define LEFT_GOES_ON    1
#define LEFT_GOES_OFF   2
#define CENT_GOES_ON    3
#define CENT_GOES_OFF   4
#define RIGHT_GOES_ON   5
#define RIGHT_GOES_OFF  6
#define HIT_TAPE        7
#define TIMER_EXP       8

#define CENT_ON  0x02
#define LEFT_ON  0x01
#define RIGHT_ON 0x04
#define ALL_ON   0x07

#define TURN_TIMER 1


/*---------------------------- Module Functions ---------------------------*/
/* prototypes for private functions for this machine, things like event
   checkers, entry & exit functions.they should be functions relevant to the
   behavior of this state machine
*/
static void CallEntryFunction( unsigned char NewState );
static unsigned char CheckEventsGentLeft( void );
static unsigned char CheckEventsGentRight( void );
static unsigned char CheckEventsHardLeft( void );
static unsigned char CheckEventsHardRight( void );
static unsigned char CheckEventsForward(void);
static unsigned char CheckHitT( void );
static unsigned char CheckLeftOn( void );
static unsigned char CheckLeftOff( void );
static unsigned char CheckRightOn( void );
static unsigned char CheckRightOff( void );
static unsigned char CheckCentOn( void );
static unsigned char CheckCentOff( void );

/*---------------------------- Module Variables ---------------------------*/
// everybody needs a state variable, you may need others as well
static unsigned char CurrentState;
static unsigned char OnLeftLastTime;
static unsigned char OnRightLastTime;
static unsigned char OnCentLastTime;
static unsigned char AtTLastTime;
static unsigned char TimerExpLastTime;

/*------------------------------ Module Code ------------------------------*/
/****************************************************************************
 Function
    TrackingTapeMachine

 Parameters
   None

 Returns
   None

 Description
   Implements the Tracking Tape state machine
 Notes
   uses nested switch/case to implement the machine.
 Author
   J. Edward Carryer, 2/20/99, 12:54PM
****************************************************************************/
void TrackingTapeMachine( void )
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
               case LEFT_GOES_ON : //If event is event one
                  // Execute action function for state one : event one
                  NextState = GENT_LEFT;//Decide what the next state will be
                  break;
               case CENT_GOES_OFF : //If event is event one
                  // Execute action function for state one : event one
                  NextState = GENT_RIGHT;//Decide what the next state will be
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

       case GENT_LEFT :       // If current state is state one
                           //Execute During function for state one
         CurrentEvent = CheckEventsGentLeft();   //Check for events
         if ( CurrentEvent != 0 )        //If an event is active
         {
            switch ( CurrentEvent)
            {
               case LEFT_GOES_OFF : //If event is event one
                  // Execute action function for state one : event one
                  NextState = DRV_FORWARD;//Decide what the next state will be
                  break;
               case TIMER_EXP : //If event is event one
               case RIGHT_GOES_OFF : //If event is event one
               case CENT_GOES_OFF : //If event is event one
                  // Execute action function for state one : event one
                  NextState = DRV_HARD_LEFT;//Decide what the next state will be
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

       case DRV_HARD_LEFT :       // If current state is state one
                           //Execute During function for state one
         CurrentEvent = CheckEventsHardLeft();   //Check for events
         if ( CurrentEvent != 0 )        //If an event is active
         {
            switch ( CurrentEvent)
            {
               case RIGHT_GOES_ON : //If event is event one
               case CENT_GOES_ON : //If event is event one
                  // Execute action function for state one : event one
                  NextState = GENT_LEFT;//Decide what the next state will be
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

       case GENT_RIGHT :       // If current state is state one
                           //Execute During function for state one
         CurrentEvent = CheckEventsGentRight();   //Check for events
         if ( CurrentEvent != 0 )        //If an event is active
         {
            switch ( CurrentEvent)
            {
               case CENT_GOES_ON : //If event is event one
                  // Execute action function for state one : event one
                  NextState = DRV_FORWARD;//Decide what the next state will be
                  break;
               case RIGHT_GOES_OFF : //If event is event one
               case TIMER_EXP : //If event is event one
                  // Execute action function for state one : event one
                  NextState = DRV_HARD_RIGHT;//Decide what the next state will be
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

       case DRV_HARD_RIGHT :       // If current state is state one
                           //Execute During function for state one
         CurrentEvent = CheckEventsHardRight();   //Check for events
         if ( CurrentEvent != 0 )        //If an event is active
         {
            switch ( CurrentEvent)
            {
               case RIGHT_GOES_ON : //If event is event one
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
     StartTrackingTapeMachine

 Parameters
     None

 Returns
     None

 Description
     Does any required initialization for this state machine
 Notes

 Author
     J. Edward Carryer, 2/20/99, 12:54PM
****************************************************************************/
void StartTrackingTapeMachine ( void )
{
   CurrentState = DRV_FORWARD;
// call the (optional) entry fucntion for the ENTRY_STATE
   CallEntryFunction(CurrentState);
// any other initialization necessary to re-start the state machine
   OnLeftLastTime = FALSE;
   OnRightLastTime = FALSE;
   OnCentLastTime = FALSE;
   TimerExpLastTime = FALSE;
   return;
}

/****************************************************************************
 Function
     IsTFound

 Parameters
     None

 Returns
     unsigned char

 Description
     tests to see if Tape T has been hit by looking at the current state.
     if we are in the DRV_STOP state, then we hit the T
 Notes

 Author
     J. Edward Carryer, 2/20/99, 12:59PM
****************************************************************************/
unsigned char IsTFound( void )
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
      case GENT_LEFT :
         MotorDrive(GENTLE_LEFT, MEDIUM);
         TMR_StartTimer(TURN_TIMER);
         break;
      case GENT_RIGHT :
         MotorDrive(GENTLE_RIGHT, MEDIUM);
         TMR_StartTimer(TURN_TIMER);
         break;
      case DRV_HARD_LEFT :
         MotorDrive(HARD_LEFT, MEDIUM);
         break;
      case DRV_HARD_RIGHT :
         MotorDrive(HARD_RIGHT, MEDIUM);
         break;
      case DRV_STOP :
         MotorDrive(FORWARD, STOP);
         break;
   }
   return;
}

static unsigned char CheckEventsGentLeft(void)
{
// if input was in another state last time & in an active state this time
   if (CheckHitT() != NO_EVENT)
      return HIT_TAPE;            // this gives T priority over edge
   if (CheckLeftOff() != NO_EVENT)
      return LEFT_GOES_OFF;
   if (CheckRightOff() != NO_EVENT)
      return RIGHT_GOES_OFF;
   if (CheckCentOff() != NO_EVENT)
      return CENT_GOES_OFF;
   if ( TMR_IsTimerExpired(TURN_TIMER) == TMR_EXPIRED)
      return TIMER_EXP;
}

static unsigned char CheckEventsGentRight(void)
{
// if input was in another state last time & in an active state this time
   if (CheckHitT() != NO_EVENT)
      return HIT_TAPE;            // this gives T priority over edge
   if (CheckCentOn() != NO_EVENT)
      return CENT_GOES_ON;
   if (CheckRightOff() != NO_EVENT)
      return RIGHT_GOES_OFF;
   if ( TMR_IsTimerExpired(TURN_TIMER) == TMR_EXPIRED)
      return TIMER_EXP;
}

static unsigned char CheckEventsHardLeft(void)
{
// if input was in another state last time & in an active state this time
   if (CheckHitT() != NO_EVENT)
      return HIT_TAPE;            // this gives T priority over edge
   if (CheckCentOn() != NO_EVENT)
      return CENT_GOES_ON;
   if (CheckRightOn() != NO_EVENT)
      return RIGHT_GOES_ON;
}

static unsigned char CheckEventsHardRight(void)
{
// if input was in another state last time & in an active state this time
   if (CheckHitT() != NO_EVENT)
      return HIT_TAPE;            // this gives T priority over edge
   if (CheckRightOn() != NO_EVENT)
      return RIGHT_GOES_ON;
}

static unsigned char CheckEventsForward(void)
{
   if (CheckHitT() != NO_EVENT)
      return HIT_TAPE;            // this gives T priority over edge
   if (CheckCentOff() != NO_EVENT)
      return CENT_GOES_OFF;
   if (CheckLeftOn() != NO_EVENT)
      return LEFT_GOES_ON;
}

static unsigned char CheckHitT( void )
{
   unsigned char ReturnVal;
   unsigned char CurrentSenseState =  (GetTapeState() == ALL_ON);

   if ((CurrentSenseState == TRUE) &&
       (AtTLastTime == FALSE))       // Check for Tape Hit
   {
      ReturnVal = HIT_TAPE;
      AtTLastTime = TRUE;
   }
   else
   {
      AtTLastTime = CurrentSenseState;
      ReturnVal = NO_EVENT;
   }
   return ReturnVal;
}

static unsigned char CheckLeftOn( void )
{
   unsigned char ReturnVal;
   unsigned char CurrentSenseState = ((GetTapeState() & LEFT_ON) == LEFT_ON);

   if ((CurrentSenseState == TRUE) &&
       (OnLeftLastTime == FALSE))       // Check for left going ON
   {
      ReturnVal = LEFT_GOES_ON;
      OnLeftLastTime = TRUE;
   }
   else
   {
      OnLeftLastTime = CurrentSenseState;
      ReturnVal = NO_EVENT;
   }
   return ReturnVal;
}

static unsigned char CheckRightOn( void )
{
   unsigned char ReturnVal;
   unsigned char CurrentSenseState = ((GetTapeState() & RIGHT_ON) == RIGHT_ON);

   if ((CurrentSenseState == TRUE) &&
       (OnRightLastTime == FALSE))       // Check for right going ON
   {
      ReturnVal = RIGHT_GOES_ON;
      OnRightLastTime = TRUE;
   }
   else
   {
      OnRightLastTime = CurrentSenseState;
      ReturnVal = NO_EVENT;
   }
   return ReturnVal;
}

static unsigned char CheckCentOn( void )
{
   unsigned char ReturnVal;
   unsigned char CurrentSenseState = ((GetTapeState() & CENT_ON) == CENT_ON);

   if ((CurrentSenseState == TRUE) &&
       (OnCentLastTime == FALSE))       // Check for center going ON
   {
      ReturnVal = CENT_GOES_ON;
      OnCentLastTime = TRUE;
   }
   else
   {
      OnCentLastTime = CurrentSenseState;
      ReturnVal = NO_EVENT;
   }
   return ReturnVal;
}

static unsigned char CheckLeftOff( void )
{
   unsigned char ReturnVal;
   unsigned char CurrentSenseState = ((GetTapeState() & LEFT_ON) == LEFT_ON);

   if ((CurrentSenseState == FALSE) &&
       (OnLeftLastTime == TRUE))       // Check for left going OFF
   {
      ReturnVal = LEFT_GOES_OFF;
      OnLeftLastTime = FALSE;
   }
   else
   {
      OnLeftLastTime = CurrentSenseState;
      ReturnVal = NO_EVENT;
   }
   return ReturnVal;
}

static unsigned char CheckRightOff( void )
{
   unsigned char ReturnVal;
   unsigned char CurrentSenseState = ((GetTapeState() & RIGHT_ON) == RIGHT_ON);

   if ((CurrentSenseState == FALSE) &&
       (OnRightLastTime == TRUE))       // Check for right going OFF
   {
      ReturnVal = RIGHT_GOES_OFF;
      OnRightLastTime = FALSE;
   }
   else
   {
      OnRightLastTime = CurrentSenseState;
      ReturnVal = NO_EVENT;
   }
   return ReturnVal;
}

static unsigned char CheckCentOff( void )
{
   unsigned char ReturnVal;
   unsigned char CurrentSenseState = ((GetTapeState() & CENT_ON) == CENT_ON);

   if ((CurrentSenseState == FALSE) &&
       (OnCentLastTime == TRUE))       // Check for center going OFF
   {
      ReturnVal = CENT_GOES_OFF;
      OnCentLastTime = FALSE;
   }
   else
   {
      OnCentLastTime = CurrentSenseState;
      ReturnVal = NO_EVENT;
   }
   return ReturnVal;
}

