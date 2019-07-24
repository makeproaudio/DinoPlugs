#include "B4000.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"

B4000::B4000(IPlugInstanceInfo instanceInfo)
: IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo)
{

  mCurrentPresetPath.Set("Default");

  GetParam(kParamUserFactory)->InitEnum("Preset Bank", 0, 2, "", 0, "", "Factory Bank", "User Bank");
  GetParam(kParamProgram)->InitInt("Program", 1, 1, 50, "", 0, "");

  GetParam(kParamKeyboardOctave)->InitEnum("Keyb Oct", 3, 7, "", 0, "", "-3", "-2", "-1", "0", "+1", "+2", "+3");
 
  GetParam(kParamMidiActive)->InitBool("MIDI Active", true, "");
  GetParam(kParamMidiActive)->InitBool("MIDI Active", true, "");

  // B5 is missed in original Pluginmanager, here also:
  GetParam(kParamSplitLowerManual)->InitEnum("Split Lower Manual", 0, 128, "", 0, "", "C-2", "C#-2", "D-2", "D#-2", "E-2", "F-2", "F#-2", "G-2", "G#-2", "A-2", "A#-2", "B-2", "C-1", "C#-1", "D-1", "D#-1", "E-1", "F-1", "F#-1", "G-1", "G#-1", "A-1", "A#-1", "B-1", "C0", "C#0", "D0", "D#0", "E0", "F0", "F#0", "G0", "G#0", "A0", "A#0", "B0", "C1", "C#1", "D1", "D#1", "E1", "F1", "F#1", "G1", "G#1", "A1", "A#1", "B1", "C2", "C#2", "D2", "D#2", "E2", "F2", "F#2", "G2", "G#2", "A2", "A#2", "B2", "C3", "C#3", "D3", "D#3", "E3", "F3", "F#3", "G3", "G#3", "A3", "A#3", "B3", "C4", "C#4", "D4", "D#4", "E4", "F4", "F#4", "G4", "G#4", "A4", "A#4", "B4", "C5", "C#5", "D5", "D#5", "E5", "F5", "F#5", "G5", "G#5", "A5", "A#5", "C6", "C#6", "D6", "D#6", "E6", "F6", "F#6", "G6", "G#6", "A6", "A#6", "B6", "C7", "C#7", "D7", "D#7", "E7", "F7", "F#7", "G7", "G#7", "A7", "A#7", "B7", "C8", "C#8", "D8", "D#8", "E8", "F8", "F#8", "G8", "G#8");
  GetParam(kParamSplitUpperManual)->InitEnum("Split Upper Manual", 0, 128, "", 0, "", "C-2", "C#-2", "D-2", "D#-2", "E-2", "F-2", "F#-2", "G-2", "G#-2", "A-2", "A#-2", "B-2", "C-1", "C#-1", "D-1", "D#-1", "E-1", "F-1", "F#-1", "G-1", "G#-1", "A-1", "A#-1", "B-1", "C0", "C#0", "D0", "D#0", "E0", "F0", "F#0", "G0", "G#0", "A0", "A#0", "B0", "C1", "C#1", "D1", "D#1", "E1", "F1", "F#1", "G1", "G#1", "A1", "A#1", "B1", "C2", "C#2", "D2", "D#2", "E2", "F2", "F#2", "G2", "G#2", "A2", "A#2", "B2", "C3", "C#3", "D3", "D#3", "E3", "F3", "F#3", "G3", "G#3", "A3", "A#3", "B3", "C4", "C#4", "D4", "D#4", "E4", "F4", "F#4", "G4", "G#4", "A4", "A#4", "B4", "C5", "C#5", "D5", "D#5", "E5", "F5", "F#5", "G5", "G#5", "A5", "A#5", "C6", "C#6", "D6", "D#6", "E6", "F6", "F#6", "G6", "G#6", "A6", "A#6", "B6", "C7", "C#7", "D7", "D#7", "E7", "F7", "F#7", "G7", "G#7", "A7", "A#7", "B7", "C8", "C#8", "D8", "D#8", "E8", "F8", "F#8", "G8", "G#8");

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


  //GetParam(kParamVolume)->InitDouble("Volume", 0, 0, 1, 0.001);

  //GetParam(kParamSynthMic)->InitDouble("Synth Mic", 0, 0, 1, 0.001);
  //GetParam(kParamBoost)->InitDouble("Boost", 0, 0, 1, 0.001);
  GetParam(kParamPedal)->InitDouble("Pedal", 0, 0, 1, 0.001);
  GetParam(kParamLowerManual)->InitDouble("Lower Manual", 0, 0, 1, 0.001);
  GetParam(kParamUpperManual)->InitDouble("Upper Manual", 0, 0, 1, 0.001);
  GetParam(kParamPercussionLevel)->InitDouble("Percussion Level", 0, 0, 1, 0.001);
  GetParam(kParamPercussionDecay)->InitDouble("Percussion Decay", 0, 0, 1, 0.001);
  GetParam(kParamPercussionHarmonic)->InitDouble("Percussion Harmonic", 0, 0, 1, 0.001);
  GetParam(kParamKeyClickLevel)->InitDouble("Key Click Level", 0, 0, 1, 0.001);
  GetParam(kParamDriveLevel)->InitDouble("Drive Level", 0, 0, 1, 0.001);
  GetParam(kParamDriveOutput)->InitDouble("Drive Output", 0, 0, 1, 0.001);
  GetParam(kParamSwell)->InitDouble("Swell", 0, 0, 1, 0.001);
  GetParam(kParamTreble)->InitDouble("Treble", 0, 0, 1, 0.001);
  GetParam(kParamBass)->InitDouble("Bass", 0, 0, 1, 0.001);
  GetParam(kParamOct1)->InitInt("Oct 1", -1, -1, 1);
  GetParam(kParamOct2)->InitInt("Oct 2", -1, -1, 1);
  GetParam(kParamOct3)->InitInt("Oct 3", -1, -1, 1);
  GetParam(kParamBar1)->InitInt("Drawbar 1", 0, 0, 8);
  GetParam(kParamBar2)->InitInt("Drawbar 2", 0, 0, 8);
  GetParam(kParamBar3)->InitInt("Drawbar 3", 0, 0, 8);
  GetParam(kParamBar4)->InitInt("Drawbar 4", 0, 0, 8);
  GetParam(kParamBar5)->InitInt("Drawbar 5", 0, 0, 8);
  GetParam(kParamBar6)->InitInt("Drawbar 6", 0, 0, 8);
  GetParam(kParamBar7)->InitInt("Drawbar 7", 0, 0, 8);
  GetParam(kParamBar8)->InitInt("Drawbar 8", 0, 0, 8);
  GetParam(kParamBar9)->InitInt("Drawbar 9", 0, 0, 8);
  GetParam(kParamBar10)->InitInt("Drawbar 10", 0, 0, 8);
  GetParam(kParamBar11)->InitInt("Drawbar 11", 0, 0, 8);
  GetParam(kParamBar12)->InitInt("Drawbar 12", 0, 0, 8);
  GetParam(kParamBar13)->InitInt("Drawbar 13", 0, 0, 8);
  GetParam(kParamBar14)->InitInt("Drawbar 14", 0, 0, 8);
  GetParam(kParamBar15)->InitInt("Drawbar 15", 0, 0, 8);
  GetParam(kParamBar16)->InitInt("Drawbar 16", 0, 0, 8);
  GetParam(kParamBar17)->InitInt("Drawbar 17", 0, 0, 8);
  GetParam(kParamBar18)->InitInt("Drawbar 18", 0, 0, 8);
  GetParam(kParamBar19)->InitInt("Drawbar 19", 0, 0, 8);
  GetParam(kParamBar20)->InitInt("Drawbar 20", 0, 0, 8);
  GetParam(kParamBar21)->InitInt("Drawbar 21", 0, 0, 8);
  GetParam(kParamBar22)->InitInt("Drawbar 22", 0, 0, 8);
  GetParam(kParamBar23)->InitInt("Drawbar 23", 0, 0, 8);
  GetParam(kParamBar24)->InitInt("Drawbar 24", 0, 0, 8);
  GetParam(kParamVibratoLower)->InitEnum("Vibrato Lower", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamVibratoUpper)->InitEnum("Vibrato Upper", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamRotor)->InitEnum("Rotor", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamPercussion)->InitEnum("Percussion", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamDrive)->InitEnum("Drive", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamVelocity)->InitEnum("Velocity", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamFastSlow)->InitEnum("Rotor Speed", 0, 2, "", 0, "", "Slow", "Fast");
  GetParam(kParamVibrato)->InitInt("Vibrato", 0, 0, 5);
  GetParam(kParamRotorOffAt)->InitEnum("Rotor", 0, 2, "", 0, "", "Off", "At");


  GetParam(kParamRotorHornSlow)->InitDouble("Rotor Horn Slow", 0, 0, 10, 0.1);
  GetParam(kParamRotorHornFast)->InitDouble("Rotor Horn Fast", 0, 0, 20, 0.1);
  GetParam(kParamRotorHornAccel)->InitDouble("Rotor Horn Accel", 0, 0, 30, 0.1);
  GetParam(kParamRotorHornBrake)->InitDouble("Rotor Horn Brake", 0, 0, 30, 0.1);
  GetParam(kParamRotorHornTone)->InitDouble("Rotor Horn Tone", 0, 0, 1, 0.1);
  GetParam(kParamRotorBassSlow)->InitDouble("Rotor Bass Slow", 0, 0, 10, 0.1);
  GetParam(kParamRotorBassFast)->InitDouble("Rotor Bass Fast", 0, 0, 20, 0.1);
  GetParam(kParamRotorBassAccel)->InitDouble("Rotor Bass Accel", 0, 0, 30, 0.1);
  GetParam(kParamRotorBassBrake)->InitDouble("Rotor Bass Brake", 0, 0, 30, 0.1);
  GetParam(kParamRotorBassTone)->InitDouble("Rotor Bass Tone", 0, 0, 1, 0.1);

  GetParam(kParamMicSpread)->InitDouble("Mic Spread", 0, 0, 1, 0.001);
  GetParam(kParamMicBalance)->InitDouble("Mic Balance", 0, 0, 1, 0.001);
  GetParam(kParamMicDistance)->InitDouble("Mic Distance", 0, 0, 1, 0.001);

  GetParam(kParamToneWheelsCondition)->InitDouble("Tonewheels Condition", 0, 0, 1, 0.001);
  GetParam(kParamToneWheelsTuning)->InitDouble("Tonewheels Tuning", 0, 0, 1, 0.001);
  GetParam(kParamDrawbarsLeakage)->InitDouble("Drawbars Leakage", 0, 0, 1, 0.001);
  GetParam(kParamDrawbarsDistortion)->InitDouble("DrawbarsDistortion", 0, 0, 1, 0.001);
  GetParam(kParamEnvelopeAttack)->InitDouble("Envelope Attack", 0, 0, 1, 0.001);
  GetParam(kParamEnvelopeRelease)->InitDouble("Envelope Release", 0, 0, 1, 0.001);

  paramToCC.fill(-1);

 // paramToCC[kParamVolume                     ]=7;
 // paramToCC[kParamSynthMic                   ]=93;
 // paramToCC[kParamBoost                      ]=105;
  paramToCC[kParamPedal                      ]=58;
  paramToCC[kParamLowerManual                ]=57;
  paramToCC[kParamUpperManual                ]=56;
  paramToCC[kParamPercussionLevel            ]=38;
  paramToCC[kParamPercussionDecay            ]=39;
  paramToCC[kParamPercussionHarmonic         ]=37;
  paramToCC[kParamKeyClickLevel              ]=41;
  paramToCC[kParamDriveLevel                 ]=52;
  paramToCC[kParamDriveOutput                ]=30;
  paramToCC[kParamSwell                      ]=11;
  paramToCC[kParamTreble                     ]=54;
  paramToCC[kParamBass                       ]=55;
  paramToCC[kParamSplitLowerManual           ]=105;
  paramToCC[kParamSplitUpperManual           ]=106;
  paramToCC[kParamOct1                       ]=108;
  paramToCC[kParamOct2                       ]=109;
  paramToCC[kParamOct3                       ]=110;
  paramToCC[kParamBar1                       ]=82;
  paramToCC[kParamBar2                       ]=83;
  paramToCC[kParamBar3                       ]=84;
  paramToCC[kParamBar4                       ]=85;
  paramToCC[kParamBar5                       ]=86;
  paramToCC[kParamBar6                       ]=87;
  paramToCC[kParamBar7                       ]=88;
  paramToCC[kParamBar8                       ]=89;
  paramToCC[kParamBar9                       ]=90;
  paramToCC[kParamBar10                      ]=21;
  paramToCC[kParamBar11                      ]=22;
  paramToCC[kParamBar12                      ]=23;
  paramToCC[kParamBar13                      ]=24;
  paramToCC[kParamBar14                      ]=25;
  paramToCC[kParamBar15                      ]=26;
  paramToCC[kParamBar16                      ]=12;
  paramToCC[kParamBar17                      ]=13;
  paramToCC[kParamBar18                      ]=14;
  paramToCC[kParamBar19                      ]=15;
  paramToCC[kParamBar20                      ]=16;
  paramToCC[kParamBar21                      ]=17;
  paramToCC[kParamBar22                      ]=18;
  paramToCC[kParamBar23                      ]=19;
  paramToCC[kParamBar24                      ]=20;
  paramToCC[kParamVibratoLower               ]=74;
  paramToCC[kParamVibratoUpper               ]=71;
  paramToCC[kParamRotor                      ] = 68;
  paramToCC[kParamPercussion                 ]=40;
  paramToCC[kParamDrive                      ]=53;
  paramToCC[kParamVelocity                   ]=48;
  paramToCC[kParamFastSlow                   ]=72;
  paramToCC[kParamVibrato                    ]=73;
  paramToCC[kParamRotorOffAt                 ]=69;
  paramToCC[kParamRotorHornSlow              ]=2;
  paramToCC[kParamRotorHornFast              ]=3;
  paramToCC[kParamRotorHornAccel             ]=4;
  paramToCC[kParamRotorHornBrake             ]=5;
  paramToCC[kParamRotorHornTone              ]=6;
  paramToCC[kParamRotorBassSlow              ]=8;
  paramToCC[kParamRotorBassFast              ]=9;
  paramToCC[kParamRotorBassAccel             ]=63;
  paramToCC[kParamRotorBassBrake             ]=75;
  paramToCC[kParamRotorBassTone              ]=76;
  paramToCC[kParamMicSpread                  ]=77;
  paramToCC[kParamMicBalance                 ]=78;
  paramToCC[kParamMicDistance                ]=62;
  paramToCC[kParamToneWheelsCondition        ]=42;
  paramToCC[kParamToneWheelsTuning           ]=43;
  paramToCC[kParamDrawbarsLeakage            ]=44;
  paramToCC[kParamDrawbarsDistortion         ]=45;
  paramToCC[kParamEnvelopeAttack             ]=46;
  paramToCC[kParamEnvelopeRelease            ]=47;
                                          
  paramToCC[kParamChorusPhase                ]=72;
  paramToCC[kParamChorusRate                 ]=71;
  paramToCC[kParamChorusDepth                ]=73;
  paramToCC[kParamChorusFeedback             ]=74;
  paramToCC[kParamChorusWet                  ]=91;
  paramToCC[kParamFlangerChorus              ]=75;
  paramToCC[kParamDelayTimeLMS               ]=81;
  paramToCC[kParamDelayTimeRMS               ]=91;
  paramToCC[kParamDelayTimeLBPM              ]=82;
  paramToCC[kParamDelayTimeRBPM              ]=92;
  paramToCC[kParamDelayFeedbackLeft          ]=119;
  paramToCC[kParamDelayHidampLeft            ]=84;
  paramToCC[kParamDelayLevelLeft             ]=85;
  paramToCC[kParamDelayFeedbackRight         ]=119;
  paramToCC[kParamDelayHidampRight           ]=94;
  paramToCC[kParamDelayLevelRight            ]=95;
  paramToCC[kParamDelayWet                   ]=10;
  paramToCC[kParamEffectBypass               ]=98;
  paramToCC[kParamDelayCrossDual             ]=90;
  paramToCC[kParamDelayUnitLeft              ]=86;
  paramToCC[kParamDelayUnitRight             ]=96;
  paramToCC[kParamMidiClockBpm               ]=97;                                    
                                                      
  paramToMsgType.fill(-1);
  
 // paramToMsgType[kParamVolume                     ]=0;
 // paramToMsgType[kParamSynthMic                   ]=0;
 // paramToMsgType[kParamBoost                      ]=1;
  paramToMsgType[kParamPedal                      ]=0;
  paramToMsgType[kParamLowerManual                ]=0;
  paramToMsgType[kParamUpperManual                ]=0;
  paramToMsgType[kParamPercussionLevel            ]=0;
  paramToMsgType[kParamPercussionDecay            ]=0;
  paramToMsgType[kParamPercussionHarmonic         ]=0;
  paramToMsgType[kParamKeyClickLevel              ]=0;
  paramToMsgType[kParamDriveLevel                 ]=0;
  paramToMsgType[kParamDriveOutput                ]=0;
  paramToMsgType[kParamSwell                      ]=0;
  paramToMsgType[kParamTreble                     ]=0;
  paramToMsgType[kParamBass                       ]=0;
  paramToMsgType[kParamSplitLowerManual           ]=0;
  paramToMsgType[kParamSplitUpperManual           ]=0;
  paramToMsgType[kParamOct1                       ]=0;
  paramToMsgType[kParamOct2                       ]=0;
  paramToMsgType[kParamOct3                       ]=0;
  paramToMsgType[kParamBar1                       ]=0;
  paramToMsgType[kParamBar2                       ]=0;
  paramToMsgType[kParamBar3                       ]=0;
  paramToMsgType[kParamBar4                       ]=0;
  paramToMsgType[kParamBar5                       ]=0;
  paramToMsgType[kParamBar6                       ]=0;
  paramToMsgType[kParamBar7                       ]=0;
  paramToMsgType[kParamBar8                       ]=0;
  paramToMsgType[kParamBar9                       ]=0;
  paramToMsgType[kParamBar10                      ]=0;
  paramToMsgType[kParamBar11                      ]=0;
  paramToMsgType[kParamBar12                      ]=0;
  paramToMsgType[kParamBar13                      ]=0;
  paramToMsgType[kParamBar14                      ]=0;
  paramToMsgType[kParamBar15                      ]=0;
  paramToMsgType[kParamBar16                      ]=0;
  paramToMsgType[kParamBar17                      ]=0;
  paramToMsgType[kParamBar18                      ]=0;
  paramToMsgType[kParamBar19                      ]=0;
  paramToMsgType[kParamBar20                      ]=0;
  paramToMsgType[kParamBar21                      ]=0;
  paramToMsgType[kParamBar22                      ]=0;
  paramToMsgType[kParamBar23                      ]=0;
  paramToMsgType[kParamBar24                      ]=0;
  paramToMsgType[kParamVibratoLower               ]=0;
  paramToMsgType[kParamVibratoUpper               ]=0;
  paramToMsgType[kParamRotor                      ]=0;
  paramToMsgType[kParamPercussion                 ]=0;
  paramToMsgType[kParamDrive                      ]=0;
  paramToMsgType[kParamVelocity                   ]=0;
  paramToMsgType[kParamFastSlow                   ]=0;
  paramToMsgType[kParamVibrato                    ]=0;
  paramToMsgType[kParamRotorOffAt                 ]=0;
  paramToMsgType[kParamRotorHornSlow              ]=0;
  paramToMsgType[kParamRotorHornFast              ]=0;
  paramToMsgType[kParamRotorHornAccel             ]=0;
  paramToMsgType[kParamRotorHornBrake             ]=0;
  paramToMsgType[kParamRotorHornTone              ]=0;
  paramToMsgType[kParamRotorBassSlow              ]=0;
  paramToMsgType[kParamRotorBassFast              ]=0;
  paramToMsgType[kParamRotorBassAccel             ]=0;
  paramToMsgType[kParamRotorBassBrake             ]=0;
  paramToMsgType[kParamRotorBassTone              ]=0;
  paramToMsgType[kParamMicSpread                  ]=0;
  paramToMsgType[kParamMicBalance                 ]=0;
  paramToMsgType[kParamMicDistance                ]=0;
  paramToMsgType[kParamToneWheelsCondition        ]=0;
  paramToMsgType[kParamToneWheelsTuning           ]=0;
  paramToMsgType[kParamDrawbarsLeakage            ]=0;
  paramToMsgType[kParamDrawbarsDistortion         ]=0;
  paramToMsgType[kParamEnvelopeAttack             ]=0;
  paramToMsgType[kParamEnvelopeRelease            ]=0;
                                                    
  paramToMsgType[kParamChorusPhase                ]=1;
  paramToMsgType[kParamChorusRate                 ]=1;
  paramToMsgType[kParamChorusDepth                ]=1;
  paramToMsgType[kParamChorusFeedback             ]=1;
  paramToMsgType[kParamChorusWet                  ]=0;
  paramToMsgType[kParamFlangerChorus              ]=1;
  paramToMsgType[kParamDelayTimeLMS               ]=1;
  paramToMsgType[kParamDelayTimeRMS               ]=1;
  paramToMsgType[kParamDelayTimeLBPM              ]=1;
  paramToMsgType[kParamDelayTimeRBPM              ]=1;
  paramToMsgType[kParamDelayFeedbackLeft          ]=0;
  paramToMsgType[kParamDelayHidampLeft            ]=1;
  paramToMsgType[kParamDelayLevelLeft             ]=1;
  paramToMsgType[kParamDelayFeedbackRight         ]=0;
  paramToMsgType[kParamDelayHidampRight           ]=1;
  paramToMsgType[kParamDelayLevelRight            ]=1;
  paramToMsgType[kParamDelayWet                   ]=0;
  paramToMsgType[kParamEffectBypass               ]=1;
  paramToMsgType[kParamDelayCrossDual             ]=1;
  paramToMsgType[kParamDelayUnitLeft              ]=1;
  paramToMsgType[kParamDelayUnitRight             ]=1;
  paramToMsgType[kParamMidiClockBpm               ]=1;
     
  
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


    bitmap = pGraphics->LoadBitmap(PNGPANEL_FN);
    IControl* panel = new IBitmapControl(0, 0, bitmap, kNoParameter);
    pGraphics->AttachControl(panel, -1, "");

    bitmap = pGraphics->LoadBitmap(PNGMIDIMONBACK_FN);
    IControl* midiCtrlBack = new IBitmapControl(HS_W, 0, bitmap, kNoParameter);
    pGraphics->AttachControl(midiCtrlBack, kCtrlTagMidiBack, "midiMonitor");

    bitmap = pGraphics->LoadBitmap(PNGHEADER_FN);
    IControl* mainPanelHeadCtrl = new IBitmapControl(0, 0, bitmap, kNoParameter);
    pGraphics->AttachControl(mainPanelHeadCtrl);

    bitmap = pGraphics->LoadBitmap(PNGMAINPANEL_FN);
    IControl* mainpanel = new IBitmapControl(18, 40, bitmap, kNoParameter);
    pGraphics->AttachControl(mainpanel, -1, "main");

    bitmap = pGraphics->LoadBitmap(PNGADDPANEL_FN);
    IControl* addpanel = new IBitmapControl(18, 40, bitmap, kNoParameter);
    pGraphics->AttachControl(addpanel, -1, "add");

    int offx = 0;
    int offy = 0;
    bitmap = pGraphics->LoadBitmap(PNGB4000KNOB_FN,64,true);
    //pGraphics->AttachControl(new IBKnobControlMidi(offx + 578, offy + 5, bitmap, kParamVolume), -1, "");
    //pGraphics->AttachControl(new IBKnobControlMidi(offx + 637, offy + 5, bitmap, kParamSynthMic), -1, "");

    bitmap = pGraphics->LoadBitmap(PNGTICKTICK_FN, 2);
    //pGraphics->AttachControl(new IBSwitchControlMidi(offx + 711, offy + 15, bitmap, kParamBoost), -1, "");

    bitmap = pGraphics->LoadBitmap(PNGTOPKNOB_FN, 40, true);
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 42, offy + 52, bitmap, kParamPedal), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 229, offy + 50, bitmap, kParamLowerManual), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 471, offy + 50, bitmap, kParamUpperManual), -1, "main");

    bitmap = pGraphics->LoadBitmap(PNGB4000KNOB1_FN, 41, true);
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 423, offy + 298, bitmap, kParamPercussionLevel), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 476, offy + 298, bitmap, kParamPercussionDecay), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 448, offy + 348, bitmap, kParamPercussionHarmonic), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 606, offy + 307, bitmap, kParamKeyClickLevel), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 676, offy + 296, bitmap, kParamDriveLevel), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 676, offy + 348, bitmap, kParamDriveOutput), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 714, offy + 98, bitmap, kParamSwell), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 714, offy + 163, bitmap, kParamTreble), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 714, offy + 214, bitmap, kParamBass), -1, "main");

    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(181, 60, 181+44, 60+18), kParamSplitLowerManual, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(424, 60, 424+44, 60+18), kParamSplitUpperManual, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");

    bitmap = pGraphics->LoadBitmap(PNGOCT_FN, 3, true);
    std::function<double(double)> mappingFunc = [](double midiVal) {return 63.5*midiVal; };
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 122, offy + 100, bitmap, kParamOct1, mappingFunc), kCtrlOct1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 294, offy + 100, bitmap, kParamOct2, mappingFunc), kCtrlOct2, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 543, offy + 100, bitmap, kParamOct3, mappingFunc), kCtrlOct3, "main");

    bitmap = pGraphics->LoadBitmap(PNGBROWNDRAWBARKNOB_FN, 9, true);
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 36, offy + 146, bitmap, kParamBar1, EDirection::Vertical, 1.), -1, "main");
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 62, offy + 146, bitmap, kParamBar2, EDirection::Vertical, 1.), -1, "main");
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 204, offy + 146, bitmap, kParamBar7, EDirection::Vertical, 1.), -1, "main");
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 230, offy + 146, bitmap, kParamBar8, EDirection::Vertical, 1.), -1, "main");
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 454, offy + 146, bitmap, kParamBar16, EDirection::Vertical, 1.), -1, "main");
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 480, offy + 146, bitmap, kParamBar17, EDirection::Vertical, 1.), -1, "main");

    bitmap = pGraphics->LoadBitmap(PNGWHITEDRAWBARKNOB_FN, 9, true);
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 88, offy + 146, bitmap, kParamBar3, EDirection::Vertical, 1.), -1, "main");
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 114, offy + 146, bitmap, kParamBar4, EDirection::Vertical, 1.), -1, "main");
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 166, offy + 146, bitmap, kParamBar6, EDirection::Vertical, 1.), -1, "main");
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 256, offy + 146, bitmap, kParamBar9, EDirection::Vertical, 1.), -1, "main");
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 282, offy + 146, bitmap, kParamBar10, EDirection::Vertical, 1.), -1, "main");
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 334, offy + 146, bitmap, kParamBar12, EDirection::Vertical, 1.), -1, "main");
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 412, offy + 146, bitmap, kParamBar15, EDirection::Vertical, 1.), -1, "main");
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 506, offy + 146, bitmap, kParamBar18, EDirection::Vertical, 1.), -1, "main");
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 532, offy + 146, bitmap, kParamBar19, EDirection::Vertical, 1.), -1, "main");
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 584, offy + 146, bitmap, kParamBar21, EDirection::Vertical, 1.), -1, "main");
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 662, offy + 146, bitmap, kParamBar24, EDirection::Vertical, 1.), -1, "main");

    bitmap = pGraphics->LoadBitmap(PNGGREYDRAWBARKNOB_FN, 9, true);
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 140, offy + 146, bitmap, kParamBar5, EDirection::Vertical, 1.), -1, "main");
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 308, offy + 146, bitmap, kParamBar11, EDirection::Vertical, 1.), -1, "main");
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 360, offy + 146, bitmap, kParamBar13, EDirection::Vertical, 1.), -1, "main");
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 386, offy + 146, bitmap, kParamBar14, EDirection::Vertical, 1.), -1, "main");
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 558, offy + 146, bitmap, kParamBar20, EDirection::Vertical, 1.), -1, "main");
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 610, offy + 146, bitmap, kParamBar22, EDirection::Vertical, 1.), -1, "main");
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 636, offy + 146, bitmap, kParamBar23, EDirection::Vertical, 1.), -1, "main");

    bitmap = pGraphics->LoadBitmap(PNGVIBRALO_FN, 2);

    std::function<double(double)> mappingFunc2 = [](double midiVal) {if (midiVal * 127 >= 1) return 1; else return 0; };
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 30, offy + 300, bitmap, kParamVibratoLower, mappingFunc2), -1, "main");
    bitmap = pGraphics->LoadBitmap(PNGVIBRAHI_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 86, offy + 300, bitmap, kParamVibratoUpper, mappingFunc2), -1, "main");
    bitmap = pGraphics->LoadBitmap(PNGROTOR_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 352, offy + 300, bitmap, kParamRotor, mappingFunc2), -1, "main");
    bitmap = pGraphics->LoadBitmap(PNGPERCUSSION_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 525, offy + 300, bitmap, kParamPercussion, mappingFunc2), -1, "main");
    bitmap = pGraphics->LoadBitmap(PNGDRIVE_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 720, offy + 300, bitmap, kParamDrive, mappingFunc2), -1, "main");
    bitmap = pGraphics->LoadBitmap(PNGVELOCITY_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 720, offy + 300, bitmap, kParamVelocity, mappingFunc2), -1, "add");

    bitmap = pGraphics->LoadBitmap(PNGFASTSLOW_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 231, offy + 305, bitmap, kParamFastSlow), -1, "main");

    bitmap = pGraphics->LoadBitmap(PNGTICKTICK3_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 253, offy + 382, bitmap, kParamRotorOffAt), -1, "main");

    bitmap = pGraphics->LoadBitmap(PNGKNOB2_FN, 6, true);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 144, offy + 306, bitmap, kParamVibrato), -1, "main");

    bitmap = pGraphics->LoadBitmap(PNGB4000KNOB1_FN, 41, true);
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 70, offy + 297, bitmap, kParamRotorHornSlow), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(75, 333, 103, 347), kParamRotorHornSlow, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 126, offy + 297, bitmap, kParamRotorHornFast), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(129, 333, 157, 347), kParamRotorHornFast, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 181, offy + 297, bitmap, kParamRotorHornAccel), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(183, 333, 211, 347), kParamRotorHornAccel, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 237, offy + 297, bitmap, kParamRotorHornBrake), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(237, 333, 265, 347), kParamRotorHornBrake, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 284, offy + 297, bitmap, kParamRotorHornTone), -1, "add");

    pGraphics->AttachControl(new IBKnobControlMidi(offx + 70, offy + 352, bitmap, kParamRotorBassSlow), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(75, 390, 103, 404), kParamRotorBassSlow, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 126, offy + 352, bitmap, kParamRotorBassFast), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(129, 390, 157, 404), kParamRotorBassFast, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 181, offy + 352, bitmap, kParamRotorBassAccel), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(183, 390, 211, 404), kParamRotorBassAccel, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 236, offy + 352, bitmap, kParamRotorBassBrake), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(237, 390, 265, 404), kParamRotorBassBrake, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 284, offy + 352, bitmap, kParamRotorBassTone), -1, "add");

    pGraphics->AttachControl(new IBKnobControlMidi(offx + 365, offy + 296, bitmap, kParamMicSpread), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 332, offy + 353, bitmap, kParamMicBalance), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 392, offy + 353, bitmap, kParamMicDistance), -1, "add");

    pGraphics->AttachControl(new IBKnobControlMidi(offx + 471, offy + 295, bitmap, kParamToneWheelsCondition), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 471, offy + 353, bitmap, kParamToneWheelsTuning), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 589, offy + 295, bitmap, kParamDrawbarsLeakage), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 589, offy + 353, bitmap, kParamDrawbarsDistortion), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 677, offy + 295, bitmap, kParamEnvelopeAttack), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 677, offy + 353, bitmap, kParamEnvelopeRelease), -1, "add");


    pGraphics->AttachControl(new IBKnobControlMidi(68,91, bitmap, kParamChorusRate), -1, "add");
    pGraphics->AttachControl(new ICaptionControl(IRECT(69, 130, 102, 146), kParamChorusRate, DEFAULT_TEXT, COLOR_WHITE), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(68,192, bitmap, kParamChorusPhase), -1, "add");
    pGraphics->AttachControl(new ICaptionControl(IRECT(69, 231, 102, 247), kParamChorusPhase, DEFAULT_TEXT, COLOR_WHITE), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(166,91, bitmap, kParamChorusDepth), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(166,192, bitmap, kParamChorusFeedback), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(458,91, bitmap, kParamDelayFeedbackLeft), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(458,192, bitmap, kParamDelayFeedbackLeft), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(260,91, bitmap, kParamChorusWet), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(368,91, bitmap, kParamDelayTimeLMS), kCtrlTagDelayTimeLMS, "add");
    pGraphics->AttachControl(new ICaptionControl(IRECT(363, 130, 408, 146), kParamDelayTimeLMS, DEFAULT_TEXT, COLOR_WHITE), kCtrlTagDelayTimeLMSCaption, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(368,192, bitmap, kParamDelayTimeRMS), kCtrlTagDelayTimeRMS, "add");
    pGraphics->AttachControl(new ICaptionControl(IRECT(363, 231, 408, 247), kParamDelayTimeRMS, DEFAULT_TEXT, COLOR_WHITE), kCtrlTagDelayTimeRMSCaption, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(363, 99, 409, 115), kParamDelayTimeLBPM, DEFAULT_TEXT, COLOR_WHITE, true), kCtrlTagDelayTimeLBPM, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(363, 200, 409, 216), kParamDelayTimeRBPM, DEFAULT_TEXT, COLOR_WHITE, true), kCtrlTagDelayTimeRBPM, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(649,91, bitmap, kParamDelayLevelLeft), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(649,192, bitmap, kParamDelayLevelRight), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(738,141, bitmap, kParamDelayWet), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(553,91, bitmap, kParamDelayHidampLeft), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(553,192, bitmap, kParamDelayHidampRight), -1, "add");

    bitmap = pGraphics->LoadBitmap(PNGTICKTICKBYPASS_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 306, offy + 245, bitmap, kParamEffectBypass), -1, "add");

    bitmap = pGraphics->LoadBitmap(PNGTICKTICK3_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 261, offy + 191, bitmap, kParamFlangerChorus), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 465, offy + 150, bitmap, kParamDelayCrossDual), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 698, offy + 98, bitmap, kParamDelayUnitLeft), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 698, offy + 198, bitmap, kParamDelayUnitRight), -1, "add");

    //std::function<double(double)> mappingFunc2 = [](double midiVal) {return midiVal+72./127.; };
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(694, 149, 733, 165), kParamMidiClockBpm, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");

    bitmap = pGraphics->LoadBitmap(PNGTIME_FN);
    pGraphics->AttachControl(new IBitmapControl(368,77, bitmap, kNoParameter), kCtrlTimeL, "add");
    pGraphics->AttachControl(new IBitmapControl(368,176, bitmap, kNoParameter), kCtrlTimeR, "add");
    bitmap = pGraphics->LoadBitmap(PNGLENGTH_FN);
    pGraphics->AttachControl(new IBitmapControl(364, 77, bitmap, kNoParameter), kCtrlLengthL, "add");
    pGraphics->AttachControl(new IBitmapControl(364, 176, bitmap, kNoParameter), kCtrlLengthR, "add");

    IRECT keybRect = IRECT(MARGIN_W, HS_H + MARGIN_H, PLUG_WIDTH - MARGIN_W, HS_H + MARGIN_H + KEYBOARD_H);
    keybCtrl = new IVKeyboardControl(keybRect.FracRectHorizontal(0.85), 36, 91);
    pGraphics->AttachControl(keybCtrl, kCtrlTagKeyboard, "keyboard");

    pGraphics->AttachControl(new ICaptionControl(IRECT(720, 451, 750, 471), kParamKeyboardOctave, DEFAULT_TEXT, COLOR_WHITE, true), -1, "keyboard");

    IVButtonControl* buttCtrl = new IVButtonControl(IRECT(696, 496, 781, 526), [&](IControl*) {
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

    

    

   
    bitmap = pGraphics->LoadBitmap(PNGMIDIACTIVE_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(308,8, bitmap, kParamMidiActive), -1, "header");

    
   
    // Program Change
    /*captionCtrl = new ICaptionControl(IRECT(871, 11, 931, 31), kParamProgram, DEFAULT_TEXT, COLOR_WHITE, true);
    pGraphics->AttachControl(captionCtrl, -1, "header");

    bitmap = pGraphics->LoadBitmap(PNGPLUS_FN);
    pGraphics->AttachControl(new IBButtonControl(931,11, bitmap, [&](IControl*) {
      captionCtrl->SetValueFromUserInput(GetParam(kParamProgram)->ToNormalized(GetParam(kParamProgram)->FromNormalized(captionCtrl->GetValue())+1));
    }
    ), -1, "header");

    bitmap = pGraphics->LoadBitmap(PNGMINUS_FN);
    pGraphics->AttachControl(new IBButtonControl(852, 11, bitmap, [&](IControl*) {
      captionCtrl->SetValueFromUserInput(GetParam(kParamProgram)->ToNormalized(GetParam(kParamProgram)->FromNormalized(captionCtrl->GetValue()) - 1));
    }
    ), -1, "header");*/

    
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
            pCaller->GetUI()->GetControlWithTag(kCtrlLengthL)->Hide(true);
            pCaller->GetUI()->GetControlWithTag(kCtrlTimeL)->Hide(false);
            pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMSCaption)->Hide(false);

          }
          else {
            pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(false);
            pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMSCaption)->Hide(true);
            pCaller->GetUI()->GetControlWithTag(kCtrlLengthL)->Hide(false);
            pCaller->GetUI()->GetControlWithTag(kCtrlTimeL)->Hide(true);
            pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMS)->Hide(true);
          }
        }

        if (pCaller->GetUI()->GetControlWithTag(kCtrlTagAdd)->GetValue() == 1) {
          if (pCaller->GetDelegate()->GetParam(kParamDelayUnitRight)->Value() == 0) {
            pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(true);
            pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMS)->Hide(false);
            pCaller->GetUI()->GetControlWithTag(kCtrlLengthR)->Hide(true);
            pCaller->GetUI()->GetControlWithTag(kCtrlTimeR)->Hide(false);
            pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMSCaption)->Hide(false);
          }
          else {
             pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(false);
             pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMSCaption)->Hide(true);
             pCaller->GetUI()->GetControlWithTag(kCtrlLengthR)->Hide(false);
             pCaller->GetUI()->GetControlWithTag(kCtrlTimeR)->Hide(true);
             pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMS)->Hide(true);
          }
        }

      }
    };

    bitmap = pGraphics->LoadBitmap(PNGMAIN_FN, 2);
    IBSwitchControlFunc *mainCtrl = new IBSwitchControlFunc(156, 8, bitmap, windowFunc, kNoParameter);
    pGraphics->AttachControl(mainCtrl, kCtrlTagMain);
    mainCtrl->SetValue(1);

    bitmap = pGraphics->LoadBitmap(PNGADD_FN, 2);
    IBSwitchControlFunc *addCtrl = new IBSwitchControlFunc(222, 8, bitmap, windowFunc, kNoParameter);
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
    pGraphics->AttachControl(new IBSwitchControlFunc(461, 8, bitmap, resizeFunc, kNoParameter), kCtrlTagMidiMonHide, "");
    bitmap = pGraphics->LoadBitmap(PNGKEYB_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlFunc(384, 8, bitmap, resizeFunc, kNoParameter), kCtrlTagKeybHide, "");

    /*mPresetMenu = new FileBrowser(IRECT(810, 446, 986, 470));
    pGraphics->AttachControl(mPresetMenu, kCtrlTagPresetMenu);



    mMidiLogger = new MidiMonitor(IRECT(HS_W + MARGIN_W, MARGIN_H + MIDILOG_H, HS_W + MIDIPRESET_W - MARGIN_W-20, HS_H-MARGIN_H), "", "", IText(12, COLOR_BLACK, NULL, EAlign::Near), COLOR_WHITE);
    pGraphics->AttachControl(mMidiLogger, kCtrlTagMidiLogger, "midiMonitor");

    pGraphics->AttachControl(new IVSliderControl(IRECT(HS_W + MIDIPRESET_W - MARGIN_W-10, MIDILOG_H, HS_W + MIDIPRESET_W-10, HS_H), [&](IControl* ctrl) {

      mMidiLogger->setEntrypointerOffset(1. - ctrl->GetValue());

    }), kCtrlSliderMidiMon1);

    pGraphics->GetControlWithTag(kCtrlSliderMidiMon1)->SetValue(1.);

    /////////////////////////////////////////
    ICaptionControl* userFactory = new ICaptionControl(IRECT(806, 48, 850, 66), kParamUserFactory, DEFAULT_TEXT, COLOR_WHITE, true);
    userFactory->SetActionFunction([&](IControl* ctrl) {

      if (ctrl->GetValue() == 0) {
        presettext txt;
        for (int k = 50; k > 0; k--) {
          char buffer[30];
          sprintf(buffer, "Factory %d", k);
          strcpy(txt.name, buffer);
          mPresetListSender.SetValRT(txt);
        }
      }
      else {
        presettext txt;
        for (int k = 50; k > 0; k--) {
          char buffer[30];
          sprintf(buffer, "User %d", k);
          strcpy(txt.name, buffer);
          mPresetListSender.SetValRT(txt);
        }
      }
    });

    pGraphics->AttachControl(userFactory,-1, "presetList");

   

    ///////////////////////////////////
    mPresetList = new PresetList(IRECT(HS_W + MARGIN_W, MARGIN_H+70 ,HS_W + MIDIPRESET_W - MARGIN_W - 20, MARGIN_H + MIDILOG_H -50), "", "", IText(12, COLOR_BLACK, NULL, EAlign::Near), COLOR_WHITE);
    pGraphics->AttachControl(mPresetList, kCtrlTagPresetList, "presetList");

    presettext txt;
    for (int k = 50; k > 0; k--) {
      char buffer[30];
      sprintf(buffer,"Factory %d", k);
      strcpy(txt.name, buffer);
      mPresetListSender.SetValRT(txt);
    }

    pGraphics->AttachControl(new IVSliderControl(IRECT(HS_W + MIDIPRESET_W - MARGIN_W - 10, MARGIN_H + 70, HS_W + MIDIPRESET_W - 10, MARGIN_H + MIDILOG_H - 50), [&](IControl* ctrl) {

      mPresetList->setEntrypointerOffset(1. - ctrl->GetValue());

    }), kCtrlSliderPresetList);

    pGraphics->GetControlWithTag(kCtrlSliderPresetList)->SetValue(1.);

   //////////

    IVButtonControl* loadButton = new IVButtonControl(IRECT(802, 214-20, 887, 244-20), [&](IControl*) {
      //mMidiLogger->Clear();
    },

      "Load", IVStyle(DEFAULT_SHOW_LABEL, DEFAULT_SHOW_VALUE, {}, IText(12)));

    buttCtrl->SetAnimation(DefaultAnimationFunc);
    pGraphics->AttachControl(loadButton, -1, "midiMonitor");

    IVButtonControl* saveButton = new IVButtonControl(IRECT(802 + 90, 214-20, 887 + 90, 244-20), [&](IControl*) {
      //mMidiLogger->Clear();
    },

      "Save", IVStyle(DEFAULT_SHOW_LABEL, DEFAULT_SHOW_VALUE, {}, IText(12)));

    buttCtrl->SetAnimation(DefaultAnimationFunc);
    pGraphics->AttachControl(saveButton, -1, "midiMonitor");

    /////////////////////*/

    ///////////////////////////////////////// PRESET /////////////////////////////////////////////////////////////


    bitmap = pGraphics->LoadBitmap(PNGCLEAR_FN, 1);
    IBButtonControl* clearCtrl = new IBButtonControl(HS_W + 64, 351, bitmap, [&](IControl*) {mMidiLogger->Clear(); });
    pGraphics->AttachControl(clearCtrl, kCtrlTagClear, "midiMonitor");



    mMidiLogger = new MidiMonitor(IRECT(HS_W + 14, 260, HS_W + 196, 325), "", "", IText(12, COLOR_BLACK, NULL, EAlign::Near), COLOR_WHITE);
    pGraphics->AttachControl(mMidiLogger, kCtrlTagMidiLogger, "midiMonitor");

    bitmap = pGraphics->LoadBitmap(PNGSLIDER_FN, 1);
    pGraphics->AttachControl(new IBSliderControl(HS_W + 210, 257, 70, -1, bitmap), kCtrlSliderMidiMon1);
    pGraphics->GetControlWithTag(kCtrlSliderMidiMon1)->SetActionFunction([&](IControl* ctrl) {mMidiLogger->setEntrypointerOffset(1. - ctrl->GetValue()); });
    pGraphics->GetControlWithTag(kCtrlSliderMidiMon1)->SetValue(1.);

    bitmap = pGraphics->LoadBitmap(PNGRECALL_FN, 1);
    IBButtonControl* RecallCtrl = new IBButtonControl(HS_W + 7, 222, bitmap, [&](IControl*) {});
    RecallCtrl->SetActionFunction([&](IControl* ctrl) {
      mPresetList->mActiveRow = mPresetList->mSelectedRow;
      GetUI()->GetControlWithTag(kCtrlProgram)->SetValue((double)mPresetList->mActiveRow / (mPresetList->maxLogSamples - 1.));
      GetUI()->GetControlWithTag(kCtrlProgram)->SetDirty();
      });
    pGraphics->AttachControl(RecallCtrl, -1, "midiMonitor");

    bitmap = pGraphics->LoadBitmap(PNGOVERWRITE_FN, 1);
    IBButtonControl* overwriteCtrl = new IBButtonControl(HS_W + 125, 222, bitmap, [&](IControl*) {});
    pGraphics->AttachControl(overwriteCtrl, -1, "midiMonitor");

    /////////////////////////////////////////////////////////////////////////

    mPresetList = new PresetList(IRECT(HS_W + 14, 70, HS_W + 196, 196), "", "", IText(12, COLOR_BLACK, NULL, EAlign::Near), COLOR_WHITE);
    pGraphics->AttachControl(mPresetList, kCtrlTagPresetList, "presetList");

    //presettext txt;
    for (int k = 0; k < 50; k++) {
      char buffer[30];
      sprintf(buffer, "%0*d - Factory", 2, k + 1);
      WDL_String str(buffer);
      mPresetList->addItem(str);
    }

    bitmap = pGraphics->LoadBitmap(PNGSLIDER_FN, 1);
    pGraphics->AttachControl(new IBSliderControl(HS_W + 210, 68, 130, -1, bitmap), kCtrlSliderPresetList);
    pGraphics->GetControlWithTag(kCtrlSliderPresetList)->SetActionFunction([&](IControl* ctrl) {mPresetList->setFirstRowToShowNormalized(ctrl->GetValue()); });
    pGraphics->GetControlWithTag(kCtrlSliderPresetList)->SetValue(1.);

    ///////////////////////////////////////// CAPTION USER/FACTORY /////////////////////////////////////////////////////////////

    ICaptionControl* userFactory = new ICaptionControl(IRECT(HS_W + 9, 36, HS_W + 114, 55), kParamUserFactory, DEFAULT_TEXT, COLOR_WHITE, true);
    userFactory->SetActionFunction([&](IControl* ctrl) {
      static int activeRowUser = 0;
      static int activeRowFactory = 0;

      if (ctrl->GetValue() == 0) {
        activeRowUser = mPresetList->mActiveRow; // save
        mPresetList->Clear();
        for (int k = 0; k < 50; k++) {
          char buffer[30];
          sprintf(buffer, "%0*d - Factory", 2, k + 1);
          WDL_String str(buffer);
          mPresetList->addItem(str);
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
          sprintf(buffer, "%0*d - User", 2, k + 1);
          WDL_String str(buffer);
          mPresetList->addItem(str);
        }
        mPresetList->mActiveRow = activeRowUser;
        mPresetList->mSelectedRow = activeRowUser;
        mPresetList->SnapToRow(activeRowUser);
      }
      });

    pGraphics->AttachControl(userFactory, -1, "presetList");



    ///////////////////////////////////

    // Program Change
    IText t;
    t.mSize = 16;
    captionCtrl = new ICaptionControl(IRECT(HS_W + 149, 33, HS_W + 211, 57), kParamProgram, t, COLOR_LIGHT_GRAY, true);
    captionCtrl->SetActionFunction([&](IControl*) {
      mPresetList->setActiveRow(GetParam(kParamProgram)->Value() - 1);
      });
    pGraphics->AttachControl(captionCtrl, kCtrlProgram, "");

    bitmap = pGraphics->LoadBitmap(PNGPLUS_FN);
    pGraphics->AttachControl(new IBButtonControl(HS_W + 211, 33, bitmap, [&](IControl*) {
      captionCtrl->SetValue(GetParam(kParamProgram)->ToNormalized(GetParam(kParamProgram)->Value() + 1));
      captionCtrl->SetDirty();
      }
    ), -1, "");

    bitmap = pGraphics->LoadBitmap(PNGMINUS_FN);
    pGraphics->AttachControl(new IBButtonControl(HS_W + 125, 33, bitmap, [&](IControl*) {

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
    }
  };
  
#endif
}

