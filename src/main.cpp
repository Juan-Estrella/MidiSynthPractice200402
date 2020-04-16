/*
     The Program:
       -Displays Note, Octave, MIDI #, Channel, and Velocity of MIDI note input.
       -USB MIDI note allocation to voice number method
        The Circuit:
       -USB Midi controller plugged into USB host port jack on on Teensy 3.6
     References:
       -  https://forum.pjrc.com/threads/41862-MIDI-notes-to-trigger-Audio-Board-synth?highlight=polyphony
       -  https://www.youtube.com/watch?v=evVRCL9-TWs  'Create a Bluetooth App and control the Arduino.'
       -  http://www.martyncurrey.com/arduino-hm-10-and-app-inventor-2-adding-a-slider/
       -  https://www.youtube.com/watch?v=zphkBTkOIyQ Notes and Volts Part 8 LFO
       -  https://www.youtube.com/watch?v=IoADj8dvTQc Notes and Volts Part 3 Keyboard
       -  https://github.com/k2rek/martone-prototype/blob/master/Final%20Prototype/main/main.ino  Martone V1 code. K. Tworek
     Author(s):
       Juan Estrella
*/

//=========
//Libraries
//=========
#include <Arduino.h>
#include <Audio.h>
#include <USBHost_t36.h>
//#include "Functions.h"
//#include "GuiTool.h"
//#include "LfoUpdate.h"
//#include "Globals.h"
#include "Martone.h"

//=====================
//Object Instantiations
//=====================
USBHost myusb;
USBHub hub1(myusb);
USBHub hub2(myusb);
MIDIDevice midi1(myusb);
Martone martone;

//=======================
//Initial String Settings
//=======================
Martone str[4]
{//                  waveform, octave, startnote, scale, volume, filtFreqCutoff, filtRes, attack, decay, sustain, release, lfoShape, lfoModeSelect, lfoSpeed, lfoDepth, lfoPitch, lfo, lfoRange, filtPercent, interpolate, poly, temperament, electrode3D
  /*string 1*/ Martone( 0,    -2,  str[0].A, str[0].minChord, .9,      10000,       0,      25,     35,    1,       2500,    1,        0,             2000,     0,        1,        0,   0,        1,           false,       true, str[0].justTemp,   0),
  /*string 2*/ Martone( 1,     0,  str[1].A, str[1].harmonicMinorScale,.8,  10000,  0,      50,     25,    1,       100,     1,        0,             7000*0.7, 0,        1,        0,   0,        1,           false,       true, str[1].justTemp,   0),
  /*string 3*/ Martone( 2,    -3,  str[2].A, str[2].chromatic, .9,     700,         1,      .1,     35,    1,       40,      1,        1,             7000*0.7, 0,        1,        0,   0,        1,           false,       true, str[2].justTemp,   0),
  /*string 4*/ Martone( 3,    -3,  str[3].A, str[3].dimChord,.6,       2000,        1,      .25,    35,    1,       50,      1,        0,             2000,     1,        1,        0,   0,        1,           false,       false,str[3].justTemp,   0),
};

//================
//Global Variables
//================


Martone *pStr[4] = {&str[0], &str[1], &str[2], &str[3]};


//==============================
//Callback Function Declarations
//==============================
void MyNoteOn(unsigned char channel, unsigned char note, unsigned char velocity);
void MyNoteOff(unsigned char channel, unsigned char note, unsigned char velocity);

//================
//Set Up. Run Once
//================
void setup()
{
  martone.Initialize();
  myusb.begin();
  midi1.setHandleNoteOn(MyNoteOn); 
  midi1.setHandleNoteOff(MyNoteOff);
  //Serial.println(pStr[3]->m_octave);
}

//=======================
//Loop. Run Over and Over
//=======================
void loop()
{
  martone.Update(pStr, 4);
  myusb.Task();
  midi1.read();  
  //LfoUpdate(false, sp.lfoModeSelect[2], sp.filterPercentage[2], sp.lfoDepth[2], 2);
}

//=============================
//Callback Function Definitions
//=============================
void MyNoteOn(unsigned char channel, unsigned char note, unsigned char velocity)
{
  martone.HandleNoteOn(channel, note, velocity);
  Serial.println("Note on");
  //LfoUpdate(true, sp.lfoModeSelect[string], sp.filterPercentage[string], sp.lfoDepth[string], string);
}

void MyNoteOff(unsigned char channel, unsigned char note, unsigned char velocity)
{
  martone.HandleNoteOff(channel, note, velocity);
  Serial.println("Note off");
}

// :~)