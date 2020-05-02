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
  static bool lfoDirection[m_NUM_STRINGS][m_NUM_OSC] = {true};
  unsigned long currentMicros;
  static bool lfoStop[m_NUM_STRINGS][m_NUM_OSC] = {false};
  static bool retriggered = false;
  static double x = 0;
  static u8 wave1Selection = 1;
  static u8 wave2Selection = 2;
  static u8 lfoCount = 0;
  static bool continuous = false;
  //*************************************************************************
  if (retrig == true)   retriggered = true;
  
  currentMicros = micros();

  if (currentMicros - lfoTime[m_str][m_osc] >= str[m_str].m_lfoSpeed[m_osc])
  {
    lfoTime[m_str][m_osc] = currentMicros;
    str[m_str].m_lfoRange[m_osc] = FILtop - FILbottom;
    if (str[m_str].m_lfoRange[m_osc] < 0)
      str[m_str].m_lfoRange[m_osc] = 0;

    //*****************LFO Mode Control****************************************
    switch (mode)
    {
    case 0: //Filter OFF
      return;
      break;
    case 1: //Filter Sine Repeating
      if (retriggered == true)
      {
        Serial.println("LFO Shape: Sine Repeating");
        lfoDirection[m_str][m_osc] = true;
        continuous = true;
        wave1Selection = 1;
        wave2Selection = 2;
        x = 0;
      }
      break;
    case 2: //Filter Cosine Repeating
      if (retriggered == true)
      {
        Serial.println("LFO Shape: Cosine Repeating");
        lfoDirection[m_str][m_osc] = false;
        continuous = true;
        wave1Selection = 1;
        wave2Selection = 2;
        x = 1;
      }
      break;
    case 3: //LFO. Exponential Rising. 1 shot
      if (retriggered == true)
      {
        x = 0;
        Serial.println("LFO Shape: Exponential Rising");
        continuous = false;
        wave1Selection = 1;
      }
      break;
    case 4: //LFO. Exponential Falling. 1 shot
      if (retriggered == true)
      {
        x = 1;
        Serial.println("LFO Shape: Exponential Falling");
        continuous = false;
        wave1Selection = 2;
      }
      break;
    case 5: //LFO. Sine. 1 shot
      if (retriggered == true)
      {
        x = 0;
        Serial.println("LFO Shape: Sine 1 Shot");
        continuous = false;
        wave1Selection = 3;
      }
      break;
    case 6: //LFO. Cosine. 1 shot
      if (retriggered == true)
      {
        x = 1;
        Serial.println("LFO Shape: Cosine 1 Shot");
        continuous = false;
        wave1Selection = 4;
      }
      break;

    default:
      break;
    } //switch
    retriggered = false;
    str[m_str].m_lfo[m_osc] = localLFO[m_str][m_osc]; //Assign local LFO value to global LFO value here.

    //************LFO Waveforms****(LFO value gets incremented here.)***********

    if (lfoDirection[m_str][m_osc] == true && continuous == true) //UP
    {
      localLFO[m_str][m_osc] = MathFunctions(wave1Selection, 1, str[m_str].m_lfo1Slope[m_osc], (x++) * .01);
      if (localLFO[m_str][m_osc] >= .99)
      {
        x = 0;
        lfoDirection[m_str][m_osc] = false;
        lfoStop[m_str][m_osc] = true;
      }
    }

    if (lfoDirection[m_str][m_osc] == false && continuous == true) //Down
    {
      localLFO[m_str][m_osc] = MathFunctions(wave2Selection, 1, str[m_str].m_lfo2Slope[m_osc], (x++) * .01);
      if (localLFO[m_str][m_osc] <= .01)
      {
        x = 0;
        lfoDirection[m_str][m_osc] = true;
        lfoStop[m_str][m_osc] = true;
      }
    }
    //************************************************************************
    if (continuous == false)
      localLFO[m_str][m_osc] = MathFunctions(wave1Selection, 1, str[m_str].m_lfo1Slope[m_osc], (x++) * .01);

    lfoCount++;

  } //millis
} //end funct
