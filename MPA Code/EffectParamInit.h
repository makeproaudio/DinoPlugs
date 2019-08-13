#pragma once

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
  
    // SWITCHES EFFECTS
  GetParam(kParamFlangerChorus)->InitEnum("Flanger", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamDelayUnitLeft)->InitEnum("Delay BPM L", 0, 2, "", 0, "", "ms", "BPM");
  GetParam(kParamDelayUnitRight)->InitEnum("Delay BPM R", 0, 2, "", 0, "", "ms", "BPM");
  GetParam(kParamDelayCrossDual)->InitEnum("Delay Cross", 0, 2, "", 0, "", "Off", "On");
  GetParam(kParamEffectBypass)->InitEnum("Effect Bypass", 0, 2, "", 0, "", "Off", "On");
