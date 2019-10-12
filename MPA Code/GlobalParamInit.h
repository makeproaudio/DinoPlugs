#pragma once

// MIXER UI
GetParam(kParamMixerDrive)->InitDouble("Mixer Saturation", 0, 0, 1, 0.001);
GetParam(kParamMixerBass)->InitDouble("Mixer Bass", 63./127, 0, 1, 0.001);
GetParam(kParamMixerTreble)->InitDouble("Mixer Treble", 63./127, 0, 1, 0.001);
GetParam(kParamMixerBalance)->InitDouble("Mixer Balance", 63./127, 0, 1, 0.001);
GetParam(kParamMixerLevel)->InitDouble("Mixer Level", 100./127, 0, 1, 0.001);
GetParam(kParamLAIGain)->InitDouble("Gain In L", 0, 0, 1, 0.001);
GetParam(kParamLAIBass)->InitDouble("Bass In L", 63./127, 0, 1, 0.001);
GetParam(kParamLAITreble)->InitDouble("Treble In L", 63./127, 0, 1, 0.001);
GetParam(kParamLAIPan)->InitDouble("Pan In L", 0., 0, 1, 0.001);
GetParam(kParamLAILevel)->InitDouble("Level In L", 100./127, 0, 1, 0.001);
GetParam(kParamRAIGain)->InitDouble("Gain In R", 0, 0, 1, 0.001);
GetParam(kParamRAIBass)->InitDouble("Bass In R", 63./127, 0, 1, 0.001);
GetParam(kParamRAITreble)->InitDouble("Treble In R", 63./127, 0, 1, 0.001);
GetParam(kParamRAIPan)->InitDouble("Pan In R", 1., 0, 1, 0.001);
GetParam(kParamRAILevel)->InitDouble("Level In R", 100./127, 0, 1, 0.001);
GetParam(kParamMixerLink)->InitBool("Mixer Link", false);

// KEYBOARD
GetParam(kParamKeyboardOctave)->InitEnum("Keyb Oct", 3, 7, "", 0, "", "-3", "-2", "-1", "0", "+1", "+2", "+3");

// PRESET/PLUGIN
GetParam(kParamUserFactory)->InitEnum("Preset Bank", 0, 2, "", 0, "", "Factory Bank", "User Bank");
GetParam(kParamProgram)->InitInt("Program", 0, 0, 49, "", 0, "");
GetParam(kParamMidiActive)->InitBool("MIDI Active", false, "", 0x1);

// EFFECT
GetParam(kParamMidiClockBpm)->InitInt("MIDI Clk BPM", 72, 72, 199, "", 0, "");
GetParam(kParamChorusRate)->InitDouble("Chorus Rate", 0, 0, 20, 0.01, "", 0, "", IParam::ShapePowCurve(6));
GetParam(kParamChorusPhase)->InitInt("Chorus Phase", 0, 0, 180);
GetParam(kParamChorusDepth)->InitDouble("Chorus Depth", 0, 0, 10, 0.01);
GetParam(kParamChorusFeedback)->InitDouble("Chorus FB", 0, -5, 5, 0.01);
GetParam(kParamChorusWet)->InitDouble("Chorus Mix", 0, 0, 10, 0.01);
GetParam(kParamDelayTimeLMS)->InitDouble("Delay Time L", 1.01, 1.01, 1365.33, 0.01);
GetParam(kParamDelayTimeRMS)->InitDouble("Delay Time R", 1.01, 1.01, 1365.33, 0.01);
GetParam(kParamDelayTimeLBPM)->InitEnum("Delaytime L BPM", 0, 19, "", 0, "", "1/1", "1/2P", "1/2", "1/2T", "1/4P", "1/4", "1/4T", "1/8P", "1/8", "1/8T", "1/16P", "1/16", "1/16T", "1/32P", "1/32", "1/32T", "1/64P", "1/64", "1/64T");
GetParam(kParamDelayTimeRBPM)->InitEnum("Delaytime R BPM", 0, 19, "", 0, "", "1/1", "1/2P", "1/2", "1/2T", "1/4P", "1/4", "1/4T", "1/8P", "1/8", "1/8T", "1/16P", "1/16", "1/16T", "1/32P", "1/32", "1/32T", "1/64P", "1/64", "1/64T");
GetParam(kParamDelayFeedbackLeft)->InitDouble("Delay FB L", 0, 0, 10, 0.01);
GetParam(kParamDelayFeedbackRight)->InitDouble("Delay FB R", 0, 0, 10, 0.01);
GetParam(kParamDelayHidampLeft)->InitDouble("Delay Hidamp L", 0, 0, 10, 0.01);
GetParam(kParamDelayHidampRight)->InitDouble("Delay Hidamp R", 0, 0, 10, 0.01);
GetParam(kParamDelayLevelLeft)->InitDouble("Delay Level L", 0, 0, 10, 0.01);
GetParam(kParamDelayLevelRight)->InitDouble("Delay Level R", 0, 0, 10, 0.01);
GetParam(kParamDelayWet)->InitDouble("Delay Mix", 0, 0, 10, 0.01);

