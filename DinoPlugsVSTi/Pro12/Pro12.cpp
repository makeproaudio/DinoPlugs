#include "Pro12.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"
#include "json.hpp"
#include <fstream>

Pro12::Pro12(IPlugInstanceInfo instanceInfo)
: IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo)
{

  presetname[0 ].Set("00: Kubau");
  presetname[1].Set("01: Heavy Fifths");
  presetname[2].Set("02: Warm Pad");
  presetname[3].Set("03: Bowed Bell");
  presetname[4].Set("04: Hornz");
  presetname[5].Set("05: Every Day Bass");
  presetname[6].Set("06: DnBass");
  presetname[7].Set("07: Thick Matter");
  presetname[8].Set("08: Eastern Slap");
  presetname[9].Set("09: Windy Droplets");
  presetname[10].Set("10: Northern Bells");
  presetname[11].Set("11: Windy Chimes");
  presetname[12].Set("12: Touch Sensitive");
  presetname[13].Set("13: Tubular");
  presetname[14].Set("14: Magrite Clouds");
  presetname[15].Set("15: Punchy Sub");
  presetname[16].Set("16: Space Descents");
  presetname[17].Set("17: Cosmic Phone ");
  presetname[18].Set("18: Space Gas");
  presetname[19].Set("19: Pure Evil");
  presetname[20].Set("20: Untamed");
  presetname[21].Set("21: Ozric");
  presetname[22].Set("22: Evil Sweep");
  presetname[23].Set("23: Beastality");
  presetname[24].Set("24: Ricocete Lead");
  presetname[25].Set("25: Brassy Lead");
  presetname[26].Set("26: Digital Wilderness");
  presetname[27].Set("27: Grape Icicle");
  presetname[28].Set("28: Hats And Ridges");
  presetname[29].Set("29: Quacker");
  presetname[30].Set("30: Fingy Lead");
  presetname[31].Set("31: Ole");
  presetname[32].Set("32: Inflatable");
  presetname[33].Set("33: Electric Guitar With Feedback");
  presetname[34].Set("34: Funky Touch");
  presetname[35].Set("35: Fly Lead");
  presetname[36].Set("36: Noisy Top");
  presetname[37].Set("37: Saw Stack");
  presetname[38].Set("38: Space Hammond");
  presetname[39].Set("39: Space Debris");
  presetname[40].Set("40: Zap It");
  presetname[41].Set("41: Magic Dust");
  presetname[42].Set("42: A.I.");
  presetname[43].Set("43: Shtringz");
  presetname[44].Set("44: Opera Singer");
  presetname[45].Set("45: Citrus punch");
  presetname[46].Set("46: Pico Stack");
  presetname[47].Set("47: Party Seq");
  presetname[48].Set("48: Tummy Pleasure");
  presetname[49].Set("49: Short Cut");

  // KNOBS MAIN

  #include "../MPA Code/GlobalParamInit.h"
 
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
  GetParam(kParamPitchWheel)->InitDouble("Pitch Wheel", 0, 0, 1, 0.001);
	  
  paramToCC[kParamFilterEnv                  ]=63;
  paramToCC[kParamOSCB                       ]=58;
  paramToCC[kParamOSCAFreq                   ]=95;
  paramToCC[kParamOSCAPW                     ]=66;
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
  paramToCC[kParamOSCASync                   ]=67;
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
  paramToCC[kParamAtPwB                      ]=65;
  paramToCC[kParamLfoRetrig                  ]=8;
  paramToCC[kParamLfoMidi                    ]=110;
  paramToCC[kParamPitchWheel                 ] = 1;

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
  paramToMsgType[kParamPitchWheel                 ]= 0;
  
#if IPLUG_EDITOR // All UI methods and member variables should be within an IPLUG_EDITOR guard, should you want distributed UI
  mMakeGraphicsFunc = [&]() {
    return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS, 1.);
  };
  
  mLayoutFunc = [&](IGraphics* pGraphics) {
    pGraphics->LoadFont("Roboto-Regular", FN_ROBOTOREGULAR);
    pGraphics->LoadFont("Calibrib", FN_CALIBRIB);
    pGraphics->LoadFont("Calibri", FN_CALIBRI);
    const IRECT b = pGraphics->GetBounds();

    IControl* pBG = new IPanelControl(IRECT(0, 0, HSM_W, HSK_H), IColor(255, 58, 58, 58));
    pGraphics->AttachControl(pBG);
    
    const IRECT controls = b.GetGridCell(1, 2, 2);

    IBitmap bitmap;

    bitmap = pGraphics->LoadBitmap(FN_MPA);
    IControl* logoCtrl = new IBitmapControl(HS_W + 40, HS_H + 28, bitmap, kNoParameter);
    pGraphics->AttachControl(logoCtrl, -1, "");

    bitmap = pGraphics->LoadBitmap(FN_MIDIMONBACK);
    IControl* midiCtrlBack = new IBitmapControl(HS_W, 0, bitmap, kNoParameter);
    pGraphics->AttachControl(midiCtrlBack, kCtrlTagMidiBack, "midiMonitor");

    bitmap = pGraphics->LoadBitmap(FN_BASE);
    IControl* baseCtrl = new IBitmapControl(0,HEADER_H, bitmap, kNoParameter);
    pGraphics->AttachControl(baseCtrl, -1, "");

    bitmap = pGraphics->LoadBitmap(FN_HEADER);
    IControl* headerCtrl = new IBitmapControl(0, 356, bitmap, kNoParameter);
    pGraphics->AttachControl(headerCtrl, -1, "");

    bitmap = pGraphics->LoadBitmap(FN_PANELMAIN);
    IControl* mainPanelCtrl = new IBitmapControl(16,HEADER_H, bitmap, kNoParameter);
    pGraphics->AttachControl(mainPanelCtrl, -1, "main");
    
    bitmap = pGraphics->LoadBitmap(FN_PANELADD);
    IControl* addPanelCtrl = new IBitmapControl(16, HEADER_H, bitmap, kNoParameter);
    pGraphics->AttachControl(addPanelCtrl, -1, "add");
    if (strcmp(addPanelCtrl->GetGroup(), "add") == 0) addPanelCtrl->Hide(true);

    bitmap = pGraphics->LoadBitmap(FN_PANELEFFECTS);
    IControl* effectsPanelCtrl = new IBitmapControl(16, HEADER_H, bitmap, kNoParameter);
    pGraphics->AttachControl(effectsPanelCtrl, -1, "effects");
    if (strcmp(effectsPanelCtrl->GetGroup(), "effects") == 0) effectsPanelCtrl->Hide(true);

#include "../MPA Code/keyboardui.h"
    
    // SWITCHES MAIN 
    bitmap = pGraphics->LoadBitmap(FN_SWITCH, 2);

    int offX = 0;
    int offY = 0;
    pGraphics->AttachControl(new IBSwitchControlMidi(33,  204-36, bitmap, kParamPolymodFRQA), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(61,  204-36, bitmap, kParamPolymodFRQB), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(89,  204-36, bitmap, kParamPolymodPWA), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(117, 204-36, bitmap, kParamPolymodPWB), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(145, 204-36, bitmap, kParamPolymodFilter), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(33,  317-36, bitmap, kParamWheelmodFRQA), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(61,  317-36, bitmap, kParamWheelmodFRQB), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(89,  317-36, bitmap, kParamWheelmodPWA), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(117, 317-36, bitmap, kParamWheelmodPWB), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(145, 317-36, bitmap, kParamWheelmodFilter), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(262, 92 -36, bitmap, kParamOSCASaw), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(292, 92 -36, bitmap, kParamOSCAPulse), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(393, 92 -36, bitmap, kParamOSCASync), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(335, 202-36, bitmap, kParamOSCBSaw), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(363, 202-36, bitmap, kParamOSCBTri), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(391, 202-36, bitmap, kParamOSCBPulse), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(493, 202-36, bitmap, kParamOSCBLowFreq), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(522, 202-36, bitmap, kParamOSCBKeyb), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(468, 313-36, bitmap, kParamLFOSaw), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(496, 313-36, bitmap, kParamLFOTri), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(524, 313-36, bitmap, kParamLFOPulse), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(568, 313-36, bitmap, kParamAdr), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(605, 313-36, bitmap, kParamRelease), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(354, 313-36, bitmap, kParamUnison), -1, "main");

    // SWITCHES ADD
    pGraphics->AttachControl(new IBSwitchControlMidi(offX+41, offY+108-36, bitmap, kParamKybRetrig), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(offX+86, offY+108-36, bitmap, kParamKybLowNote), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(offX+132, offY+108-36, bitmap, kParamKybSingle), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(343, 221-36, bitmap, kParamAtFreqA), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(377, 221-36, bitmap, kParamAtFreqB), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(479, 221-36, bitmap, kParamAtPwA), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(513, 221-36, bitmap, kParamAtPwB), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(822, 221-36, bitmap, kParamLfoRetrig), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(933, 221-36, bitmap, kParamLfoMidi), -1, "add");

    // SWITCHES EFFECTS
    pGraphics->AttachControl(new IBSwitchControlMidi(53, 85-36, bitmap, kParamFlangerChorus), -1, "effects");
    pGraphics->AttachControl(new IBSwitchControlMidi(438, 85-36, bitmap, kParamDelayUnitLeft), -1, "effects");
    pGraphics->AttachControl(new IBSwitchControlMidi(438, 169-36, bitmap, kParamDelayUnitRight), -1, "effects");
    pGraphics->AttachControl(new IBSwitchControlMidi(484, 169-36, bitmap, kParamDelayCrossDual), -1, "effects");
    bitmap = pGraphics->LoadBitmap(FN_SWITCHBYPASS, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(388, 256-36, bitmap, kParamEffectBypass), -1, "effects");

    // KNOBS MAIN 
    bitmap = pGraphics->LoadBitmap(FN_KNOB1, 65, true);

    pGraphics->AttachControl(new IBKnobControlMidi(47, 86   -36, bitmap, kParamFilterEnv), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(124, 86  -36, bitmap, kParamOSCB), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(208, 87  -36, bitmap, kParamOSCAFreq), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(338, 85  -36, bitmap, kParamOSCAPW), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(209, 196 -36, bitmap, kParamOSCBFreq), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(275, 197 -36, bitmap, kParamOSCBFine), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(431, 197 -36, bitmap, kParamOSCBPW), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(209, 306 -36, bitmap, kParamSourceMix), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(299, 306 -36, bitmap, kParamGlide), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(411, 305 -36, bitmap, kParamLFOFreq), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(452, 85  -36, bitmap, kParamMixOSCA), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(518, 85  -36, bitmap, kParamMixOSCB), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(583, 85  -36, bitmap, kParamMixNoise), -1, "main");
    bitmap = pGraphics->LoadBitmap(FN_KNOB2, 65, true);
    pGraphics->AttachControl(new IBKnobControlMidi(582, 198-36, bitmap, kParamMasterTune), -1, "main");
    bitmap = pGraphics->LoadBitmap(FN_KNOB1, 65, true);
    pGraphics->AttachControl(new IBKnobControlMidi(662, 85-36, bitmap, kParamVCFCutoff), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(725, 85-36, bitmap, kParamVCFResonance), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(789, 85-36, bitmap, kParamVCFEnvAmt), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(853, 85-36, bitmap, kParamVCFKybAmt), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(662, 196-36, bitmap, kParamVCFAttack), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(725, 196-36, bitmap, kParamVCFDecay), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(789, 196-36, bitmap, kParamVCFSustain), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(853, 196-36, bitmap, kParamVCFRelease), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(916, 196-36, bitmap, kParamVCFVelocity), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(662, 306-36, bitmap, kParamVCAAttack), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(725, 306-36, bitmap, kParamVCADecay), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(789, 306-36, bitmap, kParamVCASustain), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(853, 306-36, bitmap, kParamVCARelease), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(916, 306-36, bitmap, kParamVCAVelocity), -1, "main");
    bitmap = pGraphics->LoadBitmap(FN_KNOB2, 65, true);
    pGraphics->AttachControl(new IBKnobControlMidi(920, 85-36, bitmap, kParamVolume), -1, "main");

    bitmap = pGraphics->LoadBitmap(FN_KNOB1, 65, true);

    // KNOBS ADD
    pGraphics->AttachControl(new IBKnobControlMidi(47, 219 - 36, bitmap, kParamMWIntensity), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(116, 219 - 36, bitmap, kParamMWOffset), -1, "add");
    std::function<double(double)> mappingFunc2 = [](double midiVal) {return midiVal * 127. / 24.; };
    pGraphics->AttachControl(new IBKnobControlMidi(186, 219 - 36, bitmap, kParamMWBendRange, mappingFunc2), -1, "add");
    std::function<double(double)> mappingFuncVoices = [](double midiVal) {return midiVal * 12.7 - 0.2; };
    pGraphics->AttachControl(new IBKnobControlMidi(215, 86-36, bitmap, kParamVoices, mappingFuncVoices), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(333, 86-36, bitmap, kParamDetune), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(293, 218-36, bitmap, kParamATPitch), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(428, 218-36, bitmap, kParamATPw), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(556, 218-36, bitmap, kParamATFIlter), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(621, 218-36, bitmap, kParamATAmp), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(686, 218-36, bitmap, kParamATMWAmt), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(751, 216-36, bitmap, kParamATLfoFreq), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(428, 84-36, bitmap, kParamTimeVelVCFAttack), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(522, 84-36, bitmap, kParamTimeVelVCFDecrel), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(614, 84-36, bitmap, kParamTimeVelVCAAttack), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(708, 84-36, bitmap, kParamTimeVelVCADecrel), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(872, 216 - 36, bitmap, kParamLFOPhase), -1, "add");

    // KNOBS EFFECTS
    pGraphics->AttachControl(new IBKnobControlMidi(118, 82  -36, bitmap, kParamChorusRate), -1, "effects");
    pGraphics->AttachControl(new IBKnobControlMidi(118, 160 -36, bitmap, kParamChorusPhase), -1, "effects");
    pGraphics->AttachControl(new IBKnobControlMidi(257, 82  -36, bitmap, kParamChorusDepth), -1, "effects");
    pGraphics->AttachControl(new IBKnobControlMidi(257, 160 -36, bitmap, kParamChorusFeedback), -1, "effects");
    pGraphics->AttachControl(new IBKnobControlMidi(335, 115 -36, bitmap, kParamChorusWet), -1, "effects");
    pGraphics->AttachControl(new IBKnobControlMidi(538, 82  -36, bitmap, kParamDelayTimeLMS), kCtrlTagDelayTimeLMS, "effects");
    pGraphics->AttachControl(new IBKnobControlMidi(538, 163 -36, bitmap, kParamDelayTimeRMS), kCtrlTagDelayTimeRMS, "effects");
    pGraphics->AttachControl(new IBKnobControlMidi(688, 82  -36, bitmap, kParamDelayFeedbackLeft), -1, "effects");
    pGraphics->AttachControl(new IBKnobControlMidi(688, 160 -36, bitmap, kParamDelayFeedbackLeft), -1, "effects"); // coupled with Left FB
    pGraphics->AttachControl(new IBKnobControlMidi(757, 82  -36, bitmap, kParamDelayHidampLeft), -1, "effects");
    pGraphics->AttachControl(new IBKnobControlMidi(757, 160 -36, bitmap, kParamDelayHidampRight), -1, "effects");
    pGraphics->AttachControl(new IBKnobControlMidi(827, 82  -36, bitmap, kParamDelayLevelLeft), -1, "effects");
    pGraphics->AttachControl(new IBKnobControlMidi(825, 160 -36, bitmap, kParamDelayLevelRight), -1, "effects");
    pGraphics->AttachControl(new IBKnobControlMidi(904, 116 -36, bitmap, kParamDelayWet), -1, "effects");


  bitmap = pGraphics->LoadBitmap(FN_MIDIACTIVE, 2);
  pGraphics->AttachControl(new IBitmapControl(168, 382, bitmap), kCtrlMidiActive, "");
  pGraphics->GetControlWithTag(kCtrlMidiActive)->SetActionFunction([&](IControl *ctrl)
      {
        if (ctrl->GetValue() == 1) mMidiActive = true;
        else mMidiActive = false;
        if (GetUI()) for (auto c = 0; c < GetUI()->NControls(); c++) GetUI()->GetControl(c)->SetWantsMidi(mMidiActive);      
      }
    );
	
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(269, 94-36, 299, 109 - 36), kParamVoices, DEFAULT_TEXT, COLOR_LIGHT_GRAY, true, mappingFuncVoices), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(239, 227 - 36, 261, 242 - 36), kParamMWBendRange, DEFAULT_TEXT, COLOR_LIGHT_GRAY, true, mappingFunc2), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(927, 265 - 36, 957, 280 - 36), kParamLFOPhase, DEFAULT_TEXT, COLOR_LIGHT_GRAY, true), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(851, 106 - 36, 911, 124 - 36), kParamMidiClockBpm, DEFAULT_TEXT, COLOR_LIGHT_GRAY, true), -1, "add");

    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(178, 91 - 36, 217, 108 - 36), kParamChorusRate, DEFAULT_TEXT, COLOR_LIGHT_GRAY, true), -1, "effects");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(178+3, 171 - 36, 217-3, 188 - 36), kParamChorusPhase, DEFAULT_TEXT, COLOR_LIGHT_GRAY, true), -1, "effects");

    bitmap = pGraphics->LoadBitmap(FN_HIDE);
    IControl* hideCtrl = new IBitmapControl(505, 63 - 36, bitmap, kNoParameter);
    pGraphics->AttachControl(hideCtrl, kCtrlTagHideL, "effects");
    hideCtrl = new IBitmapControl(515, 140 - 36, bitmap, kNoParameter);
    pGraphics->AttachControl(hideCtrl, kCtrlTagHideR, "effects");

    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(530, 94 - 36, 579, 111 - 36), kParamDelayTimeLBPM, DEFAULT_TEXT, COLOR_LIGHT_GRAY, true), kCtrlTagDelayTimeLBPM, "effects");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(530, 172 - 36, 579, 189 - 36), kParamDelayTimeRBPM, DEFAULT_TEXT, COLOR_LIGHT_GRAY, true), kCtrlTagDelayTimeRBPM, "effects");

    // MAIN

    // Kein Pitchwheel sondern Modwheel
    bitmap = pGraphics->LoadBitmap(FN_PITCHWHEEL, 23, true);
    pGraphics->AttachControl(new IBKnobControlMidi(32, 356, bitmap, kParamPitchWheel), -1, "");

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
            if (pCaller->GetDelegate()->GetParam(kParamDelayUnitLeft)->Value() == 0) {
              pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(true);
              pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMS)->Hide(false);
              pCaller->GetUI()->GetControlWithTag(kCtrlTagHideL)->Hide(true);

            }
            else {
              pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(false);
              pCaller->GetUI()->GetControlWithTag(kCtrlTagHideL)->Hide(false);
              pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMS)->Hide(true);
            }
          }

          if (pCaller->GetUI()->GetControlWithTag(kCtrlTagEffects)->GetValue() == 1) {
            if (pCaller->GetDelegate()->GetParam(kParamDelayUnitRight)->Value() == 0) {
               pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(true);
               pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMS)->Hide(false);
               pCaller->GetUI()->GetControlWithTag(kCtrlTagHideR)->Hide(true);
            }
            else {
               pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(false);
               pCaller->GetUI()->GetControlWithTag(kCtrlTagHideR)->Hide(false);
               pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMS)->Hide(true);
            }
          } 
      }
    };

    bitmap = pGraphics->LoadBitmap(FN_MAIN, 2);
    IBSwitchControlFunc *mainCtrl = new IBSwitchControlFunc(75, 361, bitmap, windowFunc, kNoParameter);
    pGraphics->AttachControl(mainCtrl, kCtrlTagMain);
    mainCtrl->SetValue(1);
    bitmap = pGraphics->LoadBitmap(FN_ADD, 2);
    IBSwitchControlFunc *addCtrl = new IBSwitchControlFunc(75, 382, bitmap, windowFunc, kNoParameter);
    pGraphics->AttachControl(addCtrl, kCtrlTagAdd);
    bitmap = pGraphics->LoadBitmap(FN_EFFECTS, 2);
    IBSwitchControlFunc *effectsCtrl = new IBSwitchControlFunc(75, 403, bitmap, windowFunc, kNoParameter);
    pGraphics->AttachControl(effectsCtrl, kCtrlTagEffects);

    // MIXER UI
