#pragma once
#include <Audio.h>
//#include "Martone.h"
//=================
//Global Constants
//=================
// const int NUM_VOICES = 4;
// const int NUM_EFFECTS = 50;
// const int NUM_NOTES_STRING = 36; //rows on Livid Block Midi controller grid
// const int NUM_NOTES_INST = 64;   //number of notes in scale/instrument
// const int NUM_STRINGS = 4;
// const int MAX_DATA_LENGTH = 20; //for bluetooth data parsing
// const int LEDPIN = 13;
// const int BUFFER = 10; //Size of keyboard buffer
// const int NUM_CHARS = 32;
// const int NUM_OSC = 4;
// const int waveforms[] = {
//     WAVEFORM_SINE,
//     WAVEFORM_TRIANGLE,
//     WAVEFORM_TRIANGLE_VARIABLE,
//     WAVEFORM_SQUARE,
//     WAVEFORM_SAWTOOTH,
//     WAVEFORM_SAWTOOTH_REVERSE,
//     WAVEFORM_ARBITRARY,
//     WAVEFORM_PULSE,
//     WAVEFORM_SAMPLE_HOLD,
// };

// const float tuningArray[][NUM_NOTES_INST] =
// {
//                     //1        2.m2     3.M2     4.m3     5.M3     6.P4     7.Tri    8.P5     9.m6     10.M6    11.m7    12.M7
//   /*equal12Temp*/   {440.000, 466.163, 493.883, 523.251, 554.365, 587.329, 622.253, 659.255, 698.456, 739.988, 783.990, 830.609},   /*12 note chromatic*/
//   /*justTemp*/      {440.000, 469.333, 495,     528,     550,     586.666, 625.777, 660,     704,     733.333, 782.222, 825},       /*12 note Just Intonation Scale. pg 55*/
//   /*overtone16Temp*/{440.000, 467.5,   495,     522.5,   550, 577.5, 605,  632.5,   660, 687.5, 715, 742.5, 770, 797.5, 825, 852.5}, /*16 division overtone series*/
//   /*equal24Temp*/   {440.000, 452.892, 466.163, 479.823, 493.883, 508.355, 523.251, 538.583, 554.365, 570.609, 587.329, 604.538, 622.253, 640.487, 659.225, 678.572, 698.456, 718.992, 739.988, 761.672, 783.990, 806.963, 830.609, 854.948},   //24 division equal tempered
//   /*overtone8Temp*/ {440.000,          495.000,          550.000,    605,           660,        715,        770,        825} //8 division overtone series
// };

// const int scaleMask[][NUM_NOTES_STRING] =
// {
//   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},                               //chromatic
//   {1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1},                               //major scale
//   {1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1},                               //harmonic minor
//   {1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0},                               //pentatonic major
//   {1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0},                               //pentatonic minor
//   {1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0},                               //blues
//   {1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},                               //major chord
//   {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},                               //minor chord
//   {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0},                               //diminished chord
//   {1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0},                               //dominant 7 chord
//   {1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},                               //major 7 chord
//   {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0},                               //minor 7 chord
//   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},                   //overtone 16 division
//   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, //24 division equal tempered
//   {1, 1, 1, 1, 1, 1, 1, 1} //overtone 8 division
// };
// enum scales{chromatic,majScale,harmonicMinorScale,pentatonicMajorScale,pentatonicMinorScale,bluesScale,majChord,minChord,dimChord,dom7Chord,maj7Chord,min7Chord,overtone16Div,overtone24Div,overtone8Div};
// enum notes{A, Bb, B, C, Db, D, Eb, E, F, Gb, G, Ab};          //for printing names of notes
// enum temperaments{equal12Temp,justTemp,overtone16Temp,equal24Temp,overtone8Temp};

//===============================
//Global Variable Declarations
//===============================
// char bluetoothCharsArray[21];              //for bluetooth data parsing
// bool newBluetoothData;           //for bluetooth data parsing
// int string;
// float voice;                            //array for the notes to be assigned to one of 10 voices
// int noteCount;                         //when limit is reached, msg prints Voice Limit Exceeded!
// int scaleSteps2;
// int pressedMidi;
// bool adsrReleaseState[10];
// bool stringSelect;                  //for keyboard processing
// bool valueSelect;                   //for keyboard processing
// int parameter;                              //for keyboard processing
// int processKeyString;                       //for keyboard processing (string#)
// bool newData;                    //for parsing keyboard data in recvWithEndMarker() function. Used in keyboard control

