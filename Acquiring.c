/****************************************************************************
 Module
   d:\me218b\Lectures\Lecture 29\Acquiring.c

 Revision
   1.0.1

 Description
   This is the Acquiring state machine for the nested case example.

 Notes

  History
  When              Who         What/Why
  ----------------- ---         --------
   02/19/99 20:34   jec         Began coding
 ***************************************************************************/
/*----------------------------- Include Files -----------------------------*/
/* include header files for this state machine as well as any machines at the
   next lower level in the hierarchy that are sub-machines to this machine
*/
#include "Acquiring.h"
#include "Motor.h"
#include "BeaconSense.h"
#include "sm_general.h"
/*----------------------------- Module Defines ----------------------------*/
// define constants for the states and event for this machine
//event constants should start with 1 so that you can use 0 as "No Events"
//The states
#define SPINNING_CW   0
#define SPINNING_CCW  1
#define ACQUIRED      2
// The Events
#define NO_EVENT  0
#define LEFT_PEAK 1
#define L_EQ_R    2

// threshold to detect peak
#define PEAK_THRESH  3
#define MIN_AMP 2
// number of samples in amp array
#define SENSE_SIZE 5

/*---------------------------- Module Functions ---------------------------*/
//prototypes for private functions for this machine, things liek event
//checkers, entry & exit functions.  they should be functions relevant to the
//behavior of this state machine

unsigned char CheckLeftPeak( void );
unsigned char CheckBothSame( void );

/*---------------------------- Module Variables ---------------------------*/
// everybody needs a state variable, you may need others as well
static unsigned char CurrentState;
static unsigned char Sense[SENSE_SIZE];
static unsigned char EqualFoundLastTime;
static unsigned char PeakFoundLastTime;
/*------------------------------ Module Code ------------------------------*/
/****************************************************************************
 Function
    AcquiringMachine

 Parameters
   None

 Returns
   None

 Description
   implements the Acquiring state machine
 Notes
   uses nested switch/case to implement the machine.
 Author
   J. Edward Carryer, 2/19/99, 10:00PM
****************************************************************************/
void AcquiringMachine( void )
{
   unsigned char CurrentEvent;
   unsigned char NextState;

   switch ( CurrentState )
   {
       case SPINNING_CW :        // If current state is state one
                                 //Execute During function for state one
         CurrentEvent = CheckLeftPeak();   //Check for events
         if ( CurrentEvent != 0 )        //If an event is active
         {
            switch ( CurrentEvent)
            {
               case LEFT_PEAK : //If event is event one
                  // Execute action function for state one : event one
                  NextState = SPINNING_CCW;//Decide what the next state will be
                  break;
            }
            //   If next state is different from current state
            if ( NextState != CurrentState)
            {
               MotorDrive(SPIN_CCW, SLOW);// Execute exit function for current state
               //   Execute entry function for new state
               CurrentState = NextState; //Modify state variable
             }
         }
         return;

       case SPINNING_CCW :       // If current state is state one
                                 //Execute During function for state one
         CurrentEvent = CheckBothSame();   //Check for events
         if ( CurrentEvent != 0 )        //If an event is active
         {
            switch ( CurrentEvent)
            {
               case L_EQ_R : //If event is event one
                  // Execute action function for state one : event one
                  NextState = ACQUIRED;//Decide what the next state will be
                  break;
            }
            //   If next state is different from current state
            if ( NextState != CurrentState)
            {
               MotorDrive(FORWARD, STOP);// Execute exit function for current state
               //   Execute entry function for new state
               CurrentState = NextState; //Modify state variable
             }
         }
         return;
    }
}
/****************************************************************************
 Function
     StartAcquiringMachine

 Parameters
     None

 Returns
     None

 Description
     Does any required initialization for this state machine
 Notes

 Author
     J. Edward Carryer, 2/19/99, 10:01PM
****************************************************************************/
void StartAcquiringMachine ( void )
{
   unsigned char i;

   CurrentState = SPINNING_CW;
   MotorDrive(SPIN_CW, MED_FAST);// call the entry function for the ENTRY_STATE
// any other initialization necessary to re-start the state machine
   EqualFoundLastTime = FALSE;
   PeakFoundLastTime = FALSE;
   for ( i=0; i < SENSE_SIZE; i++)
      Sense[i] = 0;            // clear amplitude array
}

/****************************************************************************
 Function
     IsBeaconAcquired

 Parameters
     None

 Returns
     unsigned char

 Description
     determines if the beacon has been acquired by looking at whether or
     not we are in the Acquired state
 Notes

 Author
     J. Edward Carryer, 2/20/99, 2:56PM
****************************************************************************/
unsigned char IsBeaconAcquired( void )
{
   return (CurrentState == ACQUIRED);
}
/*------------------------------ Private Code ------------------------------*/
static unsigned char CheckLeftPeak(void)
{
   unsigned char ThisEvent;
   unsigned char ReturnVal;
   unsigned char i;

   for ( i=1; i < SENSE_SIZE; i++)
      Sense[i-1] = Sense[i];            // shift readings by one
   Sense[i-1] = GetBeaconAmpLeft();   // add new reading to array
 // chek for a peak in the readings
   if ( (Sense[0] > MIN_SENSE) && ((Sense[2] - Sense[0]) > PEAK_THRESH) &&
        (Sense[4] > MIN_SENSE) && ((Sense[2] - Sense[4]) > PEAK_THRESH))
      ThisEvent = TRUE;
   else
      ThisEvent = FALSE;
// if input was in another state last time & in an active state this time
   if ((ThisEvent == TRUE) &&
         (PeakFoundLastTime == FALSE))//Check for events
       ReturnVal = LEFT_PEAK;
   else
       ReturnVal = NO_EVENT;
   PeakFoundLastTime = ThisEvent;
   return ReturnVal;
}

static unsigned char CheckBothSame(void)
{
   unsigned char ThisEvent;
   unsigned char ReturnVal;
// if input was in another state last time & in an active state this time
   if ((ThisEvent == TRUE) &&
         (EqualFoundLastTime == FALSE))//Check for events
       ReturnVal = L_EQ_R;
   else
       ReturnVal = NO_EVENT;
   EqualFoundLastTime = ThisEvent;
   return ReturnVal;
}


