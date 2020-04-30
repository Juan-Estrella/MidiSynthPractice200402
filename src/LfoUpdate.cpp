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
  //Serial.println("lfoUpdate");
  static float localLFO[m_NUM_VOICES][m_NUM_OSC] = {0};
  static unsigned long lfoTime[m_NUM_VOICES][m_NUM_OSC] = {0};
  static bool lfoDirection[m_NUM_VOICES][m_NUM_OSC] = {false};
  unsigned long currentMicros;
  static bool lfoStop[m_NUM_VOICES][m_NUM_OSC] = {false};
  static bool retriggered = false;
  static int x = 0;
  // bool activeLFO[NUM_VOICES] = {false};
  // int voice;
  // for(int i = 1;i<NUM_VOICES+1;i++)
  // {
  // voice = 3;//activeVoice[i];
  // }
  // //*************************************************************************
  if (retrig == true) retriggered = true;
  currentMicros = micros();
  // //===============================================
 

  if (currentMicros - lfoTime[m_str][m_osc] >= str[m_str].m_lfoSpeed[m_osc])
  {
    lfoTime[m_str][m_osc] = currentMicros;
    str[m_str].m_lfoRange[m_osc] = FILtop - FILbottom;
    if (str[m_str].m_lfoRange[m_osc] < 0) str[m_str].m_lfoRange[m_osc] = 0;
  //   //****************LFO*******Down then Up*************************************
                     //LFO value gets incremented here.

    if (lfoDirection[m_str][m_osc] == true)  //Down
    {
      localLFO[m_str][m_osc] = (localLFO[m_str][m_osc] - (x++)*0.01);
      if (localLFO[m_str][m_osc] <= 0)
      {
        lfoDirection[m_str][m_osc] = false;
        lfoStop[m_str][m_osc] = true;
      }
    }
    if (lfoDirection[m_str][m_osc] == false)  //UP
    {
      localLFO[m_str][m_osc] = (localLFO[m_str][m_osc] + (x++)*0.01);
      if (localLFO[m_str][m_osc] >= 1)
      {
        lfoDirection[m_str][m_osc] = true;
        lfoStop[m_str][m_osc] = true;
        //localLFO[2] = 0;   //uncommenting this makes it go down, then up up up repeating.
      }
    }
  //   //**********************************************************
  //   // LFO Modes
    switch (mode)
    {
      case 0: //Filter OFF
        return;
        break;
      case 1: //Filter DOWN
        if (retriggered == true)
        {
          Serial.println("retriggered");
          lfoDirection[m_str][m_osc] = true;
          localLFO[m_str][m_osc] = 1.0;
          lfoDirection[m_str][m_osc] = true;
          localLFO[m_str][m_osc] = 1.0;
        }
  //       if (sp.lfoActiveString[str] == true)
  //       {
  //         if (activeVoice[2] == true && lfoActive[2] == true)
  //         {
  //           activeLFO[2] = true;
            str[m_str].m_lfo[m_osc] = localLFO[m_str][m_osc];
            filtosc1a.frequency(str[m_str].m_freqCut[m_osc] * (str[m_str].m_lfoRange[m_osc]*str[m_str].m_lfo[m_osc]) + str[m_str].m_lfoDepth[m_osc]);
  //         } else activeLFO[2] = false;
  //         if (activeVoice[3] == true && lfoActive[3] == true)
  //         {
  //           activeLFO[3] = true;
  //           sp.lfo[str] = localLFO[3];
  //           filter3.frequency(sp.filterFreqCutoff[str] * (sp.lfoRange[str]*sp.lfo[str]) + sp.lfoDepth[str]);
  //         } else activeLFO[3] = false;
  //       }
        break;
    }//switch
    retriggered = false;
  }//millis
  //***===============================================================
}//end funct
//****************************************