#include "DrumsNBass.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"
#include "json.hpp"
#include <fstream>

DrumsNBass::DrumsNBass(IPlugInstanceInfo instanceInfo)
: IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo)
{

  presetname[0 ].Set("00: Bomba Man"         );
  presetname[1 ].Set("01: Happy Hans"        );
  presetname[2 ].Set("02: Heavy Berta"       );
  presetname[3 ].Set("03: Niko Yoji"         );
  presetname[4 ].Set("04: Bono Down"         );
  presetname[5 ].Set("05: Jack Ordinair"     );
  presetname[6 ].Set("06: Sniffer"           );
  presetname[7 ].Set("07: Mad Dawg"          );
  presetname[8 ].Set("08: George Tiny"       );
  presetname[9 ].Set("09: Don Pinto"         );
  presetname[10].Set("10: Steve Tall"        );
  presetname[11].Set("11: Sami Simha"        );
  presetname[12].Set("12: Jumbo Jim"         );
  presetname[13].Set("13: Niko Yoji"         );
  presetname[14].Set("14: Jorg Jorgensen"    );
  presetname[15].Set("15: Haled Hawaiage"    );
  presetname[16].Set("16: Ned Nada"          );
  presetname[17].Set("17: Party Lony"        );
  presetname[18].Set("18: Tweak Slick"       );
  presetname[19].Set("19: Franco Bollo"      );
  presetname[20].Set("20: BrainCell"         );
  presetname[21].Set("21: Whistle Frantz"    );
  presetname[22].Set("22: Asher Peddy"       );
  presetname[23].Set("23: Mahmud el Punc"    );
  presetname[24].Set("24: Mendy Hop"         );
  presetname[25].Set("25: OB Anonimus"       );
  presetname[26].Set("26: La Bafoon"         );
  presetname[27].Set("27: Cheff"             );
  presetname[28].Set("28: Confi Dent"        );
  presetname[29].Set("29: Ras Tali"          );
  presetname[30].Set("30: Nonche Lant"       );
  presetname[31].Set("31: Munchkin"          );
  presetname[32].Set("32: Space Caddet"      );
  presetname[33].Set("33: Squash Game"       );
  presetname[34].Set("34: Lay D'back"        );
  presetname[35].Set("35: Lotto Port"        );
  presetname[36].Set("36: Mr. Wobble"        );
  presetname[37].Set("37: Electro Jorth"     );
  presetname[38].Set("38: Constrained"       );
  presetname[39].Set("39: New Times"         );
  presetname[40].Set("40: Old Times"         );
  presetname[41].Set("41: Donjo Vain"        );
  presetname[42].Set("42: Meron Komeron"     );
  presetname[43].Set("43: Why Like This"     );
  presetname[44].Set("44: Put It There"      );
  presetname[45].Set("45: Explo Dee"         );
  presetname[46].Set("46: Competition"       );
  presetname[47].Set("47: Fisa Near"         );
  presetname[48].Set("48: Take It Easy"      );
  presetname[49].Set("49: Gveret Salim"      );

   // MIXER UI
  #include "../MPA Code/GlobalParamInit.h"


  // This is super crazy, kParamSplitUpperManual changes to 5007 in GetParam. The exception. Cause could be array access out of bounds.

  GetParam(kParamBassSynthGlide)->InitInt("BassSynth Glide", 63, 0, 127);
  GetParam(kParamBassSynthFine)->InitInt("BassSynth Fine", 63, 0, 127);
  GetParam(kParamBassSynthFormant)->InitInt("BassSynth Formant", 63, 0, 127);
  GetParam(kParamBassSynthDrive)->InitInt("BassSynth Drive", 63, 0, 127);
  GetParam(kParamBassSynthQ)->InitInt("BassSynth Q", 63, 0, 127);
  GetParam(kParamBassSynthEnvAmt)->InitInt("BassSynth Filter Env Amt", 63, 0, 127);
  GetParam(kParamBassSynthFilterMod)->InitInt("BassSynth Filtermod", 63, 0, 127);
  GetParam(kParamBassSynthTracking)->InitInt("BassSynth Keyf", 63, 0, 127);
  GetParam(kParamBassSynthRetrig)->InitInt("BassSynth Retrig", 63, 0, 127);
  GetParam(kParamBassSynthCoarse)->InitInt("BassSynth Coarse", 63, 0, 127);
  GetParam(kParamBassSynthCutoff)->InitInt("BassSynth Cutoff", 63, 0, 127);
  GetParam(kParamBassSynthRate)->InitInt("BassSynth Rate", 63, 0, 127);
  GetParam(kParamBassSynthFilterEnvAttack)->InitInt("BassSynth Filter Attack", 63, 0, 127);
  GetParam(kParamBassSynthFilterEnvDecay)->InitInt("BassSynth Filter Decay", 63, 0, 127);
  GetParam(kParamBassSynthAmpEnvAttack)->InitInt("BassSynth Attack", 63, 0, 127);
  GetParam(kParamBassSynthAmpEnvDecay)->InitInt("BassSynth Decay", 63, 0, 127);
  GetParam(kParamBassSynthAmpEnvRelease)->InitInt("BassSynth Release", 63, 0, 127);

  GetParam(kParamBassdrum1BodyImpact)->InitInt("BD 1 Body Impact", 63, 0, 127);
  GetParam(kParamBassdrum1BodyTime)->InitInt("BD 1 Body Time", 63, 0, 127);
  GetParam(kParamBassdrum1TransientImpact)->InitInt("BD 1 Transient Impact", 63, 0, 127);
  GetParam(kParamBassdrum1TransientTime)->InitInt("BD 1 Transient Time", 63, 0, 127);
  GetParam(kParamBassdrum1SynthTune)->InitInt("BD 1 Tune", 63, 0, 127);
  GetParam(kParamBassdrum1BodyPunchSnapNormal)->InitEnum("BD 1 Body Style", 0, 3, "", 0, "", "Normal", "Punch", "Snap");
  GetParam(kParamBassdrum1TransientPunchSnapNormal)->InitEnum("BD 1 Transient Style", 0, 3, "", 0, "", "Normal", "Punch", "Snap");
  GetParam(kParamBassdrum1Waveform)->InitEnum("BD 1 Waveform", 0, 19, "", 0, "", "Sine", "909 1", "909 2", "808", "606", "DR", "Simon", "Fluff", "Warm", "Woody", "Hardcore", "Gabber", "Grunge", "Oomph", "Noisy", "Dirt", "Squash", "Damage", "Chaos");
  GetParam(kParamBassdrum1AmpEnvAttack)->InitInt("BD 1 Attack", 63, 0, 127);
  GetParam(kParamBassdrum1AmpEnvDecay)->InitInt("BD 1 Decay", 63, 0, 127);
  GetParam(kParamBassdrum1AmpEnvRelease)->InitInt("BD 1 Release", 63, 0, 127);
  GetParam(kParamBassdrum1AmpEnvCurve)->InitInt("BD 1 Curve", 63, 0, 127);
  
  GetParam(kParamBassdrum2BodyImpact)->InitInt("BD 2 Body Impact", 63, 0, 127);
  GetParam(kParamBassdrum2BodyTime)->InitInt("BD 2 Body Time", 63, 0, 127);
  GetParam(kParamBassdrum2TransientImpact)->InitInt("BD 2 Transient Impact", 63, 0, 127);
  GetParam(kParamBassdrum2TransientTime)->InitInt("BD 2 Transient Time", 63, 0, 127);
  GetParam(kParamBassdrum2SynthTune)->InitInt("BD 2 Tune", 63, 0, 127);
  GetParam(kParamBassdrum2BodyPunchSnapNormal)->InitEnum("BD 2 Body Style", 0, 3, "", 0, "", "Normal", "Punch", "Snap");
  GetParam(kParamBassdrum2TransientPunchSnapNormal)->InitEnum("BD 2 Transient Style", 0, 3, "", 0, "", "Normal", "Punch", "Snap");
  GetParam(kParamBassdrum2Waveform)->InitEnum("BD 2 Waveform", 0, 19, "", 0, "", "Sine", "909 1", "909 2", "808", "606", "DR", "Simon", "Fluff", "Warm", "Woody", "Hardcore", "Gabber", "Grunge", "Oomph", "Noisy", "Dirt", "Squash", "Damage", "Chaos");
  GetParam(kParamBassdrum2AmpEnvAttack)->InitInt("BD 2 Attack", 63, 0, 127);
  GetParam(kParamBassdrum2AmpEnvDecay)->InitInt("BD 2 Decay", 63, 0, 127);
  GetParam(kParamBassdrum2AmpEnvRelease)->InitInt("BD 2 Release", 63, 0, 127);
  GetParam(kParamBassdrum2AmpEnvCurve)->InitInt("BD 2 Curve", 63, 0, 127);
  
  GetParam(kParamCabasaQ)->InitInt("CB Q", 63, 0, 127);
  GetParam(kParamCabasaColor)->InitInt("CB Color", 63, 0, 127);
  GetParam(kParamCabasaAttack)->InitInt("CB Attack", 63, 0, 127);
  GetParam(kParamCabasaDecay)->InitInt("CB Decay", 63, 0, 127);
  
  GetParam(kParamClapPeople)->InitInt("CL People", 63, 0, 127);
  GetParam(kParamClapQ)->InitInt("CL Q", 63, 0, 127);
  GetParam(kParamClapColor)->InitInt("CL Color", 63, 0, 127);
  GetParam(kParamClapDecay)->InitInt("CL Decay", 63, 0, 127);
  
  GetParam(kParamCowbellFM)->InitInt("CB FM", 63, 0, 127);
  GetParam(kParamCowbellTonality)->InitInt("CB Tonality", 63, 0, 127);
  GetParam(kParamCowbellTune)->InitInt("CB Tune", 63, 0, 127);
  GetParam(kParamCowbellDecay)->InitInt("CB Decay", 63, 0, 127);
  GetParam(kParamCowbellWaveform)->InitEnum("CB Waveform", 0, 19, "", 0, "", "Sine", "909 1", "909 2", "808", "606", "DR", "Simon", "Fluff", "Warm", "Woody", "Hardcore", "Gabber", "Grunge", "Oomph", "Noisy", "Dirt", "Squash", "Damage", "Chaos");
  
  GetParam(kParamCymbalSwell)->InitInt("CY Swell", 63, 0, 127);
  GetParam(kParamCymbalDefinition)->InitInt("CY Definition", 63, 0, 127);
  GetParam(kParamCymbalTune)->InitInt("CY Tune", 63, 0, 127);
  GetParam(kParamCymbalColor)->InitInt("CY Color", 63, 0, 127);
  GetParam(kParamCymbalDecay)->InitInt("CY Decay", 63, 0, 127);
  GetParam(kParamCymbalWaveform)->InitEnum("CY Waveform", 0, 9, "", 0, "", "Crash 1", "Crash 2", "Crash 3", "Ride 1", "Ride 2", "Splash 1", "Splash 2", "China 1", "China 2");

  GetParam(kParamHihatType)->InitInt("HH Noise Type", 63, 0, 127);
  GetParam(kParamHihatQ)->InitInt("HH Q", 63, 0, 127);
  GetParam(kParamHihatColor)->InitInt("HH Color", 63, 0, 127);
  GetParam(kParamHihatClosed)->InitInt("HH Closed", 63, 0, 127);
  GetParam(kParamHihatOpen)->InitInt("HH Open", 63, 0, 127);

  GetParam(kParamSnaredrum1Impact)->InitInt("SD1 Impact", 63, 0, 127);
  GetParam(kParamSnaredrum1Time)->InitInt("SD1 Time", 63, 0, 127);
  GetParam(kParamSnaredrum1Q)->InitInt("SD1 Q", 63, 0, 127);
  GetParam(kParamSnaredrum1Tune)->InitInt("SD1 Tune", 63, 0, 127);
  GetParam(kParamSnaredrum1Color)->InitInt("SD1 Color", 63, 0, 127);
  GetParam(kParamSnaredrum1BodySnares)->InitInt("SD1 Body", 63, 0, 127); 
  GetParam(kParamSnaredrum1Tightness)->InitInt("SD1 Tightness", 63, 0, 127);
  GetParam(kParamSnaredrum1Waveform)->InitEnum("SD1 Waveform", 0, 19, "", 0, "", "Sine", "909 1", "909 2", "808", "606", "DR", "Simon", "Fluff", "Warm", "Woody", "Hardcore", "Gabber", "Grunge", "Oomph", "Noisy", "Dirt", "Squash", "Damage", "Chaos");
  GetParam(kParamSnaredrum1Decay)->InitInt("SD1 Decay", 63, 0, 127);
  
  GetParam(kParamSnaredrum2Impact)->InitInt("SD2 Impact", 63, 0, 127);
  GetParam(kParamSnaredrum2Time)->InitInt("SD2 Time", 63, 0, 127);
  GetParam(kParamSnaredrum2Q)->InitInt("SD2 Q", 63, 0, 127);
  GetParam(kParamSnaredrum2Tune)->InitInt("SD2 Tune", 63, 0, 127);
  GetParam(kParamSnaredrum2Color)->InitInt("SD2 Color", 63, 0, 127);
  GetParam(kParamSnaredrum2BodySnares)->InitInt("SD2 Body", 63, 0, 127);
  GetParam(kParamSnaredrum2Tightness)->InitInt("SD2 Tightness", 63, 0, 127);
  GetParam(kParamSnaredrum2Waveform)->InitEnum("SD2 Waveform", 0, 19, "", 0, "", "Sine", "909 1", "909 2", "808", "606", "DR", "Simon", "Fluff", "Warm", "Woody", "Hardcore", "Gabber", "Grunge", "Oomph", "Noisy", "Dirt", "Squash", "Damage", "Chaos");
  GetParam(kParamSnaredrum2Decay)->InitInt("SD2 Decay", 63, 0, 127);

  GetParam(kParamTom1Impact)->InitInt("TO1 Impact", 63, 0, 127);
  GetParam(kParamTom1Time)->InitInt("TO1 Time", 63, 0, 127);
  GetParam(kParamTom1NoiseLevel)->InitInt("TO1 NoiseLevel", 63, 0, 127);
  GetParam(kParamTom1Tune)->InitInt("TO1 Tune", 63, 0, 127);
  GetParam(kParamTom1NoiseColor)->InitInt("TO1 Noise Color", 63, 0, 127);
  GetParam(kParamTom1Waveform)->InitEnum("TO1 Waveform", 0, 19, "", 0, "", "Sine", "909 1", "909 2", "808", "606", "DR", "Simon", "Fluff", "Warm", "Woody", "Hardcore", "Gabber", "Grunge", "Oomph", "Noisy", "Dirt", "Squash", "Damage", "Chaos");
  GetParam(kParamTom1NoiseDecay)->InitInt("TO1 Noise Decay", 63, 0, 127);
  
  GetParam(kParamTom2Impact)->InitInt("TO2 Impact", 63, 0, 127);
  GetParam(kParamTom2Time)->InitInt("TO2 Time", 63, 0, 127);
  GetParam(kParamTom2NoiseLevel)->InitInt("TO2 Noise Level", 63, 0, 127);
  GetParam(kParamTom2Tune)->InitInt("TO2 Tune", 63, 0, 127);
  GetParam(kParamTom2NoiseColor)->InitInt("TO2 Noise Color", 63, 0, 127);
  GetParam(kParamTom2Waveform)->InitEnum("TO2 Waveform", 0, 19, "", 0, "", "Sine", "909 1", "909 2", "808", "606", "DR", "Simon", "Fluff", "Warm", "Woody", "Hardcore", "Gabber", "Grunge", "Oomph", "Noisy", "Dirt", "Squash", "Damage", "Chaos");
  GetParam(kParamTom2NoiseDecay)->InitInt("TO2 Noise Decay", 63, 0, 127);

  GetParam(kParamEffectsFilterQ)->InitInt("Effect Filter Q", 63, 0, 127);
  GetParam(kParamEffectsFilterEnvelope)->InitInt("Effects Filter Env", 63, 0, 127);
  GetParam(kParamEffectsDriveTone)->InitInt("Effects Drive Tone", 63, 0, 127);
  GetParam(kParamEffectsChorusOffset)->InitInt("Effects Chorus Offset", 63, 0, 127);
  GetParam(kParamEffectsChorusFeedback)->InitInt("Effects Chorus FB", 63, 0, 127);
  GetParam(kParamEffectsDelayDamp)->InitInt("Effects Delay Damp", 63, 0, 127);
  GetParam(kParamEffectsDelayFeedback)->InitInt("Effects Delay FB", 63, 0, 127);
  GetParam(kParamEffectsFilterCutoff)->InitInt("Effects Filter Cutoff", 63, 0, 127);
  GetParam(kParamEffectsDriveAmount)->InitInt("Effects Drive Amt", 63, 0, 127);
  GetParam(kParamEffectsChorusRate)->InitInt("Effects Chorus Rate", 63, 0, 127);
  GetParam(kParamEffectsChorusDepth)->InitInt("Effects Chorus Depth", 63, 0, 127);
  GetParam(kParamEffectsDelayTimeL)->InitInt("Effects Delaytime L", 63, 0, 127);
  GetParam(kParamEffectsDelayTimeR)->InitInt("Effects Delaytime R", 63, 0, 127);
  GetParam(kParamEffectsFilterType)->InitEnum("Effects Filtertype", 0, 3, "", 0, "", "LPF", "HPF", "BPF");
  GetParam(kParamEffectsFilterMute)->InitInt("Effects Filter Mute", 0, 0, 127);
  GetParam(kParamEffectsDriveMute)->InitInt("Effects Drive Mute", 0, 0, 127);
  GetParam(kParamEffectsChorusMute)->InitInt("Effects Chorus Mute", 0, 0, 127);
  GetParam(kParamEffectsDelayMute)->InitInt("Effects Delay Mute", 0, 0, 127);

  GetParam(kParamMixerDelayBD1        )->InitInt("Delay BD1 ", 63, 0, 127);
  GetParam(kParamMixerDelayBD2        )->InitInt("Delay BD2", 63, 0, 127);
  GetParam(kParamMixerDelaySD1        )->InitInt("Delay SD1", 63, 0, 127);
  GetParam(kParamMixerDelaySD2        )->InitInt("Delay SD2", 63, 0, 127);
  GetParam(kParamMixerDelayTO1        )->InitInt("Delay TO1", 63, 0, 127);
  GetParam(kParamMixerDelayTO2        )->InitInt("Delay TO2", 63, 0, 127);
  GetParam(kParamMixerDelayHH         )->InitInt("Delay HH", 63, 0, 127);
  GetParam(kParamMixerDelayCY         )->InitInt("Delay CY", 63, 0, 127);
  GetParam(kParamMixerDelayCow        )->InitInt("Delay Cow", 63, 0, 127);
  GetParam(kParamMixerDelayCL         )->InitInt("Delay CL", 63, 0, 127);
  GetParam(kParamMixerDelayCB         )->InitInt("Delay CB", 63, 0, 127);
  GetParam(kParamMixerDelayBass       )->InitInt("Delay Bass", 63, 0, 127);
                                     
  GetParam(kParamMixerChorusBD1       )->InitInt("Chorus BD1 ", 63, 0, 127);
  GetParam(kParamMixerChorusBD2       )->InitInt("Chorus BD2", 63, 0, 127);
  GetParam(kParamMixerChorusSD1       )->InitInt("Chorus SD1", 63, 0, 127);
  GetParam(kParamMixerChorusSD2       )->InitInt("Chorus SD2", 63, 0, 127);
  GetParam(kParamMixerChorusTO1       )->InitInt("Chorus TO1", 63, 0, 127);
  GetParam(kParamMixerChorusTO2       )->InitInt("Chorus TO2", 63, 0, 127);
  GetParam(kParamMixerChorusHH        )->InitInt("Chorus HH", 63, 0, 127);
  GetParam(kParamMixerChorusCY        )->InitInt("Chorus CY", 63, 0, 127);
  GetParam(kParamMixerChorusCow       )->InitInt("Chorus Cow", 63, 0, 127);
  GetParam(kParamMixerChorusCL        )->InitInt("Chorus CL", 63, 0, 127);
  GetParam(kParamMixerChorusCB        )->InitInt("Chorus CB", 63, 0, 127);
  GetParam(kParamMixerChorusBass      )->InitInt("Chorus Bass", 63, 0, 127);
                                     
  GetParam(kParamMixerPanBD1          )->InitInt("Pan BD1 ", 63, 0, 127);
  GetParam(kParamMixerPanBD2          )->InitInt("Pan BD2", 63, 0, 127);
  GetParam(kParamMixerPanSD1          )->InitInt("Pan SD1", 63, 0, 127);
  GetParam(kParamMixerPanSD2          )->InitInt("Pan SD2", 63, 0, 127);
  GetParam(kParamMixerPanTO1          )->InitInt("Pan TO1", 63, 0, 127);
  GetParam(kParamMixerPanTO2          )->InitInt("Pan TO2", 63, 0, 127);
  GetParam(kParamMixerPanHH           )->InitInt("Pan HH", 63, 0, 127);
  GetParam(kParamMixerPanCY           )->InitInt("Pan CY", 63, 0, 127);
  GetParam(kParamMixerPanCow          )->InitInt("Pan Cow", 63, 0, 127);
  GetParam(kParamMixerPanCL           )->InitInt("Pan CL", 63, 0, 127);
  GetParam(kParamMixerPanCB           )->InitInt("Pan CB", 63, 0, 127);
  GetParam(kParamMixerPanBass         )->InitInt("Pan Bass", 63, 0, 127);
                                    
  GetParam(kParamMixerLevelBD1        )->InitInt("Level BD1 ", 63, 0, 127);
  GetParam(kParamMixerLevelBD2        )->InitInt("Level BD2", 63, 0, 127);
  GetParam(kParamMixerLevelSD1        )->InitInt("Level SD1", 63, 0, 127);
  GetParam(kParamMixerLevelSD2        )->InitInt("Level SD2", 63, 0, 127);
  GetParam(kParamMixerLevelTO1        )->InitInt("Level TO1", 63, 0, 127);
  GetParam(kParamMixerLevelTO2        )->InitInt("Level TO2", 63, 0, 127);
  GetParam(kParamMixerLevelHH         )->InitInt("Level HH", 63, 0, 127);
  GetParam(kParamMixerLevelCY         )->InitInt("Level CY", 63, 0, 127);
  GetParam(kParamMixerLevelCow        )->InitInt("Level Cow", 63, 0, 127);
  GetParam(kParamMixerLevelCL         )->InitInt("Level CL", 63, 0, 127);
  GetParam(kParamMixerLevelCB         )->InitInt("Level CB", 63, 0, 127);
  GetParam(kParamMixerLevelBass       )->InitInt("Level Bass", 63, 0, 127);
                                     
  GetParam(kParamMixerDelayReturn     )->InitInt("Delay Return", 63, 0, 127);
  GetParam(kParamMixerChorusReturn    )->InitInt("Chorus Return ", 63, 0, 127);

  paramToCC[kParamBassSynthGlide                  ]=69;
  paramToCC[kParamBassSynthFine                   ]=70;
  paramToCC[kParamBassSynthFormant                ]=82;
  paramToCC[kParamBassSynthDrive                  ]=78;
  paramToCC[kParamBassSynthQ                      ]=71;
  paramToCC[kParamBassSynthEnvAmt                 ]=73;
  paramToCC[kParamBassSynthFilterMod              ]=67;
  paramToCC[kParamBassSynthTracking               ]=79;
  paramToCC[kParamBassSynthRetrig                 ]=12;
  paramToCC[kParamBassSynthCoarse                 ]=72;
  paramToCC[kParamBassSynthCutoff                 ]=74;
  paramToCC[kParamBassSynthRate                   ]=68;
  paramToCC[kParamBassSynthFilterEnvAttack        ]=80;
  paramToCC[kParamBassSynthFilterEnvDecay         ]=81;
  paramToCC[kParamBassSynthAmpEnvAttack           ]=75;
  paramToCC[kParamBassSynthAmpEnvDecay            ]=76;
  paramToCC[kParamBassSynthAmpEnvRelease          ]=77;
  
  paramToCC[kParamBassdrum1BodyImpact                 ]=40;
  paramToCC[kParamBassdrum1BodyTime                   ]=41;
  paramToCC[kParamBassdrum1TransientImpact            ]=37;
  paramToCC[kParamBassdrum1TransientTime              ]=93;
  paramToCC[kParamBassdrum1SynthTune                  ]=42;
  paramToCC[kParamBassdrum1BodyPunchSnapNormal        ]=43;
  paramToCC[kParamBassdrum1TransientPunchSnapNormal   ]=39;
  paramToCC[kParamBassdrum1Waveform                   ]=44;
  paramToCC[kParamBassdrum1AmpEnvAttack               ]=34;
  paramToCC[kParamBassdrum1AmpEnvDecay                ]=35;
  paramToCC[kParamBassdrum1AmpEnvRelease              ]=33;
  paramToCC[kParamBassdrum1AmpEnvCurve                ]=36;
  
  paramToCC[kParamBassdrum2BodyImpact] = 52;
  paramToCC[kParamBassdrum2BodyTime] = 53;
  paramToCC[kParamBassdrum2TransientImpact] = 49;
  paramToCC[kParamBassdrum2TransientTime] = 50;
  paramToCC[kParamBassdrum2SynthTune] = 14;
  paramToCC[kParamBassdrum2BodyPunchSnapNormal] = 54;
  paramToCC[kParamBassdrum2TransientPunchSnapNormal] = 51;
  paramToCC[kParamBassdrum2Waveform] = 55;
  paramToCC[kParamBassdrum2AmpEnvAttack] = 45;
  paramToCC[kParamBassdrum2AmpEnvDecay] = 46;
  paramToCC[kParamBassdrum2AmpEnvRelease] = 47;
  paramToCC[kParamBassdrum2AmpEnvCurve] = 48;
  
  paramToCC[kParamCabasaQ         ]=85;
  paramToCC[kParamCabasaColor     ]=19;
  paramToCC[kParamCabasaAttack    ]=83;
  paramToCC[kParamCabasaDecay     ]=84;
  
  paramToCC[kParamClapPeople  ]=59;
  paramToCC[kParamClapQ       ]=61;
  paramToCC[kParamClapColor   ]=15;
  paramToCC[kParamClapDecay   ]=60;
  
  paramToCC[kParamCowbellFM         ]=57;
  paramToCC[kParamCowbellTonality   ]=58;
  paramToCC[kParamCowbellTune       ]=20;
  paramToCC[kParamCowbellDecay      ]=56;
  paramToCC[kParamCowbellWaveform   ]=105;
  
  paramToCC[kParamCymbalSwell      ]=4;
  paramToCC[kParamCymbalDefinition   ]=5;
  paramToCC[kParamCymbalTune       ]=18;
  paramToCC[kParamCymbalColor      ]=3;
  paramToCC[kParamCymbalDecay      ]=2;
  paramToCC[kParamCymbalWaveform   ]=92;
  
  paramToCC[kParamHihatType     ]=62;
  paramToCC[kParamHihatQ        ]=63;
  paramToCC[kParamHihatColor    ]=16;
  paramToCC[kParamHihatClosed   ]=66;
  paramToCC[kParamHihatOpen     ]=65;
  
  paramToCC[kParamSnaredrum1Impact          ]=92;
  paramToCC[kParamSnaredrum1Time            ]=90;
  paramToCC[kParamSnaredrum1Q               ]=89;
  paramToCC[kParamSnaredrum1Tune            ]=13;
  paramToCC[kParamSnaredrum1Color           ]=88;
  paramToCC[kParamSnaredrum1BodySnares      ]=94;
  paramToCC[kParamSnaredrum1Tightness       ]=87;
  paramToCC[kParamSnaredrum1Waveform        ]=103;
  paramToCC[kParamSnaredrum1Decay           ]=86;
  
  paramToCC[kParamSnaredrum2Impact] = 101;
  paramToCC[kParamSnaredrum2Time] = 100;
  paramToCC[kParamSnaredrum2Q] = 95;
  paramToCC[kParamSnaredrum2Tune] = 95;
  paramToCC[kParamSnaredrum2Color] = 94;
  paramToCC[kParamSnaredrum2BodySnares] = 102;
  paramToCC[kParamSnaredrum2Tightness] = 97;
  paramToCC[kParamSnaredrum2Waveform] = 104;
  paramToCC[kParamSnaredrum2Decay] = 96;
  
  paramToCC[kParamTom1Impact     ]=25;
  paramToCC[kParamTom1Time       ]=21;
  paramToCC[kParamTom1NoiseLevel      ]=24;
  paramToCC[kParamTom1Tune       ]=17;
  paramToCC[kParamTom1NoiseColor      ]=22;
  paramToCC[kParamTom1Waveform   ]=8;
  paramToCC[kParamTom1NoiseDecay      ]=23;
  
  paramToCC[kParamTom2Impact] = 31;
  paramToCC[kParamTom2Time] = 27;
  paramToCC[kParamTom2NoiseLevel] = 30;
  paramToCC[kParamTom2Tune] = 26;
  paramToCC[kParamTom2NoiseColor] = 28;
  paramToCC[kParamTom2Waveform] = 9;
  paramToCC[kParamTom2NoiseDecay] = 29;
  
  paramToCC[kParamEffectsFilterQ           ]=76;
  paramToCC[kParamEffectsFilterEnvelope    ]=77;
  paramToCC[kParamEffectsDriveTone         ]=79;
  paramToCC[kParamEffectsChorusOffset      ]=72;
  paramToCC[kParamEffectsChorusFeedback    ]=74;
  paramToCC[kParamEffectsDelayDamp         ]=84;
  paramToCC[kParamEffectsDelayFeedback     ]=119;
  paramToCC[kParamEffectsFilterCutoff      ]=75;
  paramToCC[kParamEffectsDriveAmount       ]=78;
  paramToCC[kParamEffectsChorusRate        ]=71;
  paramToCC[kParamEffectsChorusDepth       ]=73;
  paramToCC[kParamEffectsDelayTimeL        ]=81;
  paramToCC[kParamEffectsDelayTimeR        ]=91;
  paramToCC[kParamEffectsFilterType        ]=80;
  paramToCC[kParamEffectsFilterMute        ]=101;
  paramToCC[kParamEffectsDriveMute         ]=99;
  paramToCC[kParamEffectsChorusMute        ]=100;
  paramToCC[kParamEffectsDelayMute         ]=98;
  
  paramToCC[kParamMixerDelayBD1         ]=49+13;
  paramToCC[kParamMixerDelayBD2         ]=50+13;
  paramToCC[kParamMixerDelaySD1         ]=51+13;
  paramToCC[kParamMixerDelaySD2         ]=52+13;
  paramToCC[kParamMixerDelayHH          ]=53+13;
  paramToCC[kParamMixerDelayTO1         ]=54+13;
  paramToCC[kParamMixerDelayTO2         ]=55+13;
  paramToCC[kParamMixerDelayCY          ]=56+13;
  paramToCC[kParamMixerDelayCL          ]=57+13;
  paramToCC[kParamMixerDelayCB          ]=58+27;
  paramToCC[kParamMixerDelayCow         ]=59+27;
  paramToCC[kParamMixerDelayBass        ]=60+27;
  paramToCC[kParamMixerChorusBD1       ]=37+65;
  paramToCC[kParamMixerChorusBD2       ]=38+65;
  paramToCC[kParamMixerChorusSD1       ]=39+65;
  paramToCC[kParamMixerChorusSD2       ]=40+65;
  paramToCC[kParamMixerChorusHH        ]=41+65;
  paramToCC[kParamMixerChorusTO1       ]=42+65;
  paramToCC[kParamMixerChorusTO2       ]=43+65;
  paramToCC[kParamMixerChorusCY        ]=44+65;
  paramToCC[kParamMixerChorusCL        ]=45+65;
  paramToCC[kParamMixerChorusCB        ]=46+65;
  paramToCC[kParamMixerChorusCow       ]=47+65;
  paramToCC[kParamMixerChorusBass      ]=48+65;
  paramToCC[kParamMixerPanBD1          ]=1 +49;
  paramToCC[kParamMixerPanBD2          ]=2 +49;
  paramToCC[kParamMixerPanSD1          ]=3 +49;
  paramToCC[kParamMixerPanSD2          ]=4 +49;
  paramToCC[kParamMixerPanHH           ]=5 +49;
  paramToCC[kParamMixerPanTO1          ]=6 +49;
  paramToCC[kParamMixerPanTO2          ]=7 +49;
  paramToCC[kParamMixerPanCY           ]=8 +49;
  paramToCC[kParamMixerPanCL           ]=9 +49;
  paramToCC[kParamMixerPanCB           ]=10+49;
  paramToCC[kParamMixerPanCow          ]=11+49;
  paramToCC[kParamMixerPanBass         ]=12+49;
  paramToCC[kParamMixerLevelBD1        ]=107;
  paramToCC[kParamMixerLevelBD2        ]=108;
  paramToCC[kParamMixerLevelSD1        ]=109;
  paramToCC[kParamMixerLevelSD2        ]=110;
  paramToCC[kParamMixerLevelHH         ]=111;
  paramToCC[kParamMixerLevelTO1        ]=112;
  paramToCC[kParamMixerLevelTO2        ]=113;
  paramToCC[kParamMixerLevelCY         ]=114;
  paramToCC[kParamMixerLevelCL         ]=115;
  paramToCC[kParamMixerLevelCB         ]=116;
  paramToCC[kParamMixerLevelCow        ]=117;
  paramToCC[kParamMixerLevelBass       ]=118;
  paramToCC[kParamMixerDelayReturn      ]=10;
  paramToCC[kParamMixerChorusReturn     ]=91;
  
  // Aftertouch
  paramToMsgType[kParamBassSynthGlide                  ]=0;
  paramToMsgType[kParamBassSynthFine                   ]=0;
  paramToMsgType[kParamBassSynthFormant                ]=0;
  paramToMsgType[kParamBassSynthDrive                  ]=0;
  paramToMsgType[kParamBassSynthQ                      ]=0;
  paramToMsgType[kParamBassSynthEnvAmt                 ]=0;
  paramToMsgType[kParamBassSynthFilterMod              ]=0;
  paramToMsgType[kParamBassSynthTracking               ]=0;
  paramToMsgType[kParamBassSynthRetrig                 ]=0;
  paramToMsgType[kParamBassSynthCoarse                 ]=0;
  paramToMsgType[kParamBassSynthCutoff                 ]=0;
  paramToMsgType[kParamBassSynthRate                   ]=0;
  paramToMsgType[kParamBassSynthFilterEnvAttack        ]=0;
  paramToMsgType[kParamBassSynthFilterEnvDecay         ]=0;
  paramToMsgType[kParamBassSynthAmpEnvAttack           ]=0;
  paramToMsgType[kParamBassSynthAmpEnvDecay            ]=0;
  paramToMsgType[kParamBassSynthAmpEnvRelease          ]=0;
  
  paramToMsgType[kParamBassdrum1BodyImpact                 ]=0;
  paramToMsgType[kParamBassdrum1BodyTime                   ]=0;
  paramToMsgType[kParamBassdrum1TransientImpact            ]=0;
  paramToMsgType[kParamBassdrum1TransientTime              ]=1;
  paramToMsgType[kParamBassdrum1SynthTune                  ]=0;
  paramToMsgType[kParamBassdrum1BodyPunchSnapNormal        ]=0;
  paramToMsgType[kParamBassdrum1TransientPunchSnapNormal   ]=0;
  paramToMsgType[kParamBassdrum1Waveform                   ]=0;
  paramToMsgType[kParamBassdrum1AmpEnvAttack               ]=0;
  paramToMsgType[kParamBassdrum1AmpEnvDecay                ]=0;
  paramToMsgType[kParamBassdrum1AmpEnvRelease              ]=0;
  paramToMsgType[kParamBassdrum1AmpEnvCurve                ]=0;
  
  paramToMsgType[kParamBassdrum2BodyImpact] = 0;
  paramToMsgType[kParamBassdrum2BodyTime] = 0;
  paramToMsgType[kParamBassdrum2TransientImpact] = 0;
  paramToMsgType[kParamBassdrum2TransientTime] = 0;
  paramToMsgType[kParamBassdrum2SynthTune] = 0;
  paramToMsgType[kParamBassdrum2BodyPunchSnapNormal] = 0;
  paramToMsgType[kParamBassdrum2TransientPunchSnapNormal] = 0;
  paramToMsgType[kParamBassdrum2Waveform] = 0;
  paramToMsgType[kParamBassdrum2AmpEnvAttack] = 0;
  paramToMsgType[kParamBassdrum2AmpEnvDecay] = 0;
  paramToMsgType[kParamBassdrum2AmpEnvRelease] = 0;
  paramToMsgType[kParamBassdrum2AmpEnvCurve] = 0;
  
  paramToMsgType[kParamCabasaQ         ]=0;
  paramToMsgType[kParamCabasaColor     ]=0;
  paramToMsgType[kParamCabasaAttack    ]=0;
  paramToMsgType[kParamCabasaDecay     ]=0;
  
  paramToMsgType[kParamClapPeople  ]=0;
  paramToMsgType[kParamClapQ       ]=0;
  paramToMsgType[kParamClapColor   ]=0;
  paramToMsgType[kParamClapDecay   ]=0;
  
  paramToMsgType[kParamCowbellFM         ]=0;
  paramToMsgType[kParamCowbellTonality   ]=0;
  paramToMsgType[kParamCowbellTune       ]=0;
  paramToMsgType[kParamCowbellDecay      ]=0;
  paramToMsgType[kParamCowbellWaveform   ]=0;
  
  paramToMsgType[kParamCymbalSwell      ]=0;
  paramToMsgType[kParamCymbalDefinition   ]=0;
  paramToMsgType[kParamCymbalTune       ]=0;
  paramToMsgType[kParamCymbalColor      ]=0;
  paramToMsgType[kParamCymbalDecay      ]=0;
  paramToMsgType[kParamCymbalWaveform   ]=1;
  
  paramToMsgType[kParamHihatType     ]=0;
  paramToMsgType[kParamHihatQ        ]=0;
  paramToMsgType[kParamHihatColor    ]=0;
  paramToMsgType[kParamHihatClosed   ]=0;
  paramToMsgType[kParamHihatOpen     ]=0;
  
  paramToMsgType[kParamSnaredrum1Impact          ]=0;
  paramToMsgType[kParamSnaredrum1Time            ]=0;
  paramToMsgType[kParamSnaredrum1Q               ]=0;
  paramToMsgType[kParamSnaredrum1Tune            ]=0;
  paramToMsgType[kParamSnaredrum1Color           ]=0;
  paramToMsgType[kParamSnaredrum1BodySnares      ]=0;
  paramToMsgType[kParamSnaredrum1Tightness       ]=0;
  paramToMsgType[kParamSnaredrum1Waveform        ]=0;
  paramToMsgType[kParamSnaredrum1Decay           ]=0;
  
  paramToMsgType[kParamSnaredrum2Impact] = 0;
  paramToMsgType[kParamSnaredrum2Time] = 0;
  paramToMsgType[kParamSnaredrum2Q] = 1;
  paramToMsgType[kParamSnaredrum2Tune] = 0;
  paramToMsgType[kParamSnaredrum2Color] = 1;
  paramToMsgType[kParamSnaredrum2BodySnares] = 0;
  paramToMsgType[kParamSnaredrum2Tightness] = 0;
  paramToMsgType[kParamSnaredrum2Waveform] = 0;
  paramToMsgType[kParamSnaredrum2Decay] = 0;
  
  paramToMsgType[kParamTom1Impact     ]=0;
  paramToMsgType[kParamTom1Time       ]=0;
  paramToMsgType[kParamTom1NoiseLevel      ]=0;
  paramToMsgType[kParamTom1Tune       ]=0;
  paramToMsgType[kParamTom1NoiseColor      ]=0;
  paramToMsgType[kParamTom1Waveform] = 0;
  paramToMsgType[kParamTom1NoiseDecay      ]=0;
  
  paramToMsgType[kParamTom2Impact] = 0;
  paramToMsgType[kParamTom2Time] = 0;
  paramToMsgType[kParamTom2NoiseLevel] = 0;
  paramToMsgType[kParamTom2Tune] = 0;
  paramToMsgType[kParamTom2NoiseColor] = 0;
  paramToMsgType[kParamTom2Waveform] = 0;
  paramToMsgType[kParamTom2NoiseDecay] = 0;
  
  paramToMsgType[kParamEffectsDelayFeedback     ]=0;
  
  
  paramToMsgType[kParamEffectsFilterQ] = 1;
  paramToMsgType[kParamEffectsFilterEnvelope] = 1;
  paramToMsgType[kParamEffectsDriveTone] = 1;
  paramToMsgType[kParamEffectsChorusOffset] = 1;
  paramToMsgType[kParamEffectsChorusFeedback] = 1;
  paramToMsgType[kParamEffectsDelayDamp] = 1;   
  paramToMsgType[kParamEffectsFilterCutoff] = 1;
  paramToMsgType[kParamEffectsDriveAmount] = 1;
  paramToMsgType[kParamEffectsChorusRate] = 1;
  paramToMsgType[kParamEffectsChorusDepth] = 1;
  paramToMsgType[kParamEffectsDelayTimeL] = 1;
  paramToMsgType[kParamEffectsDelayTimeR] = 1;
  paramToMsgType[kParamEffectsFilterType] = 1;
  paramToMsgType[kParamEffectsFilterMute] = 1;
  paramToMsgType[kParamEffectsDriveMute] = 1;
  paramToMsgType[kParamEffectsChorusMute] = 1;
  paramToMsgType[kParamEffectsDelayMute] = 1;
  
  paramToMsgType[kParamMixerDelayBD1         ]=1;
  paramToMsgType[kParamMixerDelayBD2         ]=1;
  paramToMsgType[kParamMixerDelaySD1         ]=1;
  paramToMsgType[kParamMixerDelaySD2         ]=1;
  paramToMsgType[kParamMixerDelayHH          ]=1;
  paramToMsgType[kParamMixerDelayTO1         ]=1;
  paramToMsgType[kParamMixerDelayTO2         ]=1;
  paramToMsgType[kParamMixerDelayCY          ]=1;
  paramToMsgType[kParamMixerDelayCL          ]=1;
  paramToMsgType[kParamMixerDelayCB          ]=1;
  paramToMsgType[kParamMixerDelayCow         ]=1;
  paramToMsgType[kParamMixerDelayBass        ]=1;
  paramToMsgType[kParamMixerChorusBD1       ]=1;
  paramToMsgType[kParamMixerChorusBD2       ]=1;
  paramToMsgType[kParamMixerChorusSD1       ]=1;
  paramToMsgType[kParamMixerChorusSD2       ]=1;
  paramToMsgType[kParamMixerChorusHH        ]=1;
  paramToMsgType[kParamMixerChorusTO1       ]=1;
  paramToMsgType[kParamMixerChorusTO2       ]=1;
  paramToMsgType[kParamMixerChorusCY        ]=1;
  paramToMsgType[kParamMixerChorusCL        ]=1;
  paramToMsgType[kParamMixerChorusCB        ]=1;
  paramToMsgType[kParamMixerChorusCow       ]=1;
  paramToMsgType[kParamMixerChorusBass      ]=1;
  paramToMsgType[kParamMixerPanBD1          ]=1;
  paramToMsgType[kParamMixerPanBD2          ]=1;
  paramToMsgType[kParamMixerPanSD1          ]=1;
  paramToMsgType[kParamMixerPanSD2          ]=1;
  paramToMsgType[kParamMixerPanHH           ]=1;
  paramToMsgType[kParamMixerPanTO1          ]=1;
  paramToMsgType[kParamMixerPanTO2          ]=1;
  paramToMsgType[kParamMixerPanCY           ]=1;
  paramToMsgType[kParamMixerPanCL           ]=1;
  paramToMsgType[kParamMixerPanCB           ]=1;
  paramToMsgType[kParamMixerPanCow          ]=1;
  paramToMsgType[kParamMixerPanBass         ]=1;
  paramToMsgType[kParamMixerLevelBD1        ]=0;
  paramToMsgType[kParamMixerLevelBD2        ]=0;
  paramToMsgType[kParamMixerLevelSD1        ]=0;
  paramToMsgType[kParamMixerLevelSD2        ]=0;
  paramToMsgType[kParamMixerLevelHH         ]=0;
  paramToMsgType[kParamMixerLevelTO1        ]=0;
  paramToMsgType[kParamMixerLevelTO2        ]=0;
  paramToMsgType[kParamMixerLevelCY         ]=0;
  paramToMsgType[kParamMixerLevelCL         ]=0;
  paramToMsgType[kParamMixerLevelCB         ]=0;
  paramToMsgType[kParamMixerLevelCow        ]=0;
  paramToMsgType[kParamMixerLevelBass       ]=0;
  paramToMsgType[kParamMixerDelayReturn      ]=0;
  paramToMsgType[kParamMixerChorusReturn     ]=0;


#if IPLUG_EDITOR // All UI methods and member variables should be within an IPLUG_EDITOR guard, should you want distributed UI
  mMakeGraphicsFunc = [&]() {
    return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS, 1.);
  };
  
  mLayoutFunc = [&](IGraphics* pGraphics) {

    pGraphics->LoadFont("Roboto-Regular", FN_ROBOTOREGULAR);
    pGraphics->LoadFont("Calibrib", FN_CALIBRIB);
    pGraphics->LoadFont("Calibri", FN_CALIBRI);
    const IRECT b = pGraphics->GetBounds();
    pGraphics->HandleMouseOver(true);
    IControl* pBG = new IPanelControl(IRECT(0, 0, HSM_W, HSK_H), IColor(255, 60, 60, 66));
    pGraphics->AttachControl(pBG);

    const IRECT controls = b.GetGridCell(1, 2, 2);

    IBitmap bitmap;
    
    bitmap = pGraphics->LoadBitmap(FN_MPA);
    IControl* logoCtrl = new IBitmapControl(HS_W + 40, HS_H + 28, bitmap, kNoParameter);
    pGraphics->AttachControl(logoCtrl, -1, "");

    bitmap = pGraphics->LoadBitmap(FN_BACKGROUND);
    IControl* backCtrl = new IBitmapControl(10, 10, bitmap, kNoParameter);
    pGraphics->AttachControl(backCtrl, -1, "");

    /**************************** Bass Synth *************************************/
    int x = 0;
    int y = 0;

    bitmap = pGraphics->LoadBitmap(FN_BASS);
    IControl* bassPanel = new IBitmapControl(0, 0, bitmap, kNoParameter);
    pGraphics->AttachControl(bassPanel, -1, "BassSynth");

    bitmap = pGraphics->LoadBitmap(FN_MEDIUMKNOBROUND, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 176, y + 640, bitmap, kParamBassSynthGlide), -1, "BassSynth");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 234, y + 640, bitmap, kParamBassSynthFine), -1, "BassSynth");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 285, y + 640, bitmap, kParamBassSynthFormant), -1, "BassSynth");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 349, y + 640, bitmap, kParamBassSynthDrive), -1, "BassSynth");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 396, y + 640, bitmap, kParamBassSynthQ), -1, "BassSynth");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 445, y + 640, bitmap, kParamBassSynthEnvAmt), -1, "BassSynth");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 523, y + 640, bitmap, kParamBassSynthFilterMod), -1, "BassSynth");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 445, y + 577, bitmap, kParamBassSynthTracking), -1, "BassSynth");

    bitmap = pGraphics->LoadBitmap(FN_LARGEKNOBROUND, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 250, y + 572, bitmap, kParamBassSynthCoarse), -1, "BassSynth");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 361, y + 572, bitmap, kParamBassSynthCutoff), -1, "BassSynth");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 511, y + 572, bitmap, kParamBassSynthRate), -1, "BassSynth");

    bitmap = pGraphics->LoadBitmap(FN_RETRIGBUTTON, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(x + 177, y + 590, bitmap, kParamBassSynthRetrig), -1, "BassSynth");

    bitmap = pGraphics->LoadBitmap(FN_MEDIUMFADER);
    pGraphics->AttachControl(new IBSliderControlMidi(x + 598, y + 575, 100, kParamBassSynthFilterEnvAttack, bitmap), -1, "BassSynth");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 648, y + 575, 100, kParamBassSynthFilterEnvDecay, bitmap), -1, "BassSynth");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 707, y + 575, 100, kParamBassSynthAmpEnvAttack, bitmap), -1, "BassSynth");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 757, y + 575, 100, kParamBassSynthAmpEnvDecay, bitmap), -1, "BassSynth");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 807, y + 575, 100, kParamBassSynthAmpEnvRelease, bitmap), -1, "BassSynth");

    /**************************** Bassdrum 1 *************************************/
    x = 0;
    y = 0;

    bitmap = pGraphics->LoadBitmap(FN_BASSDRUM1);
    IControl* bassdrum1Panel = new IBitmapControl(0, 0, bitmap, kNoParameter);
    pGraphics->AttachControl(bassdrum1Panel, -1, "Bassdrum1");

    bitmap = pGraphics->LoadBitmap(FN_MEDIUMKNOBROUND, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 256, y + 576, bitmap, kParamBassdrum1BodyImpact), -1, "Bassdrum1");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 256, y + 641, bitmap, kParamBassdrum1BodyTime), -1, "Bassdrum1");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 456, y + 576, bitmap, kParamBassdrum1TransientImpact), -1, "Bassdrum1");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 456, y + 641, bitmap, kParamBassdrum1TransientTime), -1, "Bassdrum1");

    bitmap = pGraphics->LoadBitmap(FN_LARGEKNOBROUND, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 171, y + 622, bitmap, kParamBassdrum1SynthTune), -1, "Bassdrum1");

    bitmap = pGraphics->LoadBitmap(FN_BDSWITCH,3);
    pGraphics->AttachControl(new IBitmapControl(x + 300, y + 583, bitmap, kParamBassdrum1BodyPunchSnapNormal), -1, "Bassdrum1");
    pGraphics->AttachControl(new IBitmapControl(x + 500, y + 583, bitmap, kParamBassdrum1TransientPunchSnapNormal), -1, "Bassdrum1");

    bitmap = pGraphics->LoadBitmap(FN_LARGESWITCHPOINTER, 3);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 355, y + 590, bitmap, kParamBassdrum1BodyPunchSnapNormal, 0, EDirection::Vertical, 2.), -1, "Bassdrum1");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 555, y + 590, bitmap, kParamBassdrum1TransientPunchSnapNormal, 0, EDirection::Vertical, 2.), -1, "Bassdrum1");
    
    
    bitmap = pGraphics->LoadBitmap(FN_WAVEFORMBUTTON, 19);
    pGraphics->AttachControl(new IBitmapControl(x + 158, y + 577, bitmap, kParamBassdrum1Waveform), -1, "Bassdrum1");
    std::function<double(double)> mappingFunc = [](double midiVal) {return midiVal * 127. / 18.; };
    pGraphics->AttachControl(new IInvisibleCaptionControlMidi(IRECT(x + 158, y + 579, x + 240, y + 596), kParamBassdrum1Waveform, DEFAULT_TEXT, DEFAULT_BGCOLOR, true, mappingFunc), kCtrlTagBD1Wave, "Bassdrum1");
    bitmap = pGraphics->LoadBitmap(FN_LEFTBUTTON,2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 158, y + 597, bitmap, [](IControl *ctrl) {
      if (ctrl->GetValue() == 1) {
        int val = ctrl->GetUI()->GetControlWithTag(kCtrlTagBD1Wave)->GetParam()->Int();
        val = (val - 1); if (val < 0) val = 18;
        double valN = ctrl->GetUI()->GetControlWithTag(kCtrlTagBD1Wave)->GetParam()->ToNormalized(val);
        ctrl->GetUI()->GetControlWithTag(kCtrlTagBD1Wave)->SetValue(valN);
        ctrl->GetUI()->GetControlWithTag(kCtrlTagBD1Wave)->SetDirty(true);
      }
      }), -1, "Bassdrum1");
    bitmap = pGraphics->LoadBitmap(FN_RIGHTBUTTON,2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 218, y + 597, bitmap, [](IControl* ctrl) {
      if (ctrl->GetValue() == 1) {
        int val = ctrl->GetUI()->GetControlWithTag(kCtrlTagBD1Wave)->GetParam()->Int();
        val = (val + 1) % 19;
        double valN = ctrl->GetUI()->GetControlWithTag(kCtrlTagBD1Wave)->GetParam()->ToNormalized(val);
        ctrl->GetUI()->GetControlWithTag(kCtrlTagBD1Wave)->SetValue(valN);
        ctrl->GetUI()->GetControlWithTag(kCtrlTagBD1Wave)->SetDirty(true);
      }
      }), -1, "Bassdrum1");

    bitmap = pGraphics->LoadBitmap(FN_MEDIUMFADER);
    pGraphics->AttachControl(new IBSliderControlMidi(x + 658, y + 575, 100, kParamBassdrum1AmpEnvAttack, bitmap), -1, "Bassdrum1");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 707, y + 575, 100, kParamBassdrum1AmpEnvDecay, bitmap), -1, "Bassdrum1");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 758, y + 575, 100, kParamBassdrum1AmpEnvRelease, bitmap), -1, "Bassdrum1");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 827, y + 575, 100, kParamBassdrum1AmpEnvCurve, bitmap), -1, "Bassdrum1");

    /**************************** Bassdrum 2 *************************************/
    x = 0;
    y = 0;

    bitmap = pGraphics->LoadBitmap(FN_BASSDRUM2);
    IControl* bassdrum2Panel = new IBitmapControl(0, 0, bitmap, kNoParameter);
    pGraphics->AttachControl(bassdrum2Panel, -1, "Bassdrum2");

    bitmap = pGraphics->LoadBitmap(FN_MEDIUMKNOBROUND, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 256, y + 576, bitmap, kParamBassdrum2BodyImpact), -1, "Bassdrum2");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 256, y + 641, bitmap, kParamBassdrum2BodyTime), -1, "Bassdrum2");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 456, y + 576, bitmap, kParamBassdrum2TransientImpact), -1, "Bassdrum2");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 456, y + 641, bitmap, kParamBassdrum2TransientTime), -1, "Bassdrum2");

    bitmap = pGraphics->LoadBitmap(FN_LARGEKNOBROUND, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 171, y + 622, bitmap, kParamBassdrum2SynthTune), -1, "Bassdrum2");

    bitmap = pGraphics->LoadBitmap(FN_BDSWITCH,3);
    pGraphics->AttachControl(new IBitmapControl(x + 300, y + 583, bitmap, kParamBassdrum2BodyPunchSnapNormal), -1, "Bassdrum2");
    pGraphics->AttachControl(new IBitmapControl(x + 500, y + 583, bitmap, kParamBassdrum2TransientPunchSnapNormal), -1, "Bassdrum2");

    bitmap = pGraphics->LoadBitmap(FN_LARGESWITCHPOINTER, 3);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 355, y + 590, bitmap, kParamBassdrum2BodyPunchSnapNormal, 0, EDirection::Vertical, 2.), -1, "Bassdrum2");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 555, y + 590, bitmap, kParamBassdrum2TransientPunchSnapNormal, 0, EDirection::Vertical, 2.), -1, "Bassdrum2");

    bitmap = pGraphics->LoadBitmap(FN_WAVEFORMBUTTON, 19);
    pGraphics->AttachControl(new IBitmapControl(x + 158, y + 577, bitmap, kParamBassdrum2Waveform), -1, "Bassdrum2");
    mappingFunc = [](double midiVal) {return midiVal * 127. / 18.; };
    pGraphics->AttachControl(new IInvisibleCaptionControlMidi(IRECT(x + 158, y + 579, x + 240, y + 596), kParamBassdrum2Waveform, DEFAULT_TEXT, DEFAULT_BGCOLOR, true, mappingFunc), kCtrlTagBD2Wave, "Bassdrum2");
    bitmap = pGraphics->LoadBitmap(FN_LEFTBUTTON,2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 158, y + 597, bitmap, [](IControl *ctrl) {
      if (ctrl->GetValue() == 1) {
        int val = ctrl->GetUI()->GetControlWithTag(kCtrlTagBD2Wave)->GetParam()->Int();
        val = (val - 1); if (val < 0) val = 18;
        double valN = ctrl->GetUI()->GetControlWithTag(kCtrlTagBD2Wave)->GetParam()->ToNormalized(val);
        ctrl->GetUI()->GetControlWithTag(kCtrlTagBD2Wave)->SetValue(valN);
        ctrl->GetUI()->GetControlWithTag(kCtrlTagBD2Wave)->SetDirty(true);
      }
      }), -1, "Bassdrum2");
    bitmap = pGraphics->LoadBitmap(FN_RIGHTBUTTON,2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 218, y + 597, bitmap, [](IControl *ctrl) {
      if (ctrl->GetValue() == 1) {
        int val = ctrl->GetUI()->GetControlWithTag(kCtrlTagBD2Wave)->GetParam()->Int();
        val = (val + 1) % 19;
        double valN = ctrl->GetUI()->GetControlWithTag(kCtrlTagBD2Wave)->GetParam()->ToNormalized(val);
        ctrl->GetUI()->GetControlWithTag(kCtrlTagBD2Wave)->SetValue(valN);
        ctrl->GetUI()->GetControlWithTag(kCtrlTagBD2Wave)->SetDirty(true);
      }
      }), -1, "Bassdrum2");

    bitmap = pGraphics->LoadBitmap(FN_MEDIUMFADER);
    pGraphics->AttachControl(new IBSliderControlMidi(x + 658, y + 575, 100, kParamBassdrum2AmpEnvAttack, bitmap), -1, "Bassdrum2");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 707, y + 575, 100, kParamBassdrum2AmpEnvDecay, bitmap), -1, "Bassdrum2");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 758, y + 575, 100, kParamBassdrum2AmpEnvRelease, bitmap), -1, "Bassdrum2");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 827, y + 575, 100, kParamBassdrum2AmpEnvCurve, bitmap), -1, "Bassdrum2");

    /**************************** Cabasa *************************************/
    x = 0;
    y = 0;

    bitmap = pGraphics->LoadBitmap(FN_CABASA);
    IControl* cabasaPanel = new IBitmapControl(0, 0, bitmap, kNoParameter);
    pGraphics->AttachControl(cabasaPanel, -1, "Cabasa");

    bitmap = pGraphics->LoadBitmap(FN_MEDIUMKNOBROUND, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 436, y + 641, bitmap, kParamCabasaQ), -1, "Cabasa");

    bitmap = pGraphics->LoadBitmap(FN_LARGEKNOBROUND, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 425, y + 570, bitmap, kParamCabasaColor), -1, "Cabasa");

    bitmap = pGraphics->LoadBitmap(FN_MEDIUMFADER);
    pGraphics->AttachControl(new IBSliderControlMidi(x + 507, y + 575, 100, kParamCabasaAttack, bitmap), -1, "Cabasa");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 557, y + 575, 100, kParamCabasaDecay, bitmap), -1, "Cabasa");

    /**************************** Clap *************************************/
    x = 0;
    y = 0;

    bitmap = pGraphics->LoadBitmap(FN_CLAP);
    IControl* ClapPanel = new IBitmapControl(0, 0, bitmap, kNoParameter);
    pGraphics->AttachControl(ClapPanel, -1, "Clap");

    bitmap = pGraphics->LoadBitmap(FN_MEDIUMKNOBROUND, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 436, y + 641, bitmap, kParamClapPeople), -1, "Clap");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 496, y + 641, bitmap, kParamClapQ), -1, "Clap");

    bitmap = pGraphics->LoadBitmap(FN_LARGEKNOBROUND, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 455, y + 570, bitmap, kParamClapColor), -1, "Clap");

    bitmap = pGraphics->LoadBitmap(FN_MEDIUMFADER);
    pGraphics->AttachControl(new IBSliderControlMidi(x + 547, y + 575, 100, kParamClapDecay, bitmap), -1, "Clap");

    /**************************** Cowbell *************************************/
    x = 0;
    y = 0;

    bitmap = pGraphics->LoadBitmap(FN_COWBELL);
    IControl* CowbellPanel = new IBitmapControl(0, 0, bitmap, kNoParameter);
    pGraphics->AttachControl(CowbellPanel, -1, "Cowbell");

    bitmap = pGraphics->LoadBitmap(FN_MEDIUMKNOBROUND, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 516, y + 576, bitmap, kParamCowbellFM), -1, "Cowbell");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 516, y + 641, bitmap, kParamCowbellTonality), -1, "Cowbell");

    bitmap = pGraphics->LoadBitmap(FN_LARGEKNOBROUND, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 430, y + 622, bitmap, kParamCowbellTune), -1, "Cowbell");

    bitmap = pGraphics->LoadBitmap(FN_MEDIUMFADER);
    pGraphics->AttachControl(new IBSliderControlMidi(x + 567, y + 575, 100, kParamCowbellDecay, bitmap), -1, "Cowbell");

    bitmap = pGraphics->LoadBitmap(FN_WAVEFORMBUTTON, 19);
    pGraphics->AttachControl(new IBitmapControl(x + 417, y + 577, bitmap, kParamCowbellWaveform), -1, "Cowbell");
    mappingFunc = [](double midiVal) {return midiVal * 127. / 18.; };
    pGraphics->AttachControl(new IInvisibleCaptionControlMidi(IRECT(x + 417, y + 577, x + 499, y + 594), kParamCowbellWaveform, DEFAULT_TEXT, DEFAULT_BGCOLOR, true, mappingFunc), kCtrlTagCowWave, "Cowbell");
    bitmap = pGraphics->LoadBitmap(FN_LEFTBUTTON,2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 417, y + 597, bitmap, [](IControl *ctrl) {
      if (ctrl->GetValue() == 1) {
        int val = ctrl->GetUI()->GetControlWithTag(kCtrlTagCowWave)->GetParam()->Int();
        val = (val - 1); if (val < 0) val = 18;
        double valN = ctrl->GetUI()->GetControlWithTag(kCtrlTagCowWave)->GetParam()->ToNormalized(val);
        ctrl->GetUI()->GetControlWithTag(kCtrlTagCowWave)->SetValue(valN);
        ctrl->GetUI()->GetControlWithTag(kCtrlTagCowWave)->SetDirty(true);
      }
      }), -1, "Cowbell");
    bitmap = pGraphics->LoadBitmap(FN_RIGHTBUTTON,2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 477, y + 597, bitmap, [](IControl *ctrl) {
      if (ctrl->GetValue() == 1) {
        int val = ctrl->GetUI()->GetControlWithTag(kCtrlTagCowWave)->GetParam()->Int();
        val = (val + 1) % 19;
        double valN = ctrl->GetUI()->GetControlWithTag(kCtrlTagCowWave)->GetParam()->ToNormalized(val);
        ctrl->GetUI()->GetControlWithTag(kCtrlTagCowWave)->SetValue(valN);
        ctrl->GetUI()->GetControlWithTag(kCtrlTagCowWave)->SetDirty(true);
      }
      }), -1, "Cowbell");

    /**************************** Cymbal *************************************/
    x = 0;
    y = 0;

    bitmap = pGraphics->LoadBitmap(FN_CYMBAL);
    IControl* CymbalPanel = new IBitmapControl(0, 0, bitmap, kNoParameter);
    pGraphics->AttachControl(CymbalPanel, -1, "Cymbal");

    bitmap = pGraphics->LoadBitmap(FN_MEDIUMKNOBROUND, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 483, y + 641, bitmap, kParamCymbalSwell), -1, "Cymbal");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 543, y + 641, bitmap, kParamCymbalDefinition), -1, "Cymbal");

    bitmap = pGraphics->LoadBitmap(FN_LARGEKNOBROUND, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 408, y + 621, bitmap, kParamCymbalTune), -1, "Cymbal");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 501, y + 571, bitmap, kParamCymbalColor), -1, "Cymbal");

    bitmap = pGraphics->LoadBitmap(FN_MEDIUMFADER);
    pGraphics->AttachControl(new IBSliderControlMidi(x + 593, y + 575, 100, kParamCymbalDecay, bitmap), -1, "Cymbal");

    bitmap = pGraphics->LoadBitmap(FN_CYMBALBUTTON, 9);
    pGraphics->AttachControl(new IBitmapControl(x + 394, y + 577, bitmap, kParamCymbalWaveform), -1, "Cymbal");
    mappingFunc = [](double midiVal) {return midiVal * 127. / 9.; };
    pGraphics->AttachControl(new IInvisibleCaptionControlMidi(IRECT(x + 394, y + 577, x + 476, y + 594), kParamCymbalWaveform, DEFAULT_TEXT, DEFAULT_BGCOLOR, true, mappingFunc), kCtrlCymbalWave, "Cymbal");
    bitmap = pGraphics->LoadBitmap(FN_LEFTBUTTON,2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 394, y + 597, bitmap, [](IControl *ctrl) {
      if (ctrl->GetValue() == 1) {
        int val = ctrl->GetUI()->GetControlWithTag(kCtrlCymbalWave)->GetParam()->Int();
        val = (val - 1); if (val < 0) val = 8;
        double valN = ctrl->GetUI()->GetControlWithTag(kCtrlCymbalWave)->GetParam()->ToNormalized(val);
        ctrl->GetUI()->GetControlWithTag(kCtrlCymbalWave)->SetValue(valN);
        ctrl->GetUI()->GetControlWithTag(kCtrlCymbalWave)->SetDirty(true);
      }
      }), -1, "Cymbal");
    bitmap = pGraphics->LoadBitmap(FN_RIGHTBUTTON,2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 454, y + 597, bitmap, [](IControl *ctrl) {
      if (ctrl->GetValue() == 1) {
        int val = ctrl->GetUI()->GetControlWithTag(kCtrlCymbalWave)->GetParam()->Int();
        val = (val + 1) % 9;
        double valN = ctrl->GetUI()->GetControlWithTag(kCtrlCymbalWave)->GetParam()->ToNormalized(val);
        ctrl->GetUI()->GetControlWithTag(kCtrlCymbalWave)->SetValue(valN);
        ctrl->GetUI()->GetControlWithTag(kCtrlCymbalWave)->SetDirty(true);
      }
      }), -1, "Cymbal");

    /**************************** HIHAT *************************************/
    x = 0;
    y = 0;

    bitmap = pGraphics->LoadBitmap(FN_HIHAT);
    IControl* HihatPanel = new IBitmapControl(0, 0, bitmap, kNoParameter);
    pGraphics->AttachControl(HihatPanel, -1, "Hihat");

    bitmap = pGraphics->LoadBitmap(FN_MEDIUMKNOBROUND, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 417, y + 641, bitmap, kParamHihatType), -1, "Hihat");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 456, y + 641, bitmap, kParamHihatQ), -1, "Hihat");

    bitmap = pGraphics->LoadBitmap(FN_LARGEKNOBROUND, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 425, y + 570, bitmap, kParamHihatColor), -1, "Hihat");

    bitmap = pGraphics->LoadBitmap(FN_MEDIUMFADER);
    pGraphics->AttachControl(new IBSliderControlMidi(x + 518, y + 575, 100, kParamHihatClosed, bitmap), -1, "Hihat");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 567, y + 575, 100, kParamHihatOpen, bitmap), -1, "Hihat");

    /**************************** Snaredrum 1 *************************************/
    x = 0;
    y = 0;

    bitmap = pGraphics->LoadBitmap(FN_SNAREDRUM1);
    IControl* Snaredrum1Panel = new IBitmapControl(0, 0, bitmap, kNoParameter);
    pGraphics->AttachControl(Snaredrum1Panel, -1, "Snaredrum1");

    bitmap = pGraphics->LoadBitmap(FN_MEDIUMKNOBROUND, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 446, y + 576, bitmap, kParamSnaredrum1Impact), -1, "Snaredrum1");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 446 , y + 641, bitmap, kParamSnaredrum1Time), -1, "Snaredrum1");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 517, y + 641, bitmap, kParamSnaredrum1Q), -1, "Snaredrum1");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 585, y + 576, bitmap, kParamSnaredrum1BodySnares), -1, "Snaredrum1");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 585, y + 641, bitmap, kParamSnaredrum1Tightness), -1, "Snaredrum1");

    bitmap = pGraphics->LoadBitmap(FN_LARGEKNOBROUND, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 360, y + 621, bitmap, kParamSnaredrum1Tune), -1, "Snaredrum1");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 505, y + 570, bitmap, kParamSnaredrum1Color), -1, "Snaredrum1");

    bitmap = pGraphics->LoadBitmap(FN_WAVEFORMBUTTON, 19);
    pGraphics->AttachControl(new IBitmapControl(x + 347, y + 577, bitmap, kParamSnaredrum1Waveform), -1, "Snaredrum1");
    mappingFunc = [](double midiVal) {return midiVal * 127. / 18.; };
    pGraphics->AttachControl(new IInvisibleCaptionControlMidi(IRECT(x + 347, y + 577, x + 429, y + 594), kParamSnaredrum1Waveform, DEFAULT_TEXT, DEFAULT_BGCOLOR, true, mappingFunc), kCtrlTagSD1Wave, "Snaredrum1");
    bitmap = pGraphics->LoadBitmap(FN_LEFTBUTTON,2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 347, y + 597, bitmap, [](IControl *ctrl) {
      if (ctrl->GetValue() == 1) {
        int val = ctrl->GetUI()->GetControlWithTag(kCtrlTagSD1Wave)->GetParam()->Int();
        val = (val - 1); if (val < 0) val = 18;
        double valN = ctrl->GetUI()->GetControlWithTag(kCtrlTagSD1Wave)->GetParam()->ToNormalized(val);
        ctrl->GetUI()->GetControlWithTag(kCtrlTagSD1Wave)->SetValue(valN);
        ctrl->GetUI()->GetControlWithTag(kCtrlTagSD1Wave)->SetDirty(true);
      }
      }), -1, "Snaredrum1");
    bitmap = pGraphics->LoadBitmap(FN_RIGHTBUTTON,2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 407, y + 597, bitmap, [](IControl *ctrl) {
      if (ctrl->GetValue() == 1) {
        int val = ctrl->GetUI()->GetControlWithTag(kCtrlTagSD1Wave)->GetParam()->Int();
        val = (val + 1) % 19;
        double valN = ctrl->GetUI()->GetControlWithTag(kCtrlTagSD1Wave)->GetParam()->ToNormalized(val);
        ctrl->GetUI()->GetControlWithTag(kCtrlTagSD1Wave)->SetValue(valN);
        ctrl->GetUI()->GetControlWithTag(kCtrlTagSD1Wave)->SetDirty(true);
      }
      }), -1, "Snaredrum1");

    bitmap = pGraphics->LoadBitmap(FN_MEDIUMFADER);
    pGraphics->AttachControl(new IBSliderControlMidi(x + 637, y + 575, 100, kParamSnaredrum1Decay, bitmap), -1, "Snaredrum1");

    /**************************** Snaredrum 2 *************************************/
    x = 0;
    y = 0;

    bitmap = pGraphics->LoadBitmap(FN_SNAREDRUM2);
    IControl* Snaredrum2Panel = new IBitmapControl(0, 0, bitmap, kNoParameter);
    pGraphics->AttachControl(Snaredrum2Panel, -1, "Snaredrum2");

    bitmap = pGraphics->LoadBitmap(FN_MEDIUMKNOBROUND, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 446, y + 576, bitmap, kParamSnaredrum2Impact), -1, "Snaredrum2");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 446, y + 641, bitmap, kParamSnaredrum2Time), -1, "Snaredrum2");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 517, y + 641, bitmap, kParamSnaredrum2Q), -1, "Snaredrum2");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 585, y + 576, bitmap, kParamSnaredrum2BodySnares), -1, "Snaredrum2");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 585, y + 641, bitmap, kParamSnaredrum2Tightness), -1, "Snaredrum2");

    bitmap = pGraphics->LoadBitmap(FN_LARGEKNOBROUND, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 360, y + 621, bitmap, kParamSnaredrum2Tune), -1, "Snaredrum2");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 505, y + 570, bitmap, kParamSnaredrum2Color), -1, "Snaredrum2");

    bitmap = pGraphics->LoadBitmap(FN_WAVEFORMBUTTON, 19);
    pGraphics->AttachControl(new IBitmapControl(x + 347, y + 577, bitmap, kParamSnaredrum2Waveform), -1, "Snaredrum2");
    mappingFunc = [](double midiVal) {return midiVal * 127. / 18.; };
    pGraphics->AttachControl(new IInvisibleCaptionControlMidi(IRECT(x + 347, y + 577, x + 429, y + 594), kParamSnaredrum2Waveform, DEFAULT_TEXT, DEFAULT_BGCOLOR, true, mappingFunc), kCtrlTagSD2Wave, "Snaredrum2");
    bitmap = pGraphics->LoadBitmap(FN_LEFTBUTTON,2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 347, y + 597, bitmap, [](IControl *ctrl) {
      if (ctrl->GetValue() == 1) {
        int val = ctrl->GetUI()->GetControlWithTag(kCtrlTagSD2Wave)->GetParam()->Int();
        val = (val - 1); if (val < 0) val = 18;
        double valN = ctrl->GetUI()->GetControlWithTag(kCtrlTagSD2Wave)->GetParam()->ToNormalized(val);
        ctrl->GetUI()->GetControlWithTag(kCtrlTagSD2Wave)->SetValue(valN);
        ctrl->GetUI()->GetControlWithTag(kCtrlTagSD2Wave)->SetDirty(true);
      }
      }), -1, "Snaredrum2");
    bitmap = pGraphics->LoadBitmap(FN_RIGHTBUTTON,2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 407, y + 597, bitmap, [](IControl *ctrl) {
      if (ctrl->GetValue() == 1) {
        int val = ctrl->GetUI()->GetControlWithTag(kCtrlTagSD2Wave)->GetParam()->Int();
        val = (val + 1) % 19;
        double valN = ctrl->GetUI()->GetControlWithTag(kCtrlTagSD2Wave)->GetParam()->ToNormalized(val);
        ctrl->GetUI()->GetControlWithTag(kCtrlTagSD2Wave)->SetValue(valN);
        ctrl->GetUI()->GetControlWithTag(kCtrlTagSD2Wave)->SetDirty(true);
      }
      }), -1, "Snaredrum2");

    bitmap = pGraphics->LoadBitmap(FN_MEDIUMFADER);
    pGraphics->AttachControl(new IBSliderControlMidi(x + 637, y + 575, 100, kParamSnaredrum2Decay, bitmap), -1, "Snaredrum2");

    /**************************** Tom 1 *************************************/
    x = 0;
    y = 0;

    bitmap = pGraphics->LoadBitmap(FN_TOM1);
    IControl* Tom1Panel = new IBitmapControl(0, 0, bitmap, kNoParameter);
    pGraphics->AttachControl(Tom1Panel, -1, "Tom1");

    bitmap = pGraphics->LoadBitmap(FN_MEDIUMKNOBROUND, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 482, y + 577, bitmap, kParamTom1Impact), -1, "Tom1");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 482, y + 641, bitmap, kParamTom1Time), -1, "Tom1");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 551, y + 641, bitmap, kParamTom1NoiseLevel), -1, "Tom1");

    bitmap = pGraphics->LoadBitmap(FN_LARGEKNOBROUND, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 396, y + 621, bitmap, kParamTom1Tune), -1, "Tom1");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 539, y + 571, bitmap, kParamTom1NoiseColor), -1, "Tom1");

    bitmap = pGraphics->LoadBitmap(FN_WAVEFORMBUTTON, 19);
    pGraphics->AttachControl(new IBitmapControl(x + 382, y + 577, bitmap, kParamTom1Waveform), -1, "Tom1");
    mappingFunc = [](double midiVal) {return midiVal * 127. / 18.; };
    pGraphics->AttachControl(new IInvisibleCaptionControlMidi(IRECT(x + 382, y + 577, x + 464, y + 594), kParamTom1Waveform, DEFAULT_TEXT, DEFAULT_BGCOLOR, true, mappingFunc), kCtrlTagTO1Wave, "Tom1");
    bitmap = pGraphics->LoadBitmap(FN_LEFTBUTTON,2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 382, y + 597, bitmap, [](IControl *ctrl) {
      if (ctrl->GetValue() == 1) {
        int val = ctrl->GetUI()->GetControlWithTag(kCtrlTagTO1Wave)->GetParam()->Int();
        val = (val - 1); if (val < 0) val = 18;
        double valN = ctrl->GetUI()->GetControlWithTag(kCtrlTagTO1Wave)->GetParam()->ToNormalized(val);
        ctrl->GetUI()->GetControlWithTag(kCtrlTagTO1Wave)->SetValue(valN);
        ctrl->GetUI()->GetControlWithTag(kCtrlTagTO1Wave)->SetDirty(true);
      }
      }), -1, "Tom1");
    bitmap = pGraphics->LoadBitmap(FN_RIGHTBUTTON,2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 442, y + 597, bitmap, [](IControl *ctrl) {
      if (ctrl->GetValue() == 1) {
        int val = ctrl->GetUI()->GetControlWithTag(kCtrlTagTO1Wave)->GetParam()->Int();
        val = (val + 1) % 19;
        double valN = ctrl->GetUI()->GetControlWithTag(kCtrlTagTO1Wave)->GetParam()->ToNormalized(val);
        ctrl->GetUI()->GetControlWithTag(kCtrlTagTO1Wave)->SetValue(valN);
        ctrl->GetUI()->GetControlWithTag(kCtrlTagTO1Wave)->SetDirty(true);
      }
      }), -1, "Tom1");

    bitmap = pGraphics->LoadBitmap(FN_MEDIUMFADER);
    pGraphics->AttachControl(new IBSliderControlMidi(x + 603, y + 575, 100, kParamTom1NoiseDecay, bitmap), -1, "Tom1");

    /**************************** Tom 2 *************************************/
    x = 0;
    y = 0;

    bitmap = pGraphics->LoadBitmap(FN_TOM2);
    IControl* Tom2Panel = new IBitmapControl(0, 0, bitmap, kNoParameter);
    pGraphics->AttachControl(Tom2Panel, -1, "Tom2");

    bitmap = pGraphics->LoadBitmap(FN_MEDIUMKNOBROUND, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 482, y + 577, bitmap, kParamTom2Impact), -1, "Tom2");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 482, y + 641, bitmap, kParamTom2Time), -1, "Tom2");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 551, y + 641, bitmap, kParamTom2NoiseLevel), -1, "Tom2");

    bitmap = pGraphics->LoadBitmap(FN_LARGEKNOBROUND, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 396, y + 621, bitmap, kParamTom2Tune), -1, "Tom2");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 539, y + 571, bitmap, kParamTom2NoiseColor), -1, "Tom2");

    bitmap = pGraphics->LoadBitmap(FN_WAVEFORMBUTTON, 19);
    pGraphics->AttachControl(new IBitmapControl(x + 382, y + 577, bitmap, kParamTom2Waveform), -1, "Tom2");
    mappingFunc = [](double midiVal) {return midiVal * 127. / 18.; };
    pGraphics->AttachControl(new IInvisibleCaptionControlMidi(IRECT(x + 382, y + 577, x + 464, y + 594), kParamTom2Waveform, DEFAULT_TEXT, DEFAULT_BGCOLOR, true, mappingFunc), kCtrlTagTO2Wave, "Tom2");
    bitmap = pGraphics->LoadBitmap(FN_LEFTBUTTON,2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 382, y + 597, bitmap, [](IControl* ctrl) {
      if (ctrl->GetValue() == 1) {
        int val = ctrl->GetUI()->GetControlWithTag(kCtrlTagTO2Wave)->GetParam()->Int();
        val = (val - 1); if (val < 0) val = 18;
        double valN = ctrl->GetUI()->GetControlWithTag(kCtrlTagTO2Wave)->GetParam()->ToNormalized(val);
        ctrl->GetUI()->GetControlWithTag(kCtrlTagTO2Wave)->SetValue(valN);
        ctrl->GetUI()->GetControlWithTag(kCtrlTagTO2Wave)->SetDirty(true);
      }
      }), -1, "Tom2");
    bitmap = pGraphics->LoadBitmap(FN_RIGHTBUTTON,2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 442, y + 597, bitmap, [](IControl *ctrl) {
      if (ctrl->GetValue() == 1) {
        int val = ctrl->GetUI()->GetControlWithTag(kCtrlTagTO2Wave)->GetParam()->Int();
        val = (val + 1) % 19;
        double valN = ctrl->GetUI()->GetControlWithTag(kCtrlTagTO2Wave)->GetParam()->ToNormalized(val);
        ctrl->GetUI()->GetControlWithTag(kCtrlTagTO2Wave)->SetValue(valN);
        ctrl->GetUI()->GetControlWithTag(kCtrlTagTO2Wave)->SetDirty(true);
      }
      }), -1, "Tom2");

    bitmap = pGraphics->LoadBitmap(FN_MEDIUMFADER);
    pGraphics->AttachControl(new IBSliderControlMidi(x + 603, y + 575, 100, kParamTom2NoiseDecay, bitmap), -1, "Tom2");


   

    /**************************** GLOW *************************************/

    bitmap = pGraphics->LoadBitmap(FN_GLOW,2);
    pGraphics->AttachControl(new IBitmapControl(290, 137, bitmap, kNoParameter), kCtrlGlowBD1, "");
    pGraphics->AttachControl(new IBitmapControl(428, 139, bitmap, kNoParameter), kCtrlGlowBD2, "");
    pGraphics->AttachControl(new IBitmapControl(26, -5, bitmap, kNoParameter), kCtrlGlowHH, "");
    pGraphics->AttachControl(new IBitmapControl(546, 17, bitmap, kNoParameter), kCtrlGlowCB, "");
    pGraphics->AttachControl(new IBitmapControl(150, 10, bitmap, kNoParameter), kCtrlGlowCOW, "");
    pGraphics->AttachControl(new IBitmapControl(421, -9, bitmap, kNoParameter), kCtrlGlowCY, "");
    pGraphics->AttachControl(new IBitmapControl(263, -2, bitmap, kNoParameter), kCtrlGlowTO1, "");
    pGraphics->AttachControl(new IBitmapControl(350, 2, bitmap, kNoParameter), kCtrlGlowTO2, "");
    pGraphics->AttachControl(new IBitmapControl(559, 110, bitmap, kNoParameter), kCtrlGlowCL, "");
    pGraphics->AttachControl(new IBitmapControl(60, 91, bitmap, kNoParameter), kCtrlGlowSD1, "");
    pGraphics->AttachControl(new IBitmapControl(148, 142, bitmap, kNoParameter), kCtrlGlowSD2, "");

    /**************************** BLITZ *************************************/

    bitmap = pGraphics->LoadBitmap(FN_BD1RAYO,6);
    pGraphics->AttachControl(new IBitmapControl(464, 319, bitmap, kNoParameter), kCtrlBlitzBD1, "");
    bitmap = pGraphics->LoadBitmap(FN_BD2RAY, 6);
    pGraphics->AttachControl(new IBitmapControl(618, 323, bitmap, kNoParameter), kCtrlBlitzBD2, "");
    bitmap = pGraphics->LoadBitmap(FN_CLAPRAY, 6);
    pGraphics->AttachControl(new IBitmapControl(742, 220, bitmap, kNoParameter), kCtrlBlitzCL, "");
    bitmap = pGraphics->LoadBitmap(FN_CABASARAY, 6);
    pGraphics->AttachControl(new IBitmapControl(748, 36, bitmap, kNoParameter), kCtrlBlitzCB, "");
    bitmap = pGraphics->LoadBitmap(FN_CYMBALRAY, 6);
    pGraphics->AttachControl(new IBitmapControl(637, 22, bitmap, kNoParameter), kCtrlBlitzCY, "");
    bitmap = pGraphics->LoadBitmap(FN_TOM1RAY, 6);
    pGraphics->AttachControl(new IBitmapControl(412, 50, bitmap, kNoParameter), kCtrlBlitzTO1, "");
    bitmap = pGraphics->LoadBitmap(FN_TOM2RAY, 6);
    pGraphics->AttachControl(new IBitmapControl(497, 57, bitmap, kNoParameter), kCtrlBlitzTO2, "");
    bitmap = pGraphics->LoadBitmap(FN_COWBELLRAY, 6);
    pGraphics->AttachControl(new IBitmapControl(210, 35, bitmap, kNoParameter), kCtrlBlitzCOW, "");
    bitmap = pGraphics->LoadBitmap(FN_HITHATRAY, 6);
    pGraphics->AttachControl(new IBitmapControl(16, 90, bitmap, kNoParameter), kCtrlBlitzHH, "");
    bitmap = pGraphics->LoadBitmap(FN_SD1RAY, 6);
    pGraphics->AttachControl(new IBitmapControl(95, 247, bitmap, kNoParameter), kCtrlBlitzSD1, "");
    bitmap = pGraphics->LoadBitmap(FN_SD2RAY, 6);
    pGraphics->AttachControl(new IBitmapControl(320, 319, bitmap, kNoParameter), kCtrlBlitzSD2, "");

    /**************************** INSTRUMENTS PANELS *************************************/

    bitmap = pGraphics->LoadBitmap(FN_PANELS);
    IControl* panelCtrl = new IBitmapControl(10, 10, bitmap, kNoParameter);
    pGraphics->AttachControl(panelCtrl, -1, "");

    /**************************** INSTRUMENTS *************************************/

    x = 0; y = 0;

    bitmap = pGraphics->LoadBitmap(FN_HH,2);
    pGraphics->AttachControl(new IBitmapControl(IRECT(x+130, y+97, bitmap), bitmap), kCtrlTagHHInst, "");
  
    bitmap = pGraphics->LoadBitmap(FN_BD1, 2);
    pGraphics->AttachControl(new IBitmapControl(IRECT(x+374, y+222, bitmap), bitmap), kCtrlTagBD1Inst, "");
    
    bitmap = pGraphics->LoadBitmap(FN_BD2, 2);
    pGraphics->AttachControl(new IBitmapControl(IRECT(x+521, y+223, bitmap), bitmap), kCtrlTagBD2Inst, "");

    bitmap = pGraphics->LoadBitmap(FN_CB, 2);
    pGraphics->AttachControl(new IBitmapControl(IRECT(x+668, y+125, bitmap), bitmap), kCtrlTagCBInst, "");

    bitmap = pGraphics->LoadBitmap(FN_CY, 2);
    pGraphics->AttachControl(new IBitmapControl(IRECT(x+535, y+106, bitmap), bitmap), kCtrlTagCYInst, "");
   
    bitmap = pGraphics->LoadBitmap(FN_CL, 2);
    pGraphics->AttachControl(new IBitmapControl(IRECT(x+661, y+226, bitmap), bitmap), kCtrlTagCLInst, "");

    bitmap = pGraphics->LoadBitmap(FN_SD1, 2);
    pGraphics->AttachControl(new IBitmapControl(IRECT(x+164, y+207, bitmap), bitmap), kCtrlTagSD1Inst, "");

    bitmap = pGraphics->LoadBitmap(FN_SD2, 2);
    pGraphics->AttachControl(new IBitmapControl(IRECT(x+253, y+259, bitmap), bitmap), kCtrlTagSD2Inst, "");

    bitmap = pGraphics->LoadBitmap(FN_COW, 2);
    pGraphics->AttachControl(new IBitmapControl(IRECT(x+280, y+97, bitmap), bitmap), kCtrlTagCOWInst, "");
  
    bitmap = pGraphics->LoadBitmap(FN_TO, 4);
    pGraphics->AttachControl(new IBitmapControl(IRECT(x+370, y+99, bitmap), bitmap), kCtrlTagTO1Inst, "");

    auto triggerFunc = [&](IControl *ctrl) {
      int instr = ctrl->GetTag() - kCtrlTagBD1InstButton;
      /*if (instr >= 0 && instr <= 10) {
        if (instr != 7) ctrl->GetUI()->GetControlWithTag(kCtrlTagBD1Inst + instr)->SetValueFromDelegate(1.);
        if (instr == 5) ctrl->GetUI()->GetControlWithTag(kCtrlTagTO1Inst)->SetValueFromDelegate(0.25); // Tom 1
        if (instr == 7) ctrl->GetUI()->GetControlWithTag(kCtrlTagTO1Inst)->SetValueFromDelegate(0.5); // Tom 2
        ctrl->GetUI()->GetControlWithTag(kCtrlGlowBD1 + instr)->SetValueFromDelegate(1.);
        timer[instr].ResetTimer();
        ctrl->GetUI()->GetControlWithTag(kCtrlBlitzBD1 + instr)->SetValueFromDelegate(mBlitzCnt1 / 5.);
        ctrl->GetUI()->GetControlWithTag(kCtrlBlitzBD1 + instr)->Hide(false);
        mBlitzCnt1++;
        if (mBlitzCnt1 >= 6.) mBlitzCnt1 = 0;
      }*/

      if (instr == 10) instr = 11;
  
      IMidiMsg msg;
      if(ctrl->GetValue() == 1.) msg.MakeNoteOnMsg(60 + instr, 100, mChannel);
      else msg.MakeNoteOffMsg(60 + instr, 0, mChannel);
      msg.mOffset = -2; // antiloopback
      SendMidiMsgFromUI(msg);

    };

    pGraphics->AttachControl(new InvisibleButtonControl(IRECT(182, 161, 182+113, 161+55), triggerFunc), kCtrlTagHHInstButton, "");
    pGraphics->AttachControl(new InvisibleButtonControl(IRECT(426, 271, 426 + 130, 271 + 117), triggerFunc), kCtrlTagBD1InstButton, "");
    pGraphics->AttachControl(new InvisibleButtonControl(IRECT(571, 273, 571 + 129, 273 + 117), triggerFunc), kCtrlTagBD2InstButton, "");
    pGraphics->AttachControl(new InvisibleButtonControl(IRECT(714, 169, 714 + 94, 169 + 103), triggerFunc), kCtrlTagCBInstButton, "");
    pGraphics->AttachControl(new InvisibleButtonControl(IRECT(585, 162, 585 + 124, 162 + 50), triggerFunc), kCtrlTagCYInstButton, "");
    pGraphics->AttachControl(new InvisibleButtonControl(IRECT(713, 277, 713 + 122, 277 + 95), triggerFunc), kCtrlTagCLInstButton, "");
    pGraphics->AttachControl(new InvisibleButtonControl(IRECT(214, 257, 214 + 102, 257 + 67), triggerFunc), kCtrlTagSD1InstButton, "");
    pGraphics->AttachControl(new InvisibleButtonControl(IRECT(304, 308, 304 + 101, 308 + 66), triggerFunc), kCtrlTagSD2InstButton, "");
    pGraphics->AttachControl(new InvisibleButtonControl(IRECT(326, 145, 326 + 71, 145 + 108), triggerFunc), kCtrlTagCOWInstButton, "");
    pGraphics->AttachControl(new InvisibleButtonControl(IRECT(422, 150, 422 + 87, 150 + 101), triggerFunc), kCtrlTagTO1InstButton, "");
    pGraphics->AttachControl(new InvisibleButtonControl(IRECT(508, 167, 508 + 74, 167 + 85), triggerFunc), kCtrlTagTO2InstButton, "");

    /**************************** INSTRUMENTS ACTIVE *************************************/

    auto PanelFunc = [](IControl* pCaller) {
      if (pCaller->GetUI()) {

        if (pCaller->GetValue() == 1)
        {
          for(int k = 0; k < 24; k++) pCaller->GetUI()->GetControlWithTag(kCtrlTagHH+k)->SetValueFromDelegate(0.);

          pCaller->GetUI()->ForControlInGroup("BassSynth", [](IControl &ctrl) { ctrl.Hide(true); });
          pCaller->GetUI()->ForControlInGroup("Bassdrum1", [](IControl &ctrl) { ctrl.Hide(true); });
          pCaller->GetUI()->ForControlInGroup("Bassdrum2", [](IControl &ctrl) { ctrl.Hide(true); });
          pCaller->GetUI()->ForControlInGroup("Cabasa", [](IControl &ctrl) { ctrl.Hide(true); });
          pCaller->GetUI()->ForControlInGroup("Clap", [](IControl &ctrl) { ctrl.Hide(true); });
          pCaller->GetUI()->ForControlInGroup("Cowbell", [](IControl &ctrl) { ctrl.Hide(true); });
          pCaller->GetUI()->ForControlInGroup("Cymbal", [](IControl &ctrl) { ctrl.Hide(true); });
          pCaller->GetUI()->ForControlInGroup("Hihat", [](IControl &ctrl) { ctrl.Hide(true); });
          pCaller->GetUI()->ForControlInGroup("Snaredrum1", [](IControl &ctrl) { ctrl.Hide(true); });
          pCaller->GetUI()->ForControlInGroup("Snaredrum2", [](IControl &ctrl) { ctrl.Hide(true); });
          pCaller->GetUI()->ForControlInGroup("Tom1", [](IControl &ctrl) { ctrl.Hide(true); });
          pCaller->GetUI()->ForControlInGroup("Tom2", [](IControl &ctrl) { ctrl.Hide(true); });

          if(pCaller->GetTag()== kCtrlTagBasssynth || pCaller->GetTag() == kCtrlTagEditBasssynth) pCaller->GetUI()->ForControlInGroup("BassSynth", [](IControl &ctrl) { ctrl.Hide(false); });
          if(pCaller->GetTag()== kCtrlTagBD1 || pCaller->GetTag() == kCtrlTagEditBD1) pCaller->GetUI()->ForControlInGroup("Bassdrum1", [](IControl &ctrl) { ctrl.Hide(false); });
          if(pCaller->GetTag()== kCtrlTagBD2 || pCaller->GetTag() == kCtrlTagEditBD2) pCaller->GetUI()->ForControlInGroup("Bassdrum2", [](IControl &ctrl) { ctrl.Hide(false); });
          if(pCaller->GetTag()== kCtrlTagCB || pCaller->GetTag() == kCtrlTagEditCB) pCaller->GetUI()->ForControlInGroup("Cabasa", [](IControl &ctrl) { ctrl.Hide(false); });
          if(pCaller->GetTag()== kCtrlTagCL || pCaller->GetTag() == kCtrlTagEditCL) pCaller->GetUI()->ForControlInGroup("Clap", [](IControl &ctrl) { ctrl.Hide(false); });
          if(pCaller->GetTag()== kCtrlTagCow || pCaller->GetTag() == kCtrlTagEditCow) pCaller->GetUI()->ForControlInGroup("Cowbell", [](IControl &ctrl) { ctrl.Hide(false); });
          if(pCaller->GetTag()== kCtrlTagCY || pCaller->GetTag() == kCtrlTagEditCY) pCaller->GetUI()->ForControlInGroup("Cymbal", [](IControl &ctrl) { ctrl.Hide(false); });
          if(pCaller->GetTag()== kCtrlTagHH || pCaller->GetTag() == kCtrlTagEditHH) pCaller->GetUI()->ForControlInGroup("Hihat", [](IControl &ctrl) { ctrl.Hide(false); });
          if(pCaller->GetTag()== kCtrlTagSD1 || pCaller->GetTag() == kCtrlTagEditSD1) pCaller->GetUI()->ForControlInGroup("Snaredrum1", [](IControl &ctrl) { ctrl.Hide(false); });
          if(pCaller->GetTag()== kCtrlTagSD2 || pCaller->GetTag() == kCtrlTagEditSD2) pCaller->GetUI()->ForControlInGroup("Snaredrum2", [](IControl &ctrl) { ctrl.Hide(false); });
          if(pCaller->GetTag()== kCtrlTagTO1 || pCaller->GetTag() == kCtrlTagEditTO1) pCaller->GetUI()->ForControlInGroup("Tom1", [](IControl &ctrl) { ctrl.Hide(false); });
          if(pCaller->GetTag()== kCtrlTagTO2 || pCaller->GetTag() == kCtrlTagEditTO2) pCaller->GetUI()->ForControlInGroup("Tom2", [](IControl &ctrl) { ctrl.Hide(false); });

          pCaller->SetValueFromDelegate(1.);
          if(pCaller->GetTag()< kCtrlTagEditHH) pCaller->GetUI()->GetControlWithTag(pCaller->GetTag()+12)->SetValueFromDelegate(1.);
          else pCaller->GetUI()->GetControlWithTag(pCaller->GetTag() - 12)->SetValueFromDelegate(1.);

        }
        else
        {
          pCaller->SetValue(1.);
          pCaller->SetDirty(false);
        }
      }
    };

    x = 0; y = 0;

    bitmap = pGraphics->LoadBitmap(FN_HHONOFF, 2);
    pGraphics->AttachControl(new IBSwitchControlF(x+10, y+10, bitmap, PanelFunc), kCtrlTagHH, "main");
    bitmap = pGraphics->LoadBitmap(FN_BD1ONOFF, 2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 650, y + 448, bitmap, PanelFunc), kCtrlTagBD1, "main");
    bitmap = pGraphics->LoadBitmap(FN_BD2ONOFF, 2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 836, y + 448, bitmap, PanelFunc), kCtrlTagBD2, "main");
    bitmap = pGraphics->LoadBitmap(FN_CABASAONOFF, 2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 901, y + 10, bitmap, PanelFunc), kCtrlTagCB, "main");
    bitmap = pGraphics->LoadBitmap(FN_CBONOFF, 2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 189, y + 10, bitmap, PanelFunc), kCtrlTagCow, "main");
    bitmap = pGraphics->LoadBitmap(FN_TO1ONOFF, 2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 381, y + 10, bitmap, PanelFunc), kCtrlTagTO1, "main");
    bitmap = pGraphics->LoadBitmap(FN_TO2ONOFF, 2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 583, y + 10, bitmap, PanelFunc), kCtrlTagTO2, "main");
    bitmap = pGraphics->LoadBitmap(FN_CYONOFF, 2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 769, y + 10, bitmap, PanelFunc), kCtrlTagCY, "main");
    bitmap = pGraphics->LoadBitmap(FN_CLONOFF, 2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 901, y + 224, bitmap, PanelFunc), kCtrlTagCL, "main");
    bitmap = pGraphics->LoadBitmap(FN_SD1ONOFF, 2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 11, y + 223, bitmap, PanelFunc), kCtrlTagSD1, "main");
    bitmap = pGraphics->LoadBitmap(FN_SD2ONOFF, 2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 440, y + 448, bitmap, PanelFunc), kCtrlTagSD2, "main");
    bitmap = pGraphics->LoadBitmap(FN_BASSSYNTHONOFF, 2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 267, y + 520, bitmap, PanelFunc), kCtrlTagBasssynth, "main");

    /**************************** INSTRUMENTS FADER *************************************/
    x = 0; y = 0;

    bitmap = pGraphics->LoadBitmap(FN_MEDIUMFADER);
    pGraphics->AttachControl(new IBSliderControlMidi(x+22, x+92, 77, kParamMixerLevelHH, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(x+547, y + 21, 77, kParamMixerLevelTO2, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(x+733, y + 21, 77, kParamMixerLevelCY, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(x+964, y+91, 77, kParamMixerLevelCB, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(x+964, y+305, 77, kParamMixerLevelCL, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(x+798, y+461, 77, kParamMixerLevelBD2, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(x+612, y+461, 77, kParamMixerLevelBD1, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(x+404, y+461, 77, kParamMixerLevelSD2, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(x+345, y + 21, 77, kParamMixerLevelTO1, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 22, y+304, 77, kParamMixerLevelSD1, bitmap), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(x+153, y+21, 77, kParamMixerLevelCow, bitmap), -1, "main");

    pGraphics->AttachControl(new IBSliderControlMidi(x+22, y+459, 77, kParamBassSynthCoarse, bitmap), -1, "main");

    /**************************** INSTRUMENTS KNOBS *************************************/
    x = 0; y = 0;

    bitmap = pGraphics->LoadBitmap(FN_MEDIUMKNOBROUND, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x+21,  y+37, bitmap, kParamHihatType), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(x+70,  y+37, bitmap, kParamHihatColor), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(x+203, y+37, bitmap, kParamCowbellTune), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(x+252, y+37, bitmap, kParamCowbellDecay), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(x+394, y+37, bitmap, kParamTom1Tune), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(x+444, y+37, bitmap, kParamTom1NoiseLevel), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(x+596, y+37, bitmap, kParamTom2Tune), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(x+645, y+37, bitmap, kParamTom2NoiseLevel), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(x+782, y+37, bitmap, kParamCymbalTune), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(x+832, y+37, bitmap, kParamCymbalDecay), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(x+912, y+37, bitmap, kParamCabasaAttack), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(x+963, y+37, bitmap, kParamCabasaDecay), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(x+913, y+251, bitmap, kParamClapPeople), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(x+963, y+251, bitmap, kParamClapDecay), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(x+847, y+477, bitmap, kParamBassdrum2SynthTune), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(x+897, y+477, bitmap, kParamBassdrum2BodyImpact), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(x+662, y+477, bitmap, kParamBassdrum1SynthTune), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(x+711, y+477, bitmap, kParamBassdrum1BodyImpact), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(x+453, y+477, bitmap, kParamSnaredrum2Tune), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(x+503, y+477, bitmap, kParamSnaredrum2BodySnares), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(x+21,   y+251, bitmap, kParamSnaredrum1Tune), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(x+70,  y+251, bitmap, kParamSnaredrum1BodySnares), -1, "main");

    pGraphics->AttachControl(new IBKnobControlMidi(x+71,  y+ 457, bitmap, kParamBassSynthCutoff), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(x+120, y+ 457, bitmap, kParamBassSynthQ), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(x+171, y+ 457, bitmap, kParamBassSynthFilterMod), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(x+220, y+ 457, bitmap, kParamBassSynthAmpEnvDecay), -1, "main");

    bitmap = pGraphics->LoadBitmap(FN_BASSSYNTHHIDE);
    pGraphics->AttachControl(new IBitmapControl(x + 68, y + 506, bitmap), kCtrlTagBasssynthHide, "main");


    // MIXER ADD

    bitmap = pGraphics->LoadBitmap(FN_MIXERBACKI);
    pGraphics->AttachControl(new IBitmapControl(0, 0, bitmap, kNoParameter), -1, "add");

    x = 0; y = 0;
   
    bitmap = pGraphics->LoadBitmap(FN_MEDIUMKNOBROUND, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 67,          y + 216, bitmap, kParamMixerDelayBD1), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 67+70,       y + 216, bitmap, kParamMixerDelayBD2), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 67+2*70,     y + 216, bitmap, kParamMixerDelaySD1), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 67 + 3 *  70,y + 216, bitmap, kParamMixerDelaySD2), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 67 + 4 *  70, y + 216, bitmap, kParamMixerDelayTO1), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 67 + 5 *  70, y + 216, bitmap, kParamMixerDelayTO2), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 67 + 6 *  70, y + 216, bitmap, kParamMixerDelayHH), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 67 + 7 *  70, y + 216, bitmap, kParamMixerDelayCY), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 67 + 8 *  70, y + 216, bitmap, kParamMixerDelayCow), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 67 + 9 *  70, y + 216, bitmap, kParamMixerDelayCL), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 67 + 10 * 70, y + 216, bitmap, kParamMixerDelayCB), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 67 + 11 * 70, y + 216, bitmap, kParamMixerDelayBass), -1, "add");

    bitmap = pGraphics->LoadBitmap(FN_MEDIUMKNOBROUND, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 67, y +           259, bitmap,  kParamMixerChorusBD1), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 67 + 70, y +      259, bitmap,  kParamMixerChorusBD2), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 67 + 2 * 70, y +  259, bitmap,  kParamMixerChorusSD1), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 67 + 3 * 70, y +  259, bitmap,  kParamMixerChorusSD2), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 67 + 4 * 70, y +  259, bitmap,  kParamMixerChorusTO1), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 67 + 5 * 70, y +  259, bitmap,  kParamMixerChorusTO2), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 67 + 6 * 70, y +  259, bitmap,  kParamMixerChorusHH), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 67 + 7 * 70, y +  259, bitmap,  kParamMixerChorusCY), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 67 + 8 * 70, y +  259, bitmap,  kParamMixerChorusCow), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 67 + 9 * 70, y +  259, bitmap,  kParamMixerChorusCL), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 67 + 10 * 70, y + 259, bitmap,  kParamMixerChorusCB), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 67 + 11 * 70, y + 259, bitmap,  kParamMixerChorusBass), -1, "add");

    bitmap = pGraphics->LoadBitmap(FN_MEDIUMKNOBROUNDPAN, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 62, y + 304, bitmap,          kParamMixerPanBD1), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 62 + 70, y + 304, bitmap,     kParamMixerPanBD2), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 62 + 2 * 70, y + 304, bitmap, kParamMixerPanSD1), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 62 + 3 * 70, y + 304, bitmap, kParamMixerPanSD2), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 62 + 4 * 70, y + 304, bitmap, kParamMixerPanTO1), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 62 + 5 * 70, y + 304, bitmap, kParamMixerPanTO2), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 62 + 6 * 70, y + 304, bitmap, kParamMixerPanHH), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 62 + 7 * 70, y + 304, bitmap, kParamMixerPanCY), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 62 + 8 * 70, y + 304, bitmap, kParamMixerPanCow), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 62 + 9 * 70, y + 304, bitmap, kParamMixerPanCL), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 62 + 10 * 70, y + 304, bitmap, kParamMixerPanCB), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 62 + 11 * 70, y + 304, bitmap, kParamMixerPanBass), -1, "add");

    bitmap = pGraphics->LoadBitmap(FN_MEDIUMFADER);
    pGraphics->AttachControl(new IBSliderControlMidi(x + 67 + 0 * 70 , y + 362,  120,  kParamMixerLevelBD1, bitmap), -1, "add");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 67 + 1 * 70 , y + 362,  120, kParamMixerLevelBD2, bitmap), -1, "add");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 67 + 2 * 70 , y + 362,  120, kParamMixerLevelSD1, bitmap), -1, "add");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 67 + 3 * 70 , y + 362,  120, kParamMixerLevelSD2, bitmap ), -1, "add");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 67 + 4 * 70 , y + 362,  120, kParamMixerLevelTO1, bitmap), -1, "add");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 67 + 5 * 70 , y + 362,  120, kParamMixerLevelTO2, bitmap ), -1, "add");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 67 + 6 * 70 , y + 362,  120, kParamMixerLevelHH, bitmap ), -1, "add");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 67 + 7 * 70 , y + 362,  120, kParamMixerLevelCY, bitmap ), -1, "add");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 67 + 8 * 70 , y + 362,  120, kParamMixerLevelCow, bitmap ), -1, "add");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 67 + 9 * 70 , y + 362,  120, kParamMixerLevelCL, bitmap ), -1, "add");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 67 + 10 * 70, y + 362,  120, kParamMixerLevelCB, bitmap), -1, "add");
    pGraphics->AttachControl(new IBSliderControlMidi(x + 67 + 11 * 70, y + 362,  120, kParamMixerLevelBass, bitmap ), -1, "add");

    bitmap = pGraphics->LoadBitmap(FN_EDITBUTTON,2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 63 + 0 *  70, y + 506,  bitmap, PanelFunc), kCtrlTagEditBD1, "add");
    pGraphics->AttachControl(new IBSwitchControlF(x + 63 + 1 *  70, y + 506,  bitmap, PanelFunc), kCtrlTagEditBD2, "add");
    pGraphics->AttachControl(new IBSwitchControlF(x + 63 + 2 *  70, y + 506,  bitmap, PanelFunc), kCtrlTagEditSD1, "add");
    pGraphics->AttachControl(new IBSwitchControlF(x + 63 + 3 *  70, y + 506,  bitmap, PanelFunc), kCtrlTagEditSD2, "add");
    pGraphics->AttachControl(new IBSwitchControlF(x + 63 + 4 *  70, y + 506,  bitmap, PanelFunc), kCtrlTagEditTO1, "add");
    pGraphics->AttachControl(new IBSwitchControlF(x + 63 + 5 *  70, y + 506,  bitmap, PanelFunc), kCtrlTagEditTO2, "add");
    pGraphics->AttachControl(new IBSwitchControlF(x + 63 + 6 *  70, y + 506,  bitmap, PanelFunc), kCtrlTagEditHH, "add");
    pGraphics->AttachControl(new IBSwitchControlF(x + 63 + 7 *  70, y + 506,  bitmap, PanelFunc), kCtrlTagEditCY, "add");
    pGraphics->AttachControl(new IBSwitchControlF(x + 63 + 8 *  70, y + 506,  bitmap, PanelFunc), kCtrlTagEditCow, "add");
    pGraphics->AttachControl(new IBSwitchControlF(x + 63 + 9 *  70, y + 506,  bitmap, PanelFunc), kCtrlTagEditCL, "add");
    pGraphics->AttachControl(new IBSwitchControlF(x + 63 + 10 * 70, y + 506,  bitmap, PanelFunc), kCtrlTagEditCB, "add");
    pGraphics->AttachControl(new IBSwitchControlF(x + 63 + 11 * 70, y + 506,  bitmap, PanelFunc), kCtrlTagEditBasssynth, "add");

    bitmap = pGraphics->LoadBitmap(FN_MEDIUMKNOBROUND, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 906, y + 393, bitmap, kParamMixerDelayReturn), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 906, y + 464, bitmap, kParamMixerChorusReturn), -1, "add");

    /**************************** Effects *************************************/
    x = -4;
    y = -529;

    bitmap = pGraphics->LoadBitmap(FN_MEDIUMKNOBROUND, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 340, y + 575, bitmap, kParamEffectsFilterQ), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 340, y + 640, bitmap, kParamEffectsFilterEnvelope), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 415, y + 640, bitmap, kParamEffectsDriveTone), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 505, y + 640, bitmap, kParamEffectsChorusOffset), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 574, y + 640, bitmap, kParamEffectsChorusFeedback), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 665, y + 640, bitmap, kParamEffectsDelayDamp), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 735, y + 640, bitmap, kParamEffectsDelayFeedback), -1, "add");

    bitmap = pGraphics->LoadBitmap(FN_LARGEKNOBROUND, 128);
    pGraphics->AttachControl(new IBKnobControlMidi(x + 254, y + 619, bitmap, kParamEffectsFilterCutoff), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 403, y + 570, bitmap, kParamEffectsDriveAmount), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 494, y + 570, bitmap, kParamEffectsChorusRate), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 563, y + 570, bitmap, kParamEffectsChorusDepth), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 653, y + 570, bitmap, kParamEffectsDelayTimeL), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(x + 724, y + 570, bitmap, kParamEffectsDelayTimeR), -1, "add");

    bitmap = pGraphics->LoadBitmap(FN_FILTERBUTTON, 3);
    pGraphics->AttachControl(new IBitmapControl(x + 241, y + 576, bitmap, kParamEffectsFilterType), -1, "add");
     mappingFunc = [](double midiVal) {return midiVal * 127. / 2.; };
    pGraphics->AttachControl(new IInvisibleCaptionControlMidi(IRECT(x + 241, y + 576, x + 321, y + 594), kParamEffectsFilterType, DEFAULT_TEXT, DEFAULT_BGCOLOR, true, mappingFunc), kCtrlTagFilterType, "add");
    bitmap = pGraphics->LoadBitmap(FN_LEFTBUTTON,2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 241, y + 596, bitmap, [](IControl *ctrl) {
      if (ctrl->GetValue() == 1) {
        int val = ctrl->GetUI()->GetControlWithTag(kCtrlTagFilterType)->GetParam()->Int();
        val = (val - 1); if (val < 0) val = 2;
        double valN = ctrl->GetUI()->GetControlWithTag(kCtrlTagFilterType)->GetParam()->ToNormalized(val);
        ctrl->GetUI()->GetControlWithTag(kCtrlTagFilterType)->SetValue(valN);
        ctrl->GetUI()->GetControlWithTag(kCtrlTagFilterType)->SetDirty(true);
      }
      }), -1, "add");
    bitmap = pGraphics->LoadBitmap(FN_RIGHTBUTTON,2);
    pGraphics->AttachControl(new IBSwitchControlF(x + 301, y + 596, bitmap, [](IControl *ctrl) {
      if (ctrl->GetValue() == 1) {
        int val = ctrl->GetUI()->GetControlWithTag(kCtrlTagFilterType)->GetParam()->Int();
        val = (val + 1) % 3;
        double valN = ctrl->GetUI()->GetControlWithTag(kCtrlTagFilterType)->GetParam()->ToNormalized(val);
        ctrl->GetUI()->GetControlWithTag(kCtrlTagFilterType)->SetValue(valN);
        ctrl->GetUI()->GetControlWithTag(kCtrlTagFilterType)->SetDirty(true);
      }
      }), -1, "add");

    bitmap = pGraphics->LoadBitmap(FN_MUTEBUTTON, 2);
    mappingFunc = [](double midiVal) {return 127. - midiVal * 127.; };
    pGraphics->AttachControl(new IBSwitchControlMidi(x + 350, y + 697, bitmap, kParamEffectsFilterMute, mappingFunc), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(x + 441, y + 697, bitmap, kParamEffectsDriveMute, mappingFunc), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(x + 600, y + 697, bitmap, kParamEffectsChorusMute, mappingFunc), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(x + 760, y + 697, bitmap, kParamEffectsDelayMute, mappingFunc), -1, "add");

    x = 0; y = 0;

    /********************************** MAIN ADD *************************************/

    auto windowFunc = [](IControl* pCaller) {
      pCaller->SetValue(1.);
      if (pCaller->GetUI()) {

        if (pCaller->GetTag() != kCtrlTagMain) pCaller->GetUI()->GetControlWithTag(kCtrlTagMain)->SetValueFromUserInput(0);
        if (pCaller->GetTag() != kCtrlTagAdd) pCaller->GetUI()->GetControlWithTag(kCtrlTagAdd)->SetValueFromUserInput(0);

        pCaller->GetUI()->ForControlInGroup("main", [&](IControl& control) {if (pCaller->GetTag() == kCtrlTagMain) control.Hide(false); else control.Hide(true); });
        pCaller->GetUI()->ForControlInGroup("add", [&](IControl& control) {if (pCaller->GetTag() == kCtrlTagAdd) control.Hide(false); else control.Hide(true); });
      }
    };

    bitmap = pGraphics->LoadBitmap(FN_MAIN, 2);
    IBSwitchControlFunc *mainCtrl = new IBSwitchControlFunc(892, 655, bitmap, windowFunc, kNoParameter);
    pGraphics->AttachControl(mainCtrl, kCtrlTagMain);
    mainCtrl->SetValue(1);
    bitmap = pGraphics->LoadBitmap(FN_ADD, 2);
    IBSwitchControlFunc *addCtrl = new IBSwitchControlFunc(892+52, 655, bitmap, windowFunc, kNoParameter);
    pGraphics->AttachControl(addCtrl, kCtrlTagAdd);

    bitmap = pGraphics->LoadBitmap(FN_MIDIMONBACK);
    IControl* midiCtrlBack = new IBitmapControl(HS_W, 0, bitmap, kNoParameter);
    pGraphics->AttachControl(midiCtrlBack, kCtrlTagMidiBack, "midiMonitor");
    
    // ICaptions Main

    float cw = 22; float ch = 13;
   
    bitmap = pGraphics->LoadBitmap(FN_MIDIACTIVE, 2);
    pGraphics->AttachControl(new IBitmapControl(892 + 52, 698, bitmap, kNoParameter), kCtrlMidiActive, "");
    pGraphics->GetControlWithTag(kCtrlMidiActive)->SetActionFunction([&](IControl *ctrl)
      {
        if (ctrl->GetValue() == 1) mMidiActive = true;
        else mMidiActive = false;
        if (GetUI()) for (auto c = 0; c < GetUI()->NControls(); c++) GetUI()->GetControl(c)->SetWantsMidi(mMidiActive);      
      }
    );

    // Light on/off
    auto LightOnOff = [&](IControl* pCaller) { mLightOnOff = pCaller->GetValue(); };
    bitmap = pGraphics->LoadBitmap(FN_FLASHESBUTTON, 2);
    IBSwitchControl *LightOnfOffCtrl = new IBSwitchControl(892, 633, bitmap);
    pGraphics->AttachControl(LightOnfOffCtrl);
    LightOnfOffCtrl->SetActionFunction(LightOnOff);
    LightOnfOffCtrl->SetValue(1);
 

    // MIXER UI
