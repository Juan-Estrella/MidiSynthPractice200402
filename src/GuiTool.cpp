#include "GuiTool.h"

// GUItool: begin automatically generated code
AudioSynthNoisePink      osc1n;          //xy=294.99999618530273,171.666672706604
AudioSynthWaveformModulated osc1c;          //xy=297.8333549499512,125.00000381469727
AudioSynthWaveformModulated osc1b;          //xy=298.83333587646484,83.66666984558105
AudioSynthWaveformModulated osc1a;          //xy=299.8333435058594,35.00000286102295
AudioSynthNoisePink      osc2n; //xy=299.9999809265137,375.0000171661377
AudioSynthWaveformModulated osc2c;          //xy=301.5,329.33335876464844
AudioSynthWaveformModulated osc2b;          //xy=302.83333587646484,280.00000381469727
AudioSynthWaveformModulated osc2a;          //xy=303.8333396911621,230.66668510437012
AudioSynthNoisePink      osc4n; //xy=303.33332443237305,769.9999504089355
AudioSynthNoisePink      osc3n; //xy=304.9999694824219,568.3333168029785
AudioSynthWaveformModulated osc4c;          //xy=304.4999580383301,720.0000305175781
AudioSynthWaveformModulated osc3c;          //xy=306.1666564941406,524.3333358764648
AudioSynthWaveformModulated osc4a;          //xy=306.16662979125977,621.0000467300415
AudioSynthWaveformModulated osc4b;          //xy=306.4999694824219,670.0000286102295
AudioSynthWaveformModulated osc3a;          //xy=307.4999694824219,426.6666660308838
AudioSynthWaveformModulated osc3b;          //xy=307.83331298828125,474.00000190734863
AudioFilterStateVariable filtosc1b; //xy=424.9999694824219,82.33332824707031
AudioFilterStateVariable filtosc1c; //xy=424.9999694824219,130
AudioFilterStateVariable filtosc1n; //xy=424.9999694824219,178.3333282470703
AudioFilterStateVariable filtosc2b; //xy=424.9999694824219,281.3333148956299
AudioFilterStateVariable filtosc2c; //xy=424.9999694824219,328.99998664855957
AudioFilterStateVariable filtosc2n; //xy=424.9999694824219,377.3333148956299
AudioFilterStateVariable filtosc1a; //xy=426.6666564941406,33.33333206176758
AudioFilterStateVariable filtosc2a; //xy=426.6666564941406,232.33331871032715
AudioFilterStateVariable filtosc3b; //xy=426.6666259765625,477.333309173584
AudioFilterStateVariable filtosc3c; //xy=426.6666259765625,524.9999809265137
AudioFilterStateVariable filtosc3n; //xy=426.6666259765625,573.333309173584
AudioFilterStateVariable filtosc4b; //xy=426.6666259765625,673.9999961853027
AudioFilterStateVariable filtosc4c; //xy=426.6666259765625,721.6666679382324
AudioFilterStateVariable filtosc4n; //xy=426.6666259765625,769.9999961853027
AudioFilterStateVariable filtosc3a; //xy=428.33331298828125,428.33331298828125
AudioFilterStateVariable filtosc4a; //xy=428.33331298828125,625
AudioEffectEnvelope      ADSRosc1a; //xy=564.3333549499512,32.666669845581055
AudioEffectEnvelope      ADSRosc2a; //xy=564.3333549499512,231.66665649414062
AudioEffectEnvelope      ADSRosc3a; //xy=566.0000114440918,427.6666507720947
AudioEffectEnvelope      ADSRosc1b; //xy=567.6666870117188,78.33333206176758
AudioEffectEnvelope      ADSRosc1c; //xy=567.6666870117188,126.00000381469727
AudioEffectEnvelope      ADSRosc1n; //xy=567.6666870117188,174.33333206176758
AudioEffectEnvelope      ADSRosc4a; //xy=566.0000114440918,624.3333377838135
AudioEffectEnvelope      ADSRosc2b; //xy=567.6666870117188,277.33331871032715
AudioEffectEnvelope      ADSRosc2c; //xy=567.6666870117188,324.99999046325684
AudioEffectEnvelope      ADSRosc2n; //xy=567.6666870117188,373.33331871032715
AudioEffectEnvelope      ADSRosc3b; //xy=569.3333435058594,473.33331298828125
AudioEffectEnvelope      ADSRosc3c; //xy=569.3333435058594,520.9999847412109
AudioEffectEnvelope      ADSRosc3n; //xy=569.3333435058594,569.3333129882812
AudioEffectEnvelope      ADSRosc4b; //xy=569.3333435058594,670
AudioEffectEnvelope      ADSRosc4c; //xy=569.3333435058594,717.6666717529297
AudioEffectEnvelope      ADSRosc4n;  //xy=569.3333435058594,766
AudioMixer4              voice2mix;      //xy=719.4999313354492,297.33333587646484
AudioMixer4              voice4mix;      //xy=720.8332633972168,682.6666717529297
AudioMixer4              voice3mix;      //xy=722.8333053588867,495.3333320617676
AudioMixer4              voice1mix;      //xy=734.8333206176758,100.66665649414062
AudioFilterStateVariable filter2;        //xy=845.4999618530273,297.6666488647461
AudioFilterStateVariable filter4;        //xy=847.833251953125,681.3333587646484
AudioFilterStateVariable filter3;        //xy=850.1665840148926,496.9999885559082
AudioFilterStateVariable filter1;        //xy=867.1666221618652,102.99998474121094
AudioEffectEnvelope      ADSR2;          //xy=967.8333206176758,296.99999237060547
AudioEffectEnvelope      ADSR3;          //xy=967.8332176208496,497.9999780654907
AudioEffectEnvelope      ADSR4;          //xy=967.4998626708984,680.3333787918091
AudioEffectEnvelope      ADSR1;          //xy=994.8332939147949,107.33331871032715
AudioMixer4              first4premix;   //xy=1174.833309173584,412.9999752044678
AudioMixer4              mainOutMixer;   //xy=1335.1666107177734,414.3332977294922
AudioOutputI2S           i2s1;           //xy=1484.833309173584,411.6666793823242
AudioConnection          patchCord1(osc1n, 0, filtosc1n, 0);
AudioConnection          patchCord2(osc1c, 0, filtosc1c, 0);
AudioConnection          patchCord3(osc1b, 0, filtosc1b, 0);
AudioConnection          patchCord4(osc1a, 0, filtosc1a, 0);
AudioConnection          patchCord5(osc2n, 0, filtosc2n, 0);
AudioConnection          patchCord6(osc2c, 0, filtosc2c, 0);
AudioConnection          patchCord7(osc2b, 0, filtosc2b, 0);
AudioConnection          patchCord8(osc2a, 0, filtosc2a, 0);
AudioConnection          patchCord9(osc4n, 0, filtosc4n, 0);
AudioConnection          patchCord10(osc3n, 0, filtosc3n, 0);
AudioConnection          patchCord11(osc4c, 0, filtosc4c, 0);
AudioConnection          patchCord12(osc3c, 0, filtosc3c, 0);
AudioConnection          patchCord13(osc4a, 0, filtosc4a, 0);
AudioConnection          patchCord14(osc4b, 0, filtosc4b, 0);
AudioConnection          patchCord15(osc3a, 0, filtosc3a, 0);
AudioConnection          patchCord16(osc3b, 0, filtosc3b, 0);
AudioConnection          patchCord17(filtosc1b, 0, ADSRosc1b, 0);
AudioConnection          patchCord18(filtosc1c, 0, ADSRosc1c, 0);
AudioConnection          patchCord19(filtosc1n, 0, ADSRosc1n, 0);
AudioConnection          patchCord20(filtosc2b, 0, ADSRosc2b, 0);
AudioConnection          patchCord21(filtosc2c, 0, ADSRosc2c, 0);
AudioConnection          patchCord22(filtosc2n, 0, ADSRosc2n, 0);
AudioConnection          patchCord23(filtosc1a, 0, ADSRosc1a, 0);
AudioConnection          patchCord24(filtosc2a, 0, ADSRosc2a, 0);
AudioConnection          patchCord25(filtosc3b, 0, ADSRosc3b, 0);
AudioConnection          patchCord26(filtosc3c, 0, ADSRosc3c, 0);
AudioConnection          patchCord27(filtosc3n, 0, ADSRosc3n, 0);
AudioConnection          patchCord28(filtosc4b, 0, ADSRosc4b, 0);
AudioConnection          patchCord29(filtosc4c, 0, ADSRosc4c, 0);
AudioConnection          patchCord30(filtosc4n, 0, ADSRosc4n, 0);
AudioConnection          patchCord31(filtosc3a, 0, ADSRosc3a, 0);
AudioConnection          patchCord32(filtosc4a, 0, ADSRosc4a, 0);
AudioConnection          patchCord33(ADSRosc1a, 0, voice1mix, 0);
AudioConnection          patchCord34(ADSRosc2a, 0, voice2mix, 0);
AudioConnection          patchCord35(ADSRosc3a, 0, voice3mix, 0);
AudioConnection          patchCord36(ADSRosc1b, 0, voice1mix, 1);
AudioConnection          patchCord37(ADSRosc1c, 0, voice1mix, 2);
AudioConnection          patchCord38(ADSRosc1n, 0, voice1mix, 3);
AudioConnection          patchCord39(ADSRosc4a, 0, voice4mix, 0);
AudioConnection          patchCord40(ADSRosc2b, 0, voice2mix, 1);
AudioConnection          patchCord41(ADSRosc2c, 0, voice2mix, 2);
AudioConnection          patchCord42(ADSRosc2n, 0, voice2mix, 3);
AudioConnection          patchCord43(ADSRosc3b, 0, voice3mix, 1);
AudioConnection          patchCord44(ADSRosc3c, 0, voice3mix, 2);
AudioConnection          patchCord45(ADSRosc3n, 0, voice3mix, 3);
AudioConnection          patchCord46(ADSRosc4b, 0, voice4mix, 1);
AudioConnection          patchCord47(ADSRosc4c, 0, voice4mix, 2);
AudioConnection          patchCord48(ADSRosc4n, 0, voice4mix, 3);
AudioConnection          patchCord49(voice2mix, 0, filter2, 0);
AudioConnection          patchCord50(voice4mix, 0, filter4, 0);
AudioConnection          patchCord51(voice3mix, 0, filter3, 0);
AudioConnection          patchCord52(voice1mix, 0, filter1, 0);
AudioConnection          patchCord53(filter2, 0, ADSR2, 0);
AudioConnection          patchCord54(filter4, 0, ADSR4, 0);
AudioConnection          patchCord55(filter3, 0, ADSR3, 0);
AudioConnection          patchCord56(filter1, 0, ADSR1, 0);
AudioConnection          patchCord57(ADSR2, 0, first4premix, 1);
AudioConnection          patchCord58(ADSR3, 0, first4premix, 2);
AudioConnection          patchCord59(ADSR4, 0, first4premix, 3);
AudioConnection          patchCord60(ADSR1, 0, first4premix, 0);
AudioConnection          patchCord61(first4premix, 0, mainOutMixer, 0);
AudioConnection          patchCord62(mainOutMixer, 0, i2s1, 0);
AudioConnection          patchCord63(mainOutMixer, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1482.1667175292969,351.00000381469727
// GUItool: end automatically generated code