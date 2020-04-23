#pragma once

#include <Arduino.h>
#include "GuiTool.h"

typedef uint8_t u8;
typedef int8_t s8;

class Martone
{
    //****************************************Public*****************************************

public:
    //============
    //Constructors
    //============
    Martone();
    //Martone(int osc1W, int osc2W, int osc3W, float osc1V, float osc2V, float osc3V, float osc4V);
    //Martone(int octave, int startnote, int scale, float volume, float filtFreqCutoff, float filtRes, float attack, float decay, float sustain, float release, int lfoShape, int lfoModeSelect, float lfoSpeed, float lfoDepth, float lfoPitch, float lfo, float lfoRange, float filtPercent, bool interpolate, bool poly, int temperament, int electrode3D);
    ~Martone();

    //=================
    //Public Constants
    //=================

    static const int waveforms[9];

    enum scales
    {
        chromatic,
        majScale,
        harmonicMinorScale,
        pentatonicMajorScale,
        pentatonicMinorScale,
        bluesScale,
        majChord,
        minChord,
        dimChord,
        dom7Chord,
        maj7Chord,
        min7Chord,
        overtone16Div,
        overtone24Div,
        overtone8Div
    };
    enum notes
    {
        A,
        Bb,
        B,
        C,
        Db,
        D,
        Eb,
        E,
        F,
        Gb,
        G,
        Ab
    }; //for printing names of notes
    enum temperaments
    {
        equal12Temp,
        justTemp,
        overtone16Temp,
        equal24Temp,
        overtone8Temp
    };
    //=================
    //Public Functions
    //=================
    void Initialize();
    void SetOsc(u8 string, u8 osc, float volume, u8 waveform, int frequency, int freqCut, float filtSlope, float filtRes);     //  int osc1W, int osc2W, int osc3W, float osc1V, float osc2V, float osc3V, float osc4V);
    void SetString(u8 string, s8 octave, u8 startnote, u8 scale, float volume, float filtFreqCutoff, float filtRes, float attack, float decay, float sustain, float release, u8 lfoShape, u8 lfoMode, float lfoSpeed, float lfoDepth, float lfoPitch, float lfo, float lfoRange, float filtPercent, bool interpolate, bool poly, u8 temperament, u8 electrode3D);
    void Update();
    void HandleNoteOn(u8 channel, u8 note, u8 velocity);
    void HandleNoteOff(u8 channel, u8 note, u8 velocity);

    //****************************************Private****************************************

protected:

    //=================
    //Private Constants
    //=================
    static const int m_NUM_VOICES = 4;
    static const int m_NUM_WAVEFORMS = 9;
    static const int m_NUM_EFFECTS = 50;
    static const int m_NUM_NOTES_STRING = 36; //rows on Livid Block Midi controller grid
    static const int m_NUM_NOTES_INST = 64;   //number of notes in scale/instrument
    static const int m_NUM_STRINGS = 4;
    static const int m_MAX_DATA_LENGTH = 20; //for bluetooth data parsing
    static const int m_LEDPIN = 13;
    static const int m_BUFFER = 10; //Size of keyboard buffer
    static const int m_NUM_CHARS = 32;
    static const int m_NUM_OSC = 4;
    static const int m_WAVEFORMS[];

    //=============================
    //Private Variable Declarations
    //=============================
    struct stringParameters
    {
        float m_oscV[m_NUM_OSC];
        u8 m_oscW[m_NUM_OSC];
        int m_freq[m_NUM_OSC];
        int m_freqCut[m_NUM_OSC];
        float m_filtSlope[m_NUM_OSC];
        float m_filtRes[m_NUM_OSC];

    } str[m_NUM_STRINGS];

    stringParameters *m_setting[m_NUM_STRINGS] = {&str[0], &str[1], &str[2], &str[3]};
    u8 m_osc;
    u8 m_str;
    u8 m_oscIndex;
    u8 m_pIndex; //for mapping commands to parameters
    bool m_parameterSelect;
    bool m_oscSelect;
    bool m_stringSelect; //for keyboard processing
    float m_oldKnobValue;
    float m_low, m_high; //for range mapping
    float m_mappedKnobValue[m_NUM_STRINGS + 1][m_NUM_EFFECTS];
    float m_rawKnobValue;
  

    s8 m_octave;
    u8 m_startNote;
    u8 m_scale;
    float m_volume;
    float m_filtFreqCutoff;
    float m_filtRes;
    float m_attack;  //default 10.5ms. Max 11880
    float m_decay;   //default is 35ms. Max is 11880
    float m_sustain; //0-1
    float m_release; //default is 300ms. max is 11880
    u8 m_lfoShape;
    u8 m_lfoMode;
    float m_lfoSpeed;
    float m_lfoDepth;
    float m_lfoPitch;
    float m_lfo;
    float m_lfoRange;
    float m_filtPercent;
    float m_scaleFreqs[m_NUM_NOTES_INST];
    bool m_interpolate;
    bool m_poly;
    u8 m_temperament;
    u8 m_electrode3D;
    u8 m_channel;
    u8 m_velocity;
    u8 m_note;
    u8 m_string;
   
    //=============================
    //Private Function Declarations
    //=============================
    void UpdateKeyboardData();
    void SetFilter();
    void AssignOsc(u8 m_osc, u8 string) const;
    void SetADSR(float attack, float decay, float sustain, float release, bool payNote);
    void ADSRoff();
    void ProcessKeyboardData();

    u8 SetWaveform(u8 waveform, u8 target);
    void SetOctave(s8 octave, u8 target);
    void SetStartNote(u8 startNote);
    void SetScale(u8 scale);
    void SetVolume(float volume, u8 target);
    void SetFreqCutoff(float cutoff, u8 target);
    void SetFreqRes(float res, u8 target);
    void SetAttack(float attack, u8 target);
    void SetDecay(float decay, u8 target);
    void SetSustain(float sustain, u8 target);
    void SetRelease(float release, u8 target);
    void SetLfoTarget(u8 target);
    void SetLfoShape(u8 lfoShape, u8 target);
    void SetLfoMode(u8 lfoMode, u8 target);
    void SetLfoSpeed(u8 lfoSpeed, u8 target);
    void SetLfoDepth(u8 lfoDepth, u8 target);
    void SetLfoPitch(u8 lfoPitch, u8 target);
    void SetTemperament(u8 temperament, u8 target);
    void SetPoly(bool poly);
    void ShowInfo();
    void Transpose(s8 transpose, u8 target);
    void Detune(float detune, u8 target);
    void Interval(s8 interval, u8 target);
    void ProcessBluetoothDataData(u8 string);
    void ProcessKnobData();
    void StartOscPoly(u8 midiNote, u8 vel, u8 string, u8 wobble, u8 offset);
    void StopOscPoly(u8 note, u8 vel, u8 string, u8 offset);
    void StartOscMono(u8 midiNote, u8 offset, u8 string, u8 vel);
    void StopOscMono(u8 midiNote, u8 vel, u8 string, u8 offset);
    void KeyBuff(u8 midiNote, u8 vel, u8 string, u8 wobble, u8 offset, bool playNote);
    void LfoUpdate(bool retrig, u8 mode, float FILtop, float FILbottom);
    void GetReleaseState();
    void ShowWaveform(u8 m_waveform);
    //***************************************************************************************************
protected:
};

