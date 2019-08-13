#pragma once

enum EParams
{
  #include "../MPA Code/CommonParamEnum.h" 
  
  // Knobs
  kParamMasterTune,
  kParamGlide,
  kParamModMix,
  kParamOsc2Tune,
  kParamOsc3Tune,
  kParamOsc1Volume,
  kParamOsc2Volume,
  kParamOsc3Volume,
  kParamFeedbackLevel,
  kParamNoiseVolume,
  kParamFilterCutoff,
  kParamFilterEmphasis,
  kParamFilterContour,
  kParamFilterAttack,
  kParamFilterDecay,
  kParamFilterSustain,
  kParamVcaAttack,
  kParamVcaDecay,
  kParamVcaSustain,
  kParamVolume,
  kParamVelocity,
  kParamOutputVelocity,
  kParamBendRange,
  kParamMWINT,
  kParamMWOFFS,
  kParamCvOsc,
  kParamCvFilter,
  kParamCvLoudness,
  // 6 STufen Knobs
  kParamOsc1Range,
  kParamOsc2Range,
  kParamOsc3Range,
  kParamOsc1Waveform,
  kParamOsc2Waveform,
  kParamOsc3Waveform,
  // 2 STufen Knobs
  // Switch Red V
  kParamOsc3Control,
  // Switch Red H
  kParamOscMod,
  kParamFilterMod1,
  kParamFilterMod2,
  kParamKeybControl,
  // Switch Blue V
  kParamNoiseType,
  // Switch Blue H
  kParamOsc1,
  kParamOsc2,
  kParamOsc3,
  kParamFeedback,
  kParamNoise,
  // Switch Silver
  kParamGlideOnOff,
  kParamDecay,
  kParamKeybModeRetrig,
  kParamKeybModeLowNote,
  kParamKeybModeSingle,

  kParamPitchWheel,

  kNumParams
};
