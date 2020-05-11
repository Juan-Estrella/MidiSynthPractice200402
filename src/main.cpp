/*
     The Program:
       -Uses MIDI Controller plugged into Teensy 3.6  to trigger notes.
       -Alternatively, the letter 'a' on the qwerty keyboard can trigger a note by sending a MIDI 'Note On' message for debugging.
       -And the letter 's' sends MIDI 'Note Off'.
       -Program was written on Microsoft Visual Studio Code, with PlatformIO extension.
       -All controls can be selected via qwerty input and modified with a potentiometer.
       -4 simultaneous oscillators per note, each with separate waveforms(9), LFOs, envelopes, filters, and settings.
       -9 LFO shapes selectable, each with adjustable slope, depth, speed, and height.
       -USB MIDI note allocation to voice number method.
       -LFO functionality is defined in LfoUpdate.cpp file in the src folder.
       -Most other functions are defined in 'Martone.cpp' file src folder.
       -Teensy specific settings (Serial port, baud Rate, etc. are defined in the platform.ini file.)
       -'GuiTool.cpp' contains the code exported from the Teensy Audio Library. (See link below).
       -(Currently I only have 1 note enabled (A440), bc I'm working on modulation and vocal formants, (i.e. LFOs and Filters) not melody.)
     The Circuit:
       -USB Midi controller plugged into USB host port jack on on Teensy 3.6
       -Teensy Audio Shield plugged on top of Teensy.
       -10k pot connected to 'A1' on Teensy. (I'm using a thumbwheel that I soldered onto the Audio Shield. See Teensy Audio Workshop below.)
       -The pot modifies different parameters (attack, volume, filter, etc.), depending on which parameter is selected via qwerty input.
     References:
       -  https://forum.pjrc.com/threads/41862-MIDI-notes-to-trigger-Audio-Board-synth?highlight=polyphony 'Seenthysizer' Polyphony example
       -  https://www.youtube.com/watch?v=evVRCL9-TWs  'Create a Bluetooth App and control the Arduino.'
       -  http://www.martyncurrey.com/arduino-hm-10-and-app-inventor-2-adding-a-slider/ Adding a Slider to MIT App Inventor. 
       -  https://www.youtube.com/watch?v=zphkBTkOIyQ Notes and Volts Part 8 LFO
       -  https://www.youtube.com/watch?v=IoADj8dvTQc Notes and Volts Part 3 Keyboard
       -  https://github.com/k2rek/martone-prototype/blob/master/Final%20Prototype/main/main.ino  Martone V1 code. Kyle Tworek
       -  https://www.pjrc.com/store/audio_tutorial_kit.html Teensy Audio Workshop
       -  https://www.pjrc.com/teensy/gui/ Teensy Audio Library
     Author(s):
       Juan Estrella
*/

//=========
//Libraries
//=========
#include <Arduino.h>
#include <Audio.h>
#include <USBHost_t36.h>
#include "Martone.h"

//================
//Global Constants
//================
const int NUM_STRINGS = 4;

//=====================
//Object Instantiations
//=====================
USBHost myusb;
USBHub hub1(myusb);
USBHub hub2(myusb);
MIDIDevice midi1(myusb);
Martone martone;

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
 /*      -Selectable Waveforms- 
    WAVEFORM_SINE,               //0
    WAVEFORM_SAWTOOTH,           //1
    WAVEFORM_SQUARE,             //2
    WAVEFORM_TRIANGLE,           //3
    WAVEFORM_ARBITRARY,          //4
    WAVEFORM_PULSE,              //5
    WAVEFORM_SAWTOOTH_REVERSE,   //6
    WAVEFORM_SAMPLE_HOLD,        //7
    WAVEFORM_TRIANGLE_VARIABLE,  //8 
 */

