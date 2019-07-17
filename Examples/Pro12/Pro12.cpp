#include "Pro12.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"


/*void IControl::OnMidi(const IMidiMsg &msg) {
  SetValueFromDelegate(msg.mData2);
}*/

Pro12::Pro12(IPlugInstanceInfo instanceInfo)
: IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo)
{

  mCurrentPresetPath.Set("Default");

  // KNOBS MAIN

  GetParam(kParamMasterVolume)->InitDouble("Master Volume", 0, 0, 1, 0.001);

  GetParam(kParamSynthMic)->InitDouble("Synth Mic", 0, 0, 1, 0.001);
  GetParam(kParamBoost)->InitDouble("Boost", 0, 0, 1, 0.001);

  GetParam(kParamFilterEnv)->InitDouble("Filter Env", 0, -5, 5, 0.01);
  GetParam(kParamOSCB)->InitDouble("OSC B", 0, 0, 10, 0.01);
  GetParam(kParamOSCAFreq)->InitDouble("OSC A Freq", 0, 0, 10, 0.01);
  GetParam(kParamOSCAPW)->InitDouble("OSC A PW", 0, 0, 10, 0.01);
  GetParam(kParamOSCBFreq)->InitDouble("OSC B Freq", 0, 0, 10, 0.01);
  GetParam(kParamOSCBFine)->InitDouble("OSC B Fine", 0, 0, 10, 0.01);
  GetParam(kParamOSCBPW)->InitDouble("OSC B PW", 0, 0, 10, 0.01);
  GetParam(kParamSourceMix)->InitDouble("Source Mix", 0, 0, 10, 0.01);
  GetParam(kParamGlide)->InitDouble("Glide", 0, 0, 10, 0.01);
  GetParam(kParamLFOFreq)->InitDouble("LFO Freq", 0, 0, 10, 0.01);
  GetParam(kParamMixOSCA)->InitDouble("Mix OSC A", 0, 0, 10, 0.01);
  GetParam(kParamMixOSCB)->InitDouble("Mix OSC B", 0, 0, 10, 0.01);
  GetParam(kParamMixNoise)->InitDouble("Mix Noise", 0, 0, 10, 0.01);
  GetParam(kParamMasterTune)->InitDouble("Master Tune", 0, -5, 5, 0.01);
  GetParam(kParamVCFCutoff)->InitDouble("VCF Cutoff", 0, 0, 10, 0.01);
  GetParam(kParamVCFResonance)->InitDouble("VCF Resonance", 0, 0, 10, 0.01);
  GetParam(kParamVCFEnvAmt)->InitDouble("VCF Env Amt", 0, 0, 10, 0.01);
  GetParam(kParamVCFKybAmt)->InitDouble("VCF Kyb Amt", 0, 0, 10, 0.01);
  GetParam(kParamVCFAttack)->InitDouble("VCF Attack", 0, 0, 10, 0.01);
  GetParam(kParamVCFDecay)->InitDouble("VCF Decay", 0, 0, 10, 0.01);
  GetParam(kParamVCFSustain)->InitDouble("VCF Sustain", 0, 0, 10, 0.01);
  GetParam(kParamVCFRelease)->InitDouble("VCF Release", 0, 0, 10, 0.01);
  GetParam(kParamVCFVelocity)->InitDouble("VCF Velocity", 0, 0, 10, 0.01);
  GetParam(kParamVCAAttack)->InitDouble("VCA Attack", 0, 0, 10, 0.01);
  GetParam(kParamVCADecay)->InitDouble("VCA Decay", 0, 0, 10, 0.01);
  GetParam(kParamVCASustain)->InitDouble("VCA Sustain", 0, 0, 10, 0.01);
  GetParam(kParamVCARelease)->InitDouble("VCA Release", 0, 0, 10, 0.01);
  GetParam(kParamVCAVelocity)->InitDouble("VCA Velocity", 0, 0, 10, 0.01);
  GetParam(kParamVolume)->InitDouble("Volume", 0, 0, 10, 0.01);
  // KNOBS ADD
  GetParam(kParamMWIntensity)->InitDouble("MW Intensity", 0, 0, 10, 0.01);
  GetParam(kParamMWOffset)->InitDouble("MW Offset", 0, 0, 10, 0.01);
  GetParam(kParamMWBendRange)->InitInt("MW Bend Range", 0, 0, 24);
  GetParam(kParamVoices)->InitInt("Voices", 2, 2, 12);
  GetParam(kParamDetune)->InitDouble("Detune", 0, 0, 10, 0.01);
  GetParam(kParamATPitch)->InitDouble("AT Pitch", 0, -5, 5, 0.01);
  GetParam(kParamATPw)->InitDouble("AT PW", 0, -5, 5, 0.01);
  GetParam(kParamATFIlter)->InitDouble("AT Filter", 0, -5, 5, 0.01);
  GetParam(kParamATAmp)->InitDouble("AT Amp", 0, -5, 5, 0.01);
  GetParam(kParamATMWAmt)->InitDouble("AT MW Amt", 0, -5, 5, 0.01);
  GetParam(kParamATLfoFreq)->InitDouble("AT LFO Freq", 0, -5, 5, 0.01);
  GetParam(kParamTimeVelVCFAttack)->InitDouble("Time Vel VCF Attack", 0, -5, 5, 0.01);
  GetParam(kParamTimeVelVCFDecrel)->InitDouble("Time Vel VCF Decrel", 0, -5, 5, 0.01);
  GetParam(kParamTimeVelVCAAttack)->InitDouble("Time Vel VCA Attack", 0, -5, 5, 0.01);
  GetParam(kParamTimeVelVCADecrel)->InitDouble("Time Vel VCA Decrel", 0, -5, 5, 0.01);
  GetParam(kParamLFOPhase)->InitInt("LFO Phase", 0, 0, 180);
  // KNOBS EFFECT
  GetParam(kParamChorusRate)->InitDouble("Chorus Rate", 0, 0, 20, 0.01, "", 0, "", IParam::ShapePowCurve(6));
  GetParam(kParamChorusPhase)->InitInt("Chorus Phase", 0, 0, 180);
  GetParam(kParamChorusDepth)->InitDouble("Chorus Depth", 0, 0, 10, 0.01);
  GetParam(kParamChorusFB)->InitDouble("Chorus FB", 0, -5, 5, 0.01);
  GetParam(kParamChorusMix)->InitDouble("Chorus Mix", 0, 0, 10, 0.01);
  GetParam(kParamDelayTimeL)->InitDouble("Delay Time L", 1.01, 1.01, 1365.33, 0.01);
  GetParam(kParamDelayTimeR)->InitDouble("Delay Time R", 1.01, 1.01, 1365.33, 0.01);
  GetParam(kParamDelayBpmL)->InitEnum("Delaytime L BPM", 0, 19, "", 0, "", "1/1", "1/2P", "1/2", "1/2T", "1/4P", "1/4", "1/4T", "1/8P", "1/8", "1/8T", "1/16P", "1/16", "1/16T", "1/32P", "1/32", "1/32T", "1/64P", "1/64", "1/64T");
  GetParam(kParamDelayBpmR)->InitEnum("Delaytime R BPM", 0, 19, "", 0, "", "1/1", "1/2P", "1/2", "1/2T", "1/4P", "1/4", "1/4T", "1/8P", "1/8", "1/8T", "1/16P", "1/16", "1/16T", "1/32P", "1/32", "1/32T", "1/64P", "1/64", "1/64T");
  GetParam(kParamDelayFBL)->InitDouble("Delay FB L", 0, 0, 10, 0.01);
  GetParam(kParamDelayFBR)->InitDouble("Delay FB R", 0, 0, 10, 0.01);
  GetParam(kParamDelayHidampL)->InitDouble("Delay Hidamp L", 0, 0, 10, 0.01);
  GetParam(kParamDelayHidampR)->InitDouble("Delay Hidamp R", 0, 0, 10, 0.01);
  GetParam(kParamDelayLevelL)->InitDouble("Delay Level L", 0, 0, 10, 0.01);
  GetParam(kParamDelayLevelR)->InitDouble("Delay Level R", 0, 0, 10, 0.01);
  GetParam(kParamDelayMix)->InitDouble("Delay Mix", 0, 0, 10, 0.01);

  // SWITCHES MAIN
  GetParam(kParamPolymodFRQA)->InitEnum("Poly Mod FRQ A", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamPolymodFRQB)->InitEnum("Poly Mod FRQ B", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamPolymodPWA)->InitEnum("Poly Mod PW A", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamPolymodPWB)->InitEnum("Poly Mod PW B", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamPolymodFilter)->InitEnum("Poly Mod Filter", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamWheelmodFRQA)->InitEnum("Wheel Mod FRQ A", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamWheelmodFRQB)->InitEnum("Wheel Mod FRQ B", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamWheelmodPWA)->InitEnum("Wheel Mod PW A", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamWheelmodPWB)->InitEnum("Wheel Mod PW B", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamWheelmodFilter)->InitEnum("Wheel Mod Filter", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamOSCASaw)->InitEnum("OSC A Saw", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamOSCAPulse)->InitEnum("OSC A Pulse", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamOSCASync)->InitEnum("OSC A Sync", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamOSCBSaw)->InitEnum("OSC B Saw", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamOSCBPulse)->InitEnum("OSC B Pulse", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamOSCBTri)->InitEnum("OSC B Tri", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamOSCBLowFreq)->InitEnum("OSC B LO FRQ", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamOSCBKeyb)->InitEnum("OSC B Kyb", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamLFOSaw)->InitEnum("LFO Saw", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamLFOTri)->InitEnum("LFO Tri", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamLFOPulse)->InitEnum("LFO Pulse", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamAdr)->InitEnum("ADR", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamRelease)->InitEnum("Release", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamUnison)->InitEnum("Unsion", 0, 2, "", 0, "", "Off", "On");

  // SWITCHES ADD
  GetParam(kParamKybRetrig)->InitEnum("KYB Retrig", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamKybLowNote)->InitEnum("KYB Low Note", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamKybSingle)->InitEnum("KYB Single", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamAtFreqA)->InitEnum("AT Freq A", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamAtFreqB)->InitEnum("AT Freq B", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamAtPwA)->InitEnum("AT PW A", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamAtPwB)->InitEnum("AT PW B", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamLfoRetrig)->InitEnum("LFO Retrig", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamLfoMidi)->InitEnum("LFO MIDI", 0, 2, "", 0, "", "Off", "On");

  // SWITCHES EFFECTS
  GetParam(kParamFlanger)->InitEnum("Flanger", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamDelayUnitL)->InitEnum("Delay BPM L", 0, 2, "", 0, "", "ms", "BPM");
  GetParam(kParamDelayUnitR)->InitEnum("Delay BPM R", 0, 2, "", 0, "", "ms", "BPM");
  GetParam(kParamDelayCross)->InitEnum("Delay Cross", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamEffectBypass)->InitEnum("Effect Bypass", 0, 2, "", 0, "", "Off", "On");

  GetParam(kParamMidiBpm)->InitInt("MIDI BPM", 72, 72, 199);

  GetParam(kParamKeyboardOctave)->InitEnum("Keyb Oct", 3, 7, "", 0, "", "-3","-2","-1","0","+1","+2","+3");
  GetParam(kParamProgram)->InitInt("Program", 0, 0, 99, "", 0, "");
  GetParam(kParamMidiActive)->InitBool("MIDI Active", true, "");

  GetParam(kParamPitchWheel)->InitDouble("Pitch Wheel", 0, 0, 1, 0.001);

    paramToCC.fill(-1);

    paramToCC[kParamMasterVolume] = 7;
    paramToCC[kParamSynthMic] = 93;
    paramToCC[kParamBoost] = 105;
    paramToCC[kParamFilterEnv                  ]=63;
    paramToCC[kParamOSCB                       ]=58;
    paramToCC[kParamOSCAFreq                   ]=95;
    paramToCC[kParamOSCAPW                     ]=98;
    paramToCC[kParamOSCBFreq                   ]=81;
    paramToCC[kParamOSCBFine                   ]=82;
    paramToCC[kParamOSCBPW                     ]=27;
    paramToCC[kParamSourceMix                  ]=108;
    paramToCC[kParamGlide                      ]=5;
    paramToCC[kParamLFOFreq                    ]=72;
    paramToCC[kParamMixOSCA                    ]=25;
    paramToCC[kParamMixOSCB                    ]=26;
    paramToCC[kParamMixNoise                   ]=33;
    paramToCC[kParamMasterTune                 ]=21;
    paramToCC[kParamVCFCutoff                  ]=74;
    paramToCC[kParamVCFResonance               ]=71;
    paramToCC[kParamVCFEnvAmt                  ]=73;
    paramToCC[kParamVCFKybAmt                  ]=39;
    paramToCC[kParamVCFAttack                  ]=17;
    paramToCC[kParamVCFDecay                   ]=18;
    paramToCC[kParamVCFSustain                 ]=19;
    paramToCC[kParamVCFRelease                 ]=20;
    paramToCC[kParamVCFVelocity                ]=42;
    paramToCC[kParamVCAAttack                  ]=13;
    paramToCC[kParamVCADecay                   ]=14;
    paramToCC[kParamVCASustain                 ]=15;
    paramToCC[kParamVCARelease                 ]=16;
    paramToCC[kParamVCAVelocity                ]=12;
    paramToCC[kParamVolume                     ]=11;

    paramToCC[kParamMWIntensity                ]=56;
    paramToCC[kParamMWOffset                   ]=57;
    paramToCC[kParamMWBendRange                ]=24;
    paramToCC[kParamVoices                     ] = 2;
    paramToCC[kParamDetune                     ]=3;
    paramToCC[kParamATPitch                    ]=23;
    paramToCC[kParamATPw                       ]=34;
    paramToCC[kParamATFIlter                   ]=50;
    paramToCC[kParamATAmp                      ]=51;
    paramToCC[kParamATMWAmt                    ]=35;
    paramToCC[kParamATLfoFreq                  ]=48;
    paramToCC[kParamTimeVelVCFAttack           ]=113;
    paramToCC[kParamTimeVelVCFDecrel           ]=114;
    paramToCC[kParamTimeVelVCAAttack           ]=117;
    paramToCC[kParamTimeVelVCADecrel           ]=116;
    paramToCC[kParamLFOPhase                   ]=9;

    paramToCC[kParamChorusRate                 ]=71;
    paramToCC[kParamChorusPhase                ]=72;
    paramToCC[kParamChorusDepth                ]=73;
    paramToCC[kParamChorusFB                   ]=74;
    paramToCC[kParamChorusMix                  ]=91;
    paramToCC[kParamDelayTimeL                 ]=81;
    paramToCC[kParamDelayTimeR                 ]=91;
    paramToCC[kParamDelayFBL                   ]=119;
    paramToCC[kParamDelayFBR                   ]=119;
    paramToCC[kParamDelayHidampL               ]=84;
    paramToCC[kParamDelayHidampR               ]=94;
    paramToCC[kParamDelayLevelL                ]=85;
    paramToCC[kParamDelayLevelR                ]=95;
    paramToCC[kParamDelayMix                   ]=10;
    paramToCC[kParamUnison                     ] = 69;
   
    paramToCC[kParamPolymodFRQA                ]=75;
    paramToCC[kParamPolymodFRQB                ]=76;
    paramToCC[kParamPolymodPWA                 ]=77;
    paramToCC[kParamPolymodPWB                 ]=78;
    paramToCC[kParamPolymodFilter              ]=79;
    paramToCC[kParamWheelmodFRQA               ]=102;
    paramToCC[kParamWheelmodFRQB               ]=103;
    paramToCC[kParamWheelmodPWA                ]=104;
    paramToCC[kParamWheelmodPWB                ]=105;
    paramToCC[kParamWheelmodFilter             ]=106;
    paramToCC[kParamOSCASaw                    ]=96;
    paramToCC[kParamOSCAPulse                  ]=97;
    paramToCC[kParamOSCASync                   ]=99;
    paramToCC[kParamOSCBSaw                    ]=83;
    paramToCC[kParamOSCBPulse                  ]=22;
    paramToCC[kParamOSCBTri                    ]=84;
    paramToCC[kParamOSCBLowFreq                ]=28;
    paramToCC[kParamOSCBKeyb                   ]=29;
    paramToCC[kParamLFOSaw                     ]=87;
    paramToCC[kParamLFOTri                     ]=88;
    paramToCC[kParamLFOPulse                   ]=89;
    paramToCC[kParamAdr                        ]=59;
    paramToCC[kParamRelease                    ]=49;
    paramToCC[kParamKybRetrig                  ]=60;
    paramToCC[kParamKybLowNote                 ]=61;
    paramToCC[kParamKybSingle                  ]=68;
    paramToCC[kParamAtFreqA                    ]=30;
    paramToCC[kParamAtFreqB                    ]=31;
    paramToCC[kParamAtPwA                      ]=37;
    paramToCC[kParamAtPwB                      ]=38;
    paramToCC[kParamLfoRetrig                  ]=8;
    paramToCC[kParamLfoMidi                    ]=110;
    paramToCC[kParamFlanger                    ]=75;
    paramToCC[kParamDelayBpmL                  ]=82;
    paramToCC[kParamDelayBpmR                  ]=92;
    paramToCC[kParamDelayUnitL                 ] = 86;
    paramToCC[kParamDelayUnitR                 ] = 96;
    paramToCC[kParamDelayCross                 ]=90;
    paramToCC[kParamEffectBypass               ]=98;
    paramToCC[kParamMidiBpm                    ] = 97;
    paramToCC[kParamPitchWheel                 ] = 1;

    paramToMsgType.fill(-1); // 0: CC, 1:Aftertouch

    paramToMsgType[kParamMasterVolume] = 0;
    paramToMsgType[kParamSynthMic] = 0;
    paramToMsgType[kParamBoost] = 1;
    paramToMsgType[kParamFilterEnv                  ]=0;
    paramToMsgType[kParamOSCB                       ]=0;
    paramToMsgType[kParamOSCAFreq                   ]=0;
    paramToMsgType[kParamOSCAPW                     ]=0;
    paramToMsgType[kParamOSCBFreq                   ]=0;
    paramToMsgType[kParamOSCBFine                   ]=0;
    paramToMsgType[kParamOSCBPW                     ]=0;
    paramToMsgType[kParamSourceMix                  ]=0;
    paramToMsgType[kParamGlide                      ]=0;
    paramToMsgType[kParamLFOFreq                    ]=0;
    paramToMsgType[kParamMixOSCA                    ]=0;
    paramToMsgType[kParamMixOSCB                    ]=0;
    paramToMsgType[kParamMixNoise                   ]=0;
    paramToMsgType[kParamMasterTune                 ]=0;
    paramToMsgType[kParamVCFCutoff                  ]=0;
    paramToMsgType[kParamVCFResonance               ]=0;
    paramToMsgType[kParamVCFEnvAmt                  ]=0;
    paramToMsgType[kParamVCFKybAmt                  ]=0;
    paramToMsgType[kParamVCFAttack                  ]=0;
    paramToMsgType[kParamVCFDecay                   ]=0;
    paramToMsgType[kParamVCFSustain                 ]=0;
    paramToMsgType[kParamVCFRelease                 ]=0;
    paramToMsgType[kParamVCFVelocity                ]=0;
    paramToMsgType[kParamVCAAttack                  ]=0;
    paramToMsgType[kParamVCADecay                   ]=0;
    paramToMsgType[kParamVCASustain                 ]=0;
    paramToMsgType[kParamVCARelease                 ]=0;
    paramToMsgType[kParamVCAVelocity                ]=0;
    paramToMsgType[kParamVolume                     ]=0;
                                                
    paramToMsgType[kParamMWIntensity                ]=0;
    paramToMsgType[kParamMWOffset                   ]=0;
    paramToMsgType[kParamMWBendRange                ]=0;
    paramToMsgType[kParamVoices                     ]= 0;
    paramToMsgType[kParamDetune                     ]=0;
    paramToMsgType[kParamATPitch                    ]=0;
    paramToMsgType[kParamATPw                       ]=0;
    paramToMsgType[kParamATFIlter                   ]=0;
    paramToMsgType[kParamATAmp                      ]=0;
    paramToMsgType[kParamATMWAmt                    ]=0;
    paramToMsgType[kParamATLfoFreq                  ]=0;
    paramToMsgType[kParamTimeVelVCFAttack           ]=0;
    paramToMsgType[kParamTimeVelVCFDecrel           ]=0;
    paramToMsgType[kParamTimeVelVCAAttack           ]=0;
    paramToMsgType[kParamTimeVelVCADecrel           ]=0;
    paramToMsgType[kParamLFOPhase                   ]=0;
                                                     
    paramToMsgType[kParamChorusRate                 ]=1;
    paramToMsgType[kParamChorusPhase                ]=1;
    paramToMsgType[kParamChorusDepth                ]=1;
    paramToMsgType[kParamChorusFB                   ]=1;
    paramToMsgType[kParamChorusMix                  ]=0;
    paramToMsgType[kParamDelayTimeL                 ]=1;
    paramToMsgType[kParamDelayTimeR                 ]=1;
    paramToMsgType[kParamDelayFBL                   ]=0;
    paramToMsgType[kParamDelayFBR                   ]=0;
    paramToMsgType[kParamDelayHidampL               ]=1;
    paramToMsgType[kParamDelayHidampR               ]=1;
    paramToMsgType[kParamDelayLevelL                ]=1;
    paramToMsgType[kParamDelayLevelR                ]=1;
    paramToMsgType[kParamDelayMix                   ]=0;
    paramToMsgType[kParamUnison                     ] =0;
                                                     
    paramToMsgType[kParamPolymodFRQA                ]=0;
    paramToMsgType[kParamPolymodFRQB                ]=0;
    paramToMsgType[kParamPolymodPWA                 ]=0;
    paramToMsgType[kParamPolymodPWB                 ]=0;
    paramToMsgType[kParamPolymodFilter              ]=0;
    paramToMsgType[kParamWheelmodFRQA               ]=0;
    paramToMsgType[kParamWheelmodFRQB               ]=0;
    paramToMsgType[kParamWheelmodPWA                ]=0;
    paramToMsgType[kParamWheelmodPWB                ]=0;
    paramToMsgType[kParamWheelmodFilter             ]=0;
    paramToMsgType[kParamOSCASaw                    ]=0;
    paramToMsgType[kParamOSCAPulse                  ]=0;
    paramToMsgType[kParamOSCASync                   ]=0;
    paramToMsgType[kParamOSCBSaw                    ]=0;
    paramToMsgType[kParamOSCBPulse                  ]=0;
    paramToMsgType[kParamOSCBTri                    ]=0;
    paramToMsgType[kParamOSCBLowFreq                ]=0;
    paramToMsgType[kParamOSCBKeyb                   ]=0;
    paramToMsgType[kParamLFOSaw                     ]=0;
    paramToMsgType[kParamLFOTri                     ]=0;
    paramToMsgType[kParamLFOPulse                   ]=0;
    paramToMsgType[kParamAdr                        ]=0;
    paramToMsgType[kParamRelease                    ]=0;
    paramToMsgType[kParamKybRetrig                  ]=0;
    paramToMsgType[kParamKybLowNote                 ]=0;
    paramToMsgType[kParamKybSingle                  ]=0;
    paramToMsgType[kParamAtFreqA                    ]=0;
    paramToMsgType[kParamAtFreqB                    ]=0;
    paramToMsgType[kParamAtPwA                      ]=0;
    paramToMsgType[kParamAtPwB                      ]=0;
    paramToMsgType[kParamLfoRetrig                  ]=0;
    paramToMsgType[kParamLfoMidi                    ]=0;
    paramToMsgType[kParamFlanger                    ]=1;
    paramToMsgType[kParamDelayBpmL                  ]=1;
    paramToMsgType[kParamDelayBpmR                  ]=1;
    paramToMsgType[kParamDelayUnitL                 ]= 1;
    paramToMsgType[kParamDelayUnitR                 ]= 1;
    paramToMsgType[kParamDelayCross                 ]=1;
    paramToMsgType[kParamEffectBypass               ] = 1;
    paramToMsgType[kParamMidiBpm                    ]= 1;
    paramToMsgType[kParamPitchWheel                 ]= 0;

  
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

    IControl* pBG = new IPanelControl(IRECT(0, 0, HSM_W, HSK_H), IColor(255, 39, 39, 39));
    pGraphics->AttachControl(pBG);
    
    const IRECT controls = b.GetGridCell(1, 2, 2);

    IBitmap bitmap;

    bitmap = pGraphics->LoadBitmap(PNGBACK_FN);
    IControl* backCtrl = new IBitmapControl(0, 0, bitmap, kNoParameter);
    pGraphics->AttachControl(backCtrl, -1, "");

    bitmap = pGraphics->LoadBitmap(PNGBASE_FN);
    IControl* baseCtrl = new IBitmapControl(0,HEADER_H, bitmap, kNoParameter);
    pGraphics->AttachControl(baseCtrl, -1, "");

    bitmap = pGraphics->LoadBitmap(PNGPANELMAIN_FN);
    IControl* mainPanelCtrl = new IBitmapControl(16,HEADER_H, bitmap, kNoParameter);
    pGraphics->AttachControl(mainPanelCtrl, -1, "main");
    
    bitmap = pGraphics->LoadBitmap(PNGPANELADD_FN);
    IControl* addPanelCtrl = new IBitmapControl(16, HEADER_H, bitmap, kNoParameter);
    pGraphics->AttachControl(addPanelCtrl, -1, "add");
    if (strcmp(addPanelCtrl->GetGroup(), "add") == 0) addPanelCtrl->Hide(true);

    bitmap = pGraphics->LoadBitmap(PNGPANELEFFECTS_FN);
    IControl* effectsPanelCtrl = new IBitmapControl(16, HEADER_H, bitmap, kNoParameter);
    pGraphics->AttachControl(effectsPanelCtrl, -1, "effects");
    if (strcmp(effectsPanelCtrl->GetGroup(), "effects") == 0) effectsPanelCtrl->Hide(true);

    //bitmap = pGraphics->LoadBitmap(PNGKEYBACK_FN);
    //IControl* keybackCtrl = new IBitmapControl(0, HS_H, bitmap, kNoParameter);
    //pGraphics->AttachControl(keybackCtrl, -1, "keyboard");
 
    IRECT keybRect = IRECT(MARGIN_W, HS_H + MARGIN_H, PLUG_WIDTH - MARGIN_W, HS_H + MARGIN_H + KEYBOARD_H);
    keybCtrl = new IVKeyboardControl(keybRect.FracRectHorizontal(0.85), 36, 91);
    pGraphics->AttachControl(keybCtrl, kCtrlTagKeyboard, "keyboard");

    pGraphics->AttachControl(new ICaptionControl(IRECT(889, 515, 919, 535), kParamKeyboardOctave, DEFAULT_TEXT, COLOR_MID_GRAY, true), -1, "keyboard");

    IVButtonControl* buttCtrl = new IVButtonControl(IRECT(867, 556, 952, 586), [&](IControl*) {
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
    
    // SWITCHES MAIN 
    bitmap = pGraphics->LoadBitmap(PNGSWITCH_FN, 2);

    int offX = 0;
    int offY = 0;
    pGraphics->AttachControl(new IBSwitchControlMidi(604, 411, bitmap, kParamBoost), -1, "");
    pGraphics->AttachControl(new IBSwitchControlMidi(33, 204, bitmap, kParamPolymodFRQA), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(61, 204, bitmap, kParamPolymodFRQB), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(89, 204, bitmap, kParamPolymodPWA), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(117, 204, bitmap, kParamPolymodPWB), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(145, 204, bitmap, kParamPolymodFilter), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(33, 317, bitmap, kParamWheelmodFRQA), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(61, 317, bitmap, kParamWheelmodFRQB), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(89, 317, bitmap, kParamWheelmodPWA), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(117, 317, bitmap, kParamWheelmodPWB), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(145, 317, bitmap, kParamWheelmodFilter), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(262, 92, bitmap, kParamOSCASaw), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(292, 92, bitmap, kParamOSCAPulse), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(393, 92, bitmap, kParamOSCASync), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(335, 202, bitmap, kParamOSCBSaw), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(363, 202, bitmap, kParamOSCBTri), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(391, 202, bitmap, kParamOSCBPulse), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(493, 202, bitmap, kParamOSCBLowFreq), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(522, 202, bitmap, kParamOSCBKeyb), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(468, 313, bitmap, kParamLFOSaw), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(496, 313, bitmap, kParamLFOTri), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(524, 313, bitmap, kParamLFOPulse), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(568, 313, bitmap, kParamAdr), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(605, 313, bitmap, kParamRelease), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(354, 313, bitmap, kParamUnison), -1, "main");

    // SWITCHES ADD
    pGraphics->AttachControl(new IBSwitchControlMidi(offX+41, offY+108, bitmap, kParamKybRetrig), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(offX+86, offY+108, bitmap, kParamKybLowNote), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(offX+132, offY+108, bitmap, kParamKybSingle), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(343, 221, bitmap, kParamAtFreqA), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(377, 221, bitmap, kParamAtFreqB), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(479, 221, bitmap, kParamAtPwA), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(513, 221, bitmap, kParamAtPwB), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(822, 221, bitmap, kParamLfoRetrig), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(933, 221, bitmap, kParamLfoMidi), -1, "add");

    // SWITCHES EFFECTS
    pGraphics->AttachControl(new IBSwitchControlMidi(53, 85, bitmap, kParamFlanger), -1, "effects");
    pGraphics->AttachControl(new IBSwitchControlMidi(438, 85, bitmap, kParamDelayUnitL), -1, "effects");
    pGraphics->AttachControl(new IBSwitchControlMidi(438, 169, bitmap, kParamDelayUnitR), -1, "effects");
    pGraphics->AttachControl(new IBSwitchControlMidi(484, 169, bitmap, kParamDelayCross), -1, "effects");
    bitmap = pGraphics->LoadBitmap(PNGSWITCHBYPASS_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(388, 256, bitmap, kParamEffectBypass), -1, "effects");

    // KNOBS MAIN 
    bitmap = pGraphics->LoadBitmap(PNGKNOB1_FN, 65, true);

    pGraphics->AttachControl(new IBKnobControlMidi(412, 407, bitmap, kParamMasterVolume), -1, "");
    pGraphics->AttachControl(new IBKnobControlMidi(503, 407, bitmap, kParamSynthMic), -1, "");

    pGraphics->AttachControl(new IBKnobControlMidi(47, 86, bitmap, kParamFilterEnv), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(124, 86, bitmap, kParamOSCB), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(208, 87, bitmap, kParamOSCAFreq), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(338, 85, bitmap, kParamOSCAPW), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(209, 196, bitmap, kParamOSCBFreq), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(275, 197, bitmap, kParamOSCBFine), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(431, 197, bitmap, kParamOSCBPW), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(209, 306, bitmap, kParamSourceMix), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(299, 306, bitmap, kParamGlide), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(411, 305, bitmap, kParamLFOFreq), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(452, 85, bitmap, kParamMixOSCA), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(518, 85, bitmap, kParamMixOSCB), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(583, 85, bitmap, kParamMixNoise), -1, "main");
    bitmap = pGraphics->LoadBitmap(PNGKNOB2_FN, 65, true);
    pGraphics->AttachControl(new IBKnobControlMidi(582, 198, bitmap, kParamMasterTune), -1, "main");
    bitmap = pGraphics->LoadBitmap(PNGKNOB1_FN, 65, true);
    pGraphics->AttachControl(new IBKnobControlMidi(662, 85, bitmap, kParamVCFCutoff), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(725, 85, bitmap, kParamVCFResonance), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(789, 85, bitmap, kParamVCFEnvAmt), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(853, 85, bitmap, kParamVCFKybAmt), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(662, 196, bitmap, kParamVCFAttack), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(725, 196, bitmap, kParamVCFDecay), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(789, 196, bitmap, kParamVCFSustain), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(853, 196, bitmap, kParamVCFRelease), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(916, 196, bitmap, kParamVCFVelocity), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(662, 306, bitmap, kParamVCAAttack), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(725, 306, bitmap, kParamVCADecay), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(789, 306, bitmap, kParamVCASustain), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(853, 306, bitmap, kParamVCARelease), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(916, 306, bitmap, kParamVCAVelocity), -1, "main");
    bitmap = pGraphics->LoadBitmap(PNGKNOB2_FN, 65, true);
    pGraphics->AttachControl(new IBKnobControlMidi(920, 85, bitmap, kParamVolume), -1, "main");

    bitmap = pGraphics->LoadBitmap(PNGKNOB1_FN, 65, true);

    // KNOBS ADD
    pGraphics->AttachControl(new IBKnobControlMidi(47, 219, bitmap, kParamMWIntensity), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(116, 219, bitmap, kParamMWOffset), -1, "add");
    std::function<double(double)> mappingFunc2 = [](double midiVal) {return midiVal * 127. / 24.; };
    pGraphics->AttachControl(new IBKnobControlMidi(186, 219, bitmap, kParamMWBendRange, mappingFunc2), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(215, 86, bitmap, kParamVoices), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(333, 86, bitmap, kParamDetune), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(293, 218, bitmap, kParamATPitch), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(428, 218, bitmap, kParamATPw), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(556, 218, bitmap, kParamATFIlter), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(621, 218, bitmap, kParamATAmp), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(686, 218, bitmap, kParamATMWAmt), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(751, 216, bitmap, kParamATLfoFreq), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(428, 84, bitmap, kParamTimeVelVCFAttack), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(522, 84, bitmap, kParamTimeVelVCFDecrel), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(614, 84, bitmap, kParamTimeVelVCAAttack), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(708, 84, bitmap, kParamTimeVelVCADecrel), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(872, 216, bitmap, kParamLFOPhase), -1, "add");

    // KNOBS EFFECTS
    pGraphics->AttachControl(new IBKnobControlMidi(118, 82, bitmap, kParamChorusRate), -1, "effects");
    pGraphics->AttachControl(new IBKnobControlMidi(118, 160, bitmap, kParamChorusPhase), -1, "effects");
    pGraphics->AttachControl(new IBKnobControlMidi(257, 82, bitmap, kParamChorusDepth), -1, "effects");
    pGraphics->AttachControl(new IBKnobControlMidi(257, 160, bitmap, kParamChorusFB), -1, "effects");
    pGraphics->AttachControl(new IBKnobControlMidi(335, 115, bitmap, kParamChorusMix), -1, "effects");
    pGraphics->AttachControl(new IBKnobControlMidi(538, 82, bitmap, kParamDelayTimeL), kCtrlTagDelayTimeLMS, "effects");
    pGraphics->AttachControl(new IBKnobControlMidi(538, 163, bitmap, kParamDelayTimeR), kCtrlTagDelayTimeRMS, "effects");
    pGraphics->AttachControl(new IBKnobControlMidi(688, 82, bitmap, kParamDelayFBL), -1, "effects");
    pGraphics->AttachControl(new IBKnobControlMidi(688, 160, bitmap, kParamDelayFBL), -1, "effects"); // coupled with Left FB
    pGraphics->AttachControl(new IBKnobControlMidi(757, 82, bitmap, kParamDelayHidampL), -1, "effects");
    pGraphics->AttachControl(new IBKnobControlMidi(757, 160, bitmap, kParamDelayHidampR), -1, "effects");
    pGraphics->AttachControl(new IBKnobControlMidi(827, 82, bitmap, kParamDelayLevelL), -1, "effects");
    pGraphics->AttachControl(new IBKnobControlMidi(825, 160, bitmap, kParamDelayLevelR), -1, "effects");
    pGraphics->AttachControl(new IBKnobControlMidi(904, 116, bitmap, kParamDelayMix), -1, "effects");

  


    bitmap = pGraphics->LoadBitmap(PNGMIDIACTIVE_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(199, 7, bitmap, kParamMidiActive), -1, "header");

    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(269, 94, 299, 109), kParamVoices, DEFAULT_TEXT, COLOR_LIGHT_GRAY, true), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(239, 227, 261, 242), kParamMWBendRange, DEFAULT_TEXT, COLOR_LIGHT_GRAY, true), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(927, 265, 957, 280), kParamLFOPhase, DEFAULT_TEXT, COLOR_LIGHT_GRAY, true), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(851, 106, 911, 124), kParamMidiBpm, DEFAULT_TEXT, COLOR_LIGHT_GRAY, true), -1, "add");

    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(178, 91, 217, 108), kParamChorusRate, DEFAULT_TEXT, COLOR_LIGHT_GRAY, true), -1, "effects");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(178+3, 171, 217-3, 188), kParamChorusPhase, DEFAULT_TEXT, COLOR_LIGHT_GRAY, true), -1, "effects");

    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(600, 93, 649, 110), kParamDelayTimeL, DEFAULT_TEXT, COLOR_LIGHT_GRAY, true), kCtrlTagDelayTimeLMSCaption, "effects");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(600, 171, 649, 188), kParamDelayTimeR, DEFAULT_TEXT, COLOR_LIGHT_GRAY, true), kCtrlTagDelayTimeRMSCaption, "effects");

    bitmap = pGraphics->LoadBitmap(PNGHIDE_FN);
    IControl* hideCtrl = new IBitmapControl(505, 63, bitmap, kNoParameter);
    pGraphics->AttachControl(hideCtrl, kCtrlTagHideL, "effects");
    hideCtrl = new IBitmapControl(515, 140, bitmap, kNoParameter);
    pGraphics->AttachControl(hideCtrl, kCtrlTagHideR, "effects");

    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(530, 94, 579, 111), kParamDelayBpmL, DEFAULT_TEXT, COLOR_LIGHT_GRAY, true), kCtrlTagDelayTimeLBPM, "effects");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(530, 172, 579, 189), kParamDelayBpmR, DEFAULT_TEXT, COLOR_LIGHT_GRAY, true), kCtrlTagDelayTimeRBPM, "effects");

    // Program Change
    captionCtrl = new ICaptionControl(IRECT(1059, 10, 1100, 30), kParamProgram, DEFAULT_TEXT, COLOR_WHITE, true);
    pGraphics->AttachControl(captionCtrl, -1, "header");

    bitmap = pGraphics->LoadBitmap(PNGPLUS_FN);
    pGraphics->AttachControl(new IBButtonControl(1100,10, bitmap, [&](IControl*) {
      captionCtrl->SetValueFromUserInput(GetParam(kParamProgram)->ToNormalized(GetParam(kParamProgram)->FromNormalized(captionCtrl->GetValue())+1));
    }
    ), -1, "header");

    bitmap = pGraphics->LoadBitmap(PNGMINUS_FN);
    pGraphics->AttachControl(new IBButtonControl(1040, 10, bitmap, [&](IControl*) {
      captionCtrl->SetValueFromUserInput(GetParam(kParamProgram)->ToNormalized(GetParam(kParamProgram)->FromNormalized(captionCtrl->GetValue()) - 1));
    }
    ), -1, "header");

    // MAIN

    // Kein Pitchwheel sondern Modwheel
    bitmap = pGraphics->LoadBitmap(PNGPITCHWHEEL_FN, 23, true);
    pGraphics->AttachControl(new IBKnobControlMidi(32, 392, bitmap, kParamPitchWheel), -1, "");

    auto windowFunc = [](IControl* pCaller) {
      pCaller->SetValue(1.);
      if (pCaller->GetUI()) {

        if (pCaller->GetTag() != kCtrlTagMain) pCaller->GetUI()->GetControlWithTag(kCtrlTagMain)->SetValueFromUserInput(0);
        if (pCaller->GetTag() != kCtrlTagAdd) pCaller->GetUI()->GetControlWithTag(kCtrlTagAdd)->SetValueFromUserInput(0);
        if (pCaller->GetTag() != kCtrlTagEffects) pCaller->GetUI()->GetControlWithTag(kCtrlTagEffects)->SetValueFromUserInput(0);

        pCaller->GetUI()->ForControlInGroup("main", [&](IControl& control) {if (pCaller->GetTag() == kCtrlTagMain) control.Hide(false); else control.Hide(true); });
        pCaller->GetUI()->ForControlInGroup("add", [&](IControl& control) {if (pCaller->GetTag() == kCtrlTagAdd) control.Hide(false); else control.Hide(true); });
        pCaller->GetUI()->ForControlInGroup("effects", [&](IControl& control) {if (pCaller->GetTag() == kCtrlTagEffects) control.Hide(false); else control.Hide(true); });

 
          if (pCaller->GetUI()->GetControlWithTag(kCtrlTagEffects)->GetValue() == 1) {
            if (pCaller->GetDelegate()->GetParam(kParamDelayUnitL)->Value() == 0) {
              pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(true);
              pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMS)->Hide(false);
              pCaller->GetUI()->GetControlWithTag(kCtrlTagHideL)->Hide(true);
              pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMSCaption)->Hide(false);

            }
            else {
              pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(false);
              pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMSCaption)->Hide(true);
              pCaller->GetUI()->GetControlWithTag(kCtrlTagHideL)->Hide(false);
              pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMS)->Hide(true);
            }
          }

          if (pCaller->GetUI()->GetControlWithTag(kCtrlTagEffects)->GetValue() == 1) {
            if (pCaller->GetDelegate()->GetParam(kParamDelayUnitR)->Value() == 0) {
               pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(true);
               pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMS)->Hide(false);
               pCaller->GetUI()->GetControlWithTag(kCtrlTagHideR)->Hide(true);
               pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMSCaption)->Hide(false);
            }
            else {
               pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(false);
               pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMSCaption)->Hide(true);
               pCaller->GetUI()->GetControlWithTag(kCtrlTagHideR)->Hide(false);
               pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMS)->Hide(true);
            }
          }
        
      }
    };

    bitmap = pGraphics->LoadBitmap(PNGMAINS_FN, 2);
    IBSwitchControlFunc *mainCtrl = new IBSwitchControlFunc(74, 395, bitmap, windowFunc, kNoParameter);
    pGraphics->AttachControl(mainCtrl, kCtrlTagMain);
    mainCtrl->SetValue(1);
    bitmap = pGraphics->LoadBitmap(PNGADDS_FN, 2);
    IBSwitchControlFunc *addCtrl = new IBSwitchControlFunc(74, 417, bitmap, windowFunc, kNoParameter);
    pGraphics->AttachControl(addCtrl, kCtrlTagAdd);
    bitmap = pGraphics->LoadBitmap(PNGEFFECTSS_FN, 2);
    IBSwitchControlFunc *effectsCtrl = new IBSwitchControlFunc(74, 438, bitmap, windowFunc, kNoParameter);
    pGraphics->AttachControl(effectsCtrl, kCtrlTagEffects);


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

    mPresetMenu = new FileBrowser(IRECT(992+10, 44, 1188-10, 68));
    pGraphics->AttachControl(mPresetMenu, kCtrlTagPresetMenu);

    bitmap = pGraphics->LoadBitmap(PNGMIDIMONITOR_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlFunc(108, 6, bitmap, resizeFunc, kNoParameter), kCtrlTagMidiMonHide);
    bitmap = pGraphics->LoadBitmap(PNGKEYB_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlFunc(22, 6, bitmap, resizeFunc, kNoParameter), kCtrlTagKeybHide);

    mMidiLogger = new MidiLoggerControl(IRECT(HS_W + MARGIN_W, MARGIN_H + MIDILOG_H, HS_W + MIDIPRESET_W - MARGIN_W, HS_H-MARGIN_H), "", "", IText(12, COLOR_BLACK, NULL, EAlign::Near), COLOR_WHITE);
    pGraphics->AttachControl(mMidiLogger, kCtrlTagMidiLogger, "midiMonitor");

    IVButtonControl* clearCtrl = new IVButtonControl(IRECT(994, 211, 1079, 241), [&](IControl*) {
      mMidiLogger->Clear();
    },

      "Clear", IVStyle(DEFAULT_SHOW_LABEL, DEFAULT_SHOW_VALUE, {}, IText(12)));

    buttCtrl->SetAnimation(DefaultAnimationFunc);
    pGraphics->AttachControl(clearCtrl, kCtrlTagClear, "midiMonitor");
    
    if (GetUI()) {
      for (auto k = 0; k < GetUI()->NControls(); k++) {
        if (strcmp(GetUI()->GetControl(k)->GetGroup(), "add") == 0) {
          GetUI()->GetControl(k)->Hide(true);
        }
        if (strcmp(GetUI()->GetControl(k)->GetGroup(), "effects") == 0) {
          GetUI()->GetControl(k)->Hide(true);
        }
      }

      GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(true);
      GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMS)->Hide(true);
      GetUI()->GetControlWithTag(kCtrlTagHideL)->Hide(true);
      GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMSCaption)->Hide(true);

      GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(true);
      GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMS)->Hide(true);
      GetUI()->GetControlWithTag(kCtrlTagHideR)->Hide(true);
      GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMSCaption)->Hide(true);
    }
  };
  
