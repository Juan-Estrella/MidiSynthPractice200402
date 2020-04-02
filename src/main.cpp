#include <Arduino.h>
#include <Audio.h>
#include <USBHost_t36.h>
#include "Functions.h"
#include "GuiTool.h"

//*************Object Instantiation********
USBHost myusb;
USBHub hub1(myusb);
USBHub hub2(myusb);
MIDIDevice midi1(myusb);

//*******************Set Up*********************
void setup()
{
  delay(5000); // 3 second delay for recovery
  Serial.begin(115200);
  myusb.begin();
  midi1.setHandleNoteOn(MyNoteOn);
  midi1.setHandleNoteOff(MyNoteOff);
  InitializeAudio(); 
  delay(1000);
  Serial.println("Start up Complete");
}

//********************Loop*********************
void loop()
{
  myusb.Task();
  midi1.read();

}