#include "Prodyssey.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"


/*void IControl::OnMidi(const IMidiMsg &msg) {
  SetValueFromDelegate(msg.mData2);
}*/

Prodyssey::Prodyssey(IPlugInstanceInfo instanceInfo)
: IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo)
{

  mCurrentPresetPath.Set("Default");

 

  GetParam(kParamKeyboardOctave)->InitEnum("Keyb Oct", 3, 7, "", 0, "", "-3","-2","-1","0","+1","+2","+3");
  GetParam(kParamProgram)->InitInt("Program", 0, 0, 99, "", 0, "");
  GetParam(kParamMidiActive)->InitBool("MIDI Active", true, "");

  /* SCHALTER */
  GetParam(kParamVco1FmModSource1)->InitEnum("",0,2);
  GetParam(kParamVco1FmModSource2)->InitEnum("",0,2);
  GetParam(kParamVco1PwModSource)->InitEnum("",0,2);
  GetParam(kParamVco2FmModSource1)->InitEnum("",0,2);
  GetParam(kParamVco2FmModSource2)->InitEnum("",0,2);
  GetParam(kParamVco2PwModSource)->InitEnum("",0,2);
  GetParam(kParamShMixerSource1)->InitEnum("",0,2);
  GetParam(kParamShMixerSource2)->InitEnum("",0,2);
  GetParam(kParamShTrigSource)->InitEnum("",0,2);
  GetParam(kParamMixerSource1)->InitEnum("",0,2);
  GetParam(kParamMixerSource2)->InitEnum("",0,2);
  GetParam(kParamMixerSource3)->InitEnum("",0,2);
  GetParam(kParamVcfModSource1)->InitEnum("",0,2);
  GetParam(kParamVcfModSource2)->InitEnum("",0,2);
  GetParam(kParamVcfModSource3)->InitEnum("",0,2);
  GetParam(kParamVcaModSource)->InitEnum("",0,2);
  GetParam(kParamAdsrMode)->InitEnum("",0,2);
  GetParam(kParamAdsrRepeat)->InitEnum("",0,2);
  GetParam(kParamArMode)->InitEnum("",0,2);

  GetParam(kParamNoiseType)->InitEnum("", 0, 2);
  GetParam(kParamKeybOnOff)->InitEnum("", 0, 2);
  GetParam(kParamVco2Sync)->InitEnum("", 0, 2);
  GetParam(kParamLfoBpmHertz)->InitEnum("", 0, 2);
  GetParam(kParamVcfModel)->InitEnum("", 0, 2);
  GetParam(kParamBoost)->InitEnum("", 0, 2);

  GetParam(kParamMasterOctave)->InitEnum("Octave", 1, 3);
  GetParam(kParamVco1Octave)->InitEnum("Octave VCO 1", 1, 3);
  GetParam(kParamVco2Octave)->InitEnum("Octave VCO 2", 1, 3);
  GetParam(kParamAftertouchVco)->InitEnum("Aftertouch VCO", 1, 3);

  GetParam(kParamBendRange)->InitInt("Bend Range", 0, 0, 24);
  GetParam(kParamChorusPhase)->InitInt("Chorus Phase", 0, 0, 180);
  GetParam(kParamChorusRate)->InitDouble("Chorus Rate", 0, 0.01, 20, 0.01, "", 0, "", IParam::ShapePowCurve(6));

  GetParam(kParamMidiClockBpm)->InitInt("MIDI CLK BPM", 72, 72, 199);


  GetParam(kParamDelayTimeLMS)->InitDouble("Delaytime L MS", 1.01, 1.01, 1365.33, 0.01);
  GetParam(kParamDelayTimeRMS)->InitDouble("Delaytime R MS", 1.01, 1.01, 1365.33, 0.01);
  GetParam(kParamDelayTimeLBPM)->InitEnum("Delaytime L BPM", 0, 19, "", 0, "", "1/1", "1/2P","1/2","1/2T","1/4P","1/4","1/4T", "1/8P", "1/8", "1/8T", "1/16P", "1/16", "1/16T", "1/32P", "1/32", "1/32T", "1/64P", "1/64", "1/64T");
  GetParam(kParamDelayTimeRBPM)->InitEnum("Delaytime R BPM", 0, 19, "", 0, "", "1/1", "1/2P", "1/2", "1/2T", "1/4P", "1/4", "1/4T", "1/8P", "1/8", "1/8T", "1/16P", "1/16", "1/16T", "1/32P", "1/32", "1/32T", "1/64P", "1/64", "1/64T");

  GetParam(kParamLfoNote)->InitEnum("LFO Note", 0, 19, "", 0, "", "1/1", "1/2P", "1/2", "1/2T", "1/4P", "1/4", "1/4T", "1/8P", "1/8", "1/8T", "1/16P", "1/16", "1/16T", "1/32P", "1/32", "1/32T", "1/64P", "1/64", "1/64T");


  GetParam(kParamDelayUnitLeft)->InitEnum("Delay Unit L", 0, 2, "", 0, "", "ms", "Beats");
  GetParam(kParamDelayUnitRight)->InitEnum("Delay Unit R", 0, 2, "", 0, "", "ms", "Beats");
    
    // Black Slider
    GetParam(kParamPortamento)->InitDouble("Portamento",0,0,1,0.001);
    GetParam(kParamMixerNoiseLevel)->InitDouble("Noise Level",0,0,1,0.001);
    GetParam(kParamVcfFreq)->InitDouble("VCF Freq",0,0,1,0.001);
    GetParam(kParamVcfRes)->InitDouble("VCF Res",0,0,1,0.001);
    GetParam(kParamHpfFreq)->InitDouble("HPF Freq",0,0,1,0.001);
    GetParam(kParamVcaGain)->InitDouble("VCA Gain",0,0,1,0.001);
    // Red Slider
    GetParam(kParamVcfKeyb)->InitDouble("VCF KYB",0,0,1,0.001);
    GetParam(kParamVcfAdsr)->InitDouble("VCF ADSR",0,0,1,0.001);
    GetParam(kParamVcaAdsr)->InitDouble("VCA ADSR",0,0,1,0.001);
    GetParam(kParamArAttack)->InitDouble("AR Attack",0,0,1,0.001);
    GetParam(kParamArRelease)->InitDouble("AR Release",0,0,1,0.001);
    GetParam(kParamAdsrAttack)->InitDouble("ADSR Attack",0,0,1,0.001);
    GetParam(kParamAdsrDecay)->InitDouble("ADSR Decay",0,0,1,0.001);
    // Yellow Slider
    GetParam(kParamVco1ShLevel)->InitDouble("VCO1 SH Lev",0,0,1,0.001);
    GetParam(kParamVco2ShLevel)->InitDouble("VCO2 SH Lev",0,0,1,0.001);
    GetParam(kParamShLag)->InitDouble("SH Lag" ,0,0,1,0.001);
    GetParam(kParamVcfShLevel)->InitDouble("VCF SH Lev",0,0,1,0.001);
    GetParam(kParamAdsrSustain)->InitDouble("ADSR Sustain",0,0,1,0.001);
    GetParam(kParamAdsrRelease)->InitDouble("ADSR Release",0,0,1,0.001);
    // Pink Slider
    GetParam(kParamVco1FmModLfoLevel)->InitDouble("VCO1 FM LFO Lev",0,0,1,0.001);
    GetParam(kParamVco1PwModLfoLevel)->InitDouble("VCO1 PW LFO Lev",0,0,1,0.001);
    GetParam(kParamVco2FmModLfoLevel)->InitDouble("VCO2 PW LFO Lev",0,0,1,0.001);
    GetParam(kParamVco2PwModLfoLevel)->InitDouble("VCO2 FM LFO Lev",0,0,1,0.001);
    GetParam(kParamLfoFreq)->InitDouble("LFO Freq",0,0,1,0.001);
    GetParam(kParamArVel)->InitDouble("AR Vel",0,0,1,0.001);
    GetParam(kParamArKeyb)->InitDouble("AR KYB",0,0,1,0.001);
    // Cyan Slider
    GetParam(kParamVco1Coarse)->InitDouble("VCO1 Coarse",0,0,1,0.001);
    GetParam(kParamVco1Fine)->InitDouble("VCO1 Fine",0,0,1,0.001);
    GetParam(kParamVco1PwWidth)->InitDouble("VCO1 PW",0,0,1,0.001);
    GetParam(kParamShMixerMod1Level)->InitDouble("SH Mod1 Lev",0,0,1,0.001);
    GetParam(kParamShMixerMod2Level)->InitDouble("SH Mod2 Lev",0,0,1,0.001);
    GetParam(kParamAudioMixerIn2level)->InitDouble("Mixer In1 Lev",0,0,1,0.001);
    // Green Slider
    GetParam(kParamVco2Coarse)->InitDouble("VCO2 Coarse",0,0,1,0.001);
    GetParam(kParamVco2Fine)->InitDouble("VCO2 Fine",0,0,1,0.001);
    GetParam(kParamVco2PwWidth)->InitDouble("VCO2 PW",0,0,1,0.001);
    GetParam(kParamAudioMixerIn3level)->InitDouble("Mixer In2 Lev",0,0,1,0.001);
    /* ADD  Slider */
    GetParam(kParamModWheelIntensity)->InitDouble("Mod Wheel Int",0,0,1,0.001);
    GetParam(kParamChorusDepth)->InitDouble("Chorus Depth",0,0,1,0.001);
    GetParam(kParamChorusFeedback)->InitDouble("Chorus FB",0,0,1,0.001);
    GetParam(kParamChorusWet)->InitDouble("Chorus Mix",0,0,1,0.001);
    GetParam(kParamAftertouchPitch)->InitDouble("Aftertouch Pitch",0,0,1,0.001);
    GetParam(kParamAftertouchFilter)->InitDouble("Aftertouch Filter",0,0,1,0.001);
    GetParam(kParamDelayFeedbackLeft)->InitDouble("Delay FB L",0,0,1,0.001);
    GetParam(kParamDelayHidampLeft)->InitDouble("Delay Hidamp L",0,0,1,0.001);
    GetParam(kParamDelayLevelLeft)->InitDouble("Delay Lev L",0,0,1,0.001);
    GetParam(kParamDelayFeedbackRight)->InitDouble("Delay FB R",0,0,1,0.001);
    GetParam(kParamDelayHidampRight)->InitDouble("Delay Hidamp R",0,0,1,0.001);
    GetParam(kParamDelayLevelRight)->InitDouble("Delay Lev R",0,0,1,0.001);
    GetParam(kParamDelayWet)->InitDouble("Delay Mix",0,0,1,0.001);
    GetParam(kParamFlangerChorus)->InitEnum("Flanger/Chorus",0,2);
    GetParam(kParamEffectBypass)->InitEnum("Effect Bypass",0,2);
    GetParam(kParamDelayCrossDual)->InitEnum("Delay Cross/Dual",0,2);
    GetParam(kParamKeybModeRetrig)->InitEnum("KYB Trig Mode",0,2);
    GetParam(kParamKeybModeLowNote)->InitEnum("KYB Note Mode",0,2);
    GetParam(kParamKeybModeSingle)->InitEnum("KYB Poly Mode",0,2);
    GetParam(kParamLfoSettBpm)->InitDouble("LFO",0,0,1,0.001);
    GetParam(kParamPitchWheel)->InitDouble("Pitch Wheel",0,0,1,0.001);

    GetParam(kParamVco1FmModSource1)->InitInt("VCO1 FM Mod Src 1", 0, 0, 1);
    GetParam(kParamVco1FmModSource2)->InitInt("VCO1 FM Mod Src 2", 0, 0, 1);
    GetParam(kParamVco1PwModSource)->InitInt("VCO1 PW Mod Src", 0, 0, 1);
    GetParam(kParamVco2FmModSource1)->InitInt("VCO2 FM Mod Src 1", 0, 0, 1);
    GetParam(kParamVco2FmModSource2)->InitInt("VCO2 FM Mod Src 2", 0, 0, 1);
    GetParam(kParamVco2PwModSource)->InitInt("VCO2 PW Mod Src", 0, 0, 1);
    GetParam(kParamShMixerSource1)->InitInt("SH Mixer Src 1", 0, 0, 1);
    GetParam(kParamShMixerSource2)->InitInt("SH Mixer Src 2", 0, 0, 1);
    GetParam(kParamShTrigSource)->InitInt("SH Trig Src", 0, 0, 1);
    GetParam(kParamMixerSource1)->InitInt("Mixer Src 1", 0, 0, 1);
    GetParam(kParamMixerSource2)->InitInt("Mixer Src 2", 0, 0, 1);
    GetParam(kParamMixerSource3)->InitInt("Mixer Src 3", 0, 0, 1);
    GetParam(kParamVcfModSource1)->InitInt("VCF Mod Src 1", 0, 0, 1);
    GetParam(kParamVcfModSource2)->InitInt("VCF Mod Src 2", 0, 0, 1);
    GetParam(kParamVcfModSource3)->InitInt("VCF Mod Src 3", 0, 0, 1);
    GetParam(kParamVcaModSource)->InitInt("VCA Mod Src", 0, 0, 1);
    GetParam(kParamAdsrMode)->InitInt("ADSR Mode", 0, 0, 1);
    GetParam(kParamAdsrRepeat)->InitInt("ADSR Repeat", 0, 0, 1);
    GetParam(kParamArMode)->InitInt("AR Mode", 0, 0, 1);


      GetParam(kParamNoiseType)->InitInt("Noise Type", 0, 0, 1);
      GetParam(kParamKeybOnOff)->InitInt("KYB On/Off", 0, 0, 1);
      GetParam(kParamVco2Sync)->InitInt("VCO2 Sync", 0, 0, 1);
      GetParam(kParamLfoBpmHertz)->InitInt("LFO BPM/Hz", 0, 0, 1);
      GetParam(kParamVcfModel)->InitInt("VCF Model", 0, 0, 1);
      GetParam(kParamBoost)->InitInt("Boost", 0, 0, 1);

      GetParam(kParamMasterVolume)->InitDouble("Volume", 0, 0, 1, 0.001);
      GetParam(kParamSynthMic)->InitDouble("Synth Mic", 0, 0, 1, 0.001);

    paramToCC.fill(-1);

    paramToCC[kParamMasterVolume] = 7;
    paramToCC[kParamSynthMic] = 93;
    paramToCC[kParamVco1FmModSource1          ]=85;
    paramToCC[kParamVco1FmModSource2          ]=87;
    paramToCC[kParamVco1PwModSource           ]=22;
    paramToCC[kParamVco2FmModSource1          ]=27;
    paramToCC[kParamVco2FmModSource2          ]=29;
    paramToCC[kParamVco2PwModSource           ]=33;
    paramToCC[kParamShMixerSource1            ]=76;
    paramToCC[kParamShMixerSource2            ]=78;
    paramToCC[kParamShTrigSource              ]=102;
    paramToCC[kParamMixerSource1              ]=39;
    paramToCC[kParamMixerSource2              ]=35;
    paramToCC[kParamMixerSource3              ]=37;
    paramToCC[kParamVcfModSource1             ]=46;
    paramToCC[kParamVcfModSource2             ]=48;
    paramToCC[kParamVcfModSource3             ]=50;
    paramToCC[kParamVcaModSource              ]=52;
    paramToCC[kParamAdsrMode                  ]=61;
    paramToCC[kParamAdsrRepeat                ]=62;
    paramToCC[kParamArMode                    ]=63;
    paramToCC[kParamNoiseType                 ]=80;
    paramToCC[kParamKeybOnOff                 ]=83;
    paramToCC[kParamVco2Sync                  ]=25;
    paramToCC[kParamLfoBpmHertz               ]=94;
    paramToCC[kParamVcfModel                  ]=41;
    paramToCC[kParamBoost                     ]=105;
    paramToCC[kParamPortamento                ]=5;
    paramToCC[kParamMixerNoiseLevel           ]=38;
    paramToCC[kParamVcfFreq                   ]=74;
    paramToCC[kParamVcfRes                    ]=71;
    paramToCC[kParamHpfFreq                   ]=19;
    paramToCC[kParamVcaGain                   ]=11;
    paramToCC[kParamVcfKeyb                   ]=45;
    paramToCC[kParamVcfAdsr                   ]=49;
    paramToCC[kParamVcaAdsr                   ]=51;
    paramToCC[kParamArAttack                  ]=17;
    paramToCC[kParamArRelease                 ]=20;
    paramToCC[kParamAdsrAttack                ]=13;
    paramToCC[kParamAdsrDecay                 ]=82;
    paramToCC[kParamVco1ShLevel               ]=86;
    paramToCC[kParamVco2ShLevel               ]=28;
    paramToCC[kParamShLag                     ]=103;
    paramToCC[kParamVcfShLevel                ]=47;
    paramToCC[kParamAdsrSustain               ]=15;
    paramToCC[kParamAdsrRelease               ]=16;
    paramToCC[kParamVco1FmModLfoLevel         ]=84;
    paramToCC[kParamVco1PwModLfoLevel         ]=21;
    paramToCC[kParamVco2FmModLfoLevel         ]=26;
    paramToCC[kParamVco2PwModLfoLevel         ]=31;
    paramToCC[kParamLfoFreq                   ]=72;
    paramToCC[kParamArVel                     ]=73;
    paramToCC[kParamArKeyb                    ]=12;
    paramToCC[kParamVco1Coarse                ]=81;
    paramToCC[kParamVco1Fine                  ]=14;
    paramToCC[kParamVco1PwWidth               ]=88;
    paramToCC[kParamShMixerMod1Level          ]=75;
    paramToCC[kParamShMixerMod2Level          ]=77;
    paramToCC[kParamAudioMixerIn2level        ]=34;
    paramToCC[kParamVco2Coarse                ]=23;
    paramToCC[kParamVco2Fine                  ]=24;
    paramToCC[kParamVco2PwWidth               ]=30;
    paramToCC[kParamAudioMixerIn3level        ]=36;
    paramToCC[kParamBendRange                 ]=97;
    paramToCC[kParamModWheelIntensity         ]=104;
    paramToCC[kParamChorusPhase               ]=72;
    paramToCC[kParamChorusRate                ]=71;
    paramToCC[kParamChorusDepth               ]=73;
    paramToCC[kParamChorusFeedback            ]=74;
    paramToCC[kParamChorusWet                 ]=91;
    paramToCC[kParamAftertouchPitch           ]=105;
    paramToCC[kParamAftertouchFilter          ]=108;
    paramToCC[kParamDelayTimeLMS              ]=81;
    paramToCC[kParamDelayTimeRMS              ]=91;
    paramToCC[kParamDelayTimeLBPM             ]=82;
    paramToCC[kParamDelayTimeRBPM             ]=92;
    paramToCC[kParamDelayFeedbackLeft         ]=119;
    paramToCC[kParamDelayHidampLeft           ]=84;
    paramToCC[kParamDelayLevelLeft            ]=85;
    paramToCC[kParamDelayFeedbackRight        ]=-1;
    paramToCC[kParamDelayHidampRight          ]=94;
    paramToCC[kParamDelayLevelRight           ]=95;
    paramToCC[kParamDelayWet                  ]=10;
    paramToCC[kParamFlangerChorus             ]=75;
    paramToCC[kParamEffectBypass              ]=98;
    paramToCC[kParamDelayUnitLeft             ]=86;
    paramToCC[kParamDelayUnitRight            ]=96;
    paramToCC[kParamDelayCrossDual            ]=90;
    paramToCC[kParamKeybModeRetrig            ]=69;
    paramToCC[kParamKeybModeLowNote           ]=101;
    paramToCC[kParamKeybModeSingle            ]=68;
    paramToCC[kParamLfoSettBpm                ]=-1;
    paramToCC[kParamAftertouchVco             ]=106;
    paramToCC[kParamMidiClockBpm              ]=97;
    paramToCC[kParamPitchWheel                ]=1;
    paramToCC[kParamMasterOctave              ]=109;
    paramToCC[kParamVco1Octave                ]=113;
    paramToCC[kParamVco2Octave                ]=114;
    paramToCC[kParamLfoNote                   ]=96;

    paramToMsgType.fill(-1);

    paramToMsgType[kParamMasterVolume] = 0;
    paramToMsgType[kParamSynthMic] = 0;
    paramToMsgType[kParamVco1FmModSource1          ]=0;
    paramToMsgType[kParamVco1FmModSource2          ]=0;
    paramToMsgType[kParamVco1PwModSource           ]=0;
    paramToMsgType[kParamVco2FmModSource1          ]=0;
    paramToMsgType[kParamVco2FmModSource2          ]=0;
    paramToMsgType[kParamVco2PwModSource           ]=0;
    paramToMsgType[kParamShMixerSource1            ]=0;
    paramToMsgType[kParamShMixerSource2            ]=0;
    paramToMsgType[kParamShTrigSource              ]=0;
    paramToMsgType[kParamMixerSource1              ]=0;
    paramToMsgType[kParamMixerSource2              ]=0;
    paramToMsgType[kParamMixerSource3              ]=0;
    paramToMsgType[kParamVcfModSource1             ]=0;
    paramToMsgType[kParamVcfModSource2             ]=0;
    paramToMsgType[kParamVcfModSource3             ]=0;
    paramToMsgType[kParamVcaModSource              ]=0;
    paramToMsgType[kParamAdsrMode                  ]=0;
    paramToMsgType[kParamAdsrRepeat                ]=0;
    paramToMsgType[kParamArMode                    ]=0;
    paramToMsgType[kParamNoiseType                 ]=0;
    paramToMsgType[kParamKeybOnOff                 ]=0;
    paramToMsgType[kParamVco2Sync                  ]=0;
    paramToMsgType[kParamLfoBpmHertz               ]=0;
    paramToMsgType[kParamVcfModel                  ]=0;
    paramToMsgType[kParamBoost                     ]=0;
    paramToMsgType[kParamPortamento                ]=0;
    paramToMsgType[kParamMixerNoiseLevel           ]=0;
    paramToMsgType[kParamVcfFreq                   ]=0;
    paramToMsgType[kParamVcfRes                    ]=0;
    paramToMsgType[kParamHpfFreq                   ]=0;
    paramToMsgType[kParamVcaGain                   ]=0;
    paramToMsgType[kParamVcfKeyb                   ]=0;
    paramToMsgType[kParamVcfAdsr                   ]=0;
    paramToMsgType[kParamVcaAdsr                   ]=0;
    paramToMsgType[kParamArAttack                  ]=0;
    paramToMsgType[kParamArRelease                 ]=0;
    paramToMsgType[kParamAdsrAttack                ]=0;
    paramToMsgType[kParamAdsrDecay                 ]=0;
    paramToMsgType[kParamVco1ShLevel               ]=0;
    paramToMsgType[kParamVco2ShLevel               ]=0;
    paramToMsgType[kParamShLag                     ]=0;
    paramToMsgType[kParamVcfShLevel                ]=0;
    paramToMsgType[kParamAdsrSustain               ]=0;
    paramToMsgType[kParamAdsrRelease               ]=0;
    paramToMsgType[kParamVco1FmModLfoLevel         ]=0;
    paramToMsgType[kParamVco1PwModLfoLevel         ]=0;
    paramToMsgType[kParamVco2FmModLfoLevel         ]=0;
    paramToMsgType[kParamVco2PwModLfoLevel         ]=0;
    paramToMsgType[kParamLfoFreq                   ]=0;
    paramToMsgType[kParamArVel                     ]=0;
    paramToMsgType[kParamArKeyb                    ]=0;
    paramToMsgType[kParamVco1Coarse                ]=0;
    paramToMsgType[kParamVco1Fine                  ]=0;
    paramToMsgType[kParamVco1PwWidth               ]=0;
    paramToMsgType[kParamShMixerMod1Level          ]=0;
    paramToMsgType[kParamShMixerMod2Level          ]=0;
    paramToMsgType[kParamAudioMixerIn2level        ]=0;
    paramToMsgType[kParamVco2Coarse                ]=0;
    paramToMsgType[kParamVco2Fine                  ]=0;
    paramToMsgType[kParamVco2PwWidth               ]=0;
    paramToMsgType[kParamAudioMixerIn3level        ]=0;
    paramToMsgType[kParamBendRange                 ]=0;
    paramToMsgType[kParamModWheelIntensity         ]=0;
    paramToMsgType[kParamChorusPhase               ]=1;
    paramToMsgType[kParamChorusRate                ]=1;
    paramToMsgType[kParamChorusDepth               ]=1;
    paramToMsgType[kParamChorusFeedback            ]=1;
    paramToMsgType[kParamChorusWet                 ]=0;
    paramToMsgType[kParamAftertouchPitch           ]=0;
    paramToMsgType[kParamAftertouchFilter          ]=0;
    paramToMsgType[kParamDelayTimeLMS              ]=1;
    paramToMsgType[kParamDelayTimeRMS              ]=1;
    paramToMsgType[kParamDelayTimeLBPM             ]=1;
    paramToMsgType[kParamDelayTimeRBPM             ]=1;
    paramToMsgType[kParamDelayFeedbackLeft         ]=0;
    paramToMsgType[kParamDelayHidampLeft           ]=1;
    paramToMsgType[kParamDelayLevelLeft            ]=1;
    paramToMsgType[kParamDelayFeedbackRight        ]=0;
    paramToMsgType[kParamDelayHidampRight          ]=1;
    paramToMsgType[kParamDelayLevelRight           ]=1;
    paramToMsgType[kParamDelayWet                  ]=0;
    paramToMsgType[kParamFlangerChorus             ]=1;
    paramToMsgType[kParamEffectBypass              ]=1;
    paramToMsgType[kParamDelayUnitLeft             ]=1;
    paramToMsgType[kParamDelayUnitRight            ]=1;
    paramToMsgType[kParamDelayCrossDual            ]=1;
    paramToMsgType[kParamKeybModeRetrig            ]=0;
    paramToMsgType[kParamKeybModeLowNote           ]=0;
    paramToMsgType[kParamKeybModeSingle            ]=0;
    paramToMsgType[kParamLfoSettBpm                ]=0;
    paramToMsgType[kParamAftertouchVco             ]=0;
    paramToMsgType[kParamMidiClockBpm              ]=1;
    paramToMsgType[kParamPitchWheel                ]=0;
    paramToMsgType[kParamMasterOctave              ]=0;
    paramToMsgType[kParamVco1Octave                ]=0;
    paramToMsgType[kParamVco2Octave                ]=0;
    paramToMsgType[kParamLfoNote                   ]=0;

  
#if IPLUG_EDITOR // All UI methods and member variables should be within an IPLUG_EDITOR guard, should you want distributed UI
  mMakeGraphicsFunc = [&]() {
    return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS, 1.);
  };
  
  mLayoutFunc = [&](IGraphics* pGraphics) {
    pGraphics->AttachCornerResizer(EUIResizerMode::Scale, false);
    //pGraphics->AttachPanelBackground(COLOR_GRAY);
    pGraphics->HandleMouseOver(true);
    //pGraphics->EnableLiveEdit(true);
    pGraphics->LoadFont("Roboto-Regular", ROBOTTO_FN);
    const IRECT b = pGraphics->GetBounds();

    IControl* pBG = new IPanelControl(IRECT(0,0, HSM_W, HSK_H), IColor(255,39,39,39));
    pGraphics->AttachControl(pBG);


    //pGraphics->AttachControl(new IVMultiSliderControl<4>(b.GetGridCell(0, 2, 2).GetPadded(-30), "", DEFAULT_STYLE, kParamAttack, kVertical, 0.f, 1.f));
    const IRECT controls = b.GetGridCell(1, 2, 2);

    IBitmap bitmap;

    bitmap = pGraphics->LoadBitmap(PNGBACK_FN);
    IControl* backCtrl = new IBitmapControl(0,0, bitmap, kNoParameter);
    pGraphics->AttachControl(backCtrl, -1, "");

    /* BITMAPS */
    //bitmap = pGraphics->LoadBitmap(PNGPANELHEAD1_FN);
    //IControl* mainPanelHeadCtrl = new IBitmapControl(0, 0, bitmap, kNoParameter);
    //pGraphics->AttachControl(mainPanelHeadCtrl);

    bitmap = pGraphics->LoadBitmap(PNGPANELMAIN_FN);
    IControl* mainPanelCtrl = new IBitmapControl(4, 35, bitmap, kNoParameter);
    pGraphics->AttachControl(mainPanelCtrl, -1, "main");

    bitmap = pGraphics->LoadBitmap(PNGPANELADD_FN);
    IControl* addPanelCtrl = new IBitmapControl(4, 35, bitmap, kNoParameter);
    pGraphics->AttachControl(addPanelCtrl, -1, "add");
    if (strcmp(addPanelCtrl->GetGroup(), "add") == 0) addPanelCtrl->Hide(true);

    //bitmap = pGraphics->LoadBitmap(PNGKEYBACK_FN);
    //IControl* keybackCtrl = new IBitmapControl(0, HS_H, bitmap, kNoParameter);
    //pGraphics->AttachControl(keybackCtrl, -1, "keyboard");
 
    IRECT keybRect = IRECT(MARGIN_W, HS_H + MARGIN_H, PLUG_WIDTH - MARGIN_W, HS_H + MARGIN_H + KEYBOARD_H);
    keybCtrl = new IVKeyboardControl(keybRect.FracRectHorizontal(0.85), 36, 91);
    pGraphics->AttachControl(keybCtrl, kCtrlTagKeyboard, "keyboard");

    pGraphics->AttachControl(new ICaptionControl(IRECT(873, 543, 903, 563), kParamKeyboardOctave, DEFAULT_TEXT, COLOR_LIGHT_GRAY, true), -1, "keyboard");

    IVButtonControl* buttCtrl = new IVButtonControl(IRECT(847, 590, 932, 620), [&](IControl*) {
      IMidiMsg msg;
      msg.Clear();
      msg.mStatus = mChannel | (IMidiMsg::kControlChange << 4);
      msg.mData1 = IMidiMsg::kAllNotesOff;
      msg.mData2 = 0;
      msg.mOffset = 0;
      SendMidiMsgFromUI(msg);
    },

      "All Notes Off", IVStyle(DEFAULT_SHOW_LABEL, DEFAULT_SHOW_VALUE, {}, IText(12)));

    buttCtrl->SetAnimation(DefaultAnimationFunc);
    pGraphics->AttachControl(buttCtrl, -1, "keyboard");

    

    //pGraphics->AttachBackground("panelmain.png");

    //IControl* IBitmapControl = new IBitmapControl(0, 0, bg, kNoParameter, kBlendClobber);
    //pGraphics->AttachBackground("panelhead1.png");

    /* SWITCHES */
    bitmap = pGraphics->LoadBitmap(PNGTT_FN, 2);

    pGraphics->AttachControl(new IBSwitchControlMidi(86,  426, bitmap, kParamVco1FmModSource1), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(122, 426, bitmap, kParamVco1FmModSource2), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(196, 426, bitmap, kParamVco1PwModSource), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(234, 426, bitmap, kParamVco2FmModSource1), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(271, 426, bitmap, kParamVco2FmModSource2), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(345, 426, bitmap, kParamVco2PwModSource), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(382, 426, bitmap, kParamShMixerSource1), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(419, 426, bitmap, kParamShMixerSource2), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(456, 426, bitmap, kParamShTrigSource), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(527, 426, bitmap, kParamMixerSource1), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(564, 426, bitmap, kParamMixerSource2), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(599, 426, bitmap, kParamMixerSource3), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(638, 426, bitmap, kParamVcfModSource1), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(675, 426, bitmap, kParamVcfModSource2), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(711, 426, bitmap, kParamVcfModSource3), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(781, 426, bitmap, kParamVcaModSource), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(819, 426, bitmap, kParamAdsrMode), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(854, 426, bitmap, kParamAdsrRepeat), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(931, 426, bitmap, kParamArMode), -1, "main");

    pGraphics->AttachControl(new IBSwitchControlMidi(41, 88, bitmap, kParamNoiseType), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(163, 88, bitmap, kParamKeybOnOff), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(309, 88, bitmap, kParamVco2Sync), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(398, 54, bitmap, kParamLfoBpmHertz), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(637, 84, bitmap, kParamVcfModel), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(893, 4, bitmap, kParamBoost), -1, "header");

    bitmap = pGraphics->LoadBitmap(PNGHFADERRED_FN, 1);
    pGraphics->AttachControl(new IBSliderControlMidi(601, 10, 80, kParamMasterVolume, bitmap, NULL,  EDirection::Horizontal), -1, "");
    pGraphics->AttachControl(new IBSliderControlMidi(741, 11, 80, kParamSynthMic, bitmap, NULL, EDirection::Horizontal), -1, "");

    /* FADER BLACK*/
    bitmap = pGraphics->LoadBitmap(PNGFADERBLACK_FN, 1);
    pGraphics->AttachControl(new IBSliderControlMidi(39, 288,89, kParamPortamento, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(523, 288, 89, kParamMixerNoiseLevel, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(523, 83, 89, kParamVcfFreq, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(560, 83, 89, kParamVcfRes, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(709, 83, 89, kParamHpfFreq, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(778, 83, 89, kParamVcaGain, bitmap), -1, "main");

    bitmap = pGraphics->LoadBitmap(PNGFADERRED_FN, 1);
    pGraphics->AttachControl(new IBSliderControlMidi(635, 288, 89, kParamVcfKeyb, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(709, 288, 89, kParamVcfAdsr, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(779, 288, 89, kParamVcaAdsr, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(815, 83, 89, kParamArAttack, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(817+36, 83, 89, kParamArRelease, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(782+36, 288, 89, kParamAdsrAttack, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(817+36, 288, 89, kParamAdsrDecay, bitmap), -1, "main");

    bitmap = pGraphics->LoadBitmap(PNGFADERYELLOW_FN, 1);
    pGraphics->AttachControl(new IBSliderControlMidi(121, 288, 89, kParamVco1ShLevel, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(269, 288, 89, kParamVco2ShLevel, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(486, 288, 89, kParamShLag, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(671, 288, 89, kParamVcfShLevel, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(890, 288, 89, kParamAdsrSustain, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(926, 288, 89, kParamAdsrRelease, bitmap), -1, "main");

    bitmap = pGraphics->LoadBitmap(PNGFADERPINK_FN, 1);
    pGraphics->AttachControl(new IBSliderControlMidi(83, 288, 89, kParamVco1FmModLfoLevel, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(195, 288, 89, kParamVco1PwModLfoLevel, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(231, 288, 89, kParamVco2FmModLfoLevel, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(343, 288, 89, kParamVco2PwModLfoLevel, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(486, 83, 89, kParamLfoFreq, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(853+36, 83, 89, kParamArVel, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(926, 83, 89, kParamArKeyb, bitmap), -1, "main");

    bitmap = pGraphics->LoadBitmap(PNGFADERCYAN_FN, 1);
    pGraphics->AttachControl(new IBSliderControlMidi(83, 83, 89, kParamVco1Coarse, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(119, 83, 89, kParamVco1Fine, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(158, 288, 89, kParamVco1PwWidth, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(379, 288, 89, kParamShMixerMod1Level, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(417, 288, 89, kParamShMixerMod2Level, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(561, 288, 89, kParamAudioMixerIn2level, bitmap), -1, "main");

    bitmap = pGraphics->LoadBitmap(PNGFADERGREEN_FN, 1);
    pGraphics->AttachControl(new IBSliderControlMidi(230, 83, 89, kParamVco2Coarse, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(267, 83, 89, kParamVco2Fine, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(306, 288, 89, kParamVco2PwWidth, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(597, 288, 89, kParamAudioMixerIn3level, bitmap), -1, "main");

    // Slider ADD 
    bitmap = pGraphics->LoadBitmap(PNGFADERBLACK_FN, 1);
    std::function<double(double)> mappingFunc2 = [](double midiVal) {return midiVal * 127. / 24.; };
    pGraphics->AttachControl(new IBSliderControlMidi(22, 84, 89, kParamBendRange, bitmap, mappingFunc2), -1, "add");
    pGraphics->AttachControl(new ICaptionControl(IRECT(22, 185, 47, 205), kParamBendRange, DEFAULT_TEXT, COLOR_LIGHT_GRAY), -1, "add");
    pGraphics->AttachControl(new IBSliderControlMidi(22, 303, 89, kParamModWheelIntensity, bitmap), -1, "add");
    pGraphics->AttachControl(new IBSliderControlMidi(123, 303, 89, kParamChorusRate, bitmap), -1, "add");
    pGraphics->AttachControl(new ICaptionControl(IRECT(121, 273, 153, 288), kParamChorusRate, DEFAULT_TEXT, COLOR_LIGHT_GRAY), -1, "add");

    bitmap = pGraphics->LoadBitmap(PNGFADERCYAN_FN, 1);
    pGraphics->AttachControl(new IBSliderControlMidi(81, 303, 89, kParamChorusPhase, bitmap), -1, "add");
    pGraphics->AttachControl(new ICaptionControl(IRECT(78, 273, 110, 288), kParamChorusPhase, DEFAULT_TEXT, COLOR_LIGHT_GRAY), -1, "add");

    bitmap = pGraphics->LoadBitmap(PNGFADERRED_FN, 1);
    pGraphics->AttachControl(new IBSliderControlMidi(168, 303, 89, kParamChorusDepth, bitmap), -1, "add");

    bitmap = pGraphics->LoadBitmap(PNGFADERYELLOW_FN, 1);
    pGraphics->AttachControl(new IBSliderControlMidi(211, 303, 89, kParamChorusFeedback, bitmap), -1, "add");
    pGraphics->AttachControl(new IBSliderControlMidi(507, 303, 89, kParamDelayFeedbackLeft, bitmap), -1, "add");
    pGraphics->AttachControl(new IBSliderControlMidi(655, 303, 89, kParamDelayFeedbackLeft, bitmap), -1, "add");

    bitmap = pGraphics->LoadBitmap(PNGFADERGREEN_FN, 1);

    
    pGraphics->AttachControl(new IBSliderControlMidi(282, 303, 89, kParamChorusWet, bitmap), -1, "add");

    bitmap = pGraphics->LoadBitmap(PNGFADERBG_FN);
    pGraphics->AttachControl(new IBitmapControl(357, 304, bitmap, kNoParameter), kCtrlTagFaderBg1, "add");
    pGraphics->AttachControl(new IBitmapControl(410, 304, bitmap, kNoParameter), kCtrlTagFaderBg2, "add");

    bitmap = pGraphics->LoadBitmap(PNGFADERGREEN_FN, 1);

    pGraphics->AttachControl(new IBSliderControlMidi(359, 303, 89, kParamDelayTimeLMS, bitmap), kCtrlTagDelayTimeLMS, "add");
    pGraphics->AttachControl(new ICaptionControl(IRECT(347, 287, 392, 302), kParamDelayTimeLMS, DEFAULT_TEXT, COLOR_LIGHT_GRAY), kCtrlTagDelayTimeLMSCaption, "add");

    pGraphics->AttachControl(new IBSliderControlMidi(412, 303, 89, kParamDelayTimeRMS, bitmap), kCtrlTagDelayTimeRMS, "add");
    pGraphics->AttachControl(new ICaptionControl(IRECT(401, 287, 447, 302), kParamDelayTimeRMS, DEFAULT_TEXT, COLOR_LIGHT_GRAY), kCtrlTagDelayTimeRMSCaption, "add");



    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(351, 322, 397, 342), kParamDelayTimeLBPM, DEFAULT_TEXT, COLOR_LIGHT_GRAY, true), kCtrlTagDelayTimeLBPM, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(426, 322, 472, 342), kParamDelayTimeRBPM, DEFAULT_TEXT, COLOR_LIGHT_GRAY, true), kCtrlTagDelayTimeRBPM, "add");

    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(694, 94, 744, 114), kParamLfoNote, DEFAULT_TEXT, COLOR_LIGHT_GRAY, true), -1, "add");
   

    pGraphics->AttachControl(new IBSliderControlMidi(594, 303, 89, kParamDelayLevelLeft, bitmap), -1, "add");
    pGraphics->AttachControl(new IBSliderControlMidi(737, 303, 89, kParamDelayLevelRight, bitmap), -1, "add");
    pGraphics->AttachControl(new IBSliderControlMidi(836, 303, 89, kParamDelayWet, bitmap), -1, "add");

    bitmap = pGraphics->LoadBitmap(PNGFADERPINK_FN, 1);
    pGraphics->AttachControl(new IBSliderControlMidi(550, 303, 89, kParamDelayHidampLeft, bitmap), -1, "add");
    pGraphics->AttachControl(new IBSliderControlMidi(696, 303, 89, kParamDelayHidampRight, bitmap), -1, "add");
    pGraphics->AttachControl(new IBSliderControlMidi(506, 60, 89, kParamAftertouchPitch, bitmap), -1, "add");
    pGraphics->AttachControl(new IBSliderControlMidi(612, 60, 89, kParamAftertouchFilter, bitmap), -1, "add");

    // SWITCHES ADD

    bitmap = pGraphics->LoadBitmap(PNGTT_FN, 2);

    pGraphics->AttachControl(new IBSwitchControlMidi(162, 422, bitmap, kParamFlangerChorus), -1,    "add");
    bitmap = pGraphics->LoadBitmap(PNGTTBYPASS_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(328, 422, bitmap, kParamEffectBypass), -1,    "add");
    bitmap = pGraphics->LoadBitmap(PNGTT_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(371, 422, bitmap, kParamDelayUnitLeft), -1,   "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(442, 422, bitmap, kParamDelayUnitRight), -1,  "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(483, 422, bitmap, kParamDelayCrossDual), -1,  "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(306, 83, bitmap, kParamKeybModeRetrig), -1,  "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(366, 83, bitmap, kParamKeybModeLowNote), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(423, 83, bitmap, kParamKeybModeSingle), -1,  "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(761, 83, bitmap, kParamLfoSettBpm), -1,      "add");

    bitmap = pGraphics->LoadBitmap(PNGSWITCH5_FN, 3, true);
    pGraphics->AttachControl(new IBSwitchControlMidi(557, 87, bitmap, kParamAftertouchVco), -1, "add");

    bitmap = pGraphics->LoadBitmap(PNGMIDIACTIVE_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(812, 226, bitmap, kParamMidiActive), -1, "main");

    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(141, 97, 188, 114), kParamMidiClockBpm, DEFAULT_TEXT, COLOR_LIGHT_GRAY, true), -1, "add");

    // Program Change
    captionCtrl = new ICaptionControl(IRECT(820 + 207, 10, 880 + 207, 30), kParamProgram, DEFAULT_TEXT, COLOR_LIGHT_GRAY, true);
    pGraphics->AttachControl(captionCtrl, -1, "header");

    bitmap = pGraphics->LoadBitmap(PNGPLUS_FN);
    pGraphics->AttachControl(new IBButtonControl(880 + 207,10, bitmap, [&](IControl*) {
      captionCtrl->SetValueFromUserInput(GetParam(kParamProgram)->ToNormalized(GetParam(kParamProgram)->FromNormalized(captionCtrl->GetValue())+1));
    }
    ), -1, "header");

    bitmap = pGraphics->LoadBitmap(PNGMINUS_FN);
    pGraphics->AttachControl(new IBButtonControl(800+207, 10, bitmap, [&](IControl*) {
      captionCtrl->SetValueFromUserInput(GetParam(kParamProgram)->ToNormalized(GetParam(kParamProgram)->FromNormalized(captionCtrl->GetValue()) - 1));
    }
    ), -1, "header");

    // MAIN

    // Kein Pitchwheel sondern Modwheel
    bitmap = pGraphics->LoadBitmap(PNGPITCHWHEEL_FN, 18, true);
    pGraphics->AttachControl(new IBKnobControlMidi(40, 395, bitmap, kParamPitchWheel), -1, "main");

    bitmap = pGraphics->LoadBitmap(PNGSWITCH4_FN, 3, true);
    pGraphics->AttachControl(new IBKnobControlMidi(41, 177, bitmap, kParamMasterOctave), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(196, 87, bitmap, kParamVco1Octave), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(343, 87, bitmap, kParamVco2Octave), -1, "main");


    auto windowFunc = [](IControl* pCaller) {
      pCaller->SetValue(1.);
      if (pCaller->GetUI()) {

        if (pCaller->GetTag() != kCtrlTagMain) pCaller->GetUI()->GetControlWithTag(kCtrlTagMain)->SetValueFromUserInput(0);
        if (pCaller->GetTag() != kCtrlTagAdd) pCaller->GetUI()->GetControlWithTag(kCtrlTagAdd)->SetValueFromUserInput(0);

        pCaller->GetUI()->ForControlInGroup("main", [&](IControl& control) {if (pCaller->GetTag() == kCtrlTagMain) control.Hide(false); else control.Hide(true); });
        pCaller->GetUI()->ForControlInGroup("add", [&](IControl& control) {if (pCaller->GetTag() == kCtrlTagAdd) control.Hide(false); else control.Hide(true); });
      
        if (pCaller->GetUI()->GetControlWithTag(kCtrlTagAdd)->GetValue() == 1) {
          if (pCaller->GetDelegate()->GetParam(kParamDelayUnitLeft)->Value() == 0) {
            pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(true);
            pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMS)->Hide(false);
            pCaller->GetUI()->GetControlWithTag(kCtrlTagFaderBg1)->Hide(false);
            pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMSCaption)->Hide(false);

          }
          else {
           pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(false);
           pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMSCaption)->Hide(true);
           pCaller->GetUI()->GetControlWithTag(kCtrlTagFaderBg1)->Hide(true);
           pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMS)->Hide(true);
          }
        }

        if (pCaller->GetUI()->GetControlWithTag(kCtrlTagAdd)->GetValue() == 1) {
          if (pCaller->GetDelegate()->GetParam(kParamDelayUnitRight)->Value() == 0) {
            pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(true);
            pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMS)->Hide(false);
            pCaller->GetUI()->GetControlWithTag(kCtrlTagFaderBg2)->Hide(false);
            pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMSCaption)->Hide(false);
          }
          else {
            pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(false);
            pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMSCaption)->Hide(true);
            pCaller->GetUI()->GetControlWithTag(kCtrlTagFaderBg2)->Hide(true);
            pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMS)->Hide(true);
          }
        }

      }
    };

    bitmap = pGraphics->LoadBitmap(PNGMAIN_FN, 2);
    IBSwitchControlFunc *mainCtrl = new IBSwitchControlFunc(232, 8, bitmap, windowFunc, kNoParameter);
    pGraphics->AttachControl(mainCtrl, kCtrlTagMain);
    mainCtrl->SetValue(1);
    bitmap = pGraphics->LoadBitmap(PNGADD_FN, 2);
    IBSwitchControlFunc *addCtrl = new IBSwitchControlFunc(298, 8, bitmap, windowFunc, kNoParameter);
    pGraphics->AttachControl(addCtrl, kCtrlTagAdd);
   
    
    auto resizeFunc = [](IControl* pCaller) 
    {
     
      if (pCaller->GetUI()) {

      int keybHide = pCaller->GetUI()->GetControlWithTag(kCtrlTagKeybHide)->GetValue();
      int midimonHide = pCaller->GetUI()->GetControlWithTag(kCtrlTagMidiMonHide)->GetValue();

      if (midimonHide == 1 && keybHide == 1) {
        pCaller->GetUI()->Resize(HSM_W, HSK_H, 1);
      }
      else if (midimonHide == 1 && keybHide == 0) {
        pCaller->GetUI()->Resize(HSM_W, HS_H, 1);
      }
      else if (midimonHide == 0 && keybHide == 0) {
        pCaller->GetUI()->Resize(HS_W, HS_H, 1);
      }
      else if (midimonHide == 0 && keybHide == 1) {
        pCaller->GetUI()->Resize(HS_W, HSK_H, 1);
      }
    }

    pCaller->SetDirty();
    };

    bitmap = pGraphics->LoadBitmap(PNGMIDIMONITOR_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlFunc(812, 176, bitmap, resizeFunc, kNoParameter), kCtrlTagMidiMonHide, "main");
    bitmap = pGraphics->LoadBitmap(PNGKEYB_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlFunc(812, 201, bitmap, resizeFunc, kNoParameter), kCtrlTagKeybHide, "main");



    //bitmap = pGraphics->LoadBitmap(PNGMIDIMONBACK_FN);
    //IControl* midiCtrlBack = new IBitmapControl(0, HSK_H+MARGIN_H, bitmap, kNoParameter);
    //pGraphics->AttachControl(midiCtrlBack, kCtrlTagMidiBack, "midiMonitor");

    mMidiLogger = new MidiLoggerControl(IRECT(HS_W + MARGIN_W, MARGIN_H + MIDILOG_H, HS_W + MIDIPRESET_W - MARGIN_W, HS_H-MARGIN_H), "", "", IText(12, COLOR_BLACK, NULL, EAlign::Near), COLOR_WHITE);
    pGraphics->AttachControl(mMidiLogger, kCtrlTagMidiLogger, "midiMonitor");

    IVButtonControl* clearCtrl = new IVButtonControl(IRECT(966, 212, 1051, 242), [&](IControl*) {
      mMidiLogger->Clear();
    },

      "Clear", IVStyle(DEFAULT_SHOW_LABEL, DEFAULT_SHOW_VALUE, {}, IText(12)));

    buttCtrl->SetAnimation(DefaultAnimationFunc);
    pGraphics->AttachControl(clearCtrl, kCtrlTagClear, "midiMonitor");

    mPresetMenu = new FileBrowser(IRECT(964+10, 36, 1160-10, 60));
    pGraphics->AttachControl(mPresetMenu, kCtrlTagPresetMenu);

    //mPresetMenu = new FileBrowser(IRECT(650, 10, 796, 27));
    //pGraphics->AttachControl(mPresetMenu, kCtrlTagPresetMenu);


    if (GetUI()) {
      for (auto k = 0; k < GetUI()->NControls(); k++) {
        if (strcmp(GetUI()->GetControl(k)->GetGroup(), "add") == 0) {
          GetUI()->GetControl(k)->Hide(true);
        }
      }

      GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(true);
      GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMS)->Hide(true);
      GetUI()->GetControlWithTag(kCtrlTagFaderBg1)->Hide(true);
      GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMSCaption)->Hide(true);

      GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(true);
      GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMS)->Hide(true);
      GetUI()->GetControlWithTag(kCtrlTagFaderBg2)->Hide(true);
      GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMSCaption)->Hide(true);
    }

  };
  
#endif
}

#if IPLUG_DSP
void Prodyssey::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
  const int nChans = NOutChansConnected();
  
  for (auto s = 0; s < nFrames; s++) {
    for (auto c = 0; c < nChans; c++) {
      outputs[c][s] = 0.;
    }
  }
}

void Prodyssey::OnIdle()
{
  mMidiLoggerSender.TransmitData(*this);
}

void Prodyssey::OnReset()
{
}

void Prodyssey::OnUIOpen() {

  SendCurrentParamValuesFromDelegate();

  // Presetname
  //mPresetMenu->restorePresetPath(mCurrentPresetPath.Get());
}

bool Prodyssey::OnMessage(int messageTag, int controlTag, int dataSize, const void *pData) {

  // Step wurde von GUI verädnert
 

  // Preset wurde geändert
  if (messageTag == 5) { // PresetPfadUpdate;
    if (controlTag == kCtrlTagPresetMenu) {
      struct Data {
        int sequence;
        int step;
        double val;
      };
      mCurrentPresetPath = (WDL_String*)pData;
    }
  }

  // sage Host das was geändert wurde und bei schließen gespeichert werden soll.
  DirtyParametersFromUI();
  return true;
}

// wird nur von Keyboard und control bewegungen aufgerufen
void Prodyssey::ProcessMidiMsg(const IMidiMsg& msg)
{
  TRACE;

  if (mMidiActive) {

    if (msg.mOffset == -2) { // From UI

      int status = msg.StatusMsg();

      switch (status)
      {
      case IMidiMsg::kNoteOn:
      case IMidiMsg::kNoteOff:
      case IMidiMsg::kPolyAftertouch:
      case IMidiMsg::kControlChange:
      case IMidiMsg::kProgramChange:
      case IMidiMsg::kChannelAftertouch:
      case IMidiMsg::kPitchWheel:
      {
        SendMidiMsg(msg); // nach außen
        mMidiLoggerSender.SetValRT(msg);
      }
      default:
        return;
      }
    }
    else { // From MIDI IN
      mMidiLoggerSender.SetValRT(msg);
    }
  }
}

void Prodyssey::OnParamChange(int paramIdx)
{
  IMidiMsg msg;
  static IMidiMsg msgAlt;
  static double valAlt = 0;

  if (paramToCC[paramIdx] >= 0) {
    msg.Clear();

    if (paramToMsgType[paramIdx] == 0) { //CC
      msg.mStatus = mChannel | (IMidiMsg::kControlChange << 4);
    }
    else if (paramToMsgType[paramIdx] == 1) { // Aftertouch
      msg.mStatus = mChannel | (IMidiMsg::kPolyAftertouch << 4);
    }
  
    msg.mData1 = paramToCC[paramIdx];
    msg.mData2 = (int)(GetParam(paramIdx)->GetNormalized() * 127.0);

    // Schalter muss in Mittelstellung 64 liefern
    switch (paramIdx) {
    case kParamMasterOctave:
    case kParamVco1Octave:
    case kParamVco2Octave:
    case kParamAftertouchVco:
      if ((int)(GetParam(paramIdx)->GetNormalized() * 127.0) == 63) msg.mData2 = 64;
      break;
    }

    switch (paramIdx) {
    case kParamDelayTimeLBPM:
    case kParamDelayTimeRBPM:
    case kParamLfoNote:
      msg.mData2 = GetParam(paramIdx)->Value();
      break;
    case kParamMidiClockBpm:
      msg.mData2 = GetParam(paramIdx)->Value()-72;
      break;
    }


    if(paramIdx == kParamBendRange) msg.mData2 = GetParam(paramIdx)->Value();

    msg.mOffset = -2;
  }
  if (msg.mStatus != msgAlt.mStatus || msg.mData1 != msgAlt.mData1 || msg.mData2 != msgAlt.mData2) {
    SendMidiMsgFromUI(msg);
  }
  msgAlt = msg;
 

  switch (paramIdx)
  {

    int val;
    int lowNote; 
    int highNote;
 
  case kParamKeyboardOctave:
    val = GetParam(paramIdx)->Value(); // 0-6
    lowNote = 36 + (val-3) * 12;
    highNote = 91 + (val-3) * 12;
    if(keybCtrl && GetUI()) keybCtrl->SetNoteRange(lowNote, highNote, true);
    break;

  case kParamProgram:
    msg.Clear();
    msg.mStatus = mChannel | (IMidiMsg::kProgramChange << 4);
    msg.mData1 = GetParam(paramIdx)->Value();
    msg.mData2 = 0;
    msg.mOffset = 0;
    SendMidiMsgFromUI(msg);
          
   // DIno Spezialität Preset mit Wheel
    msg.Clear();
    msg.mStatus = 0xE0;
    msg.mData1 = 0x01; // Proddy
    msg.mData2 = GetParam(paramIdx)->Value();
    msg.mOffset = 0;
    SendMidiMsgFromUI(msg);
          
    break;

  case kParamMidiActive:
    mMidiActive = GetParam(paramIdx)->Value();

    if (!mMidiActive) {
      if (GetUI())
      {
        for (auto c = 0; c < GetUI()->NControls(); c++) // TODO: could keep a map
        {
          IControl* pControl = GetUI()->GetControl(c);
          pControl->SetWantsMidi(false);
        }
      }
    }
    else {
      if (GetUI())
      {
        for (auto c = 0; c < GetUI()->NControls(); c++) // TODO: could keep a map
        {
          IControl* pControl = GetUI()->GetControl(c);
          pControl->SetWantsMidi(true);
        }
      }
    }

    break;

  case kParamDelayUnitLeft:
    if (GetUI()) {
      if (GetUI()->GetControlWithTag(kCtrlTagAdd)->GetValue() == 1) {
        if (GetParam(paramIdx)->Value() == 0) {
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(true);
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMS)->Hide(false);
          GetUI()->GetControlWithTag(kCtrlTagFaderBg1)->Hide(false);
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMSCaption)->Hide(false);

        }
        else {
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(false);
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMSCaption)->Hide(true);
          GetUI()->GetControlWithTag(kCtrlTagFaderBg1)->Hide(true);
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMS)->Hide(true);
        }
      }
    }
    break;
  case kParamDelayUnitRight:
    if (GetUI()) {
      if (GetUI()->GetControlWithTag(kCtrlTagAdd)->GetValue() == 1) {
        if (GetParam(paramIdx)->Value() == 0) {
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(true);
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMS)->Hide(false);
          GetUI()->GetControlWithTag(kCtrlTagFaderBg2)->Hide(false);
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMSCaption)->Hide(false);
        }
        else {
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(false);
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMSCaption)->Hide(true);
          GetUI()->GetControlWithTag(kCtrlTagFaderBg2)->Hide(true);
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMS)->Hide(true);
        }
      }
    }
    break;
      
    default:
      break;
  }
}

bool Prodyssey::SerializeState(IByteChunk& chunk) const {

  TRACE;

 
  // Presetname
  WDL_String s;
  s.Set(mCurrentPresetPath.Get());
  chunk.PutStr(s.Get());

  return SerializeParams(chunk);
}

// this over-ridden method is called when the host is trying to load the plug-in state and you need to unpack the data into your algorithm
// HIER KÖNNEN KEINE CONTROLS GEUPDATED WERDEN; DA MGRAPHICS NOCH NICHT EXISTIERT!!!!
int Prodyssey::UnserializeState(const IByteChunk& chunk, int startPos) {

  TRACE;

 
  int pos = startPos;
  // Presetname
  WDL_String str;
  pos = chunk.GetStr(str, pos);
  mCurrentPresetPath.Set(str.Get());

  return UnserializeParams(chunk, pos);
}
#endif
