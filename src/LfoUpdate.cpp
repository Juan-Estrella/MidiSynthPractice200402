#include <Arduino.h>
#include <Audio.h>
#include <USBHost_t36.h>
#include "Globals.h"
#include "GuiTool.h"
#include "LfoUpdate.h"
#include "Martone.h"

void Martone::LfoUpdate(bool retrig, u8 mode, float FILtop, float FILbottom, u8 m_str, u8 m_osc)
{
  static double localLFO[m_NUM_STRINGS][m_NUM_OSC] = {0};
  static unsigned long lfoTime[m_NUM_STRINGS][m_NUM_OSC] = {0};
  static u8 lfoDirection[m_NUM_STRINGS][m_NUM_OSC] = {0};
  unsigned long currentMicros;
  static bool retriggered = false;
  static double x[m_NUM_STRINGS][m_NUM_OSC] = {0};
  static u8 waveFunction1[m_NUM_STRINGS][m_NUM_OSC] = {1};
  static u8 waveFunction2[m_NUM_STRINGS][m_NUM_OSC] = {2};
  static u8 lfoCount1[m_NUM_STRINGS][m_NUM_OSC] = {0};
  static u8 lfoCount2[m_NUM_STRINGS][m_NUM_OSC] = {0};
  unsigned long maxLfoCount[m_NUM_STRINGS][m_NUM_OSC] = {3000000};
  static bool continuous1[m_NUM_STRINGS][m_NUM_OSC] = {false};
  static bool continuous2[m_NUM_STRINGS][m_NUM_OSC] = {false};
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
        continuous1[m_str][m_osc] = true; //Enables first half of waveform
        continuous2[m_str][m_osc] = true; //Enables second half of waveform
        waveFunction1[m_str][m_osc] = 1;  //1 = Exponential Rising Shape Selected. //3 = Sine Shape Selected
        waveFunction2[m_str][m_osc] = 2;  //2 = Exponential Falling Shape Selected //4 = Cosine Shape Selected
        x[m_str][m_osc] = 0;
        lfoCount1[m_str][m_osc] = 0;
        lfoCount2[m_str][m_osc] = 0;
      }
      break;
    case 2: //LFO. Cosine Repeating
      if (retriggered == true)
      {
        Serial.println("LFO Shape: Cosine Repeating");
        lfoDirection[m_str][m_osc] = 1;
        continuous1[m_str][m_osc] = true;
        continuous2[m_str][m_osc] = true;
        waveFunction1[m_str][m_osc] = 2;
        waveFunction2[m_str][m_osc] = 1;
        x[m_str][m_osc] = 0;
        lfoCount1[m_str][m_osc] = 0;
        lfoCount2[m_str][m_osc] = 0;
      }
      break;
    case 3: //LFO. Exponential Rising. Repeating
      if (retriggered == true)
      {
        Serial.println("LFO Shape: Exponential Rising Repeating");
        lfoDirection[m_str][m_osc] = 1;
        continuous1[m_str][m_osc] = true;
        continuous2[m_str][m_osc] = true;
        waveFunction1[m_str][m_osc] = 1;
        waveFunction2[m_str][m_osc] = 1;
        x[m_str][m_osc] = 0;
        lfoCount1[m_str][m_osc] = 0;
        lfoCount2[m_str][m_osc] = 0;
      }
      break;
    case 4: //LFO. Exponential Falling. Repeating
      if (retriggered == true)
      {
        Serial.println("LFO Shape: Exponential Falling Repeating");
        lfoDirection[m_str][m_osc] = 1;
        continuous1[m_str][m_osc] = true;
        continuous2[m_str][m_osc] = true;
        waveFunction1[m_str][m_osc] = 2;
        waveFunction2[m_str][m_osc] = 2;
        x[m_str][m_osc] = 0;
        lfoCount1[m_str][m_osc] = 0;
        lfoCount2[m_str][m_osc]= 0;
      }
      break;
    case 5: //LFO. Exponential Rising 1 Shot Sustained
      if (retriggered == true)
      {
        Serial.println("LFO Shape: Exponential Rising 1 Shot Sustained");
        lfoDirection[m_str][m_osc] = 1;
        continuous1[m_str][m_osc] = true;
        continuous2[m_str][m_osc] = false;
        waveFunction1[m_str][m_osc] = 1;
        waveFunction2[m_str][m_osc] = 1;
        x[m_str][m_osc] = 0;
        lfoCount1[m_str][m_osc] = 0;
        lfoCount2[m_str][m_osc] = 0;
      }
      break;
    case 6: //LFO. Exponential Rising 1 Shot Stopped
      if (retriggered == true)
      {
        Serial.println("LFO Shape: Exponential Rising 1 Shot Stopped");
        lfoDirection[m_str][m_osc] = 3;
        continuous1[m_str][m_osc] = false;
        continuous2[m_str][m_osc] = false;
        waveFunction1[m_str][m_osc] = 1;
        x[m_str][m_osc] = 0;
        lfoCount1[m_str][m_osc] = 0;
        lfoCount2[m_str][m_osc] = 0;
      }
      break;
    case 7: //LFO. Exponential Falling 1 Shot Stopped
      if (retriggered == true)
      {
        Serial.println("LFO Shape: Exponential Falling 1 Shot Stopped");
        lfoDirection[m_str][m_osc] = 3;
        waveFunction1[m_str][m_osc] = 2;
        x[m_str][m_osc] = 0;
        lfoCount1[m_str][m_osc] = 0;
        lfoCount2[m_str][m_osc] = 0;
      }
      break;
     case 8: //LFO. Sine 1 Shot Stopped
      if (retriggered == true)
      {
        Serial.println("LFO Shape: Sine Wave 1 Shot Stopped");
        lfoDirection[m_str][m_osc] = 3;
        waveFunction1[m_str][m_osc] = 3;
        x[m_str][m_osc] = 0;
        lfoCount1[m_str][m_osc] = 0;
        lfoCount2[m_str][m_osc] = 0;
      }
      break;
     case 9: //LFO. Cosine 1 Shot Stopped
      if (retriggered == true)
      {
        Serial.println("LFO Shape: Cosine Wave 1 Shot Stopped");
        lfoDirection[m_str][m_osc] = 3;
        waveFunction1[m_str][m_osc] = 4;
        x[m_str][m_osc] = 0;
        lfoCount1[m_str][m_osc] = 0;
        lfoCount2[m_str][m_osc] = 0;
      }
      break;

    default:
      break;
    } //switch
    retriggered = false;
     //********Assign local LFO value to global LFO value here.*********

    str[m_str].m_lfo[m_osc] = localLFO[m_str][m_osc]; 

    //************Increment Continuous LFOs Here*************************************

    if ((lfoCount2[m_str][m_osc]  < maxLfoCount[m_str][m_osc]  && waveFunction1 != waveFunction2) || (waveFunction1 == waveFunction2 && (lfoCount1[m_str][m_osc] + lfoCount2[m_str][m_osc]) < maxLfoCount[m_str][m_osc]))
    {
      if (lfoDirection[m_str][m_osc] == 1 && continuous1[m_str][m_osc] == true) //UP
      {
        localLFO[m_str][m_osc] = MathFunctions(waveFunction1[m_str][m_osc], 1, str[m_str].m_lfoFrontSlope[m_osc], (x[m_str][m_osc]++) * .01);
        if (x[m_str][m_osc] * .01 >= 1)
        {
          x[m_str][m_osc] = 0;
          lfoDirection[m_str][m_osc] = 2;
          lfoCount1[m_str][m_osc]++;
        }
      }

      if (lfoDirection[m_str][m_osc] == 2 && continuous2[m_str][m_osc] == true) //Down
      {
        localLFO[m_str][m_osc] = MathFunctions(waveFunction2[m_str][m_osc], 1, str[m_str].m_lfoBackSlope[m_osc], (x[m_str][m_osc]++) * .01);
        if (x[m_str][m_osc] * .01 >= 1)
        {
          x[m_str][m_osc] = 0;
          lfoDirection[m_str][m_osc] = 1;
          //Serial.println(lfoCount2++);
          lfoCount2[m_str][m_osc]++;
        }
      }
    }
    //*****************//To Increment 1 Shot Stopped LFO Waveforms****************
    if (lfoDirection[m_str][m_osc] == 3 && lfoCount1[m_str][m_osc] < 1)
      localLFO[m_str][m_osc] = MathFunctions(waveFunction1[m_str][m_osc], 1, str[m_str].m_lfoFrontSlope[m_osc], (x[m_str][m_osc]++) * .01);
  //  if (x * .01 >= 1)
  //  {
  //    x = 0;
  //    lfoCount1++;
  //  }
  } //millis
} //end funct
