#include <Arduino.h>
#include <Audio.h>
#include "Functions.h"
#include "GuiTool.h"

//**************Functions****************************
void SetOsc()
{

  //***Voice 1
  osc1a.begin(WAVEFORM_TRIANGLE);
  osc1a.amplitude(0.5);
  osc1a.frequency(220);

  osc1b.begin(WAVEFORM_SAWTOOTH);
  osc1b.amplitude(0.5);
  osc1b.frequency(440);

  osc1c.begin(WAVEFORM_SQUARE);
  osc1c.amplitude(0.5);
  osc1c.frequency(880);

  osc1n.amplitude(0.5);

  //***********************
  //*** Voice 2
  // osc2a.begin(WAVEFORM_SAWTOOTH);
  // osc2a.amplitude(0.5);
  // osc2a.frequency(440);

  // osc2b.begin(WAVEFORM_SAWTOOTH);
  // osc2b.amplitude(0.0);
  // osc2b.frequency(440);

  // osc2c.begin(WAVEFORM_SAWTOOTH);
  // osc2c.amplitude(0.0);
  // osc2c.frequency(440);

  // osc2n.amplitude(0.0);
  // //***Voice 3
  // osc3a.begin(WAVEFORM_SAWTOOTH);
  // osc3a.amplitude(0.5);
  // osc3a.frequency(440);

  // osc3b.begin(WAVEFORM_SAWTOOTH);
  // osc3b.amplitude(0.0);
  // osc3b.frequency(440);

  // osc3c.begin(WAVEFORM_SAWTOOTH);
  // osc3c.amplitude(0.0);
  // osc3c.frequency(440);

  // osc3n.amplitude(0.0);
  // //***Voice 4
  // osc4a.begin(WAVEFORM_SAWTOOTH);
  // osc4a.amplitude(0.5);
  // osc4a.frequency(440);

  // osc4b.begin(WAVEFORM_SAWTOOTH);
  // osc4b.amplitude(0.0);
  // osc4b.frequency(440);

  // osc4c.begin(WAVEFORM_SAWTOOTH);
  // osc4c.amplitude(0.0);
  // osc4c.frequency(440);

  // osc4n.amplitude(0.0);
}

void SetADSR()
{
  ADSR1.noteOn();
  ADSRosc1a.noteOn();
  ADSRosc1b.noteOn();
  ADSRosc1c.noteOn();
  ADSRosc1n.noteOn();

  ADSR1.attack(1);    //default 10.5ms. max 11.88 seconds  
  ADSR1.decay(35);    //default 35 ms. max 11.88 seconds
  ADSR1.sustain(1);   //0-1
  ADSR1.release(2000); //default 300ms. max 11.88 seconds

  ADSRosc1a.attack(900);    //tri
  ADSRosc1b.attack(800);    //saw
  ADSRosc1c.attack(300);    //square
  ADSRosc1n.attack(1000);     //noise

  ADSRosc1a.decay(1);
  ADSRosc1b.decay(1);
  ADSRosc1c.decay(1);
  ADSRosc1n.decay(1);

  ADSRosc1a.sustain(1);
  ADSRosc1b.sustain(1);
  ADSRosc1c.sustain(1);
  ADSRosc1n.sustain(1);

  ADSRosc1a.release(1000);
  ADSRosc1b.release(200);
  ADSRosc1c.release(400);
  ADSRosc1n.release(50);
}

void SetFilter()
{
  filter1.frequency(10000);
  filter1.resonance(1);

  filtosc1a.frequency(10000);    //tri
  filtosc1a.resonance(1);

  filtosc1b.frequency(10000);   //saw
  filtosc1b.resonance(1);

  filtosc1c.frequency(500);    //square
  filtosc1c.resonance(1);

  filtosc1n.frequency(10000);    //noise
  filtosc1n.resonance(1);
}

void ADSRoff()
{
  ADSR1.noteOff();
  ADSRosc1a.noteOff();
  ADSRosc1b.noteOff();
  ADSRosc1c.noteOff();
  ADSRosc1n.noteOff();
}