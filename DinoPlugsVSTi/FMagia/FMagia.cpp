#include "FMagia.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"
#include "json.hpp"
#include <fstream>

FMagia::FMagia(IPlugInstanceInfo instanceInfo)
: IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo)
{

  presetname[0 ].Set("00: Windows");
  presetname[1].Set("01: Fynthesizer");
  presetname[2].Set("02: Spring Bass");
  presetname[3].Set("03: Sliter Attack");
  presetname[4].Set("04: Wigly Clav");
  presetname[5].Set("05: Indesicive");
  presetname[6].Set("06: Emotional Numbers");
  presetname[7].Set("07: Jungle");
  presetname[8].Set("08: Tubar");
  presetname[9].Set("09: Chub");
  presetname[10].Set("10: Forks");
  presetname[11].Set("11: Falling Stars");
  presetname[12].Set("12: Oxy");
  presetname[13].Set("13: Synthphony");
  presetname[14].Set("14: Afrika");
  presetname[15].Set("15: Big Ben");
  presetname[16].Set("16: Music Box");
  presetname[17].Set("17: FMagia");
  presetname[18].Set("18: Soft Horns");
  presetname[19].Set("19: Liquid Sine");
  presetname[20].Set("20: Hello Lead");
  presetname[21].Set("21: Fluteria");
  presetname[22].Set("22: Feedback");
  presetname[23].Set("23: Non Shaved");
  presetname[24].Set("24: Maleter");
  presetname[25].Set("25: Spit Lead");
  presetname[26].Set("26: Singulator");
  presetname[27].Set("27: Clarinet");
  presetname[28].Set("28: Serpant");
  presetname[29].Set("29: BoK p");
  presetname[30].Set("30: DigELP");
  presetname[31].Set("31: Warm Pad");
  presetname[32].Set("32: Pipe Dreams");
  presetname[33].Set("33: Emerger");
  presetname[34].Set("34: Flag It");
  presetname[35].Set("35: String Machine");
  presetname[36].Set("36: Funhesia");
  presetname[37].Set("37: Flubergased");
  presetname[38].Set("38: Padlead");
  presetname[39].Set("39: Omnified");
  presetname[40].Set("40: Rhodez");
  presetname[41].Set("41: Keyboard Delight");
  presetname[42].Set("42: Classic FM Piano");
  presetname[43].Set("43: Toy Joy");
  presetname[44].Set("44: Nicity");
  presetname[45].Set("45: Cufflings");
  presetname[46].Set("46: Why Sir");
  presetname[47].Set("47: Digitor");
  presetname[48].Set("48: Delicay");
  presetname[49].Set("49: Ciffer");

   // MIXER UI
  #include "../MPA Code/GlobalParamInit.h"

  GetParam(kParamLfoWaveform)->InitEnum("LFO Waveform", 0, 6, "", 0, "", "Sine", "Trinangle", "Square", "Saw Up", "Saw Down", "Random");
  GetParam(kParamOperator1Waveform)->InitEnum("Operator 1 Waveform", 0, 4, "", 0, "", "Sine", "Power", "Rectified", "Half Rect");
  GetParam(kParamOperator2Waveform)->InitEnum("Operator 2 Waveform", 0, 4, "", 0, "", "Sine", "Power", "Rectified", "Half Rect");
  GetParam(kParamOperator3Waveform)->InitEnum("Operator 3 Waveform", 0, 4, "", 0, "", "Sine", "Power", "Rectified", "Half Rect");
  GetParam(kParamOperator4Waveform)->InitEnum("Operator 4 Waveform", 0, 4, "", 0, "", "Sine", "Power", "Rectified", "Half Rect");
  GetParam(kParamAlgorithm)->InitInt("Algorithm", 0, 0, 8);

  GetParam(kParamTune)->InitInt("Tune", 0, -99, 99);
  GetParam(kParamVolume)->InitInt("Volume", 63, 0, 127);
  GetParam(kParamPWheel)->InitInt("P-Wheel", 0, -24, 24);
  GetParam(kParamEnvTime)->InitInt("Env Time", 63, 0, 127);
  GetParam(kParamGlide)->InitInt("Glide", 63, 0, 127);

  GetParam(kParamEffectsFeedback)->InitInt("Effect Feedback", 63, 0, 127);
  GetParam(kParamEffectsDryWet)->InitInt("Effect Dry/Wet", 63, 0, 127);
  GetParam(kParamEffectsStereo)->InitInt("Effect Stereo", 63, 0, 127);
  GetParam(kParamEffectsDetune)->InitInt("Effect Detune", 63, 0, 127);

  GetParam(kParamGlobalFMModEnvAmt)->InitInt("Global FM Mod Env Amt", 63, 0, 127);
  GetParam(kParamGlobalFMLFOAmt)->InitInt("Global FM LFO Amt", 63, 0, 127);
  GetParam(kParamGlobalFBModEnvAmt)->InitInt("Global FB Mod Env Amt", 63, 0, 127);
  GetParam(kParamGlobalFBLFOAmt)->InitInt("Global FB LFO Amt", 63, 0, 127);

  GetParam(kParamLfoPhase)->InitInt("LFO Phase", 63, 0, 127);
  GetParam(kParamLfoFadeIn)->InitInt("LFO Fade In", 63, 0, 127);

  GetParam(kParamEffectsDelayTime)->InitInt("Effect Delaytime", 63, 0, 127);
  GetParam(kParamFMDepth)->InitInt("Global FM Depth", 63, 0, 127);
  GetParam(kParamFeedback)->InitInt("Global Feedback", 63, 0, 127);
  GetParam(kParamLfoFrequency)->InitInt("LFO Frquency", 63, 0, 127);

  GetParam(kParamCoarse)->InitInt("Coarse", 0, -24, 24);
  GetParam(kParamOperator1Coarse)->InitInt("Operator 1 Coarse", 0, -48, 48);
  GetParam(kParamOperator2Coarse)->InitInt("Operator 2 Coarse", 0, -48, 48);
  GetParam(kParamOperator3Coarse)->InitInt("Operator 3 Coarse", 0, -48, 48);
  GetParam(kParamOperator4Coarse)->InitInt("Operator 4 Coarse", 0, -48, 48);

  GetParam(kParamModEnvAttack)->InitInt("Mod Env Attack", 63, 0, 127);
  GetParam(kParamModEnvDecay)->InitInt("Mod Env Decay", 63, 0, 127);
  GetParam(kParamModEnvSustain)->InitInt("Mod Env Sustain", 63, 0, 127);
  GetParam(kParamModEnvRelease)->InitInt("Mod Env Release", 63, 0, 127);

  GetParam(kParamOperator1Level)->InitInt("Operator 1 Level", 63, 0, 127);
  GetParam(kParamOperator2Level)->InitInt("Operator 2 Level", 63, 0, 127);
  GetParam(kParamOperator3Level)->InitInt("Operator 3 Level", 63, 0, 127);
  GetParam(kParamOperator4Level)->InitInt("Operator 4 Level", 63, 0, 127);

  GetParam(kParamOperator1Invert)->InitBool("Operator 1 Invert", false);
  GetParam(kParamOperator2Invert)->InitBool("Operator 2 Invert", false);
  GetParam(kParamOperator3Invert)->InitBool("Operator 3 Invert", false);
  GetParam(kParamOperator4Invert)->InitBool("Operator 4 Invert", false);

  GetParam(kParamOperator1Overtone)->InitInt("Operator 1 Overtone", 0, 0, 127);
  GetParam(kParamOperator1FMDepth)->InitInt("Operator 1 FM Depth", 63, 0, 127);
  GetParam(kParamOperator1Phase)->InitInt("Operator 1 Phase", 63, 0, 127);
  GetParam(kParamOperator1Feedback)->InitInt("Operator 1 FB", 63, 0, 127);
  GetParam(kParamOperator1PitchLFO)->InitInt("Operator 1 LFO Pitch", 63, 0, 127);
  GetParam(kParamOperator1LevelLFO)->InitInt("Operator 1 LFO Level", 63, 0, 127);
  GetParam(kParamOperator1LevelVelocity)->InitInt("Operator 1 Level Vel", 63, 0, 127);
  GetParam(kParamOperator1LevelKeyf)->InitInt("Operator 1 Level Keyf", 63, 0, 127);
  GetParam(kParamOperator1EnvAttack)->InitInt("Operator 1 Env Attack", 63, 0, 127);
  GetParam(kParamOperator1EnvDecay)->InitInt("Operator 1 Env Decay", 63, 0, 127);
  GetParam(kParamOperator1EnvSustain)->InitInt("Operator 1 Env Sustain", 63, 0, 127);
  GetParam(kParamOperator1EnvRelease)->InitInt("Operator 1 Env Release", 63, 0, 127);
  GetParam(kParamOperator1EnvCurve)->InitInt("Operator 1 Env Curve", 63, 0, 127);
  GetParam(kParamOperator1Detune)->InitInt("Operator 1 Detune", 0, -100, 100);

  GetParam(kParamOperator2Overtone)->InitInt("Operator 2 Overtone", 0, 0, 127);
  GetParam(kParamOperator2FMDepth)->InitInt("Operator 2 FM Depth", 63, 0, 127);
  GetParam(kParamOperator2Phase)->InitInt("Operator 2 Phase", 63, 0, 127);
  GetParam(kParamOperator2Feedback)->InitInt("Operator 2 FB", 63, 0, 127);
  GetParam(kParamOperator2PitchLFO)->InitInt("Operator 2 LFO Pitch", 63, 0, 127);
  GetParam(kParamOperator2LevelLFO)->InitInt("Operator 2 LFO Level", 63, 0, 127);
  GetParam(kParamOperator2LevelVelocity)->InitInt("Operator 1 Level Vel", 63, 0, 127);
  GetParam(kParamOperator2LevelKeyf)->InitInt("Operator 2 Level Keyf", 63, 0, 127);
  GetParam(kParamOperator2EnvAttack)->InitInt("Operator 2 Env Attack", 63, 0, 127);
  GetParam(kParamOperator2EnvDecay)->InitInt("Operator 2 Env Decay", 63, 0, 127);
  GetParam(kParamOperator2EnvSustain)->InitInt("Operator 2 Env Sustain", 63, 0, 127);
  GetParam(kParamOperator2EnvRelease)->InitInt("Operator 2 Env Release", 63, 0, 127);
  GetParam(kParamOperator2EnvCurve)->InitInt("Operator 2 Env Curve", 63, 0, 127);
  GetParam(kParamOperator2Detune)->InitInt("Operator 2 Detune", 0, -100, 100);

  GetParam(kParamOperator3Overtone)->InitInt("Operator 3 Overtone", 0, 0, 127);
  GetParam(kParamOperator3FMDepth)->InitInt("Operator 3 FM Depth", 63, 0, 127);
  GetParam(kParamOperator3Phase)->InitInt("Operator 3 Phase", 63, 0, 127);
  GetParam(kParamOperator3Feedback)->InitInt("Operator 3 FB", 63, 0, 127);
  GetParam(kParamOperator3PitchLFO)->InitInt("Operator 3 LFO Pitch", 63, 0, 127);
  GetParam(kParamOperator3LevelLFO)->InitInt("Operator 3 LFO Level", 63, 0, 127);
  GetParam(kParamOperator3LevelVelocity)->InitInt("Operator 3 Level Vel", 63, 0, 127);
  GetParam(kParamOperator3LevelKeyf)->InitInt("Operator 3 Level Keyf", 63, 0, 127);
  GetParam(kParamOperator3EnvAttack)->InitInt("Operator 3 Env Attack", 63, 0, 127);
  GetParam(kParamOperator3EnvDecay)->InitInt("Operator 3 Env Decay", 63, 0, 127);
  GetParam(kParamOperator3EnvSustain)->InitInt("Operator 3 Env Sustain", 63, 0, 127);
  GetParam(kParamOperator3EnvRelease)->InitInt("Operator 3 Env Release", 63, 0, 127);
  GetParam(kParamOperator3EnvCurve)->InitInt("Operator 3 Env Curve", 63, 0, 127);
  GetParam(kParamOperator3Detune)->InitInt("Operator 3 Detune", 0, -100, 100);

  GetParam(kParamOperator4Overtone)->InitInt("Operator 4 Overtone", 0, 0, 127);
  GetParam(kParamOperator4FMDepth)->InitInt("Operator 4 FM Depth", 63, 0, 127);
  GetParam(kParamOperator4Phase)->InitInt("Operator 4 Phase", 63, 0, 127);
  GetParam(kParamOperator4Feedback)->InitInt("Operator 4 FB", 63, 0, 127);
  GetParam(kParamOperator4PitchLFO)->InitInt("Operator 4 LFO Pitch", 63, 0, 127);
  GetParam(kParamOperator4LevelLFO)->InitInt("Operator 4 LFO Level", 63, 0, 127);
  GetParam(kParamOperator4LevelVelocity)->InitInt("Operator 1 Level Vel", 63, 0, 127);
  GetParam(kParamOperator4LevelKeyf)->InitInt("Operator 4 Level Keyf", 63, 0, 127);
  GetParam(kParamOperator4EnvAttack)->InitInt("Operator 4 Env Attack", 63, 0, 127);
  GetParam(kParamOperator4EnvDecay)->InitInt("Operator 4 Env Decay", 63, 0, 127);
  GetParam(kParamOperator4EnvSustain)->InitInt("Operator 4 Env Sustain", 63, 0, 127);
  GetParam(kParamOperator4EnvRelease)->InitInt("Operator 4 Env Release", 63, 0, 127);
  GetParam(kParamOperator4EnvCurve)->InitInt("Operator 4 Env Curve", 63, 0, 127);
  GetParam(kParamOperator4Detune)->InitInt("Operator 4 Detune", 0, -100, 100);

    paramToCC[kParamTune                                   ]=91;               
    paramToCC[kParamVolume                                 ]=11;
    paramToCC[kParamPWheel                                 ]=8;
    paramToCC[kParamEnvTime                                ]=13;
    paramToCC[kParamGlide                                  ]=92;                                                           
    paramToCC[kParamEffectsFeedback                        ]=119;
    paramToCC[kParamEffectsDryWet                          ]=10;
    paramToCC[kParamEffectsStereo                          ]=23;
    paramToCC[kParamEffectsDetune                          ]=102;                                                           
    paramToCC[kParamGlobalFMModEnvAmt                      ]=73;
    paramToCC[kParamGlobalFMLFOAmt                         ]=15;
    paramToCC[kParamGlobalFBModEnvAmt                      ]=72;
    paramToCC[kParamGlobalFBLFOAmt                         ]=16;                                                          
    paramToCC[kParamLfoPhase                               ]=5;
    paramToCC[kParamLfoFadeIn                              ]=2;                                                           
    paramToCC[kParamEffectsDelayTime                       ]=81;
    paramToCC[kParamFMDepth                                ]=37;
    paramToCC[kParamFeedback                               ]=55;
    paramToCC[kParamLfoFrequency                           ]=14;                                                           
    paramToCC[kParamCoarse                                 ]=101;
    paramToCC[kParamOperator1Coarse                        ]=28;
    paramToCC[kParamOperator2Coarse                        ]=47;
    paramToCC[kParamOperator3Coarse                        ]=76;
    paramToCC[kParamOperator4Coarse                        ]=66;                                                           
    paramToCC[kParamModEnvAttack                           ]=103;
    paramToCC[kParamModEnvDecay                            ]=3;
    paramToCC[kParamModEnvSustain                          ]=4;
    paramToCC[kParamModEnvRelease                          ]=104;                                                          
    paramToCC[kParamOperator1Level                         ]=74;
    paramToCC[kParamOperator2Level                         ]=71;
    paramToCC[kParamOperator3Level                         ]=84;
    paramToCC[kParamOperator4Level                         ]=106;                                                          
    paramToCC[kParamOperator1Invert                        ]=26;
    paramToCC[kParamOperator2Invert                        ]=45;
    paramToCC[kParamOperator3Invert                        ]=63;
    paramToCC[kParamOperator4Invert                        ]=96;                                                    
    paramToCC[kParamLfoWaveform                            ]=9;
    paramToCC[kParamAlgorithm                              ]=70;                                                        
    paramToCC[kParamOperator1Overtone                      ]=30;
    paramToCC[kParamOperator1FMDepth                       ]=24;
    paramToCC[kParamOperator1Phase                         ]=42;
    paramToCC[kParamOperator1Feedback                      ]=25;
    paramToCC[kParamOperator1PitchLFO                      ]=65;
    paramToCC[kParamOperator1LevelLFO                      ]=39;
    paramToCC[kParamOperator1LevelVelocity                 ]=40;
    paramToCC[kParamOperator1LevelKeyf                     ]=41;
    paramToCC[kParamOperator1EnvAttack                     ]=31;
    paramToCC[kParamOperator1EnvDecay                      ]=33;
    paramToCC[kParamOperator1EnvSustain                    ]=34;
    paramToCC[kParamOperator1EnvRelease                    ]=35;
    paramToCC[kParamOperator1EnvCurve                      ]=36;
    paramToCC[kParamOperator1Detune                        ]=29;
    paramToCC[kParamOperator1Waveform                      ]=27;                                                    
    paramToCC[kParamOperator2Overtone                      ]=49;
    paramToCC[kParamOperator2FMDepth                       ]=43;
    paramToCC[kParamOperator2Phase                         ]=60;
    paramToCC[kParamOperator2Feedback                      ]=44;
    paramToCC[kParamOperator2PitchLFO                      ]=56;
    paramToCC[kParamOperator2LevelLFO                      ]=57;
    paramToCC[kParamOperator2LevelVelocity                 ]=58;
    paramToCC[kParamOperator2LevelKeyf                     ]=59;
    paramToCC[kParamOperator2EnvAttack                     ]=50;
    paramToCC[kParamOperator2EnvDecay                      ]=51;
    paramToCC[kParamOperator2EnvSustain                    ]=52;
    paramToCC[kParamOperator2EnvRelease                    ]=53;
    paramToCC[kParamOperator2EnvCurve                      ]=54;
    paramToCC[kParamOperator2Detune                        ]=48;
    paramToCC[kParamOperator2Waveform                      ]=46;                                                          
    paramToCC[kParamOperator3Overtone                      ]=78;
    paramToCC[kParamOperator3FMDepth                       ]=61;
    paramToCC[kParamOperator3Phase                         ]=89;
    paramToCC[kParamOperator3Feedback                      ]=62;
    paramToCC[kParamOperator3PitchLFO                      ]=85;
    paramToCC[kParamOperator3LevelLFO                      ]=86;
    paramToCC[kParamOperator3LevelVelocity                 ]=40;
    paramToCC[kParamOperator3LevelKeyf                     ]=41;
    paramToCC[kParamOperator3EnvAttack                     ]=79;
    paramToCC[kParamOperator3EnvDecay                      ]=80;
    paramToCC[kParamOperator3EnvSustain                    ]=81;
    paramToCC[kParamOperator3EnvRelease                    ]=82;
    paramToCC[kParamOperator3EnvCurve                      ]=83;
    paramToCC[kParamOperator3Detune                        ]=77;
    paramToCC[kParamOperator3Waveform                      ]=75;                                                         
    paramToCC[kParamOperator4Overtone                      ]=100;
    paramToCC[kParamOperator4FMDepth                       ]=94;
    paramToCC[kParamOperator4Phase                         ]=111;
    paramToCC[kParamOperator4Feedback                      ]=95;
    paramToCC[kParamOperator4PitchLFO                      ]=107;
    paramToCC[kParamOperator4LevelLFO                      ]=108;
    paramToCC[kParamOperator4LevelVelocity                 ]=109;
    paramToCC[kParamOperator4LevelKeyf                     ]=110;
    paramToCC[kParamOperator4EnvAttack                     ]=17;
    paramToCC[kParamOperator4EnvDecay                      ]=18;
    paramToCC[kParamOperator4EnvSustain                    ]=19;
    paramToCC[kParamOperator4EnvRelease                    ]=20;
    paramToCC[kParamOperator4EnvCurve                      ]=105;
    paramToCC[kParamOperator4Detune                        ]=67;
    paramToCC[kParamOperator4Waveform                      ]=97;

    paramToMsgType[kParamTune                                   ]=0;        
    paramToMsgType[kParamVolume                                 ]=0;
    paramToMsgType[kParamPWheel                                 ]=0;
    paramToMsgType[kParamEnvTime                                ]=0;
    paramToMsgType[kParamGlide                                  ]=0;         
    paramToMsgType[kParamEffectsFeedback                        ]=0;
    paramToMsgType[kParamEffectsDryWet                          ]=0;
    paramToMsgType[kParamEffectsStereo                          ]=0;
    paramToMsgType[kParamEffectsDetune                          ]=0;         
    paramToMsgType[kParamGlobalFMModEnvAmt                      ]=0;
    paramToMsgType[kParamGlobalFMLFOAmt                         ]=0;
    paramToMsgType[kParamGlobalFBModEnvAmt                      ]=0;
    paramToMsgType[kParamGlobalFBLFOAmt                         ]=0;         
    paramToMsgType[kParamLfoPhase                               ]=0;
    paramToMsgType[kParamLfoFadeIn                              ]=0;         
    paramToMsgType[kParamEffectsDelayTime                       ]=1;
    paramToMsgType[kParamFMDepth                                ]=0;
    paramToMsgType[kParamFeedback                               ]=0;
    paramToMsgType[kParamLfoFrequency                           ]=0;         
    paramToMsgType[kParamCoarse                                 ]=0;
    paramToMsgType[kParamOperator1Coarse                        ]=0;
    paramToMsgType[kParamOperator2Coarse                        ]=0;
    paramToMsgType[kParamOperator3Coarse                        ]=0;
    paramToMsgType[kParamOperator4Coarse                        ]=0;         
    paramToMsgType[kParamModEnvAttack                           ]=0;
    paramToMsgType[kParamModEnvDecay                            ]=0;
    paramToMsgType[kParamModEnvSustain                          ]=0;
    paramToMsgType[kParamModEnvRelease                          ]=0;         
    paramToMsgType[kParamOperator1Level                         ]=0;
    paramToMsgType[kParamOperator2Level                         ]=0;
    paramToMsgType[kParamOperator3Level                         ]=0;
    paramToMsgType[kParamOperator4Level                         ]=0;         
    paramToMsgType[kParamOperator1Invert                        ]=0;
    paramToMsgType[kParamOperator2Invert                        ]=0;
    paramToMsgType[kParamOperator3Invert                        ]=0;
    paramToMsgType[kParamOperator4Invert                        ]=0;         
    paramToMsgType[kParamLfoWaveform                            ]=0;
    paramToMsgType[kParamAlgorithm                              ]=0;         
    paramToMsgType[kParamOperator1Overtone                      ]=0;
    paramToMsgType[kParamOperator1FMDepth                       ]=0;
    paramToMsgType[kParamOperator1Phase                         ]=0;
    paramToMsgType[kParamOperator1Feedback                      ]=0;
    paramToMsgType[kParamOperator1PitchLFO                      ]=0;
    paramToMsgType[kParamOperator1LevelLFO                      ]=0;
    paramToMsgType[kParamOperator1LevelVelocity                 ]=0;
    paramToMsgType[kParamOperator1LevelKeyf                     ]=0;
    paramToMsgType[kParamOperator1EnvAttack                     ]=0;
    paramToMsgType[kParamOperator1EnvDecay                      ]=0;
    paramToMsgType[kParamOperator1EnvSustain                    ]=0;
    paramToMsgType[kParamOperator1EnvRelease                    ]=0;
    paramToMsgType[kParamOperator1EnvCurve                      ]=0;
    paramToMsgType[kParamOperator1Detune                        ]=0;
    paramToMsgType[kParamOperator1Waveform                      ]=0;         
    paramToMsgType[kParamOperator2Overtone                      ]=0;
    paramToMsgType[kParamOperator2FMDepth                       ]=0;
    paramToMsgType[kParamOperator2Phase                         ]=0;
    paramToMsgType[kParamOperator2Feedback                      ]=0;
    paramToMsgType[kParamOperator2PitchLFO                      ]=0;
    paramToMsgType[kParamOperator2LevelLFO                      ]=0;
    paramToMsgType[kParamOperator2LevelVelocity                 ]=0;
    paramToMsgType[kParamOperator2LevelKeyf                     ]=0;
    paramToMsgType[kParamOperator2EnvAttack                     ]=0;
    paramToMsgType[kParamOperator2EnvDecay                      ]=0;
    paramToMsgType[kParamOperator2EnvSustain                    ]=0;
    paramToMsgType[kParamOperator2EnvRelease                    ]=0;
    paramToMsgType[kParamOperator2EnvCurve                      ]=0;
    paramToMsgType[kParamOperator2Detune                        ]=0;
    paramToMsgType[kParamOperator2Waveform                      ]=0;         
    paramToMsgType[kParamOperator3Overtone                      ]=0;
    paramToMsgType[kParamOperator3FMDepth                       ]=0;
    paramToMsgType[kParamOperator3Phase                         ]=0;
    paramToMsgType[kParamOperator3Feedback                      ]=0;
    paramToMsgType[kParamOperator3PitchLFO                      ]=0;
    paramToMsgType[kParamOperator3LevelLFO                      ]=0;
    paramToMsgType[kParamOperator3LevelVelocity                 ]=0;
    paramToMsgType[kParamOperator3LevelKeyf                     ]=0;
    paramToMsgType[kParamOperator3EnvAttack                     ]=0;
    paramToMsgType[kParamOperator3EnvDecay                      ]=0;
    paramToMsgType[kParamOperator3EnvSustain                    ]=0;
    paramToMsgType[kParamOperator3EnvRelease                    ]=0;
    paramToMsgType[kParamOperator3EnvCurve                      ]=0;
    paramToMsgType[kParamOperator3Detune                        ]=0;
    paramToMsgType[kParamOperator3Waveform                      ]=0;         
    paramToMsgType[kParamOperator4Overtone                      ]=0;
    paramToMsgType[kParamOperator4FMDepth                       ]=0;
    paramToMsgType[kParamOperator4Phase                         ]=0;
    paramToMsgType[kParamOperator4Feedback                      ]=0;
    paramToMsgType[kParamOperator4PitchLFO                      ]=0;
    paramToMsgType[kParamOperator4LevelLFO                      ]=0;
    paramToMsgType[kParamOperator4LevelVelocity                 ]=0;
    paramToMsgType[kParamOperator4LevelKeyf                     ]=0;
    paramToMsgType[kParamOperator4EnvAttack                     ]=0;
    paramToMsgType[kParamOperator4EnvDecay                      ]=0;
    paramToMsgType[kParamOperator4EnvSustain                    ]=0;
    paramToMsgType[kParamOperator4EnvRelease                    ]=0;
    paramToMsgType[kParamOperator4EnvCurve                      ]=0;
    paramToMsgType[kParamOperator4Detune                        ]=0;
    paramToMsgType[kParamOperator4Waveform                      ]=0;

#if IPLUG_EDITOR // All UI methods and member variables should be within an IPLUG_EDITOR guard, should you want distributed UI
  mMakeGraphicsFunc = [&]() {
    return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS, 1.);
  };
  
  mLayoutFunc = [&](IGraphics* pGraphics) {

    pGraphics->LoadFont("Roboto-Regular", FN_ROBOTOREGULAR);
    pGraphics->LoadFont("Calibrib", FN_CALIBRIB);
    pGraphics->LoadFont("Calibri", FN_CALIBRI);
    //pGraphics->LoadFont("overpass-regular", FN_OVERPASSREGULAR);
    pGraphics->HandleMouseOver(true);

    IControl* pBG = new IPanelControl(IRECT(0, 0, HSM_W, HSK_H), IColor(255, 58, 58, 58));
    pGraphics->AttachControl(pBG);

    IBitmap bitmap;
    
    bitmap = pGraphics->LoadBitmap(FN_MPA);
    IControl* logoCtrl = new IBitmapControl(HS_W + 40, HS_H + 28, bitmap, kNoParameter);
    pGraphics->AttachControl(logoCtrl, -1, "");

    bitmap = pGraphics->LoadBitmap(FN_BACKGROUND);
    IControl* backCtrl = new IBitmapControl(0, 0, bitmap, kNoParameter);
    pGraphics->AttachControl(backCtrl, -1, "");

    int x = 0;
    int y = 0;

    bitmap = pGraphics->LoadBitmap(FN_OPERATOR1);
    pGraphics->AttachControl(new IBitmapControl(x + 0, y + 0, bitmap), -1, "Operator1");
    bitmap = pGraphics->LoadBitmap(FN_OPERATOR2);
    pGraphics->AttachControl(new IBitmapControl(x + 0, y + 0, bitmap), -1, "Operator2");
    bitmap = pGraphics->LoadBitmap(FN_OPERATOR3);
    pGraphics->AttachControl(new IBitmapControl(x + 0, y + 0, bitmap), -1, "Operator3");
    bitmap = pGraphics->LoadBitmap(FN_OPERATOR4);
    pGraphics->AttachControl(new IBitmapControl(x + 0, y + 0, bitmap), -1, "Operator4");

    /* OPERATOR 1 */
    bitmap = pGraphics->LoadBitmap(FN_MEDIUMKNOBGLOW, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 366, y + 74, bitmap, kParamOperator1Overtone), -1, "Operator1");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 415, y + 74, bitmap, kParamOperator1FMDepth), -1, "Operator1");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 366, y + 146, bitmap, kParamOperator1Phase), -1, "Operator1");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 415, y + 146, bitmap, kParamOperator1Feedback), -1, "Operator1");

    pGraphics->AttachControl(new IBKnobControlMidi(x + 505, y + 74, bitmap, kParamOperator1PitchLFO), -1, "Operator1");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 555, y + 74, bitmap, kParamOperator1LevelLFO), -1, "Operator1");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 505, y + 146, bitmap, kParamOperator1LevelVelocity), -1, "Operator1");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 555, y + 146, bitmap, kParamOperator1LevelKeyf), -1, "Operator1");

    bitmap = pGraphics->LoadBitmap(FN_LARGEKNOBGLOW, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 278, y + 123, bitmap, kParamOperator1Detune), -1, "Operator1");

    bitmap = pGraphics->LoadBitmap(FN_FADERHANDLEGLOW);
    pGraphics->AttachControl(new IBSliderControlMidi(x + 278, y + 261, 90, kParamOperator1EnvAttack, bitmap), -1, "Operator1");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 333, y + 261, 90, kParamOperator1EnvDecay, bitmap), -1, "Operator1");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 388, y + 261, 90, kParamOperator1EnvSustain, bitmap), -1, "Operator1");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 443, y + 261, 90, kParamOperator1EnvRelease, bitmap), -1, "Operator1");

    pGraphics->AttachControl(new IBSliderControlMidi(x + 518, y + 261, 90, kParamOperator1EnvCurve, bitmap), -1, "Operator1");

    bitmap = pGraphics->LoadBitmap(FN_WAVEFORMSELECTORGLOW, 4);
    pGraphics->AttachControl(new IBitmapControl(x + 265, y + 76, bitmap, kParamOperator1Waveform), -1, "Operator1");
    std::function<double(double)> mappingFunc = [](double midiVal) {return midiVal * 127. / 3.; };
    pGraphics->AttachControl(new IInvisibleCaptionControlMidi(IRECT(x + 265, y + 76, x + 351, y + 94), kParamOperator1Waveform, DEFAULT_TEXT, DEFAULT_BGCOLOR, true, mappingFunc), kCtrlOperator1Waveform, "Operator1");
    bitmap = pGraphics->LoadBitmap(FN_LEFTBUTTONGLOW, 2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 265, y + 96, bitmap, [](IControl* ctrl) {
      if (ctrl->GetValue() == 1) {
        int val = ctrl->GetUI()->GetControlWithTag(kCtrlOperator1Waveform)->GetParam()->Int();
        val = (val - 1); if (val < 0) val = 3;
        double valN = ctrl->GetUI()->GetControlWithTag(kCtrlOperator1Waveform)->GetParam()->ToNormalized(val);
        ctrl->GetUI()->GetControlWithTag(kCtrlOperator1Waveform)->SetValue(valN);
        ctrl->GetUI()->GetControlWithTag(kCtrlOperator1Waveform)->SetDirty(true);
      }
      }), -1, "Operator1");
    bitmap = pGraphics->LoadBitmap(FN_RIGHTBUTTONGLOW, 2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 325, y + 96, bitmap, [](IControl* ctrl) {
      if (ctrl->GetValue() == 1) {
        int val = ctrl->GetUI()->GetControlWithTag(kCtrlOperator1Waveform)->GetParam()->Int();
        val = (val + 1) % 4;
        double valN = ctrl->GetUI()->GetControlWithTag(kCtrlOperator1Waveform)->GetParam()->ToNormalized(val);
        ctrl->GetUI()->GetControlWithTag(kCtrlOperator1Waveform)->SetValue(valN);
        ctrl->GetUI()->GetControlWithTag(kCtrlOperator1Waveform)->SetDirty(true);
      }
      }), -1, "Operator1");

    /* OPERATOR 2 */
    bitmap = pGraphics->LoadBitmap(FN_MEDIUMKNOBGLOW, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 366, y + 74, bitmap, kParamOperator2Overtone), -1, "Operator2");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 415, y + 74, bitmap, kParamOperator2FMDepth), -1, "Operator2");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 366, y + 146, bitmap, kParamOperator2Phase), -1, "Operator2");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 415, y + 146, bitmap, kParamOperator2Feedback), -1, "Operator2");

    pGraphics->AttachControl(new IBKnobControlMidi(x + 505, y + 74, bitmap, kParamOperator2PitchLFO), -1, "Operator2");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 555, y + 74, bitmap, kParamOperator2LevelLFO), -1, "Operator2");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 505, y + 146, bitmap, kParamOperator2LevelVelocity), -1, "Operator2");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 555, y + 146, bitmap, kParamOperator2LevelKeyf), -1, "Operator2");

    bitmap = pGraphics->LoadBitmap(FN_LARGEKNOBGLOW, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 278, y + 123, bitmap, kParamOperator2Detune), -1, "Operator2");

    bitmap = pGraphics->LoadBitmap(FN_FADERHANDLEGLOW);
    pGraphics->AttachControl(new IBSliderControlMidi(x + 278, y + 261, 90, kParamOperator2EnvAttack, bitmap), -1, "Operator2");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 333, y + 261, 90, kParamOperator2EnvDecay, bitmap), -1, "Operator2");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 388, y + 261, 90, kParamOperator2EnvSustain, bitmap), -1, "Operator2");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 443, y + 261, 90, kParamOperator2EnvRelease, bitmap), -1, "Operator2");

    pGraphics->AttachControl(new IBSliderControlMidi(x + 518, y + 261, 90, kParamOperator2EnvCurve, bitmap), -1, "Operator2");

    bitmap = pGraphics->LoadBitmap(FN_WAVEFORMSELECTORGLOW, 4);
    pGraphics->AttachControl(new IBitmapControl(x + 265, y + 76, bitmap, kParamOperator2Waveform), -1, "Operator2");
    mappingFunc = [](double midiVal) {return midiVal * 127. / 3.; };
    pGraphics->AttachControl(new IInvisibleCaptionControlMidi(IRECT(x + 265, y + 76, x + 351, y + 94), kParamOperator2Waveform, DEFAULT_TEXT, DEFAULT_BGCOLOR, true, mappingFunc), kCtrlOperator2Waveform, "Operator2");
    bitmap = pGraphics->LoadBitmap(FN_LEFTBUTTONGLOW, 2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 265, y + 96, bitmap, [](IControl* ctrl) {
      if (ctrl->GetValue() == 1) {
        int val = ctrl->GetUI()->GetControlWithTag(kCtrlOperator2Waveform)->GetParam()->Int();
        val = (val - 1); if (val < 0) val = 3;
        double valN = ctrl->GetUI()->GetControlWithTag(kCtrlOperator2Waveform)->GetParam()->ToNormalized(val);
        ctrl->GetUI()->GetControlWithTag(kCtrlOperator2Waveform)->SetValue(valN);
        ctrl->GetUI()->GetControlWithTag(kCtrlOperator2Waveform)->SetDirty(true);
      }
      }), -1, "Operator2");
    bitmap = pGraphics->LoadBitmap(FN_RIGHTBUTTONGLOW, 2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 325, y + 96, bitmap, [](IControl* ctrl) {
      if (ctrl->GetValue() == 1) {
        int val = ctrl->GetUI()->GetControlWithTag(kCtrlOperator2Waveform)->GetParam()->Int();
        val = (val + 1) % 4;
        double valN = ctrl->GetUI()->GetControlWithTag(kCtrlOperator2Waveform)->GetParam()->ToNormalized(val);
        ctrl->GetUI()->GetControlWithTag(kCtrlOperator2Waveform)->SetValue(valN);
        ctrl->GetUI()->GetControlWithTag(kCtrlOperator2Waveform)->SetDirty(true);
      }
      }), -1, "Operator2");

    /* OPERATOR 3 */
    bitmap = pGraphics->LoadBitmap(FN_MEDIUMKNOBGLOW, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 366, y + 74, bitmap, kParamOperator3Overtone), -1, "Operator3");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 415, y + 74, bitmap, kParamOperator3FMDepth), -1, "Operator3");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 366, y + 146, bitmap, kParamOperator3Phase), -1, "Operator3");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 415, y + 146, bitmap, kParamOperator3Feedback), -1, "Operator3");

    pGraphics->AttachControl(new IBKnobControlMidi(x + 505, y + 74, bitmap, kParamOperator3PitchLFO), -1, "Operator3");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 555, y + 74, bitmap, kParamOperator3LevelLFO), -1, "Operator3");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 505, y + 146, bitmap, kParamOperator3LevelVelocity), -1, "Operator3");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 555, y + 146, bitmap, kParamOperator3LevelKeyf), -1, "Operator3");

    bitmap = pGraphics->LoadBitmap(FN_LARGEKNOBGLOW, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 278, y + 123, bitmap, kParamOperator3Detune), -1, "Operator3");

    bitmap = pGraphics->LoadBitmap(FN_FADERHANDLEGLOW);
    pGraphics->AttachControl(new IBSliderControlMidi(x + 278, y + 261, 90, kParamOperator3EnvAttack, bitmap), -1, "Operator3");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 333, y + 261, 90, kParamOperator3EnvDecay, bitmap), -1, "Operator3");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 388, y + 261, 90, kParamOperator3EnvSustain, bitmap), -1, "Operator3");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 443, y + 261, 90, kParamOperator3EnvRelease, bitmap), -1, "Operator3");

    pGraphics->AttachControl(new IBSliderControlMidi(x + 518, y + 261, 90, kParamOperator3EnvCurve, bitmap), -1, "Operator3");

    bitmap = pGraphics->LoadBitmap(FN_WAVEFORMSELECTORGLOW, 4);
    pGraphics->AttachControl(new IBitmapControl(x + 265, y + 76, bitmap, kParamOperator3Waveform), -1, "Operator3");
    mappingFunc = [](double midiVal) {return midiVal * 127. / 3.; };
    pGraphics->AttachControl(new IInvisibleCaptionControlMidi(IRECT(x + 265, y + 76, x + 351, y + 94), kParamOperator3Waveform, DEFAULT_TEXT, DEFAULT_BGCOLOR, true, mappingFunc), kCtrlOperator3Waveform, "Operator3");
    bitmap = pGraphics->LoadBitmap(FN_LEFTBUTTONGLOW, 2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 265, y + 96, bitmap, [](IControl* ctrl) {
      if (ctrl->GetValue() == 1) {
        int val = ctrl->GetUI()->GetControlWithTag(kCtrlOperator3Waveform)->GetParam()->Int();
        val = (val - 1); if (val < 0) val = 3;
        double valN = ctrl->GetUI()->GetControlWithTag(kCtrlOperator3Waveform)->GetParam()->ToNormalized(val);
        ctrl->GetUI()->GetControlWithTag(kCtrlOperator3Waveform)->SetValue(valN);
        ctrl->GetUI()->GetControlWithTag(kCtrlOperator3Waveform)->SetDirty(true);
      }
      }), -1, "Operator3");
    bitmap = pGraphics->LoadBitmap(FN_RIGHTBUTTONGLOW, 2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 325, y + 96, bitmap, [](IControl* ctrl) {
      if (ctrl->GetValue() == 1) {
        int val = ctrl->GetUI()->GetControlWithTag(kCtrlOperator3Waveform)->GetParam()->Int();
        val = (val + 1) % 4;
        double valN = ctrl->GetUI()->GetControlWithTag(kCtrlOperator3Waveform)->GetParam()->ToNormalized(val);
        ctrl->GetUI()->GetControlWithTag(kCtrlOperator3Waveform)->SetValue(valN);
        ctrl->GetUI()->GetControlWithTag(kCtrlOperator3Waveform)->SetDirty(true);
      }
      }), -1, "Operator3");

    /* OPERATOR 4 */
    bitmap = pGraphics->LoadBitmap(FN_MEDIUMKNOBGLOW, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 366, y + 74, bitmap, kParamOperator4Overtone), -1, "Operator4");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 415, y + 74, bitmap, kParamOperator4FMDepth), -1, "Operator4");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 366, y + 146, bitmap, kParamOperator4Phase), -1, "Operator4");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 415, y + 146, bitmap, kParamOperator4Feedback), -1, "Operator4");

    pGraphics->AttachControl(new IBKnobControlMidi(x + 505, y + 74, bitmap, kParamOperator4PitchLFO), -1, "Operator4");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 555, y + 74, bitmap, kParamOperator4LevelLFO), -1, "Operator4");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 505, y + 146, bitmap, kParamOperator4LevelVelocity), -1, "Operator4");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 555, y + 146, bitmap, kParamOperator4LevelKeyf), -1, "Operator4");

    bitmap = pGraphics->LoadBitmap(FN_LARGEKNOBGLOW, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 278, y + 123, bitmap, kParamOperator4Detune), -1, "Operator4");

    bitmap = pGraphics->LoadBitmap(FN_FADERHANDLEGLOW);
    pGraphics->AttachControl(new IBSliderControlMidi(x + 278, y + 261, 90, kParamOperator4EnvAttack, bitmap), -1, "Operator4");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 333, y + 261, 90, kParamOperator4EnvDecay, bitmap), -1, "Operator4");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 388, y + 261, 90, kParamOperator4EnvSustain, bitmap), -1, "Operator4");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 443, y + 261, 90, kParamOperator4EnvRelease, bitmap), -1, "Operator4");

    pGraphics->AttachControl(new IBSliderControlMidi(x + 518, y + 261, 90, kParamOperator4EnvCurve, bitmap), -1, "Operator4");

    bitmap = pGraphics->LoadBitmap(FN_WAVEFORMSELECTORGLOW, 4);
    pGraphics->AttachControl(new IBitmapControl(x + 265, y + 76, bitmap, kParamOperator4Waveform), -1, "Operator4");
    mappingFunc = [](double midiVal) {return midiVal * 127. / 3.; };
    pGraphics->AttachControl(new IInvisibleCaptionControlMidi(IRECT(x + 265, y + 76, x + 351, y + 94), kParamOperator4Waveform, DEFAULT_TEXT, DEFAULT_BGCOLOR, true, mappingFunc), kCtrlOperator4Waveform, "Operator4");
    bitmap = pGraphics->LoadBitmap(FN_LEFTBUTTONGLOW, 2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 265, y + 96, bitmap, [](IControl* ctrl) {
      if (ctrl->GetValue() == 1) {
        int val = ctrl->GetUI()->GetControlWithTag(kCtrlOperator4Waveform)->GetParam()->Int();
        val = (val - 1); if (val < 0) val = 3;
        double valN = ctrl->GetUI()->GetControlWithTag(kCtrlOperator4Waveform)->GetParam()->ToNormalized(val);
        ctrl->GetUI()->GetControlWithTag(kCtrlOperator4Waveform)->SetValue(valN);
        ctrl->GetUI()->GetControlWithTag(kCtrlOperator4Waveform)->SetDirty(true);
      }
      }), -1, "Operator4");
    bitmap = pGraphics->LoadBitmap(FN_RIGHTBUTTONGLOW, 2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 325, y + 96, bitmap, [](IControl* ctrl) {
      if (ctrl->GetValue() == 1) {
        int val = ctrl->GetUI()->GetControlWithTag(kCtrlOperator4Waveform)->GetParam()->Int();
        val = (val + 1) % 4;
        double valN = ctrl->GetUI()->GetControlWithTag(kCtrlOperator4Waveform)->GetParam()->ToNormalized(val);
        ctrl->GetUI()->GetControlWithTag(kCtrlOperator4Waveform)->SetValue(valN);
        ctrl->GetUI()->GetControlWithTag(kCtrlOperator4Waveform)->SetDirty(true);
      }
      }), -1, "Operator4");

    bitmap = pGraphics->LoadBitmap(FN_MEDIUMKNOBROUNDRED,128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 97, y + 36, bitmap, kParamTune));
    pGraphics->AttachControl(new IBKnobControlMidi(x + 26, y + 75, bitmap, kParamVolume));
    pGraphics->AttachControl(new IBKnobControlMidi(x + 26, y + 146, bitmap, kParamPWheel));
    pGraphics->AttachControl(new IBKnobControlMidi(x + 166, y + 75, bitmap, kParamEnvTime));
    pGraphics->AttachControl(new IBKnobControlMidi(x + 166, y + 146, bitmap, kParamGlide));

    pGraphics->AttachControl(new IBKnobControlMidi(x + 166, y + 341, bitmap, kParamEffectsDetune));
    pGraphics->AttachControl(new IBKnobControlMidi(x + 166, y + 255, bitmap, kParamEffectsStereo));
    pGraphics->AttachControl(new IBKnobControlMidi(x + 86, y + 255, bitmap, kParamEffectsDryWet));
    pGraphics->AttachControl(new IBKnobControlMidi(x + 26, y + 255, bitmap, kParamEffectsFeedback));

    pGraphics->AttachControl(new IBKnobControlMidi(x + 187, y + 564, bitmap, kParamGlobalFBLFOAmt));
    pGraphics->AttachControl(new IBKnobControlMidi(x + 125, y + 564, bitmap, kParamGlobalFBModEnvAmt));
    pGraphics->AttachControl(new IBKnobControlMidi(x + 86, y + 443, bitmap, kParamGlobalFMLFOAmt));
    pGraphics->AttachControl(new IBKnobControlMidi(x + 26, y + 443, bitmap, kParamGlobalFMModEnvAmt));

    pGraphics->AttachControl(new IBKnobControlMidi(x + 526, y + 585, bitmap, kParamLfoPhase));
    pGraphics->AttachControl(new IBKnobControlMidi(x + 585, y + 585, bitmap, kParamLfoFadeIn));

    bitmap = pGraphics->LoadBitmap(FN_LARGEKNOBROUNDRED, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 45, y + 317, bitmap, kParamEffectsDelayTime));
    pGraphics->AttachControl(new IBKnobControlMidi(x + 44, y + 506, bitmap, kParamFMDepth));
    pGraphics->AttachControl(new IBKnobControlMidi(x + 145, y + 477, bitmap, kParamFeedback));
    pGraphics->AttachControl(new IBKnobControlMidi(x + 544, y + 497, bitmap, kParamLfoFrequency));

    bitmap = pGraphics->LoadBitmap(FN_LARGEKNOBROUNDREDLIGHTS, 49);
    mappingFunc = [](double midiVal) {return midiVal * 127. / 48.; };
    pGraphics->AttachControl(new IBKnobControlMidi(x + 81, y + 93, bitmap, kParamCoarse, mappingFunc));
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(99, 159, 130, 175), kParamCoarse, IText(12, IColor(255, 255, 167, 52), nullptr, EAlign::Center, EVAlign::Middle, 0, COLOR_TRANSPARENT, IColor(255, 255, 167, 52)), COLOR_TRANSPARENT, true, mappingFunc));

    bitmap = pGraphics->LoadBitmap(FN_LARGEKNOBROUNDREDLIGHTS2, 97);
    mappingFunc = [](double midiVal) {return midiVal * 127. / 96.; };
    pGraphics->AttachControl(new IBKnobControlMidi(x + 661, y + 49, bitmap, kParamOperator1Coarse, mappingFunc));
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(661+18, 49+66, 661 + 18 + 31, 49 + 66+16), kParamOperator1Coarse, IText(10, IColor(255, 255, 167, 52), nullptr, EAlign::Center, EVAlign::Middle, 0, COLOR_TRANSPARENT, IColor(255, 255, 167, 52)), COLOR_TRANSPARENT, true, mappingFunc));
    pGraphics->AttachControl(new IBKnobControlMidi(x + 661, y + 168, bitmap, kParamOperator2Coarse, mappingFunc));
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(661 + 18, 168+66, 661 + 18 + 31, 168 + 66+16), kParamOperator2Coarse, IText(12, IColor(255, 255, 167, 52), nullptr, EAlign::Center, EVAlign::Middle, 0, COLOR_TRANSPARENT, IColor(255, 255, 167, 52)), COLOR_TRANSPARENT, true, mappingFunc));
    pGraphics->AttachControl(new IBKnobControlMidi(x + 661, y + 289, bitmap, kParamOperator3Coarse, mappingFunc));
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(661 + 18, 289+66, 661 + 18 + 31, 289 + 66+16), kParamOperator3Coarse, IText(12, IColor(255, 255, 167, 52), nullptr, EAlign::Center, EVAlign::Middle, 0, COLOR_TRANSPARENT, IColor(255, 255, 167, 52)), COLOR_TRANSPARENT, true, mappingFunc));
    pGraphics->AttachControl(new IBKnobControlMidi(x + 661, y + 408, bitmap, kParamOperator4Coarse, mappingFunc));
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(661 + 18, 408+66, 661 + 18 + 31, 408 + 66+16), kParamOperator4Coarse, IText(12, IColor(255, 255, 167, 52), nullptr, EAlign::Center, EVAlign::Middle, 0, COLOR_TRANSPARENT, IColor(255, 255, 167, 52)), COLOR_TRANSPARENT, true, mappingFunc));

    bitmap = pGraphics->LoadBitmap(FN_FADERHANDLE);
    pGraphics->AttachControl(new IBSliderControlMidi(x + 279, y + 450, 90, kParamModEnvAttack, bitmap));
    pGraphics->AttachControl(new IBSliderControlMidi(x + 334, y + 450, 90, kParamModEnvDecay, bitmap));
    pGraphics->AttachControl(new IBSliderControlMidi(x + 389, y + 450, 90, kParamModEnvSustain, bitmap));
    pGraphics->AttachControl(new IBSliderControlMidi(x + 444, y + 450, 90, kParamModEnvRelease, bitmap));

    pGraphics->AttachControl(new IBSliderControlMidi(x + 744, y + 44, 90, kParamOperator1Level, bitmap));
    pGraphics->AttachControl(new IBSliderControlMidi(x + 744, y + 164, 90, kParamOperator2Level, bitmap));
    pGraphics->AttachControl(new IBSliderControlMidi(x + 744, y + 284, 90, kParamOperator3Level, bitmap));
    pGraphics->AttachControl(new IBSliderControlMidi(x + 744, y + 404, 90, kParamOperator4Level, bitmap));

    auto PanelFunc = [](IControl* pCaller) {
      if (pCaller->GetUI()) {

        if (pCaller->GetValue() == 1)
        {
          for (int k = 0; k < 4; k++) pCaller->GetUI()->GetControlWithTag(kCtrlTagEditOperator1 + k)->SetValueFromDelegate(0.);

          pCaller->GetUI()->ForControlInGroup("Operator1", [](IControl& ctrl) { ctrl.Hide(true); });
          pCaller->GetUI()->ForControlInGroup("Operator2", [](IControl& ctrl) { ctrl.Hide(true); });
          pCaller->GetUI()->ForControlInGroup("Operator3", [](IControl& ctrl) { ctrl.Hide(true); });
          pCaller->GetUI()->ForControlInGroup("Operator4", [](IControl& ctrl) { ctrl.Hide(true); });

          if (pCaller->GetTag() == kCtrlTagEditOperator1) pCaller->GetUI()->ForControlInGroup("Operator1", [](IControl& ctrl) { ctrl.Hide(false); });
          if (pCaller->GetTag() == kCtrlTagEditOperator2) pCaller->GetUI()->ForControlInGroup("Operator2", [](IControl& ctrl) { ctrl.Hide(false); });
          if (pCaller->GetTag() == kCtrlTagEditOperator3) pCaller->GetUI()->ForControlInGroup("Operator3", [](IControl& ctrl) { ctrl.Hide(false); });
          if (pCaller->GetTag() == kCtrlTagEditOperator4) pCaller->GetUI()->ForControlInGroup("Operator4", [](IControl& ctrl) { ctrl.Hide(false); });
 

          pCaller->SetValueFromDelegate(1.);
        }
        else
        {
          pCaller->SetValue(1.);
          pCaller->SetDirty(false);
        }
      }
    };

    bitmap = pGraphics->LoadBitmap(FN_EDITBUTTON, 2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 789, y + 44, bitmap, PanelFunc), kCtrlTagEditOperator1);
    pGraphics->AttachControl(new IBSwitchControlF(x + 789, y + 164, bitmap, PanelFunc), kCtrlTagEditOperator2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 789, y + 284, bitmap, PanelFunc), kCtrlTagEditOperator3);
    pGraphics->AttachControl(new IBSwitchControlF(x + 789, y + 404, bitmap, PanelFunc), kCtrlTagEditOperator4);

    bitmap = pGraphics->LoadBitmap(FN_INVERTBUTTON, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(x + 789, y + 44 + 25, bitmap, kParamOperator1Invert));
    pGraphics->AttachControl(new IBSwitchControlMidi(x + 789, y + 164 + 25, bitmap, kParamOperator2Invert));
    pGraphics->AttachControl(new IBSwitchControlMidi(x + 789, y + 284 + 25, bitmap, kParamOperator3Invert));
    pGraphics->AttachControl(new IBSwitchControlMidi(x + 789, y + 404 + 25, bitmap, kParamOperator4Invert));

    bitmap = pGraphics->LoadBitmap(FN_LFOWAVEFORMSELECTOR, 6);
    pGraphics->AttachControl(new IBitmapControl(x + 530, y + 450, bitmap, kParamLfoWaveform));
    mappingFunc = [](double midiVal) {return midiVal * 127. / 5.; };
    pGraphics->AttachControl(new IInvisibleCaptionControlMidi(IRECT(x + 530, y + 451, x + 616, y + 469), kParamLfoWaveform, DEFAULT_TEXT, DEFAULT_BGCOLOR, true, mappingFunc), kCtrlLfoWaveform, "Tom2");
    bitmap = pGraphics->LoadBitmap(FN_LEFTBUTTON, 2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 530, y + 470, bitmap, [](IControl* ctrl) {
      if (ctrl->GetValue() == 1) {
        int val = ctrl->GetUI()->GetControlWithTag(kCtrlLfoWaveform)->GetParam()->Int();
        val = (val - 1); if (val < 0) val = 5;
        double valN = ctrl->GetUI()->GetControlWithTag(kCtrlLfoWaveform)->GetParam()->ToNormalized(val);
        ctrl->GetUI()->GetControlWithTag(kCtrlLfoWaveform)->SetValue(valN);
        ctrl->GetUI()->GetControlWithTag(kCtrlLfoWaveform)->SetDirty(true);
      }
      }));
    bitmap = pGraphics->LoadBitmap(FN_RIGHTBUTTON, 2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 590, y + 470, bitmap, [](IControl* ctrl) {
      if (ctrl->GetValue() == 1) {
        int val = ctrl->GetUI()->GetControlWithTag(kCtrlLfoWaveform)->GetParam()->Int();
        val = (val + 1) % 6;
        double valN = ctrl->GetUI()->GetControlWithTag(kCtrlLfoWaveform)->GetParam()->ToNormalized(val);
        ctrl->GetUI()->GetControlWithTag(kCtrlLfoWaveform)->SetValue(valN);
        ctrl->GetUI()->GetControlWithTag(kCtrlLfoWaveform)->SetDirty(true);
      }
      }));



    bitmap = pGraphics->LoadBitmap(FN_ALGORITHMSELECTOR, 9);
    mappingFunc = [](double midiVal) {return midiVal * 127. / 8.; };
    pGraphics->AttachControl(new IBitmapControlMidi(x + 689, y + 538, bitmap, kParamAlgorithm, EBlend::Default, mappingFunc), kCtrlAlgorithm);
    bitmap = pGraphics->LoadBitmap(FN_LEFTBUTTON, 2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 680, y + 616, bitmap, [](IControl* ctrl) {
      if (ctrl->GetValue() == 1) {
        int val = ctrl->GetUI()->GetControlWithTag(kCtrlAlgorithm)->GetParam()->Int();
        val = (val - 1); if (val < 0) val = 8;
        double valN = ctrl->GetUI()->GetControlWithTag(kCtrlAlgorithm)->GetParam()->ToNormalized(val);
        ctrl->GetUI()->GetControlWithTag(kCtrlAlgorithm)->SetValue(valN);
        ctrl->GetUI()->GetControlWithTag(kCtrlAlgorithm)->SetDirty(true);
      }
      }));
    bitmap = pGraphics->LoadBitmap(FN_RIGHTBUTTON, 2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 783, y + 616, bitmap, [](IControl* ctrl) {
      if (ctrl->GetValue() == 1) {
        int val = ctrl->GetUI()->GetControlWithTag(kCtrlAlgorithm)->GetParam()->Int();
        val = (val + 1) % 9;
        double valN = ctrl->GetUI()->GetControlWithTag(kCtrlAlgorithm)->GetParam()->ToNormalized(val);
        ctrl->GetUI()->GetControlWithTag(kCtrlAlgorithm)->SetValue(valN);
        ctrl->GetUI()->GetControlWithTag(kCtrlAlgorithm)->SetDirty(true);
      }
      }));

   


    bitmap = pGraphics->LoadBitmap(FN_MIDIMONBACK);
    IControl* midiCtrlBack = new IBitmapControl(HS_W, 0, bitmap, kNoParameter);
    pGraphics->AttachControl(midiCtrlBack, kCtrlTagMidiBack, "midiMonitor");
      
    // ICaptions Main

    float cw = 22; float ch = 13;
   
    bitmap = pGraphics->LoadBitmap(FN_MIDIACTIVE, 2);
    pGraphics->AttachControl(new IBitmapControl(444, 634, bitmap, kNoParameter), kCtrlMidiActive, "");
    pGraphics->GetControlWithTag(kCtrlMidiActive)->SetActionFunction([&](IControl* ctrl)
      {
        if (ctrl->GetValue() == 1) mMidiActive = true;
        else mMidiActive = false;
        if (GetUI()) for (auto c = 0; c < GetUI()->NControls(); c++) GetUI()->GetControl(c)->SetWantsMidi(mMidiActive);
      }
    );
  

    // MIXER UI
