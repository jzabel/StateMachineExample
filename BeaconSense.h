unsigned char GetBeaconAmpLeft(void);
unsigned char GetBeaconAmpRight(void);
unsigned char LeftEqualRight( void );
int GetSensorDiff( void );

// threshold to detect equal
#define EQUAL_THRESH  3
// minimum sensor reading to detect a peak or equal
#define MIN_SENSE 2

