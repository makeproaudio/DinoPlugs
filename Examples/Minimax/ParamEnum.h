#pragma once

enum EParams
{

  kParamMasterVolume,
  kParamSynthMic,

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
  kParamChorusPhase,
  kParamChorusRate,
  kParamChorusDepth,
  kParamChorusFeedback,
  kParamChorusWet,
  kParamDelayTimeLMS,
  kParamDelayTimeRMS,
  kParamDelayTimeLBPM,
  kParamDelayTimeRBPM,
  kParamDelayFeedbackLeft,
  kParamDelayHidampLeft,
  kParamDelayLevelLeft,
  kParamDelayFeedbackRight,
  kParamDelayHidampRight,
  kParamDelayLevelRight,
  kParamDelayWet,
  // 6 STufen Knobs
  kParamOsc1Range,
  kParamOsc2Range,
  kParamOsc3Range,
  kParamOsc1Waveform,
  kParamOsc2Waveform,
  kParamOsc3Waveform,
  // 2 STufen Knobs
  kParamFlangerChorus,
  // Switch Red V
  kParamOsc3Control,
  // Switch Red H
  kParamOscMod,
  kParamFilterMod1,
  kParamFilterMod2,
  kParamKeybControl,
  kParamEffectBypass,
  kParamDelayCrossDual,
  kParamDelayUnitLeft,
  kParamDelayUnitRight,
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

  kParamMidiClockBpm,
  kParamPitchWheel,

  kParamKeyboardOctave,
  kParamProgram,
  kParamMidiActive,
  kNumParams
};