#include "../MPA Code/MixerUI.h" 

    // KEYBOARD UI
#include "../MPA Code/KeyboardUI.h"

// RESIZE CONTROLS ////////////////////////////////////////////////////////////////////////////////////////////////

#include "../MPA Code/Resize.h"



    bitmap = pGraphics->LoadBitmap(FN_PRESETSBUTTON, 2);
    IBSwitchControl *presetUI = new IBSwitchControl(393, 634, bitmap, kNoParameter);
    pGraphics->AttachControl(presetUI, kCtrlTagMidiMonHide, "");
    presetUI->SetActionFunction(resizeFunc);

    bitmap = pGraphics->LoadBitmap(FN_MIXER, 2); // MIXER UI
    IBSwitchControl *mixerUICtrl = new IBSwitchControl(449, 611, bitmap, kNoParameter);
    pGraphics->AttachControl(mixerUICtrl, kCtrlTagMixerHide, "");
    mixerUICtrl->SetActionFunction(resizeFunc);

    bitmap = pGraphics->LoadBitmap(FN_KEYB, 2);
    IBSwitchControl *keybCtrl = new IBSwitchControl(393, 611, bitmap, kNoParameter);
    pGraphics->AttachControl(keybCtrl, kCtrlTagKeybHide, "");
    keybCtrl->SetActionFunction(resizeFunc);

    mixerUICtrl->SetValue(mMixerHide);
    presetUI->SetValue(mPresetHide);
    keybCtrl->SetValue(mKeybHide);

    if (mMixerHide == 1) resizeFunc(mixerUICtrl);
    if (mKeybHide == 1) resizeFunc(keybCtrl);
    resizeFunc(presetUI);

        ///////////////////////////////////////// PRESET /////////////////////////////////////////////////////////////

    bitmap = pGraphics->LoadBitmap(FN_CLEAR, 1);
    IBButtonControl* clearCtrl = new IBButtonControl(HS_W + 64, 469+50+118, bitmap, [&](IControl*) {mMidiLogger->Clear(); });
    pGraphics->AttachControl(clearCtrl, kCtrlTagClear, "midiMonitor");

    mMidiLogger = new MidiMonitor(IRECT(HS_W + 14, 379+50+118, HS_W + 196, 454+50+118), "", "", IText(12, COLOR_BLACK, "Calibri", EAlign::Near), COLOR_WHITE);
    pGraphics->AttachControl(mMidiLogger, kCtrlTagMidiLogger, "midiMonitor");

    bitmap = pGraphics->LoadBitmap(FN_SLIDER, 1);
    pGraphics->AttachControl(new IBSliderControlScroll(HS_W + 210, 378 + 50+118, 75, -1, bitmap), kCtrlSliderMidiMon1);
    pGraphics->GetControlWithTag(kCtrlSliderMidiMon1)->SetActionFunction([&](IControl* ctrl) {mMidiLogger->setEntrypointerOffset(1. - ctrl->GetValue()); });
    pGraphics->GetControlWithTag(kCtrlSliderMidiMon1)->SetValue(1.);

    bitmap = pGraphics->LoadBitmap(FN_RECALL, 1);
    IBButtonControl* RecallCtrl = new IBButtonControl(HS_W + 6, 321+50+118, bitmap, [&](IControl*) {});
    RecallCtrl->SetActionFunction([&](IControl* ctrl) {
      mPresetList->mActiveRow = mPresetList->mSelectedRow;
      GetUI()->GetControlWithTag(kCtrlProgram)->SetValue((double)mPresetList->mActiveRow / (mPresetList->maxLogSamples - 1.));
      GetUI()->GetControlWithTag(kCtrlProgram)->SetDirty();
      });
    pGraphics->AttachControl(RecallCtrl, -1, "midiMonitor");

        bitmap = pGraphics->LoadBitmap(FN_OVERWRITE, 1);
    IBButtonControl* overwriteCtrl = new IBButtonControl(HS_W+85, 321+50+118, bitmap, [&](IControl* pCaller)
      {
        WDL_String str;
        if(GetParam(kParamUserFactory)->Value()==0) str.SetFormatted(100, "You are attempting to overwrite preset %d on factory bank. Please confirm!", mPresetList->mSelectedRow);
        else if(GetParam(kParamUserFactory)->Value() == 1) str.SetFormatted(100, "You are attempting to overwrite preset %d on user bank. Please confirm!", mPresetList->mSelectedRow);

          pCaller->GetUI()->ShowMessageBox(str.Get(), "Overwrite Preset", kMB_YESNO, [&](EMsgBoxResult result) {
            WDL_String str;
            if (result == EMsgBoxResult::kYES) {
              IMidiMsg msg;
              msg.Clear();
              msg.mStatus = mChannel | (IMidiMsg::kProgramChange << 4);
              msg.mData1 = 0x6F;
              msg.mData2 = 0;
              msg.mOffset = -2;
              SendMidiMsgFromUI(msg);
              msg.Clear();
              msg.mStatus = mChannel | (IMidiMsg::kProgramChange << 4);
              msg.mData1 = mPresetList->mSelectedRow;
              msg.mData2 = 0;
              msg.mOffset = -2;
              SendMidiMsgFromUI(msg);
              msg.Clear();
              msg.mStatus = mChannel | (IMidiMsg::kProgramChange << 4);
              msg.mData1 = mPresetList->mSelectedRow;
              msg.mData2 = 0;
              msg.mOffset = -2;
              SendMidiMsgFromUI(msg);
            }
            else if (result == EMsgBoxResult::kNO) {

            }
            });        
      }
    );
    pGraphics->AttachControl(overwriteCtrl, -1, "midiMonitor");
	
	bitmap = pGraphics->LoadBitmap(FN_RESET, 1);
    IBButtonControl* resetCtrl = new IBButtonControl(HS_W + 164, 321+50+118, bitmap,

      [&](IControl* pCaller)
      {
        WDL_String str;
        if (GetParam(kParamUserFactory)->Value() == 0) str.SetFormatted(100, "You are attempting to reset preset %d on factory bank. Please confirm!", mPresetList->mSelectedRow);
        else if (GetParam(kParamUserFactory)->Value() == 1) str.SetFormatted(100, "You are attempting to reset preset %d on user bank. Please confirm!", mPresetList->mSelectedRow);

        pCaller->GetUI()->ShowMessageBox(str.Get(), "Reset Preset", kMB_YESNO, [&](EMsgBoxResult result) {
          WDL_String str;
          if (result == EMsgBoxResult::kYES)
          {
            IMidiMsg msg;
            msg.Clear();
            msg.mStatus = mChannel | (IMidiMsg::kProgramChange << 4);
            msg.mData1 = 0x70;
            msg.mData2 = 0;
            msg.mOffset = -2;
            SendMidiMsgFromUI(msg);
            msg.Clear();
            msg.mStatus = mChannel | (IMidiMsg::kProgramChange << 4);
            msg.mData1 = mPresetList->mSelectedRow;
            msg.mData2 = 0;
            msg.mOffset = -2;
            SendMidiMsgFromUI(msg);
            msg.Clear();
            msg.mStatus = mChannel | (IMidiMsg::kProgramChange << 4);
            msg.mData1 = mPresetList->mSelectedRow;
            msg.mData2 = 0;
            msg.mOffset = -2;
            SendMidiMsgFromUI(msg);
          }
          else if (result == EMsgBoxResult::kNO) {

          }
          });
      }
    );
    pGraphics->AttachControl(resetCtrl, -1, "midiMonitor");

    /////////////////////////////////////////////////////////////////////////

    mPresetList = new PresetList(IRECT(HS_W + 14, 97, HS_W + 196, 310+50+118), 30, "", "", IText(12, COLOR_BLACK, "Calibri", EAlign::Near), COLOR_WHITE);
    pGraphics->AttachControl(mPresetList, kCtrlTagPresetList, "presetList");

    for (int k = 0; k < 50; k++) {
		  mPresetList->addItem(presetname[k]);
	  }

    bitmap = pGraphics->LoadBitmap(FN_SLIDER, 1);
    pGraphics->AttachControl(new IBSliderControlScroll(HS_W + 210, 95, 214+50+118, -1, bitmap), kCtrlSliderPresetList);
    pGraphics->GetControlWithTag(kCtrlSliderPresetList)->SetActionFunction([&](IControl* ctrl) {mPresetList->setFirstRowToShowNormalized(ctrl->GetValue()); });
    pGraphics->GetControlWithTag(kCtrlSliderPresetList)->SetValue(1.);

    ///////////////////////////////////////// CAPTION USER/FACTORY /////////////////////////////////////////////////////////////

   ICaptionControl* userFactory = new ICaptionControl(IRECT(HS_W+10,39,HS_W+115, 58), kParamUserFactory, IText(12,COLOR_WHITE,"Calibrib"), COLOR_BLACK, true);
    userFactory->SetActionFunction([&](IControl* ctrl) {

      if (ctrl->GetValue() == 0) {
        activeRowUser = mPresetList->mActiveRow; // save
        mPresetList->Clear();
        for (int k = 0; k < 50; k++) {
			mPresetList->addItem(presetname[k]);
        }
        mPresetList->mActiveRow = activeRowFactory;
        mPresetList->mSelectedRow = activeRowFactory;
        mPresetList->SnapToRow(activeRowFactory);

      }
      else {
        activeRowFactory = mPresetList->mActiveRow; // save
        mPresetList->Clear();
        for (int k = 0; k < 50; k++) {
          char buffer[30];
          sprintf(buffer, "%0*d - User", 2, k);
          WDL_String str(buffer);
          mPresetList->addItem(str);
        }
        mPresetList->mActiveRow = activeRowUser;
        mPresetList->mSelectedRow = activeRowUser;
        mPresetList->SnapToRow(activeRowUser);
      }
      });

    pGraphics->AttachControl(userFactory, kCtrlUserFactory, "presetList");

    ///////////////////////////////////

    IText t(12, COLOR_WHITE, "Calibrib");
    t.mTextEntryFGColor = COLOR_WHITE;
    t.mTextEntryBGColor = COLOR_BLACK;
    captionCtrl = new ICaptionControl(IRECT(HS_W+149, 37, HS_W+211, 59), kParamProgram, t, COLOR_BLACK, true);
    captionCtrl->SetActionFunction([&](IControl*) {
      mPresetList->setActiveRow(GetParam(kParamProgram)->Value());
      });
    pGraphics->AttachControl(captionCtrl, kCtrlProgram, "");

    bitmap = pGraphics->LoadBitmap(FN_PLUS);
    pGraphics->AttachControl(new IBButtonControl(HS_W + 211, 36, bitmap, [&](IControl*) {
      captionCtrl->SetValue(GetParam(kParamProgram)->ToNormalized(GetParam(kParamProgram)->Value() + 1));
      captionCtrl->SetDirty();
      }
    ), -1, "");

    bitmap = pGraphics->LoadBitmap(FN_MINUS);
    pGraphics->AttachControl(new IBButtonControl(HS_W + 125, 36, bitmap, [&](IControl*) {

      captionCtrl->SetValue(GetParam(kParamProgram)->ToNormalized(GetParam(kParamProgram)->Value() - 1));
      captionCtrl->SetDirty();
      }
    ), -1, "");

    //////////

    bitmap = pGraphics->LoadBitmap(FN_SAVE, 1);

    IBButtonControl* saveButton = new IBButtonControl(HS_W + 8, 6, bitmap, [&](IControl*) {

      WDL_String filename;
      WDL_String path;
      GetUI()->PromptForFile(filename, path, EFileAction::Save, "mpapreset");
      if (filename.GetLength()) {
        nlohmann::json j;
        j["presetname"] = filename.Get();
        nlohmann::json parameters;
        nlohmann::json parameter;
        for (int i = 0; i < kNumParams; i++)
        { // Params
          parameter[GetParam(i)->GetNameForHost()] = GetParam(i)->GetNormalized();
        }
        j["parameters"] = parameter;
        std::ofstream ofs(filename.Get(), std::ofstream::out);
        ofs << j;
        ofs.close();
      }
      });
    pGraphics->AttachControl(saveButton, kCtrlSave, "midiMonitor");

    bitmap = pGraphics->LoadBitmap(FN_LOAD, 1);
    IBButtonControl* loadButton = new IBButtonControl(HS_W + 125, 6, bitmap, [&](IControl*) {
      WDL_String filename;
      WDL_String path;
      GetUI()->PromptForFile(filename, path, EFileAction::Open, "mpapreset");
      try {
        std::ifstream infile;
        infile.open(filename.Get());
        nlohmann::json j;
        infile >> j;
        infile.close();
        for (int i = 0; i < kNumParams; i++) {
          double val = j.at("parameters").at(GetParam(i)->GetNameForHost());
          if(i != kParamProgram) GetUI()->ForControlWithParam(i, [&](IControl& control) {control.SetValueFromUserInput(val); }); // macht nur wenn parameterwert anders als alter ist.
        }
      }
      catch (...) { return; }
      });
    pGraphics->AttachControl(loadButton, kCtrlLoad, "midiMonitor");


    ///////////////////// PRESET END /////////////////////////////////////////////

    if (GetUI()) {
      GetUI()->GetControlWithTag(kCtrlTagEditOperator1)->SetValueFromUserInput(1.);
    }
  };
  
