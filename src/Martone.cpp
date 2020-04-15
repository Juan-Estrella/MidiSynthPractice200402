//====================
//Class Implementation
//====================
#include <Arduino.h>
#include <Audio.h>
#include <USBHost_t36.h>
//#include "Functions.h"
//#include "GuiTool.h"
//#include "LfoUpdate.h"
//#include "Globals.h"
#include "Martone.h"

//=================
//Public Constants
//=================
static const int waveforms[] ={
        WAVEFORM_SINE,
        WAVEFORM_TRIANGLE,
        WAVEFORM_TRIANGLE_VARIABLE,
        WAVEFORM_SQUARE,
        WAVEFORM_SAWTOOTH,
        WAVEFORM_SAWTOOTH_REVERSE,
        WAVEFORM_ARBITRARY,
        WAVEFORM_PULSE,
        WAVEFORM_SAMPLE_HOLD};

//********************************************************************************
//============
//Constructors
//============
Martone::Martone()
{
    m_waveform[0] = WAVEFORM_SAWTOOTH;
    m_octave = -3;
    m_startNote = A;
    m_scale = chromatic;

    m_volume = .9;
    m_filtFreqCutoff = 700;
    m_filtRes = 1;
    m_attack = .1;
    m_decay = 35;
    m_sustain = 1;
    m_release = 40;
    m_lfoShape;
    m_lfoMode = 1;
    m_lfoSpeed = 7000 * 0.7;
    m_lfoDepth = 0;
    m_lfoPitch = 1;
    m_lfo;
    m_lfoRange;

    m_filtPercent = 1;
    m_interpolate = false;
    m_poly = true;
    m_temperament = justTemp;
    m_electrode3D;
}
//******************************
Martone::Martone(int waveform, int octave, int startNote, int scale, float volume, float filtFreqCutoff, float filtRes, float attack, float decay, float sustain, float release, int lfoShape, int lfoMode, float lfoSpeed, float lfoDepth, float lfoPitch, float lfo, float lfoRange, float filtPercent, bool interpolate, bool poly, int temperament, int electrode3D)
{
    for (int i = 0; i < m_NUM_OSC; i++)
    {
        m_waveform[i] = waveform;
    }
    m_octave = octave;
    m_startNote = startNote;
    m_scale = scale;

    m_volume = volume;
    m_filtFreqCutoff = filtFreqCutoff;
    m_filtRes = filtRes;
    m_attack = attack;
    m_decay = decay;
    m_sustain = sustain;
    m_release = release;
    m_lfoShape = lfoShape;
    m_lfoMode = lfoMode;
    m_lfoSpeed = lfoSpeed;
    m_lfoDepth = lfoDepth;
    m_lfoPitch = lfoPitch;
    m_lfo = lfo;
    m_lfoRange = lfoRange;

    m_filtPercent = filtPercent;
    m_interpolate = interpolate;
    m_poly = poly;
    m_temperament = temperament;
    m_electrode3D = electrode3D;
}

Martone::~Martone() {}

//=================
//Public Functions
//=================
void Martone::Initialize()
{
    delay(3000); // 3 second delay for recovery
    Serial.begin(115200);
    AudioMemory(20);
    sgtl5000_1.enable();
    sgtl5000_1.volume(0.4);
    SetOsc();
    Serial.println("Start up Complete!");
}
//************************************************************
void Martone::HandleNoteOn(int channel, int note, int velocity)
{
    SetADSR(1, 2, 3, 4, 5);
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
}

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
void Martone::SetOsc()
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
}
//*********************************************************
void Martone::SetADSR(float attack, float decay, float sustain, float release, int target)
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
int Martone::SetWaveform(int waveform, int target)
{
    switch (waveform)
    {
    case 1:
        if (target < m_NUM_OSC)
            m_waveform[target] = WAVEFORM_SINE;
        else
            for (int i = 0; i < m_NUM_OSC; i++)
                m_waveform[i] = WAVEFORM_SINE;
        return waveforms[waveform];
    case 2:
        if (target < m_NUM_OSC)
            m_waveform[target] = WAVEFORM_TRIANGLE;
        else
            for (int i = 0; i < m_NUM_OSC; i++)
                m_waveform[i] = WAVEFORM_TRIANGLE;
        return waveforms[waveform];
    case 3:
        if (target < m_NUM_OSC)
            m_waveform[target] = WAVEFORM_TRIANGLE_VARIABLE;
        else
            for (int i = 0; i < m_NUM_OSC; i++)
                m_waveform[i] = WAVEFORM_TRIANGLE_VARIABLE;
        return waveforms[waveform];
    case 4:
        if (target < m_NUM_OSC)
            m_waveform[target] = WAVEFORM_SQUARE;
        else
            for (int i = 0; i < m_NUM_OSC; i++)
                m_waveform[i] = WAVEFORM_SQUARE;
        return waveforms[waveform];
    case 5:
        if (target < m_NUM_OSC)
            m_waveform[target] = WAVEFORM_SAWTOOTH;
        else
            for (int i = 0; i < m_NUM_OSC; i++)
                m_waveform[i] = WAVEFORM_SAWTOOTH;
        return waveforms[waveform];
    case 6:
        if (target < m_NUM_OSC)
            m_waveform[target] = WAVEFORM_SAWTOOTH_REVERSE;
        else
            for (int i = 0; i < m_NUM_OSC; i++)
                m_waveform[i] = WAVEFORM_SAWTOOTH_REVERSE;
        return waveforms[waveform];
    case 7:
        if (target < m_NUM_OSC)
            m_waveform[target] = WAVEFORM_ARBITRARY;
        else
            for (int i = 0; i < m_NUM_OSC; i++)
                m_waveform[i] = WAVEFORM_ARBITRARY;
        return waveforms[waveform];
    case 8:
        if (target < m_NUM_OSC)
            m_waveform[target] = WAVEFORM_PULSE;
        else
            for (int i = 0; i < m_NUM_OSC; i++)
                m_waveform[i] = WAVEFORM_PULSE;
        return waveforms[waveform];
    case 9:
        if (target < m_NUM_OSC)
            m_waveform[target] = WAVEFORM_SAMPLE_HOLD;
        else
            for (int i = 0; i < m_NUM_OSC; i++)
                m_waveform[i] = WAVEFORM_SAMPLE_HOLD;
        return waveforms[waveform];
    default:
        Serial.println("SetWaveform error");
        break;
    }
}
//*********************************************************