// SWITCHES EFFECT
GetParam(kParamFlangerChorus)->InitEnum("Flanger", 0, 2, "", 0, "", "Off", "On");
GetParam(kParamDelayUnitLeft)->InitEnum("Delay BPM L", 0, 2, "", 0, "", "ms", "BPM");
GetParam(kParamDelayUnitRight)->InitEnum("Delay BPM R", 0, 2, "", 0, "", "ms", "BPM");
GetParam(kParamDelayCrossDual)->InitEnum("Delay Cross", 0, 2, "", 0, "", "Off", "On");
GetParam(kParamEffectBypass)->InitEnum("Effect Bypass", 0, 2, "", 0, "", "Off", "On");

paramToCC.fill(-1);

// MIXER UI
paramToCC[kParamMixerDrive] = 93;
paramToCC[kParamMixerBass] = 2;
paramToCC[kParamMixerTreble] = 5;
paramToCC[kParamMixerBalance] = 8;
paramToCC[kParamMixerLevel] = 7;
paramToCC[kParamLAIGain] = 20;
paramToCC[kParamLAIBass] = 22;
paramToCC[kParamLAITreble] = 25;
paramToCC[kParamLAIPan] = 28;
paramToCC[kParamLAILevel] = 29;
paramToCC[kParamRAIGain] = 40;
paramToCC[kParamRAIBass] = 42;
paramToCC[kParamRAITreble] = 45;
paramToCC[kParamRAIPan] = 48;
paramToCC[kParamRAILevel] = 49;

paramToCC[kParamMidiClockBpm] = 97;
paramToCC[kParamChorusPhase] = 72;
paramToCC[kParamChorusRate] = 71;
paramToCC[kParamChorusDepth] = 73;
paramToCC[kParamChorusFeedback] = 74;
paramToCC[kParamChorusWet] = 91;
paramToCC[kParamDelayTimeLMS] = 81;
paramToCC[kParamDelayTimeRMS] = 91;
paramToCC[kParamDelayTimeLBPM] = 82;
paramToCC[kParamDelayTimeRBPM] = 92;
paramToCC[kParamDelayFeedbackLeft] = 119;
paramToCC[kParamDelayHidampLeft] = 84;
paramToCC[kParamDelayLevelLeft] = 85;
paramToCC[kParamDelayFeedbackRight] = -1;
paramToCC[kParamDelayHidampRight] = 94;
paramToCC[kParamDelayLevelRight] = 95;
paramToCC[kParamDelayWet] = 10;
paramToCC[kParamFlangerChorus] = 75;
paramToCC[kParamEffectBypass] = 98;
paramToCC[kParamDelayUnitLeft] = 86;
paramToCC[kParamDelayUnitRight] = 96;
paramToCC[kParamDelayCrossDual] = 90;

paramToMsgType.fill(-1);

// MIXER UI
paramToMsgType[kParamMixerDrive] = 0;
paramToMsgType[kParamMixerBass] = 1;
paramToMsgType[kParamMixerTreble] = 1;
paramToMsgType[kParamMixerBalance] = 1;
paramToMsgType[kParamMixerLevel] = 0;
paramToMsgType[kParamLAIGain] = 1;
paramToMsgType[kParamLAIBass] = 1;
paramToMsgType[kParamLAITreble] = 1;
paramToMsgType[kParamLAIPan] = 1;
paramToMsgType[kParamLAILevel] = 1;
paramToMsgType[kParamRAIGain] = 1;
paramToMsgType[kParamRAIBass] = 1;
paramToMsgType[kParamRAITreble] = 1;
paramToMsgType[kParamRAIPan] = 1;
paramToMsgType[kParamRAILevel] = 1;