#endif
}

#if IPLUG_DSP
void FMagia::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
  /*const int nChans = NOutChansConnected();
  
  for (auto s = 0; s < nFrames; s++) {
    for (auto c = 0; c < nChans; c++) {
      outputs[c][s] = 0.;
    }
  }*/
}

void FMagia::OnIdle()
{
  mMidiLoggerSender.TransmitData(*this);  
}

void FMagia::OnReset()
{
}

void FMagia ::OnUIClose() {
  if(GetParam(kParamUserFactory)->Value() == 0) activeRowFactory = mPresetList->mActiveRow;
  if (GetParam(kParamUserFactory)->Value() == 1) activeRowUser = mPresetList->mActiveRow;

  for (auto r = 0; r < mMidiLogger->maxLogSamples; r++) {
    for (auto c = 0; c < mMidiLogger->numColumns; c++) {
      mStrBufSave[r][c] = mMidiLogger->mStrBuf[r][c];
    }
  }
  mEntryPtrSave = mMidiLogger->mEntryPointer;
}

void FMagia::OnUIOpen() {

  SendCurrentParamValuesFromDelegate();
  if (GetParam(kParamUserFactory)->Value() == 0) { //Factory
    mPresetList->Clear();
    for (int k = 0; k < 50; k++) {
      mPresetList->addItem(presetname[k]);
    }
    mPresetList->mActiveRow = activeRowFactory;
    mPresetList->mSelectedRow = activeRowFactory;
    mPresetList->SnapToRow(activeRowFactory);
  }
  else if (GetParam(kParamUserFactory)->Value() == 1) { //User
    mPresetList->Clear();
    for (int k = 0; k < 50; k++) {
      char buffer[30];
      sprintf(buffer, "%0*d - User", 2, k);
      WDL_String str(buffer);
      mPresetList->addItem(str);
    }
    mPresetList->mActiveRow = activeRowUser;
    mPresetList->mSelectedRow = activeRowUser;
    mPresetList->SnapToRow(activeRowUser);
  }

  mPresetList->SetDirty();

  for (auto r = 0; r < mMidiLogger->maxLogSamples; r++) {
    for (auto c = 0; c < mMidiLogger->numColumns; c++) {
      mMidiLogger->mStrBuf[r][c] = mStrBufSave[r][c];
    }
  }

  mMidiLogger->mEntryPointer = mEntryPtrSave;

  mMidiLogger->SetDirty();
}

