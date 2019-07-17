#include "Minimax.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"


/*void IControl::OnMidi(const IMidiMsg &msg) {
  SetValueFromDelegate(msg.mData2);
}*/

Minimax::Minimax(IPlugInstanceInfo instanceInfo)
: IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo)
{

  mCurrentPresetPath.Set("Default");

  GetParam(kParamKeyboardOctave)->InitEnum("Keyb Oct", 3, 7, "", 0, "", "-3","-2","-1","0","+1","+2","+3");
  GetParam(kParamProgram)->InitInt("Program", 0, 0, 99, "", 0, "");
  GetParam(kParamMidiActive)->InitBool("MIDI Active", true, "");
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

  GetParam(kParamMasterVolume)->InitDouble("Volume", 0, 0, 1, 0.001);
  GetParam(kParamSynthMic)->InitDouble("Synth Mic", 0, 0, 1, 0.001);

    paramToCC.fill(-1);

    paramToCC[kParamMasterVolume] = 7;
    paramToCC[kParamSynthMic] = 93;
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
      paramToCC[kParamDelayFeedbackRight             ]=119;
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

    paramToMsgType[kParamMasterVolume] = 0;
    paramToMsgType[kParamSynthMic] = 0;
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
      //paramToCC[kParamProgram                      ]=0;
   

  
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
    IControl* backCtrl = new IBitmapControl(0,0, bitmap, kNoParameter);
    pGraphics->AttachControl(backCtrl, -1, "");
    
    // BITMAPS 
    //bitmap = pGraphics->LoadBitmap(PNGPANELHEAD1_FN);
    //IControl* mainPanelHeadCtrl = new IBitmapControl(0, 0, bitmap, kNoParameter);
    //pGraphics->AttachControl(mainPanelHeadCtrl);

    bitmap = pGraphics->LoadBitmap(PNGPANELMAIN_FN);
    IControl* mainPanelCtrl = new IBitmapControl(6, 29, bitmap, kNoParameter);
    pGraphics->AttachControl(mainPanelCtrl, -1, "main");

    bitmap = pGraphics->LoadBitmap(PNGPANELADD_FN);
    IControl* addPanelCtrl = new IBitmapControl(6, 29, bitmap, kNoParameter);
    pGraphics->AttachControl(addPanelCtrl, -1, "add");
    if (strcmp(addPanelCtrl->GetGroup(), "add") == 0) addPanelCtrl->Hide(true);

    //bitmap = pGraphics->LoadBitmap(PNGKEYBACK_FN);
    //IControl* keybackCtrl = new IBitmapControl(0, HS_H, bitmap, kNoParameter);
    //pGraphics->AttachControl(keybackCtrl, -1, "keyboard");
 
    IRECT keybRect = IRECT(MARGIN_W, HS_H + MARGIN_H, PLUG_WIDTH - MARGIN_W, HS_H + MARGIN_H + KEYBOARD_H);
    keybCtrl = new IVKeyboardControl(keybRect.FracRectHorizontal(0.85), 36, 91);
    pGraphics->AttachControl(keybCtrl, kCtrlTagKeyboard, "keyboard");

    pGraphics->AttachControl(new ICaptionControl(IRECT(873, 424, 903, 444), kParamKeyboardOctave, DEFAULT_TEXT, COLOR_MID_GRAY, true), -1, "keyboard");

    IVButtonControl* buttCtrl = new IVButtonControl(IRECT(850, 476, 935, 506), [&](IControl*) {
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

    // KNOBS
    bitmap = pGraphics->LoadBitmap(PNGKNOB32_FN, 33);

    int offx = 6;
    int offy = -6;

    pGraphics->AttachControl(new IBKnobControlMidi(435, 340, bitmap, kParamMasterVolume), -1, "");
    pGraphics->AttachControl(new IBKnobControlMidi(555, 340, bitmap, kParamSynthMic), -1, "");

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
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 609, 232, bitmap, kParamDelayFeedbackRight), -1, "add");
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

    bitmap = pGraphics->LoadBitmap(PNGSWITCHSILVERH2_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 63, offy + 254, bitmap, kParamKeybModeRetrig), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 63, offy + 225, bitmap, kParamKeybModeLowNote), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 63, offy + 284, bitmap, kParamKeybModeSingle), -1, "add");

    bitmap = pGraphics->LoadBitmap(PNGPITCHWHEEL14_FN, 14, true);
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 108, offy + 230, bitmap, kParamPitchWheel), -1, "add");

    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(108, 40, 138, 55), kParamBendRange, DEFAULT_TEXT, COLOR_MID_GRAY, true), -1, "add");

    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(268, 154, 307, 170), kParamChorusRate, DEFAULT_TEXT, COLOR_MID_GRAY, true), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(268, 274, 307, 290), kParamChorusPhase, DEFAULT_TEXT, COLOR_MID_GRAY, true), -1, "add");

    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(832, 168, 878, 186), kParamMidiClockBpm, DEFAULT_TEXT, COLOR_MID_GRAY, true), -1, "add");

    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(525, 154, 574, 171), kParamDelayTimeLMS, DEFAULT_TEXT, COLOR_MID_GRAY, true), kCtrlTagDelayTimeLMSCaption, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(525, 287, 574, 304), kParamDelayTimeRMS, DEFAULT_TEXT, COLOR_MID_GRAY, true), kCtrlTagDelayTimeRMSCaption, "add");


    bitmap = pGraphics->LoadBitmap(PNGKNOBBG_FN);
    IControl* delayTimeSkalaL = new IBitmapControl(503, 70, bitmap, kNoParameter);
    pGraphics->AttachControl(delayTimeSkalaL, kCtrlTagSkalaL, "add");

    IControl* delayTimeSkalaR = new IBitmapControl(503, 200, bitmap, kNoParameter);
    pGraphics->AttachControl(delayTimeSkalaR, kCtrlTagSkalaR, "add");


    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(528, 114, 577, 131), kParamDelayTimeLBPM, DEFAULT_TEXT, COLOR_MID_GRAY, true), kCtrlTagDelayTimeLBPM, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(528, 245, 577, 262), kParamDelayTimeRBPM, DEFAULT_TEXT, COLOR_MID_GRAY, true), kCtrlTagDelayTimeRBPM, "add");

    
   


    

   
    bitmap = pGraphics->LoadBitmap(PNGMIDIACTIVE_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(326, 4, bitmap, kParamMidiActive), -1, "header");

    
   
    // Program Change
    captionCtrl = new ICaptionControl(IRECT(1034, 5, 1094, 25), kParamProgram, DEFAULT_TEXT, COLOR_MID_GRAY, true);
    pGraphics->AttachControl(captionCtrl, -1, "header");

    bitmap = pGraphics->LoadBitmap(PNGPLUS_FN);
    pGraphics->AttachControl(new IBButtonControl(1094,5, bitmap, [&](IControl*) {
      captionCtrl->SetValueFromUserInput(GetParam(kParamProgram)->ToNormalized(GetParam(kParamProgram)->FromNormalized(captionCtrl->GetValue())+1));
    }
    ), -1, "header");

    bitmap = pGraphics->LoadBitmap(PNGMINUS_FN);
    pGraphics->AttachControl(new IBButtonControl(1015, 5, bitmap, [&](IControl*) {
      captionCtrl->SetValueFromUserInput(GetParam(kParamProgram)->ToNormalized(GetParam(kParamProgram)->FromNormalized(captionCtrl->GetValue()) - 1));
    }
    ), -1, "header");

    
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
            pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMSCaption)->Hide(false);

          }
          else {
          pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(false);
          pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMSCaption)->Hide(true);
          pCaller->GetUI()->GetControlWithTag(kCtrlTagSkalaL)->Hide(false);
          pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMS)->Hide(true);
          }
        }

        if (pCaller->GetUI()->GetControlWithTag(kCtrlTagAdd)->GetValue() == 1) {
          if (pCaller->GetDelegate()->GetParam(kParamDelayUnitRight)->Value() == 0) {
          pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(true);
          pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMS)->Hide(false);
          pCaller->GetUI()->GetControlWithTag(kCtrlTagSkalaR)->Hide(true);
          pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMSCaption)->Hide(false);
          }
          else {
           pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(false);
           pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMSCaption)->Hide(true);
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
    pGraphics->AttachControl(new IBSwitchControlFunc(152, 4, bitmap, resizeFunc, kNoParameter), kCtrlTagMidiMonHide);
    bitmap = pGraphics->LoadBitmap(PNGKEYB_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlFunc(237, 4, bitmap, resizeFunc, kNoParameter), kCtrlTagKeybHide);



    //bitmap = pGraphics->LoadBitmap(PNGMIDIMONBACK_FN);
    //IControl* midiCtrlBack = new IBitmapControl(0, HSK_H+MARGIN_H, bitmap, kNoParameter);
    //pGraphics->AttachControl(midiCtrlBack, kCtrlTagMidiBack, "midiMonitor");

    mMidiLogger = new MidiLoggerControl(IRECT(HS_W + MARGIN_W, MARGIN_H + MIDILOG_H, HS_W + MIDIPRESET_W - MARGIN_W, HS_H-MARGIN_H), "", "", IText(12, COLOR_BLACK, NULL, EAlign::Near), COLOR_WHITE);
    pGraphics->AttachControl(mMidiLogger, kCtrlTagMidiLogger, "midiMonitor");

    IVButtonControl* clearCtrl = new IVButtonControl(IRECT(973, 213, 1058, 243), [&](IControl*) {
      mMidiLogger->Clear();
    },

      "Clear", IVStyle(DEFAULT_SHOW_LABEL, DEFAULT_SHOW_VALUE, {}, IText(12)));

    buttCtrl->SetAnimation(DefaultAnimationFunc);
    pGraphics->AttachControl(clearCtrl, kCtrlTagClear, "midiMonitor");

    mPresetMenu = new FileBrowser(IRECT(971+10, 37, 1167-10, 61));
    pGraphics->AttachControl(mPresetMenu, kCtrlTagPresetMenu);

    
    if (GetUI()) {
      for (auto k = 0; k < GetUI()->NControls(); k++) {
        if (strcmp(GetUI()->GetControl(k)->GetGroup(), "add") == 0) {
          GetUI()->GetControl(k)->Hide(true);
        }
      }

     GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(true);
      GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMS)->Hide(true);
      GetUI()->GetControlWithTag(kCtrlTagSkalaL)->Hide(true);
      GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMSCaption)->Hide(true);

      GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(true);
      GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMS)->Hide(true);
      GetUI()->GetControlWithTag(kCtrlTagSkalaR)->Hide(true);
      GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMSCaption)->Hide(true);
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

void Minimax::OnUIOpen() {

  SendCurrentParamValuesFromDelegate();

  // Presetname
  //mPresetMenu->restorePresetPath(mCurrentPresetPath.Get());
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

void Minimax::OnParamChange(int paramIdx)
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
          GetUI()->GetControlWithTag(kCtrlTagSkalaL)->Hide(true);
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMSCaption)->Hide(false);

        }
        else {
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(false);
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMSCaption)->Hide(true);
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
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMSCaption)->Hide(false);
        }
        else {
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(false);
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMSCaption)->Hide(true);
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
