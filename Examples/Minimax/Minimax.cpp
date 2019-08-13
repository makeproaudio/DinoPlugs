#include "Minimax.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"


/*void IControl::OnMidi(const IMidiMsg &msg) {
  SetValueFromDelegate(msg.mData2);
}*/

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


  mCurrentPresetPath.Set("Default");


   // MIXER UI
#include "../MPA Code/MixerUIInit.h" 


  GetParam(kParamUserFactory)->InitEnum("Preset Bank", 0, 2, "", 0, "", "Factory Bank", "User Bank");
  GetParam(kParamProgram)->InitInt("Program", 0, 0, 49, "", 0, "");

  GetParam(kParamKeyboardOctave)->InitEnum("Keyb Oct", 3, 7, "", 0, "", "-3","-2","-1","0","+1","+2","+3");

  //GetParam(kParamMidiActive)->InitBool("MIDI Active", true, "");
  GetParam(kParamBendRange)->InitInt("Bend Range", 0, 0, 24);
  GetParam(kParamChorusPhase)->InitInt("Chorus Phase", 0, 0, 180);
  GetParam(kParamChorusRate)->InitDouble("Chorus Rate", 0, 0.01, 20, 0.01, "", 0, "", IParam::ShapePowCurve(6));
  GetParam(kParamMidiClockBpm)->InitInt("MIDI CLK BPM", 72, 72, 199);
  GetParam(kParamDelayTimeLMS)->InitDouble("Delaytime L MS", 1.01, 1.01, 1365.33, 0.01);
  GetParam(kParamDelayTimeRMS)->InitDouble("Delaytime R MS", 1.01, 1.01, 1365.33, 0.01);
  GetParam(kParamDelayTimeLBPM)->InitEnum("Delaytime L BPM", 0, 19, "", 0, "", "1/1", "1/2P","1/2","1/2T","1/4P","1/4","1/4T", "1/8P", "1/8", "1/8T", "1/16P", "1/16", "1/16T", "1/32P", "1/32", "1/32T", "1/64P", "1/64", "1/64T");
  GetParam(kParamDelayTimeRBPM)->InitEnum("Delaytime R BPM", 0, 19, "", 0, "", "1/1", "1/2P", "1/2", "1/2T", "1/4P", "1/4", "1/4T", "1/8P", "1/8", "1/8T", "1/16P", "1/16", "1/16T", "1/32P", "1/32", "1/32T", "1/64P", "1/64", "1/64T");
  GetParam(kParamDelayUnitLeft)->InitEnum("Delay Unit L", 0, 2, "", 0, "", "ms", "Beats");
  GetParam(kParamDelayUnitRight)->InitEnum("Delay Unit R", 0, 2, "", 0, "", "ms", "Beats");
  GetParam(kParamChorusDepth)->InitDouble("Chorus Depth",0,0,1,0.001);
  GetParam(kParamChorusFeedback)->InitDouble("Chorus FB",0,0,1,0.001);
  GetParam(kParamChorusWet)->InitDouble("Chorus Mix",0,0,1,0.001);
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

    paramToCC.fill(-1);

     // MIXER UI
      paramToCC[kParamMixerDrive      ]=93;
      paramToCC[kParamMixerBass       ]=2;
      paramToCC[kParamMixerTreble     ]=5;
      paramToCC[kParamMixerBalance    ]=8;
      paramToCC[kParamMixerLevel      ]=7;
      paramToCC[kParamLAIGain         ]=20;
      paramToCC[kParamLAIBass         ]=22;
      paramToCC[kParamLAITreble       ]=25;
      paramToCC[kParamLAIPan          ]=28;
      paramToCC[kParamLAILevel        ]=29;
      paramToCC[kParamRAIGain         ]=40;
      paramToCC[kParamRAIBass         ]=42;
      paramToCC[kParamRAITreble       ]=45;
      paramToCC[kParamRAIPan          ]=48;
      paramToCC[kParamRAILevel        ]=49;
     // paramToCC[kParamMixerLink       ]=0;
//      paramToCC[kParamMixerBassFreq   ]=4;
      //paramToCC[kParamMixerTrebleFreq ]=7;
