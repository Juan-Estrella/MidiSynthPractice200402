#pragma once
#include <Audio.h>

// GUItool: begin automatically generated code
extern AudioSynthNoisePink      osc1n;          //xy=294.99999618530273,171.666672706604
extern AudioSynthWaveformModulated osc1c;          //xy=297.8333549499512,125.00000381469727
extern AudioSynthWaveformModulated osc1b;          //xy=298.83333587646484,83.66666984558105
extern AudioSynthWaveformModulated osc1a;          //xy=299.8333435058594,35.00000286102295
extern AudioSynthNoisePink      osc2n; //xy=299.9999809265137,375.0000171661377
extern AudioSynthWaveformModulated osc2c;          //xy=301.5,329.33335876464844
extern AudioSynthWaveformModulated osc2b;          //xy=302.83333587646484,280.00000381469727
extern AudioSynthWaveformModulated osc2a;          //xy=303.8333396911621,230.66668510437012
extern AudioSynthNoisePink      osc4n; //xy=303.33332443237305,769.9999504089355
extern AudioSynthNoisePink      osc3n; //xy=304.9999694824219,568.3333168029785
extern AudioSynthWaveformModulated osc4c;          //xy=304.4999580383301,720.0000305175781
extern AudioSynthWaveformModulated osc3c;          //xy=306.1666564941406,524.3333358764648
extern AudioSynthWaveformModulated osc4a;          //xy=306.16662979125977,621.0000467300415
extern AudioSynthWaveformModulated osc4b;          //xy=306.4999694824219,670.0000286102295
extern AudioSynthWaveformModulated osc3a;          //xy=307.4999694824219,426.6666660308838
extern AudioSynthWaveformModulated osc3b;          //xy=307.83331298828125,474.00000190734863
extern AudioFilterStateVariable filtosc1b; //xy=424.9999694824219,82.33332824707031
extern AudioFilterStateVariable filtosc1c; //xy=424.9999694824219,130
extern AudioFilterStateVariable filtosc1n; //xy=424.9999694824219,178.3333282470703
extern AudioFilterStateVariable filtosc2b; //xy=424.9999694824219,281.3333148956299
extern AudioFilterStateVariable filtosc2c; //xy=424.9999694824219,328.99998664855957
extern AudioFilterStateVariable filtosc2n; //xy=424.9999694824219,377.3333148956299
extern AudioFilterStateVariable filtosc1a; //xy=426.6666564941406,33.33333206176758
extern AudioFilterStateVariable filtosc2a; //xy=426.6666564941406,232.33331871032715
extern AudioFilterStateVariable filtosc3b; //xy=426.6666259765625,477.333309173584
extern AudioFilterStateVariable filtosc3c; //xy=426.6666259765625,524.9999809265137
extern AudioFilterStateVariable filtosc3n; //xy=426.6666259765625,573.333309173584
extern AudioFilterStateVariable filtosc4b; //xy=426.6666259765625,673.9999961853027
extern AudioFilterStateVariable filtosc4c; //xy=426.6666259765625,721.6666679382324
extern AudioFilterStateVariable filtosc4n; //xy=426.6666259765625,769.9999961853027
extern AudioFilterStateVariable filtosc3a; //xy=428.33331298828125,428.33331298828125
extern AudioFilterStateVariable filtosc4a; //xy=428.33331298828125,625
extern AudioEffectEnvelope      ADSRosc1a; //xy=564.3333549499512,32.666669845581055
extern AudioEffectEnvelope      ADSRosc2a; //xy=564.3333549499512,231.66665649414062
extern AudioEffectEnvelope      ADSRosc3a; //xy=566.0000114440918,427.6666507720947
extern AudioEffectEnvelope      ADSRosc1b; //xy=567.6666870117188,78.33333206176758
extern AudioEffectEnvelope      ADSRosc1c; //xy=567.6666870117188,126.00000381469727
extern AudioEffectEnvelope      ADSRosc1n; //xy=567.6666870117188,174.33333206176758
extern AudioEffectEnvelope      ADSRosc4a; //xy=566.0000114440918,624.3333377838135
extern AudioEffectEnvelope      ADSRosc2b; //xy=567.6666870117188,277.33331871032715
extern AudioEffectEnvelope      ADSRosc2c; //xy=567.6666870117188,324.99999046325684
extern AudioEffectEnvelope      ADSRosc2n; //xy=567.6666870117188,373.33331871032715
extern AudioEffectEnvelope      ADSRosc3b; //xy=569.3333435058594,473.33331298828125
extern AudioEffectEnvelope      ADSRosc3c; //xy=569.3333435058594,520.9999847412109
extern AudioEffectEnvelope      ADSRosc3n; //xy=569.3333435058594,569.3333129882812
extern AudioEffectEnvelope      ADSRosc4b; //xy=569.3333435058594,670
extern AudioEffectEnvelope      ADSRosc4c; //xy=569.3333435058594,717.6666717529297
extern AudioEffectEnvelope      ADSRosc4n;  //xy=569.3333435058594,766
extern AudioMixer4              voice2mix;      //xy=719.4999313354492,297.33333587646484
extern AudioMixer4              voice4mix;      //xy=720.8332633972168,682.6666717529297
extern AudioMixer4              voice3mix;      //xy=722.8333053588867,495.3333320617676
extern AudioMixer4              voice1mix;      //xy=734.8333206176758,100.66665649414062
extern AudioFilterStateVariable filter2;        //xy=845.4999618530273,297.6666488647461
extern AudioFilterStateVariable filter4;        //xy=847.833251953125,681.3333587646484
extern AudioFilterStateVariable filter3;        //xy=850.1665840148926,496.9999885559082
extern AudioFilterStateVariable filter1;        //xy=867.1666221618652,102.99998474121094
extern AudioEffectEnvelope      ADSR2;          //xy=967.8333206176758,296.99999237060547
extern AudioEffectEnvelope      ADSR3;          //xy=967.8332176208496,497.9999780654907
extern AudioEffectEnvelope      ADSR4;          //xy=967.4998626708984,680.3333787918091
extern AudioEffectEnvelope      ADSR1;          //xy=994.8332939147949,107.33331871032715
extern AudioMixer4              first4premix;   //xy=1174.833309173584,412.9999752044678
extern AudioMixer4              mainOutMixer;   //xy=1335.1666107177734,414.3332977294922
extern AudioOutputI2S           i2s1;           //xy=1484.833309173584,411.6666793823242
extern AudioConnection          patchCord1;
extern AudioConnection          patchCord2;
extern AudioConnection          patchCord3;
extern AudioConnection          patchCord4;
extern AudioConnection          patchCord5;
extern AudioConnection          patchCord6;
extern AudioConnection          patchCord7;
extern AudioConnection          patchCord8;
extern AudioConnection          patchCord9;
extern AudioConnection          patchCord10;
extern AudioConnection          patchCord11;
extern AudioConnection          patchCord12;
extern AudioConnection          patchCord13;
extern AudioConnection          patchCord14;
extern AudioConnection          patchCord15;
extern AudioConnection          patchCord16;
extern AudioConnection          patchCord17;
extern AudioConnection          patchCord18;
extern AudioConnection          patchCord19;
extern AudioConnection          patchCord20;
extern AudioConnection          patchCord21;
extern AudioConnection          patchCord22;
extern AudioConnection          patchCord23;
extern AudioConnection          patchCord24;
extern AudioConnection          patchCord25;
extern AudioConnection          patchCord26;
extern AudioConnection          patchCord27;
extern AudioConnection          patchCord28;
extern AudioConnection          patchCord29;
extern AudioConnection          patchCord30;
extern AudioConnection          patchCord31;
extern AudioConnection          patchCord32;
extern AudioConnection          patchCord33;
extern AudioConnection          patchCord34;
extern AudioConnection          patchCord35;
extern AudioConnection          patchCord36;
extern AudioConnection          patchCord37;
extern AudioConnection          patchCord38;
extern AudioConnection          patchCord39;
extern AudioConnection          patchCord40;
extern AudioConnection          patchCord41;
extern AudioConnection          patchCord42;
extern AudioConnection          patchCord43;
extern AudioConnection          patchCord44;
extern AudioConnection          patchCord45;
extern AudioConnection          patchCord46;
extern AudioConnection          patchCord47;
extern AudioConnection          patchCord48;
extern AudioConnection          patchCord49;
extern AudioConnection          patchCord50;
extern AudioConnection          patchCord51;
extern AudioConnection          patchCord52;
extern AudioConnection          patchCord53;
extern AudioConnection          patchCord54;
extern AudioConnection          patchCord55;
extern AudioConnection          patchCord56;
extern AudioConnection          patchCord57;
extern AudioConnection          patchCord58;
extern AudioConnection          patchCord59;
extern AudioConnection          patchCord60;
extern AudioConnection          patchCord61;
extern AudioConnection          patchCord62;
extern AudioConnection          patchCord63;
extern AudioControlSGTL5000     sgtl5000_1;     //xy=1482.1667175292969,351.00000381469727
// GUItool: end automatically generated code
