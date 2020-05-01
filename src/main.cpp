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
 /* WAVEFORM_SINE,               //0
    WAVEFORM_SAWTOOTH,           //1
    WAVEFORM_SQUARE,             //2
    WAVEFORM_TRIANGLE,           //3
    WAVEFORM_ARBITRARY,          //4
    WAVEFORM_PULSE,              //5
    WAVEFORM_SAWTOOTH_REVERSE,   //6
    WAVEFORM_SAMPLE_HOLD,        //7
    WAVEFORM_TRIANGLE_VARIABLE,  //8 
 */

  //********************Oscillator Set Up********************
  //String 1. string, osc, volume, waveform, freq, freqCut, filtSlope, filtRes                  
  martone.SetOsc(1,   1,  .5,      1,        220,  10000,   1.9,      1);    
  martone.SetOsc(1,   2,  0,       5,        440,  10000,   1.9,      1);       
  martone.SetOsc(1,   3,  0,       9,        880,  10000,   1.9,      1);        
  martone.SetOsc(1,   4,  0,       3,        990,  10000,   1.9,      1);   

  //String 2. string, osc, volume, waveform, freq, freqCut, filtSlope. filtRes                  
  martone.SetOsc(2,   1,  .5,      2,        220,  10000,   1.9,      1);    
  martone.SetOsc(2,   2,  .6,      6,        440,  10000,   1.9,      1);      
  martone.SetOsc(2,   3,  .7,      0,        880,  10000,   1.9,      1);       
  martone.SetOsc(2,   4,  .8,     4,       1000,  10000,   1.9,      1);     

  //String 3. string, osc, volume, waveform, freq, freqCut, filtSlope, filtRes                  
  martone.SetOsc(3,   1,  .9,      3,      220,  10000,   1.9,      1);       
  martone.SetOsc(3,   2,  .11,      7,      440,  10000,   1.9,      1);        
  martone.SetOsc(3,   3,  .22,     1,      880,  10000,   1.9,      1);        
  martone.SetOsc(3,   4,  .33,      5,     1660,  10000,   1.9,      1);     

  //String 4. string, osc, volume, waveform, freq, freqCut, filtSlope, filtRes                  
  martone.SetOsc(4,   1,  .44,      4,      220,  10000,   1.9,      1);         
  martone.SetOsc(4,   2,  .55,      8,      440,  10000,   1.9,      1);          
  martone.SetOsc(4,   3,  .66,     2,      880,  10000,   1.9,      1);      
  martone.SetOsc(4,   4,  .69,      7,     1660,  10000,   1.9,      1);                       

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
  if (Serial.available())
  {
    char ch = Serial.read();
    if (ch == 'a')
    {

      MyNoteOn(1, 1, 1);
      Serial.println("Keyboard Entry");
    }
    if (ch == 's')
    {
      MyNoteOff(1, 1, 1);
      Serial.println("Keyboard Entry");
    }
  }
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