//      paramToCC[kParamLAIBassFreq     ]=24;
//      paramToCC[kParamLAITrebleFreq   ]=27;
//      paramToCC[kParamRAIBassFreq     ]=44;
//      paramToCC[kParamRAITrebleFreq   ] = 47;
	  
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
      paramToCC[kParamChorusPhase                    ]=72;
      paramToCC[kParamChorusRate                     ]=71;
      paramToCC[kParamChorusDepth                    ]=73;
      paramToCC[kParamChorusFeedback                 ]=74;
      paramToCC[kParamChorusWet                      ]=91;
      paramToCC[kParamDelayTimeLMS                   ]=81;
      paramToCC[kParamDelayTimeRMS                   ]=91;
      paramToCC[kParamDelayTimeLBPM                  ]=82;
      paramToCC[kParamDelayTimeRBPM                  ]=92;
      paramToCC[kParamDelayFeedbackLeft              ]=119;
      paramToCC[kParamDelayHidampLeft                ]=84;
      paramToCC[kParamDelayLevelLeft                 ]=85;
      paramToCC[kParamDelayFeedbackRight             ]=-1;
      paramToCC[kParamDelayHidampRight               ]=94;
      paramToCC[kParamDelayLevelRight                ]=95;
      paramToCC[kParamDelayWet                       ]=10;
     
      paramToCC[kParamOsc1Range                      ]=79;
      paramToCC[kParamOsc2Range                      ]=16;
      paramToCC[kParamOsc3Range                      ]=20;
      paramToCC[kParamOsc1Waveform                   ]=80;
      paramToCC[kParamOsc2Waveform                   ]=83;
      paramToCC[kParamOsc3Waveform                   ]=86;
 
      paramToCC[kParamFlangerChorus                  ]=75;
    
      paramToCC[kParamOsc3Control                    ]=87;
 
      paramToCC[kParamOscMod                         ]=22;
      paramToCC[kParamFilterMod1                     ]=47;
      paramToCC[kParamFilterMod2                     ]=48;
      paramToCC[kParamKeybControl                    ]=49;
      paramToCC[kParamEffectBypass                   ]=98;
      paramToCC[kParamDelayCrossDual                 ]=90;
      paramToCC[kParamDelayUnitLeft                  ]=86;
      paramToCC[kParamDelayUnitRight                 ]=96;
   
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
      paramToCC[kParamMidiClockBpm                   ]=97;
      paramToCC[kParamPitchWheel                     ]=1;
      //paramToCC[kParamProgram                      ]=0;
                                                   
    paramToMsgType.fill(-1);

     // MIXER UI
    paramToMsgType[kParamMixerDrive] = 0;
    paramToMsgType[kParamMixerBass] = 1;
    paramToMsgType[kParamMixerTreble] = 1;
    paramToMsgType[kParamMixerBalance] = 1;
    paramToMsgType[kParamMixerLevel] = 0;
    paramToMsgType[kParamLAIGain] = 1;
    paramToMsgType[kParamLAIBass] = 1;
    paramToMsgType[kParamLAITreble] =1;
    paramToMsgType[kParamLAIPan] = 1;
    paramToMsgType[kParamLAILevel] = 1;
    paramToMsgType[kParamRAIGain] = 1;
    paramToMsgType[kParamRAIBass] = 1;
    paramToMsgType[kParamRAITreble] = 1;
    paramToMsgType[kParamRAIPan] = 1;
    paramToMsgType[kParamRAILevel] = 1;
//    paramToMsgType[kParamMixerBassFreq] = 1;
    //paramToMsgType[kParamMixerTrebleFreq] = 1;