paramToMsgType[kParamMidiClockBpm] = 1;
paramToMsgType[kParamChorusPhase] = 1;
paramToMsgType[kParamChorusRate] = 1;
paramToMsgType[kParamChorusDepth] = 1;
paramToMsgType[kParamChorusFeedback] = 1;
paramToMsgType[kParamChorusWet] = 0;
paramToMsgType[kParamDelayTimeLMS] = 1;
paramToMsgType[kParamDelayTimeRMS] = 1;
paramToMsgType[kParamDelayTimeLBPM] = 1;
paramToMsgType[kParamDelayTimeRBPM] = 1;
paramToMsgType[kParamDelayFeedbackLeft] = 0;
paramToMsgType[kParamDelayHidampLeft] = 1;
paramToMsgType[kParamDelayLevelLeft] = 1;
paramToMsgType[kParamDelayFeedbackRight] = 0;
paramToMsgType[kParamDelayHidampRight] = 1;
paramToMsgType[kParamDelayLevelRight] = 1;
paramToMsgType[kParamDelayWet] = 0;
paramToMsgType[kParamFlangerChorus] = 1;
paramToMsgType[kParamEffectBypass] = 1;
paramToMsgType[kParamDelayUnitLeft] = 1;
paramToMsgType[kParamDelayUnitRight] = 1;
paramToMsgType[kParamDelayCrossDual] = 1;

ccIsNRPN.fill(-1);

ccIsNRPN[2] = 1;
ccIsNRPN[3] = 1;
ccIsNRPN[4] = 1;
ccIsNRPN[5] = 1;
ccIsNRPN[6] = 1;
ccIsNRPN[7] = 1;
ccIsNRPN[8] = 1;
ccIsNRPN[20] = 1;
ccIsNRPN[21] = 1;
ccIsNRPN[22] = 1;
ccIsNRPN[23] = 1;
ccIsNRPN[24] = 1;
ccIsNRPN[25] = 1;
ccIsNRPN[26] = 1;
ccIsNRPN[27] = 1;
ccIsNRPN[28] = 1;
ccIsNRPN[29] = 1;
ccIsNRPN[40] = 1;
ccIsNRPN[41] = 1;
ccIsNRPN[42] = 1;
ccIsNRPN[43] = 1;
ccIsNRPN[44] = 1;
ccIsNRPN[45] = 1;
ccIsNRPN[46] = 1;
ccIsNRPN[47] = 1;
ccIsNRPN[48] = 1;
ccIsNRPN[49] = 1;
ccIsNRPN[70] = 1;
ccIsNRPN[71] = 1;
ccIsNRPN[72] = 1;
ccIsNRPN[73] = 1;
ccIsNRPN[74] = 1;
ccIsNRPN[75] = 1;
ccIsNRPN[76] = 1;
ccIsNRPN[77] = 1;
ccIsNRPN[78] = 1;
ccIsNRPN[79] = 1;
ccIsNRPN[80] = 1;
ccIsNRPN[81] = 1;
ccIsNRPN[82] = 1;
ccIsNRPN[83] = 1;
ccIsNRPN[84] = 1;
ccIsNRPN[85] = 1;
ccIsNRPN[86] = 1;
ccIsNRPN[87] = 1;
ccIsNRPN[88] = 1;
ccIsNRPN[89] = 1;
ccIsNRPN[90] = 1;
ccIsNRPN[91] = 1;
ccIsNRPN[92] = 1;
ccIsNRPN[93] = 1;
ccIsNRPN[94] = 1;
ccIsNRPN[95] = 1;
ccIsNRPN[96] = 1;
ccIsNRPN[97] = 1;
ccIsNRPN[98] = 1;
ccIsNRPN[99] = 1;
ccIsNRPN[100] = 1;
ccIsNRPN[101] = 1;
ccIsNRPN[102] = 1;
ccIsNRPN[103] = 1;
ccIsNRPN[104] = 1;

ccIsNRPN[119] = 1; // für Lightwave

