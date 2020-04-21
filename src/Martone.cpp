//====================
//Class Implementation
//====================
#include <Arduino.h>
#include <Audio.h>
#include <USBHost_t36.h>
//#include <Fastled.h>
#include "Martone.h"

//=================
//Public Constants
//=================
   const int waveforms[] = {
    WAVEFORM_SINE,               //0
    WAVEFORM_SAWTOOTH,           //1
    WAVEFORM_SQUARE,             //2
    WAVEFORM_TRIANGLE,           //3
    WAVEFORM_ARBITRARY,          //4
    WAVEFORM_PULSE,              //5
    WAVEFORM_SAWTOOTH_REVERSE,   //6
    WAVEFORM_SAMPLE_HOLD,        //7
    WAVEFORM_TRIANGLE_VARIABLE}; //8

//********************************************************************************
//============
//Constructors
//============
Martone::Martone()
{
    m_octave = -3;
    m_startNote = A;
    m_scale = chromatic;
    m_volume = .9;
    m_filtFreqCutoff = 700;
    m_filtRes = 1;
    m_attack = 100;
    m_decay = 35;
    m_sustain = 1;
    m_release = 40;
    //m_lfoShape;
    m_lfoMode = 1;
    m_lfoSpeed = 7000 * 0.7;
    m_lfoDepth = 0;
    m_lfoPitch = 1;
    //m_lfo;
    // m_lfoRange;
    m_filtPercent = 1;
    m_interpolate = false;
    m_poly = true;
    m_temperament = justTemp;
    // m_electrode3D;
    m_pIndex = 0; //for mapping commands to parameters
    m_parameterSelect = false;
    m_mappedKnobValue[m_NUM_STRINGS][m_NUM_EFFECTS] = {0};
    m_str = 0;
    m_stringSelect = false;
}

Martone::~Martone() {}

