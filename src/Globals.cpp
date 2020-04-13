#include "Globals.h"

struct martone str[4]
{         //.stringVolume .osc1 .osc1Volume .startNote .scale .octave .osc2 .osc2Interval .osc2Detune .osc2Volume .osc3 .osc3nterval .osc3Detune .osc3Volume  
/*string1*/   {1,       2,             3,           4},  
/*string2*/   {5,       200,           7,           8}    
};


//===============================
//Global Variable Initializations
//===============================
char bluetoothCharsArray[21] ;              //for bluetooth data parsing
boolean newBluetoothData = false;           //for bluetooth data parsing
int string = 0;
float voice[10];                            //array for the notes to be assigned to one of 10 voices
byte noteCount = 0;                         //when limit is reached, msg prints Voice Limit Exceeded!
int scaleSteps2 = 0;
int pressedMidi[10];
bool adsrReleaseState[10] = {false};
bool stringSelect = false;                  //for keyboard processing
bool valueSelect = false;                   //for keyboard processing
int parameter;                              //for keyboard processing
int processKeyString;                       //for keyboard processing (string#)
boolean newData = false;                    //for parsing keyboard data in recvWithEndMarker() function. Used in keyboard control
const byte numChars = 32;
float dataNumber = 0;                         //for parsing keyboard data in recvWithEndMarker() function. Used in keyboard control
char receivedChars[numChars];               // an array to store the received keyboard data. Keyboard control.
byte globalNote;
byte globalVelocity;
int globalOffset;
int globalString;
int pIndex = 0;                        //for mapping commands to parameters
bool parameterSelect = false;
float oldKnobValue;
float low, high;                       //for range mapping
float mappedKnobValue[NUM_STRINGS][NUM_EFFECTS] = {0};
float rawKnobValue;
int str = 0;
bool activeVoice[10] = {false};
bool activeEffect[10] = {false};
int activeEffectNote[24] = {0};
bool lfoActive[10] = {false};
AudioEffectEnvelope *adsrArray[10] =
{
  &ADSR1, &ADSR2, &ADSR3, &ADSR4, &ADSR5,
  &ADSR6, &ADSR7, &ADSR8, &ADSR9, &ADSR10
};