// wird nur von Keyboard und control bewegungen aufgerufen
void FMagia::ProcessMidiMsg(const IMidiMsg& msg)
{
  TRACE;
  #include "../MPA Code/ProcessMidi.h"
}

void FMagia::OnParamChange(int paramIdx)
{
  IMidiMsg msg;

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

    switch (paramIdx) {
     case kParamCoarse:
     case kParamPWheel:
       msg.mData2 = GetParam(paramIdx)->Value() + 24;
       break;
     case kParamOperator1Coarse:
     case kParamOperator2Coarse:
     case kParamOperator3Coarse:
     case kParamOperator4Coarse:
       msg.mData2 = GetParam(paramIdx)->Value() + 48;
       break;
     case kParamLfoWaveform:
     case kParamOperator1Waveform:
     case kParamOperator2Waveform:
     case kParamOperator3Waveform:
     case kParamOperator4Waveform:
     case kParamAlgorithm:
       msg.mData2 = GetParam(paramIdx)->Value();
       break;
    }

    msg.mOffset = -2; // tell ProcessMidiMsg that msg comes from UI
  }

#include "../MPA Code/OnParamChange.h"

  switch (paramIdx)
  {

    int val;
    int lowNote; 
    int highNote;

  case kParamUserFactory:
    if (GetParam(paramIdx)->Value() == 0) { // Factory
      msg.Clear();
      msg.mStatus = mChannel | (IMidiMsg::kControlChange << 4);
      msg.mData1 = 0x00;
      msg.mData2 = PLUGIN_ID;
      msg.mOffset = -2;
      SendMidiMsgFromUI(msg);
      msg.Clear();
      msg.mStatus = mChannel | (IMidiMsg::kControlChange << 4);
      msg.mData1 = 0x20;
      msg.mData2 = 0x00;
      msg.mOffset = -2;
      SendMidiMsgFromUI(msg);
    }
    else if (GetParam(paramIdx)->Value() == 1) { // User
      msg.Clear();
      msg.mStatus = mChannel | (IMidiMsg::kControlChange << 4);
      msg.mData1 = 0x00;
      msg.mData2 = PLUGIN_ID;
      msg.mOffset = -2;
      SendMidiMsgFromUI(msg);
      msg.Clear();
      msg.mStatus = mChannel | (IMidiMsg::kControlChange << 4);
      msg.mData1 = 0x20;
      msg.mData2 = 0x01;
      msg.mOffset = -2;
      SendMidiMsgFromUI(msg);
    }

    break;

  case kParamKeyboardOctave:
    val = GetParam(paramIdx)->Value(); // 0-6
    lowNote = 36 + (val-3) * 12;
    highNote = 91 + (val-3) * 12;
    if(keybCtrl && GetUI()) keybCtrl->SetNoteRange(lowNote, highNote, true);
    break;

  case kParamProgram:

    //if (GetParam(kParamProgram)->Value() == 0) return;
    /* Problem:
    bei start schicek ich Programchange an dino, dann unserialize ich alle parameter, dann kommt vom dino midi zurürck, das überschreibt zustand.
    Könnte nur program unserializen, dann läd es nur das program.
    könnte program nicht unserializen, dann wäre alle parameter korrekt, aber dino würde preset nciht anzeigen. 


    */
    //using namespace std::chrono_literals;
   // std::this_thread::sleep_for(2s);
    //if (unserialized) {
      //return;
   // }

   
    // schalte midi inaktiv, wird in processmidi wieder aktiviert, wenn DP MIDI zurückgibt
    if (GetUI() && GetUI()->GetControlWithTag(kCtrlMidiActive)) GetUI()->GetControlWithTag(kCtrlMidiActive)->SetValueFromUserInput(0.);
   
    // msg.offset = -3 bedeutet dass es immer rausgeht auch wenn midi inaktiv
    if (GetParam(kParamUserFactory)->Value() == 0) { // Factory
      msg.Clear();
      msg.mStatus = mChannel | (IMidiMsg::kControlChange << 4);
      msg.mData1 = 0x00;
      msg.mData2 = PLUGIN_ID;
      msg.mOffset = -3;
      SendMidiMsgFromUI(msg);
      msg.Clear();
      msg.mStatus = mChannel | (IMidiMsg::kControlChange << 4);
      msg.mData1 = 0x20;
      msg.mData2 = 0x00;
      msg.mOffset = -3;
      SendMidiMsgFromUI(msg);
    }
    else if (GetParam(kParamUserFactory)->Value() == 1) { // User
      msg.Clear();
      msg.mStatus = mChannel | (IMidiMsg::kControlChange << 4);
      msg.mData1 = 0x00;
      msg.mData2 = PLUGIN_ID;
      msg.mOffset = -3;
      SendMidiMsgFromUI(msg);
      msg.Clear();
      msg.mStatus = mChannel | (IMidiMsg::kControlChange << 4);
      msg.mData1 = 0x20;
      msg.mData2 = 0x01;
      msg.mOffset = -3;
      SendMidiMsgFromUI(msg);
    }

    msg.Clear();
    msg.mStatus = mChannel | (IMidiMsg::kProgramChange << 4);
    msg.mData1 = GetParam(paramIdx)->Value();
    msg.mData2 = 0;
    msg.mOffset = -3;
    SendMidiMsgFromUI(msg);

    
    break;
    default:
      break;
  }
}