//    paramToMsgType[kParamLAIBassFreq] = 1;
//    paramToMsgType[kParamLAITrebleFreq] = 1;
//    paramToMsgType[kParamRAIBassFreq] = 1;
//    paramToMsgType[kParamRAITrebleFreq] = 1;
	
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
      paramToMsgType[kParamChorusPhase                    ]=1;
      paramToMsgType[kParamChorusRate                     ]=1;
      paramToMsgType[kParamChorusDepth                    ]=1;
      paramToMsgType[kParamChorusFeedback                 ]=1;
      paramToMsgType[kParamChorusWet                      ]=0;
      paramToMsgType[kParamDelayTimeLMS                   ]=1;
      paramToMsgType[kParamDelayTimeRMS                   ]=1;
      paramToMsgType[kParamDelayTimeLBPM                  ]=1;
      paramToMsgType[kParamDelayTimeRBPM                  ]=1;
      paramToMsgType[kParamDelayFeedbackLeft              ]=0;
      paramToMsgType[kParamDelayHidampLeft                ]=1;
      paramToMsgType[kParamDelayLevelLeft                 ]=1;
      paramToMsgType[kParamDelayFeedbackRight             ]=0;
      paramToMsgType[kParamDelayHidampRight               ]=1;
      paramToMsgType[kParamDelayLevelRight                ]=1;
      paramToMsgType[kParamDelayWet                       ]=0;
                                                            
      paramToMsgType[kParamOsc1Range                      ]=0;
      paramToMsgType[kParamOsc2Range                      ]=0;
      paramToMsgType[kParamOsc3Range                      ]=0;
      paramToMsgType[kParamOsc1Waveform                   ]=0;
      paramToMsgType[kParamOsc2Waveform                   ]=0;
      paramToMsgType[kParamOsc3Waveform                   ]=0;
                                                            
      paramToMsgType[kParamFlangerChorus                  ]=1;
                                                            
      paramToMsgType[kParamOsc3Control                    ]=0;
                                                           
      paramToMsgType[kParamOscMod                         ]=0;
      paramToMsgType[kParamFilterMod1                     ]=0;
      paramToMsgType[kParamFilterMod2                     ]=0;
      paramToMsgType[kParamKeybControl                    ]=0;
      paramToMsgType[kParamEffectBypass                   ]=1;
      paramToMsgType[kParamDelayCrossDual                 ]=1;
      paramToMsgType[kParamDelayUnitLeft                  ]=1;
      paramToMsgType[kParamDelayUnitRight                 ]=1;
                                                          
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
      paramToMsgType[kParamMidiClockBpm                   ]=1;
      paramToMsgType[kParamPitchWheel                     ]=0;

