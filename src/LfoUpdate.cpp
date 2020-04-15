#include <Arduino.h>
#include <Audio.h>
#include <USBHost_t36.h>
#include "Globals.h"
#include "Functions.h"
#include "GuiTool.h"
#include "LfoUpdate.h"


void LfoUpdate(bool retrig, int mode, float FILtop, float FILbottom, int str)
{
  // //Serial.println("lfoUpdate");
  // static float localLFO[NUM_VOICES] = {0};
  // static unsigned long lfoTime[NUM_VOICES] = {0};
  // static bool lfoDirection[NUM_VOICES] = {false};
  // unsigned long currentMicros;
  // static bool lfoStop[NUM_VOICES] = {false};
  // static bool retriggered = false;
  // bool activeLFO[NUM_VOICES] = {false};
  // int voice;
  // for(int i = 1;i<NUM_VOICES+1;i++)
  // {
  // voice = 3;//activeVoice[i];
  // }
  // //*************************************************************************
  // if (retrig == true) retriggered = true;
  //   currentMicros = micros();
  // //===============================================
 

  // if (currentMicros - lfoTime[voice] >= sp.lfoSpeed[str])
  // {
  //   lfoTime[voice] = currentMicros;
  //   sp.lfoRange[str] = FILtop - FILbottom;
  //   if (sp.lfoRange[str] < 0) sp.lfoRange[str] = 0;
  //   //****************LFO*******Down then Up*************************************


  //   if (lfoDirection[voice] == true)  //Down
  //   {
  //     localLFO[voice] = (localLFO[voice] - 0.01);
  //     if (localLFO[voice] <= 0)
  //     {
  //       lfoDirection[voice] = false;
  //       lfoStop[voice] = true;
  //     }
  //   }
  //   if (lfoDirection[voice] == false)  //UP
  //   {
  //     localLFO[voice] = (localLFO[voice] + 0.01);
  //     if (localLFO[voice] >= 1)
  //     {
  //       lfoDirection[voice] = true;
  //       lfoStop[voice] = true;
  //       //localLFO[2] = 0;   //uncommenting this makes it go down, then up up up repeating.
  //     }
  //   }
  //   //**********************************************************
  //   // LFO Modes
  //   switch (mode)
  //   {
  //     case 0: //Filter OFF
  //       return;
  //       break;
  //     case 1: //Filter DOWN
  //       if (retriggered == true)
  //       {
  //         Serial.println("retriggered");
  //         lfoDirection[voice] = true;
  //         localLFO[voice] = 1.0;
  //         lfoDirection[voice] = true;
  //         localLFO[voice] = 1.0;
  //       }
  //       if (sp.lfoActiveString[str] == true)
  //       {
  //         if (activeVoice[2] == true && lfoActive[2] == true)
  //         {
  //           activeLFO[2] = true;
  //           sp.lfo[str] = localLFO[2];
  //           filter2.frequency(sp.filterFreqCutoff[str] * (sp.lfoRange[str]*sp.lfo[str]) + sp.lfoDepth[str]);
  //         } else activeLFO[2] = false;
  //         if (activeVoice[3] == true && lfoActive[3] == true)
  //         {
  //           activeLFO[3] = true;
  //           sp.lfo[str] = localLFO[3];
  //           filter3.frequency(sp.filterFreqCutoff[str] * (sp.lfoRange[str]*sp.lfo[str]) + sp.lfoDepth[str]);
  //         } else activeLFO[3] = false;
  //       }
  //       break;
  //   }//switch
  //   retriggered = false;
  // }//millis
  //***===============================================================
}//end funct
//****************************************