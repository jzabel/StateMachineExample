/***********************************************************
 *
 *   Program:    NestedCase.c
 *   Created:    2/13/99 8:29PM
 *   Author:     J. Edward Carryer
 *   Requested:
 *   Comments:   An example program to demonstrate nesting of state machines.
 *
 ************************************************************
 *
 * History:
 *2/13/99 8:30PM started coding
 *
 * $Log:$
 *
 ************************************************************/

#include "MasterMachine.h"
#include "Timer.h"

void main(void)
{
   TMR_Init(TMR_RATE_4MS);              // start the timer sub-system
   StartMasterStateMachine();
   while ( 1 )
   {
       MasterStateMachine();
   }
}