/*    -Selectable LFO Modes-
 0 = LFO Off
 1 = LFO Sine Repeating
 2 = LFO Cosine Repeating
 3 = LFO Exponential. Rising. Repeating.
 4 = LFO Exponential. Falling. Repeating.
 5 = LFO Exponential. Rising. 1 Shot. Sustained.
 6 = LFO Exponential. Rising. 1 Shot. Stopped.
 7 = LFO Exponential. Falling. 1 Shot. Stopped.
 8 = LFO Sine. 1 Shot. Stopped.
 9 = LFO Cosine. 1 Shot. Stopped.
*/

  //********************Oscillator Set Up********************
  //String 1. string, osc, volume, waveform, freq, freqCut, filtSlope, filtRes, lfoMode, lfoSpeed, lfoFrSlope, lfoBckSlope, lfoRange, lfoDepth, lfoFilt%                  
  martone.SetOsc(1,   1,  .2,      1,        220,  10000,   1.9,       1,        1,       7000,     1.5,        1.5,         1,        0,        1);    
  martone.SetOsc(1,   2,  .2,       2,        440,  10000,   1.9,       1,       2,       3000,     1.5,        1.5,         1,        0,        1);          
  martone.SetOsc(1,   3,  .2,       3,        880,  10000,   1.9,       1,       0,       7000,     1.5,        1.5,         1,        0,        1);          
  martone.SetOsc(1,   4,  .7,       3,        990,  10000,   1.9,       1,      0,       7000,     1.5,        1.5,         1,        0,        1);     

  //String 2. string, osc, volume, waveform, freq, freqCut, filtSlope. filtRes                  
  martone.SetOsc(2,   1,  .5,      1,        220,  10000,   1.9,       1,       0,       7000,     1.5,        1.5,         1,        0,        1);      
  martone.SetOsc(2,   2,  .0,      1,        440,  10000,   1.9,       1,       0,       7000,     1.5,        1.5,         1,        0,        1);         
  martone.SetOsc(2,   3,  .0,      1,        880,  10000,   1.9,       1,       0,       7000,     1.5,        1.5,         1,        0,        1);         
  martone.SetOsc(2,   4,  .8,      1,       1000,  10000,   1.9,       1,       0,       7000,     1.5,        1.5,         1,        0,        1);       

  //String 3. string, osc, volume, waveform, freq, freqCut, filtSlope, filtRes                  
  martone.SetOsc(3,   1,  .9,      3,        220,  10000,   1.9,       1,       0,       7000,     1.5,        1.5,         1,        0,        1);         
  martone.SetOsc(3,   2,  .11,     7,        440,  10000,   1.9,       1,       0,       7000,     1.5,        1.5,         1,        0,        1);          
  martone.SetOsc(3,   3,  .22,     1,        880,  10000,   1.9,       1,       0,       7000,     1.5,        1.5,         1,        0,        1);          
  martone.SetOsc(3,   4,  .33,     5,       1660,  10000,   1.9,       1,       0,       7000,     1.5,        1.5,         1,        0,        1);       

  //String 4. string, osc, volume, waveform, freq, freqCut, filtSlope, filtRes                  
  martone.SetOsc(4,   1,  .44,     4,        220,  10000,   1.9,       1,       0,       7000,     1.5,        1.5,         1,        0,        1);           
  martone.SetOsc(4,   2,  .55,     8,        440,  10000,   1.9,       1,       0,       7000,     1.5,        1.5,         1,        0,        1);             
  martone.SetOsc(4,   3,  .66,     2,        880,  10000,   1.9,       1,       0,       7000,     1.5,        1.5,         1,        0,        1);        
  martone.SetOsc(4,   4,  .69,     7,       1660,  10000,   1.9,       1,       0,       7000,     1.5,        1.5,         1,        0,        1);                         

//********************String Set Up*************************
//              string, octave, startnote,  scale,                     vol, filtCutoff, filtRes, attack, decay, sustain, release, lfoShape, lfoMode, lfoSpeed, lfoDepth, lfoPitch, lfo, lfoRange, filtPercent, interpolate, poly, temperament,    electrode3D
  martone.SetString(1, -2,      martone.A,  martone.minChord,          .9,  10000,      0,       25,     35,    1,       2500,    1,        0,       2000,     0,        1,        0,   0,        1,           false,       true,  martone.justTemp,   0);
  martone.SetString(2,  0,      martone.A,  martone.harmonicMinorScale,.8,  10000,      0,       50,     25,    1,       100,     1,        0,       7000*0.7, 0,        1,        0,   0,        1,           false,       true,  martone.justTemp,   0);
  martone.SetString(3, -3,      martone.A,  martone.chromatic,         .9,  700,        1,       .1,     35,    1,       40,      1,        1,       7000*0.7, 0,        1,        0,   0,        1,           false,       true,  martone.justTemp,   0);
  martone.SetString(4, -3,      martone.A,  martone.dimChord,          .6,  2000,       1,       .25,    35,    1,       50,      1,        0,       2000,     1,        1,        0,   0,        1,           false,       false, martone.justTemp,   0);

  martone.Initialize();
  myusb.begin();
  midi1.setHandleNoteOn(MyNoteOn); 
  midi1.setHandleNoteOff(MyNoteOff);
}

//=======================
//Loop. Run Over and Over
//=======================
void loop()
{
  martone.Update();
  myusb.Task();
  midi1.read();  
}

//=============================
//Callback Function Definitions
//=============================
void MyNoteOn(unsigned char channel, unsigned char note, unsigned char velocity)
{
  martone.HandleNoteOn(channel, note, velocity);
  Serial.println("Note on");
}

void MyNoteOff(unsigned char channel, unsigned char note, unsigned char velocity)
{
  martone.HandleNoteOff(channel, note, velocity);
  Serial.println("Note off");
}

// :~)