#if IPLUG_DSP
void B4000::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
  const int nChans = NOutChansConnected();
  
  for (auto s = 0; s < nFrames; s++) {
    for (auto c = 0; c < nChans; c++) {
      outputs[c][s] = 0.;
    }
  }
}

void B4000::OnIdle()
{
  mMidiLoggerSender.TransmitData(*this);
  //mPresetListSender.TransmitData(*this);
}

void B4000::OnReset()
{
}

void B4000::OnUIOpen() {

  SendCurrentParamValuesFromDelegate();

  // Presetname
  //mPresetMenu->restorePresetPath(mCurrentPresetPath.Get());
}

bool B4000::OnMessage(int messageTag, int controlTag, int dataSize, const void *pData) {

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

// SendMidiMsgFromUI: GUI -> MIDI OUT
// MIDI IN -> ProcessMidiMsg(Monitor, GUI Update)

//void B4000::SendMidiMsgFromUI(const IMidiMsg& msg) {
  //if (mMidiActive) {
  //  SendMidiMsg(msg);
  //  mMidiLoggerSender.SetValRT(msg);
  //}
//}


// wird nur von Keyboard und control bewegungen aufgerufen
void B4000::ProcessMidiMsg(const IMidiMsg& msg)
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
     // if (GetUI()) {
       // if (GetUI()->GetControlWithTag(kCtrlOct3)) {
      //    GetUI()->GetControlWithTag(kCtrlOct3)->SetValueFromDelegate(msg.mData2 / 2.);
      //  }

      //}
     // }
      mMidiLoggerSender.SetValRT(msg);
    }
  }
