#include <Arduino.h>
#include <Audio.h>
#include <USBHost_t36.h>
#include "Globals.h"
#include "GuiTool.h"
#include "LfoUpdate.h"
#include "Martone.h"

void Martone::LfoUpdate(bool retrig, u8 mode, float FILtop, float FILbottom, u8 m_str, u8 m_osc)
{
  static double localLFO[][m_NUM_OSC] = {0};
  static unsigned long lfoTime[][m_NUM_OSC] = {0};
  static u8 lfoDirection[m_NUM_STRINGS][m_NUM_OSC] = {0};
  unsigned long currentMicros;
  static bool lfoStop[m_NUM_STRINGS][m_NUM_OSC] = {false};
  static bool retriggered = false;
  static bool oneShot = false;
  static double x = 0;
  static u8 wave1Selection = 1;
  static u8 wave2Selection = 2;
  static u8 lfoCount = 0;
  static bool continuous1 = false;
  static bool continuous2 = false;
  //*************************************************************************
  if (retrig == true)
    retriggered = true;

  currentMicros = micros();

  if (currentMicros - lfoTime[m_str][m_osc] >= str[m_str].m_lfoSpeed[m_osc])
  {
    lfoTime[m_str][m_osc] = currentMicros;
    str[m_str].m_lfoRange[m_osc] = FILtop - FILbottom;
    if (str[m_str].m_lfoRange[m_osc] < 0)
      str[m_str].m_lfoRange[m_osc] = 0;

    //***********************LFO Mode Control****************************************
    switch (mode)
    {
    case 0: //LFO OFF
      return;
      break;
    case 1: //LFO. Sine Repeating
      if (retriggered == true)
      {
        Serial.println("LFO Shape: Sine Repeating");
        lfoDirection[m_str][m_osc] = 1;
        continuous1 = true;    //Enables first half of waveform
        continuous2 = true;    //Enables second half od waveform
        wave1Selection = 1;   //1 = Exponential Rising Shape Selected.
        wave2Selection = 2;   //2 = Exponential Falling Shape Selected
        x = 0;
      }
      break;
    case 2: //LFO. Cosine Repeating
      if (retriggered == true)
      {
        Serial.println("LFO Shape: Cosine Repeating");
        lfoDirection[m_str][m_osc] = 2;
        continuous1 = true;
        continuous2 = true;
        wave1Selection = 1;
        wave2Selection = 2;
        x = 0;
      }
      break;
    case 3: //LFO. Exponential Rising. Repeating
      if (retriggered == true)
      {
        Serial.println("LFO Shape: Exponential Rising Repeating");
        lfoDirection[m_str][m_osc] = 1;
        continuous1 = true;
        continuous2 = true;
        wave1Selection = 1;
        wave2Selection = 1;
        x = 0;
      }
      break;
    case 4: //LFO. Exponential Falling. Repeating
      if (retriggered == true)
      {
        Serial.println("LFO Shape: Exponential Falling Repeating");
        lfoDirection[m_str][m_osc] = 1;
        continuous1 = true;
        continuous2 = true;
        wave1Selection = 2;
        wave2Selection = 2;
        x = 0;
      }
      break;
    case 5: //LFO. Exponential Rising 1 Shot Sustained
      if (retriggered == true)
      {
        Serial.println("LFO Shape: Exponential Rising 1 Shot Sustained");
        lfoDirection[m_str][m_osc] = 1;
        continuous1 = true;
        continuous2 = false;
        wave1Selection = 1;
        wave2Selection = 1;
        x = 0;
      }
      break;
     case 6: //LFO. Exponential Rising 1 Shot Stopped
      if (retriggered == true)
      {
        Serial.println("LFO Shape: Exponential Rising 1 Shot Stopped");
        lfoDirection[m_str][m_osc] = 1;
        continuous1 = false;
        continuous2 = false;
        wave1Selection = 1;
        wave2Selection = 1;
        x = 0;
      }
      break;
       case 7: //LFO. Exponential Falling 1 Shot Stopped
      if (retriggered == true)
      {
        Serial.println("LFO Shape: Exponential Falling 1 Shot Stopped");
        lfoDirection[m_str][m_osc] = 1;
        continuous1 = false;
        continuous2 = false;
        wave1Selection = 2;
        wave2Selection = 1;
        x = 0;
      }
      break;

    default:
      break;
    } //switch
    retriggered = false;
    str[m_str].m_lfo[m_osc] = localLFO[m_str][m_osc];    //Assign local LFO value to global LFO value here.

    //************Increment LFOs Here********************

    if (lfoDirection[m_str][m_osc] == 1 && continuous1 == true) //UP
    {
      localLFO[m_str][m_osc] = MathFunctions(wave1Selection, 1, str[m_str].m_lfo1Slope[m_osc], (x++) * .01);
      if (x * .01 >= 1)
      {
        x = 0;
        lfoDirection[m_str][m_osc] = 2;
      }
    }

    if (lfoDirection[m_str][m_osc] == 2 && continuous2 == true) //Down
    {
      localLFO[m_str][m_osc] = MathFunctions(wave2Selection, 1, str[m_str].m_lfo2Slope[m_osc], (x++) * .01);
      if (x * .01 >= 1)
      {
        x = 0;
        lfoDirection[m_str][m_osc] = 1;
      }
    }
    else  //For 1 Shot Stopped  LFO Waveforms
      localLFO[m_str][m_osc] = MathFunctions(wave1Selection, 1, str[m_str].m_lfo1Slope[m_osc], (x++) * .01); 
  } //millis
} //end funct
