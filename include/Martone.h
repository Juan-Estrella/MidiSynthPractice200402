#ifndef Martone_H
#define Martone_H

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
    Martone(int waveform, int octave, int startnote, int scale, float volume, float filtFreqCutoff, float filtRes, float attack, float decay, float sustain, float release, int lfoShape, int lfoModeSelect, float lfoSpeed, float lfoDepth, float lfoPitch, float lfo, float lfoRange, float filtPercent, bool interpolate, bool poly, int temperament, int electrode3D);
    ~Martone();

//=================
//Public Constants
//=================
    enum scales{chromatic,majScale,harmonicMinorScale,pentatonicMajorScale,pentatonicMinorScale,bluesScale,majChord,minChord,dimChord,dom7Chord,maj7Chord,min7Chord,overtone16Div,overtone24Div,overtone8Div};
    enum notes{A, Bb, B, C, Db, D, Eb, E, F, Gb, G, Ab};          //for printing names of notes
    enum temperaments{equal12Temp,justTemp,overtone16Temp,equal24Temp,overtone8Temp};
    int waveform;
//=================
//Public Functions
//=================
    void Initialize();
    void HandleNoteOn(int channel, int note, int velocity);
    void HandleNoteOff(int channel, int note, int velocity);
    void Update(Martone * pStr[]);
    void Troubleshoot();
//****************************************Private****************************************

private:

//=================
//Private Constants
//=================
    static const int m_NUM_VOICES = 4;
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
    int m_waveform[m_NUM_OSC];
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
    //************************
    int m_pIndex;                        //for mapping commands to parameters
    bool m_parameterSelect;
    float m_oldKnobValue;
    float m_low, m_high;                       //for range mapping
    float m_mappedKnobValue[m_NUM_STRINGS][m_NUM_EFFECTS];
    float m_rawKnobValue;
    int m_str;
    bool m_stringSelect;                  //for keyboard processing

//=============================
//Private Function Declarations
//=============================
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
    void ProcessKeyboardData(Martone * pStr[]);
    void ProcessBluetoothDataData(int string);
    void ProcessKnobData();
    void StartOscPoly(int midiNote, int vel, int string, int wobble, int offset);
    void StopOscPoly(int note, int vel, int string, int offset);
    void StartOscMono(int midiNote, int offset, int string, int vel);
    void StopOscMono(int midiNote, int vel, int string, int offset);
    void KeyBuff(int midiNote, int vel, int string, int wobble, int offset, bool playNote);
    void LfoUpdate(bool retrig, int mode, float FILtop, float FILbottom);
    void GetReleaseState();
    void UpdateSettings(int pIndex, Martone * pStr[],int m_str);

    void SetFilter();
    void SetOsc(float m_volume);
    void SetADSR(float attack, float decay, float sustain, float release, int target);
    void ADSRoff();
//***************************************************************************************************
protected:


};
#endif
//****************************************************************************************************
    
    
    
    
    //********************************Set-up****************************************
    //  void SetInitialSettings();
    //     /***/void SetString();
    //     /***/void ReinitializeString(int string);
    //     /********/float ApplyScaleMask(const float tuningArray[][NUM_NOTES_INST], const int scaleMask[][NUM_NOTES_STRING], int string); //applies scale mask to tuning array. Stores results into global 'tempNotesArray'.
    //     /********/int GetScaleSteps(const int scaleMask[][NUM_NOTES_STRING], int string);
    //     /********/void InitScale(int steps, float tempNotesArray[][NUM_NOTES_INST], int numberOfNotes, int string);  //turns 1 octave 'tempNotesArray' scale into 12 octave scale.
    //     /********/void TransposeScale(int octave, float startNote, int string);
    //     /********/void SetADSR(float atk, float dec, float sus, float rel);
    //     //*********************************Loop*****************************************
    //     void ProcessKeyboardData();
    //     /***/void UpdateSettings(int pIndex, int str);
    //     /********/void SetVolume();
    //     //////////void ReinitializeString(int string);
    //     /********/void SetOsc(int str);
    //     /********/void SetFilter(int str);
    //     void ParseBluetoothData();                                                              //for parsing bluetooth data.
    //     void ProcessBluetoothData(int string);
    //     void GetReleaseState();
    //     void LfoUpdate(bool retrig, int mode, float FILtop, float FILbottom);
    // //********************************Callback Functions********************************************
    //     void MyNoteOn(byte channel, byte note, byte velocity);                        //Poly Mode
    //     /////void SetADSR(float atk, float dec, float sus, float rel);
    //     /***/void StartOscPoly(int midiNote, int vel, int string, int wobble, int offset); //inside MyNoteOn callback function.
    //     //////////void LfoUpdate(bool retrig, int mode, float FILtop, float FILbottom);
    //     /********/const char *GetNoteName(int midi_note);
    //     /***************/ int GetNoteNumber(int midi_note);
    //     /********/int GetOctave(float midi_note);

    //     void MyNoteOff(byte channel, byte note, byte velocity);                       //Poly Mode
    //     /***/void SetADSR(float atk, float dec, float sus, float rel);
    //     /***/void StopOscPoly(int note, int vel, int string, int offset);                  //inside MyNoteOff callback function. //turns on 4 waveforms for 10 voices.
    //     /////const char *GetNoteName(int midi_note);
    //     //////////// int GetNoteNumber(int midi_note);

    //     //void MyNoteOn(byte channel, byte note, byte velocity);                        //Callback function. Mono Mode
    //     /*****/void KeyBuff(int midiNote, int vel, int string, int wobble, int offset, bool playNote);
    //     /***********/void StartOscMono(int midiNote, int offset, int string, int vel);
    //     //////////////////const char *GetNoteName(int midi_note);
    //     //////////////////int GetOctave(float midi_note);

    //     //void MyNoteOff(byte channel, byte note, byte velocity);                        //Callback function. Mono Mode
    //     /*****/void StopOscMono(int midiNote, int vel, int string, int offset);
    //     /**********/const char *GetNoteName(int midi_note);
    //     /*****************/ int GetNoteNumber(int midi_note);

