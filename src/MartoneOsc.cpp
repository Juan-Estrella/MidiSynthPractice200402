#include "MartoneOsc.h"

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

//============
//Constructors
//============
MartoneOsc::MartoneOsc()
{
    m_oscWave[0] = 0;
    m_oscWave[1] = 0;
    m_oscWave[2] = 0;
    m_oscVol[0] = .5;
    m_oscVol[1] = .5;
    m_oscVol[2] = .5;
    m_oscVol[3] = .5;
}
//******************************
MartoneOsc::MartoneOsc(int osc1W, int osc2W, int osc3W, float osc1V, float osc2V, float osc3V, float osc4V)// int octave, int startNote, int scale, float volume, float filtFreqCutoff, float filtRes, float attack, float decay, float sustain, float release, int lfoShape, int lfoMode, float lfoSpeed, float lfoDepth, float lfoPitch, float lfo, float lfoRange, float filtPercent);
{
    m_oscWave[0] = osc1W;
    m_oscWave[1] = osc2W;
    m_oscWave[2] = osc3W;

    m_oscVol[0] = osc1V;
    m_oscVol[1] = osc2V;
    m_oscVol[2] = osc3V;
    m_oscVol[3] = osc4V;
}

MartoneOsc::~MartoneOsc() {}

//=================
//Public Functions
//=================
void MartoneOsc::Initialize(Martone *pStr[], MartoneOsc *pOsc[])
{
    delay(3000); // 3 second delay for recovery
    Serial.begin(115200);
    AudioMemory(20);
    sgtl5000_1.enable();
    sgtl5000_1.volume(0.4);
    for (int i = 0; i < m_NUM_OSC; i++)
        SetOsc(m_volume, m_oscWave[m_osc], i, pStr, pOsc);
    SetADSR(1, 2, 3, 4, false);
    Serial.println("Martone Set-up Complete!");
}
//************************************************************
void MartoneOsc::HandleNoteOn(int channel, int note, int velocity)
{
    SetADSR(1, 2, 3, 4, 5);
    SetFilter();
    Serial.println("***");
}
//*************************************************************
void MartoneOsc::HandleNoteOff(int channel, int note, int velocity)
{
    ADSRoff();
    Serial.println("***");
}
//*************************************************************
void MartoneOsc::Update(Martone *pStr[], MartoneOsc *pOsc[])
{
    ProcessKeyboardData(pStr, pOsc);
}
//*****************************************************

//=================
//Private Functions
//=================

void MartoneOsc::SetFilter()
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
void MartoneOsc::SetOsc(float m_volume, int m_waveform, int m_osc, Martone *pStr[], MartoneOsc *pOsc[])
{

    //***Voice 1
    if (m_osc == 0) //osc 1
    {
        osc1a.begin(waveforms[pOsc[m_str]->m_oscWave[m_osc]]);
        osc1a.amplitude(pOsc[m_str]->m_oscVol[m_osc]);
        osc1a.frequency(220);
    }
    if (m_osc == 1) //osc 2
    {
        osc1b.begin(waveforms[m_oscWave[m_osc]]);
        osc1b.amplitude(pOsc[m_str]->m_oscVol[m_osc]);
        osc1b.frequency(440);
    }
    if (m_osc == 2) //osc 3
    {
        osc1c.begin(waveforms[m_oscWave[m_osc]]);
        osc1c.amplitude(pOsc[m_str]->m_oscVol[m_osc]);
        osc1c.frequency(880);
    }
    if (m_osc == 3) //osc 4
    {
        osc1n.amplitude(pOsc[m_str]->m_oscVol[m_osc]);
    }
    if (m_osc == 4) //all oscillators selected
    {
        osc1a.begin(waveforms[m_oscWave[0]]);
        osc1a.amplitude(pOsc[m_str]->m_oscVol[m_osc]);
        osc1a.frequency(220);

        osc1b.begin(waveforms[m_oscWave[1]]);
        osc1b.amplitude(pOsc[m_str]->m_oscVol[m_osc]);
        osc1b.frequency(440);

        osc1c.begin(waveforms[m_oscWave[2]]);
        osc1c.amplitude(pOsc[m_str]->m_oscVol[m_osc]);
        osc1c.frequency(880);

        osc1n.amplitude(0);
    }
}
//*********************************************************
void MartoneOsc::UpdateSettings(int pIndex, Martone *pStr[], int m_str, int m_osc,  MartoneOsc *pOsc[])

{
    //float xSpeed;
    switch (pIndex)
    {
    case 5: //'%' Set Osc Waveform
        pOsc[m_str]->m_oscWave[m_osc] = waveforms[(int)m_mappedKnobValue[m_str][pIndex]];
        SetOsc(pOsc[m_str]->m_oscVol[m_osc], pOsc[m_str]->m_oscWave[m_osc], m_osc, pStr, pOsc);
        break;
    case 6: //'^' Set Osc Volume
        pOsc[m_str]->m_oscVol[m_osc] = m_mappedKnobValue[m_str][pIndex];
        SetOsc(pOsc[m_str]->m_oscVol[m_osc], pOsc[m_str]->m_oscWave[m_osc], m_osc, pStr, pOsc);
        break;

    default:
        break;
    }
}
//*************************************************************
void MartoneOsc::SetADSR(float attack, float decay, float sustain, float release, bool playNote)
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
void MartoneOsc::ADSRoff()
{
    ADSR1.noteOff();
    ADSRosc1a.noteOff();
    ADSRosc1b.noteOff();
    ADSRosc1c.noteOff();
    ADSRosc1n.noteOff();
}
//**************************************************************
void MartoneOsc::ShowWaveform(int m_waveform)
{
}

//*****************************************************************
//int MartoneOsc::SetWaveform(int waveform, int target)
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