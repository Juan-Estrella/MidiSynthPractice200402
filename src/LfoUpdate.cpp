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
  static bool lfoDirection[m_NUM_STRINGS][m_NUM_OSC] = {false};
  unsigned long currentMicros;
  static bool lfoStop[m_NUM_STRINGS][m_NUM_OSC] = {false};
  static bool retriggered = false;
  static double x = 0;
  // //*************************************************************************
  if (retrig == true)  retriggered = true;
   
  currentMicros = micros();

  if (currentMicros - lfoTime[m_str][m_osc] >= str[m_str].m_lfoSpeed[m_osc])
  {
    lfoTime[m_str][m_osc] = currentMicros;
    str[m_str].m_lfoRange[m_osc] = FILtop - FILbottom;
    if (str[m_str].m_lfoRange[m_osc] < 0)  str[m_str].m_lfoRange[m_osc] = 0;
     
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
        x = 0;
      }
      break;
    case 2: //Filter Cosine Repeating
      if (retriggered == true)
      {
        Serial.println("LFO Shape: Cosine Repeating");
        lfoDirection[m_str][m_osc] = true;
        x = 1;
      }
      break;

    default:
      break;
    } //switch
    retriggered = false;
    str[m_str].m_lfo[m_osc] = localLFO[m_str][m_osc];   //Assign local LFO value to global LFO value here.

    //************LFO Waveforms****(LFO value gets incremented here.)***********

     if (lfoDirection[m_str][m_osc] == true) //UP
    {
      //localLFO[m_str][m_osc] = (localLFO[m_str][m_osc] + 0.01);
      localLFO[m_str][m_osc] = MathFunctions(1, 1, str[m_str].m_filtSlope[m_osc], (x++) * .01);
      if (localLFO[m_str][m_osc] >= .99)
      {
        x = 0;
        //Serial.println("hello");
        lfoDirection[m_str][m_osc] = false;
        lfoStop[m_str][m_osc] = true;
        //localLFO[2] = 0;   //uncommenting this makes it go down, then up up up repeating.
      }
    }

    if (lfoDirection[m_str][m_osc] == false) //Down
    {
      //localLFO[m_str][m_osc] = (localLFO[m_str][m_osc] - 0.01);
      localLFO[m_str][m_osc] = MathFunctions(2, 1, str[m_str].m_filtSlope[m_osc], (x++) * .01);

      if (localLFO[m_str][m_osc] <= .01)
      {
        x = 0;
        //Serial.println("hello2");
        lfoDirection[m_str][m_osc] = true;
        lfoStop[m_str][m_osc] = true;
      }
    }

  } //millis
} //end funct
  //****************************************