/****************************************************************************
 Module
   d:\me218b\Lectures\Lecture 29\FindingTape.c

 Revision
   1.0.1

 Description
   This is the FindingTape state machine for the Lab 9 example.

 Notes

 History
 When           Who     What/Why
 -------------- ---     --------
 02/18/99 10:36 jec      built from SMTemplate.c
****************************************************************************/
/*----------------------------- Include Files -----------------------------*/
/* include header files for this state mahcine as well as any machines at the
   next lower level in the hierarchy that are sub-machines to this machine
*/
#include <hc11defs.h>
#include "FindingTape.h"
#include "Acquiring.h"
#include "Driving.h"
#include "sm_general.h"

/*----------------------------- Module Defines ----------------------------*/
// define constants for the states and event for this machine
// The states
#define ACQUIRING 0
#define DRIVING   1
#define STOP      2
// The Events
#define NO_EVENT  0
#define ACQUIRED  1
#define HIT_TAPE  2

/*---------------------------- Module Functions ---------------------------*/
/* prototypes for private functions for this machine, things like event
   checkers, entry & exit functions.they should be functions relevant to the
   behavior of this state machine
*/
static unsigned char CheckBeaconAcquired(void);
static unsigned char CheckHitTape(void);

/*---------------------------- Module Variables ---------------------------*/
// everybody needs a state variable, you may need others as well
static unsigned char CurrentState;
static unsigned char AcquiredLastTime;
static unsigned char TapeHitLastTime;

/*------------------------------ Module Code ------------------------------*/
/****************************************************************************
 Function
    FindingTapeMachine

 Parameters
   None

 Returns
   None

 Description
   Implements the FindingTape state machine

 Notes
   uses nested switch/case to implement the machine.
 Author
   J. Edward Carryer, 2/18/99, 11:10AM
****************************************************************************/
void FindingTapeMachine( void )
{
   unsigned char CurrentEvent;
   unsigned char NextState;

   switch ( CurrentState )
   {
       case ACQUIRING :       // If current state is state one
         AcquiringMachine();   //Execute During function for state one
         CurrentEvent = CheckBeaconAcquired();   //Check for events
         if ( CurrentEvent != 0 )        //If an event is active
         {
            switch ( CurrentEvent)
            {
               case ACQUIRED : //If event is event one
                  // Execute action function for state one : event one
                  NextState = DRIVING;//Decide what the next state will be
                  break;
            }
            //   If next state is different from current state
            if ( NextState != CurrentState)
            {
               //   Execute exit function for current state
               StartDrivingMachine(); //Execute entry function for new state
               CurrentState = NextState; //Modify state variable
             }
         }
         return;

       case DRIVING :       // If current state is state one
         DrivingMachine();   //Execute During function for state one
         CurrentEvent = CheckHitTape();   //Check for events
         if ( CurrentEvent != 0 )        //If an event is active
         {
            switch ( CurrentEvent)
            {
               case HIT_TAPE : //If event is event one
                  // Execute action function for state one : event one
                  NextState = STOP;//Decide what the next state will be
                  break;
            }
            //   If next state is different from current state
            if ( NextState != CurrentState)
            {
               //   Execute exit function for current state
               //   Execute entry function for new state
               CurrentState = NextState; //Modify state variable
             }
         }
         return;
    }
}

/****************************************************************************
 Function
     StartFindingTapeMachine

 Parameters
     None

 Returns
     None

 Description
     Does the start-up activities for the FindingTape state machine
 Notes

 Author
     J. Edward Carryer, 2/18/99, 12:06PM
****************************************************************************/
void StartFindingTapeMachine( void )
{
   CurrentState = ACQUIRING;
// call the (optional) entry fucntion for the ENTRY_STATE
   StartAcquiringMachine();
// any other initialization necessary to re-start the state machine
   AcquiredLastTime = FALSE;
   TapeHitLastTime = FALSE;
}

/****************************************************************************
 Function
     IsTapeFound

 Parameters
     None

 Returns
     unsigned char

 Description
     Tests to see if we are found tape, determined by looking at the current
     state
 Notes

 Author
     J. Edward Carryer, 2/19/99, 11:37PM
****************************************************************************/
unsigned char IsTapeFound( void )
{
   return(CurrentState == STOP);
}

/*------------------------------ Private Code ------------------------------*/
static unsigned char CheckBeaconAcquired(void)
{
   unsigned char ThisEvent;
   unsigned char ReturnVal = NO_EVENT;

   // if input was in another state last time & in an active state this time
   if (((ThisEvent = IsBeaconAcquired()) == TRUE) &&
         (AcquiredLastTime == FALSE))//Check for events
       ReturnVal = HIT_TAPE;
   AcquiredLastTime = ThisEvent;
   return ReturnVal;
}

static unsigned char CheckHitTape(void)
{
   unsigned char ThisEvent;
   unsigned char ReturnVal = NO_EVENT;

   // if input was in another state last time & in an active state this time
   if (((ThisEvent = IsTapeHit()) == TRUE) &&
         (TapeHitLastTime == FALSE))//Check for events
       ReturnVal = HIT_TAPE;
   TapeHitLastTime = ThisEvent;
   return ReturnVal;
}

