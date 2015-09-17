/****************************************************************************
 Module
         tapestatus.h

 Description
         header file for the Tape Status Event Checker

 2/11/01 AHL
 ****************************************************************************/

unsigned char GetTapeStatus(void);

#define RIGHT_ON  1
#define LEFT_ON   2
#define BOTH_ON   3
#define BOTH_OFF   0

