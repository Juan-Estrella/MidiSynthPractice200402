//====================
//Class Implementation
//====================
#include <Arduino.h>
#include <Audio.h>
#include <USBHost_t36.h>
#include "Martone.h"

//=================
//Public Constants
//=================
static const int waveforms[] = {
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
//*****************************************************************************
Martone::~Martone() {}

//=================
//Public Functions
//=================
void Martone::SetOsc(int string, int osc1W, int osc2W, int osc3W, float osc1V, float osc2V, float osc3V, float osc4V)
{
    Serial.println("SetOsc");
    str[0].m_oscV[0] = osc1V;
    str[string - 1].m_oscV[1] = osc2V;
    str[string - 1].m_oscV[2] = osc3V;
    str[string - 1].m_oscV[3] = osc4V;

    str[string - 1].m_oscW[0] = osc1W;
    str[string - 1].m_oscW[1] = osc2W;
    str[string - 1].m_oscW[2] = osc3W;
}
//****************************************************************
void Martone::AssignOsc(float m_volume, int m_waveform, int m_osc)
{
    //***Voice 1
    if (m_osc == 0) //osc 1
    {
        osc1a.begin(waveforms[str[0].m_oscW[0]]);
        osc1a.amplitude(str[0].m_oscV[0]);
        osc1a.frequency(220);
    }
    if (m_osc == 1) //osc 2
    {
        osc1b.begin(waveforms[str[0].m_oscW[1]]);
        osc1b.amplitude(str[0].m_oscV[1]);
        osc1b.frequency(440);
    }
    if (m_osc == 2) //osc 3
    {
        osc1c.begin(waveforms[str[0].m_oscW[2]]);
        osc1c.amplitude(str[0].m_oscV[2]);
        osc1c.frequency(880);
    }
    if (m_osc == 3) //osc 4
    {
        osc1n.amplitude(str[0].m_oscV[3]);
    }
    if (m_osc == 4) //all oscillators selected
    {
        osc1a.begin(waveforms[str[0].m_oscW[0]]);
        osc1a.amplitude(str[0].m_oscV[0]);
        osc1a.frequency(220);

        osc1b.begin(waveforms[str[0].m_oscW[1]]);
        osc1b.amplitude(str[0].m_oscV[1]);
        osc1b.frequency(440);

        osc1c.begin(waveforms[str[0].m_oscW[2]]);
        osc1c.amplitude(str[0].m_oscV[2]);
        osc1c.frequency(880);

        osc1n.amplitude(0);
    }
}
//*********************************************************
void Martone::SetString(int string, int octave, int startNote, int scale, float volume, float filtFreqCutoff, float filtRes, float attack, float decay, float sustain, float release, int lfoShape, int lfoMode, float lfoSpeed, float lfoDepth, float lfoPitch, float lfo, float lfoRange, float filtPercent, bool interpolate, bool poly, int temperament, int electrode3D)
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
void Martone::Initialize()
{
    delay(3000); // 3 second delay for recovery
    Serial.begin(115200);
    AudioMemory(20);
    sgtl5000_1.enable();
    sgtl5000_1.volume(0.4);
    for (int i = 0; i < m_NUM_OSC; i++)
        AssignOsc(str[0].m_oscV[i], str[0].m_oscW[i], i);
    SetADSR(1, 2, 3, 4, false);
    Serial.println("Martone Set-up Complete!");
}
//************************************************************
void Martone::HandleNoteOn(int channel, int note, int velocity)
{
    SetADSR(1, 2, 3, 4, true);
    SetFilter();
    Serial.println("***");
}
//*************************************************************
void Martone::HandleNoteOff(int channel, int note, int velocity)
{
    ADSRoff();
    Serial.println("***");
}
//*************************************************************
void Martone::Update()
{
    ProcessKeyboardData();
}
//*****************************************************

//=================
//Private Functions
//=================

void Martone::SetFilter()
{
    filter1.frequency(10000);
    filter1.resonance(1);

    filtosc1a.frequency(10000); //tri
    filtosc1a.resonance(1);

    filtosc1b.frequency(10000); //saw
    filtosc1b.resonance(1);

    filtosc1c.frequency(500); //square
    filtosc1c.resonance(1);

    filtosc1n.frequency(10000); //noise
    filtosc1n.resonance(1);
}
//*********************************************************
void Martone::UpdateSettings(int pIndex, int m_str, int m_osc)
{
    // float xSpeed;
    switch (pIndex)
    {
    case 5: //'%' Set Osc Waveform
        str[m_str].m_oscW[m_osc] = waveforms[(int)m_mappedKnobValue[m_str][pIndex]];
        AssignOsc(str[m_str].m_oscV[m_osc], str[m_str].m_oscW[m_osc], m_osc);
        break;
    case 6: //'^' Set Osc Volume
        str[m_str].m_oscV[m_osc] = m_mappedKnobValue[m_str][pIndex];
        AssignOsc(str[m_str].m_oscV[m_osc], str[m_str].m_oscW[m_osc], m_osc);
        break;

    default:
        break;
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
//***********************************************************
void Martone::ADSRoff()
{
    ADSR1.noteOff();
    ADSRosc1a.noteOff();
    ADSRosc1b.noteOff();
    ADSRosc1c.noteOff();
    ADSRosc1n.noteOff();
}

//************************************************************

//**************************************************************
void Martone::ShowWaveform(int m_waveform)
{
}

//*****************************************************************
int Martone::SetWaveform(int waveform, int target)
{
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
}
//*********************************************************