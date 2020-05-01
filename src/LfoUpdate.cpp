#include <Arduino.h>
#include <Audio.h>
#include <USBHost_t36.h>
#include "Globals.h"
#include "Functions.h"
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
  if (retrig == true) retriggered = true;
  currentMicros = micros();
  // //===============================================

  if (currentMicros - lfoTime[m_str][m_osc] >= str[m_str].m_lfoSpeed[m_osc])
  {
    lfoTime[m_str][m_osc] = currentMicros;
    str[m_str].m_lfoRange[m_osc] = FILtop - FILbottom;
    if (str[m_str].m_lfoRange[m_osc] < 0)
      str[m_str].m_lfoRange[m_osc] = 0;

  //****************LFO. Down then Up*************************************
                      //LFO value gets incremented here.

    if (lfoDirection[m_str][m_osc] == true) //Down
    {
      //localLFO[m_str][m_osc] = (localLFO[m_str][m_osc] - 0.01);
      localLFO[m_str][m_osc] = MathFunctions(2, 1, str[m_str].m_filtSlope[m_osc], (x++) * .01);

      if (localLFO[m_str][m_osc] <= .01)
      {
        x=0;
        Serial.println("hello2");
        lfoDirection[m_str][m_osc] = false;
        lfoStop[m_str][m_osc] = true;
      }
    }

    if (lfoDirection[m_str][m_osc] == false) //UP
    {
      //   //localLFO[m_str][m_osc] = (localLFO[m_str][m_osc] + 0.01);
      localLFO[m_str][m_osc] = MathFunctions(1, 1, str[m_str].m_filtSlope[m_osc], (x++) * .01);
      if (localLFO[m_str][m_osc] >= .99)
      {
        x=0;
        Serial.println("hello");
        lfoDirection[m_str][m_osc] = true;
        lfoStop[m_str][m_osc] = true;
        //localLFO[2] = 0;   //uncommenting this makes it go down, then up up up repeating.
      }
    }

    //******************* LFO Modes***************************************
    switch (mode)
    {
    case 0: //Filter OFF
      return;
      break;
    case 1: //Filter DOWN
      if (retriggered == true)
      {
        Serial.println("retriggered");
        lfoDirection[m_str][m_osc] = false;
        x = 0;
        // lfoDirection[m_str][m_osc] = true;
        // localLFO[m_str][m_osc] = 1.0;
      }
      str[m_str].m_lfo[m_osc] = localLFO[m_str][m_osc];
      filtosc1a.frequency(str[m_str].m_freqCut[m_osc] * (str[m_str].m_lfoRange[m_osc] * localLFO[m_str][m_osc]) + str[m_str].m_lfoDepth[m_osc]); 
      break;
    } //switch
    retriggered = false;
  } //millis
} //end funct
  //****************************************