//*****************************************************************************
//=================
//Public Functions
//=================
void Martone::Initialize()
{
    delay(5000); // 3 second delay for recovery
    Serial.begin(115200);
    AudioMemory(20);
    sgtl5000_1.enable();
    sgtl5000_1.volume(0.4);
    for (int j = m_NUM_STRINGS-1; j >= 0; j--)
    {
        for (int i = 0; i < m_NUM_OSC; i++)
        {
            AssignOsc(i, j);
        }
    }
    SetADSR(1, 2, 3, 4, false);
    Serial.println("Martone Set-up Complete!");
}
//********************************************************************
void Martone::AssignOsc(u8 osc, u8 string) const
{
    if (osc == 0) //osc 1
    {
        osc1a.begin(waveforms[str[string].m_oscW[osc]]);
        osc1a.amplitude(str[string].m_oscV[osc]);
        osc1a.frequency(str[string].m_freq[osc]);
        filtosc1a.frequency(str[m_str].m_freqCut[m_osc]); 
        //Serial.println(str[string].m_oscW[osc]);
    }
    if (osc == 1) //osc 2
    {
        osc1b.begin(waveforms[str[string].m_oscW[osc]]);
        osc1b.amplitude(str[string].m_oscV[osc]);
        osc1b.frequency(str[string].m_freq[osc]);
        filtosc1b.frequency(str[m_str].m_freqCut[m_osc]); 
        //Serial.println(str[string].m_oscW[osc]);
    }
    if (osc == 2) //osc 3
    {
        osc1c.begin(waveforms[str[string].m_oscW[osc]]);
        osc1c.amplitude(str[string].m_oscV[osc]);
        osc1c.frequency(str[string].m_freq[osc]);
        filtosc1c.frequency(str[m_str].m_freqCut[m_osc]); 
        //Serial.println(str[string].m_oscW[osc]);
    }
    if (osc == 3) //osc 4
    {
        osc1n.amplitude(str[string].m_oscV[osc]);
         filtosc1n.frequency(str[m_str].m_freqCut[m_osc]); 
        //Serial.println(str[string].m_oscV[osc]);
    }
    if (osc == 4) //all oscillators selected
    {
        osc1a.begin(waveforms[str[string].m_oscW[0]]);
        osc1a.amplitude(str[string].m_oscV[0]);
        osc1a.frequency(str[string].m_freq[osc]);
        filtosc1a.frequency(str[m_str].m_freqCut[m_osc]); 

        osc1b.begin(waveforms[str[string].m_oscW[1]]);
        osc1b.amplitude(str[string].m_oscV[1]);
        osc1b.frequency(str[string].m_freq[osc]);
        filtosc1b.frequency(str[m_str].m_freqCut[m_osc]); 

        osc1c.begin(waveforms[str[string].m_oscW[2]]);
        osc1c.amplitude(str[string].m_oscV[2]);
        osc1c.frequency(str[string].m_freq[osc]);
        filtosc1c.frequency(str[m_str].m_freqCut[m_osc]); 

        osc1n.amplitude(0);
    }
}
//*************************************************************
void Martone::SetADSR(float attack, float decay, float sustain, float release, bool playNote)
{
    if (playNote == true)
    {
        ADSR1.noteOn();
        ADSRosc1a.noteOn();
        ADSRosc1b.noteOn();
        ADSRosc1c.noteOn();
        ADSRosc1n.noteOn();

        ADSR1.attack(1);     //default 10.5ms. max 11.88 seconds
        ADSR1.decay(35);     //default 35 ms. max 11.88 seconds
        ADSR1.sustain(1);    //0-1
        ADSR1.release(2000); //default 300ms. max 11.88 seconds

        ADSRosc1a.attack(900);  //tri
        ADSRosc1b.attack(800);  //saw
        ADSRosc1c.attack(300);  //square
        ADSRosc1n.attack(1000); //noise

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
    else
    {
        ADSR1.attack(1);     //default 10.5ms. max 11.88 seconds
        ADSR1.decay(35);     //default 35 ms. max 11.88 seconds
        ADSR1.sustain(1);    //0-1
        ADSR1.release(2000); //default 300ms. max 11.88 seconds

        ADSRosc1a.attack(900);  //tri
        ADSRosc1b.attack(800);  //saw
        ADSRosc1c.attack(300);  //square
        ADSRosc1n.attack(1000); //noise

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
}
//************************************************************************
void Martone::SetOsc(u8 string, u8 osc, float volume, u8 waveform, int frequency, int freqCut)
{
    Serial.println("SetOsc");
    str[string - 1].m_oscV[osc - 1] = volume;
    str[string - 1].m_oscW[osc - 1] = waveform;
    str[string - 1].m_freq[osc - 1] = frequency;
    str[string - 1].m_freqCut[osc - 1] = freqCut;

}
//************************************************************
void Martone::Update()
{
    ProcessKeyboardData(); //defined in KeyboardControl.cpp file
}
//*********************************************************
void Martone::HandleNoteOn(u8 channel, u8 note, u8 velocity)
{
    SetADSR(1, 2, 3, 4, true);
    AssignOsc(m_osc, m_string);
    //SetFilter();
    Serial.println("***");
}
//*************************************************************
void Martone::HandleNoteOff(u8 channel, u8 note, u8 velocity)
{
    ADSRoff();
    Serial.println("***");
}
//**************************************************************
void Martone::SetFilter()
{
    filter1.frequency(str[m_str].m_freqCut[m_osc]);
    filter1.resonance(1);

    filtosc1a.frequency(str[m_str].m_freqCut[m_osc]); //tri
    filtosc1a.resonance(1);

    filtosc1b.frequency(str[m_str].m_freqCut[m_osc]); //saw
    filtosc1b.resonance(1);

    filtosc1c.frequency(str[m_str].m_freqCut[m_osc]); //square
    filtosc1c.resonance(1);

    filtosc1n.frequency(str[m_str].m_freqCut[m_osc]); //noise
    filtosc1n.resonance(1);
}
//***********************************************************
void Martone::ADSRoff()
{
    ADSR1.noteOff();
    ADSRosc1a.noteOff();
    ADSRosc1b.noteOff();
    ADSRosc1c.noteOff();
    ADSRosc1n.noteOff();
}
//**************************************************************
void Martone::ShowWaveform(u8 m_waveform)
{
}
//*********************************************************
void Martone::SetString(u8 string, s8 octave, u8 startNote, u8 scale, float volume, float filtFreqCutoff, float filtRes, float attack, float decay, float sustain, float release, u8 lfoShape, u8 lfoMode, float lfoSpeed, float lfoDepth, float lfoPitch, float lfo, float lfoRange, float filtPercent, bool interpolate, bool poly, u8 temperament, u8 electrode3D)
{
    //     m_octave = octave;
    //     m_startNote = startNote;
    //     m_scale = scale;

    //     m_volume = volume;
    //     m_filtFreqCutoff = filtFreqCutoff;
    //     m_filtRes = filtRes;
    //     m_attack = attack;
    //     m_decay = decay;
    //     m_sustain = sustain;
    //     m_release = release;
    //     m_lfoShape = lfoShape;
    //     m_lfoMode = lfoMode;
    //     m_lfoSpeed = lfoSpeed;
    //     m_lfoDepth = lfoDepth;
    //     m_lfoPitch = lfoPitch;
    //     m_lfo = lfo;
    //     m_lfoRange = lfoRange;

    //     m_filtPercent = filtPercent;
    //     m_interpolate = interpolate;
    //     m_poly = poly;
    //     m_temperament = temperament;
    //     m_electrode3D = electrode3D;
}
//*************************************************************

//*****************************************************************
//int Martone::SetWaveform(int waveform, int target)
//{
// switch (waveform)
// {
// case 1:
//     if (target < m_NUM_OSC)
//         m_waveform[target] = WAVEFORM_SINE;
//     else
//         for (int i = 0; i < m_NUM_OSC; i++)
//             m_waveform[i] = WAVEFORM_SINE;
//     return m_WAVEFORMS[waveform];
// case 2:
//     if (target < m_NUM_OSC)
//         m_waveform[target] = WAVEFORM_TRIANGLE;
//     else
//         for (int i = 0; i < m_NUM_OSC; i++)
//             m_waveform[i] = WAVEFORM_TRIANGLE;
//     return m_WAVEFORMS[waveform];
// case 3:
//     if (target < m_NUM_OSC)
//         m_waveform[target] = WAVEFORM_TRIANGLE_VARIABLE;
//     else
//         for (int i = 0; i < m_NUM_OSC; i++)
//             m_waveform[i] = WAVEFORM_TRIANGLE_VARIABLE;
//     return m_WAVEFORMS[waveform];
// case 4:
//     if (target < m_NUM_OSC)
//         m_waveform[target] = WAVEFORM_SQUARE;
//     else
//         for (int i = 0; i < m_NUM_OSC; i++)
//             m_waveform[i] = WAVEFORM_SQUARE;
//     return m_WAVEFORMS[waveform];
// case 5:
//     if (target < m_NUM_OSC)
//         m_waveform[target] = WAVEFORM_SAWTOOTH;
//     else
//         for (int i = 0; i < m_NUM_OSC; i++)
//             m_waveform[i] = WAVEFORM_SAWTOOTH;
//     return m_WAVEFORMS[waveform];
// case 6:
//     if (target < m_NUM_OSC)
//         m_waveform[target] = WAVEFORM_SAWTOOTH_REVERSE;
//     else
//         for (int i = 0; i < m_NUM_OSC; i++)
//             m_waveform[i] = WAVEFORM_SAWTOOTH_REVERSE;
//     return m_WAVEFORMS[waveform];
// case 7:
//     if (target < m_NUM_OSC)
//         m_waveform[target] = WAVEFORM_ARBITRARY;
//     else
//         for (int i = 0; i < m_NUM_OSC; i++)
//             m_waveform[i] = WAVEFORM_ARBITRARY;
//     return m_WAVEFORMS[waveform];
// case 8:
//     if (target < m_NUM_OSC)
//         m_waveform[target] = WAVEFORM_PULSE;
//     else
//         for (int i = 0; i < m_NUM_OSC; i++)
//             m_waveform[i] = WAVEFORM_PULSE;
//     return m_WAVEFORMS[waveform];
// case 9:
//     if (target < m_NUM_OSC)
//         m_waveform[target] = WAVEFORM_SAMPLE_HOLD;
//     else
//         for (int i = 0; i < m_NUM_OSC; i++)
//             m_waveform[i] = WAVEFORM_SAMPLE_HOLD;
//     return m_WAVEFORMS[waveform];
// default:
//     Serial.println("SetWaveform error");
//     break;
// }
//}
//*********************************************************