#include "../MPA Code/Init.h"
   

  
#if IPLUG_EDITOR // All UI methods and member variables should be within an IPLUG_EDITOR guard, should you want distributed UI
  mMakeGraphicsFunc = [&]() {
    return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS, 1.);
  };
  
  mLayoutFunc = [&](IGraphics* pGraphics) {
    //pGraphics->AttachCornerResizer(EUIResizerMode::Scale, false);
    //pGraphics->AttachPanelBackground(COLOR_GRAY);
    //pGraphics->HandleMouseOver(true);
    //pGraphics->EnableLiveEdit(true);
    pGraphics->LoadFont("Roboto-Regular", ROBOTTO_FN);
	    pGraphics->LoadFont("Calibrib", CALIBRI_FN);
    pGraphics->LoadFont("Calibri", CALIBRID_FN);
    const IRECT b = pGraphics->GetBounds();

IControl* pBG = new IPanelControl(IRECT(0,0, HSM_W, HSK_H), IColor(255,58,58,58));
    pGraphics->AttachControl(pBG);

    const IRECT controls = b.GetGridCell(1, 2, 2);

    IBitmap bitmap;
	
 bitmap = pGraphics->LoadBitmap(PNGMPA_FN);
    IControl* logoCtrl = new IBitmapControl(HS_W+40, HS_H+28, bitmap, kNoParameter);
    pGraphics->AttachControl(logoCtrl, -1, "");

    bitmap = pGraphics->LoadBitmap(PNGBACK_FN);
    IControl* backCtrl = new IBitmapControl(0,0, bitmap, kNoParameter);
    pGraphics->AttachControl(backCtrl, -1, "");

    bitmap = pGraphics->LoadBitmap(PNGHEADER_FN);
     IControl* mainPanelHeadCtrl = new IBitmapControl(0, 338, bitmap, kNoParameter);
    pGraphics->AttachControl(mainPanelHeadCtrl);
    
    // BITMAPS 
    //bitmap = pGraphics->LoadBitmap(PNGPANELHEAD1_FN);
    //IControl* mainPanelHeadCtrl = new IBitmapControl(0, 0, bitmap, kNoParameter);
    //pGraphics->AttachControl(mainPanelHeadCtrl);

    bitmap = pGraphics->LoadBitmap(PNGMIDIMONBACK_FN);
    IControl* midiCtrlBack = new IBitmapControl(HS_W, 0, bitmap, kNoParameter);
    pGraphics->AttachControl(midiCtrlBack, kCtrlTagMidiBack, "midiMonitor");

    bitmap = pGraphics->LoadBitmap(PNGPANELMAIN_FN);
    IControl* mainPanelCtrl = new IBitmapControl(6, 29, bitmap, kNoParameter);
    pGraphics->AttachControl(mainPanelCtrl, -1, "main");

    bitmap = pGraphics->LoadBitmap(PNGPANELADD_FN);
    IControl* addPanelCtrl = new IBitmapControl(6, 29, bitmap, kNoParameter);
    pGraphics->AttachControl(addPanelCtrl, -1, "add");
    if (strcmp(addPanelCtrl->GetGroup(), "add") == 0) addPanelCtrl->Hide(true);

   

    // KNOBS
    bitmap = pGraphics->LoadBitmap(PNGKNOB32_FN, 33);

    int offx = 6;
    int offy = -6;

    //pGraphics->AttachControl(new IBKnobControlMidi(435, 340, bitmap, kParamMasterVolume), -1, "");
    //pGraphics->AttachControl(new IBKnobControlMidi(555, 340, bitmap, kParamSynthMic), -1, "");

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
    bitmap = pGraphics->LoadBitmap(PNGKNOB6_FN, 6, true);
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 190, offy + 69, bitmap, kParamOsc1Range), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 190, offy + 156, bitmap, kParamOsc2Range), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 190, offy + 249, bitmap, kParamOsc3Range), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 353, offy + 69, bitmap, kParamOsc1Waveform), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 353, offy + 156, bitmap, kParamOsc2Waveform), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 353, offy + 249, bitmap, kParamOsc3Waveform), -1, "main");

    bitmap = pGraphics->LoadBitmap(PNGKNOB2_FN, 2, true);
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 352, offy + 69, bitmap, kParamFlangerChorus, NULL, EDirection::Vertical, 1.), -1, "add");

    bitmap = pGraphics->LoadBitmap(PNGSWITCHREDV_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 164, offy + 278, bitmap, kParamOsc3Control), -1, "main");

    bitmap = pGraphics->LoadBitmap(PNGSWITCHREDHBYPASS_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(483, 316, bitmap, kParamEffectBypass), -1, "add");

    bitmap = pGraphics->LoadBitmap(PNGSWITCHREDH_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 623, offy + 175, bitmap, kParamKeybControl), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 623, offy + 92, bitmap, kParamFilterMod1), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 623, offy + 137, bitmap, kParamFilterMod2), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 136, offy + 100, bitmap, kParamOscMod), -1, "main");

    
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 611, offy + 172, bitmap, kParamDelayCrossDual), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 840, offy + 110, bitmap, kParamDelayUnitLeft), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 840, offy + 243, bitmap, kParamDelayUnitRight), -1, "add");

    bitmap = pGraphics->LoadBitmap(PNGSWITCHBLUEV_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 614, offy + 214, bitmap, kParamNoiseType), -1, "main");

    bitmap = pGraphics->LoadBitmap(PNGSWITCHBLUEH_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 497, offy + 92, bitmap, kParamOsc1), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 497, offy + 175, bitmap, kParamOsc2), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 497, offy + 260, bitmap, kParamOsc3), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 497, offy + 134, bitmap, kParamFeedback), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 497, offy + 216, bitmap, kParamNoise), -1, "main");

    bitmap = pGraphics->LoadBitmap(PNGSWITCHSILVERH_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 63, offy + 240, bitmap, kParamGlideOnOff), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 63, offy + 268, bitmap, kParamDecay), -1, "main");

    bitmap = pGraphics->LoadBitmap(PNGSWITCHSILVERH_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 63, offy + 254, bitmap, kParamKeybModeRetrig), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 63, offy + 225, bitmap, kParamKeybModeLowNote), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 63, offy + 284, bitmap, kParamKeybModeSingle), -1, "add");

    bitmap = pGraphics->LoadBitmap(PNGPITCHWHEEL14_FN, 14, true);
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 108, offy + 230, bitmap, kParamPitchWheel), -1, "add");

    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(108, 40, 138, 55), kParamBendRange, DEFAULT_TEXT, COLOR_MID_GRAY, true), -1, "add");

    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(268, 154, 307, 170), kParamChorusRate, DEFAULT_TEXT, COLOR_MID_GRAY, true), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(268, 274, 307, 290), kParamChorusPhase, DEFAULT_TEXT, COLOR_MID_GRAY, true), -1, "add");

    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(832, 168, 878, 186), kParamMidiClockBpm, DEFAULT_TEXT, COLOR_MID_GRAY, true), -1, "add");

    //pGraphics->AttachControl(new ICaptionControlMidi(IRECT(525, 154, 574, 171), kParamDelayTimeLMS, DEFAULT_TEXT, COLOR_MID_GRAY, true), kCtrlTagDelayTimeLMSCaption, "add");
    //pGraphics->AttachControl(new ICaptionControlMidi(IRECT(525, 287, 574, 304), kParamDelayTimeRMS, DEFAULT_TEXT, COLOR_MID_GRAY, true), kCtrlTagDelayTimeRMSCaption, "add");


    bitmap = pGraphics->LoadBitmap(PNGKNOBBG_FN);
    IControl* delayTimeSkalaL = new IBitmapControl(503, 70, bitmap, kNoParameter);
    pGraphics->AttachControl(delayTimeSkalaL, kCtrlTagSkalaL, "add");

    IControl* delayTimeSkalaR = new IBitmapControl(503, 200, bitmap, kNoParameter);
    pGraphics->AttachControl(delayTimeSkalaR, kCtrlTagSkalaR, "add");


    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(528, 114, 577, 131), kParamDelayTimeLBPM, DEFAULT_TEXT, COLOR_MID_GRAY, true), kCtrlTagDelayTimeLBPM, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(528, 245, 577, 262), kParamDelayTimeRBPM, DEFAULT_TEXT, COLOR_MID_GRAY, true), kCtrlTagDelayTimeRBPM, "add");

    
   

