#pragma once
//=================
//Global Constants
//=================
const int NUM_VOICES = 10;
const int NUM_EFFECTS = 50;
const int NUM_NOTES_STRING = 36; //rows on Livid Block Midi controller grid
const int NUM_NOTES_INST = 64;   //number of notes in scale/instrument
const int NUM_STRINGS = 4;
const int MAX_DATA_LENGTH = 20; //for bluetooth data parsing
const int LEDPIN = 13;
const int BUFFER = 10; //Size of keyboard buffer
const int waveforms[] = {
    WAVEFORM_SINE,
    WAVEFORM_TRIANGLE,
    WAVEFORM_TRIANGLE_VARIABLE,
    WAVEFORM_SQUARE,
    WAVEFORM_SAWTOOTH,
    WAVEFORM_SAWTOOTH_REVERSE,
    WAVEFORM_ARBITRARY,
    WAVEFORM_PULSE,
    WAVEFORM_SAMPLE_HOLD,
};

//===============================
//Global Variable Declarations
//===============================
char bluetoothCharsArray;              //for bluetooth data parsing
boolean newBluetoothData;           //for bluetooth data parsing
int string;
float voice;                            //array for the notes to be assigned to one of 10 voices
byte noteCount;                         //when limit is reached, msg prints Voice Limit Exceeded!
int scaleSteps2;
int pressedMidi;
bool adsrReleaseState[10];
bool stringSelect;                  //for keyboard processing
bool valueSelect;                   //for keyboard processing
int parameter;                              //for keyboard processing
int processKeyString;                       //for keyboard processing (string#)
boolean newData;                    //for parsing keyboard data in recvWithEndMarker() function. Used in keyboard control
const byte numChars;
float dataNumber;                         //for parsing keyboard data in recvWithEndMarker() function. Used in keyboard control
char receivedChars;               // an array to store the received keyboard data. Keyboard control.
byte globalNote;
byte globalVelocity;
int globalOffset;
int globalString;
int pIndex;                        //for mapping commands to parameters
bool parameterSelect;
float oldKnobValue;
float low, high;                       //for range mapping
float mappedKnobValue[NUM_STRINGS][NUM_EFFECTS];
float rawKnobValue;
int str;
bool activeVoice[10];
bool activeEffect[10];
int activeEffectNote[24];
bool lfoActive[10];
AudioEffectEnvelope *adsrArray[];

//============================
//Struct Declarations
//============================
struct martone
{
    int stringOctave;
    int stringStartNote;
    int stringScale;

    float stringVolume;
    float stringfiltFreqCutoff;
    float stringfiltRes;
    float stringAttack;  //default 10.5ms. Max 11880
    float stringDecay;   //default is 35ms. Max is 11880
    float stringSustain; //0-1
    float stringRelease; //default is 300ms. max is 11880
    int stringLfoShape;
    int stringLfoModeSelect;
    float stringLfoSpeed;
    float stringLfoDepth;
    float stringLfoPitch;
    float stringLfo;
    float stringLfoRange;
   
    float filterPercentage;
    bool interpolate;
    bool poly;
    int tuningSelection;
    int electrode3D;
//*************************************************
    int oscA;
    float oscAInterval;
    int oscADetune;
    float oscAVolume;
    float oscAfiltFreqCutoff;
    float oscAfiltRes;
    float oscAattack;  //default 10.5ms. Max 11880
    float oscAdecay;   //default is 35ms. Max is 11880
    float oscAsustain; //0-1
    float oscArelease; //default is 300ms. max is 11880
    int oscAlfoShape;
    int oscAlfoModeSelect;
    float oscAlfoSpeed;
    float oscAlfoDepth;
    float oscAlfoPitch;
    float oscAlfo;
    float oscAlfoRange;

    int oscB;
    float oscBInterval;
    int oscBDetune;
    float oscBVolume;
    float oscBfiltFreqCutoff;
    float oscBfiltRes;
    float oscBattack;  //default 10.5ms. Max 11880
    float oscBdecay;   //default is 35ms. Max is 11880
    float oscBsustain; //0-1
    float oscBrelease; //default is 300ms. max is 11880
    int oscBlfoShape;
    int oscBlfoModeSelect;
    float oscBlfoSpeed;
    float oscBlfoDepth;
    float oscBlfoPitch;
    float oscBlfo;
    float oscBlfoRange;

    int oscC;
    int oscCInterval;
    int oscCDetune;
    float oscCVolume;
    float oscCfiltFreqCutoff;
    float oscCfiltRes;
    float oscCattack;  //default 10.5ms. Max 11880
    float oscCdecay;   //default is 35ms. Max is 11880
    float oscCsustain; //0-1
    float oscCrelease; //default is 300ms. max is 11880
    int oscClfoShape;
    int oscClfoModeSelect;
    float oscClfoSpeed;
    float oscClfoDepth;
    float oscClfoPitch;
    float oscClfo;
    float oscClfoRange;

    float oscNVolume;
    float oscNfiltFreqCutoff;
    float oscNfiltRes;
    float oscNattack;  //default 10.5ms. Max 11880
    float oscNdecay;   //default is 35ms. Max is 11880
    float oscNsustain; //0-1
    float oscNrelease; //default is 300ms. max is 11880
    int oscNlfoShape;
    int oscNlfoModeSelect;
    float oscNlfoSpeed;
    float oscNlfoDepth;
    float oscNlfoPitch;
    float oscNlfo;
    float oscNlfoRange;
};