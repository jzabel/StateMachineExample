/****************************************************************************
 Module
   d:\me218b\Lectures\Lecture 29\MasterMachine.c

 Revision
   1.0.1

 Description
   This is a module implementing the master state machine for the nested
   state machine example.

 Notes

 History
 When           Who     What/Why
 -------------- ---     --------
 02/14/99 10:34 jec      Began Coding
****************************************************************************/
/*----------------------------- Include Files -----------------------------*/
#include "MasterMachine.h"
#include "FindingTape.h"
#include "TrackingTape.h"
#include "sm_general.h"

/*----------------------------- Module Defines ----------------------------*/
#define FINDING_TAPE_1 0
#define TRACKING_TAPE  1
#define FINDING_TAPE_2 2
#define STOP           3

#define NO_EVENT 0
#define HIT_TAPE 1
#define HIT_T    2

/*---------------------------- Module Functions ---------------------------*/
static unsigned char CheckEventsTape(void);
static unsigned char CheckEventsT(void);

/*---------------------------- Module Variables ---------------------------*/
static unsigned char CurrentState;
static unsigned char TapeFoundLastTime;
static unsigned char TFoundLastTime;

/*------------------------------ Module Code ------------------------------*/
/****************************************************************************
 Function
    MasterStateMachine

 Parameters
   None

 Returns
   None

 Description
   This is the top level state machine for the NestedCase.c example program.
 Notes
   uses nested switch/case to implement the machine even though there are only
   three states and a single event for each state.
 Author
   J. Edward Carryer, 2/15/99, 1:17PM
****************************************************************************/
void MasterStateMachine( void )
{
   unsigned char CurrentEvent;
   unsigned char NextState;

   switch ( CurrentState )
   {
       case FINDING_TAPE_1 :       // If current state is state one
         FindingTapeMachine();   //Execute During function for state one
         CurrentEvent = CheckEventsTape();   //Check for events
         if ( CurrentEvent != 0 )        //If an event is active
         {
            switch ( CurrentEvent)
            {
               case HIT_TAPE : //If event is event one
                  // Execute action function for state one : event one
                  NextState = TRACKING_TAPE;//Decide what the next state will be
                  break;
            }
            //   If next state is different from current state
            if ( NextState != CurrentState)
            {
                                       //Execute exit function for current state
               StartTrackingTapeMachine();//Execute entry function for new state
               CurrentState = NextState; //Modify state variable
             }
         }
         return;

       case TRACKING_TAPE :       // If current state is state one
         TrackingTapeMachine();   //Execute During function for state one
         CurrentEvent = CheckEventsT();   //Check for events
         if ( CurrentEvent != 0 )        //If an event is active
         {
            switch ( CurrentEvent)
            {
               case HIT_T : //If event is event one
                  // Execute action function for state one : event one
                  NextState = FINDING_TAPE_2;//Decide what the next state will be
                  break;
            }
            //   If next state is different from current state
            if ( NextState != CurrentState)
            {
               //   Execute exit function for current state
               StartFindingTapeMachine();// Execute entry function for new state
               TapeFoundLastTime = FALSE;// since we know we found it before
               CurrentState = NextState; //Modify state variable
             }
         }
         return;

       case FINDING_TAPE_2 :       // If current state is state one
         FindingTapeMachine();   //Execute During function for state one
         CurrentEvent = CheckEventsTape();   //Check for events
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
     StartMasterStateMachine

 Parameters
     None

 Returns
     None

 Description
     Does the initialization for the Master State machine
 Notes

 Author
     J. Edward Carryer, 2/18/99, 3:17PM
****************************************************************************/
void StartMasterStateMachine( void )
{
   CurrentState = FINDING_TAPE_1;
// call the (optional) entry fucntion for the ENTRY_STATE
   StartFindingTapeMachine();
// any other initialization necessary to re-start the state machine
   TapeFoundLastTime = FALSE;
   TFoundLastTime = FALSE;

}


/*------------------------------ Private Code ------------------------------*/
static unsigned char CheckEventsTape(void)
{
   unsigned char ThisEvent;
   unsigned char ReturnVal = NO_EVENT;

   // if input was in another state last time & in an active state this time
   if (((ThisEvent = IsTapeFound()) == TRUE) &&
         (TapeFoundLastTime == FALSE))//Check for events
       ReturnVal = HIT_TAPE;
   TapeFoundLastTime = ThisEvent;
   return ReturnVal;
}

static unsigned char CheckEventsT(void)
{
   unsigned char ThisEvent;
   unsigned char ReturnVal = NO_EVENT;

   // if input was in another state last time & in an active state this time
   if (((ThisEvent = IsTFound()) == TRUE) &&
         (TFoundLastTime == FALSE))//Check for events
       ReturnVal = HIT_T;
   TFoundLastTime = ThisEvent;
   return ReturnVal;
}