#include "../MPA Code/MixerUI.h" 

// RESIZE CONTROLS ////////////////////////////////////////////////////////////////////////////////////////////////

    // RESIZE CONTROLS

    #include "../MPA Code/Resize.h" 

    bitmap = pGraphics->LoadBitmap(FN_MIDIMONITOR, 2);
    IBSwitchControl *presetUI = new IBSwitchControl(406, 382, bitmap, kNoParameter);
    pGraphics->AttachControl(presetUI, kCtrlTagMidiMonHide, "");
    presetUI->SetActionFunction(resizeFunc);

    bitmap = pGraphics->LoadBitmap(FN_MIXER, 2); // MIXER UI
    IBSwitchControl *mixerUICtrl = new IBSwitchControl(327, 382, bitmap, kNoParameter);
    pGraphics->AttachControl(mixerUICtrl, kCtrlTagMixerHide, "");
    mixerUICtrl->SetActionFunction(resizeFunc);

    bitmap = pGraphics->LoadBitmap(FN_KEYB, 2);
    IBSwitchControl *keybCtrl = new IBSwitchControl(247, 382, bitmap, kNoParameter);
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
    IBButtonControl* clearCtrl = new IBButtonControl(HS_W + 64, 400, bitmap, [&](IControl*) {mMidiLogger->Clear(); });
    pGraphics->AttachControl(clearCtrl, kCtrlTagClear, "midiMonitor");

    mMidiLogger = new MidiMonitor(IRECT(HS_W + 14, 379 -70, HS_W + 196, 454 -70), "", "", IText(14, COLOR_BLACK, NULL, EAlign::Near), COLOR_WHITE);
    pGraphics->AttachControl(mMidiLogger, kCtrlTagMidiLogger, "midiMonitor");

    bitmap = pGraphics->LoadBitmap(FN_SLIDER, 1);
    pGraphics->AttachControl(new IBSliderControlScroll(HS_W + 210, 378 -70, 70, -1, bitmap), kCtrlSliderMidiMon1);
    pGraphics->GetControlWithTag(kCtrlSliderMidiMon1)->SetActionFunction([&](IControl* ctrl) {mMidiLogger->setEntrypointerOffset(1. - ctrl->GetValue()); });
    pGraphics->GetControlWithTag(kCtrlSliderMidiMon1)->SetValue(1.);

    bitmap = pGraphics->LoadBitmap(FN_RECALL, 1);
    IBButtonControl* RecallCtrl = new IBButtonControl(HS_W + 6, 251, bitmap, [&](IControl*) {});
    RecallCtrl->SetActionFunction([&](IControl* ctrl) {
      mPresetList->mActiveRow = mPresetList->mSelectedRow;
      GetUI()->GetControlWithTag(kCtrlProgram)->SetValue((double)mPresetList->mActiveRow / (mPresetList->maxLogSamples - 1.));
      GetUI()->GetControlWithTag(kCtrlProgram)->SetDirty();
      });
    pGraphics->AttachControl(RecallCtrl, -1, "midiMonitor");

    bitmap = pGraphics->LoadBitmap(FN_OVERWRITE, 1);
    IBButtonControl* overwriteCtrl = new IBButtonControl(HS_W+85, 251, bitmap, [&](IControl* pCaller)
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
    IBButtonControl* resetCtrl = new IBButtonControl(HS_W + 164, 251, bitmap,

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

    mPresetList = new PresetList(IRECT(HS_W + 14, 97, HS_W + 196, 310 -70), 10,"", "", IText(14, COLOR_BLACK, NULL, EAlign::Near), COLOR_WHITE);
    pGraphics->AttachControl(mPresetList, kCtrlTagPresetList, "presetList");

    for (int k = 0; k < 50; k++) {
		  mPresetList->addItem(presetname[k]);
    }

    bitmap = pGraphics->LoadBitmap(FN_SLIDER, 1);
    pGraphics->AttachControl(new IBSliderControlScroll(HS_W + 210, 95, 214 -70, -1, bitmap), kCtrlSliderPresetList);
    pGraphics->GetControlWithTag(kCtrlSliderPresetList)->SetActionFunction([&](IControl* ctrl) {mPresetList->setFirstRowToShowNormalized(ctrl->GetValue()); });
    pGraphics->GetControlWithTag(kCtrlSliderPresetList)->SetValue(1.);

    ///////////////////////////////////////// CAPTION USER/FACTORY /////////////////////////////////////////////////////////////

    ICaptionControl* userFactory = new ICaptionControl(IRECT(HS_W + 10, 39, HS_W + 115, 58), kParamUserFactory, IText(12, COLOR_WHITE, "Calibrib"), COLOR_BLACK, true);
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

   // Program Change
    IText t;
    t.mSize = 16;
    t.mFGColor = COLOR_WHITE;
    t.mTextEntryFGColor = COLOR_WHITE;
    t.mTextEntryBGColor = COLOR_BLACK;
    captionCtrl = new ICaptionControl(IRECT(HS_W + 149, 37, HS_W + 211, 59), kParamProgram, t, COLOR_BLACK, true);
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

      GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(true);
      GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMS)->Hide(true);
      GetUI()->GetControlWithTag(kCtrlTagHideR)->Hide(true);
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

void Pro12::OnUIClose() {
  if (GetParam(kParamUserFactory)->Value() == 0) activeRowFactory = mPresetList->mActiveRow;
  if (GetParam(kParamUserFactory)->Value() == 1) activeRowUser = mPresetList->mActiveRow;

  for (auto r = 0; r < mMidiLogger->maxLogSamples; r++) {
    for (auto c = 0; c < mMidiLogger->numColumns; c++) {
      mStrBufSave[r][c] = mMidiLogger->mStrBuf[r][c];
    }
  }
  mEntryPtrSave = mMidiLogger->mEntryPointer;
}

void Pro12::OnUIOpen() {

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
void Pro12::ProcessMidiMsg(const IMidiMsg& msg)
{
  TRACE;

#include "../MPA Code/ProcessMidi.h"
}

void Pro12::OnParamChange(int paramIdx)
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


    // Controls get value direct, not 0-127
    switch (paramIdx) {
    case kParamDelayTimeLBPM:
    case kParamDelayTimeRBPM:
    case kParamMWBendRange:
    case kParamVoices:
      msg.mData2 = GetParam(paramIdx)->Value();
      break;
    case kParamMidiClockBpm:
      msg.mData2 = GetParam(paramIdx)->Value()-72;
      break;
    }

    msg.mOffset = -2;
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
      msg.mData2 = 0x01;
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
      msg.mData2 = 0x01;
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
    if (GetUI() && GetUI()->GetControlWithTag(kCtrlMidiActive)) GetUI()->GetControlWithTag(kCtrlMidiActive)->SetValueFromUserInput(0.);
  
  if (GetParam(kParamUserFactory)->Value() == 0) { // Factory
      msg.Clear();
      msg.mStatus = mChannel | (IMidiMsg::kControlChange << 4);
      msg.mData1 = 0x00;
      msg.mData2 = 0x01;
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
      msg.mData2 = 0x01;
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

  case kParamDelayUnitLeft:
    if (GetUI()) {
      if (GetUI()->GetControlWithTag(kCtrlTagEffects)->GetValue() == 1) {
        if (GetParam(paramIdx)->Value() == 0) {
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(true);
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMS)->Hide(false);
          GetUI()->GetControlWithTag(kCtrlTagHideL)->Hide(true);

        }
        else {
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(false);
          GetUI()->GetControlWithTag(kCtrlTagHideL)->Hide(false);
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMS)->Hide(true);
        }
      }
    }
    break;
  case kParamDelayUnitRight:
    if (GetUI()) {
      if (GetUI()->GetControlWithTag(kCtrlTagEffects)->GetValue() == 1) {
        if (GetParam(paramIdx)->Value() == 0) {
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(true);
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMS)->Hide(false);
          GetUI()->GetControlWithTag(kCtrlTagHideR)->Hide(true);
        }
        else {
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(false);
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

  return SerializeParams(chunk);
}

// this over-ridden method is called when the host is trying to load the plug-in state and you need to unpack the data into your algorithm
// HIER KÖNNEN KEINE CONTROLS GEUPDATED WERDEN; DA MGRAPHICS NOCH NICHT EXISTIERT!!!!
int Pro12::UnserializeState(const IByteChunk& chunk, int startPos) {

  TRACE;

  return UnserializeParams(chunk, startPos);
}
#endif