// float dataNumber;                         //for parsing keyboard data in recvWithEndMarker() function. Used in keyboard control
// char receivedChars[NUM_CHARS];               // an array to store the received keyboard data. Keyboard control.
// int globalNote;
// int globalVelocity;
// int globalOffset;
// int globalString;
// int pIndex;                        //for mapping commands to parameters
// bool parameterSelect;
// float oldKnobValue;
// float low, high;                       //for range mapping
// float mappedKnobValue[NUM_STRINGS][NUM_EFFECTS];
// float rawKnobValue;
// int mstr;
// bool activeVoice[10];
// bool activeEffect[10];
// int activeEffectNote[24];
// bool lfoActive[10];

//============================
//Object Instantiations
//============================
//extern struct Martone str[4];
//extern Martone str[4];

//============================
//Struct Declarations
//============================
// struct Martone
// {
//     int stringOctave;
//     int stringStartNote;
//     int stringScale;

//     float stringVolume;
//     float stringfiltFreqCutoff;
//     float stringfiltRes;
//     float stringAttack;  //default 10.5ms. Max 11880
//     float stringDecay;   //default is 35ms. Max is 11880
//     float stringSustain; //0-1
//     float stringRelease; //default is 300ms. max is 11880
//     int stringLfoShape;
//     int stringLfoModeSelect;
//     float stringLfoSpeed;
//     float stringLfoDepth;
//     float stringLfoPitch;
//     float stringLfo;
//     float stringLfoRange;
   
//     float filterPercentage;
//     bool interpolate;
//     bool poly;
//     int tuningSelection;
//     int electrode3D;
// //*************************************************
//     int oscA;
//     float oscAInterval;
//     int oscADetune;

//     float oscAVolume;
//     float oscAfiltFreqCutoff;
//     float oscAfiltRes;
//     float oscAattack;  //default 10.5ms. Max 11880
//     float oscAdecay;   //default is 35ms. Max is 11880
//     float oscAsustain; //0-1
//     float oscArelease; //default is 300ms. max is 11880
//     int oscAlfoShape;
//     int oscAlfoModeSelect;
//     float oscAlfoSpeed;
//     float oscAlfoDepth;
//     float oscAlfoPitch;
//     float oscAlfo;
//     float oscAlfoRange;

//     int oscB;
//     float oscBInterval;
//     int oscBDetune;
//     float oscBVolume;
//     float oscBfiltFreqCutoff;
//     float oscBfiltRes;
//     float oscBattack;  //default 10.5ms. Max 11880
//     float oscBdecay;   //default is 35ms. Max is 11880
//     float oscBsustain; //0-1
//     float oscBrelease; //default is 300ms. max is 11880
//     int oscBlfoShape;
//     int oscBlfoModeSelect;
//     float oscBlfoSpeed;
//     float oscBlfoDepth;
//     float oscBlfoPitch;
//     float oscBlfo;
//     float oscBlfoRange;

//     int oscC;
//     int oscCInterval;
//     int oscCDetune;
//     float oscCVolume;
//     float oscCfiltFreqCutoff;
//     float oscCfiltRes;
//     float oscCattack;  //default 10.5ms. Max 11880
//     float oscCdecay;   //default is 35ms. Max is 11880
//     float oscCsustain; //0-1
//     float oscCrelease; //default is 300ms. max is 11880
//     int oscClfoShape;
//     int oscClfoModeSelect;
//     float oscClfoSpeed;
//     float oscClfoDepth;
//     float oscClfoPitch;
//     float oscClfo;
//     float oscClfoRange;

//     float oscNVolume;
//     float oscNfiltFreqCutoff;
//     float oscNfiltRes;
//     float oscNattack;  //default 10.5ms. Max 11880
//     float oscNdecay;   //default is 35ms. Max is 11880
//     float oscNsustain; //0-1
//     float oscNrelease; //default is 300ms. max is 11880
//     int oscNlfoShape;
//     int oscNlfoModeSelect;
//     float oscNlfoSpeed;
//     float oscNlfoDepth;
//     float oscNlfoPitch;
//     float oscNlfo;
//     float oscNlfoRange;
// };

