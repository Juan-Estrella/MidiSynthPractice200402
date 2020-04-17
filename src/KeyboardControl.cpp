#include "Martone.h"

void Martone::ProcessKeyboardData(Martone *pStr[])
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
            UpdateSettings(m_pIndex, pStr, m_str, m_osc);
            Serial.println(m_mappedKnobValue[m_str][m_pIndex]);
        }
    }
    //****************************************************
    if (Serial.available() > 0)
    {
        int inByte = Serial.read();
        switch (inByte)
        {
        case '1': //Select string 1
            m_str = 0;
            m_stringSelect = true;
            Serial.println("String 1 Selected");
            break;
        case '2': //Select string 2
            m_str = 1;
            m_stringSelect = true;
            Serial.println("String 2 Selected");
            break;
        case '3': //Select string 3
            m_str = 2;
            m_stringSelect = true;
            Serial.println("String 3 Selected");
            break;
        case '4': //Select string 4
            m_str = 3;
            m_stringSelect = true;
            Serial.println("String 4 Selected");
            break;
            //************************************************************
        case '~': //Oscillator 1 select
            m_pIndex = 0;
            m_osc = 0;
            m_oscSelect = true;
            Serial.println("Oscillator 1 Selected");
            break;
        case '!': //Oscillator 2 select
            m_pIndex = 1;
            m_osc = 1;
            m_oscSelect = true;
            Serial.println("Oscillator 2 Selected");
            break;
        case '@': //Oscillator 3 select
            m_pIndex = 2;
            m_osc = 2;
            m_oscSelect = true;
            Serial.println("Oscillator 3 Selected");
            break;
        case '#': //Oscillator 4 select
            m_pIndex = 3;
            m_osc = 3;
            m_oscSelect = true;
            Serial.println("Noise Oscillator Selected");
            break;
        case '$': //All Oscillators Selected
            m_pIndex = 4;
            m_osc = 4;
            m_oscSelect = true;
            Serial.println("All Oscillators Selected ");
            break;
        case '%': //waveform select
            m_pIndex = 5;
            m_low = 0;
            m_high = 8;
            m_parameterSelect = true;
            Serial.println("Waveform Select ");
            break;
        case '^': //Volume
            m_pIndex = 6;
            m_low = 0;
            m_high = 1;
            m_parameterSelect = true;
            if(m_osc<m_NUM_OSC)
            {
            Serial.print("Oscillator ");
            Serial.print(m_osc+1);
            Serial.println(" Gain");
            }else  Serial.println("All Oscillator Gain");
            break;

        default:
            // Serial.println("Invalid Entry");
            break;
        }
    }
}