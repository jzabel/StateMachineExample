  #include "BeaconSense.h"
#include "sm_general.h"

unsigned char LeftEqualRight( void )
{
   unsigned char LeftVal = GetBeaconAmpLeft();
   unsigned char RightVal = GetBeaconAmpRight();
   int Difference = LeftVal - RightVal;

   if ( Difference < 0)
      Difference *= -1;

 // check for approximately equal readings
   if ( (LeftVal > MIN_SENSE) && (RightVal > MIN_SENSE) &&
        (Difference < EQUAL_THRESH))
      return TRUE;
   else
      return FALSE;
}

int GetSensorDiff( void )
{
   unsigned char LeftVal = GetBeaconAmpLeft();
   unsigned char RightVal = GetBeaconAmpRight();
   int Difference = LeftVal - RightVal;

   return Difference;
}

unsigned char GetBeaconAmpLeft( void )
{
   return 0;                            // just for trial compile
}

unsigned char GetBeaconAmpRight( void )
{
   return 0;                            // just for trial compile
}

