#include "Martone.h"

typedef uint8_t u8;
typedef int8_t s8;

void Martone::ProcessKeyboardData()
{
    if (m_parameterSelect == true)
    {
        m_rawKnobValue = analogRead(A13); // double read?
        m_rawKnobValue = analogRead(A13); // double read?
        m_rawKnobValue = constrain(m_rawKnobValue, 5, 1023);
        m_mappedKnobValue[m_str][m_pIndex] = (map(m_rawKnobValue, 1023, 5, m_low - currentSettingValue, m_high - currentSettingValue)) + currentSettingValue;
        if (m_rawKnobValue < (m_oldKnobValue - 5) || m_rawKnobValue > (m_oldKnobValue + 5))
        {
            m_oldKnobValue = m_rawKnobValue;
            UpdateKeyboardData();
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
            if (m_osc < m_NUM_OSC)
            {
                Serial.print("Oscillator ");
                Serial.print(m_osc + 1);
                Serial.println(" Volume");
            }
            else
                Serial.println("All Oscillator Gain");
            break;
        case '&': //waveform frequency
            m_pIndex = 7;
            m_low = 0;
            m_high = 20000;
            m_parameterSelect = true;
            Serial.println("Oscillator Frequency ");
            break;
        case '*': //Freqency Cutoff
            m_pIndex = 8;
            m_low = 0;
            //m_high = 1;
            m_high = 20000;
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
        case '_': //LFO Mode
            m_pIndex = 11;
            m_low = 0;
            m_high = 10;
            m_parameterSelect = true;
            Serial.println("LFO Mode");
            break;
         case '+': //LFO Speed
            m_pIndex = 12;
            m_low = 50;
            m_high = 20000;
            m_parameterSelect = true;
            Serial.println("LFO Speed");
            break;
        case 'q': //LFO front Slope
            m_pIndex = 13;
            m_low = 0;
            m_high = 10;
            m_parameterSelect = true;
            Serial.println("LFO Front Slope");
            break;
         case 'w': //LFO back Slope
            m_pIndex = 14;
            m_low = 0;
            m_high = 10;
            m_parameterSelect = true;
            Serial.println("LFO Back Slope");
            break;
        case 'a': //TriggerNote               *******
            HandleNoteOn(1, 1, 1);
            Serial.println("Qwerty Note On Trigger");
            break;
        case 's': //TriggerNote             *******
            HandleNoteOff(1, 1, 1);
            Serial.println("Qwerty Note Off Trigger");
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
    //float x = map(m_mappedKnobValue[m_str][m_pIndex], m_low, m_high, 0,3.01); //for n&v function
    float x = map(m_mappedKnobValue[m_str][m_pIndex], m_low, m_high, 0, 1); //for roommate function
    float n = str[m_str].m_filtSlope[m_osc];
    // float xSpeed;
    switch (m_pIndex)
    {
    case 5:                                                 //'%' Set Osc Waveform
        currentSettingValue = strInit[m_str].m_oscW[m_osc]; //initialization setting
        str[m_str].m_oscW[m_osc] = waveforms[(int)m_mappedKnobValue[m_str][m_pIndex]];
        AssignOsc(m_osc, m_str);
        Serial.println(str[m_str].m_oscW[m_osc]);
        break;
    case 6: //'^' Set Osc Volume
        currentSettingValue = strInit[m_str].m_oscV[m_osc];
        str[m_str].m_oscV[m_osc] = m_mappedKnobValue[m_str][m_pIndex];
        AssignOsc(m_osc, m_str);
        Serial.println(str[m_str].m_oscV[m_osc]);
        break;
    case 7: //'&' Set Osc Frequency
        currentSettingValue = strInit[m_str].m_freq[m_osc];
        //str[m_str].m_freq[m_osc] =  (int)m_mappedKnobValue[m_str][m_pIndex];
        str[m_str].m_freq[m_osc] = 10000 * pow(1 - pow(1 - x, (1 / n)), n);
        AssignOsc(m_osc, m_str);
        Serial.println(str[m_str].m_freq[m_osc]);
        break;
    case 8: //'*' Set Filter Frequency Cutoff
        currentSettingValue = strInit[m_str].m_freqCut[m_osc];
        str[m_str].m_freqCut[m_osc] = MathFunctions(1, 10000, 1.55, x);
        //str[m_str].m_freqCut[m_osc] = 10000 * pow(1 - pow(1 - x, (1 / n)), n); //good one
        // str[m_str].m_freqCut[m_osc] = pow(100,x - 1);
        //str[m_str].m_freqCut[m_osc] =  m_mappedKnobValue[m_str][m_pIndex];
        AssignOsc(m_osc, m_str);
        Serial.println(str[m_str].m_freqCut[m_osc]);
        break;
    case 9: //'(' Set Filter Slope
        currentSettingValue = strInit[m_str].m_filtSlope[m_osc];
        str[m_str].m_filtSlope[m_osc] = m_mappedKnobValue[m_str][m_pIndex];
        AssignOsc(m_osc, m_str);
        Serial.println(str[m_str].m_filtSlope[m_osc]);
        break;
    case 10: //')' Set Filter Resonance
        currentSettingValue = strInit[m_str].m_filtRes[m_osc];
        str[m_str].m_filtRes[m_osc] = m_mappedKnobValue[m_str][m_pIndex];
        AssignOsc(m_osc, m_str);
        Serial.println(str[m_str].m_filtRes[m_osc]);
        break;
    case 11: //'_' Set LFO Mode
        currentSettingValue = strInit[m_str].m_lfoMode[m_osc];
        str[m_str].m_lfoMode[m_osc] = m_mappedKnobValue[m_str][m_pIndex];
        AssignOsc(m_osc, m_str);
        Serial.println(str[m_str].m_lfoMode[m_osc]);
        break;
    case 12: //'+' Set LFO Speed
        currentSettingValue = strInit[m_str].m_lfoSpeed[m_osc];
        str[m_str].m_lfoSpeed[m_osc] = m_mappedKnobValue[m_str][m_pIndex];
        AssignOsc(m_osc, m_str);
        Serial.println(str[m_str].m_lfoSpeed[m_osc]);
        break;
    case 13: //'q' Set LFO Front Slope
        currentSettingValue = strInit[m_str].m_lfoFrontSlope[m_osc];
        str[m_str].m_lfoFrontSlope[m_osc] = m_mappedKnobValue[m_str][m_pIndex];
        AssignOsc(m_osc, m_str);
        Serial.println(str[m_str].m_lfoFrontSlope[m_osc]);
        break;
    case 14: //'w' Set LFO Back Slope
        currentSettingValue = strInit[m_str].m_lfoBackSlope[m_osc];
        str[m_str].m_lfoBackSlope[m_osc] = m_mappedKnobValue[m_str][m_pIndex];
        AssignOsc(m_osc, m_str);
        Serial.println(str[m_str].m_lfoBackSlope[m_osc]);
        break;


    default:
        break;
    }
}
//********************************************************************************************
double Martone::MathFunctions(u8 function, float highestValue, float slope, double x)
{
    switch (function)
    {

    case 1: //Exponential rising
        return highestValue * pow(1 - pow(1 - x, (1 / slope)), slope);

    case 2: //Exponential falling
        return highestValue * pow(1 - pow(x, 1 / slope), slope);

    case 3: //Sine    //slope = width = 0-10 /higher is narrower/ 2.5 avg
        if (x < 1)
            return highestValue * (pow(sin(PI * x), slope));
        else
            return -1;
    case 4: //Cosine    //slope = width = 0-10 /higher is narrower
        if (x < 1)
            return highestValue * (1 - pow(sin(PI * x), slope)); //cosine
        else
            return -1;
    default:
        break;
    }
}