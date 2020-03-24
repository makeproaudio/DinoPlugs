#include "Minimax.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"
#include "json.hpp"
#include <fstream>

Minimax::Minimax(IPlugInstanceInfo instanceInfo)
: IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo)
{

  presetname[0 ].Set("00: Tarkus");
  presetname[1].Set("01: Fat Bastard");
  presetname[2].Set("02: Eary Night");
  presetname[3].Set("03: String Machine");
  presetname[4].Set("04: Synth Brass");
  presetname[5].Set("05: Bells And Birds");
  presetname[6].Set("06: Water Bass");
  presetname[7].Set("07: Soft Bass");
  presetname[8].Set("08: Liquid Steps");
  presetname[9].Set("09: ResoFat");
  presetname[10].Set("10: Subby Dubby");
  presetname[11].Set("11: To Be");
  presetname[12].Set("12: Sexy Boy");
  presetname[13].Set("13: Down Low");
  presetname[14].Set("14: Digital Age");
  presetname[15].Set("15: Bass Wood Winds");
  presetname[16].Set("16: Beyond Forever");
  presetname[17].Set("17: The Cave");
  presetname[18].Set("18: RadioPhonic");
  presetname[19].Set("19: Fresh Lead");
  presetname[20].Set("20: Funny Rascal");
  presetname[21].Set("21: X Files");
  presetname[22].Set("22: Phasing Lead");
  presetname[23].Set("23: Broke");
  presetname[24].Set("24: Father Fungus");
  presetname[25].Set("25: Open Cycle");
  presetname[26].Set("26: Egg Lead");
  presetname[27].Set("27: Fusion Lead");
  presetname[28].Set("28: Prodigy");
  presetname[29].Set("29: Shiny Plato");
  presetname[30].Set("30: Clown Lead");
  presetname[31].Set("31: Zamphir");
  presetname[32].Set("32: Fruit Fly Lead");
  presetname[33].Set("33: Rubber Ducky");
  presetname[34].Set("34: Vintage 5ths");
  presetname[35].Set("35: Synced FM");
  presetname[36].Set("36: Sine Lead");
  presetname[37].Set("37: A.I.");
  presetname[38].Set("38: Lucky Man");
  presetname[39].Set("39: Clicker");
  presetname[40].Set("40: Pancho");
  presetname[41].Set("41: Overtone Pinner");
  presetname[42].Set("42: Warm Pad");
  presetname[43].Set("43: Chease Cake");
  presetname[44].Set("44: Silver Drops");
  presetname[45].Set("45: Mandoline");
  presetname[46].Set("46: Fixed Formant");
  presetname[47].Set("47: Mr. Smart");
  presetname[48].Set("48: Agties");
  presetname[49].Set("49: Hollow world");

   // MIXER UI
  #include "../MPA Code/GlobalParamInit.h" 

  GetParam(kParamBendRange)->InitInt("Bend Range", 0, 0, 24);
  GetParam(kParamKeybModeRetrig)->InitEnum("KYB Trig Mode",0,2);
  GetParam(kParamKeybModeLowNote)->InitEnum("KYB Note Mode",0,2);
  GetParam(kParamKeybModeSingle)->InitEnum("KYB Poly Mode",0,2);
  GetParam(kParamPitchWheel)->InitDouble("Pitch Wheel",0,0,1,0.001);

  GetParam(kParamMasterTune)->InitDouble("Master Tune",0,-2.5,2.5,0.001);
  GetParam(kParamGlide)->InitDouble("Glide", 0, 0, 10, 0.001);
  GetParam(kParamModMix)->InitDouble("Mod Mix", 0, 0, 10, 0.001);
  GetParam(kParamOsc2Tune)->InitDouble("Tune OSC 2", 0, -10, 10, 0.001);
  GetParam(kParamOsc3Tune)->InitDouble("Tune OSC 3", 0, -10, 10, 0.001);
  GetParam(kParamOsc1Volume)->InitDouble("Volume OSC 1", 0, 0, 10, 0.001);
  GetParam(kParamOsc2Volume)->InitDouble("Volume OSC 2", 0, 0, 10, 0.001);
  GetParam(kParamOsc3Volume)->InitDouble("Volume OSC 3", 0, 0, 10, 0.001);
  GetParam(kParamFeedbackLevel)->InitDouble("FB Level", 0, 0, 10, 0.001);
  GetParam(kParamNoiseVolume)->InitDouble("Volume Noise", 0, 0, 10, 0.001);
  GetParam(kParamFilterCutoff)->InitDouble("Filter Cutoff", 0, -5, 5, 0.001);
  GetParam(kParamFilterEmphasis)->InitDouble("Filter Emphasis", 0, 0, 10, 0.001);
  GetParam(kParamFilterContour)->InitDouble("Filter Contour", 0, 0, 10, 0.001);
  GetParam(kParamFilterAttack)->InitDouble("Filter Attack", 0, -0,1, 0.001);
  GetParam(kParamFilterDecay)->InitDouble("Filter Decay", 0, 0,1, 0.001);
  GetParam(kParamFilterSustain)->InitDouble("Filter Sustain", 0, 0, 10, 0.001);
  GetParam(kParamVcaAttack)->InitDouble("VCA Attack", 0, 0,1, 0.001);
  GetParam(kParamVcaDecay)->InitDouble("VCA Decay", 0, 0, 1, 0.001);
  GetParam(kParamVcaSustain)->InitDouble("VCA Sustain", 0, 0, 10, 0.001);
  GetParam(kParamVolume)->InitDouble("Volume", 0, 0, 10, 0.001);
  GetParam(kParamVelocity)->InitDouble("Velocity", 0, 0, 10, 0.001);
  GetParam(kParamOutputVelocity)->InitDouble("Output Velocity", 0, 0, 10, 0.001);
  GetParam(kParamMWINT)->InitDouble("MWINT", 0, 0, 10, 0.001);
  GetParam(kParamMWOFFS)->InitDouble("MWOFFS", 0, 0, 10, 0.001);
  GetParam(kParamCvOsc)->InitDouble("CV OSC", 0, -5, 5, 0.001);
  GetParam(kParamCvFilter)->InitDouble("CV Filter", 0, -5, 5, 0.001);
  GetParam(kParamCvLoudness)->InitDouble("CV Loudness", 0, -5, 5, 0.001);

  // 6 Step Knobs
  GetParam(kParamOsc1Range)->InitInt("OSC 1 Range", 0, 0, 5);
  GetParam(kParamOsc2Range)->InitInt("OSC 2 Range", 0, 0, 5);
  GetParam(kParamOsc3Range)->InitInt("OSC 3 Range", 0, 0, 5);
  GetParam(kParamOsc1Waveform)->InitInt("OSC 1 Waveform", 0, 0, 5);
  GetParam(kParamOsc2Waveform)->InitInt("OSC 2 Waveform", 0, 0, 5);
  GetParam(kParamOsc3Waveform)->InitInt("OSC 3 Waveform", 0, 0, 5);

  // Switches
  GetParam(kParamOsc3Control)->InitInt("OSC 3 Waveform", 0, 0, 1);
  GetParam(kParamOscMod)->InitInt("OSC Mod", 0, 0, 1);
  GetParam(kParamFilterMod1)->InitInt("Filter Mod 1", 0, 0, 1);
  GetParam(kParamFilterMod2)->InitInt("Filter Mod 2", 0, 0, 1);
  GetParam(kParamNoiseType)->InitInt("Noise Type", 0, 0, 1);

  GetParam(kParamOsc1)->InitInt("OSC 1", 0, 0, 1);
  GetParam(kParamOsc2)->InitInt("OSC 2", 0, 0, 1);
  GetParam(kParamOsc3)->InitInt("OSC 3", 0, 0, 1);
  GetParam(kParamFeedback)->InitInt("Feedback", 0, 0, 1);
  GetParam(kParamNoise)->InitInt("Noise", 0, 0, 1);

  GetParam(kParamGlideOnOff)->InitInt("Glide On/Off", 0, 0, 1);
  GetParam(kParamDecay)->InitInt("Decay", 0, 0, 1);
 
  paramToCC[kParamMasterTune                     ]=21;     
  paramToCC[kParamGlide                          ]=5;
  paramToCC[kParamModMix                         ]=58;
  paramToCC[kParamOsc2Tune                       ]=72;
  paramToCC[kParamOsc3Tune                       ]=85;
  paramToCC[kParamOsc1Volume                     ]=25;
  paramToCC[kParamOsc2Volume                     ]=26;
  paramToCC[kParamOsc3Volume                     ]=27;
  paramToCC[kParamFeedbackLevel                  ]=36;
  paramToCC[kParamNoiseVolume                    ]=33;
  paramToCC[kParamFilterCutoff                   ]=74;
  paramToCC[kParamFilterEmphasis                 ]=71;
  paramToCC[kParamFilterContour                  ]=73;
  paramToCC[kParamFilterAttack                   ]=17;
  paramToCC[kParamFilterDecay                    ]=18;
  paramToCC[kParamFilterSustain                  ]=19;
  paramToCC[kParamVcaAttack                      ]=13;
  paramToCC[kParamVcaDecay                       ]=14;
  paramToCC[kParamVcaSustain                     ]=15;
  paramToCC[kParamVolume                         ]=11;
  paramToCC[kParamVelocity                       ]=84;
  paramToCC[kParamOutputVelocity                 ]=81;
  paramToCC[kParamBendRange                      ]=24;
  paramToCC[kParamMWINT                          ]=56;
  paramToCC[kParamMWOFFS                         ]=57;
  paramToCC[kParamCvOsc                          ]=23;
  paramToCC[kParamCvFilter                       ]=50;
  paramToCC[kParamCvLoudness                     ]=51;
  paramToCC[kParamOsc1Range                      ]=79;
  paramToCC[kParamOsc2Range                      ]=16;
  paramToCC[kParamOsc3Range                      ]=20;
  paramToCC[kParamOsc1Waveform                   ]=80;
  paramToCC[kParamOsc2Waveform                   ]=83;
  paramToCC[kParamOsc3Waveform                   ]=86;
  paramToCC[kParamOsc3Control                    ]=87;
  paramToCC[kParamOscMod                         ]=22;
  paramToCC[kParamFilterMod1                     ]=47;
  paramToCC[kParamFilterMod2                     ]=48;
  paramToCC[kParamKeybControl                    ]=49;
  paramToCC[kParamNoiseType                      ]=35;
  paramToCC[kParamOsc1                           ]=28;
  paramToCC[kParamOsc2                           ]=29;
  paramToCC[kParamOsc3                           ]=30;
  paramToCC[kParamFeedback                       ]=37;
  paramToCC[kParamNoise                          ]=34;
  paramToCC[kParamGlideOnOff                     ]=65;
  paramToCC[kParamDecay                          ]=59;
  paramToCC[kParamKeybModeRetrig                 ]=60;
  paramToCC[kParamKeybModeLowNote                ]=61;
  paramToCC[kParamKeybModeSingle                 ]=68;
  paramToCC[kParamPitchWheel                     ]=1;

  paramToMsgType[kParamMasterTune                     ]=0;
  paramToMsgType[kParamGlide                          ]=0;
  paramToMsgType[kParamModMix                         ]=0;
  paramToMsgType[kParamOsc2Tune                       ]=0;
  paramToMsgType[kParamOsc3Tune                       ]=0;
  paramToMsgType[kParamOsc1Volume                     ]=0;
  paramToMsgType[kParamOsc2Volume                     ]=0;
  paramToMsgType[kParamOsc3Volume                     ]=0;
  paramToMsgType[kParamFeedbackLevel                  ]=0;
  paramToMsgType[kParamNoiseVolume                    ]=0;
  paramToMsgType[kParamFilterCutoff                   ]=0;
  paramToMsgType[kParamFilterEmphasis                 ]=0;
  paramToMsgType[kParamFilterContour                  ]=0;
  paramToMsgType[kParamFilterAttack                   ]=0;
  paramToMsgType[kParamFilterDecay                    ]=0;
  paramToMsgType[kParamFilterSustain                  ]=0;
  paramToMsgType[kParamVcaAttack                      ]=0;
  paramToMsgType[kParamVcaDecay                       ]=0;
  paramToMsgType[kParamVcaSustain                     ]=0;
  paramToMsgType[kParamVolume                         ]=0;
  paramToMsgType[kParamVelocity                       ]=0;
  paramToMsgType[kParamOutputVelocity                 ]=0;
  paramToMsgType[kParamBendRange                      ]=0;
  paramToMsgType[kParamMWINT                          ]=0;
  paramToMsgType[kParamMWOFFS                         ]=0;
  paramToMsgType[kParamCvOsc                          ]=0;
  paramToMsgType[kParamCvFilter                       ]=0;
  paramToMsgType[kParamCvLoudness                     ]=0;                                                   
  paramToMsgType[kParamOsc1Range                      ]=0;
  paramToMsgType[kParamOsc2Range                      ]=0;
  paramToMsgType[kParamOsc3Range                      ]=0;
  paramToMsgType[kParamOsc1Waveform                   ]=0;
  paramToMsgType[kParamOsc2Waveform                   ]=0;
  paramToMsgType[kParamOsc3Waveform                   ]=0;                                                     
  paramToMsgType[kParamOsc3Control                    ]=0;                                            
  paramToMsgType[kParamOscMod                         ]=0;
  paramToMsgType[kParamFilterMod1                     ]=0;
  paramToMsgType[kParamFilterMod2                     ]=0;
  paramToMsgType[kParamKeybControl                    ]=0;                                                
  paramToMsgType[kParamNoiseType                      ]=0;                                                 
  paramToMsgType[kParamOsc1                           ]=0;
  paramToMsgType[kParamOsc2                           ]=0;
  paramToMsgType[kParamOsc3                           ]=0;
  paramToMsgType[kParamFeedback                       ]=0;
  paramToMsgType[kParamNoise                          ]=0;                             
  paramToMsgType[kParamGlideOnOff                     ]=0;
  paramToMsgType[kParamDecay                          ]=0;
  paramToMsgType[kParamKeybModeRetrig                 ]=0;
  paramToMsgType[kParamKeybModeLowNote                ]=0;
  paramToMsgType[kParamKeybModeSingle                 ]=0;
  paramToMsgType[kParamPitchWheel                     ]=0;
  
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

    bitmap = pGraphics->LoadBitmap(FN_HEADER);
     IControl* mainPanelHeadCtrl = new IBitmapControl(0, 338, bitmap, kNoParameter);
    pGraphics->AttachControl(mainPanelHeadCtrl);
    
    bitmap = pGraphics->LoadBitmap(FN_MIDIMONBACK);
    IControl* midiCtrlBack = new IBitmapControl(HS_W, 0, bitmap, kNoParameter);
    pGraphics->AttachControl(midiCtrlBack, kCtrlTagMidiBack, "midiMonitor");

    bitmap = pGraphics->LoadBitmap(FN_PANELMAIN);
    IControl* mainPanelCtrl = new IBitmapControl(6, 29, bitmap, kNoParameter);
    pGraphics->AttachControl(mainPanelCtrl, -1, "main");

    bitmap = pGraphics->LoadBitmap(FN_PANELADD);
    IControl* addPanelCtrl = new IBitmapControl(6, 29, bitmap, kNoParameter);
    pGraphics->AttachControl(addPanelCtrl, -1, "add");
    if (strcmp(addPanelCtrl->GetGroup(), "add") == 0) addPanelCtrl->Hide(true);

    // KNOBS
    bitmap = pGraphics->LoadBitmap(FN_KNOB32, 33);

    int offx = 6;
    int offy = -6;

    pGraphics->AttachControl(new IBKnobControlMidi(54, 72, bitmap, kParamMasterTune), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(20, 161, bitmap, kParamGlide), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(92, 161, bitmap, kParamModMix), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(278, 165, bitmap, kParamOsc2Tune), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(278, 259, bitmap, kParamOsc3Tune), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 430, offy + 86, bitmap, kParamOsc1Volume), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 430, offy + 168, bitmap, kParamOsc2Volume), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 430, offy + 253, bitmap, kParamOsc3Volume), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 548, offy + 127, bitmap, kParamFeedbackLevel), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 548, offy + 209, bitmap, kParamNoiseVolume), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(681, offy + 88, bitmap, kParamFilterCutoff), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 750, offy + 88, bitmap, kParamFilterEmphasis), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 820, offy + 88, bitmap, kParamFilterContour), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(681, offy + 171, bitmap, kParamFilterAttack), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 750, offy + 171, bitmap, kParamFilterDecay), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 820, offy + 171, bitmap, kParamFilterSustain), -1, "main");

    pGraphics->AttachControl(new IBKnobControlMidi(681, offy + 264, bitmap, kParamVcaAttack), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 750, offy + 264, bitmap, kParamVcaDecay), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 820, offy + 264, bitmap, kParamVcaSustain), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 896, offy + 86, bitmap, kParamVolume), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 896, offy + 174, bitmap, kParamVelocity), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 896, offy + 264, bitmap, kParamOutputVelocity), -1, "main");

    std::function<double(double)> mappingFunc2 = [](double midiVal) {return midiVal*127./24.; };
    pGraphics->AttachControl(new IBKnobControlMidi(53, 73, bitmap, kParamBendRange, mappingFunc2), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(19, 161, bitmap, kParamMWINT), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(93, 161, bitmap, kParamMWOFFS), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(173, 72, bitmap, kParamCvOsc), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(173, 159, bitmap, kParamCvFilter), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(173, 247, bitmap, kParamCvLoudness), -1, "add");

    offx = 0;
    offy = 0;
    pGraphics->AttachControl(new IBKnobControlMidi(265, 220, bitmap, kParamChorusPhase), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(269, 101, bitmap, kParamChorusRate), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(357, 156, bitmap, kParamChorusDepth), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(354, 247, bitmap, kParamChorusFeedback), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(437, 157, bitmap, kParamChorusWet), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(530, 101, bitmap, kParamDelayTimeLMS), kCtrlTagDelayTimeLMS, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(530, 232, bitmap, kParamDelayTimeRMS), kCtrlTagDelayTimeRMS, "add");

    pGraphics->AttachControl(new IBKnobControlMidi(offx + 609, 101, bitmap, kParamDelayFeedbackLeft), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 609, 232, bitmap, kParamDelayFeedbackLeft), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 691, 101, bitmap, kParamDelayHidampLeft), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 691, 232, bitmap, kParamDelayHidampRight), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 769, 101, bitmap, kParamDelayLevelLeft), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 769, 232, bitmap, kParamDelayLevelRight), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(897, 158, bitmap, kParamDelayWet), -1, "add");

    // SWITCHES 
    bitmap = pGraphics->LoadBitmap(FN_KNOB6, 6, true);
    std::function<double(double)> mappingRange = [](double midiVal) {return midiVal * 127./110.; };
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 190, offy + 69, bitmap, kParamOsc1Range, mappingRange), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 190, offy + 156, bitmap, kParamOsc2Range, mappingRange), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 190, offy + 249, bitmap, kParamOsc3Range, mappingRange), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 353, offy + 69, bitmap, kParamOsc1Waveform, mappingRange), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 353, offy + 156, bitmap, kParamOsc2Waveform, mappingRange), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 353, offy + 249, bitmap, kParamOsc3Waveform, mappingRange), -1, "main");

    bitmap = pGraphics->LoadBitmap(FN_KNOB2, 2, true);
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 352, offy + 69, bitmap, kParamFlangerChorus, NULL, EDirection::Vertical, 1.), -1, "add");

    bitmap = pGraphics->LoadBitmap(FN_SWITCHREDV, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 164, offy + 278, bitmap, kParamOsc3Control), -1, "main");

    bitmap = pGraphics->LoadBitmap(FN_SWITCHREDHBYPASS, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(483, 316, bitmap, kParamEffectBypass), -1, "add");

    bitmap = pGraphics->LoadBitmap(FN_SWITCHREDH, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 623, offy + 175, bitmap, kParamKeybControl), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 623, offy + 92, bitmap, kParamFilterMod1), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 623, offy + 137, bitmap, kParamFilterMod2), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 136, offy + 100, bitmap, kParamOscMod), -1, "main");

    
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 611, offy + 172, bitmap, kParamDelayCrossDual), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 840, offy + 110, bitmap, kParamDelayUnitLeft), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 840, offy + 243, bitmap, kParamDelayUnitRight), -1, "add");

    bitmap = pGraphics->LoadBitmap(FN_SWITCHBLUEV, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 614, offy + 214, bitmap, kParamNoiseType), -1, "main");

    bitmap = pGraphics->LoadBitmap(FN_SWITCHBLUEH, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 497, offy + 92, bitmap, kParamOsc1), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 497, offy + 175, bitmap, kParamOsc2), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 497, offy + 260, bitmap, kParamOsc3), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 497, offy + 134, bitmap, kParamFeedback), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 497, offy + 216, bitmap, kParamNoise), -1, "main");

    bitmap = pGraphics->LoadBitmap(FN_SWITCHSILVERH, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 63, offy + 240, bitmap, kParamGlideOnOff), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 63, offy + 268, bitmap, kParamDecay), -1, "main");

    bitmap = pGraphics->LoadBitmap(FN_SWITCHSILVERH, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 63, offy + 254, bitmap, kParamKeybModeRetrig), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 63, offy + 225, bitmap, kParamKeybModeLowNote), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 63, offy + 284, bitmap, kParamKeybModeSingle), -1, "add");

    bitmap = pGraphics->LoadBitmap(FN_PITCHWHEEL14, 14, true);
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 108, offy + 230, bitmap, kParamPitchWheel), -1, "add");

    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(108, 40, 138, 55), kParamBendRange, DEFAULT_TEXT, COLOR_MID_GRAY, true, mappingFunc2), -1, "add");

    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(268, 154, 307, 170), kParamChorusRate, DEFAULT_TEXT, COLOR_MID_GRAY, true), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(268, 274, 307, 290), kParamChorusPhase, DEFAULT_TEXT, COLOR_MID_GRAY, true), -1, "add");

    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(832, 168, 878, 186), kParamMidiClockBpm, DEFAULT_TEXT, COLOR_MID_GRAY, true), -1, "add");

    bitmap = pGraphics->LoadBitmap(FN_KNOBBG);
    IControl* delayTimeSkalaL = new IBitmapControl(503, 70, bitmap, kNoParameter);
    pGraphics->AttachControl(delayTimeSkalaL, kCtrlTagSkalaL, "add");

    IControl* delayTimeSkalaR = new IBitmapControl(503, 200, bitmap, kNoParameter);
    pGraphics->AttachControl(delayTimeSkalaR, kCtrlTagSkalaR, "add");


    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(528, 114, 577, 131), kParamDelayTimeLBPM, DEFAULT_TEXT, COLOR_MID_GRAY, true), kCtrlTagDelayTimeLBPM, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(528, 245, 577, 262), kParamDelayTimeRBPM, DEFAULT_TEXT, COLOR_MID_GRAY, true), kCtrlTagDelayTimeRBPM, "add");
   
    bitmap = pGraphics->LoadBitmap(FN_MIDIACTIVE, 2);
    pGraphics->AttachControl(new IBitmapControl(166, 4, bitmap), kCtrlMidiActive, "");
    pGraphics->GetControlWithTag(kCtrlMidiActive)->SetActionFunction([&](IControl *ctrl)
      {
        if (ctrl->GetValue() == 1) mMidiActive = true;
        else mMidiActive = false;
        if (GetUI()) for (auto c = 0; c < GetUI()->NControls(); c++) GetUI()->GetControl(c)->SetWantsMidi(mMidiActive);      
      }
    );
  
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
            pCaller->GetUI()->GetControlWithTag(kCtrlTagSkalaL)->Hide(true);

          }
          else {
          pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(false);
          pCaller->GetUI()->GetControlWithTag(kCtrlTagSkalaL)->Hide(false);
          pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMS)->Hide(true);
          }
        }

        if (pCaller->GetUI()->GetControlWithTag(kCtrlTagAdd)->GetValue() == 1) {
          if (pCaller->GetDelegate()->GetParam(kParamDelayUnitRight)->Value() == 0) {
          pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(true);
          pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMS)->Hide(false);
          pCaller->GetUI()->GetControlWithTag(kCtrlTagSkalaR)->Hide(true);
          }
          else {
           pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(false);
           pCaller->GetUI()->GetControlWithTag(kCtrlTagSkalaR)->Hide(false);
           pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMS)->Hide(true);
          }
        }

      }
    };

    bitmap = pGraphics->LoadBitmap(FN_MAIN, 2);
    IBSwitchControlFunc *mainCtrl = new IBSwitchControlFunc(10, 4, bitmap, windowFunc, kNoParameter);
    pGraphics->AttachControl(mainCtrl, kCtrlTagMain);
    mainCtrl->SetValue(1);
    bitmap = pGraphics->LoadBitmap(FN_ADD, 2);
    IBSwitchControlFunc *addCtrl = new IBSwitchControlFunc(76, 4, bitmap, windowFunc, kNoParameter);
    pGraphics->AttachControl(addCtrl, kCtrlTagAdd);

    // MIXER UI