#endif
}

#if IPLUG_DSP
void Pro12::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
  const int nChans = NOutChansConnected();
  
  for (auto s = 0; s < nFrames; s++) {
    for (auto c = 0; c < nChans; c++) {
      outputs[c][s] = 0.;
    }
  }
}

void Pro12::OnIdle()
{
  mMidiLoggerSender.TransmitData(*this);
}

void Pro12::OnReset()
{
}

void Pro12::OnUIOpen() {

  SendCurrentParamValuesFromDelegate();

  // Presetname
  //mPresetMenu->restorePresetPath(mCurrentPresetPath.Get());
}

bool Pro12::OnMessage(int messageTag, int controlTag, int dataSize, const void *pData) {

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
void Pro12::ProcessMidiMsg(const IMidiMsg& msg)
{
  TRACE;

  if (mMidiActive) {

    if (msg.mOffset == -2) { // From UI , verhindert dummerweise keyboardmidi

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

void Pro12::OnParamChange(int paramIdx)
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


    // Controls get value direct, not 0-127
    switch (paramIdx) {
    case kParamDelayBpmL:
    case kParamDelayBpmR:
    case kParamMWBendRange:
    case kParamVoices:
      msg.mData2 = GetParam(paramIdx)->Value();
      break;
    case kParamMidiBpm:
      msg.mData2 = GetParam(paramIdx)->Value()-72;
      break;
    }


    //if(paramIdx == kParamBendRange) msg.mData2 = GetParam(paramIdx)->Value();

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

  case kParamDelayUnitL:
    if (GetUI()) {
      if (GetUI()->GetControlWithTag(kCtrlTagEffects)->GetValue() == 1) {
        if (GetParam(paramIdx)->Value() == 0) {
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(true);
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMS)->Hide(false);
          GetUI()->GetControlWithTag(kCtrlTagHideL)->Hide(true);
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMSCaption)->Hide(false);

        }
        else {
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(false);
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMSCaption)->Hide(true);
          GetUI()->GetControlWithTag(kCtrlTagHideL)->Hide(false);
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMS)->Hide(true);
        }
      }
    }
    break;
  case kParamDelayUnitR:
    if (GetUI()) {
      if (GetUI()->GetControlWithTag(kCtrlTagEffects)->GetValue() == 1) {
        if (GetParam(paramIdx)->Value() == 0) {
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(true);
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMS)->Hide(false);
          GetUI()->GetControlWithTag(kCtrlTagHideR)->Hide(true);
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMSCaption)->Hide(false);
        }
        else {
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(false);
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMSCaption)->Hide(true);
          GetUI()->GetControlWithTag(kCtrlTagHideR)->Hide(false);
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMS)->Hide(true);
        }
      }
    }
    break;
      
    default:
      break;
  }
}

bool Pro12::SerializeState(IByteChunk& chunk) const {

  TRACE;

 

  // Presetname
  WDL_String s;
  s.Set(mCurrentPresetPath.Get());
  chunk.PutStr(s.Get());

  return SerializeParams(chunk);
}

// this over-ridden method is called when the host is trying to load the plug-in state and you need to unpack the data into your algorithm
// HIER KÖNNEN KEINE CONTROLS GEUPDATED WERDEN; DA MGRAPHICS NOCH NICHT EXISTIERT!!!!
int Pro12::UnserializeState(const IByteChunk& chunk, int startPos) {

  TRACE;

 
  int pos;
  // Presetname
  WDL_String str;
  pos = chunk.GetStr(str, pos);
  mCurrentPresetPath.Set(str.Get());

  return UnserializeParams(chunk, pos);
}
#endif
