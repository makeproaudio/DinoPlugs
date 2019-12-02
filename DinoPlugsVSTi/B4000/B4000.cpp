#include "B4000.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"
#include "json.hpp"
#include <fstream>

B4000::B4000(IPlugInstanceInfo instanceInfo)
: IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo)
{

  //for (int k = 0; k < 50; k++)
  //{
  //  presetname[k].Set("",64);
  //}

  /*presetname[0].Set("00: Made In Japan");
  presetname[1].Set("01: 5th");
  presetname[2].Set("02: Augernization");
  presetname[3].Set("03: Church");
  presetname[4].Set("04: Fast Rotary");
  presetname[5].Set("05: For Percs Only");
  presetname[6].Set("06: Slow Attack");
  presetname[7].Set("07: Landing");
  presetname[8].Set("08: Soft Perc");
  presetname[9].Set("09: Dr John");
  presetname[10].Set("10: Acid Jazz");
  presetname[11].Set("11: 8' For Brian");
  presetname[12].Set("12: Scanner");
  presetname[13].Set("13: Nearly Full");
  presetname[14].Set("14: Fast But Sad");
  presetname[15].Set("15: Full");
  presetname[16].Set("16: Smoke");
  presetname[17].Set("17: Spooky Tooth");
  presetname[18].Set("18: Groove Tubes");
  presetname[19].Set("19: Who's In The House");
  presetname[20].Set("20: Strange Perc");
  presetname[21].Set("21: Velo-City");
  presetname[22].Set("22: Overtone 5");
  presetname[23].Set("23: Smooth Scanner");
  presetname[24].Set("24: Simple Sixteen");
  presetname[25].Set("25: The Cat");
  presetname[26].Set("26: Steppy");
  presetname[27].Set("27: Jazzy Perc");
  presetname[28].Set("28: Plop");
  presetname[29].Set("29: Motown");
  presetname[30].Set("30: Love Letter");
  presetname[31].Set("31: Blue Soul");
  presetname[32].Set("32: One Drop");
  presetname[33].Set("33: Tilt");
  presetname[34].Set("34: J.S. Bach");
  presetname[35].Set("35: Wailers");
  presetname[36].Set("36: Hollow Stops");
  presetname[37].Set("37: U");
  presetname[38].Set("38: Waiting In Vain");
  presetname[39].Set("39: Perc on");
  presetname[40].Set("40: 87654321");
  presetname[41].Set("41: The Harder They Spin");
  presetname[42].Set("42: Nonharmonic");
  presetname[43].Set("43: Upwards");
  presetname[44].Set("44: C3 Chorus");
  presetname[45].Set("45: Soul Madness");
  presetname[46].Set("46: 4'+1'");
  presetname[47].Set("47: Softy");
  presetname[48].Set("48: 16'+1 1/3'");
  presetname[49].Set("49: Otis");*/

  presetname[0] = "00: Made In Japan";
  presetname[1 ]="01: 5th";
  presetname[2 ]="02: Augernization";
  presetname[3 ]="03: Church";
  presetname[4 ]="04: Fast Rotary";
  presetname[5 ]="05: For Percs Only";
  presetname[6 ]="06: Slow Attack";
  presetname[7 ]="07: Landing";
  presetname[8 ]="08: Soft Perc";
  presetname[9 ]="09: Dr John";
  presetname[10]="10: Acid Jazz";
  presetname[11]="11: 8' For Brian";
  presetname[12]="12: Scanner";
  presetname[13]="13: Nearly Full";
  presetname[14]="14: Fast But Sad";
  presetname[15]="15: Full";
  presetname[16]="16: Smoke";
  presetname[17]="17: Spooky Tooth";
  presetname[18]="18: Groove Tubes";
  presetname[19]="19: Who's In The House";
  presetname[20]="20: Strange Perc";
  presetname[21]="21: Velo-City";
  presetname[22]="22: Overtone 5";
  presetname[23]="23: Smooth Scanner";
  presetname[24]="24: Simple Sixteen";
  presetname[25]="25: The Cat";
  presetname[26]="26: Steppy";
  presetname[27]="27: Jazzy Perc";
  presetname[28]="28: Plop";
  presetname[29]="29: Motown";
  presetname[30]="30: Love Letter";
  presetname[31]="31: Blue Soul";
  presetname[32]="32: One Drop";
  presetname[33]="33: Tilt";
  presetname[34]="34: J.S. Bach";
  presetname[35]="35: Wailers";
  presetname[36]="36: Hollow Stops";
  presetname[37]="37: U";
  presetname[38]="38: Waiting In Vain";
  presetname[39]="39: Perc on";
  presetname[40]="40: 87654321";
  presetname[41]="41: The Harder They Spin";
  presetname[42]="42: Nonharmonic";
  presetname[43]="43: Upwards";
  presetname[44]="44: C3 Chorus";
  presetname[45]="45: Soul Madness";
  presetname[46]="46: 4'+1'";
  presetname[47]="47: Softy";
  presetname[48]="48: 16'+1 1/3'";
  presetname[49] = "49: Otis";


  #include "../MPA Code/GlobalParamInit.h" 

  // B5 is missed in original Pluginmanager, here also:
  GetParam(kParamSplitLowerManual)->InitEnum("Split Lower Manual", 0, 128, "", 0, "", "C-2", "C#-2", "D-2", "D#-2", "E-2", "F-2", "F#-2", "G-2", "G#-2", "A-2", "A#-2", "B-2", "C-1", "C#-1", "D-1", "D#-1", "E-1", "F-1", "F#-1", "G-1", "G#-1", "A-1", "A#-1", "B-1", "C0", "C#0", "D0", "D#0", "E0", "F0", "F#0", "G0", "G#0", "A0", "A#0", "B0", "C1", "C#1", "D1", "D#1", "E1", "F1", "F#1", "G1", "G#1", "A1", "A#1", "B1", "C2", "C#2", "D2", "D#2", "E2", "F2", "F#2", "G2", "G#2", "A2", "A#2", "B2", "C3", "C#3", "D3", "D#3", "E3", "F3", "F#3", "G3", "G#3", "A3", "A#3", "B3", "C4", "C#4", "D4", "D#4", "E4", "F4", "F#4", "G4", "G#4", "A4", "A#4", "B4", "C5", "C#5", "D5", "D#5", "E5", "F5", "F#5", "G5", "G#5", "A5", "A#5", "C6", "C#6", "D6", "D#6", "E6", "F6", "F#6", "G6", "G#6", "A6", "A#6", "B6", "C7", "C#7", "D7", "D#7", "E7", "F7", "F#7", "G7", "G#7", "A7", "A#7", "B7", "C8", "C#8", "D8", "D#8", "E8", "F8", "F#8", "G8", "G#8");

  // This is super crazy, kParamSplitUpperManual changes to 5007 in GetParam. The exception. Cause could be array access out of bounds.
  try {
    GetParam(kParamSplitUpperManual)->InitEnum("Split Upper Manual", 0, 128, "", 0, "", "C-2", "C#-2", "D-2", "D#-2", "E-2", "F-2", "F#-2", "G-2", "G#-2", "A-2", "A#-2", "B-2", "C-1", "C#-1", "D-1", "D#-1", "E-1", "F-1", "F#-1", "G-1", "G#-1", "A-1", "A#-1", "B-1", "C0", "C#0", "D0", "D#0", "E0", "F0", "F#0", "G0", "G#0", "A0", "A#0", "B0", "C1", "C#1", "D1", "D#1", "E1", "F1", "F#1", "G1", "G#1", "A1", "A#1", "B1", "C2", "C#2", "D2", "D#2", "E2", "F2", "F#2", "G2", "G#2", "A2", "A#2", "B2", "C3", "C#3", "D3", "D#3", "E3", "F3", "F#3", "G3", "G#3", "A3", "A#3", "B3", "C4", "C#4", "D4", "D#4", "E4", "F4", "F#4", "G4", "G#4", "A4", "A#4", "B4", "C5", "C#5", "D5", "D#5", "E5", "F5", "F#5", "G5", "G#5", "A5", "A#5", "C6", "C#6", "D6", "D#6", "E6", "F6", "F#6", "G6", "G#6", "A6", "A#6", "B6", "C7", "C#7", "D7", "D#7", "E7", "F7", "F#7", "G7", "G#7", "A7", "A#7", "B7", "C8", "C#8", "D8", "D#8", "E8", "F8", "F#8", "G8", "G#8");
  }
  catch (...) { return; }
  try {
    GetParam(kParamSplitUpperManual)->InitEnum("Split Upper Manual", 0, 128, "", 0, "", "C-2", "C#-2", "D-2", "D#-2", "E-2", "F-2", "F#-2", "G-2", "G#-2", "A-2", "A#-2", "B-2", "C-1", "C#-1", "D-1", "D#-1", "E-1", "F-1", "F#-1", "G-1", "G#-1", "A-1", "A#-1", "B-1", "C0", "C#0", "D0", "D#0", "E0", "F0", "F#0", "G0", "G#0", "A0", "A#0", "B0", "C1", "C#1", "D1", "D#1", "E1", "F1", "F#1", "G1", "G#1", "A1", "A#1", "B1", "C2", "C#2", "D2", "D#2", "E2", "F2", "F#2", "G2", "G#2", "A2", "A#2", "B2", "C3", "C#3", "D3", "D#3", "E3", "F3", "F#3", "G3", "G#3", "A3", "A#3", "B3", "C4", "C#4", "D4", "D#4", "E4", "F4", "F#4", "G4", "G#4", "A4", "A#4", "B4", "C5", "C#5", "D5", "D#5", "E5", "F5", "F#5", "G5", "G#5", "A5", "A#5", "C6", "C#6", "D6", "D#6", "E6", "F6", "F#6", "G6", "G#6", "A6", "A#6", "B6", "C7", "C#7", "D7", "D#7", "E7", "F7", "F#7", "G7", "G#7", "A7", "A#7", "B7", "C8", "C#8", "D8", "D#8", "E8", "F8", "F#8", "G8", "G#8");
  }
  catch (...) { return; }
  try {
    GetParam(kParamSplitUpperManual)->InitEnum("Split Upper Manual", 0, 128, "", 0, "", "C-2", "C#-2", "D-2", "D#-2", "E-2", "F-2", "F#-2", "G-2", "G#-2", "A-2", "A#-2", "B-2", "C-1", "C#-1", "D-1", "D#-1", "E-1", "F-1", "F#-1", "G-1", "G#-1", "A-1", "A#-1", "B-1", "C0", "C#0", "D0", "D#0", "E0", "F0", "F#0", "G0", "G#0", "A0", "A#0", "B0", "C1", "C#1", "D1", "D#1", "E1", "F1", "F#1", "G1", "G#1", "A1", "A#1", "B1", "C2", "C#2", "D2", "D#2", "E2", "F2", "F#2", "G2", "G#2", "A2", "A#2", "B2", "C3", "C#3", "D3", "D#3", "E3", "F3", "F#3", "G3", "G#3", "A3", "A#3", "B3", "C4", "C#4", "D4", "D#4", "E4", "F4", "F#4", "G4", "G#4", "A4", "A#4", "B4", "C5", "C#5", "D5", "D#5", "E5", "F5", "F#5", "G5", "G#5", "A5", "A#5", "C6", "C#6", "D6", "D#6", "E6", "F6", "F#6", "G6", "G#6", "A6", "A#6", "B6", "C7", "C#7", "D7", "D#7", "E7", "F7", "F#7", "G7", "G#7", "A7", "A#7", "B7", "C8", "C#8", "D8", "D#8", "E8", "F8", "F#8", "G8", "G#8");
  }
  catch (...) { return; }

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
  
  paramToCC[kParamPedal                      ]=58;
  paramToCC[kParamLowerManual                ]=57;
  paramToCC[kParamUpperManual                ]=56;
  paramToCC[kParamPercussionLevel            ]=36;
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
  paramToCC[kParamRotorHornTone              ]=35;
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

    bitmap = pGraphics->LoadBitmap(FN_PANEL);
    IControl* panel = new IBitmapControl(0, 0, bitmap, kNoParameter);
    pGraphics->AttachControl(panel, -1, "");

    bitmap = pGraphics->LoadBitmap(FN_MIDIMONBACK);
    IControl* midiCtrlBack = new IBitmapControl(HS_W, 0, bitmap, kNoParameter);
    pGraphics->AttachControl(midiCtrlBack, kCtrlTagMidiBack, "midiMonitor");

    bitmap = pGraphics->LoadBitmap(FN_HEADER);
    IControl* mainPanelHeadCtrl = new IBitmapControl(0, 0, bitmap, kNoParameter);
    pGraphics->AttachControl(mainPanelHeadCtrl);

    bitmap = pGraphics->LoadBitmap(FN_MAINPANEL);
    IControl* mainpanel = new IBitmapControl(18, 40, bitmap, kNoParameter);
    pGraphics->AttachControl(mainpanel, -1, "main");

    bitmap = pGraphics->LoadBitmap(FN_ADDPANEL);
    IControl* addpanel = new IBitmapControl(18, 40, bitmap, kNoParameter);
    pGraphics->AttachControl(addpanel, -1, "add");

    int offx = 0;
    int offy = 0;
    bitmap = pGraphics->LoadBitmap(FN_B4000KNOB,64,true);
    
    bitmap = pGraphics->LoadBitmap(FN_TICKTICK, 2);
 
    bitmap = pGraphics->LoadBitmap(FN_TOPKNOB, 40, true);
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 42, offy + 52, bitmap, kParamPedal), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 229, offy + 50, bitmap, kParamLowerManual), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 471, offy + 50, bitmap, kParamUpperManual), -1, "main");

    bitmap = pGraphics->LoadBitmap(FN_B4000KNOB1, 41, true);
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

    bitmap = pGraphics->LoadBitmap(FN_OCT, 3, true);
    std::function<double(double)> mappingFunc = [](double midiVal) {return 63.5*midiVal; };
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 122, offy + 100, bitmap, kParamOct1, mappingFunc), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 294, offy + 100, bitmap, kParamOct2, mappingFunc), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 543, offy + 100, bitmap, kParamOct3, mappingFunc), -1, "main");

    bitmap = pGraphics->LoadBitmap(FN_BROWNDRAWBARKNOB, 9, true);
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 36, offy + 146, bitmap, kParamBar1, EDirection::Vertical, 1.), -1, "main");
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 62, offy + 146, bitmap, kParamBar2, EDirection::Vertical, 1.), -1, "main");
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 204, offy + 146, bitmap, kParamBar7, EDirection::Vertical, 1.), -1, "main");
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 230, offy + 146, bitmap, kParamBar8, EDirection::Vertical, 1.), -1, "main");
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 454, offy + 146, bitmap, kParamBar16, EDirection::Vertical, 1.), -1, "main");
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 480, offy + 146, bitmap, kParamBar17, EDirection::Vertical, 1.), -1, "main");

    bitmap = pGraphics->LoadBitmap(FN_WHITEDRAWBARKNOB, 9, true);
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

    bitmap = pGraphics->LoadBitmap(FN_GREYDRAWBARKNOB, 9, true);
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 140, offy + 146, bitmap, kParamBar5, EDirection::Vertical, 1.), -1, "main");
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 308, offy + 146, bitmap, kParamBar11, EDirection::Vertical, 1.), -1, "main");
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 360, offy + 146, bitmap, kParamBar13, EDirection::Vertical, 1.), -1, "main");
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 386, offy + 146, bitmap, kParamBar14, EDirection::Vertical, 1.), -1, "main");
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 558, offy + 146, bitmap, kParamBar20, EDirection::Vertical, 1.), -1, "main");
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 610, offy + 146, bitmap, kParamBar22, EDirection::Vertical, 1.), -1, "main");
    pGraphics->AttachControl(new IBDrawbarControlMidi(offx + 636, offy + 146, bitmap, kParamBar23, EDirection::Vertical, 1.), -1, "main");

    bitmap = pGraphics->LoadBitmap(FN_VIBRALO, 2);

    std::function<double(double)> mappingFunc2 = [](double midiVal) {if (midiVal * 127 >= 1) return 1; else return 0; };
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 30, offy + 300, bitmap, kParamVibratoLower, mappingFunc2), -1, "main");
    bitmap = pGraphics->LoadBitmap(FN_VIBRAHI, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 86, offy + 300, bitmap, kParamVibratoUpper, mappingFunc2), -1, "main");
    bitmap = pGraphics->LoadBitmap(FN_ROTOR, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 352, offy + 300, bitmap, kParamRotor, mappingFunc2), -1, "main");
    bitmap = pGraphics->LoadBitmap(FN_PERCUSSION, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 525, offy + 300, bitmap, kParamPercussion, mappingFunc2), -1, "main");
    bitmap = pGraphics->LoadBitmap(FN_DRIVE, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 720, offy + 300, bitmap, kParamDrive, mappingFunc2), -1, "main");
    bitmap = pGraphics->LoadBitmap(FN_VELOCITY, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 720, offy + 300, bitmap, kParamVelocity, mappingFunc2), -1, "add");

    bitmap = pGraphics->LoadBitmap(FN_FASTSLOW, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 231, offy + 305, bitmap, kParamFastSlow), -1, "main");

    bitmap = pGraphics->LoadBitmap(FN_TICKTICK3, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 253, offy + 382, bitmap, kParamRotorOffAt), -1, "main");

    bitmap = pGraphics->LoadBitmap(FN_KNOB2, 6, true);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 144, offy + 306, bitmap, kParamVibrato), -1, "main");

    bitmap = pGraphics->LoadBitmap(FN_B4000KNOB1, 41, true);
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
    pGraphics->AttachControl(new IBKnobControlMidi(368,192, bitmap, kParamDelayTimeRMS), kCtrlTagDelayTimeRMS, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(363, 99, 409, 115), kParamDelayTimeLBPM, DEFAULT_TEXT, COLOR_WHITE, true), kCtrlTagDelayTimeLBPM, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(363, 200, 409, 216), kParamDelayTimeRBPM, DEFAULT_TEXT, COLOR_WHITE, true), kCtrlTagDelayTimeRBPM, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(649,91, bitmap, kParamDelayLevelLeft), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(649,192, bitmap, kParamDelayLevelRight), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(738,141, bitmap, kParamDelayWet), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(553,91, bitmap, kParamDelayHidampLeft), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(553,192, bitmap, kParamDelayHidampRight), -1, "add");

    bitmap = pGraphics->LoadBitmap(FN_TICKTICKBYPASS, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 306, offy + 245, bitmap, kParamEffectBypass), -1, "add");

    bitmap = pGraphics->LoadBitmap(FN_TICKTICK3, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 261, offy + 191, bitmap, kParamFlangerChorus), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 465, offy + 150, bitmap, kParamDelayCrossDual), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 698, offy + 98, bitmap, kParamDelayUnitLeft), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 698, offy + 198, bitmap, kParamDelayUnitRight), -1, "add");

    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(694, 149, 733, 165), kParamMidiClockBpm, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");

    bitmap = pGraphics->LoadBitmap(FN_TIME);
    pGraphics->AttachControl(new IBitmapControl(368,77, bitmap, kNoParameter), kCtrlTimeL, "add");
    pGraphics->AttachControl(new IBitmapControl(368,176, bitmap, kNoParameter), kCtrlTimeR, "add");
    bitmap = pGraphics->LoadBitmap(FN_LENGTH);
    pGraphics->AttachControl(new IBitmapControl(364, 77, bitmap, kNoParameter), kCtrlLengthL, "add");
    pGraphics->AttachControl(new IBitmapControl(364, 176, bitmap, kNoParameter), kCtrlLengthR, "add");
   
    bitmap = pGraphics->LoadBitmap(FN_MIDIACTIVE, 2);
    pGraphics->AttachControl(new IBitmapControl(308, 8, bitmap, kParamMidiActive), kCtrlMidiActive, "");
    pGraphics->GetControlWithTag(kCtrlMidiActive)->SetActionFunction([&](IControl *ctrl)
      {
        if (GetUI())
        {
          for (auto c = 0; c < GetUI()->NControls(); c++) // TODO: could keep a map
          {
            IControl* pControl = GetUI()->GetControl(c);
            bool midiActive = GetParam(kParamMidiActive)->Value();
            pControl->SetWantsMidi(midiActive);
          }
        }
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
            pCaller->GetUI()->GetControlWithTag(kCtrlLengthL)->Hide(true);
            pCaller->GetUI()->GetControlWithTag(kCtrlTimeL)->Hide(false);

          }
          else {
            pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(false);
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
          }
          else {
             pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(false);
             pCaller->GetUI()->GetControlWithTag(kCtrlLengthR)->Hide(false);
             pCaller->GetUI()->GetControlWithTag(kCtrlTimeR)->Hide(true);
             pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMS)->Hide(true);
          }
        }
      }
    };

    bitmap = pGraphics->LoadBitmap(FN_MAIN, 2);
    IBSwitchControlFunc *mainCtrl = new IBSwitchControlFunc(156, 8, bitmap, windowFunc, kNoParameter);
    pGraphics->AttachControl(mainCtrl, kCtrlTagMain);
    mainCtrl->SetValue(1);

    bitmap = pGraphics->LoadBitmap(FN_ADD, 2);
    IBSwitchControlFunc *addCtrl = new IBSwitchControlFunc(222, 8, bitmap, windowFunc, kNoParameter);
    pGraphics->AttachControl(addCtrl, kCtrlTagAdd);

    // MIXER UI