#include "../MPA Code/MixerUI.h" 

    // KEYBOARD UI
#include "../MPA Code/KeyboardUI.h"

// RESIZE CONTROLS ////////////////////////////////////////////////////////////////////////////////////////////////

#include "../MPA Code/Resize.h"



    bitmap = pGraphics->LoadBitmap(FN_MIDIMONITOR, 2);
    IBSwitchControl *presetUI = new IBSwitchControl(892, 698, bitmap, kNoParameter);
    pGraphics->AttachControl(presetUI, kCtrlTagMidiMonHide, "");
    presetUI->SetActionFunction(resizeFunc);

    bitmap = pGraphics->LoadBitmap(FN_MIXER, 2); // MIXER UI
    IBSwitchControl *mixerUICtrl = new IBSwitchControl(892+52, 676, bitmap, kNoParameter);
    pGraphics->AttachControl(mixerUICtrl, kCtrlTagMixerHide, "");
    mixerUICtrl->SetActionFunction(resizeFunc);

    bitmap = pGraphics->LoadBitmap(FN_KEYB, 2);
    IBSwitchControl *keybCtrl = new IBSwitchControl(892, 676, bitmap, kNoParameter);
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
    IBButtonControl* clearCtrl = new IBButtonControl(HS_W + 64, 469+50+178, bitmap, [&](IControl*) {mMidiLogger->Clear(); });
    pGraphics->AttachControl(clearCtrl, kCtrlTagClear, "midiMonitor");

    mMidiLogger = new MidiMonitor(IRECT(HS_W + 14, 379+50 + 178, HS_W + 196, 454+50 + 178), "", "", IText(12, COLOR_BLACK, "Calibri", EAlign::Near), COLOR_WHITE);
    pGraphics->AttachControl(mMidiLogger, kCtrlTagMidiLogger, "midiMonitor");

    bitmap = pGraphics->LoadBitmap(FN_SLIDER, 1);
    pGraphics->AttachControl(new IBSliderControlScroll(HS_W + 210, 378+50 + 178, 75, -1, bitmap), kCtrlSliderMidiMon1);
    pGraphics->GetControlWithTag(kCtrlSliderMidiMon1)->SetActionFunction([&](IControl* ctrl) {mMidiLogger->setEntrypointerOffset(1. - ctrl->GetValue()); });
    pGraphics->GetControlWithTag(kCtrlSliderMidiMon1)->SetValue(1.);

    bitmap = pGraphics->LoadBitmap(FN_RECALL, 1);
    IBButtonControl* RecallCtrl = new IBButtonControl(HS_W + 6, 321+50+178, bitmap, [&](IControl*) {});
    RecallCtrl->SetActionFunction([&](IControl* ctrl) {
      mPresetList->mActiveRow = mPresetList->mSelectedRow;
      GetUI()->GetControlWithTag(kCtrlProgram)->SetValue((double)mPresetList->mActiveRow / (mPresetList->maxLogSamples - 1.));
      GetUI()->GetControlWithTag(kCtrlProgram)->SetDirty();
      });
    pGraphics->AttachControl(RecallCtrl, -1, "midiMonitor");

        bitmap = pGraphics->LoadBitmap(FN_OVERWRITE, 1);
    IBButtonControl* overwriteCtrl = new IBButtonControl(HS_W+85, 321+50 + 178, bitmap, [&](IControl* pCaller)
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
    IBButtonControl* resetCtrl = new IBButtonControl(HS_W + 164, 321+50 + 178, bitmap,

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

    mPresetList = new PresetList(IRECT(HS_W + 14, 97, HS_W + 196, 310+50 + 178), 35, "", "", IText(12, COLOR_BLACK, "Calibri", EAlign::Near), COLOR_WHITE);
    pGraphics->AttachControl(mPresetList, kCtrlTagPresetList, "presetList");

    for (int k = 0; k < 50; k++) {
		  mPresetList->addItem(presetname[k]);
	  }

    bitmap = pGraphics->LoadBitmap(FN_SLIDER, 1);
    pGraphics->AttachControl(new IBSliderControlScroll(HS_W + 210, 95, 214+50 + 178, -1, bitmap), kCtrlSliderPresetList);
    pGraphics->GetControlWithTag(kCtrlSliderPresetList)->SetActionFunction([&](IControl* ctrl) {mPresetList->setFirstRowToShowNormalized(ctrl->GetValue()); });
    pGraphics->GetControlWithTag(kCtrlSliderPresetList)->SetValue(1.);

    ///////////////////////////////////////// CAPTION USER/FACTORY /////////////////////////////////////////////////////////////

   ICaptionControl* userFactory = new ICaptionControl(IRECT(HS_W+10,39,HS_W+115, 58), kParamUserFactory, IText(12,COLOR_WHITE,"Calibrib"), COLOR_BLACK, true);
    userFactory->SetActionFunction([&](IControl* ctrl) {

      if (ctrl->GetValue() == 0) {
        activeRowUser = mPresetList->mActiveRow; // save
        mPresetList->Clear();
        for (int k = 0; k < 50; k++) {
			mPresetList->addItem(presetname[k]);
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

    IBButtonControl* saveButton = new IBButtonControl(HS_W + 8, 6, bitmap, [&](IControl*) {

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
      GetUI()->GetControlWithTag(kCtrlTagBD1)->SetValue(1.);
      GetUI()->GetControlWithTag(kCtrlTagBD1)->SetDirty(true);
      GetUI()->GetControlWithTag(kCtrlTagBD1+12)->SetValue(1.);
      GetUI()->GetControlWithTag(kCtrlTagBD1+12)->SetDirty(true);

      GetUI()->GetControlWithTag(kCtrlBlitzBD1  )->Hide(true);
      GetUI()->GetControlWithTag(kCtrlBlitzBD2  )->Hide(true);
      GetUI()->GetControlWithTag(kCtrlBlitzHH   )->Hide(true);
      GetUI()->GetControlWithTag(kCtrlBlitzCB   )->Hide(true);
      GetUI()->GetControlWithTag(kCtrlBlitzCOW  )->Hide(true);
      GetUI()->GetControlWithTag(kCtrlBlitzCY   )->Hide(true);
      GetUI()->GetControlWithTag(kCtrlBlitzTO1  )->Hide(true);
      GetUI()->GetControlWithTag(kCtrlBlitzTO2  )->Hide(true);
      GetUI()->GetControlWithTag(kCtrlBlitzCL   )->Hide(true);
      GetUI()->GetControlWithTag(kCtrlBlitzSD1  )->Hide(true);
      GetUI()->GetControlWithTag(kCtrlBlitzSD2  )->Hide(true);
    }
  };
  
#endif
}

#if IPLUG_DSP
void DrumsNBass::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
  const int nChans = NOutChansConnected();
  
  for (auto s = 0; s < nFrames; s++) {
    for (auto c = 0; c < nChans; c++) {
      outputs[c][s] = 0.;
    }
  }
}

void DrumsNBass::OnIdle()
{
  mMidiLoggerSender.TransmitData(*this); 
}

void DrumsNBass::OnReset()
{
}

void DrumsNBass ::OnUIClose() {
  if(GetParam(kParamUserFactory)->Value() == 0) activeRowFactory = mPresetList->mActiveRow;
  if (GetParam(kParamUserFactory)->Value() == 1) activeRowUser = mPresetList->mActiveRow;

  for (auto r = 0; r < mMidiLogger->maxLogSamples; r++) {
    for (auto c = 0; c < mMidiLogger->numColumns; c++) {
      mStrBufSave[r][c] = mMidiLogger->mStrBuf[r][c];
    }
  }
  mEntryPtrSave = mMidiLogger->mEntryPointer;
}

void DrumsNBass::OnUIOpen() {

  SendCurrentParamValuesFromDelegate();
  if (GetParam(kParamUserFactory)->Value() == 0) { //Factory
    mPresetList->Clear();
    for (int k = 0; k < 50; k++) {
      mPresetList->addItem(presetname[k]);
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
void DrumsNBass::ProcessMidiMsg(const IMidiMsg& msg)
{
  TRACE;

  // Blitze

  if (GetUI()) {
    int status = msg.StatusMsg();
    int note = msg.mData1;
    int instr = note - 60;
    if (instr == 10) instr = 6;
    if (instr == 11) instr = 10;

    if (status == IMidiMsg::kNoteOn)
    {
      if (instr >= 0 && instr <= 10) {
        if (instr != 7) SendControlValueFromDelegate(kCtrlTagBD1Inst + instr, 1.);
        if (instr == 5) SendControlValueFromDelegate(kCtrlTagTO1Inst, 0.25);
        if (instr == 7) SendControlValueFromDelegate(kCtrlTagTO1Inst, 0.5);
        if (mLightOnOff == 1) {
          SendControlValueFromDelegate(kCtrlGlowBD1 + instr, 1.);
          SendControlValueFromDelegate(kCtrlBlitzBD1 + instr, mBlitzCnt1 / 5.);
          if (GetUI()->GetControlWithTag(kCtrlBlitzBD1 + instr)) GetUI()->GetControlWithTag(kCtrlBlitzBD1 + instr)->Hide(false);
          mBlitzCnt1++;
          if (mBlitzCnt1 >= 6.) mBlitzCnt1 = 0;
        }
      }
      else {
        if(GetUI()->GetControlWithTag(kCtrlTagBasssynthHide)) GetUI()->GetControlWithTag(kCtrlTagBasssynthHide)->Hide(true);
      }
    }
    if (status == IMidiMsg::kNoteOff)
    {
      if (instr >= 0 && instr <= 10) {
        if (instr != 7) SendControlValueFromDelegate(kCtrlTagBD1Inst + instr, 0.);
        if (instr == 5) SendControlValueFromDelegate(kCtrlTagTO1Inst, 0.); // Tom 1
        if (instr == 7) SendControlValueFromDelegate(kCtrlTagTO1Inst, 0.); // Tom 2
        SendControlValueFromDelegate(kCtrlGlowBD1 + instr, 0.);
        if(GetUI()->GetControlWithTag(kCtrlBlitzBD1 + instr)) GetUI()->GetControlWithTag(kCtrlBlitzBD1 + instr)->Hide(true);
      }
      else {
        if (GetUI()->GetControlWithTag(kCtrlTagBasssynthHide)) GetUI()->GetControlWithTag(kCtrlTagBasssynthHide)->Hide(false);
      }
    }
  }

  

#include "../MPA Code/ProcessMidi.h"

 
}

void DrumsNBass::OnParamChange(int paramIdx)
{
  IMidiMsg msg;

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
      msg.mData2 = GetParam(paramIdx)->Value();
      break;
    case kParamMidiClockBpm:
      msg.mData2 = GetParam(paramIdx)->Value()-72;
      break;
    }

    switch (paramIdx) {
     case kParamBassdrum1Waveform:
     case kParamBassdrum2Waveform:
     case kParamSnaredrum1Waveform:
     case kParamSnaredrum2Waveform:
     case kParamCowbellWaveform:
     case kParamCymbalWaveform:
     case kParamTom1Waveform:
     case kParamTom2Waveform:
     case kParamEffectsFilterType:
       msg.mData2 = GetParam(paramIdx)->Value();
       break;
     case kParamBassdrum1BodyPunchSnapNormal:
     case kParamBassdrum1TransientPunchSnapNormal:
     case kParamBassdrum2BodyPunchSnapNormal:
     case kParamBassdrum2TransientPunchSnapNormal:
       if ((int)(GetParam(paramIdx)->GetNormalized() * 127.0) == 63) msg.mData2 = 64;
       break;
     case kParamEffectsFilterMute:
     case kParamEffectsDriveMute:
     case kParamEffectsChorusMute:
     case kParamEffectsDelayMute:
       msg.mData2 = 127.-GetParam(paramIdx)->Value();
       break;
    }

    msg.mOffset = -2; // tell ProcessMidiMsg that msg comes from UI
  }

#include "../MPA Code/OnParamChange.h"

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
      msg.mData2 = PLUGIN_ID;
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
      msg.mData2 = PLUGIN_ID;
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
  
    // schalte midi inaktiv, wird in processmidi wieder aktiviert, wenn DP MIDI zurückgibt
    if (GetUI() && GetUI()->GetControlWithTag(kCtrlMidiActive)) GetUI()->GetControlWithTag(kCtrlMidiActive)->SetValueFromUserInput(0.);

    // msg.offset = -3 bedeutet dass es immer rausgeht auch wenn midi inaktiv
    if (GetParam(kParamUserFactory)->Value() == 0) { // Factory
      msg.Clear();
      msg.mStatus = mChannel | (IMidiMsg::kControlChange << 4);
      msg.mData1 = 0x00;
      msg.mData2 = PLUGIN_ID;
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
      msg.mData2 = PLUGIN_ID;
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

    break;


      
    default:
      break;
  }
}

bool DrumsNBass::SerializeState(IByteChunk& chunk) const {

  TRACE;

  return SerializeParams(chunk);
}

// this over-ridden method is called when the host is trying to load the plug-in state and you need to unpack the data into your algorithm
// HIER KÖNNEN KEINE CONTROLS GEUPDATED WERDEN; DA MGRAPHICS NOCH NICHT EXISTIERT!!!!
int DrumsNBass::UnserializeState(const IByteChunk& chunk, int startPos) {

  TRACE;

  return UnserializeParams(chunk, startPos);
}
#endif
