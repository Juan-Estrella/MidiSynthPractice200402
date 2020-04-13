#include <Arduino.h>
#include <Audio.h>
#include <USBHost_t36.h>
#include "Functions.h"
#include "GuiTool.h"
#include "LfoUpdate.h"
#include "Globals.h"

//*************Object Instantiations For USB MIDI********
USBHost myusb;
USBHub hub1(myusb);
USBHub hub2(myusb);
MIDIDevice midi1(myusb);

//*******************Set Up*********************
void setup()
{
  delay(3000); // 3 second delay for recovery
  Serial.begin(115200);
  AudioMemory(20);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.4);
  myusb.begin();
  midi1.setHandleNoteOn(MyNoteOn);  //MyNoteOn = Callback function triggered on MIDI input
  midi1.setHandleNoteOff(MyNoteOff);
  SetOsc();
  Serial.println("Start up Complete!");
}

//********************Loop*********************
void loop()
{
  myusb.Task();
  midi1.read();     //Scans for USB Midi Input. Triggers call back functions.
}

//*************************************************************************
void MyNoteOn(uint8_t channel, uint8_t note, uint8_t velocity)
{ 
  SetADSR();
  SetFilter();
  Serial.println("Note on");
}

void MyNoteOff(uint8_t channel, uint8_t note, uint8_t velocity)
{
  ADSRoff();
  Serial.println("Note off");
}
//*******************************************************************************