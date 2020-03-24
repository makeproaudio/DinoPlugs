#include "Prodyssey.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"
#include "json.hpp"
#include <fstream>

Prodyssey::Prodyssey(IPlugInstanceInfo instanceInfo)
: IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo)
{
  #include "../MPA Code/GlobalParamInit.h"

  presetname[0].Set("00: Evilead");
  presetname[1 ].Set("01 : Talk To Me!");
  presetname[2 ].Set("02 : Zappa Lead");
  presetname[3 ].Set("03 : Accentor");
  presetname[4 ].Set("04 : Shining Star");
  presetname[5 ].Set("05 : Heavy Bass");
  presetname[6 ].Set("06 : Window Wiper");
  presetname[7 ].Set("07 : Air");
  presetname[8 ].Set("08 : Decintegrator");
  presetname[9 ].Set("09 : WowaWa");
  presetname[10].Set("10 : Creaper");
  presetname[11].Set("11 : Honey Funk");
  presetname[12].Set("12 : Vintage Rug");
  presetname[13].Set("13 : Don't Tell Me...");
  presetname[14].Set("14 : BoK Tvei");
  presetname[15].Set("15 : Subby Doo");
  presetname[16].Set("16 : Pulsating");
  presetname[17].Set("17 : Elongatio");
  presetname[18].Set("18 : Goo");
  presetname[19].Set("19 : Fleas");
  presetname[20].Set("20 : Claus Schultz");
  presetname[21].Set("21 : Winds Of Time");
  presetname[22].Set("22 : MiniArp");
  presetname[23].Set("23 : The Detune");
  presetname[24].Set("24 : Snake Tail");
  presetname[25].Set("25 : Mother Goose");
  presetname[26].Set("26 : Dense Enough?");
  presetname[27].Set("27 : Robot Singer");
  presetname[28].Set("28 : Override");
  presetname[29].Set("29 : Counting Sheep");
  presetname[30].Set("30 : OctoLead");
  presetname[31].Set("31 : Binary Worms");
  presetname[32].Set("32 : Piercer");
  presetname[33].Set("33 : Human Organ");
  presetname[34].Set("34 : Hysterrical");
  presetname[35].Set("35 : Warm Pad");
  presetname[36].Set("36 : Hollow Pad");
  presetname[37].Set("37 : Dark Pad");
  presetname[38].Set("38 : Fuzzy Pazzy");
  presetname[39].Set("39 : Piano");
  presetname[40].Set("40 : Gibson");
  presetname[41].Set("41 : Criptonite");
  presetname[42].Set("42 : Baby Trance");
  presetname[43].Set("43 : Wiper");
  presetname[44].Set("44 : MiniKong");
  presetname[45].Set("45 : The Big Machine");
  presetname[46].Set("46 : Vintage Banjo");
  presetname[47].Set("47 : Digiman");
  presetname[48].Set("48 : Pocket Calculator");
  presetname[49].Set("49 : Open");

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

  GetParam(kParamMasterOctave)->InitEnum("Octave", 1, 3);
  GetParam(kParamVco1Octave)->InitEnum("Octave VCO 1", 1, 3);
  GetParam(kParamVco2Octave)->InitEnum("Octave VCO 2", 1, 3);
  GetParam(kParamAftertouchVco)->InitEnum("Aftertouch VCO", 1, 3);
  GetParam(kParamBendRange)->InitInt("Bend Range", 0, 0, 24);
  GetParam(kParamLfoNote)->InitEnum("LFO Note", 0, 19, "", 0, "", "1/1", "1/2P", "1/2", "1/2T", "1/4P", "1/4", "1/4T", "1/8P", "1/8", "1/8T", "1/16P", "1/16", "1/16T", "1/32P", "1/32", "1/32T", "1/64P", "1/64", "1/64T");

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
  GetParam(kParamAftertouchPitch)->InitDouble("Aftertouch Pitch",0,0,1,0.001);
  GetParam(kParamAftertouchFilter)->InitDouble("Aftertouch Filter",0,0,1,0.001);
  
  GetParam(kParamKeybModeRetrig)->InitEnum("KYB Trig Mode",0,2);
  GetParam(kParamKeybModeLowNote)->InitEnum("KYB Note Mode",0,2);
  GetParam(kParamKeybModeSingle)->InitEnum("KYB Poly Mode",0,2);
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
  paramToCC[kParamPortamento                ]=5;
  paramToCC[kParamMixerNoiseLevel           ]=42;
  paramToCC[kParamVcfFreq                   ]=74;
  paramToCC[kParamVcfRes                    ]=71;
  paramToCC[kParamHpfFreq                   ]=19;
  paramToCC[kParamVcaGain                   ]=51;
  paramToCC[kParamVcfKeyb                   ]=45;
  paramToCC[kParamVcfAdsr                   ]=49;
  paramToCC[kParamVcaAdsr                   ]=11;
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
  
  paramToCC[kParamAftertouchPitch           ]=105;
  paramToCC[kParamAftertouchFilter          ]=108;
  paramToCC[kParamKeybModeRetrig            ]=69;
  paramToCC[kParamKeybModeLowNote           ]=101;
  paramToCC[kParamKeybModeSingle            ]=68;
  paramToCC[kParamAftertouchVco             ]=106;
  paramToCC[kParamPitchWheel                ]=1;
  paramToCC[kParamMasterOctave              ]=109;
  paramToCC[kParamVco1Octave                ]=113;
  paramToCC[kParamVco2Octave                ]=114;
  paramToCC[kParamLfoNote                   ]=96;

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
  paramToMsgType[kParamAftertouchPitch           ]=0;
  paramToMsgType[kParamAftertouchFilter          ]=0;
  paramToMsgType[kParamKeybModeRetrig            ]=0;
  paramToMsgType[kParamKeybModeLowNote           ]=0;
  paramToMsgType[kParamKeybModeSingle            ]=0;
  paramToMsgType[kParamAftertouchVco             ]=0;
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

    pGraphics->LoadFont("Roboto-Regular", FN_ROBOTOREGULAR);
    pGraphics->LoadFont("Calibrib", FN_CALIBRIB);
    pGraphics->LoadFont("Calibri", FN_CALIBRI);

    const IRECT b = pGraphics->GetBounds();

    IControl* pBG = new IPanelControl(IRECT(0,0, HSM_W, HSK_H), IColor(255,58,58,58));
    pGraphics->AttachControl(pBG);

    const IRECT controls = b.GetGridCell(1, 2, 2);

    IBitmap bitmap;

    bitmap = pGraphics->LoadBitmap(FN_MPA);
    IControl* logoCtrl = new IBitmapControl(HS_W+40, HS_H+28, bitmap, kNoParameter);
    pGraphics->AttachControl(logoCtrl, -1, "");

    bitmap = pGraphics->LoadBitmap(FN_BACK);
    IControl* backCtrl = new IBitmapControl(0,0, bitmap, kNoParameter);
    pGraphics->AttachControl(backCtrl, -1, "");

    bitmap = pGraphics->LoadBitmap(FN_MIDIMONBACK);
    IControl* midiCtrlBack = new IBitmapControl(HS_W, 0, bitmap, kNoParameter);
    pGraphics->AttachControl(midiCtrlBack, kCtrlTagMidiBack, "midiMonitor");

    /* BITMAPS */
    bitmap = pGraphics->LoadBitmap(FN_HEADER);
    IControl* mainPanelHeadCtrl = new IBitmapControl(0, 0, bitmap, kNoParameter);
    pGraphics->AttachControl(mainPanelHeadCtrl);

    bitmap = pGraphics->LoadBitmap(FN_PANELMAIN);
    IControl* mainPanelCtrl = new IBitmapControl(4, 35, bitmap, kNoParameter);
    pGraphics->AttachControl(mainPanelCtrl, -1, "main");

    bitmap = pGraphics->LoadBitmap(FN_PANELADD);
    IControl* addPanelCtrl = new IBitmapControl(4, 35, bitmap, kNoParameter);
    pGraphics->AttachControl(addPanelCtrl, -1, "add");
    if (strcmp(addPanelCtrl->GetGroup(), "add") == 0) addPanelCtrl->Hide(true);

    /* SWITCHES */
    bitmap = pGraphics->LoadBitmap(FN_TT, 2);

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

    /* FADER BLACK*/
    bitmap = pGraphics->LoadBitmap(FN_FADERBLACK, 1);
    pGraphics->AttachControl(new IBSliderControlMidi(39, 288,89, kParamPortamento, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(523, 288, 89, kParamMixerNoiseLevel, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(523, 83, 89, kParamVcfFreq, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(560, 83, 89, kParamVcfRes, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(709, 83, 89, kParamHpfFreq, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(778, 83, 89, kParamVcaGain, bitmap), -1, "main");

    bitmap = pGraphics->LoadBitmap(FN_FADERRED, 1);
    pGraphics->AttachControl(new IBSliderControlMidi(635, 288, 89, kParamVcfKeyb, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(709, 288, 89, kParamVcfAdsr, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(779, 288, 89, kParamVcaAdsr, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(815, 83, 89, kParamArAttack, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(817+36, 83, 89, kParamArRelease, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(782+36, 288, 89, kParamAdsrAttack, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(817+36, 288, 89, kParamAdsrDecay, bitmap), -1, "main");

    bitmap = pGraphics->LoadBitmap(FN_FADERYELLOW, 1);
    pGraphics->AttachControl(new IBSliderControlMidi(121, 288, 89, kParamVco1ShLevel, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(269, 288, 89, kParamVco2ShLevel, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(486, 288, 89, kParamShLag, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(671, 288, 89, kParamVcfShLevel, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(890, 288, 89, kParamAdsrSustain, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(926, 288, 89, kParamAdsrRelease, bitmap), -1, "main");

    bitmap = pGraphics->LoadBitmap(FN_FADERPINK, 1);
    pGraphics->AttachControl(new IBSliderControlMidi(83, 288, 89, kParamVco1FmModLfoLevel, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(195, 288, 89, kParamVco1PwModLfoLevel, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(231, 288, 89, kParamVco2FmModLfoLevel, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(343, 288, 89, kParamVco2PwModLfoLevel, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(486, 83, 89, kParamLfoFreq, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(853+36, 83, 89, kParamArVel, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(926, 83, 89, kParamArKeyb, bitmap), -1, "main");

    bitmap = pGraphics->LoadBitmap(FN_FADERCYAN, 1);
    pGraphics->AttachControl(new IBSliderControlMidi(83, 83, 89, kParamVco1Coarse, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(119, 83, 89, kParamVco1Fine, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(158, 288, 89, kParamVco1PwWidth, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(379, 288, 89, kParamShMixerMod1Level, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(417, 288, 89, kParamShMixerMod2Level, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(561, 288, 89, kParamAudioMixerIn2level, bitmap), -1, "main");

    bitmap = pGraphics->LoadBitmap(FN_FADERGREEN, 1);
    pGraphics->AttachControl(new IBSliderControlMidi(230, 83, 89, kParamVco2Coarse, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(267, 83, 89, kParamVco2Fine, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(306, 288, 89, kParamVco2PwWidth, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(597, 288, 89, kParamAudioMixerIn3level, bitmap), -1, "main");

    // Slider ADD 
    bitmap = pGraphics->LoadBitmap(FN_FADERBLACK, 1);
    std::function<double(double)> mappingFunc2 = [](double midiVal) {return midiVal * 127. / 24.; };
    pGraphics->AttachControl(new IBSliderControlMidi(22, 84, 89, kParamBendRange, bitmap, mappingFunc2), -1, "add");
    pGraphics->AttachControl(new ICaptionControl(IRECT(22, 185, 47, 205), kParamBendRange, DEFAULT_TEXT, COLOR_LIGHT_GRAY), -1, "add");
    pGraphics->AttachControl(new IBSliderControlMidi(22, 303, 89, kParamModWheelIntensity, bitmap), -1, "add");
    pGraphics->AttachControl(new IBSliderControlMidi(123, 303, 89, kParamChorusRate, bitmap), -1, "add");
    pGraphics->AttachControl(new ICaptionControl(IRECT(121, 273, 153, 288), kParamChorusRate, DEFAULT_TEXT, COLOR_LIGHT_GRAY), -1, "add");

    bitmap = pGraphics->LoadBitmap(FN_FADERCYAN, 1);
    pGraphics->AttachControl(new IBSliderControlMidi(81, 303, 89, kParamChorusPhase, bitmap), -1, "add");
    pGraphics->AttachControl(new ICaptionControl(IRECT(78, 273, 110, 288), kParamChorusPhase, DEFAULT_TEXT, COLOR_LIGHT_GRAY), -1, "add");

    bitmap = pGraphics->LoadBitmap(FN_FADERRED, 1);
    pGraphics->AttachControl(new IBSliderControlMidi(168, 303, 89, kParamChorusDepth, bitmap), -1, "add");

    bitmap = pGraphics->LoadBitmap(FN_FADERYELLOW, 1);
    pGraphics->AttachControl(new IBSliderControlMidi(211, 303, 89, kParamChorusFeedback, bitmap), -1, "add");
    pGraphics->AttachControl(new IBSliderControlMidi(507, 303, 89, kParamDelayFeedbackLeft, bitmap), -1, "add");
    pGraphics->AttachControl(new IBSliderControlMidi(655, 303, 89, kParamDelayFeedbackLeft, bitmap), -1, "add");

    bitmap = pGraphics->LoadBitmap(FN_FADERGREEN, 1);

    pGraphics->AttachControl(new IBSliderControlMidi(282, 303, 89, kParamChorusWet, bitmap), -1, "add");

    bitmap = pGraphics->LoadBitmap(FN_FADERBG);
    pGraphics->AttachControl(new IBitmapControl(357+8, 304, bitmap, kNoParameter), kCtrlTagFaderBg1, "add");
    pGraphics->AttachControl(new IBitmapControl(410+27, 304, bitmap, kNoParameter), kCtrlTagFaderBg2, "add");

    bitmap = pGraphics->LoadBitmap(FN_FADERGREEN, 1);

    pGraphics->AttachControl(new IBSliderControlMidi(359+8, 303, 89, kParamDelayTimeLMS, bitmap), kCtrlTagDelayTimeLMS, "add");
    pGraphics->AttachControl(new IBSliderControlMidi(412+27, 303, 89, kParamDelayTimeRMS, bitmap), kCtrlTagDelayTimeRMS, "add");

    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(351, 322, 397, 342), kParamDelayTimeLBPM, DEFAULT_TEXT, COLOR_LIGHT_GRAY, true), kCtrlTagDelayTimeLBPM, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(426, 322, 472, 342), kParamDelayTimeRBPM, DEFAULT_TEXT, COLOR_LIGHT_GRAY, true), kCtrlTagDelayTimeRBPM, "add");

    std::function<double(double)> mappingFuncLfoNote = [](double midiVal) {return midiVal * 127. / 18.; };
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(708, 93, 758, 113), kParamLfoNote, DEFAULT_TEXT, COLOR_LIGHT_GRAY, true, mappingFuncLfoNote), -1, "add");
   
    pGraphics->AttachControl(new IBSliderControlMidi(594, 303, 89, kParamDelayLevelLeft, bitmap), -1, "add");
    pGraphics->AttachControl(new IBSliderControlMidi(737, 303, 89, kParamDelayLevelRight, bitmap), -1, "add");
    pGraphics->AttachControl(new IBSliderControlMidi(836, 303, 89, kParamDelayWet, bitmap), -1, "add");

    bitmap = pGraphics->LoadBitmap(FN_FADERPINK, 1);
    pGraphics->AttachControl(new IBSliderControlMidi(550, 303, 89, kParamDelayHidampLeft, bitmap), -1, "add");
    pGraphics->AttachControl(new IBSliderControlMidi(696, 303, 89, kParamDelayHidampRight, bitmap), -1, "add");
    pGraphics->AttachControl(new IBSliderControlMidi(506, 60, 89, kParamAftertouchPitch, bitmap), -1, "add");
    pGraphics->AttachControl(new IBSliderControlMidi(612, 60, 89, kParamAftertouchFilter, bitmap), -1, "add");

    // SWITCHES ADD

    bitmap = pGraphics->LoadBitmap(FN_TT, 2);

    pGraphics->AttachControl(new IBSwitchControlMidi(162, 422, bitmap, kParamFlangerChorus), -1,    "add");
    bitmap = pGraphics->LoadBitmap(FN_TTBYPASS, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(328, 422, bitmap, kParamEffectBypass), -1,    "add");
    bitmap = pGraphics->LoadBitmap(FN_TT, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(371, 422, bitmap, kParamDelayUnitLeft), -1,   "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(442, 422, bitmap, kParamDelayUnitRight), -1,  "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(483, 422, bitmap, kParamDelayCrossDual), -1,  "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(306, 83, bitmap, kParamKeybModeRetrig), -1,  "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(366, 83, bitmap, kParamKeybModeLowNote), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(423, 83, bitmap, kParamKeybModeSingle), -1,  "add");

    bitmap = pGraphics->LoadBitmap(FN_SWITCH5, 3, true);
    pGraphics->AttachControl(new IBSwitchControlMidi(557, 87, bitmap, kParamAftertouchVco), -1, "add");

    bitmap = pGraphics->LoadBitmap(FN_MIDIACTIVE, 2);
    pGraphics->AttachControl(new IBitmapControl(493, 9, bitmap), kCtrlMidiActive, "");
    pGraphics->GetControlWithTag(kCtrlMidiActive)->SetActionFunction([&](IControl *ctrl)
      {
        if (ctrl->GetValue() == 1) mMidiActive = true;
        else mMidiActive = false;
        if (GetUI()) for (auto c = 0; c < GetUI()->NControls(); c++) GetUI()->GetControl(c)->SetWantsMidi(mMidiActive);      
      }
    );

    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(141, 97, 188, 114), kParamMidiClockBpm, DEFAULT_TEXT, COLOR_LIGHT_GRAY, true), -1, "add");
 
    // Kein Pitchwheel sondern Modwheel
    bitmap = pGraphics->LoadBitmap(FN_PITCHWHEEL, 18, true);
    pGraphics->AttachControl(new IBKnobControlMidi(40, 395, bitmap, kParamPitchWheel), -1, "main");

    bitmap = pGraphics->LoadBitmap(FN_SWITCH4, 3, true);
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

          }
          else {
           pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(false);
           pCaller->GetUI()->GetControlWithTag(kCtrlTagFaderBg1)->Hide(true);
           pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMS)->Hide(true);
          }
        }

        if (pCaller->GetUI()->GetControlWithTag(kCtrlTagAdd)->GetValue() == 1) {
          if (pCaller->GetDelegate()->GetParam(kParamDelayUnitRight)->Value() == 0) {
            pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(true);
            pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMS)->Hide(false);
            pCaller->GetUI()->GetControlWithTag(kCtrlTagFaderBg2)->Hide(false);
          }
          else {
            pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(false);
            pCaller->GetUI()->GetControlWithTag(kCtrlTagFaderBg2)->Hide(true);
            pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMS)->Hide(true);
          }
        }

      }
    };

    bitmap = pGraphics->LoadBitmap(FN_MAIN, 2);
    IBSwitchControlFunc *mainCtrl = new IBSwitchControlFunc(243, 9, bitmap, windowFunc, kNoParameter);
    pGraphics->AttachControl(mainCtrl, kCtrlTagMain);
    mainCtrl->SetValue(1);

    bitmap = pGraphics->LoadBitmap(FN_ADD, 2);
    IBSwitchControlFunc *addCtrl = new IBSwitchControlFunc(310, 9, bitmap, windowFunc, kNoParameter);
    pGraphics->AttachControl(addCtrl, kCtrlTagAdd);

    // MIXER UI
    #include "../MPA Code/MixerUI.h"

        // KEYBOARD UI
#include "../MPA Code/KeyboardUI.h"

    // RESIZE CONTROLS ////////////////////////////////////////////////////////////////////////////////////////////////

    #include "../MPA Code/Resize.h" 
  
    bitmap = pGraphics->LoadBitmap(FN_MIDIMONITOR, 2);
    IBSwitchControl *presetUI = new IBSwitchControl(724, 9, bitmap, kNoParameter);
    pGraphics->AttachControl(presetUI, kCtrlTagMidiMonHide, "");
    presetUI->SetActionFunction(resizeFunc);

    bitmap = pGraphics->LoadBitmap(FN_MIXER, 2); // MIXER UI
    IBSwitchControl *mixerUICtrl = new IBSwitchControl(647, 9, bitmap, kNoParameter);
    pGraphics->AttachControl(mixerUICtrl, kCtrlTagMixerHide, "");
    mixerUICtrl->SetActionFunction(resizeFunc);
  
    bitmap = pGraphics->LoadBitmap(FN_KEYB, 2);
    IBSwitchControl *keybCtrl = new IBSwitchControl(570, 9, bitmap, kNoParameter);
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
    IBButtonControl* clearCtrl = new IBButtonControl(HS_W + 64, 469, bitmap, [&](IControl*) {mMidiLogger->Clear(); /*mMidiLoggerBuf.Clear();*/ });
    pGraphics->AttachControl(clearCtrl, kCtrlTagClear, "midiMonitor");

    mMidiLogger = new MidiMonitor(IRECT(HS_W+16, 379, HS_W+201, 454), "", "", IText(12, COLOR_BLACK, "Calibri", EAlign::Near), COLOR_WHITE);
    pGraphics->AttachControl(mMidiLogger, kCtrlTagMidiLogger, "midiMonitor");

    bitmap = pGraphics->LoadBitmap(FN_SLIDER, 1);
    pGraphics->AttachControl(new IBSliderControlScroll(HS_W + 210, 378, 75, -1, bitmap), kCtrlSliderMidiMon1);
    pGraphics->GetControlWithTag(kCtrlSliderMidiMon1)->SetActionFunction([&](IControl* ctrl) {mMidiLogger->setEntrypointerOffset(1. - ctrl->GetValue()); });
    pGraphics->GetControlWithTag(kCtrlSliderMidiMon1)->SetValue(1.);

    bitmap = pGraphics->LoadBitmap(FN_RECALL, 1);
    IBButtonControl* RecallCtrl = new IBButtonControl(HS_W + 6, 321, bitmap, [&](IControl*) {});
    RecallCtrl->SetActionFunction([&](IControl* ctrl) {
      mPresetList->mActiveRow = mPresetList->mSelectedRow;
      GetUI()->GetControlWithTag(kCtrlProgram)->SetValue((double)mPresetList->mActiveRow / (mPresetList->maxLogSamples - 1.));
      GetUI()->GetControlWithTag(kCtrlProgram)->SetDirty();
      });
    pGraphics->AttachControl(RecallCtrl, -1, "midiMonitor");

    bitmap = pGraphics->LoadBitmap(FN_OVERWRITE, 1);
    IBButtonControl* overwriteCtrl = new IBButtonControl(HS_W+85, 321, bitmap, [&](IControl* pCaller)
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
    IBButtonControl* resetCtrl = new IBButtonControl(HS_W + 164, 321, bitmap,

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

    mPresetList = new PresetList(IRECT(HS_W+16, 97, HS_W+201, 310), 16, "", "", IText(12, COLOR_BLACK, "Calibri", EAlign::Near), COLOR_WHITE);
    pGraphics->AttachControl(mPresetList, kCtrlTagPresetList, "presetList");


    WDL_String presetnames[50];// = { "sdf","dsf" };
    presetnames[0].Set("sdf");

    for (int k = 0; k < 50; k++) {
      mPresetList->addItem(presetname[k]);
    }

    bitmap = pGraphics->LoadBitmap(FN_SLIDER, 1);
    pGraphics->AttachControl(new IBSliderControlScroll(HS_W + 210, 95, 214, -1, bitmap), kCtrlSliderPresetList);
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

    // Program Change
    IText t(12, COLOR_WHITE, "Calibrib");
    t.mTextEntryFGColor = COLOR_WHITE;
    t.mTextEntryBGColor = COLOR_BLACK;
    captionCtrl = new ICaptionControl(IRECT(HS_W+149, 37, HS_W+211, 59), kParamProgram, t, COLOR_BLACK, true);
    captionCtrl->SetActionFunction([&](IControl*) {
      mPresetList->setActiveRow(GetParam(kParamProgram)->Value());
      });
    pGraphics->AttachControl(captionCtrl, kCtrlProgram, "");

    bitmap = pGraphics->LoadBitmap(FN_PLUS);
    pGraphics->AttachControl(new IBButtonControl(HS_W +211, 36, bitmap, [&](IControl*) {
      captionCtrl->SetValue(GetParam(kParamProgram)->ToNormalized(GetParam(kParamProgram)->Value()+1));
      captionCtrl->SetDirty();
      }
    ), -1, "");

    bitmap = pGraphics->LoadBitmap(FN_MINUS);
    pGraphics->AttachControl(new IBButtonControl(HS_W+125, 36, bitmap, [&](IControl*) {

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
    IBButtonControl* loadButton = new IBButtonControl(HS_W+ 125, 6, bitmap, [&](IControl*) {
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
      }

      GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(true);
      GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMS)->Hide(true);
      GetUI()->GetControlWithTag(kCtrlTagFaderBg1)->Hide(true);

      GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(true);
      GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMS)->Hide(true);
      GetUI()->GetControlWithTag(kCtrlTagFaderBg2)->Hide(true);
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

void Prodyssey ::OnUIClose() {
  if(GetParam(kParamUserFactory)->Value() == 0) activeRowFactory = mPresetList->mActiveRow;
  if (GetParam(kParamUserFactory)->Value() == 1) activeRowUser = mPresetList->mActiveRow;

  for (auto r = 0; r < mMidiLogger->maxLogSamples; r++) {
    for (auto c = 0; c < mMidiLogger->numColumns; c++) {
      mStrBufSave[r][c] = mMidiLogger->mStrBuf[r][c];
    }
  }
  mEntryPtrSave = mMidiLogger->mEntryPointer;
}

void Prodyssey::OnUIOpen() {

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
// dino->Control.OnMidi->Onparamchange->Processmidi->sendMidi (schlecht)
// onparamChange->ProcessMidi->SendMidi (gut)
void Prodyssey::ProcessMidiMsg(const IMidiMsg& msg)
{
  TRACE;

#include "../MPA Code/ProcessMidi.h"
}

void Prodyssey::OnParamChange(int paramIdx)
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
      msg.mData2 = 0x02;
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
      msg.mData2 = 0x02;
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
    
    if(GetUI() && GetUI()->GetControlWithTag(kCtrlMidiActive)) GetUI()->GetControlWithTag(kCtrlMidiActive)->SetValueFromUserInput(0.);

    if (GetParam(kParamUserFactory)->Value() == 0) { // Factory
      msg.Clear();
      msg.mStatus = mChannel | (IMidiMsg::kControlChange << 4);
      msg.mData1 = 0x00;
      msg.mData2 = 0x02;
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
      msg.mData2 = 0x02;
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
      if (GetUI()->GetControlWithTag(kCtrlTagAdd)->GetValue() == 1) {
        if (GetParam(paramIdx)->Value() == 0) {
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(true);
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMS)->Hide(false);
          GetUI()->GetControlWithTag(kCtrlTagFaderBg1)->Hide(false);

        }
        else {
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(false);
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
        }
        else {
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(false);
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

  return SerializeParams(chunk);
}

// this over-ridden method is called when the host is trying to load the plug-in state and you need to unpack the data into your algorithm
// HIER KÖNNEN KEINE CONTROLS GEUPDATED WERDEN; DA MGRAPHICS NOCH NICHT EXISTIERT!!!!
int Prodyssey::UnserializeState(const IByteChunk& chunk, int startPos) {

  TRACE;

  return UnserializeParams(chunk, startPos);
}
#endif
