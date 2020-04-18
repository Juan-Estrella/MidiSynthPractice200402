#pragma once

#include <Arduino.h>
#include "Martone.h"
#include "GuiTool.h"

class MartoneOsc : public Martone
{
public:
    //============
    //Constructors
    //============
    MartoneOsc();
    MartoneOsc(int osc1W,
               int osc2W, 
               int osc3W, 
               float osc1V, 
               float osc2V, 
               float osc3V, 
               float osc4V
    );

~MartoneOsc();

//=================
//Public Constants
//=================

//=================
//Public Functions
//=================
void Initialize(Martone *pStr[], MartoneOsc *pOsc[]);
void HandleNoteOn(int channel, int note, int velocity);
void HandleNoteOff(int channel, int note, int velocity);
void Update(Martone *pStr[], MartoneOsc *pOsc[]);
//****************************************Private****************************************

protected:
//===================
//Protected Constants
//===================

//===============================
//Protected Variable Declarations
//===============================
//int m_waveform;
int m_osc;
int m_oscWave[3];
float m_oscVol[4];
int m_oscIndex;

//=============================
//Private Function Declarations
//=============================
void ProcessKeyboardData(Martone *pStr[], MartoneOsc *pOsc[]);
void UpdateSettings(int pIndex, Martone *pStr[], int m_str, int m_osc, MartoneOsc *pOsc[]);
void SetFilter();
void SetOsc(float m_volume, int m_waveform, int m_osc, Martone *pStr[], MartoneOsc *pOsc[]);
void SetADSR(float attack, float decay, float sustain, float release, bool payNote);
void ADSRoff();


int SetWaveform(int waveform, int target);
void SetOctave(int octave, int target);
void SetStartNote(int startNote);
void SetScale(int scale);
void SetVolume(int volume, int target);
void SetFreqCutoff(float cutoff, int target);
void SetFreqRes(float res, int target);
void SetAttack(float attack, int target);
void SetDecay(float decay, int target);
void SetSustain(float sustain, int target);
void SetRelease(float release, int target);
void SetLfoTarget(int target);
void SetLfoShape(int lfoShape, int target);
void SetLfoMode(int lfoMode, int target);
void SetLfoSpeed(int lfoSpeed, int target);
void SetLfoDepth(int lfoDepth, int target);
void SetLfoPitch(int lfoPitch, int target);
void SetTemperament(int temperament, int target);
void SetPoly(bool poly);
void ShowInfo();
void Transpose(int transpose, int target);
void Detune(float detune, int target);
void Interval(int interval, int target);
void ProcessBluetoothDataData(int string);
void ProcessKnobData();
void StartOscPoly(int midiNote, int vel, int string, int wobble, int offset);
void StopOscPoly(int note, int vel, int string, int offset);
void StartOscMono(int midiNote, int offset, int string, int vel);
void StopOscMono(int midiNote, int vel, int string, int offset);
void KeyBuff(int midiNote, int vel, int string, int wobble, int offset, bool playNote);
void LfoUpdate(bool retrig, int mode, float FILtop, float FILbottom);
void GetReleaseState();
void ShowWaveform(int m_waveform);
//***************************************************************************************************
private:
};
