#include "Martone.h"

// const int waveforms[] = {
//     WAVEFORM_SINE,               //0
//     WAVEFORM_SAWTOOTH,           //1
//     WAVEFORM_SQUARE,             //2
//     WAVEFORM_TRIANGLE,           //3
//     WAVEFORM_ARBITRARY,          //4
//     WAVEFORM_PULSE,              //5
//     WAVEFORM_SAWTOOTH_REVERSE,   //6
//     WAVEFORM_SAMPLE_HOLD,        //7
//     WAVEFORM_TRIANGLE_VARIABLE}; //8
//extern Martone::stringParameters str[m_NUM_STRINGS];

void Martone::ProcessKeyboardData()
{
    if (m_parameterSelect == true)
    {
        m_rawKnobValue = analogRead(A13); // double read?
        m_rawKnobValue = analogRead(A13); // double read?
        m_rawKnobValue = constrain(m_rawKnobValue, 5, 1023);
        m_mappedKnobValue[m_str][m_pIndex] = map(m_rawKnobValue, 1023, 5, m_low, m_high);

        if (m_rawKnobValue < (m_oldKnobValue - 4) || m_rawKnobValue > (m_oldKnobValue + 4))
        {
            // if(m_rawKnobValue >= m_oldKnobValue)
            // m_mappedKnobValue[m_str][m_pIndex] += (m_setting+m_str)->m_oscV[m_osc];
            //  else
            // m_mappedKnobValue[m_str][m_pIndex] -= (m_setting+m_str)->m_oscV[m_osc];
            m_oldKnobValue = m_rawKnobValue;
            UpdateKeyboardData();
            //Serial.println(m_mappedKnobValue[m_str][m_pIndex]);
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
            Serial.println(" Volume");
            }else  Serial.println("All Oscillator Gain");
            break;
         case '&': //waveform frequency
            m_pIndex = 7;
            m_low = 0;
            m_high = 1;
            m_parameterSelect = true;
            Serial.println("Oscillator Frequency ");
            break;
        case '*': //Freqency Cutoff
            m_pIndex = 8;
            m_low = 0;
            m_high = 1;
            m_parameterSelect = true;
            Serial.println("Filter Frequency Cutoff");
            break;
        case '(': //Freqency Cutoff Slope
            m_pIndex = 9;
            m_low = 0;
            m_high = 10;
            m_parameterSelect = true;
            Serial.println("Filter Frequency Slope");
            break;
        case ')': //Filter Resonance
            m_pIndex = 10;
            m_low = 0;
            m_high = 1;
            m_parameterSelect = true;
            Serial.println("Filter Resonance");
            break;

        default:
            // Serial.println("Invalid Entry");
            break;
        }
    }
}
    //********************************************************************
void Martone::UpdateKeyboardData()
{
     float x = m_mappedKnobValue[m_str][m_pIndex];
     float n = str[m_str].m_filtSlope[m_osc];  
    // float xSpeed;
    switch (m_pIndex)
    {
    case 5: //'%' Set Osc Waveform
        //(m_setting+m_str)->m_oscW[m_osc];
        m_setting[m_str]->m_oscW[m_osc];
        str[m_str].m_oscW[m_osc] = waveforms[(int)m_mappedKnobValue[m_str][m_pIndex]];
        AssignOsc(m_osc, m_str);
        //Serial.println(str[m_str].m_oscW[m_osc]);
        //Serial.println((m_setting+m_str)->m_oscW[m_osc]);
        Serial.println(m_setting[m_str]->m_oscW[m_osc]);
        break;
    case 6: //'^' Set Osc Volume
        //(m_setting+m_str)->m_oscV[m_osc];
        m_setting[m_str]->m_oscV[m_osc];
        str[m_str].m_oscV[m_osc] = m_mappedKnobValue[m_str][m_pIndex];
        AssignOsc(m_osc, m_str);
        //Serial.println(str[m_str].m_oscV[m_osc]);
        Serial.println(m_setting[m_str]->m_oscV[m_osc]);
        break;
    case 7: //'&' Set Osc Frequency
   //(m_setting+m_str)->m_freq[m_osc];
        //str[m_str].m_freq[m_osc] = (int)m_mappedKnobValue[m_str][m_pIndex];
        str[m_str].m_freq[m_osc] = 10000* pow(   pow((1-(1-x)), (1/n)),   n);
        AssignOsc(m_osc, m_str);
        Serial.println(str[m_str].m_freq[m_osc]);
        break;
    case 8: //'*' Set Filter Frequency Cutoff
        str[m_str].m_freqCut[m_osc] = 10000* pow(   pow((1-(1-x)), (1/n)),   n);
        AssignOsc(m_osc, m_str);
        Serial.println(str[m_str].m_freqCut[m_osc]);
        break;
    case 9: //'(' Set Filter Slope
        str[m_str].m_filtSlope[m_osc] = m_mappedKnobValue[m_str][m_pIndex];
        AssignOsc(m_osc, m_str);
        Serial.println(str[m_str].m_filtSlope[m_osc]);
        break;
    case 10: //')' Set Filter Resonance
        str[m_str].m_filtRes[m_osc] = m_mappedKnobValue[m_str][m_pIndex];
        AssignOsc(m_osc, m_str);
        Serial.println(str[m_str].m_filtRes[m_osc]);
        break;

    default:
        break;
    }
}