#include "../MPA Code/MixerUI.h" 

    // KEYBOARD UI
#include "../MPA Code/KeyboardUI.h"

// RESIZE CONTROLS ////////////////////////////////////////////////////////////////////////////////////////////////

#include "../MPA Code/Resize.h" 

    bitmap = pGraphics->LoadBitmap(FN_MIDIMONITOR, 2);
    IBSwitchControl *presetUI = new IBSwitchControl(400, 4, bitmap, kNoParameter);
    pGraphics->AttachControl(presetUI, kCtrlTagMidiMonHide, "");
    presetUI->SetActionFunction(resizeFunc);

    bitmap = pGraphics->LoadBitmap(FN_MIXER, 2); // MIXER UI
    IBSwitchControl *mixerUICtrl = new IBSwitchControl(322, 4, bitmap, kNoParameter);
    pGraphics->AttachControl(mixerUICtrl, kCtrlTagMixerHide, "");
    mixerUICtrl->SetActionFunction(resizeFunc);

    bitmap = pGraphics->LoadBitmap(FN_KEYB, 2);
    IBSwitchControl *keybCtrl = new IBSwitchControl(243, 4, bitmap, kNoParameter);
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
    IBButtonControl* clearCtrl = new IBButtonControl(HS_W + 64, 351, bitmap, [&](IControl*) {mMidiLogger->Clear(); });
    pGraphics->AttachControl(clearCtrl, kCtrlTagClear, "midiMonitor");

    mMidiLogger = new MidiMonitor(IRECT(HS_W + 14, 379-118, HS_W + 196, 454-118), "", "", IText(12, COLOR_BLACK, "Calibri", EAlign::Near), COLOR_WHITE);
    pGraphics->AttachControl(mMidiLogger, kCtrlTagMidiLogger, "midiMonitor");

    bitmap = pGraphics->LoadBitmap(FN_SLIDER, 1);
    pGraphics->AttachControl(new IBSliderControlScroll(HS_W + 210, 378 -118, 75, -1, bitmap), kCtrlSliderMidiMon1);
    pGraphics->GetControlWithTag(kCtrlSliderMidiMon1)->SetActionFunction([&](IControl* ctrl) {mMidiLogger->setEntrypointerOffset(1. - ctrl->GetValue()); });
    pGraphics->GetControlWithTag(kCtrlSliderMidiMon1)->SetValue(1.);

    bitmap = pGraphics->LoadBitmap(FN_RECALL, 1);
    IBButtonControl* RecallCtrl = new IBButtonControl(HS_W + 6, 321-118, bitmap, [&](IControl*) {});
    RecallCtrl->SetActionFunction([&](IControl* ctrl) {
      mPresetList->mActiveRow = mPresetList->mSelectedRow;
      GetUI()->GetControlWithTag(kCtrlProgram)->SetValue((double)mPresetList->mActiveRow / (mPresetList->maxLogSamples - 1.));
      GetUI()->GetControlWithTag(kCtrlProgram)->SetDirty();
      });
    pGraphics->AttachControl(RecallCtrl, -1, "midiMonitor");

        bitmap = pGraphics->LoadBitmap(FN_OVERWRITE, 1);
    IBButtonControl* overwriteCtrl = new IBButtonControl(HS_W+85, 321-118, bitmap, [&](IControl* pCaller)
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
    IBButtonControl* resetCtrl = new IBButtonControl(HS_W + 164, 321-118, bitmap,

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

    mPresetList = new PresetList(IRECT(HS_W + 14, 97, HS_W + 196, 310-118), 8, "", "", IText(12, COLOR_BLACK, "Calibri", EAlign::Near), COLOR_WHITE);
    pGraphics->AttachControl(mPresetList, kCtrlTagPresetList, "presetList");

    for (int k = 0; k < 50; k++) {
		  mPresetList->addItem(presetname[k]);
	  }

    bitmap = pGraphics->LoadBitmap(FN_SLIDER, 1);
    pGraphics->AttachControl(new IBSliderControlScroll(HS_W + 210, 95, 214-118, -1, bitmap), kCtrlSliderPresetList);
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
      for (auto k = 0; k < GetUI()->NControls(); k++) {
        if (strcmp(GetUI()->GetControl(k)->GetGroup(), "add") == 0) {
          GetUI()->GetControl(k)->Hide(true);
        }
      }

     GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(true);
      GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMS)->Hide(true);
      GetUI()->GetControlWithTag(kCtrlTagSkalaL)->Hide(true);

      GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(true);
      GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMS)->Hide(true);
      GetUI()->GetControlWithTag(kCtrlTagSkalaR)->Hide(true);
    }
  };
  
