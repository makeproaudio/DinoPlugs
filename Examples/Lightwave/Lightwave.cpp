#include "Lightwave.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"
#include "json.hpp"
#include <fstream>

Lightwave::Lightwave(IPlugInstanceInfo instanceInfo)
: IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo)
{

  presetname[0 ].Set("00: Tarkus");
  presetname[1].Set("01: Fat Bastard");
  presetname[2].Set("02: Eary Night");
  presetname[3].Set("03: String Machine");
  presetname[4].Set("04: Synth Brass");
  presetname[5].Set("05: Bells And Birds");
  presetname[6].Set("06: Water Bass");
  presetname[7].Set("07: Soft Bass");
  presetname[8].Set("08: Liquid Steps");
  presetname[9].Set("09: ResoFat");
  presetname[10].Set("10: Subby Dubby");
  presetname[11].Set("11: To Be");
  presetname[12].Set("12: Sexy Boy");
  presetname[13].Set("13: Down Low");
  presetname[14].Set("14: Digital Age");
  presetname[15].Set("15: Bass Wood Winds");
  presetname[16].Set("16: Beyond Forever");
  presetname[17].Set("17: The Cave");
  presetname[18].Set("18: RadioPhonic");
  presetname[19].Set("19: Fresh Lead");
  presetname[20].Set("20: Funny Rascal");
  presetname[21].Set("21: X Files");
  presetname[22].Set("22: Phasing Lead");
  presetname[23].Set("23: Broke");
  presetname[24].Set("24: Father Fungus");
  presetname[25].Set("25: Open Cycle");
  presetname[26].Set("26: Egg Lead");
  presetname[27].Set("27: Fusion Lead");
  presetname[28].Set("28: Prodigy");
  presetname[29].Set("29: Shiny Plato");
  presetname[30].Set("30: Clown Lead");
  presetname[31].Set("31: Zamphir");
  presetname[32].Set("32: Fruit Fly Lead");
  presetname[33].Set("33: Rubber Ducky");
  presetname[34].Set("34: Vintage 5ths");
  presetname[35].Set("35: Synced FM");
  presetname[36].Set("36: Sine Lead");
  presetname[37].Set("37: A.I.");
  presetname[38].Set("38: Lucky Man");
  presetname[39].Set("39: Clicker");
  presetname[40].Set("40: Pancho");
  presetname[41].Set("41: Overtone Pinner");
  presetname[42].Set("42: Warm Pad");
  presetname[43].Set("43: Chease Cake");
  presetname[44].Set("44: Silver Drops");
  presetname[45].Set("45: Mandoline");
  presetname[46].Set("46: Fixed Formant");
  presetname[47].Set("47: Mr. Smart");
  presetname[48].Set("48: Agties");
  presetname[49].Set("49: Hollow world");

   // MIXER UI
  #include "../MPA Code/GlobalParamInit.h" 

  GetParam(kParamOsc1Waveform)->InitEnum("Osc 1 Waveform", 0, 128, "", 0, "", "noise", "sine wave", "sawtooth", "square", "vectron typical 1", "vectron typical 2", "cream wave 1", "fifthback", "vectron typical 3", "trash 1", "trash 2", "American twang", "sandangle", "cheeporg", "highly pulsive", "restrained pulse", "smooth reed", "JayBase", "options open", "upscale", "hammertone", "Anywave 1", "Anywave 2", "Anywave 3", "uppercrust", "acchord", "nondescript", "tiney thing", "langpipe", "deepring", "rhodeToNowhere", "thikring", "whirlitza", "no occident", "pipe up", "alreedy there", "generic", "pop smear 1", "poem freet", "clara nette", "seriously now", "jaz pic", "deep sax", "mareemba", "say what", "pro fundo", "mund harp", "take it down", "plucky", "under the neck", "sin flute", "oboy", "got a run", "silophone", "ach du liebe", "namelesswave", "lead off", "no ground", "digitine", "red whine", "hand me pliers", "wearing thin", "bridge", "reed directions", "ol'fateful", "windy city", "far feeza", "knew orleans", "cruis'n attitude", "fresh", "VocForm01", "VocForm02", "VocForm03", "VocForm04", "VocForm05", "VocForm06", "VocForm07", "VocForm08", "VocForm09", "VocForm10", "VocForm11", "VocForm12", "only a test", "spinBottle", "blown cap", "bassish", "kitschorg", "come 2 harm", "huzz", "under the rug", "gryndyr", "to the point", "mars lander", "String perc", "Annoys Dog", "Short perc", "ModForm1 A", "ModForm1 AE", "ModForm1 E", "ModForm1 I", "ModForm1 EE", "ModForm1 OO", "ModForm1 O", "ModForm1 OU", "Partials 1-4", "Partials 5-8", "Partials 8-12", "Partial 1+2", "Partial 1+3", "Partial 1+4", "Partial 1+5", "Partial 1+6", "Partial 1+7", "Partial 1+8", "Partial 1+2+4", "Partial 1+3+5", "Partial 1+2+4+6", "Partial 1+3+5+7", "20p FM 1:1", "20p FM 1:2", "20p FM 1:3", "20p FM 1:4", "20p FM 1:5", "20p FM 1:6", "20p FM 1:7", "DownSampSync1", "DownSampSync2", "Reading Room");
  GetParam(kParamOsc1Coarse)->InitInt("Osc 1 Coarse", 0, -48, 48);
  GetParam(kParamOsc1Fine)->InitInt("Osc 1 Fine", 0, -99, 99);
  GetParam(kParamOsc1Grunge)->InitInt("Osc 1 Grunge", 0, 0, 127);
  GetParam(kParamOsc1PitchModSrc)->InitEnum("Osc 1 Pitch Mod Src", 0, 17, "", 0, "", "OFF", "LFO1", "LFO2", "LFO1+2", "LFO1*2", "LFO1*MW", "LFO1*AT", "LFO2*MW", "LFO2*AT", "Filter Env", "Amp Env", "Free Env +", "Free Env -", "Key follow", "Velocity", "AfterTouch", "Mod wheel");
  GetParam(kParamOsc1PitchModAmt)->InitInt("Osc 1 Pitch Mod Amt", 0, -63, 63);

  GetParam(kParamOsc2Waveform)->InitEnum("Osc 2 Waveform", 0, 128, "", 0, "", "noise", "sine wave", "sawtooth", "square", "vectron typical 1", "vectron typical 2", "cream wave 1", "fifthback", "vectron typical 3", "trash 1", "trash 2", "American twang", "sandangle", "cheeporg", "highly pulsive", "restrained pulse", "smooth reed", "JayBase", "options open", "upscale", "hammertone", "Anywave 1", "Anywave 2", "Anywave 3", "uppercrust", "acchord", "nondescript", "tiney thing", "langpipe", "deepring", "rhodeToNowhere", "thikring", "whirlitza", "no occident", "pipe up", "alreedy there", "generic", "pop smear 1", "poem freet", "clara nette", "seriously now", "jaz pic", "deep sax", "mareemba", "say what", "pro fundo", "mund harp", "take it down", "plucky", "under the neck", "sin flute", "oboy", "got a run", "silophone", "ach du liebe", "namelesswave", "lead off", "no ground", "digitine", "red whine", "hand me pliers", "wearing thin", "bridge", "reed directions", "ol'fateful", "windy city", "far feeza", "knew orleans", "cruis'n attitude", "fresh", "VocForm01", "VocForm02", "VocForm03", "VocForm04", "VocForm05", "VocForm06", "VocForm07", "VocForm08", "VocForm09", "VocForm10", "VocForm11", "VocForm12", "only a test", "spinBottle", "blown cap", "bassish", "kitschorg", "come 2 harm", "huzz", "under the rug", "gryndyr", "to the point", "mars lander", "String perc", "Annoys Dog", "Short perc", "ModForm1 A", "ModForm1 AE", "ModForm1 E", "ModForm1 I", "ModForm1 EE", "ModForm1 OO", "ModForm1 O", "ModForm1 OU", "Partials 1-4", "Partials 5-8", "Partials 8-12", "Partial 1+2", "Partial 1+3", "Partial 1+4", "Partial 1+5", "Partial 1+6", "Partial 1+7", "Partial 1+8", "Partial 1+2+4", "Partial 1+3+5", "Partial 1+2+4+6", "Partial 1+3+5+7", "20p FM 1:1", "20p FM 1:2", "20p FM 1:3", "20p FM 1:4", "20p FM 1:5", "20p FM 1:6", "20p FM 1:7", "DownSampSync1", "DownSampSync2", "Reading Room");
  GetParam(kParamOsc2Coarse)->InitInt("Osc 2 Coarse", 0, -48, 48);
  GetParam(kParamOsc2Fine)->InitInt("Osc 2 Fine", 0, -99, 99);
  GetParam(kParamOsc2Grunge)->InitInt("Osc 2 Grunge", 0, 0, 127);
  GetParam(kParamOsc2PitchModSrc)->InitEnum("Osc 2 Pitch Mod Src", 0, 17, "", 0, "", "OFF", "LFO1", "LFO2", "LFO1+2", "LFO1*2", "LFO1*MW", "LFO1*AT", "LFO2*MW", "LFO2*AT", "Filter Env", "Amp Env", "Free Env +", "Free Env -", "Key follow", "Velocity", "AfterTouch", "Mod wheel");
  GetParam(kParamOsc2PitchModAmt)->InitInt("Osc 2 Pitch Mod Amt", 0, -63, 63);

  GetParam(kParamMixOsc1)->InitInt("Osc 1 Amp", 63, 0, 127);
  GetParam(kParamMixOsc1AmpModSrc)->InitEnum("Osc 1 Amp Mod Src", 0, 17, "", 0, "", "OFF", "LFO1", "LFO2", "LFO1+2", "LFO1*2", "LFO1*MW", "LFO1*AT", "LFO2*MW", "LFO2*AT", "Filter Env", "Amp Env", "Free Env +", "Free Env -", "Key follow", "Velocity", "AfterTouch", "Mod wheel");
  GetParam(kParamMixOsc1AmpModAmt)->InitInt("Osc 1 Amp Mod Amt", 0, -63, 63);
  GetParam(kParamMixOsc1Balance)->InitInt("Osc 1 Balance", 0, -63, 63);
  GetParam(kParamMixOsc1BalanceModSrc)->InitEnum("Osc 1 Balance Mod Src", 0, 17, "", 0, "", "OFF", "LFO1", "LFO2", "LFO1+2", "LFO1*2", "LFO1*MW", "LFO1*AT", "LFO2*MW", "LFO2*AT", "Filter Env", "Amp Env", "Free Env +", "Free Env -", "Key follow", "Velocity", "AfterTouch", "Mod wheel");
  GetParam(kParamMixOsc1BalanceModAmt)->InitInt("Osc 1 Balance Mod Amt", 0, -63, 63);
  GetParam(kParamMixOsc2)->InitInt("Osc 2 Amp", 63, 0, 127);
  GetParam(kParamMixOsc2AmpModSrc)->InitEnum("Osc 2 Amp Mod Src", 0, 17, "", 0, "", "OFF", "LFO1", "LFO2", "LFO1+2", "LFO1*2", "LFO1*MW", "LFO1*AT", "LFO2*MW", "LFO2*AT", "Filter Env", "Amp Env", "Free Env +", "Free Env -", "Key follow", "Velocity", "AfterTouch", "Mod wheel");
  GetParam(kParamMixOsc2AmpModAmt)->InitInt("Osc 2 Amp Mod Amt", 0, -63, 63);
  GetParam(kParamMixOsc2Balance)->InitInt("Osc 2 Balance", 0, -63, 63);
  GetParam(kParamMixOsc2BalanceModSrc)->InitEnum("Osc 2 Balance Mod Src", 0, 17, "", 0, "", "OFF", "LFO1", "LFO2", "LFO1+2", "LFO1*2", "LFO1*MW", "LFO1*AT", "LFO2*MW", "LFO2*AT", "Filter Env", "Amp Env", "Free Env +", "Free Env -", "Key follow", "Velocity", "AfterTouch", "Mod wheel");
  GetParam(kParamMixOsc2BalanceModAmt)->InitInt("Osc 2 Balance Mod Amt", 0, -63, 63);
  GetParam(kParamMixGain)->InitInt("Mix Gain", 0, 0, 127);

  GetParam(kParamVcf1Cf)->InitInt("Vcf 1 Cutoff", 0, 0, 127);
  GetParam(kParamVcf1Res)->InitInt("Vcf 1 Res", 0, 0, 127);
  GetParam(kParamVcf1keyf)->InitInt("Vcf 1 Keyf", 0, -200, 200);
  GetParam(kParamVcf1Env)->InitInt("Vcf 1 Env", 0, -63, 63);
  GetParam(kParamVcf1Type)->InitEnum("Vcf 1 Type", 0, 4, "", 0, "", "LPF", "HPF", "BPF", "THRU");
  GetParam(kParamVcf1ModCfAmt)->InitInt("Vcf 1 Cf Mod Amt", 0, -63, 63);
  GetParam(kParamVcf1ModResAmt)->InitInt("Vcf 1 Res Mod Amt", 0, -63, 63);
  GetParam(kParamVcf1ModCfSrc)->InitEnum("Vcf 1 Cf Mod Src", 0, 17, "", 0, "", "OFF", "LFO1", "LFO2", "LFO1+2", "LFO1*2", "LFO1*MW", "LFO1*AT", "LFO2*MW", "LFO2*AT", "Filter Env", "Amp Env", "Free Env +", "Free Env -", "Key follow", "Velocity", "AfterTouch", "Mod wheel");
  GetParam(kParamVcf1ModResSrc)->InitEnum("Vcf 1 Res Mod Src", 0, 17, "", 0, "", "OFF", "LFO1", "LFO2", "LFO1+2", "LFO1*2", "LFO1*MW", "LFO1*AT", "LFO2*MW", "LFO2*AT", "Filter Env", "Amp Env", "Free Env +", "Free Env -", "Key follow", "Velocity", "AfterTouch", "Mod wheel");

  GetParam(kParamVcf2Cf)->InitInt("Vcf 2 Cutoff", 0, 0, 127);
  GetParam(kParamVcf2Res)->InitInt("Vcf 2 Res", 0, 0, 127);
  GetParam(kParamVcf2keyf)->InitInt("Vcf 2 Keyf", 0, -200, 200);
  GetParam(kParamVcf2Env)->InitInt("Vcf 2 Env", 0, -63, 63);
  GetParam(kParamVcf2Type)->InitEnum("Vcf 2 Type", 0, 4, "", 0, "", "LPF", "HPF", "BPF", "THRU");
  GetParam(kParamVcf2ModCfAmt)->InitInt("Vcf 2 Cf Mod Amt", 0, -63, 63);
  GetParam(kParamVcf2ModResAmt)->InitInt("Vcf 2 Res Mod Amt", 0, -63, 63);
  GetParam(kParamVcf2ModCfSrc)->InitEnum("Vcf 2 Cf Mod Src", 0, 17, "", 0, "", "OFF", "LFO1", "LFO2", "LFO1+2", "LFO1*2", "LFO1*MW", "LFO1*AT", "LFO2*MW", "LFO2*AT", "Filter Env", "Amp Env", "Free Env +", "Free Env -", "Key follow", "Velocity", "AfterTouch", "Mod wheel");
  GetParam(kParamVcf2ModResSrc)->InitEnum("Vcf 2 Res Mod Src", 0, 17, "", 0, "", "OFF", "LFO1", "LFO2", "LFO1+2", "LFO1*2", "LFO1*MW", "LFO1*AT", "LFO2*MW", "LFO2*AT", "Filter Env", "Amp Env", "Free Env +", "Free Env -", "Key follow", "Velocity", "AfterTouch", "Mod wheel");

  GetParam(kParamVcfSerPar)->InitEnum("Vcf Serial/Parallel", 0, 2, "", 0, "", "Serial", "Parallel");
  GetParam(kParamVcfLink)->InitEnum("Vcf Link", 0, 2, "", 0, "", "On", "Off");
  GetParam(kParamVcfCutoffModSrc)->InitEnum("Vcf Cf Mod Src", 0, 17, "", 0, "", "OFF", "LFO1", "LFO2", "LFO1+2", "LFO1*2", "LFO1*MW", "LFO1*AT", "LFO2*MW", "LFO2*AT", "Filter Env", "Amp Env", "Free Env +", "Free Env -", "Key follow", "Velocity", "AfterTouch", "Mod wheel");
  GetParam(kParamVcfCutoffModAmt)->InitInt("Vcf Cf Mod Amt", 0, -63, 63);
  GetParam(kParamVcfResModSrc)->InitEnum("Osc 2 Pitch Mod Src", 0, 17, "", 0, "", "OFF", "LFO1", "LFO2", "LFO1+2", "LFO1*2", "LFO1*MW", "LFO1*AT", "LFO2*MW", "LFO2*AT", "Filter Env", "Amp Env", "Free Env +", "Free Env -", "Key follow", "Velocity", "AfterTouch", "Mod wheel");
  GetParam(kParamVcfResModAmt)->InitInt("Vcf Res Mod Amt", 0, -63, 63);
  GetParam(kParamVcfEnvTKf)->InitInt("Vcf Env Keyf", 0, -200, 200);
  GetParam(kParamVcfEnvTVel)->InitInt("Vcf Env TVel", 0, -200, 200);
  GetParam(kParamVcfEnvLVel)->InitInt("Vcf Env LVel", 0, 0, 127);
  GetParam(kParamVcfEnvA)->InitInt("Vcf Env Attack", 0, 0, 127);
  GetParam(kParamVcfEnvD)->InitInt("Vcf Env Decay", 0, 0, 127);
  GetParam(kParamVcfEnvS)->InitInt("Vcf Env Sustain", 0, 0, 127);
  GetParam(kParamVcfEnvR)->InitInt("Vcf Env Release", 0, 0, 127);
  GetParam(kParamAmpVol)->InitInt("Amp Vol", 0, 0, 127);
  GetParam(kParamAmpPan)->InitInt("Amp Pan", 0, -63, 63);
  GetParam(kParamAmpPanModSrc)->InitEnum("Amp Pan Mod Src", 0, 17, "", 0, "", "OFF", "LFO1", "LFO2", "LFO1+2", "LFO1*2", "LFO1*MW", "LFO1*AT", "LFO2*MW", "LFO2*AT", "Filter Env", "Amp Env", "Free Env +", "Free Env -", "Key follow", "Velocity", "AfterTouch", "Mod wheel");
  GetParam(kParamAmpPanModAmt)->InitInt("Amp Pan Mod Amt", 0, -63, 63);
  GetParam(kParamAmpEnvTKf)->InitInt("Amp Env Tkf", 0, -200, 200);
  GetParam(kParamAmpEnvTVel)->InitInt("Amp Env TVel", 0, -200, 200);
  GetParam(kParamAmpEnvLVel)->InitInt("Amp Env LVel", 0, -0, 127);
  GetParam(kParamAmpEnvA)->InitInt("Vcf Env Attack", 0, 0, 127);
  GetParam(kParamAmpEnvD)->InitInt("Vcf Env Decay", 0, 0, 127);
  GetParam(kParamAmpEnvS)->InitInt("Vcf Env Sustain", 0, 0, 127);
  GetParam(kParamAmpEnvR)->InitInt("Vcf Env Release", 0, 0, 127);
 
 /* paramToCC[kParamMasterTune                     ]=21;     
  paramToCC[kParamGlide                          ]=5;
  paramToCC[kParamModMix                         ]=58;
  paramToCC[kParamOsc2Tune                       ]=72;
  paramToCC[kParamOsc3Tune                       ]=85;
  paramToCC[kParamOsc1Volume                     ]=25;
  paramToCC[kParamOsc2Volume                     ]=26;
  paramToCC[kParamOsc3Volume                     ]=27;
  paramToCC[kParamFeedbackLevel                  ]=36;
  paramToCC[kParamNoiseVolume                    ]=33;
  paramToCC[kParamFilterCutoff                   ]=74;
  paramToCC[kParamFilterEmphasis                 ]=71;
  paramToCC[kParamFilterContour                  ]=73;
  paramToCC[kParamFilterAttack                   ]=17;
  paramToCC[kParamFilterDecay                    ]=18;
  paramToCC[kParamFilterSustain                  ]=19;
  paramToCC[kParamVcaAttack                      ]=13;
  paramToCC[kParamVcaDecay                       ]=14;
  paramToCC[kParamVcaSustain                     ]=15;
  paramToCC[kParamVolume                         ]=11;
  paramToCC[kParamVelocity                       ]=84;
  paramToCC[kParamOutputVelocity                 ]=81;
  paramToCC[kParamBendRange                      ]=24;
  paramToCC[kParamMWINT                          ]=56;
  paramToCC[kParamMWOFFS                         ]=57;
  paramToCC[kParamCvOsc                          ]=23;
  paramToCC[kParamCvFilter                       ]=50;
  paramToCC[kParamCvLoudness                     ]=51;
  paramToCC[kParamOsc1Range                      ]=79;
  paramToCC[kParamOsc2Range                      ]=16;
  paramToCC[kParamOsc3Range                      ]=20;
  paramToCC[kParamOsc1Waveform                   ]=80;
  paramToCC[kParamOsc2Waveform                   ]=83;
  paramToCC[kParamOsc3Waveform                   ]=86;
  paramToCC[kParamOsc3Control                    ]=87;
  paramToCC[kParamOscMod                         ]=22;
  paramToCC[kParamFilterMod1                     ]=47;
  paramToCC[kParamFilterMod2                     ]=48;
  paramToCC[kParamKeybControl                    ]=49;
  paramToCC[kParamNoiseType                      ]=35;
  paramToCC[kParamOsc1                           ]=28;
  paramToCC[kParamOsc2                           ]=29;
  paramToCC[kParamOsc3                           ]=30;
  paramToCC[kParamFeedback                       ]=37;
  paramToCC[kParamNoise                          ]=34;
  paramToCC[kParamGlideOnOff                     ]=65;
  paramToCC[kParamDecay                          ]=59;
  paramToCC[kParamKeybModeRetrig                 ]=60;
  paramToCC[kParamKeybModeLowNote                ]=61;
  paramToCC[kParamKeybModeSingle                 ]=68;
  paramToCC[kParamPitchWheel                     ]=1;

  paramToMsgType[kParamMasterTune                     ]=0;
  paramToMsgType[kParamGlide                          ]=0;
  paramToMsgType[kParamModMix                         ]=0;
  paramToMsgType[kParamOsc2Tune                       ]=0;
  paramToMsgType[kParamOsc3Tune                       ]=0;
  paramToMsgType[kParamOsc1Volume                     ]=0;
  paramToMsgType[kParamOsc2Volume                     ]=0;
  paramToMsgType[kParamOsc3Volume                     ]=0;
  paramToMsgType[kParamFeedbackLevel                  ]=0;
  paramToMsgType[kParamNoiseVolume                    ]=0;
  paramToMsgType[kParamFilterCutoff                   ]=0;
  paramToMsgType[kParamFilterEmphasis                 ]=0;
  paramToMsgType[kParamFilterContour                  ]=0;
  paramToMsgType[kParamFilterAttack                   ]=0;
  paramToMsgType[kParamFilterDecay                    ]=0;
  paramToMsgType[kParamFilterSustain                  ]=0;
  paramToMsgType[kParamVcaAttack                      ]=0;
  paramToMsgType[kParamVcaDecay                       ]=0;
  paramToMsgType[kParamVcaSustain                     ]=0;
  paramToMsgType[kParamVolume                         ]=0;
  paramToMsgType[kParamVelocity                       ]=0;
  paramToMsgType[kParamOutputVelocity                 ]=0;
  paramToMsgType[kParamBendRange                      ]=0;
  paramToMsgType[kParamMWINT                          ]=0;
  paramToMsgType[kParamMWOFFS                         ]=0;
  paramToMsgType[kParamCvOsc                          ]=0;
  paramToMsgType[kParamCvFilter                       ]=0;
  paramToMsgType[kParamCvLoudness                     ]=0;                                                   
  paramToMsgType[kParamOsc1Range                      ]=0;
  paramToMsgType[kParamOsc2Range                      ]=0;
  paramToMsgType[kParamOsc3Range                      ]=0;
  paramToMsgType[kParamOsc1Waveform                   ]=0;
  paramToMsgType[kParamOsc2Waveform                   ]=0;
  paramToMsgType[kParamOsc3Waveform                   ]=0;                                                     
  paramToMsgType[kParamOsc3Control                    ]=0;                                            
  paramToMsgType[kParamOscMod                         ]=0;
  paramToMsgType[kParamFilterMod1                     ]=0;
  paramToMsgType[kParamFilterMod2                     ]=0;
  paramToMsgType[kParamKeybControl                    ]=0;                                                
  paramToMsgType[kParamNoiseType                      ]=0;                                                 
  paramToMsgType[kParamOsc1                           ]=0;
  paramToMsgType[kParamOsc2                           ]=0;
  paramToMsgType[kParamOsc3                           ]=0;
  paramToMsgType[kParamFeedback                       ]=0;
  paramToMsgType[kParamNoise                          ]=0;                             
  paramToMsgType[kParamGlideOnOff                     ]=0;
  paramToMsgType[kParamDecay                          ]=0;
  paramToMsgType[kParamKeybModeRetrig                 ]=0;
  paramToMsgType[kParamKeybModeLowNote                ]=0;
  paramToMsgType[kParamKeybModeSingle                 ]=0;
  paramToMsgType[kParamPitchWheel                     ]=0;
  */
  
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
    IControl* pBG = new IPanelControl(IRECT(0,0, HSM_W, HSK_H), IColor(255,58,58,58));
    pGraphics->AttachControl(pBG);

    const IRECT controls = b.GetGridCell(1, 2, 2);

    IBitmap bitmap;
	
    bitmap = pGraphics->LoadBitmap(FN_MPA);
    IControl* logoCtrl = new IBitmapControl(HS_W+40, HS_H+28, bitmap, kNoParameter);
    pGraphics->AttachControl(logoCtrl, -1, "");

    bitmap = pGraphics->LoadBitmap(FN_LIGHTWAVE);
    IControl* backCtrl = new IBitmapControl(0,0, bitmap, kNoParameter);
    pGraphics->AttachControl(backCtrl, -1, "");

   // bitmap = pGraphics->LoadBitmap(PNGHEADER_FN);
   //  IControl* mainPanelHeadCtrl = new IBitmapControl(0, 338, bitmap, kNoParameter);
   // pGraphics->AttachControl(mainPanelHeadCtrl);
    
    bitmap = pGraphics->LoadBitmap(FN_MIDIMONBACK);
    IControl* midiCtrlBack = new IBitmapControl(HS_W, 0, bitmap, kNoParameter);
    pGraphics->AttachControl(midiCtrlBack, kCtrlTagMidiBack, "midiMonitor");

    bitmap = pGraphics->LoadBitmap(FN_MAIN_PANEL);
    IControl* mainPanelCtrl = new IBitmapControl(19, 44, bitmap, kNoParameter);
    pGraphics->AttachControl(mainPanelCtrl, -1, "main");

    bitmap = pGraphics->LoadBitmap(FN_ADD_PANEL);
    IControl* addPanelCtrl = new IBitmapControl(19, 44, bitmap, kNoParameter);
    pGraphics->AttachControl(addPanelCtrl, -1, "add");
    if (strcmp(addPanelCtrl->GetGroup(), "add") == 0) addPanelCtrl->Hide(true);


    // ICaptions Main

    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(31, 74, 139, 91), kParamOsc1Waveform, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(31, 222, 139, 239), kParamOsc2Waveform, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(31, 155, 101, 172), kParamOsc1PitchModSrc, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(31, 303, 101, 320), kParamOsc2PitchModSrc, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(171, 97, 241, 114), kParamMixOsc1AmpModSrc, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(171, 214, 241, 231), kParamMixOsc2AmpModSrc, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(171, 154, 241, 171), kParamMixOsc1BalanceModSrc, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(171, 267, 241, 284), kParamMixOsc2BalanceModSrc, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");

    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(296, 140, 366, 157), kParamVcf1ModCfSrc, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(296, 162, 366, 179), kParamVcf1ModResSrc, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(296, 283, 366, 300), kParamVcf2ModCfSrc, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(296, 305, 366, 322), kParamVcf2ModCfSrc, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");

    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(457, 199, 527, 216), kParamVcfCutoffModSrc, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(457, 268, 527, 285), kParamVcfResModSrc, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");

    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(534, 216, 604, 233), kParamAmpPanModSrc, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");

    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(364, 56, 434, 73), kParamVcf1Type, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(364, 199, 434, 216), kParamVcf2Type, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");

    // IKnobs Main Green

    IBitmap knob = pGraphics->LoadBitmap(FN_GREENLW, 31, true);

    pGraphics->AttachControl(new IBKnobControlMidi(107, 154, knob, kParamOsc1PitchModAmt), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(134, 158, 157, 173), kParamOsc1PitchModAmt, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(107, 302, knob, kParamOsc2PitchModAmt), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(134, 306, 157, 321), kParamOsc2PitchModAmt, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");

    pGraphics->AttachControl(new IBKnobControlMidi(246, 96, knob, kParamMixOsc1AmpModAmt), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(267, 99, 290, 114), kParamMixOsc1AmpModAmt, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(246, 213, knob, kParamMixOsc2AmpModAmt), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(267, 156, 290, 171), kParamMixOsc2AmpModAmt, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(246, 153, knob, kParamMixOsc1BalanceModAmt), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(38, 133, 61, 148), kParamMixOsc1BalanceModAmt, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(246, 266, knob, kParamMixOsc2BalanceModAmt), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(38, 133, 61, 148), kParamMixOsc2BalanceModAmt, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");

    pGraphics->AttachControl(new IBKnobControlMidi(375, 91, knob, kParamVcf1keyf), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(374, 116, 397, 131), kParamVcf1keyf, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(415, 91, knob, kParamVcf1Env), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(414, 116, 437, 131), kParamVcf1Env, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(368, 140, knob, kParamVcf1ModCfAmt), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(413, 143, 436, 158), kParamVcf1ModCfAmt, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(368, 161, knob, kParamVcf1ModResAmt), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(413, 163, 436, 178), kParamVcf1ModResAmt, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");

    pGraphics->AttachControl(new IBKnobControlMidi(375, 91 + 143, knob, kParamVcf2keyf), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(373, 260, 396, 275), kParamVcf2keyf, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(415, 91 + 143, knob, kParamVcf2Env), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(413, 260, 436, 275), kParamVcf2Env, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(368, 140 + 143, knob, kParamVcf2ModCfAmt), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(413, 286, 436, 301), kParamVcf2ModCfAmt, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(368, 161 + 143, knob, kParamVcf2ModResAmt), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(413, 307, 436, 322), kParamVcf2ModResAmt, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");

    pGraphics->AttachControl(new IBKnobControlMidi(536, 285 - 197, knob, kParamVcfEnvTKf), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(535, 113, 558, 128), kParamVcfEnvTKf, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(569, 285 - 197, knob, kParamVcfEnvTVel), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(568, 113, 591, 128), kParamVcfEnvTVel, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(600, 285 - 197, knob, kParamVcfEnvLVel), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(598, 113, 621, 128), kParamVcfEnvLVel, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
 
    pGraphics->AttachControl(new IBKnobControlMidi(536, 285, knob, kParamAmpEnvTKf), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(535, 311, 558, 326), kParamAmpEnvTKf, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(569, 285, knob, kParamAmpEnvTVel), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(568, 311, 591, 326), kParamAmpEnvTVel, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(600, 285, knob, kParamAmpEnvLVel), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(598, 311, 621, 326), kParamAmpEnvLVel, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");

    pGraphics->AttachControl(new IBKnobControlMidi(655, 214, knob, kParamAmpPanModAmt), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(679, 217, 702, 232), kParamAmpPanModAmt, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(462, 224, knob, kParamVcfCutoffModAmt), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(494, 227, 517, 242), kParamVcfCutoffModAmt, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(462, 292, knob, kParamVcfResModAmt), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(494, 295, 517, 310), kParamVcfResModAmt, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");


    // IKnobs Main Blue

    knob = pGraphics->LoadBitmap(FN_BLUELW, 31, true);

    pGraphics->AttachControl(new IBKnobControlMidi(39, 108, knob, kParamOsc1Coarse), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(38, 133, 61, 148), kParamOsc1Coarse, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(74, 108, knob, kParamOsc1Fine), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(73, 133, 96, 148), kParamOsc1Fine, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(110, 109, knob, kParamOsc1Grunge), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(109, 133, 132, 148), kParamOsc1Grunge, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");

    pGraphics->AttachControl(new IBKnobControlMidi(39, 257, knob, kParamOsc2Coarse), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(38, 133+149, 61, 148 + 149), kParamOsc2Coarse, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(74, 257, knob, kParamOsc2Fine), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(73, 133 + 149, 96, 148 + 149), kParamOsc2Fine, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(110, 257, knob, kParamOsc2Grunge), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(109, 133 + 149, 132, 148 + 149), kParamOsc2Grunge, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");

    pGraphics->AttachControl(new IBKnobControlMidi(246, 71, knob, kParamMixOsc1), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(267, 75, 290, 90), kParamMixOsc1, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(246, 128, knob, kParamMixOsc1Balance), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(267, 131, 290, 146), kParamMixOsc1Balance, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(246, 188, knob, kParamMixOsc2), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(267, 192, 290, 207), kParamMixOsc2, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(246, 241, knob, kParamMixOsc2Balance), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(267, 244, 290, 259), kParamMixOsc2Balance, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
                                                
    pGraphics->AttachControl(new IBKnobControlMidi(246, 304, knob, kParamMixGain), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(267, 306, 290, 321), kParamMixGain, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");

    pGraphics->AttachControl(new IBKnobControlMidi(655, 140, knob, kParamAmpVol), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(679, 142, 702, 157), kParamAmpVol, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(655, 165, knob, kParamAmpPan), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(679, 168, 702, 183), kParamAmpPan, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");

    // IKnobs Main Red

    knob = pGraphics->LoadBitmap(FN_REDLW, 31, true);

    pGraphics->AttachControl(new IBKnobControlMidi(302, 91, knob, kParamVcf1Cf), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(301, 116, 324, 131), kParamVcf1Cf, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(334, 91, knob, kParamVcf1Res), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(333, 116, 356, 131), kParamVcf1Res, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");

    pGraphics->AttachControl(new IBKnobControlMidi(302, 234, knob, kParamVcf2Cf), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(301, 260, 324, 275), kParamVcf2Cf, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(334, 234, knob, kParamVcf2Res), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(333, 260, 356, 275), kParamVcf2Res, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");

    // KNOBS
    /*bitmap = pGraphics->LoadBitmap(PNGKNOB32_FN, 33);

    int offx = 6;
    int offy = -6;

    pGraphics->AttachControl(new IBKnobControlMidi(54, 72, bitmap, kParamMasterTune), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(20, 161, bitmap, kParamGlide), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(92, 161, bitmap, kParamModMix), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(278, 165, bitmap, kParamOsc2Tune), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(278, 259, bitmap, kParamOsc3Tune), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 430, offy + 86, bitmap, kParamOsc1Volume), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 430, offy + 168, bitmap, kParamOsc2Volume), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 430, offy + 253, bitmap, kParamOsc3Volume), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 548, offy + 127, bitmap, kParamFeedbackLevel), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 548, offy + 209, bitmap, kParamNoiseVolume), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(681, offy + 88, bitmap, kParamFilterCutoff), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 750, offy + 88, bitmap, kParamFilterEmphasis), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 820, offy + 88, bitmap, kParamFilterContour), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(681, offy + 171, bitmap, kParamFilterAttack), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 750, offy + 171, bitmap, kParamFilterDecay), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 820, offy + 171, bitmap, kParamFilterSustain), -1, "main");

    pGraphics->AttachControl(new IBKnobControlMidi(681, offy + 264, bitmap, kParamVcaAttack), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 750, offy + 264, bitmap, kParamVcaDecay), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 820, offy + 264, bitmap, kParamVcaSustain), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 896, offy + 86, bitmap, kParamVolume), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 896, offy + 174, bitmap, kParamVelocity), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 896, offy + 264, bitmap, kParamOutputVelocity), -1, "main");

    std::function<double(double)> mappingFunc2 = [](double midiVal) {return midiVal*127./24.; };
    pGraphics->AttachControl(new IBKnobControlMidi(53, 73, bitmap, kParamBendRange, mappingFunc2), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(19, 161, bitmap, kParamMWINT), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(93, 161, bitmap, kParamMWOFFS), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(173, 72, bitmap, kParamCvOsc), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(173, 159, bitmap, kParamCvFilter), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(173, 247, bitmap, kParamCvLoudness), -1, "add");

    offx = 0;
    offy = 0;
    pGraphics->AttachControl(new IBKnobControlMidi(265, 220, bitmap, kParamChorusPhase), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(269, 101, bitmap, kParamChorusRate), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(357, 156, bitmap, kParamChorusDepth), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(354, 247, bitmap, kParamChorusFeedback), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(437, 157, bitmap, kParamChorusWet), -1, "add");
    */
    pGraphics->AttachControl(new IBKnobControlMidi(530, 101, bitmap, kParamDelayTimeLMS), kCtrlTagDelayTimeLMS, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(530, 232, bitmap, kParamDelayTimeRMS), kCtrlTagDelayTimeRMS, "add");
    /*
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 609, 101, bitmap, kParamDelayFeedbackLeft), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 609, 232, bitmap, kParamDelayFeedbackLeft), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 691, 101, bitmap, kParamDelayHidampLeft), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 691, 232, bitmap, kParamDelayHidampRight), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 769, 101, bitmap, kParamDelayLevelLeft), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 769, 232, bitmap, kParamDelayLevelRight), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(897, 158, bitmap, kParamDelayWet), -1, "add");
    /*
    // SWITCHES 
    bitmap = pGraphics->LoadBitmap(PNGKNOB6_FN, 6, true);
    std::function<double(double)> mappingRange = [](double midiVal) {return midiVal * 127./110.; };
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 190, offy + 69, bitmap, kParamOsc1Range, mappingRange), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 190, offy + 156, bitmap, kParamOsc2Range, mappingRange), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 190, offy + 249, bitmap, kParamOsc3Range, mappingRange), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 353, offy + 69, bitmap, kParamOsc1Waveform, mappingRange), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 353, offy + 156, bitmap, kParamOsc2Waveform, mappingRange), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 353, offy + 249, bitmap, kParamOsc3Waveform, mappingRange), -1, "main");

    bitmap = pGraphics->LoadBitmap(PNGKNOB2_FN, 2, true);
    pGraphics->AttachControl(new IBKnobControlMidi(offx + 352, offy + 69, bitmap, kParamFlangerChorus, NULL, EDirection::Vertical, 1.), -1, "add");

    bitmap = pGraphics->LoadBitmap(PNGSWITCHREDV_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 164, offy + 278, bitmap, kParamOsc3Control), -1, "main");

    bitmap = pGraphics->LoadBitmap(PNGSWITCHREDHBYPASS_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(483, 316, bitmap, kParamEffectBypass), -1, "add");

    bitmap = pGraphics->LoadBitmap(PNGSWITCHREDH_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 623, offy + 175, bitmap, kParamKeybControl), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 623, offy + 92, bitmap, kParamFilterMod1), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 623, offy + 137, bitmap, kParamFilterMod2), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 136, offy + 100, bitmap, kParamOscMod), -1, "main");

    
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 611, offy + 172, bitmap, kParamDelayCrossDual), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 840, offy + 110, bitmap, kParamDelayUnitLeft), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 840, offy + 243, bitmap, kParamDelayUnitRight), -1, "add");

    bitmap = pGraphics->LoadBitmap(PNGSWITCHBLUEV_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 614, offy + 214, bitmap, kParamNoiseType), -1, "main");

    bitmap = pGraphics->LoadBitmap(PNGSWITCHBLUEH_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 497, offy + 92, bitmap, kParamOsc1), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 497, offy + 175, bitmap, kParamOsc2), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 497, offy + 260, bitmap, kParamOsc3), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 497, offy + 134, bitmap, kParamFeedback), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 497, offy + 216, bitmap, kParamNoise), -1, "main");

    bitmap = pGraphics->LoadBitmap(PNGSWITCHSILVERH_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 63, offy + 240, bitmap, kParamGlideOnOff), -1, "main");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 63, offy + 268, bitmap, kParamDecay), -1, "main");

    bitmap = pGraphics->LoadBitmap(PNGSWITCHSILVERH_FN, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 63, offy + 254, bitmap, kParamKeybModeRetrig), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 63, offy + 225, bitmap, kParamKeybModeLowNote), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(offx + 63, offy + 284, bitmap, kParamKeybModeSingle), -1, "add");
    */
    //bitmap = pGraphics->LoadBitmap(FN_PITCHWHEEL14, 14, true);
    //pGraphics->AttachControl(new IBKnobControlMidi(offx + 108, offy + 230, bitmap, kParamPitchWheel), -1, "add");
    /*
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(108, 40, 138, 55), kParamBendRange, DEFAULT_TEXT, COLOR_MID_GRAY, true, mappingFunc2), -1, "add");

    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(268, 154, 307, 170), kParamChorusRate, DEFAULT_TEXT, COLOR_MID_GRAY, true), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(268, 274, 307, 290), kParamChorusPhase, DEFAULT_TEXT, COLOR_MID_GRAY, true), -1, "add");

    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(832, 168, 878, 186), kParamMidiClockBpm, DEFAULT_TEXT, COLOR_MID_GRAY, true), -1, "add");
    */
    //bitmap = pGraphics->LoadBitmap(PNGKNOBBG_FN);
    IControl* delayTimeSkalaL = new IBitmapControl(503, 70, bitmap, kNoParameter);
    pGraphics->AttachControl(delayTimeSkalaL, kCtrlTagSkalaL, "add");

    IControl* delayTimeSkalaR = new IBitmapControl(503, 200, bitmap, kNoParameter);
    pGraphics->AttachControl(delayTimeSkalaR, kCtrlTagSkalaR, "add");

    
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(528, 114, 577, 131), kParamDelayTimeLBPM, DEFAULT_TEXT, COLOR_MID_GRAY, true), kCtrlTagDelayTimeLBPM, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(528, 245, 577, 262), kParamDelayTimeRBPM, DEFAULT_TEXT, COLOR_MID_GRAY, true), kCtrlTagDelayTimeRBPM, "add");
   
    bitmap = pGraphics->LoadBitmap(FN_MIDIACTIVE, 2);
    pGraphics->AttachControl(new IBitmapControl(282, 14, bitmap, kParamMidiActive), kCtrlMidiActive, "");
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
            pCaller->GetUI()->GetControlWithTag(kCtrlTagSkalaL)->Hide(true);

          }
          else {
          pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(false);
          pCaller->GetUI()->GetControlWithTag(kCtrlTagSkalaL)->Hide(false);
          pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMS)->Hide(true);
          }
        }

        if (pCaller->GetUI()->GetControlWithTag(kCtrlTagAdd)->GetValue() == 1) {
          if (pCaller->GetDelegate()->GetParam(kParamDelayUnitRight)->Value() == 0) {
          pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(true);
          pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMS)->Hide(false);
          pCaller->GetUI()->GetControlWithTag(kCtrlTagSkalaR)->Hide(true);
          }
          else {
           pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(false);
           pCaller->GetUI()->GetControlWithTag(kCtrlTagSkalaR)->Hide(false);
           pCaller->GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMS)->Hide(true);
          }
        }

      }
    };

    bitmap = pGraphics->LoadBitmap(FN_MAIN, 2);
    IBSwitchControlFunc *mainCtrl = new IBSwitchControlFunc(35, 345, bitmap, windowFunc, kNoParameter);
    pGraphics->AttachControl(mainCtrl, kCtrlTagMain);
    mainCtrl->SetValue(1);
    bitmap = pGraphics->LoadBitmap(FN_ADD, 2);
    IBSwitchControlFunc *addCtrl = new IBSwitchControlFunc(100, 345, bitmap, windowFunc, kNoParameter);
    pGraphics->AttachControl(addCtrl, kCtrlTagAdd);

    // MIXER UI
#include "../MPA Code/MixerUI.h" 

    // KEYBOARD UI
#include "../MPA Code/KeyboardUI.h"

// RESIZE CONTROLS ////////////////////////////////////////////////////////////////////////////////////////////////

#include "../MPA Code/Resize.h" 

    bitmap = pGraphics->LoadBitmap(FN_MIDIMONITOR, 2);
    IBSwitchControl *presetUI = new IBSwitchControl(509, 14, bitmap, kNoParameter);
    pGraphics->AttachControl(presetUI, kCtrlTagMidiMonHide, "");
    presetUI->SetActionFunction(resizeFunc);

    bitmap = pGraphics->LoadBitmap(FN_MIXER, 2); // MIXER UI
    IBSwitchControl *mixerUICtrl = new IBSwitchControl(434, 14, bitmap, kNoParameter);
    pGraphics->AttachControl(mixerUICtrl, kCtrlTagMixerHide, "");
    mixerUICtrl->SetActionFunction(resizeFunc);

    bitmap = pGraphics->LoadBitmap(FN_KEYB, 2);
    IBSwitchControl *keybCtrl = new IBSwitchControl(359, 14, bitmap, kNoParameter);
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
    IBButtonControl* clearCtrl = new IBButtonControl(HS_W + 64, 351, bitmap, [&](IControl*) {mMidiLogger->Clear(); });
    pGraphics->AttachControl(clearCtrl, kCtrlTagClear, "midiMonitor");

    mMidiLogger = new MidiMonitor(IRECT(HS_W + 14, 379-118, HS_W + 196, 454-118), "", "", IText(12, COLOR_BLACK, "Calibri", EAlign::Near), COLOR_WHITE);
    pGraphics->AttachControl(mMidiLogger, kCtrlTagMidiLogger, "midiMonitor");

    bitmap = pGraphics->LoadBitmap(FN_SLIDER, 1);
    pGraphics->AttachControl(new IBSliderControlScroll(HS_W + 210, 378 -118, 75, -1, bitmap), kCtrlSliderMidiMon1);
    pGraphics->GetControlWithTag(kCtrlSliderMidiMon1)->SetActionFunction([&](IControl* ctrl) {mMidiLogger->setEntrypointerOffset(1. - ctrl->GetValue()); });
    pGraphics->GetControlWithTag(kCtrlSliderMidiMon1)->SetValue(1.);

    bitmap = pGraphics->LoadBitmap(FN_RECALL, 1);
    IBButtonControl* RecallCtrl = new IBButtonControl(HS_W + 6, 321-118, bitmap, [&](IControl*) {});
    RecallCtrl->SetActionFunction([&](IControl* ctrl) {
      mPresetList->mActiveRow = mPresetList->mSelectedRow;
      GetUI()->GetControlWithTag(kCtrlProgram)->SetValue((double)mPresetList->mActiveRow / (mPresetList->maxLogSamples - 1.));
      GetUI()->GetControlWithTag(kCtrlProgram)->SetDirty();
      });
    pGraphics->AttachControl(RecallCtrl, -1, "midiMonitor");

        bitmap = pGraphics->LoadBitmap(FN_OVERWRITE, 1);
    IBButtonControl* overwriteCtrl = new IBButtonControl(HS_W+85, 321-118, bitmap, [&](IControl* pCaller)
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
    IBButtonControl* resetCtrl = new IBButtonControl(HS_W + 164, 321-118, bitmap,

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

    mPresetList = new PresetList(IRECT(HS_W + 14, 97, HS_W + 196, 310-118), 8, "", "", IText(12, COLOR_BLACK, "Calibri", EAlign::Near), COLOR_WHITE);
    pGraphics->AttachControl(mPresetList, kCtrlTagPresetList, "presetList");

    for (int k = 0; k < 50; k++) {
		  mPresetList->addItem(presetname[k]);
	  }

    bitmap = pGraphics->LoadBitmap(FN_SLIDER, 1);
    pGraphics->AttachControl(new IBSliderControlScroll(HS_W + 210, 95, 214-118, -1, bitmap), kCtrlSliderPresetList);
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

     GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(true);
      GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMS)->Hide(true);
      GetUI()->GetControlWithTag(kCtrlTagSkalaL)->Hide(true);

      GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(true);
      GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMS)->Hide(true);
      GetUI()->GetControlWithTag(kCtrlTagSkalaR)->Hide(true);
    }
  };
  
#endif
}

#if IPLUG_DSP
void Lightwave::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
  const int nChans = NOutChansConnected();
  
  for (auto s = 0; s < nFrames; s++) {
    for (auto c = 0; c < nChans; c++) {
      outputs[c][s] = 0.;
    }
  }
}

void Lightwave::OnIdle()
{
  mMidiLoggerSender.TransmitData(*this);
}

void Lightwave::OnReset()
{
}

void Lightwave ::OnUIClose() {
  if(GetParam(kParamUserFactory)->Value() == 0) activeRowFactory = mPresetList->mActiveRow;
  if (GetParam(kParamUserFactory)->Value() == 1) activeRowUser = mPresetList->mActiveRow;

  for (auto r = 0; r < mMidiLogger->maxLogSamples; r++) {
    for (auto c = 0; c < mMidiLogger->numColumns; c++) {
      mStrBufSave[r][c] = mMidiLogger->mStrBuf[r][c];
    }
  }
  mEntryPtrSave = mMidiLogger->mEntryPointer;
}

void Lightwave::OnUIOpen() {

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
void Lightwave::ProcessMidiMsg(const IMidiMsg& msg)
{
  TRACE;

#include "../MPA Code/ProcessMidi.h"
}

void Lightwave::OnParamChange(int paramIdx)
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
//    case kParamOsc1Range:
    //case kParamOsc2Range:
   // case kParamOsc3Range:
    case kParamOsc1Waveform:
    case kParamOsc2Waveform:
   // case kParamOsc3Waveform:
      msg.mData2 = GetParam(paramIdx)->Value()*22;
      break;
    }


   // if(paramIdx == kParamBendRange) msg.mData2 = GetParam(paramIdx)->Value();

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
      msg.mData2 = 0x00;
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
      msg.mData2 = 0x00;
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
  
    if (GetUI() && GetUI()->GetControlWithTag(kCtrlMidiActive)) GetUI()->GetControlWithTag(kCtrlMidiActive)->SetValueFromUserInput(1.);
  
  if (GetParam(kParamUserFactory)->Value() == 0) { // Factory
      msg.Clear();
      msg.mStatus = mChannel | (IMidiMsg::kControlChange << 4);
      msg.mData1 = 0x00;
      msg.mData2 = 0x00;
      msg.mOffset = -2;
      SendMidiMsgFromUI(msg);
      msg.Clear();
      msg.mStatus = mChannel | (IMidiMsg::kControlChange << 4);
      msg.mData1 = 0x20;
      msg.mData2 = 0x00;
      msg.mOffset = -2;
      SendMidiMsgFromUI(msg);
    }
    else if (GetParam(kParamUserFactory)->Value() == 1) { // User
      msg.Clear();
      msg.mStatus = mChannel | (IMidiMsg::kControlChange << 4);
      msg.mData1 = 0x00;
      msg.mData2 = 0x00;
      msg.mOffset = -2;
      SendMidiMsgFromUI(msg);
      msg.Clear();
      msg.mStatus = mChannel | (IMidiMsg::kControlChange << 4);
      msg.mData1 = 0x20;
      msg.mData2 = 0x01;
      msg.mOffset = -2;
      SendMidiMsgFromUI(msg);
    }
	
    msg.Clear();
    msg.mStatus = mChannel | (IMidiMsg::kProgramChange << 4);
    msg.mData1 = GetParam(paramIdx)->Value();
    msg.mData2 = 0;
    msg.mOffset = -2;
    SendMidiMsgFromUI(msg);
          
    break;

  case kParamDelayUnitLeft:
    if (GetUI()) {
      if (GetUI()->GetControlWithTag(kCtrlTagAdd)->GetValue() == 1) {
        if (GetParam(paramIdx)->Value() == 0) {
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(true);
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeLMS)->Hide(false);
          GetUI()->GetControlWithTag(kCtrlTagSkalaL)->Hide(true);

        }
        else {
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeLBPM)->Hide(false);
          GetUI()->GetControlWithTag(kCtrlTagSkalaL)->Hide(false);
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
          GetUI()->GetControlWithTag(kCtrlTagSkalaR)->Hide(true);
        }
        else {
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeRBPM)->Hide(false);
          GetUI()->GetControlWithTag(kCtrlTagSkalaR)->Hide(false);
          GetUI()->GetControlWithTag(kCtrlTagDelayTimeRMS)->Hide(true);
        }
      }
    }
    break;
      
    default:
      break;
  }
}

bool Lightwave::SerializeState(IByteChunk& chunk) const {

  TRACE;

  return SerializeParams(chunk);
}

// this over-ridden method is called when the host is trying to load the plug-in state and you need to unpack the data into your algorithm
// HIER KÖNNEN KEINE CONTROLS GEUPDATED WERDEN; DA MGRAPHICS NOCH NICHT EXISTIERT!!!!
int Lightwave::UnserializeState(const IByteChunk& chunk, int startPos) {

  TRACE;

  return UnserializeParams(chunk, startPos);
}
#endif
