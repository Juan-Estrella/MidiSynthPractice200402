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
  static bool retriggered = false;
  static double x = 0;
  static u8 waveFunction1 = 1;
  static u8 waveFunction2 = 2;
  static u8 lfoCount1 = 0;
  static u8 lfoCount2 = 0;
  unsigned long maxLfoCount = 3000000;
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
        continuous1 = true; //Enables first half of waveform
        continuous2 = true; //Enables second half of waveform
        waveFunction1 = 1;  //1 = Exponential Rising Shape Selected. //3 = Sine Shape Selected
        waveFunction2 = 2;  //2 = Exponential Falling Shape Selected //4 = Cosine Shape Selected
        x = 0;
        lfoCount1 = 0;
        lfoCount2 = 0;
      }
      break;
    case 2: //LFO. Cosine Repeating
      if (retriggered == true)
      {
        Serial.println("LFO Shape: Cosine Repeating");
        lfoDirection[m_str][m_osc] = 1;
        continuous1 = true;
        continuous2 = true;
        waveFunction1 = 2;
        waveFunction2 = 1;
        x = 0;
        lfoCount1 = 0;
        lfoCount2 = 0;
      }
      break;
    case 3: //LFO. Exponential Rising. Repeating
      if (retriggered == true)
      {
        Serial.println("LFO Shape: Exponential Rising Repeating");
        lfoDirection[m_str][m_osc] = 1;
        continuous1 = true;
        continuous2 = true;
        waveFunction1 = 1;
        waveFunction2 = 1;
        x = 0;
        lfoCount1 = 0;
        lfoCount2 = 0;
      }
      break;
    case 4: //LFO. Exponential Falling. Repeating
      if (retriggered == true)
      {
        Serial.println("LFO Shape: Exponential Falling Repeating");
        lfoDirection[m_str][m_osc] = 1;
        continuous1 = true;
        continuous2 = true;
        waveFunction1 = 2;
        waveFunction2 = 2;
        x = 0;
        lfoCount1 = 0;
        lfoCount2 = 0;
      }
      break;
    case 5: //LFO. Exponential Rising 1 Shot Sustained
      if (retriggered == true)
      {
        Serial.println("LFO Shape: Exponential Rising 1 Shot Sustained");
        lfoDirection[m_str][m_osc] = 1;
        continuous1 = true;
        continuous2 = false;
        waveFunction1 = 1;
        waveFunction2 = 1;
        x = 0;
        lfoCount1 = 0;
        lfoCount2 = 0;
      }
      break;
    case 6: //LFO. Exponential Rising 1 Shot Stopped
      if (retriggered == true)
      {
        Serial.println("LFO Shape: Exponential Rising 1 Shot Stopped");
        lfoDirection[m_str][m_osc] = 3;
        continuous1 = false;
        continuous2 = false;
        waveFunction1 = 1;
        x = 0;
        lfoCount1 = 0;
        lfoCount2 = 0;
      }
      break;
    case 7: //LFO. Exponential Falling 1 Shot Stopped
      if (retriggered == true)
      {
        Serial.println("LFO Shape: Exponential Falling 1 Shot Stopped");
        lfoDirection[m_str][m_osc] = 3;
        waveFunction1 = 2;
        x = 0;
        lfoCount1 = 0;
        lfoCount2 = 0;
      }
      break;
     case 8: //LFO. Sine 1 Shot Stopped
      if (retriggered == true)
      {
        Serial.println("LFO Shape: Sine Wave 1 Shot Stopped");
        lfoDirection[m_str][m_osc] = 3;
        waveFunction1 = 3;
        x = 0;
        lfoCount1 = 0;
        lfoCount2 = 0;
      }
      break;
     case 9: //LFO. Cosine 1 Shot Stopped
      if (retriggered == true)
      {
        Serial.println("LFO Shape: Cosine Wave 1 Shot Stopped");
        lfoDirection[m_str][m_osc] = 3;
        waveFunction1 = 4;
        x = 0;
        lfoCount1 = 0;
        lfoCount2 = 0;
      }
      break;

    default:
      break;
    } //switch
    retriggered = false;
     //********Assign local LFO value to global LFO value here.*********

    str[m_str].m_lfo[m_osc] = localLFO[m_str][m_osc]; 

    //************Increment Continuous LFOs Here*************************************

    if ((lfoCount2 < maxLfoCount && waveFunction1 != waveFunction2) || (waveFunction1 == waveFunction2 && (lfoCount1 + lfoCount2) < maxLfoCount))
    {
      if (lfoDirection[m_str][m_osc] == 1 && continuous1 == true) //UP
      {
        localLFO[m_str][m_osc] = MathFunctions(waveFunction1, 1, str[m_str].m_lfoFrontSlope[m_osc], (x++) * .01);
        if (x * .01 >= 1)
        {
          x = 0;
          lfoDirection[m_str][m_osc] = 2;
          lfoCount1++;
        }
      }

      if (lfoDirection[m_str][m_osc] == 2 && continuous2 == true) //Down
      {
        localLFO[m_str][m_osc] = MathFunctions(waveFunction2, 1, str[m_str].m_lfoBackSlope[m_osc], (x++) * .01);
        if (x * .01 >= 1)
        {
          x = 0;
          lfoDirection[m_str][m_osc] = 1;
          //Serial.println(lfoCount2++);
          lfoCount2++;
        }
      }
    }
    //*****************//To Increment 1 Shot Stopped LFO Waveforms****************
    if (lfoDirection[m_str][m_osc] == 3 && lfoCount1 < 1)
      localLFO[m_str][m_osc] = MathFunctions(waveFunction1, 1, str[m_str].m_lfoFrontSlope[m_osc], (x++) * .01);
  //  if (x * .01 >= 1)
  //  {
  //    x = 0;
  //    lfoCount1++;
  //  }
  } //millis
} //end funct