/*
    bitmap = pGraphics->LoadBitmap(PNGDEVELOPER_FN, 2);
    IBSwitchControl *devCtrl = new IBSwitchControl(478, 4, bitmap, kNoParameter);
    devCtrl->SetActionFunction([&](IControl *ctrl) { mDeveloperActive = ctrl->GetValue(); });
    pGraphics->AttachControl(devCtrl, -1, "");
    devCtrl->SetValue(mDeveloperActive);
*/
   
    bitmap = pGraphics->LoadBitmap(PNGMIDIACTIVE_FN, 2);
    //pGraphics->AttachControl(new IBSwitchControlMidi(166, 4, bitmap, kParamMidiActive), kCtrlMidiActive, "header");
	pGraphics->AttachControl(new IBitmapControl(166, 4, bitmap, kNoParameter), kCtrlMidiActive, "header");

  
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
//            pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMSCaption)->Hide(false);

          }
          else {
          pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(false);
//          pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMSCaption)->Hide(true);
          pCaller->GetUI()->GetControlWithTag(kCtrlTagSkalaL)->Hide(false);
          pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMS)->Hide(true);
          }
        }

        if (pCaller->GetUI()->GetControlWithTag(kCtrlTagAdd)->GetValue() == 1) {
          if (pCaller->GetDelegate()->GetParam(kParamDelayUnitRight)->Value() == 0) {
          pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(true);
          pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMS)->Hide(false);
          pCaller->GetUI()->GetControlWithTag(kCtrlTagSkalaR)->Hide(true);
//          pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMSCaption)->Hide(false);
          }
          else {
           pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(false);
//           pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMSCaption)->Hide(true);
           pCaller->GetUI()->GetControlWithTag(kCtrlTagSkalaR)->Hide(false);
           pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMS)->Hide(true);
          }
        }

      }
    };

    bitmap = pGraphics->LoadBitmap(PNGMAIN_FN, 2);
    IBSwitchControlFunc *mainCtrl = new IBSwitchControlFunc(10, 4, bitmap, windowFunc, kNoParameter);
    pGraphics->AttachControl(mainCtrl, kCtrlTagMain);
    mainCtrl->SetValue(1);
    bitmap = pGraphics->LoadBitmap(PNGADD_FN, 2);
    IBSwitchControlFunc *addCtrl = new IBSwitchControlFunc(76, 4, bitmap, windowFunc, kNoParameter);
    pGraphics->AttachControl(addCtrl, kCtrlTagAdd);

    // MIXER UI
