#pragma once
enum EParams
{

  kParamUserFactory,

  //kParamMasterVolume,
  //kParamSynthMic,

  kParamVco1FmModSource1,
  kParamVco1FmModSource2,
  kParamVco1PwModSource,
  kParamVco2FmModSource1,
  kParamVco2FmModSource2,
  kParamVco2PwModSource,
  kParamShMixerSource1,
  kParamShMixerSource2,
  kParamShTrigSource,
  kParamMixerSource1,
  kParamMixerSource2,
  kParamMixerSource3,
  kParamVcfModSource1,
  kParamVcfModSource2,
  kParamVcfModSource3,
  kParamVcaModSource,
  kParamAdsrMode,
  kParamAdsrRepeat,
  kParamArMode,

  kParamNoiseType,
  kParamKeybOnOff,
  kParamVco2Sync,
  kParamLfoBpmHertz,
  kParamVcfModel,
  //kParamBoost,


  // Black Slider
  kParamPortamento,
  kParamMixerNoiseLevel,
  kParamVcfFreq,
  kParamVcfRes,
  kParamHpfFreq,
  kParamVcaGain,

  // Red Slider
  kParamVcfKeyb,
  kParamVcfAdsr,
  kParamVcaAdsr,
  kParamArAttack,
  kParamArRelease,
  kParamAdsrAttack,
  kParamAdsrDecay,

  // Yellow Slider
  kParamVco1ShLevel,
  kParamVco2ShLevel,
  kParamShLag,
  kParamVcfShLevel,
  kParamAdsrSustain,
  kParamAdsrRelease,

  // Pink Slider
  kParamVco1FmModLfoLevel,
  kParamVco1PwModLfoLevel,
  kParamVco2FmModLfoLevel,
  kParamVco2PwModLfoLevel,
  kParamLfoFreq,
  kParamArVel,
  kParamArKeyb,

  // Cyan Slider
  kParamVco1Coarse,
  kParamVco1Fine,
  kParamVco1PwWidth,
  kParamShMixerMod1Level,
  kParamShMixerMod2Level,
  kParamAudioMixerIn2level,

  // Green Slider
  kParamVco2Coarse,
  kParamVco2Fine,
  kParamVco2PwWidth,
  kParamAudioMixerIn3level,

  /* ADD  Slider */
  kParamBendRange,
  kParamModWheelIntensity,
  kParamChorusPhase,
  kParamChorusRate,
  kParamChorusDepth,
  kParamChorusFeedback,
  kParamChorusWet,
  kParamAftertouchPitch,
  kParamAftertouchFilter,
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

  kParamFlangerChorus,
  kParamEffectBypass,
  kParamDelayUnitLeft,
  kParamDelayUnitRight,
  kParamDelayCrossDual,
  kParamKeybModeRetrig,
  kParamKeybModeLowNote,
  kParamKeybModeSingle,
  kParamLfoSettBpm,

  kParamAftertouchVco,
  kParamMidiClockBpm,



  kParamPitchWheel,
  kParamMasterOctave,
  kParamVco1Octave,
  kParamVco2Octave,

  kParamKeyboardOctave,

    kParamLfoNote,

  kParamProgram,
  kParamMidiActive,
  kNumParams
};
