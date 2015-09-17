
//#define TESTING
/****************************************************************************
 Module
          tapestatus.c

 Description
          Event Checker for Tape Sensors

 Notes
          This configuration uses 3 tape sensors.
          Returns a sign signal

****************************************************************************/


unsigned char GetTapeStatus(void)
{
   TapeStatus = _H12PORTDLC & BOTH_HI

   return;
}