#include "../MPA Code/MixerUI.h" 

    // KEYBOARD UI
#include "../MPA Code/KeyboardUI.h"

// RESIZE CONTROLS ////////////////////////////////////////////////////////////////////////////////////////////////

#include "../MPA Code/Resize.h" 

    bitmap = pGraphics->LoadBitmap(PNGMIDIMONITOR_FN, 2);
    IBSwitchControl *presetUI = new IBSwitchControl(400, 4, bitmap, kNoParameter);
    pGraphics->AttachControl(presetUI, kCtrlTagMidiMonHide, "");
    presetUI->SetActionFunction(resizeFunc);

    bitmap = pGraphics->LoadBitmap(PNGMIXER_FN, 2); // MIXER UI
    IBSwitchControl *mixerUICtrl = new IBSwitchControl(322, 4, bitmap, kNoParameter);
    pGraphics->AttachControl(mixerUICtrl, kCtrlTagMixerHide, "");
    mixerUICtrl->SetActionFunction(resizeFunc);

    bitmap = pGraphics->LoadBitmap(PNGKEYB_FN, 2);
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

    bitmap = pGraphics->LoadBitmap(PNGCLEAR_FN, 1);
    IBButtonControl* clearCtrl = new IBButtonControl(HS_W + 64, 351, bitmap, [&](IControl*) {mMidiLogger->Clear(); });
    pGraphics->AttachControl(clearCtrl, kCtrlTagClear, "midiMonitor");



    mMidiLogger = new MidiMonitor(IRECT(HS_W + 14, 379-118, HS_W + 196, 454-118), "", "", IText(12, COLOR_BLACK, "Calibri", EAlign::Near), COLOR_WHITE);
    pGraphics->AttachControl(mMidiLogger, kCtrlTagMidiLogger, "midiMonitor");

    bitmap = pGraphics->LoadBitmap(PNGSLIDER_FN, 1);
    pGraphics->AttachControl(new IBSliderControlScroll(HS_W + 210, 378 -118, 75, -1, bitmap), kCtrlSliderMidiMon1);
    pGraphics->GetControlWithTag(kCtrlSliderMidiMon1)->SetActionFunction([&](IControl* ctrl) {mMidiLogger->setEntrypointerOffset(1. - ctrl->GetValue()); });
    pGraphics->GetControlWithTag(kCtrlSliderMidiMon1)->SetValue(1.);

    bitmap = pGraphics->LoadBitmap(PNGRECALL_FN, 1);
    IBButtonControl* RecallCtrl = new IBButtonControl(HS_W + 6, 321-118, bitmap, [&](IControl*) {});
    RecallCtrl->SetActionFunction([&](IControl* ctrl) {
      mPresetList->mActiveRow = mPresetList->mSelectedRow;
      GetUI()->GetControlWithTag(kCtrlProgram)->SetValue((double)mPresetList->mActiveRow / (mPresetList->maxLogSamples - 1.));
      GetUI()->GetControlWithTag(kCtrlProgram)->SetDirty();
      });
    pGraphics->AttachControl(RecallCtrl, -1, "midiMonitor");

        bitmap = pGraphics->LoadBitmap(PNGOVERWRITE_FN, 1);
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
	
	bitmap = pGraphics->LoadBitmap(PNGRESET_FN, 1);
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

    //presettext txt;
    for (int k = 0; k < 50; k++) {
		mPresetList->addItem(presetname[k]);
	}

    bitmap = pGraphics->LoadBitmap(PNGSLIDER_FN, 1);
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

    bitmap = pGraphics->LoadBitmap(PNGPLUS_FN);
    pGraphics->AttachControl(new IBButtonControl(HS_W + 211, 36, bitmap, [&](IControl*) {
      captionCtrl->SetValue(GetParam(kParamProgram)->ToNormalized(GetParam(kParamProgram)->Value() + 1));
      captionCtrl->SetDirty();
      }
    ), -1, "");

    bitmap = pGraphics->LoadBitmap(PNGMINUS_FN);
    pGraphics->AttachControl(new IBButtonControl(HS_W + 125, 36, bitmap, [&](IControl*) {

      captionCtrl->SetValue(GetParam(kParamProgram)->ToNormalized(GetParam(kParamProgram)->Value() - 1));
      captionCtrl->SetDirty();
      }
    ), -1, "");


    //////////


    bitmap = pGraphics->LoadBitmap(PNGSAVE_FN, 1);

    IBButtonControl* saveButton = new IBButtonControl(HS_W + 7, 6, bitmap, [&](IControl*) {

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

    bitmap = pGraphics->LoadBitmap(PNGLOAD_FN, 1);
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
          GetUI()->ForControlWithParam(i, [&](IControl& control) {control.SetValueFromUserInput(val); }); // macht nur wenn parameterwert anders als alter ist.
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
      //GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMSCaption)->Hide(true);

      GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(true);
      GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMS)->Hide(true);
      GetUI()->GetControlWithTag(kCtrlTagSkalaR)->Hide(true);
     // GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMSCaption)->Hide(true);
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
  //mPresetList->mSelectedRow = GetParam(kParamProgram)->Value();
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

bool Minimax::OnMessage(int messageTag, int controlTag, int dataSize, const void *pData) {

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
    //case kParamLfoNote:
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
  
  if (GetParam(kParamUserFactory)->Value() == 0) { // Factory
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
    else if (GetParam(kParamUserFactory)->Value() == 1) { // User
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
	
    msg.Clear();
    msg.mStatus = mChannel | (IMidiMsg::kProgramChange << 4);
    msg.mData1 = GetParam(paramIdx)->Value();
    msg.mData2 = 0;
    msg.mOffset = -2;
    SendMidiMsgFromUI(msg);
          
    break;

  /*case kParamMidiActive:
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

    break;*/

  case kParamDelayUnitLeft:
    if (GetUI()) {
      if (GetUI()->GetControlWithTag(kCtrlTagAdd)->GetValue() == 1) {
        if (GetParam(paramIdx)->Value() == 0) {
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(true);
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMS)->Hide(false);
          GetUI()->GetControlWithTag(kCtrlTagSkalaL)->Hide(true);
//          GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMSCaption)->Hide(false);

        }
        else {
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(false);
//          GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMSCaption)->Hide(true);
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
//          GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMSCaption)->Hide(false);
        }
        else {
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(false);
//          GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMSCaption)->Hide(true);
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



  // Presetname
  WDL_String s;
  s.Set(mCurrentPresetPath.Get());
  chunk.PutStr(s.Get());

  return SerializeParams(chunk);
}

// this over-ridden method is called when the host is trying to load the plug-in state and you need to unpack the data into your algorithm
// HIER KÖNNEN KEINE CONTROLS GEUPDATED WERDEN; DA MGRAPHICS NOCH NICHT EXISTIERT!!!!
int Minimax::UnserializeState(const IByteChunk& chunk, int startPos) {

  TRACE;


  int pos;
  // Presetname
  WDL_String str;
  pos = chunk.GetStr(str, pos);
  mCurrentPresetPath.Set(str.Get());

  return UnserializeParams(chunk, pos);
}
#endif
