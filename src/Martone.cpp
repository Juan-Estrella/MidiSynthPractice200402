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
      //************************
    int m_pIndex = 0;                        //for mapping commands to parameters
    bool m_parameterSelect = false;  
    float m_mappedKnobValue[m_NUM_STRINGS][m_NUM_EFFECTS] = {0};
    int m_str = 0;
    bool m_stringSelect = false;               


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
    SetOsc(m_volume);
    Serial.println("Martone Set-up Complete!");
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
void Martone::Update(Martone * pStr[])
{
    //Serial.println(pStr[0]->m_octave);
    ProcessKeyboardData(pStr);
}
//*****************************************************
void Martone::Troubleshoot()
{
    Serial.println("Troubleshoot");
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
void Martone::SetOsc(float m_volume)
{

    //***Voice 1
    osc1a.begin(WAVEFORM_TRIANGLE);
    osc1a.amplitude(m_volume);
    osc1a.frequency(220);

    osc1b.begin(WAVEFORM_SAWTOOTH);
    osc1b.amplitude(m_volume);
    osc1b.frequency(440);

    osc1c.begin(WAVEFORM_SQUARE);
    osc1c.amplitude(m_volume);
    osc1c.frequency(880);

    osc1n.amplitude(m_volume);
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
void Martone::ProcessKeyboardData(Martone * pStr[])
{
    // pStr[0]->m_octave =7;
    // Serial.println(pStr[0]->m_octave);
    if (m_parameterSelect == true)
  {
    m_rawKnobValue = analogRead(A13); // double read?
    m_rawKnobValue = analogRead(A13); // double read?
    m_rawKnobValue = constrain(m_rawKnobValue, 5, 1023);
    m_mappedKnobValue[m_str][m_pIndex] = map(m_rawKnobValue, 1023, 5, m_low, m_high);

    if (m_rawKnobValue < (m_oldKnobValue - 4) || m_rawKnobValue > (m_oldKnobValue + 4))
    {
      m_oldKnobValue = m_rawKnobValue;
      UpdateSettings(m_pIndex, pStr, m_str);
      Serial.println(m_mappedKnobValue[m_str][m_pIndex]);
    }
  }
  //****************************************************
  if (Serial.available() > 0)
  {
    int inByte = Serial.read();
    switch (inByte)
    {
      case '1':           //Select string 1
        m_str = 0;
        m_stringSelect = true;
        Serial.println("String 1 Selected");
        break;

      case '2':           //Select string 2
        m_str = 1;
        m_stringSelect = true;
        Serial.println("String 2 Selected");
        break;

      case '3':           //Select string 3
        m_str = 2;
        m_stringSelect = true;
        Serial.println("String 3 Selected");
        break;

      case '4':           //Select string 4
        m_str = 3;
        m_stringSelect = true;
        Serial.println("String 4 Selected");
        break;

      //************************************************************
      case '~':           //waveform 1 gain
        m_pIndex = 0;
        m_low = 0;
        m_high = 1;
        m_parameterSelect = true;
        Serial.print("Waveform 1 Gain ");
        break;

      case '!':           //waveform 1 select
        m_pIndex = 1;
        m_low = 0;
        m_high = 10;
        m_parameterSelect = true;
        Serial.print("Select Waveform 1 ");
        break;
      default:
        // Serial.println("Invalid Entry");
        break;
    }
  }
}
//*************************************************************
    void Martone::UpdateSettings(int pIndex, Martone * pStr[], int m_str)
{
  float xSpeed;
  switch (pIndex)
  {
    case 0:
      pStr[m_str]->m_volume = m_mappedKnobValue[m_str][pIndex];                   //'~' Set string volume
      //Serial.println(pStr[m_str]->m_volume);
      SetOsc(pStr[m_str]->m_volume);
      //SetVolume();
      break;

    case 1:
      //sp.waveform1[str] = waveforms[(int)m_mappedKnobValue[str][pIndex]];      //'!' Set Waveform 1
      break;
       default:
      break;
  }
}
//**************************************************************
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
        return m_WAVEFORMS[waveform];
    case 2:
        if (target < m_NUM_OSC)
            m_waveform[target] = WAVEFORM_TRIANGLE;
        else
            for (int i = 0; i < m_NUM_OSC; i++)
                m_waveform[i] = WAVEFORM_TRIANGLE;
        return m_WAVEFORMS[waveform];
    case 3:
        if (target < m_NUM_OSC)
            m_waveform[target] = WAVEFORM_TRIANGLE_VARIABLE;
        else
            for (int i = 0; i < m_NUM_OSC; i++)
                m_waveform[i] = WAVEFORM_TRIANGLE_VARIABLE;
        return m_WAVEFORMS[waveform];
    case 4:
        if (target < m_NUM_OSC)
            m_waveform[target] = WAVEFORM_SQUARE;
        else
            for (int i = 0; i < m_NUM_OSC; i++)
                m_waveform[i] = WAVEFORM_SQUARE;
        return m_WAVEFORMS[waveform];
    case 5:
        if (target < m_NUM_OSC)
            m_waveform[target] = WAVEFORM_SAWTOOTH;
        else
            for (int i = 0; i < m_NUM_OSC; i++)
                m_waveform[i] = WAVEFORM_SAWTOOTH;
        return m_WAVEFORMS[waveform];
    case 6:
        if (target < m_NUM_OSC)
            m_waveform[target] = WAVEFORM_SAWTOOTH_REVERSE;
        else
            for (int i = 0; i < m_NUM_OSC; i++)
                m_waveform[i] = WAVEFORM_SAWTOOTH_REVERSE;
        return m_WAVEFORMS[waveform];
    case 7:
        if (target < m_NUM_OSC)
            m_waveform[target] = WAVEFORM_ARBITRARY;
        else
            for (int i = 0; i < m_NUM_OSC; i++)
                m_waveform[i] = WAVEFORM_ARBITRARY;
        return m_WAVEFORMS[waveform];
    case 8:
        if (target < m_NUM_OSC)
            m_waveform[target] = WAVEFORM_PULSE;
        else
            for (int i = 0; i < m_NUM_OSC; i++)
                m_waveform[i] = WAVEFORM_PULSE;
        return m_WAVEFORMS[waveform];
    case 9:
        if (target < m_NUM_OSC)
            m_waveform[target] = WAVEFORM_SAMPLE_HOLD;
        else
            for (int i = 0; i < m_NUM_OSC; i++)
                m_waveform[i] = WAVEFORM_SAMPLE_HOLD;
        return m_WAVEFORMS[waveform];
    default:
        Serial.println("SetWaveform error");
        break;
    }
}
//*********************************************************