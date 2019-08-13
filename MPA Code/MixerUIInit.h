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

