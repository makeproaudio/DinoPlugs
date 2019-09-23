#pragma once

enum EParams
{
  #include "../MPA Code/CommonParamEnum.h" 
  
  kParamOsc1Waveform,
  kParamOsc1Coarse,
  kParamOsc1Fine,
  kParamOsc1Grunge,
  kParamOsc1PitchModSrc,
  kParamOsc1PitchModAmt,
  kParamOsc2Waveform,
  kParamOsc2Coarse,
  kParamOsc2Fine,
  kParamOsc2Grunge,
  kParamOsc2PitchModSrc,
  kParamOsc2PitchModAmt,

  kParamMixOsc1,
  kParamMixOsc1AmpModSrc,
  kParamMixOsc1AmpModAmt,
  kParamMixOsc1Balance,
  kParamMixOsc1BalanceModSrc,
  kParamMixOsc1BalanceModAmt,
  kParamMixOsc2,
  kParamMixOsc2AmpModSrc,
  kParamMixOsc2AmpModAmt,
  kParamMixOsc2Balance,
  kParamMixOsc2BalanceModSrc,
  kParamMixOsc2BalanceModAmt,
  kParamMixGain,

  kParamVcf1Cf,
  kParamVcf1Res,
  kParamVcf1keyf,
  kParamVcf1Env,
  kParamVcf1Type,
  kParamVcf1ModCfAmt,
  kParamVcf1ModResAmt,
  kParamVcf1ModCfSrc,
  kParamVcf1ModResSrc,

  kParamVcf2Cf,
  kParamVcf2Res,
  kParamVcf2keyf,
  kParamVcf2Env,
  kParamVcf2Type,
  kParamVcf2ModCfAmt,
  kParamVcf2ModResAmt,
  kParamVcf2ModCfSrc,
  kParamVcf2ModResSrc,

  kParamVcfSerPar,
  kParamVcfLink,
  kParamVcfCutoffModSrc,
  kParamVcfCutoffModAmt,
  kParamVcfResModSrc,
  kParamVcfResModAmt,

  kParamVcfEnvTKf,
  kParamVcfEnvTVel,
  kParamVcfEnvLVel,
  kParamVcfEnvA,
  kParamVcfEnvD,
  kParamVcfEnvS,
  kParamVcfEnvR,

  kParamAmpVol,
  kParamAmpPan,
  kParamAmpPanModSrc,
  kParamAmpPanModAmt,

  kParamAmpEnvTKf,
  kParamAmpEnvTVel,
  kParamAmpEnvLVel,
  kParamAmpEnvA,
  kParamAmpEnvD,
  kParamAmpEnvS,
  kParamAmpEnvR,

  kNumParams
};
