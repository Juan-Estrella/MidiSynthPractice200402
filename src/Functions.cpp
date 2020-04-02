#include <Arduino.h>
#include <Audio.h>
#include "Functions.h"
#include "GuiTool.h"

//**************Functions****************************
void InitializeAudio()
{
  AudioMemory(20);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8);
  //***Voice 1
  osc1a.begin(WAVEFORM_SAWTOOTH);
  osc1a.amplitude(0.5);
  osc1a.frequency(440);

  osc1b.begin(WAVEFORM_SAWTOOTH);
  osc1b.amplitude(0.0);
  osc1b.frequency(440);

  osc1c.begin(WAVEFORM_SAWTOOTH);
  osc1c.amplitude(0.0);
  osc1c.frequency(440);

  osc1n.amplitude(0.0);
  //*** Voice 2
  osc2a.begin(WAVEFORM_SAWTOOTH);
  osc2a.amplitude(0.5);
  osc2a.frequency(440);

  osc2b.begin(WAVEFORM_SAWTOOTH);
  osc2b.amplitude(0.0);
  osc2b.frequency(440);

  osc2c.begin(WAVEFORM_SAWTOOTH);
  osc2c.amplitude(0.0);
  osc2c.frequency(440);

  osc2n.amplitude(0.0);
  //***Voice 3
  osc3a.begin(WAVEFORM_SAWTOOTH);
  osc3a.amplitude(0.5);
  osc3a.frequency(440);

  osc3b.begin(WAVEFORM_SAWTOOTH);
  osc3b.amplitude(0.0);
  osc3b.frequency(440);

  osc3c.begin(WAVEFORM_SAWTOOTH);
  osc3c.amplitude(0.0);
  osc3c.frequency(440);

  osc3n.amplitude(0.0);
  //***Voice 4
  osc4a.begin(WAVEFORM_SAWTOOTH);
  osc4a.amplitude(0.5);
  osc4a.frequency(440);

  osc4b.begin(WAVEFORM_SAWTOOTH);
  osc4b.amplitude(0.0);
  osc4b.frequency(440);

  osc4c.begin(WAVEFORM_SAWTOOTH);
  osc4c.amplitude(0.0);
  osc4c.frequency(440);

  osc4n.amplitude(0.0);
}
void MyNoteOn(uint8_t channel, uint8_t note, uint8_t velocity)
{
  osc1a.frequency(440);
  osc1a.amplitude(1);
  Serial.println("Note on");
}

void MyNoteOff(uint8_t channel, uint8_t note, uint8_t velocity)
{
  osc1a.frequency(440);
  osc1a.amplitude(0);
  Serial.println("Note off");
}