#include "../MPA Code/MixerUI.h"

    // KEYBOARD UI
#include "../MPA Code/KeyboardUI.h"

// RESIZE CONTROLS ////////////////////////////////////////////////////////////////////////////////////////////////

#include "../MPA Code/Resize.h" 

    bitmap = pGraphics->LoadBitmap(FN_MIDIMONITOR, 2);
    IBSwitchControl *presetUI = new IBSwitchControl(538, 8, bitmap, kNoParameter);
    pGraphics->AttachControl(presetUI, kCtrlTagMidiMonHide, "");
    presetUI->SetActionFunction(resizeFunc);

    bitmap = pGraphics->LoadBitmap(FN_MIXER, 2); // MIXER UI
    IBSwitchControl *mixerUICtrl = new IBSwitchControl(461, 8, bitmap, kNoParameter);
    pGraphics->AttachControl(mixerUICtrl, kCtrlTagMixerHide, "");
    mixerUICtrl->SetActionFunction(resizeFunc);

    bitmap = pGraphics->LoadBitmap(FN_KEYB, 2);
    IBSwitchControl *keybCtrl = new IBSwitchControl(384, 8, bitmap, kNoParameter);
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
    IBButtonControl* clearCtrl = new IBButtonControl(HS_W + 64, 383, bitmap, [&](IControl*) {mMidiLogger->Clear(); });
    pGraphics->AttachControl(clearCtrl, kCtrlTagClear, "midiMonitor");

    mMidiLogger = new MidiMonitor(IRECT(HS_W + 14, 379-84, HS_W + 196, 454-84), "", "", IText(12, COLOR_BLACK, "Calibri", EAlign::Near), COLOR_WHITE);
    pGraphics->AttachControl(mMidiLogger, kCtrlTagMidiLogger, "midiMonitor");

    bitmap = pGraphics->LoadBitmap(FN_SLIDER, 1);
    pGraphics->AttachControl(new IBSliderControlScroll(HS_W + 210, 378-84, 75, -1, bitmap), kCtrlSliderMidiMon1);
    pGraphics->GetControlWithTag(kCtrlSliderMidiMon1)->SetActionFunction([&](IControl* ctrl) {mMidiLogger->setEntrypointerOffset(1. - ctrl->GetValue()); });
    pGraphics->GetControlWithTag(kCtrlSliderMidiMon1)->SetValue(1.);

    bitmap = pGraphics->LoadBitmap(FN_RECALL, 1);
    IBButtonControl* RecallCtrl = new IBButtonControl(HS_W + 7, 321-84, bitmap, [&](IControl*) {});
    RecallCtrl->SetActionFunction([&](IControl* ctrl) {
      mPresetList->mActiveRow = mPresetList->mSelectedRow;
      GetUI()->GetControlWithTag(kCtrlProgram)->SetValue((double)mPresetList->mActiveRow / (mPresetList->maxLogSamples - 1.));
      GetUI()->GetControlWithTag(kCtrlProgram)->SetDirty();
      });
    pGraphics->AttachControl(RecallCtrl, -1, "midiMonitor");

        bitmap = pGraphics->LoadBitmap(FN_OVERWRITE, 1);
    IBButtonControl* overwriteCtrl = new IBButtonControl(HS_W+85, 321-84, bitmap, [&](IControl* pCaller)
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
    IBButtonControl* resetCtrl = new IBButtonControl(HS_W + 164, 321-84, bitmap,

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

    mPresetList = new PresetList(IRECT(HS_W + 14, 97, HS_W + 196, 310-84), 10, "", "", IText(12, COLOR_BLACK, "Calibri", EAlign::Near), COLOR_WHITE);
    pGraphics->AttachControl(mPresetList, kCtrlTagPresetList, "presetList");

    //presettext txt;
    for (int k = 0; k < 50; k++) {
		 // mPresetList->addItem(presetname[k]);
      WDL_String str;
      str.Set(presetname[k].c_str(),64);
      mPresetList->addItem(str);
    }

    bitmap = pGraphics->LoadBitmap(FN_SLIDER, 1);
    pGraphics->AttachControl(new IBSliderControlScroll(HS_W + 210, 95, 214-84, -1, bitmap), kCtrlSliderPresetList);
    pGraphics->GetControlWithTag(kCtrlSliderPresetList)->SetActionFunction([&](IControl* ctrl) {mPresetList->setFirstRowToShowNormalized(ctrl->GetValue()); });
    pGraphics->GetControlWithTag(kCtrlSliderPresetList)->SetValue(1.);

    ///////////////////////////////////////// CAPTION USER/FACTORY /////////////////////////////////////////////////////////////

   ICaptionControl* userFactory = new ICaptionControl(IRECT(HS_W+10,39,HS_W+115, 58), kParamUserFactory, IText(12,COLOR_WHITE,"Calibrib"), COLOR_BLACK, true);
    userFactory->SetActionFunction([&](IControl* ctrl) {

      if (ctrl->GetValue() == 0) {
        activeRowUser = mPresetList->mActiveRow; // save
        mPresetList->Clear();
        for (int k = 0; k < 50; k++) {
//          mPresetList->addItem(presetname[k]);
          WDL_String str;
          str.Set(presetname[k].c_str(), 64);
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
}

void B4000::OnReset()
{
}

void B4000 ::OnUIClose() {
  if(GetParam(kParamUserFactory)->Value() == 0) activeRowFactory = mPresetList->mActiveRow;
  if (GetParam(kParamUserFactory)->Value() == 1) activeRowUser = mPresetList->mActiveRow;

  for (auto r = 0; r < mMidiLogger->maxLogSamples; r++) {
    for (auto c = 0; c < mMidiLogger->numColumns; c++) {
      mStrBufSave[r][c] = mMidiLogger->mStrBuf[r][c];
    }
  }
  mEntryPtrSave = mMidiLogger->mEntryPointer;
}

void B4000::OnUIOpen() {

  SendCurrentParamValuesFromDelegate();
  if (GetParam(kParamUserFactory)->Value() == 0) { //Factory
    mPresetList->Clear();
    for (int k = 0; k < 50; k++) {
//      mPresetList->addItem(presetname[k]);
      WDL_String str;
      str.Set(presetname[k].c_str(), 64);
      mPresetList->addItem(str);
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
void B4000::ProcessMidiMsg(const IMidiMsg& msg)
{
  TRACE;

#include "../MPA Code/ProcessMidi.h"
}

void B4000::OnParamChange(int paramIdx)
{
  IMidiMsg msg;

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

#include "../MPA Code/OnParamChange.h"
 
  // Other Stuff
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
      msg.mData2 = 0x03;
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
      msg.mData2 = 0x03;
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
      msg.mData2 = 0x03;
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
      msg.mData2 = 0x03;
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

    case kParamDelayUnitLeft:
      if (GetUI()) {
        if (GetUI()->GetControlWithTag(kCtrlTagAdd)->GetValue() == 1) {
          if (GetParam(paramIdx)->Value() == 0) {
            GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(true);
            GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMS)->Hide(false);
            GetUI()->GetControlWithTag(kCtrlLengthL)->Hide(true);
            GetUI()->GetControlWithTag(kCtrlTimeL)->Hide(false);

          }
          else {
            GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(false);
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
          }
          else {
            GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(false);
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

  return SerializeParams(chunk);
}

// this over-ridden method is called when the host is trying to load the plug-in state and you need to unpack the data into your algorithm
// HIER KÖNNEN KEINE CONTROLS GEUPDATED WERDEN; DA MGRAPHICS NOCH NICHT EXISTIERT!!!!
int B4000::UnserializeState(const IByteChunk& chunk, int startPos) {

  TRACE;

  return UnserializeParams(chunk, startPos);
}
#endif
