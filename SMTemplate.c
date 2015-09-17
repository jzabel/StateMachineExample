/****************************************************************************
 Module
   d:\me218b\Lectures\Lecture 29\SMTemplate.c

 Description
   This is a template file for implementing state machines.

 Notes

 History
 When           Who     What/Why
 -------------- ---     --------
 02/20/03 10:31 jec      converted to use an external event checker with
                         events passed into the the RunStateMachine function
 02/18/99 10:19 jec      built template from MasterMachine.c
 02/14/99 10:34 jec      Began Coding
****************************************************************************/
/*----------------------------- Include Files -----------------------------*/
/* include header files for this state machine as well as any machines at the
   next lower level in the hierarchy that are sub-machines to this machine
*/

/*----------------------------- Module Defines ----------------------------*/
// define constants for the states and event for this machine

/*---------------------------- Module Functions ---------------------------*/
/* prototypes for private functions for this machine, things like entry & exit
   functions.*/
/*---------------------------- Module Variables ---------------------------*/
// everybody needs a state variable, you may need others as well
static unsigned char CurrentState;

/*------------------------------ Module Code ------------------------------*/
/****************************************************************************
 Function
    RunStateMachine

 Parameters
   None

 Returns
   None

 Description
   add your description here
 Notes
   uses nested switch/case to implement the machine.
 Author
   J. Edward Carryer, 2/15/99, 1:17PM
****************************************************************************/
void RunStateMachine( unsigned char CurrentEvent )
{
      unsigned char NextState;

   switch ( CurrentState )
   {
       case STATE_ONE :       // If current state is state one
         DuringStateOne();   //Execute During function for state one
         if ( CurrentEvent != NO_EVENT )        //If an event is active
         {
            switch ( CurrentEvent)
            {
               case EVENT_ONE : //If event is event one
                  // Execute action function for state one : event one
                  NextState = STATE_TWO;//Decide what the next state will be
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

       case STATE_TWO :       // If current state is state one
         DuringStateTwo();   //Execute During function for state one
         if ( CurrentEvent != NO_EVENT )        //If an event is active
         {
            switch ( CurrentEvent)
            {
               case EVENT_TWO : //If event is event one
                  // Execute action function for state one : event one
                  NextState = STATE_THREE;//Decide what the next state will be
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

       case STATE_THREE :       // If current state is state one
         DuringStateThree();   //Execute During function for state one
         CurrentEvent = CheckEventsStateThree();   //Check for events
         if ( CurrentEvent != 0 )        //If an event is active
         {
            switch ( CurrentEvent)
            {
               case EVENT_THREE : //If event is event one
                  // Execute action function for state one : event one
                  NextState = STATE_FOUR;//Decide what the next state will be
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
     StartStateMachine

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
void StartStateMachine ( void )
{
   CurrentState = ENTRY_STATE;
// call the (optional) entry fucntion for the ENTRY_STATE
// any other initialization necessary to re-start the state machine
}