#endif
}

#if IPLUG_DSP
void Minimax::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
  const int nChans = NOutChansConnected();
  
  for (auto s = 0; s < nFrames; s++) {
    for (auto c = 0; c < nChans; c++) {
      outputs[c][s] = 0.;
    }
  }
}

void Minimax::OnIdle()
{
  mMidiLoggerSender.TransmitData(*this);
}

void Minimax::OnReset()
{
}

void Minimax ::OnUIClose() {
  if(GetParam(kParamUserFactory)->Value() == 0) activeRowFactory = mPresetList->mActiveRow;
  if (GetParam(kParamUserFactory)->Value() == 1) activeRowUser = mPresetList->mActiveRow;

  for (auto r = 0; r < mMidiLogger->maxLogSamples; r++) {
    for (auto c = 0; c < mMidiLogger->numColumns; c++) {
      mStrBufSave[r][c] = mMidiLogger->mStrBuf[r][c];
    }
  }
  mEntryPtrSave = mMidiLogger->mEntryPointer;
}

void Minimax::OnUIOpen() {

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
void Minimax::ProcessMidiMsg(const IMidiMsg& msg)
{
  TRACE;

#include "../MPA Code/ProcessMidi.h"
}

void Minimax::OnParamChange(int paramIdx)
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
    case kParamDelayTimeLBPM:
    case kParamDelayTimeRBPM:
      msg.mData2 = GetParam(paramIdx)->Value();
      break;
    case kParamMidiClockBpm:
      msg.mData2 = GetParam(paramIdx)->Value()-72;
      break;
    }

    switch (paramIdx) {
    case kParamOsc1Range:
    case kParamOsc2Range:
    case kParamOsc3Range:
    case kParamOsc1Waveform:
    case kParamOsc2Waveform:
    case kParamOsc3Waveform:
      msg.mData2 = GetParam(paramIdx)->Value()*22;
      break;
    }


    if(paramIdx == kParamBendRange) msg.mData2 = GetParam(paramIdx)->Value();

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
      msg.mData2 = 0x00;
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
      msg.mData2 = 0x00;
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
      msg.mData2 = 0x00;
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
      msg.mData2 = 0x00;
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
          GetUI()->GetControlWithTag(kCtrlTagSkalaL)->Hide(true);

        }
        else {
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(false);
          GetUI()->GetControlWithTag(kCtrlTagSkalaL)->Hide(false);
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
          GetUI()->GetControlWithTag(kCtrlTagSkalaR)->Hide(true);
        }
        else {
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(false);
          GetUI()->GetControlWithTag(kCtrlTagSkalaR)->Hide(false);
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMS)->Hide(true);
        }
      }
    }
    break;
      
    default:
      break;
  }
}

bool Minimax::SerializeState(IByteChunk& chunk) const {

  TRACE;

  return SerializeParams(chunk);
}

// this over-ridden method is called when the host is trying to load the plug-in state and you need to unpack the data into your algorithm
// HIER KÖNNEN KEINE CONTROLS GEUPDATED WERDEN; DA MGRAPHICS NOCH NICHT EXISTIERT!!!!
int Minimax::UnserializeState(const IByteChunk& chunk, int startPos) {

  TRACE;

  return UnserializeParams(chunk, startPos);
}
#endif