//handle:
  //if (mMidiActive) {
    //SendMidiMsg(msg); // nach außen
    
    //if (msg. == IMidiMsg::kProgramChange) {
    //SendMidiMsgFromDelegate(msg); // to controls

  //}
}

void B4000::OnParamChange(int paramIdx)
{
  IMidiMsg msg;
  static IMidiMsg msgAlt;
  static double valAlt = 0;

  // Param Linked To CC or Aftertouch ?
  if (paramToCC[paramIdx] >= 0) {

    msg.Clear();
    if (paramToMsgType[paramIdx] == 0) { //CC
      msg.mStatus = mChannel | (IMidiMsg::kControlChange << 4);
    }
    else if (paramToMsgType[paramIdx] == 1) { // Aftertouch
      msg.mStatus = mChannel | (IMidiMsg::kPolyAftertouch << 4);
    }
    msg.mData1 = paramToCC[paramIdx];
    msg.mData2 = (int)(GetParam(paramIdx)->GetNormalized() * 127.0); // 0:1 -> 0-:127

    // Special Values
    switch (paramIdx) {
    case kParamDelayTimeLBPM:
    case kParamDelayTimeRBPM:
      msg.mData2 = GetParam(paramIdx)->Value(); // BPM -> Not Normalized
      break;
    case kParamMidiClockBpm:
      msg.mData2 = GetParam(paramIdx)->Value()-72; // Midi Clock 72:199 -> 0:127
      break;
    case kParamVibrato:
      switch ((int)GetParam(paramIdx)->Value()) {
      case 0: msg.mData2 = 10; break; // 10,30,50,70,90,120
      case 1: msg.mData2 = 30; break;
      case 2: msg.mData2 = 50; break;
      case 3: msg.mData2 = 70; break;
      case 4: msg.mData2 = 90; break;
      case 5: msg.mData2 = 120; break;
      }
      break;
    case kParamOct1:
    case kParamOct2:
    case kParamOct3:
      msg.mData2 = GetParam(paramIdx)->Value() + 1; // -1,0,1 -> 0,1,2
      break;
    }

    msg.mOffset = -2; // tell ProcessMidiMsg that msg comes from UI
  }

  if (msg.mStatus != msgAlt.mStatus || msg.mData1 != msgAlt.mData1 || msg.mData2 != msgAlt.mData2) {
    SendMidiMsgFromUI(msg);
  }
  msgAlt = msg;
 
  // Other Stuff
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
          
      // Dino Spezialität Preset mit Wheel
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
            GetUI()->GetControlWithTag(kCtrlLengthL)->Hide(true);
            GetUI()->GetControlWithTag(kCtrlTimeL)->Hide(false);
            GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMSCaption)->Hide(false);

          }
          else {
            GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(false);
            GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMSCaption)->Hide(true);
            GetUI()->GetControlWithTag(kCtrlLengthL)->Hide(false);
            GetUI()->GetControlWithTag(kCtrlTimeL)->Hide(true);
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
            GetUI()->GetControlWithTag(kCtrlLengthR)->Hide(true);
            GetUI()->GetControlWithTag(kCtrlTimeR)->Hide(false);
            GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMSCaption)->Hide(false);
          }
          else {
            GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(false);
            GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMSCaption)->Hide(true);
            GetUI()->GetControlWithTag(kCtrlLengthR)->Hide(false);
            GetUI()->GetControlWithTag(kCtrlTimeR)->Hide(true);
            GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMS)->Hide(true);
          }
        }
      }
      break; 
    default:
    break;
  }
}

bool B4000::SerializeState(IByteChunk& chunk) const {

  TRACE;

 
  // Presetname
  WDL_String s;
  s.Set(mCurrentPresetPath.Get());
  chunk.PutStr(s.Get());

  return SerializeParams(chunk);
}

// this over-ridden method is called when the host is trying to load the plug-in state and you need to unpack the data into your algorithm
// HIER KÖNNEN KEINE CONTROLS GEUPDATED WERDEN; DA MGRAPHICS NOCH NICHT EXISTIERT!!!!
int B4000::UnserializeState(const IByteChunk& chunk, int startPos) {

  TRACE;

 
  int pos;
  // Presetname
  WDL_String str;
  pos = chunk.GetStr(str, pos);
  mCurrentPresetPath.Set(str.Get());

  return UnserializeParams(chunk, pos);
}
#endif