bool FMagia::SerializeState(IByteChunk& chunk) const {

  TRACE;

  /*if (mPresetList) {
    // Overwrite Preset
    IMidiMsg msg;
    msg.Clear();
    msg.mStatus = mChannel | (IMidiMsg::kProgramChange << 4);
    msg.mData1 = 0x6F;
    msg.mData2 = 0;
    msg.mOffset = -2;

    (const_cast<FMagia*>(this))->SendMidiMsgFromUI(msg); // hack
    msg.Clear();
    msg.mStatus = mChannel | (IMidiMsg::kProgramChange << 4);
    msg.mData1 = mPresetList->mSelectedRow;
    msg.mData2 = 0;
    msg.mOffset = -2;
    (const_cast<FMagia*>(this))->SendMidiMsgFromUI(msg);
    msg.Clear();
    msg.mStatus = mChannel | (IMidiMsg::kProgramChange << 4);
    msg.mData1 = mPresetList->mSelectedRow;
    msg.mData2 = 0;
    msg.mOffset = -2;
    (const_cast<FMagia*>(this))->SendMidiMsgFromUI(msg);
  }*/
  
  return SerializeParams(chunk);
}

// this over-ridden method is called when the host is trying to load the plug-in state and you need to unpack the data into your algorithm
// HIER KÖNNEN KEINE CONTROLS GEUPDATED WERDEN; DA MGRAPHICS NOCH NICHT EXISTIERT!!!!
int FMagia::UnserializeState(const IByteChunk& chunk, int startPos) {

  TRACE;

  UnserializeParams(chunk, startPos);
  return 1;
}
#endif
