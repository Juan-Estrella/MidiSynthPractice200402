#pragma once

#include <Arduino.h>
#include "GuiTool.h"
//#include "Globals.h"

class Martone
{
 //****************************************Public*****************************************

public:

    //============
    //Constructors
    //============
    Martone();
    Martone(int octave, 
            int startnote, 
            int scale, 
            float volume, 
            float filtFreqCutoff, 
            float filtRes, 
            float attack, 
            float decay, 
            float sustain, 
            float release, 
            int lfoShape, 
            int lfoModeSelect, 
            float lfoSpeed, 
            float lfoDepth, 
            float lfoPitch, 
            float lfo, 
            float lfoRange, 
            float filtPercent, 
            bool interpolate, 
            bool poly, 
            int temperament, 
            int electrode3D);
    ~Martone();

    //=================
    //Public Constants
    //=================
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
     enum notes  //for printing names of notes
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
    }; 
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
    //void Initialize(Martone *pStr[], Martone *pOsc[]);
    //void HandleNoteOn(int channel, int note, int velocity);
    //void HandleNoteOff(int channel, int note, int velocity);
    //void Update(Martone *pStr[], Martone *pOsc[]);
    //****************************************Private****************************************

protected:
    //===================
    //Protected Constants
    //===================
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

    //===============================
    //Protected Variable Declarations
    //===============================
    int m_octave;
    int m_startNote;
    int m_scale;
    float m_volume;
    float m_filtFreqCutoff;
    float m_filtRes;
    float m_attack;  //default 10.5ms. Max 11880
    float m_decay;   //default is 35ms. Max is 11880
    float m_sustain; //0-1
    float m_release; //default is 300ms. max is 11880
    int m_lfoShape;
    int m_lfoMode;
    float m_lfoSpeed;
    float m_lfoDepth;
    float m_lfoPitch;
    float m_lfo;
    float m_lfoRange;
    float m_filtPercent;
    float m_scaleFreqs[m_NUM_NOTES_INST];
    bool m_interpolate;
    bool m_poly;
    int m_temperament;
    int m_electrode3D;
    int m_channel;
    int m_velocity;
    int m_note;
    int m_string;
    int m_pIndex; //for mapping commands to parameters
    bool m_stringSelect;   //for keyboard processing
    bool m_parameterSelect;
    bool m_oscSelect;
    float m_oldKnobValue;
    float m_low, m_high;       //for range mapping
    float m_mappedKnobValue[5][m_NUM_EFFECTS];
    float m_rawKnobValue;
    int m_str;
    
    //=============================
    //Private Function Declarations
    //=============================
    
    //***************************************************************************************************
private:
};

