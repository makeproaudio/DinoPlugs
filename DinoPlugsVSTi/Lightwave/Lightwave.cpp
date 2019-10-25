#include "Lightwave.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"
#include "json.hpp"
#include <fstream>

Lightwave::Lightwave(IPlugInstanceInfo instanceInfo)
: IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo)
{

  presetname[0 ].Set("00: Flip Wave");
  presetname[1].Set("01: Distant Memories");
  presetname[2].Set("02: Flash Gordon");
  presetname[3].Set("03: Imagine");
  presetname[4].Set("04: Tech Bass");
  presetname[5].Set("05: D-Bass");
  presetname[6].Set("06: Fret Bass");
  presetname[7].Set("07: Brass Bass");
  presetname[8].Set("08: Rock Bass");
  presetname[9].Set("09: Dub Sub Mod");
  presetname[10].Set("10: Electro Bass");
  presetname[11].Set("11: Synergy");
  presetname[12].Set("12: Brave New Universe");
  presetname[13].Set("13: Bell Chiffer");
  presetname[14].Set("14: Both Ways");
  presetname[15].Set("15: Whistler");
  presetname[16].Set("16: You Cant Have It Both Ways");
  presetname[17].Set("17: Moon Walk");
  presetname[18].Set("18: Bellica Lead");
  presetname[19].Set("19: Bellish Hammond");
  presetname[20].Set("20: Inner Organ");
  presetname[21].Set("21: Fantasia");
  presetname[22].Set("22: Pulsar");
  presetname[23].Set("23: Dirty Mouth");
  presetname[24].Set("24: Cristal Glass");
  presetname[25].Set("25: Steve Ostin");
  presetname[26].Set("26: Pat My Ear");
  presetname[27].Set("27: Where Is The Phaser ?");
  presetname[28].Set("28: Music Box");
  presetname[29].Set("29: Deep Water");
  presetname[30].Set("30: Fender Farfisa");
  presetname[31].Set("31: Samba Piano");
  presetname[32].Set("32: Afrikan Piano");
  presetname[33].Set("33: DX7");
  presetname[34].Set("34: Pintseta");
  presetname[35].Set("35: Human Bells");
  presetname[36].Set("36: Jaffanese Fynth");
  presetname[37].Set("37: Jazz Guitar");
  presetname[38].Set("38: Dekliker");
  presetname[39].Set("39: Top Resudue");
  presetname[40].Set("40: Lightwave");
  presetname[41].Set("41: Evolver");
  presetname[42].Set("42: Humptty");
  presetname[43].Set("43: Velocity Choker");
  presetname[44].Set("44: Behind The Speekers");
  presetname[45].Set("45: Light Switch");
  presetname[46].Set("46: Sekwen Son");
  presetname[47].Set("47: Dark Disco");
  presetname[48].Set("48: Bipolar");
  presetname[49].Set("49: Greeze");

   // MIXER UI
  #include "../MPA Code/GlobalParamInit.h"

  GetParam(kParamPitchWheel)->InitDouble("Pitch Wheel", 0, 0, 1, 0.001);

  GetParam(kParamOsc1Waveform)->InitEnum("Osc 1 Waveform", 0, 128, "", 0, "", "noise", "sine wave", "sawtooth", "square", "vectron typical 1", "vectron typical 2", "cream wave 1", "fifthback", "vectron typical 3", "trash 1", "trash 2", "American twang", "sandangle", "cheeporg", "highly pulsive", "restrained pulse", "smooth reed", "JayBase", "options open", "upscale", "hammertone", "Anywave 1", "Anywave 2", "Anywave 3", "uppercrust", "acchord", "nondescript", "tiney thing", "langpipe", "deepring", "rhodeToNowhere", "thikring", "whirlitza", "no occident", "pipe up", "alreedy there", "generic", "pop smear 1", "poem freet", "clara nette", "seriously now", "jaz pic", "deep sax", "mareemba", "say what", "pro fundo", "mund harp", "take it down", "plucky", "under the neck", "sin flute", "oboy", "got a run", "silophone", "ach du liebe", "namelesswave", "lead off", "no ground", "digitine", "red whine", "hand me pliers", "wearing thin", "bridge", "reed directions", "ol'fateful", "windy city", "far feeza", "knew orleans", "cruis'n attitude", "fresh", "VocForm01", "VocForm02", "VocForm03", "VocForm04", "VocForm05", "VocForm06", "VocForm07", "VocForm08", "VocForm09", "VocForm10", "VocForm11", "VocForm12", "only a test", "spinBottle", "blown cap", "bassish", "kitschorg", "come 2 harm", "huzz", "under the rug", "gryndyr", "to the point", "mars lander", "String perc", "Annoys Dog", "Short perc", "ModForm1 A", "ModForm1 AE", "ModForm1 E", "ModForm1 I", "ModForm1 EE", "ModForm1 OO", "ModForm1 O", "ModForm1 OU", "Partials 1-4", "Partials 5-8", "Partials 8-12", "Partial 1+2", "Partial 1+3", "Partial 1+4", "Partial 1+5", "Partial 1+6", "Partial 1+7", "Partial 1+8", "Partial 1+2+4", "Partial 1+3+5", "Partial 1+2+4+6", "Partial 1+3+5+7", "20p FM 1:1", "20p FM 1:2", "20p FM 1:3", "20p FM 1:4", "20p FM 1:5", "20p FM 1:6", "20p FM 1:7", "DownSampSync1", "DownSampSync2", "Reading Room");

  // This is super crazy, kParamSplitUpperManual changes to 5007 in GetParam. The exception. Cause could be array access out of bounds.
 
    if(GetParam(kParamOsc1Coarse)) GetParam(kParamOsc1Coarse)->InitInt("Osc 1 Coarse", 0, -48, 48);
    if (GetParam(kParamOsc1Coarse))GetParam(kParamOsc1Coarse)->InitInt("Osc 1 Coarse", 0, -48, 48);


  
  GetParam(kParamOsc1Fine)->InitInt("Osc 1 Fine", 0, -99, 99);
  GetParam(kParamOsc1Grunge)->InitInt("Osc 1 Grunge", 0, 0, 127);
  GetParam(kParamOsc1PitchModSrc)->InitEnum("Osc 1 Pitch Mod Src", 0, 17, "", 0, "", "OFF", "LFO1", "LFO2", "LFO1+2", "LFO1*2", "LFO1*MW", "LFO1*AT", "LFO2*MW", "LFO2*AT", "Filter Env", "Amp Env", "Free Env +", "Free Env -", "Key follow", "Velocity", "AfterTouch", "Mod wheel");
  GetParam(kParamOsc1PitchModAmt)->InitInt("Osc 1 Pitch Mod Amt", 0, -63, 63);

  GetParam(kParamOsc2Waveform)->InitEnum("Osc 2 Waveform", 0, 128, "", 0, "", "noise", "sine wave", "sawtooth", "square", "vectron typical 1", "vectron typical 2", "cream wave 1", "fifthback", "vectron typical 3", "trash 1", "trash 2", "American twang", "sandangle", "cheeporg", "highly pulsive", "restrained pulse", "smooth reed", "JayBase", "options open", "upscale", "hammertone", "Anywave 1", "Anywave 2", "Anywave 3", "uppercrust", "acchord", "nondescript", "tiney thing", "langpipe", "deepring", "rhodeToNowhere", "thikring", "whirlitza", "no occident", "pipe up", "alreedy there", "generic", "pop smear 1", "poem freet", "clara nette", "seriously now", "jaz pic", "deep sax", "mareemba", "say what", "pro fundo", "mund harp", "take it down", "plucky", "under the neck", "sin flute", "oboy", "got a run", "silophone", "ach du liebe", "namelesswave", "lead off", "no ground", "digitine", "red whine", "hand me pliers", "wearing thin", "bridge", "reed directions", "ol'fateful", "windy city", "far feeza", "knew orleans", "cruis'n attitude", "fresh", "VocForm01", "VocForm02", "VocForm03", "VocForm04", "VocForm05", "VocForm06", "VocForm07", "VocForm08", "VocForm09", "VocForm10", "VocForm11", "VocForm12", "only a test", "spinBottle", "blown cap", "bassish", "kitschorg", "come 2 harm", "huzz", "under the rug", "gryndyr", "to the point", "mars lander", "String perc", "Annoys Dog", "Short perc", "ModForm1 A", "ModForm1 AE", "ModForm1 E", "ModForm1 I", "ModForm1 EE", "ModForm1 OO", "ModForm1 O", "ModForm1 OU", "Partials 1-4", "Partials 5-8", "Partials 8-12", "Partial 1+2", "Partial 1+3", "Partial 1+4", "Partial 1+5", "Partial 1+6", "Partial 1+7", "Partial 1+8", "Partial 1+2+4", "Partial 1+3+5", "Partial 1+2+4+6", "Partial 1+3+5+7", "20p FM 1:1", "20p FM 1:2", "20p FM 1:3", "20p FM 1:4", "20p FM 1:5", "20p FM 1:6", "20p FM 1:7", "DownSampSync1", "DownSampSync2", "Reading Room");
  if (GetParam(kParamOsc2Coarse)) GetParam(kParamOsc2Coarse)->InitInt("Osc 2 Coarse", 0, -48, 48);
  if (GetParam(kParamOsc2Coarse)) GetParam(kParamOsc2Coarse)->InitInt("Osc 2 Coarse", 0, -48, 48);
  if (GetParam(kParamOsc2Fine)) GetParam(kParamOsc2Fine)->InitInt("Osc 2 Fine", 0, -99, 99);
  if (GetParam(kParamOsc2Fine)) GetParam(kParamOsc2Fine)->InitInt("Osc 2 Fine", 0, -99, 99);
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
  GetParam(kParamAmpPan1)->InitInt("Amp Pan 1", 0, -63, 63);
  GetParam(kParamAmpPanModSrc1)->InitEnum("Amp Pan 1 Mod Src", 0, 17, "", 0, "", "OFF", "LFO1", "LFO2", "LFO1+2", "LFO1*2", "LFO1*MW", "LFO1*AT", "LFO2*MW", "LFO2*AT", "Filter Env", "Amp Env", "Free Env +", "Free Env -", "Key follow", "Velocity", "AfterTouch", "Mod wheel");
  GetParam(kParamAmpPanModAmt1)->InitInt("Amp Pan 1 Mod Amt", 0, -63, 63);
  GetParam(kParamAmpEnvTKf)->InitInt("Amp Env Tkf", 0, -200, 200);
  GetParam(kParamAmpEnvTVel)->InitInt("Amp Env TVel", 0, -200, 200);
  GetParam(kParamAmpEnvLVel)->InitInt("Amp Env LVel", 0, -0, 127);
  GetParam(kParamAmpEnvA)->InitInt("Vcf Env Attack", 0, 0, 127);
  GetParam(kParamAmpEnvD)->InitInt("Vcf Env Decay", 0, 0, 127);
  GetParam(kParamAmpEnvS)->InitInt("Vcf Env Sustain", 0, 0, 127);
  GetParam(kParamAmpEnvR)->InitInt("Vcf Env Release", 0, 0, 127);

  // add

  GetParam(kParamCoarse)->InitInt("Coarse", 0, -48, 48);
  GetParam(kParamFine)->InitInt("Fine", 0, -99, 99);
  GetParam(kParamBendRange)->InitInt("Bend Range", 0, -0, 24);
  GetParam(kParamPModAmt)->InitInt("P Mod Amt", 0, -63, 63);
  GetParam(kParamPModSrc)->InitEnum("P Mod Src", 0, 17, "", 0, "", "OFF", "LFO1", "LFO2", "LFO1+2", "LFO1*2", "LFO1*MW", "LFO1*AT", "LFO2*MW", "LFO2*AT", "Filter Env", "Amp Env", "Free Env +", "Free Env -", "Key follow", "Velocity", "AfterTouch", "Mod wheel");

  GetParam(kParamLfo1Wave)->InitEnum("LFO 1 Waveform", 0, 6, "", 0, "", "Sine", "Rectangle", "Triangle", "Sawtooth Up", "Sawtooth Down", "Noise");
  GetParam(kParamLfo1Rate)->InitInt("LFO 1 Rate", 1, 1, 20);
  GetParam(kParamLfo1RateBPM)->InitEnum("LFO 1 Rate BPM", 0, 19, "", 0, "", "1/1", "1/2P", "1/2", "1/2T", "1/4P", "1/4", "1/4T", "1/8P", "1/8", "1/8T", "1/16P", "1/16", "1/16T", "1/32P", "1/32", "1/32T", "1/64P", "1/64", "1/64T");
  GetParam(kParamLfo1Retrig)->InitBool("LFO 1 Retrig", false);
  GetParam(kParamLfo1Del)->InitInt("LFO 1 Del", 0, 0, 127);
  GetParam(kParamLfo1Fin)->InitInt("LFO 1 F In", 0, 0, 127);
  GetParam(kParamLfo1Fout)->InitInt("LFO 1 F Out", 0, 0, 127);
  GetParam(kParamLfo1Midi)->InitBool("LFO 1 MIDI", false);
  GetParam(kParamLfo1Phase)->InitInt("LFO 1 Phase", 0, -180, 180);
  GetParam(kParamLfo1Keyf)->InitInt("LFO 1 Keyf", 0, -200, 200);
  GetParam(kParamLfo1Rmod1Amt)->InitInt("LFO 1 R Mod 1 Amt", 0, -63, 63);
  GetParam(kParamLfo1Rmod2Amt)->InitInt("LFO 1 R Mod 2 Amt", 0, -63, 63);
  GetParam(kParamLfo1Rmod1Src)->InitEnum("LFO 1 R Mod 1 Src", 0, 17, "", 0, "", "OFF", "LFO1", "LFO2", "LFO1+2", "LFO1*2", "LFO1*MW", "LFO1*AT", "LFO2*MW", "LFO2*AT", "Filter Env", "Amp Env", "Free Env +", "Free Env -", "Key follow", "Velocity", "AfterTouch", "Mod wheel");
  GetParam(kParamLfo1Rmod2Src)->InitEnum("LFO 1 R Mod 2 Src", 0, 17, "", 0, "", "OFF", "LFO1", "LFO2", "LFO1+2", "LFO1*2", "LFO1*MW", "LFO1*AT", "LFO2*MW", "LFO2*AT", "Filter Env", "Amp Env", "Free Env +", "Free Env -", "Key follow", "Velocity", "AfterTouch", "Mod wheel");
  GetParam(kParamLfo1LevModAmt)->InitInt("LFO 1 Lev Mod Amt", 0, -63, 63);
  GetParam(kParamLfo1LevModSrc)->InitEnum("LFO 1 LevMod Src", 0, 17, "", 0, "", "OFF", "LFO1", "LFO2", "LFO1+2", "LFO1*2", "LFO1*MW", "LFO1*AT", "LFO2*MW", "LFO2*AT", "Filter Env", "Amp Env", "Free Env +", "Free Env -", "Key follow", "Velocity", "AfterTouch", "Mod wheel");

  GetParam(kParamLfo2Wave)->InitEnum("LFO 2 Waveform", 0, 6, "", 0, "", "Sine", "Rectangle", "Triangle", "Sawtooth Up", "Sawtooth Down", "Noise");
  GetParam(kParamLfo2Rate)->InitInt("LFO 2 Rate", 1, 1, 20);
  GetParam(kParamLfo2RateBPM)->InitEnum("LFO 2 Rate BPM", 0, 19, "", 0, "", "1/1", "1/2P", "1/2", "1/2T", "1/4P", "1/4", "1/4T", "1/8P", "1/8", "1/8T", "1/16P", "1/16", "1/16T", "1/32P", "1/32", "1/32T", "1/64P", "1/64", "1/64T");
  GetParam(kParamLfo2Retrig)->InitBool("LFO 2 Retrig", false);
  GetParam(kParamLfo2Del)->InitInt("LFO 2 Del", 0, 0, 127);
  GetParam(kParamLfo2Fin)->InitInt("LFO 2 F In", 0, 0, 127);
  GetParam(kParamLfo2Fout)->InitInt("LFO 2 F Out", 0, 0, 127);
  GetParam(kParamLfo2Midi)->InitBool("LFO 2 MIDI", false);
  GetParam(kParamLfo2Phase)->InitInt("LFO 2 Phase", 0, -180, 180);
  GetParam(kParamLfo2Keyf)->InitInt("LFO 2 Keyf", 0, -200, 200);
  GetParam(kParamLfo2Rmod1Amt)->InitInt("LFO 2 R Mod 1 Amt", 0, -63, 63);
  GetParam(kParamLfo2Rmod2Amt)->InitInt("LFO 2 R Mod 2 Amt", 0, -63, 63);
  GetParam(kParamLfo2Rmod1Src)->InitEnum("LFO 2 R Mod 1 Src", 0, 17, "", 0, "", "OFF", "LFO1", "LFO2", "LFO1+2", "LFO1*2", "LFO1*MW", "LFO1*AT", "LFO2*MW", "LFO2*AT", "Filter Env", "Amp Env", "Free Env +", "Free Env -", "Key follow", "Velocity", "AfterTouch", "Mod wheel");
  GetParam(kParamLfo2Rmod2Src)->InitEnum("LFO 2 R Mod 2 Src", 0, 17, "", 0, "", "OFF", "LFO1", "LFO2", "LFO1+2", "LFO1*2", "LFO1*MW", "LFO1*AT", "LFO2*MW", "LFO2*AT", "Filter Env", "Amp Env", "Free Env +", "Free Env -", "Key follow", "Velocity", "AfterTouch", "Mod wheel");
  GetParam(kParamLfo2LevModAmt)->InitInt("LFO 2 Lev Mod Amt", 0, -63, 63);
  GetParam(kParamLfo2LevModSrc)->InitEnum("LFO 2 LevMod Src", 0, 17, "", 0, "", "OFF", "LFO1", "LFO2", "LFO1+2", "LFO1*2", "LFO1*MW", "LFO1*AT", "LFO2*MW", "LFO2*AT", "Filter Env", "Amp Env", "Free Env +", "Free Env -", "Key follow", "Velocity", "AfterTouch", "Mod wheel");


  GetParam(kParamFreeEnvTKf)->InitInt("Free Env TKf", 0, -200, 200);
  GetParam(kParamFreeEnvTVel)->InitInt("Free Env TVel", 0, -200, 200);
  GetParam(kParamFreeEnvLVel)->InitInt("Free Env LVel", 0, -0, 127);
  GetParam(kParamFreeEnvA)->InitInt("Free Env Attack", 0, 0, 127);
  GetParam(kParamFreeEnvD)->InitInt("Free Env Decay", 0, 0, 127);
  GetParam(kParamFreeEnvS)->InitInt("Free Env Sustain", 0, 0, 127);
  GetParam(kParamFreeEnvR)->InitInt("Free Env Release", 0, 0, 127);
  GetParam(kParamFreeEnvAI)->InitInt("Free Env AI", 0, 0, 127);
  GetParam(kParamFreeEnvDR)->InitInt("Free Env DR", 0, 0, 127);

    paramToCC[kParamOsc1Waveform            ] = 48;
    paramToCC[kParamOsc1Coarse              ] = 51;
    paramToCC[kParamOsc1Fine                ] = 59;
    paramToCC[kParamOsc1Grunge              ] = 81;
    paramToCC[kParamOsc1PitchModSrc         ] = 49;
    paramToCC[kParamOsc1PitchModAmt         ] = 21;
    paramToCC[kParamOsc2Waveform            ] = 22;
    paramToCC[kParamOsc2Coarse              ] = 23;
    paramToCC[kParamOsc2Fine                ] = 24;
    paramToCC[kParamOsc2Grunge              ] = 25;
    paramToCC[kParamOsc2PitchModSrc         ] = 26;
    paramToCC[kParamOsc2PitchModAmt         ] = 27;

    paramToCC[kParamMixOsc1               ] = 28;
    paramToCC[kParamMixOsc1AmpModSrc      ] = 29;
    paramToCC[kParamMixOsc1AmpModAmt      ] = 30;
    paramToCC[kParamMixOsc1Balance        ] = 31;
    paramToCC[kParamMixOsc1BalanceModSrc  ] = 33;
    paramToCC[kParamMixOsc1BalanceModAmt  ] = 34;
    paramToCC[kParamMixOsc2               ] = 35;
    paramToCC[kParamMixOsc2AmpModSrc      ] = 36;
    paramToCC[kParamMixOsc2AmpModAmt      ] = 37;
    paramToCC[kParamMixOsc2Balance        ] = 66;
    paramToCC[kParamMixOsc2BalanceModSrc  ] = 39;
    paramToCC[kParamMixOsc2BalanceModAmt  ] = 40;
    paramToCC[kParamMixGain               ] = 4;

    paramToCC[kParamVcf1Cf        ] = 57;
    paramToCC[kParamVcf1Res       ] = 58;
    paramToCC[kParamVcf1keyf      ] = 59;
    paramToCC[kParamVcf1Env       ] = 60;
    paramToCC[kParamVcf1Type      ] = 47;
    paramToCC[kParamVcf1ModCfAmt  ] = 53;
    paramToCC[kParamVcf1ModResAmt ] = 55;
    paramToCC[kParamVcf1ModCfSrc  ] = 52;
    paramToCC[kParamVcf1ModResSrc ] = 54;

    paramToCC[kParamVcf2Cf       ] = 74;
    paramToCC[kParamVcf2Res      ] = 71;
    paramToCC[kParamVcf2keyf     ] = 72;
    paramToCC[kParamVcf2Env      ] = 73;
    paramToCC[kParamVcf2Type     ] = 56;
    paramToCC[kParamVcf2ModCfAmt ] = 62;
    paramToCC[kParamVcf2ModResAmt] = 119;
    paramToCC[kParamVcf2ModCfSrc ] = 61;
    paramToCC[kParamVcf2ModResSrc] = 63;

    paramToCC[kParamVcfSerPar      ] = 41;
    paramToCC[kParamVcfLink        ] = -1;
    paramToCC[kParamVcfCutoffModSrc] = 43;
    paramToCC[kParamVcfCutoffModAmt] = 44;
    paramToCC[kParamVcfResModSrc   ] = 45;
    paramToCC[kParamVcfResModAmt   ] = 46;

    paramToCC[kParamVcfEnvTKf     ] = 82;
    paramToCC[kParamVcfEnvTVel    ] = 83;
    paramToCC[kParamVcfEnvLVel    ] = 84;
    paramToCC[kParamVcfEnvA       ] = 17;
    paramToCC[kParamVcfEnvD       ] = 18;
    paramToCC[kParamVcfEnvS       ] = 19;
    paramToCC[kParamVcfEnvR       ] = 20;

    paramToCC[kParamAmpVol        ] = 11;
    paramToCC[kParamAmpPan        ] = 78;
    paramToCC[kParamAmpPanModSrc  ] = 79;
    paramToCC[kParamAmpPanModAmt  ] = 80;
    paramToCC[kParamAmpPan1       ] = 75;
    paramToCC[kParamAmpPanModSrc1 ] = 76;
    paramToCC[kParamAmpPanModAmt1 ] = 77;

    paramToCC[kParamAmpEnvTKf    ] = 85;
    paramToCC[kParamAmpEnvTVel   ] = 86;
    paramToCC[kParamAmpEnvLVel   ] = 87;
    paramToCC[kParamAmpEnvA      ] = 13;
    paramToCC[kParamAmpEnvD      ] = 14;
    paramToCC[kParamAmpEnvS      ] = 15;
    paramToCC[kParamAmpEnvR      ] = 16;

    // add
    paramToCC[kParamCoarse    ] = 65;
    paramToCC[kParamFine      ] = 8;
    paramToCC[kParamBendRange ] = 3;
    paramToCC[kParamPModAmt   ] = 42;
    paramToCC[kParamPModSrc   ] = 9;

    paramToCC[kParamLfo1Wave       ] = 88;
    paramToCC[kParamLfo1Rate       ] = 89;
    paramToCC[kParamLfo1RateBPM     ] = 103;
    paramToCC[kParamLfo1Retrig     ] = 90;
    paramToCC[kParamLfo1Del        ] = 92;
    paramToCC[kParamLfo1Fin        ] = 70;
    paramToCC[kParamLfo1Fout       ] = 94;
    paramToCC[kParamLfo1Midi       ] = 102;
    paramToCC[kParamLfo1Phase      ] = 69;
    paramToCC[kParamLfo1Keyf       ] = 95;
    paramToCC[kParamLfo1Rmod1Amt   ] = 97;
    paramToCC[kParamLfo1Rmod2Amt   ] = 68;
    paramToCC[kParamLfo1Rmod1Src   ] = 96;
    paramToCC[kParamLfo1Rmod2Src   ] = 67;
    paramToCC[kParamLfo1LevModAmt  ] = 101;
    paramToCC[kParamLfo1LevModSrc  ] = 100;

    paramToCC[kParamLfo2Wave       ] = 104;
    paramToCC[kParamLfo2Rate       ] = 105;
    paramToCC[kParamLfo2RateBPM    ] = 118;
    paramToCC[kParamLfo2Retrig     ] = 106;
    paramToCC[kParamLfo2Del        ] = 108;
    paramToCC[kParamLfo2Fin        ] = 109;
    paramToCC[kParamLfo2Fout       ] = 110;
    paramToCC[kParamLfo2Midi       ] = 2;
    paramToCC[kParamLfo2Phase      ] = 107;
    paramToCC[kParamLfo2Keyf       ] = 111;
    paramToCC[kParamLfo2Rmod1Amt   ] = 113;
    paramToCC[kParamLfo2Rmod2Amt   ] = 115;
    paramToCC[kParamLfo2Rmod1Src   ] = 112;
    paramToCC[kParamLfo2Rmod2Src   ] = 114;
    paramToCC[kParamLfo2LevModAmt  ] = 117;
    paramToCC[kParamLfo2LevModSrc  ] = 116;

    paramToCC[kParamFreeEnvTKf    ] = 114;
    paramToCC[kParamFreeEnvTVel   ] = 115;
    paramToCC[kParamFreeEnvLVel   ] = 116;
    paramToCC[kParamFreeEnvA      ] = 110;
    paramToCC[kParamFreeEnvD      ] = 111;
    paramToCC[kParamFreeEnvS      ] = 112;
    paramToCC[kParamFreeEnvR      ] = 113;
    paramToCC[kParamFreeEnvAI     ] = 117;
    paramToCC[kParamFreeEnvDR     ] = 118;

    paramToCC[kParamPitchWheel] = 1;

    paramToMsgType[kParamOsc1Waveform             ] = 0;
    paramToMsgType[kParamOsc1Coarse              ] = 0;
    paramToMsgType[kParamOsc1Fine                ] = 1;
    paramToMsgType[kParamOsc1Grunge              ] = 0;
    paramToMsgType[kParamOsc1PitchModSrc         ] = 0;
    paramToMsgType[kParamOsc1PitchModAmt         ] = 0;
    paramToMsgType[kParamOsc2Waveform            ] = 0;
    paramToMsgType[kParamOsc2Coarse              ] = 0;
    paramToMsgType[kParamOsc2Fine                ] = 0;
    paramToMsgType[kParamOsc2Grunge              ] = 0;
    paramToMsgType[kParamOsc2PitchModSrc         ] = 0;
    paramToMsgType[kParamOsc2PitchModAmt         ] = 0;

    paramToMsgType[kParamMixOsc1               ] = 0;
    paramToMsgType[kParamMixOsc1AmpModSrc      ] = 0;
    paramToMsgType[kParamMixOsc1AmpModAmt      ] = 0;
    paramToMsgType[kParamMixOsc1Balance        ] = 0;
    paramToMsgType[kParamMixOsc1BalanceModSrc  ] = 0;
    paramToMsgType[kParamMixOsc1BalanceModAmt  ] = 0;
    paramToMsgType[kParamMixOsc2               ] = 0;
    paramToMsgType[kParamMixOsc2AmpModSrc      ] = 0;
    paramToMsgType[kParamMixOsc2AmpModAmt      ] = 0;
    paramToMsgType[kParamMixOsc2Balance        ] = 0;
    paramToMsgType[kParamMixOsc2BalanceModSrc  ] = 0;
    paramToMsgType[kParamMixOsc2BalanceModAmt  ] = 0;
    paramToMsgType[kParamMixGain               ] = 0;

    paramToMsgType[kParamVcf1Cf        ] = 0;
    paramToMsgType[kParamVcf1Res       ] = 0;
    paramToMsgType[kParamVcf1keyf      ] = 0;
    paramToMsgType[kParamVcf1Env       ] = 0;
    paramToMsgType[kParamVcf1Type      ] = 0;
    paramToMsgType[kParamVcf1ModCfAmt  ] = 0;
    paramToMsgType[kParamVcf1ModResAmt ] = 0;
    paramToMsgType[kParamVcf1ModCfSrc  ] = 0;
    paramToMsgType[kParamVcf1ModResSrc ] = 0;

    paramToMsgType[kParamVcf2Cf       ] = 0;
    paramToMsgType[kParamVcf2Res      ] = 0;
    paramToMsgType[kParamVcf2keyf     ] = 0;
    paramToMsgType[kParamVcf2Env      ] = 0;
    paramToMsgType[kParamVcf2Type     ] = 0;
    paramToMsgType[kParamVcf2ModCfAmt ] = 0;
    paramToMsgType[kParamVcf2ModResAmt] = 1;
    paramToMsgType[kParamVcf2ModCfSrc ] = 0;
    paramToMsgType[kParamVcf2ModResSrc] = 0;

    paramToMsgType[kParamVcfSerPar      ] = 0;
    paramToMsgType[kParamVcfLink        ] = 0;
    paramToMsgType[kParamVcfCutoffModSrc] = 0;
    paramToMsgType[kParamVcfCutoffModAmt] = 0;
    paramToMsgType[kParamVcfResModSrc   ] = 0;
    paramToMsgType[kParamVcfResModAmt   ] = 0;

    paramToMsgType[kParamVcfEnvTKf     ] = 0;
    paramToMsgType[kParamVcfEnvTVel    ] = 0;
    paramToMsgType[kParamVcfEnvLVel    ] = 0;
    paramToMsgType[kParamVcfEnvA       ] = 0;
    paramToMsgType[kParamVcfEnvD       ] = 0;
    paramToMsgType[kParamVcfEnvS       ] = 0;
    paramToMsgType[kParamVcfEnvR       ] = 0;

    paramToMsgType[kParamAmpVol        ] = 0;
    paramToMsgType[kParamAmpPan        ] = 0;
    paramToMsgType[kParamAmpPanModSrc  ] = 0;
    paramToMsgType[kParamAmpPanModAmt  ] = 0;
    paramToMsgType[kParamAmpPan1       ] = 0;
    paramToMsgType[kParamAmpPanModSrc1 ] = 0;
    paramToMsgType[kParamAmpPanModAmt1 ] = 0;

    paramToMsgType[kParamAmpEnvTKf    ] = 0;
    paramToMsgType[kParamAmpEnvTVel   ] = 0;
    paramToMsgType[kParamAmpEnvLVel   ] = 0;
    paramToMsgType[kParamAmpEnvA      ] = 0;
    paramToMsgType[kParamAmpEnvD      ] = 0;
    paramToMsgType[kParamAmpEnvS      ] = 0;
    paramToMsgType[kParamAmpEnvR      ] = 0;

    // add
    paramToMsgType[kParamCoarse    ] = 0;
    paramToMsgType[kParamFine      ] = 0;
    paramToMsgType[kParamBendRange ] = 0;
    paramToMsgType[kParamPModAmt   ] = 0;
    paramToMsgType[kParamPModSrc   ] = 0;

    paramToMsgType[kParamLfo1Wave       ] = 0;
    paramToMsgType[kParamLfo1Rate       ] = 0;
    paramToMsgType[kParamLfo1RateBPM    ] = 0;
    paramToMsgType[kParamLfo1Retrig     ] = 0;
    paramToMsgType[kParamLfo1Del        ] = 0;
    paramToMsgType[kParamLfo1Fin        ] = 0;
    paramToMsgType[kParamLfo1Fout       ] = 0;
    paramToMsgType[kParamLfo1Midi       ] = 0;
    paramToMsgType[kParamLfo1Phase      ] = 0;
    paramToMsgType[kParamLfo1Keyf       ] = 0;
    paramToMsgType[kParamLfo1Rmod1Amt   ] = 0;
    paramToMsgType[kParamLfo1Rmod2Amt   ] = 0;
    paramToMsgType[kParamLfo1Rmod1Src   ] = 0;
    paramToMsgType[kParamLfo1Rmod2Src   ] = 0;
    paramToMsgType[kParamLfo1LevModAmt  ] = 0;
    paramToMsgType[kParamLfo1LevModSrc  ] = 0;

    paramToMsgType[kParamLfo2Wave       ] = 0;
    paramToMsgType[kParamLfo2Rate       ] = 0;
    paramToMsgType[kParamLfo2RateBPM    ] = 0;
    paramToMsgType[kParamLfo2Retrig     ] = 0;
    paramToMsgType[kParamLfo2Del        ] = 0;
    paramToMsgType[kParamLfo2Fin        ] = 0;
    paramToMsgType[kParamLfo2Fout       ] = 0;
    paramToMsgType[kParamLfo2Midi       ] = 0;
    paramToMsgType[kParamLfo2Phase      ] = 0;
    paramToMsgType[kParamLfo2Keyf       ] = 0;
    paramToMsgType[kParamLfo2Rmod1Amt   ] = 0;
    paramToMsgType[kParamLfo2Rmod2Amt   ] = 0;
    paramToMsgType[kParamLfo2Rmod1Src   ] = 0;
    paramToMsgType[kParamLfo2Rmod2Src   ] = 0;
    paramToMsgType[kParamLfo2LevModAmt  ] = 0;
    paramToMsgType[kParamLfo2LevModSrc  ] = 0;

    paramToMsgType[kParamFreeEnvTKf    ] = 1;
    paramToMsgType[kParamFreeEnvTVel   ] = 1;
    paramToMsgType[kParamFreeEnvLVel   ] = 1;
    paramToMsgType[kParamFreeEnvA      ] = 1;
    paramToMsgType[kParamFreeEnvD      ] = 1;
    paramToMsgType[kParamFreeEnvS      ] = 1;
    paramToMsgType[kParamFreeEnvR      ] = 1;
    paramToMsgType[kParamFreeEnvAI     ] = 1;
    paramToMsgType[kParamFreeEnvDR     ] = 1;

    paramToMsgType[kParamPitchWheel] = 0;

 
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
    IControl* pBG = new IPanelControl(IRECT(0, 0, HSM_W, HSK_H), IColor(255, 58, 58, 58));
    pGraphics->AttachControl(pBG);

    const IRECT controls = b.GetGridCell(1, 2, 2);

    IBitmap bitmap;

    bitmap = pGraphics->LoadBitmap(FN_MPA);
    IControl* logoCtrl = new IBitmapControl(HS_W + 40, HS_H + 28, bitmap, kNoParameter);
    pGraphics->AttachControl(logoCtrl, -1, "");

    bitmap = pGraphics->LoadBitmap(FN_LIGHTWAVE);
    IControl* backCtrl = new IBitmapControl(0, 0, bitmap, kNoParameter);
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

    float cw = 22; float ch = 13;

    std::function<double(double)> mappingFuncModSrc = [&](double midiVal) {return GetUI()->GetDelegate()->GetParam(kParamOsc1PitchModSrc)->ToNormalized(midiVal * 127.); };

    pGraphics->AttachControl(new ICaptionControlSubMidi(IRECT(31, 74, 139, 91), kParamOsc1Waveform, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new ICaptionControlSubMidi(IRECT(31, 222, 139, 239), kParamOsc2Waveform, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(31, 155, 101+2, 172), kParamOsc1PitchModSrc, DEFAULT_TEXT, COLOR_WHITE, true, mappingFuncModSrc), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(31, 303, 101+2, 320), kParamOsc2PitchModSrc, DEFAULT_TEXT, COLOR_WHITE, true, mappingFuncModSrc), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(166, 97, 238, 114), kParamMixOsc1AmpModSrc, DEFAULT_TEXT, COLOR_WHITE, true, mappingFuncModSrc), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(166, 214,238, 231), kParamMixOsc2AmpModSrc, DEFAULT_TEXT, COLOR_WHITE, true, mappingFuncModSrc), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(166, 154,238, 171), kParamMixOsc1BalanceModSrc, DEFAULT_TEXT, COLOR_WHITE, true, mappingFuncModSrc), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(166, 267,238, 284), kParamMixOsc2BalanceModSrc, DEFAULT_TEXT, COLOR_WHITE, true, mappingFuncModSrc), -1, "main");

    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(296-3, 140, 366+2-3, 157), kParamVcf1ModCfSrc, DEFAULT_TEXT, COLOR_WHITE, true, mappingFuncModSrc), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(296-3, 162, 366+2-3, 179), kParamVcf1ModResSrc, DEFAULT_TEXT, COLOR_WHITE, true, mappingFuncModSrc), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(296-3, 140+143, 366+2-3, 157+143), kParamVcf2ModCfSrc, DEFAULT_TEXT, COLOR_WHITE, true, mappingFuncModSrc), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(296-3, 162+143, 366+2-3, 179+143), kParamVcf2ModCfSrc, DEFAULT_TEXT, COLOR_WHITE, true, mappingFuncModSrc), -1, "main");

    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(458, 199, 525, 216), kParamVcfCutoffModSrc, DEFAULT_TEXT, COLOR_WHITE, true, mappingFuncModSrc), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(458, 199+69, 525, 216+69), kParamVcfResModSrc, DEFAULT_TEXT, COLOR_WHITE, true, mappingFuncModSrc), -1, "main");

    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(532, 217, 604, 234), kParamAmpPanModSrc, DEFAULT_TEXT, COLOR_WHITE, true, mappingFuncModSrc), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(532, 194, 604, 211), kParamAmpPanModSrc1, DEFAULT_TEXT, COLOR_WHITE, true, mappingFuncModSrc), -1, "main par");

    std::function<double(double)> mappingFuncVCFType = [&](double midiVal) {return GetUI()->GetDelegate()->GetParam(kParamVcf1Type)->ToNormalized(midiVal * 127.); };
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(364, 56, 434, 73), kParamVcf1Type, DEFAULT_TEXT, COLOR_WHITE, true, mappingFuncVCFType), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(364, 56+143, 434, 73+143), kParamVcf2Type, DEFAULT_TEXT, COLOR_WHITE, true, mappingFuncVCFType), -1, "main");

    // IKnobs Main Green

    IBitmap knob = pGraphics->LoadBitmap(FN_GREENLW, 31, true);

    std::function<double(double)> mappingModAmt = [&](double midiVal) {return GetUI()->GetDelegate()->GetParam(kParamOsc1PitchModAmt)->ToNormalized(midiVal * 127. - 63.); };
    pGraphics->AttachControl(new IBKnobControlMidi(107, 154, knob, kParamOsc1PitchModAmt, mappingModAmt), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(131, 158), kParamOsc1PitchModAmt, DEFAULT_TEXT, COLOR_WHITE, true, mappingModAmt), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(107, 302, knob, kParamOsc2PitchModAmt, mappingModAmt), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(131, 306), kParamOsc2PitchModAmt, DEFAULT_TEXT, COLOR_WHITE, true, mappingModAmt), -1, "main");

    pGraphics->AttachControl(new IBKnobControlMidi(241, 96, knob, kParamMixOsc1AmpModAmt, mappingModAmt), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(263, 99), kParamMixOsc1AmpModAmt, DEFAULT_TEXT, COLOR_WHITE, true, mappingModAmt), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(241, 213, knob, kParamMixOsc2AmpModAmt, mappingModAmt), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(263, 217), kParamMixOsc2AmpModAmt, DEFAULT_TEXT, COLOR_WHITE, true, mappingModAmt), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(241, 153, knob, kParamMixOsc1BalanceModAmt, mappingModAmt), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(263, 155), kParamMixOsc1BalanceModAmt, DEFAULT_TEXT, COLOR_WHITE, true, mappingModAmt), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(241, 266, knob, kParamMixOsc2BalanceModAmt, mappingModAmt), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(263, 269), kParamMixOsc2BalanceModAmt, DEFAULT_TEXT, COLOR_WHITE, true, mappingModAmt), -1, "main");

    std::function<double(double)> mappingFunckeyf = [&](double midiVal) {return GetUI()->GetDelegate()->GetParam(kParamVcf1keyf)->ToNormalized(400.*midiVal - 200.); };
    pGraphics->AttachControl(new IBKnobControlMidi(375, 91, knob, kParamVcf1keyf, mappingFunckeyf), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(374, 116), kParamVcf1keyf, DEFAULT_TEXT, COLOR_WHITE, true, mappingFunckeyf), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(415, 91, knob, kParamVcf1Env, mappingModAmt), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(414, 116), kParamVcf1Env, DEFAULT_TEXT, COLOR_WHITE, true, mappingModAmt), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(368, 139, knob, kParamVcf1ModCfAmt, mappingModAmt), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(414, 143), kParamVcf1ModCfAmt, DEFAULT_TEXT, COLOR_WHITE, true, mappingModAmt), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(368, 161, knob, kParamVcf1ModResAmt, mappingModAmt), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(414, 163), kParamVcf1ModResAmt, DEFAULT_TEXT, COLOR_WHITE, true, mappingModAmt), -1, "main");

    pGraphics->AttachControl(new IBKnobControlMidi(375, 91 + 143, knob, kParamVcf2keyf, mappingFunckeyf), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(374, 116+143), kParamVcf2keyf, DEFAULT_TEXT, COLOR_WHITE, true, mappingFunckeyf), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(415, 91 + 143, knob, kParamVcf2Env, mappingModAmt), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(414, 116+143), kParamVcf2Env, DEFAULT_TEXT, COLOR_WHITE, true, mappingModAmt), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(368, 139 + 143, knob, kParamVcf2ModCfAmt, mappingModAmt), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(414, 143+143), kParamVcf2ModCfAmt, DEFAULT_TEXT, COLOR_WHITE, true, mappingModAmt), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(368, 161 + 143, knob, kParamVcf2ModResAmt, mappingModAmt), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(414, 163+143), kParamVcf2ModResAmt, DEFAULT_TEXT, COLOR_WHITE, true, mappingModAmt), -1, "main");

    pGraphics->AttachControl(new IBKnobControlMidi(537, 285 - 197, knob, kParamVcfEnvTKf, mappingFunckeyf), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(536, 113), kParamVcfEnvTKf, DEFAULT_TEXT, COLOR_WHITE, true, mappingFunckeyf), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(569, 285 - 197, knob, kParamVcfEnvTVel, mappingFunckeyf), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(568, 113), kParamVcfEnvTVel, DEFAULT_TEXT, COLOR_WHITE, true, mappingFunckeyf), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(601, 285 - 197, knob, kParamVcfEnvLVel), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(599, 113), kParamVcfEnvLVel, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");

    pGraphics->AttachControl(new IBKnobControlMidi(537, 285, knob, kParamAmpEnvTKf, mappingFunckeyf), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(536, 311), kParamAmpEnvTKf, DEFAULT_TEXT, COLOR_WHITE, true, mappingFunckeyf), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(569, 285, knob, kParamAmpEnvTVel, mappingFunckeyf), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(567, 311), kParamAmpEnvTVel, DEFAULT_TEXT, COLOR_WHITE, true, mappingFunckeyf), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(601, 285, knob, kParamAmpEnvLVel), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(598, 311), kParamAmpEnvLVel, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");

    pGraphics->AttachControl(new IBKnobControlMidi(659, 214, knob, kParamAmpPanModAmt, mappingModAmt), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(683, 217), kParamAmpPanModAmt, DEFAULT_TEXT, COLOR_WHITE, true, mappingModAmt), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(659, 190, knob, kParamAmpPanModAmt1, mappingModAmt), -1, "main par");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(683, 193), kParamAmpPanModAmt1, DEFAULT_TEXT, COLOR_WHITE, true, mappingModAmt), -1, "main par");
    pGraphics->AttachControl(new IBKnobControlMidi(464, 224, knob, kParamVcfCutoffModAmt, mappingModAmt), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(494, 227), kParamVcfCutoffModAmt, DEFAULT_TEXT, COLOR_WHITE, true, mappingModAmt), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(464, 292, knob, kParamVcfResModAmt, mappingModAmt), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(494, 296), kParamVcfResModAmt, DEFAULT_TEXT, COLOR_WHITE, true, mappingModAmt), -1, "main");


    // IKnobs Main Blue

    knob = pGraphics->LoadBitmap(FN_BLUELW, 31, true);

    
    std::function<double(double)> mappingFuncCoarse = [&](double midiVal) {return GetUI()->GetDelegate()->GetParam(kParamOsc1Coarse)->ToNormalized(midiVal * 127. - 48.); };
    pGraphics->AttachControl(new IBKnobControlMidi(37, 108, knob, kParamOsc1Coarse, mappingFuncCoarse), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(37, 134), kParamOsc1Coarse, IText(14, COLOR_BLACK, nullptr, EAlign::Center), COLOR_WHITE, true, mappingFuncCoarse), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(71, 108, knob, kParamOsc1Fine), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(70, 134), kParamOsc1Fine, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(107, 109, knob, kParamOsc1Grunge), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(105, 134), kParamOsc1Grunge, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");

    pGraphics->AttachControl(new IBKnobControlMidi(37, 257, knob, kParamOsc2Coarse, mappingFuncCoarse), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(37, 134+149), kParamOsc2Coarse, DEFAULT_TEXT, COLOR_WHITE, true, mappingFuncCoarse), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(71, 257, knob, kParamOsc2Fine), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(70, 134 + 149), kParamOsc2Fine, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(107, 257, knob, kParamOsc2Grunge), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(105, 134 + 149), kParamOsc2Grunge, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");

    pGraphics->AttachControl(new IBKnobControlMidi(241, 71, knob, kParamMixOsc1), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(263, 75), kParamMixOsc1, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(241, 128, knob, kParamMixOsc1Balance, mappingModAmt), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(263, 131), kParamMixOsc1Balance, DEFAULT_TEXT, COLOR_WHITE, true, mappingModAmt), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(241, 188, knob, kParamMixOsc2), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(263, 192), kParamMixOsc2, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(241, 241, knob, kParamMixOsc2Balance, mappingModAmt), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(263, 244), kParamMixOsc2Balance, DEFAULT_TEXT, COLOR_WHITE, true, mappingModAmt), -1, "main");

    pGraphics->AttachControl(new IBKnobControlMidi(241, 304, knob, kParamMixGain), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(263, 307), kParamMixGain, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");

    pGraphics->AttachControl(new IBKnobControlMidi(659, 140, knob, kParamAmpVol), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(683, 142), kParamAmpVol, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(659, 165, knob, kParamAmpPan, mappingModAmt), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(683, 168), kParamAmpPan, DEFAULT_TEXT, COLOR_WHITE, true, mappingModAmt), -1, "main");
    pGraphics->AttachControl(new IBKnobControlMidi(568, 165, knob, kParamAmpPan1, mappingModAmt), -1, "main par");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(594, 168), kParamAmpPan1, DEFAULT_TEXT, COLOR_WHITE, true, mappingModAmt), -1, "main par");

    // IKnobs Main Redl

    knob = pGraphics->LoadBitmap(FN_REDLW, 31, true);

    IBKnobControlMidi* cf1control = new IBKnobControlMidi(302, 91, knob, kParamVcf1Cf);
    cf1control->SetActionFunction([&](IControl* ctrl) {
      if (GetUI()->GetControlWithTag(kCtrlTagVcfLink)->GetValue() == 1) {
        GetUI()->GetControlWithTag(kCtrlTagVcf2Cf)->SetValueFromUserInput(ctrl->GetValue());
      }
      });
    pGraphics->AttachControl(cf1control, kCtrlTagVcf1Cf, "main");

    ICaptionControlMidi* capCf1Ctrl = new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(301, 116), kParamVcf1Cf, DEFAULT_TEXT, COLOR_WHITE, true);
    capCf1Ctrl->SetActionFunction([&](IControl* ctrl) {
      if (GetUI()->GetControlWithTag(kCtrlTagVcfLink)->GetValue() == 1) {
        GetUI()->GetControlWithTag(kCtrlTagVcf2Cf)->SetValueFromUserInput(ctrl->GetValue());
      }
      });
    pGraphics->AttachControl(capCf1Ctrl, -1, "main");
    

    pGraphics->AttachControl(new IBKnobControlMidi(334, 91, knob, kParamVcf1Res), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(334, 116), kParamVcf1Res, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");

    IBKnobControlMidi* cf2control = new IBKnobControlMidi(302, 91 + 143, knob, kParamVcf2Cf);
    cf2control->SetActionFunction([&](IControl* ctrl) {
      if (GetUI()->GetControlWithTag(kCtrlTagVcfLink)->GetValue() == 1) {
        GetUI()->GetControlWithTag(kCtrlTagVcf1Cf)->SetValueFromUserInput(ctrl->GetValue());
      }
      });
    pGraphics->AttachControl(cf2control, kCtrlTagVcf2Cf, "main");

    ICaptionControlMidi* capCf2Ctrl = new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(301, 116+143), kParamVcf2Cf, DEFAULT_TEXT, COLOR_WHITE, true);
    capCf2Ctrl->SetActionFunction([&](IControl* ctrl) {
      if (GetUI()->GetControlWithTag(kCtrlTagVcfLink)->GetValue() == 1) {
        GetUI()->GetControlWithTag(kCtrlTagVcf1Cf)->SetValueFromUserInput(ctrl->GetValue());
      }
      });
    pGraphics->AttachControl(capCf2Ctrl, -1, "main");

    pGraphics->AttachControl(new IBKnobControlMidi(334, 91+143, knob, kParamVcf2Res), -1, "main");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(334, 116+143), kParamVcf2Res, DEFAULT_TEXT, COLOR_WHITE, true), -1, "main");

    // Fader Main
    IBitmap sliderBack = pGraphics->LoadBitmap(FN_LWFADERBG1, 1);

    pGraphics->AttachControl(new IBitmapControl(630, 69-2, sliderBack), -1, "main");
    pGraphics->AttachControl(new IBitmapControl(650, 69-2, sliderBack), -1, "main");
    pGraphics->AttachControl(new IBitmapControl(670, 69-2, sliderBack), -1, "main");
    pGraphics->AttachControl(new IBitmapControl(689, 69-2, sliderBack), -1, "main");

    pGraphics->AttachControl(new IBitmapControl(630, 262-2, sliderBack), -1, "main");
    pGraphics->AttachControl(new IBitmapControl(650, 262-2, sliderBack), -1, "main");
    pGraphics->AttachControl(new IBitmapControl(670, 262-2, sliderBack), -1, "main");
    pGraphics->AttachControl(new IBitmapControl(689, 262-2, sliderBack), -1, "main");


    IBitmap slider = pGraphics->LoadBitmap(FN_LWSLIDER2, 1);
    pGraphics->AttachControl(new IBSliderControlMidi(630, 69-2, 46, kParamVcfEnvA, slider), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(650, 69-2, 46, kParamVcfEnvD, slider), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(670, 69-2, 46, kParamVcfEnvS, slider), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(689, 69-2, 46, kParamVcfEnvR, slider), -1, "main");

    pGraphics->AttachControl(new IBSliderControlMidi(630, 262-2, 46, kParamAmpEnvA, slider), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(650, 262-2, 46, kParamAmpEnvD, slider), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(670, 262-2, 46, kParamAmpEnvS, slider), -1, "main");
    pGraphics->AttachControl(new IBSliderControlMidi(689, 262-2, 46, kParamAmpEnvR, slider), -1, "main");

    IBitmap linkButton = pGraphics->LoadBitmap(FN_SQUAREBUTTON, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(484, 131, linkButton, kParamVcfLink), kCtrlTagVcfLink, "main");

    pGraphics->AttachControl(new IBitmapControl(535, 168, pGraphics->LoadBitmap(FN_PAN1)), -1, "main par");
    pGraphics->AttachControl(new IBitmapControl(624, 168, pGraphics->LoadBitmap(FN_PAN2)), -1, "main par");
    pGraphics->AttachControl(new IBitmapControl(605, 195, pGraphics->LoadBitmap(FN_PAN1MOD)), -1, "main par");
    pGraphics->AttachControl(new IBitmapControl(605, 219, pGraphics->LoadBitmap(FN_PAN2MOD)), -1, "main par");

    IBitmap serpar = pGraphics->LoadBitmap(FN_SERPAR, 2);
    auto serparFunc = [](IControl* pCaller) {
      if (pCaller->GetUI()) {

        if (pCaller->GetParam()->Value() == 0)
        {
          pCaller->GetUI()->ForControlInGroup("main par", [&](IControl& control) { control.Hide(true); });
        }
        else if (pCaller->GetParam()->Value() == 1)
        {
          pCaller->GetUI()->ForControlInGroup("main par", [&](IControl& control) { control.Hide(false); });
        }
      }
    };
    pGraphics->AttachControl(new ExclusiveSwitchControl(470, 82, serpar, kParamVcfSerPar, serparFunc), -1, "main");
    pGraphics->ForControlInGroup("main par", [&](IControl& control) { control.Hide(true); });

    // ICaptions Add
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(193, 117, 263, 134), kParamPModSrc, DEFAULT_TEXT, COLOR_WHITE, true, mappingFuncModSrc), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(31, 262, 101, 279), kParamLfo1Rmod1Src, DEFAULT_TEXT, COLOR_WHITE, true, mappingFuncModSrc), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(31, 286, 101, 303), kParamLfo1Rmod2Src, DEFAULT_TEXT, COLOR_WHITE, true, mappingFuncModSrc), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(215, 262, 285, 279), kParamLfo2Rmod1Src, DEFAULT_TEXT, COLOR_WHITE, true, mappingFuncModSrc), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(215, 286, 285, 303), kParamLfo2Rmod2Src, DEFAULT_TEXT, COLOR_WHITE, true, mappingFuncModSrc), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(31, 309, 101, 326), kParamLfo1LevModSrc, DEFAULT_TEXT, COLOR_WHITE, true, mappingFuncModSrc), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(215, 309, 285, 326), kParamLfo2LevModSrc, DEFAULT_TEXT, COLOR_WHITE, true, mappingFuncModSrc), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(615-4, 83, 638+4, 98), kParamMidiClockBpm, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");

    IBitmap button = pGraphics->LoadBitmap(FN_SQUAREBUTTON, 2);
    pGraphics->AttachControl(new IBSwitchControlMidi(77, 196, button, kParamLfo1Retrig), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(188, 196, button, kParamLfo1Midi), kCtrlTagLfo1Midi, "add");
    pGraphics->GetControlWithTag(kCtrlTagLfo1Midi)->SetActionFunction([](IControl* ctrl)
    {
        if (ctrl->GetUI())
        {
          if (ctrl->GetUI()->GetControlWithTag(kCtrlTagAdd)->GetValue() == 1) // nur wenn Add page
          {
            if (ctrl->GetValue() == 1)
            {
              ctrl->GetUI()->GetControlWithTag(kCtrlTagLfo1RateBPM)->Hide(false);
              ctrl->GetUI()->GetControlWithTag(kCtrlTagLfo1RateKnob)->Hide(true);
              ctrl->GetUI()->GetControlWithTag(kCtrlTagLfo1RateText)->Hide(true);
            }
            else
            {
              ctrl->GetUI()->GetControlWithTag(kCtrlTagLfo1RateBPM)->Hide(true);
              ctrl->GetUI()->GetControlWithTag(kCtrlTagLfo1RateKnob)->Hide(false);
              ctrl->GetUI()->GetControlWithTag(kCtrlTagLfo1RateText)->Hide(false);
            }
          }
        }
    }
    );

    pGraphics->AttachControl(new IBSwitchControlMidi(266, 196, button, kParamLfo2Retrig), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(376, 196, button, kParamLfo2Midi), kCtrlTagLfo2Midi, "add");
    pGraphics->GetControlWithTag(kCtrlTagLfo2Midi)->SetActionFunction([](IControl* ctrl)
      {
        if (ctrl->GetUI())
        {
          if (ctrl->GetUI()->GetControlWithTag(kCtrlTagAdd)->GetValue() == 1) // nur wenn Add page
          {
            if (ctrl->GetValue() == 1)
            {
              ctrl->GetUI()->GetControlWithTag(kCtrlTagLfo2RateBPM)->Hide(false);
              ctrl->GetUI()->GetControlWithTag(kCtrlTagLfo2RateKnob)->Hide(true);
              ctrl->GetUI()->GetControlWithTag(kCtrlTagLfo2RateText)->Hide(true);
            }
            else
            {
              ctrl->GetUI()->GetControlWithTag(kCtrlTagLfo2RateBPM)->Hide(true);
              ctrl->GetUI()->GetControlWithTag(kCtrlTagLfo2RateKnob)->Hide(false);
              ctrl->GetUI()->GetControlWithTag(kCtrlTagLfo2RateText)->Hide(false);
            }
          }
        }
      }
    );

    pGraphics->AttachControl(new IBSwitchControlMidi(453, 316, button, kParamFlangerChorus), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(508, 159, button, kParamEffectBypass), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(534, 317, button, kParamDelayCrossDual), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(688, 200, button, kParamDelayUnitLeft), -1, "add");
    pGraphics->AttachControl(new IBSwitchControlMidi(688, 260, button, kParamDelayUnitRight), -1, "add");

    // Wheel
    bitmap = pGraphics->LoadBitmap(FN_MOD_WHEEL, 14, true);
    pGraphics->AttachControl(new IBKnobControlMidi(682, 64, bitmap, kParamPitchWheel), -1, "add");

    // Wave Selector
    IBitmap waveSelector = pGraphics->LoadBitmap(FN_WAVE_SELECTOR_OFF, 1);

    pGraphics->AttachControl(new IBitmapControl(33, 155, waveSelector), -1, "add");
    pGraphics->AttachControl(new IBitmapControl(220, 155, waveSelector), -1, "add");

    waveSelector = pGraphics->LoadBitmap(FN_WAVESELECTOR, 6);
    pGraphics->AttachControl(new WaveSwitchControl(32, 155, 6, kParamLfo1Wave, waveSelector, nullptr), -1, "add");
    pGraphics->AttachControl(new WaveSwitchControl(220, 155, 6, kParamLfo2Wave, waveSelector, nullptr), -1, "add");


    // Fader Add
    sliderBack = pGraphics->LoadBitmap(FN_LWFADERBG1, 1);

    pGraphics->AttachControl(new IBitmapControl(395, 75-2, sliderBack), -1, "add");
    pGraphics->AttachControl(new IBitmapControl(415, 75-2, sliderBack), -1, "add");
    pGraphics->AttachControl(new IBitmapControl(435, 75-2, sliderBack), -1, "add");
    pGraphics->AttachControl(new IBitmapControl(455, 75-2, sliderBack), -1, "add");

    slider = pGraphics->LoadBitmap(FN_LWSLIDER2, 1);
    pGraphics->AttachControl(new IBSliderControlMidi(395, 75-2, 46, kParamFreeEnvA, slider), -1, "add");
    pGraphics->AttachControl(new IBSliderControlMidi(415, 75-2, 46, kParamFreeEnvD, slider), -1, "add");
    pGraphics->AttachControl(new IBSliderControlMidi(435, 75-2, 46, kParamFreeEnvS, slider), -1, "add");
    pGraphics->AttachControl(new IBSliderControlMidi(455, 75-2, 46, kParamFreeEnvR, slider), -1, "add");

    knob = pGraphics->LoadBitmap(FN_BLUELW, 31, true);

    pGraphics->AttachControl(new IBKnobControlMidi(41, 72, knob, kParamCoarse, mappingFuncCoarse), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(40, 98), kParamCoarse, DEFAULT_TEXT, COLOR_WHITE, true, mappingFuncCoarse), -1, "add");

    std::function<double(double)> mappingFuncFine = [&](double midiVal) {return GetUI()->GetDelegate()->GetParam(kParamFine)->ToNormalized(2.*99.*midiVal - 99.); };
    pGraphics->AttachControl(new IBKnobControlMidi(76, 72, knob, kParamFine, mappingFuncFine), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(75, 98), kParamFine, DEFAULT_TEXT, COLOR_WHITE, true, mappingFuncFine), -1, "add");

    std::function<double(double)> mappingFuncBendRange = [&](double midiVal) {return GetUI()->GetDelegate()->GetParam(kParamBendRange)->ToNormalized(midiVal*127.); };
    pGraphics->AttachControl(new IBKnobControlMidi(135, 91, knob, kParamBendRange, mappingFuncBendRange), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(162, 95), kParamBendRange, DEFAULT_TEXT, COLOR_WHITE, true, mappingFuncBendRange), -1, "add");

    std::function<double(double)> mappingFuncLfoRate = [&](double midiVal) {return GetUI()->GetDelegate()->GetParam(kParamLfo1RateBPM)->ToNormalized(midiVal*127.); };
    pGraphics->AttachControl(new IBKnobControlMidi(41, 192, knob, kParamLfo1Rate), kCtrlTagLfo1RateKnob, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(40, 217), kParamLfo1Rate, DEFAULT_TEXT, COLOR_WHITE, true), kCtrlTagLfo1RateText, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw+10, ch).GetTranslated(40-5, 217), kParamLfo1RateBPM, DEFAULT_TEXT, COLOR_WHITE, true, mappingFuncLfoRate), kCtrlTagLfo1RateBPM, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(105, 192, knob, kParamLfo1Del), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(104, 217), kParamLfo1Del, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(133, 192, knob, kParamLfo1Fin), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(132, 217), kParamLfo1Fin, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(158, 192, knob, kParamLfo1Fout), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(158, 217), kParamLfo1Fout, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(64, 239, knob, kParamLfo1Phase), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(89, 243), kParamLfo1Phase, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");

    float dx = 187;
    pGraphics->AttachControl(new IBKnobControlMidi(41 + dx, 192, knob, kParamLfo2Rate), kCtrlTagLfo2RateKnob, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(40+dx, 217), kParamLfo2Rate, DEFAULT_TEXT, COLOR_WHITE, true), kCtrlTagLfo2RateText, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw + 10, ch).GetTranslated(40 - 5+dx, 217), kParamLfo2RateBPM, DEFAULT_TEXT, COLOR_WHITE, true, mappingFuncLfoRate), kCtrlTagLfo2RateBPM, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(105 + dx, 192, knob, kParamLfo2Del), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(104+dx, 217), kParamLfo2Del, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(133 + dx, 192, knob, kParamLfo2Fin), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(132+dx, 217), kParamLfo2Fin, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(158 + dx, 192, knob, kParamLfo2Fout), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(158+dx, 217), kParamLfo2Fout, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(64 + dx, 239, knob, kParamLfo2Phase), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(89+dx, 243), kParamLfo2Phase, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");

    pGraphics->AttachControl(new IBKnobControlMidi(486, 93, knob, kParamFreeEnvAI), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(485, 117), kParamFreeEnvAI, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(517, 93, knob, kParamFreeEnvDR), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(515, 117), kParamFreeEnvDR, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");

    pGraphics->AttachControl(new IBKnobControlMidi(415, 234, knob, kParamChorusPhase), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(413, 258), kParamChorusPhase, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(417, 194, knob, kParamChorusRate), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw+10, ch).GetTranslated(441-5+5, 197), kParamChorusRate, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(479, 233, knob, kParamChorusDepth), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw+10, ch).GetTranslated(478-5, 258), kParamChorusDepth, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(415, 286, knob, kParamChorusFeedback), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw+10, ch).GetTranslated(413-5, 313), kParamChorusFeedback, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(479, 286, knob, kParamChorusWet), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw+10, ch).GetTranslated(478-5, 313), kParamChorusWet, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");

    pGraphics->AttachControl(new IBKnobControlMidi(538, 196, knob, kParamDelayTimeLMS), kCtrlTagDelayTimeLMS, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw+18, ch).GetTranslated(536 - 9, 223), kParamDelayTimeLMS, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(538, 259, knob, kParamDelayTimeRMS), kCtrlTagDelayTimeRMS, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw+18, ch).GetTranslated(536 - 9, 285), kParamDelayTimeRMS, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(589, 198, knob, kParamDelayFeedbackLeft), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw+6, ch).GetTranslated(589 - 3, 225), kParamDelayFeedbackLeft, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(621, 198, knob, kParamDelayHidampLeft), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw+6, ch).GetTranslated(619 - 3+2, 225), kParamDelayHidampLeft, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(652, 198, knob, kParamDelayLevelLeft), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw+6, ch).GetTranslated(652 - 3, 225), kParamDelayLevelLeft, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(589, 261, knob, kParamDelayFeedbackLeft), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw+6, ch).GetTranslated(589 - 3, 287), kParamDelayFeedbackLeft, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(621, 261, knob, kParamDelayHidampRight), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw+6, ch).GetTranslated(619 - 3+2, 287), kParamDelayHidampRight, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(651, 261, knob, kParamDelayLevelRight), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw+6, ch).GetTranslated(652 - 3, 287), kParamDelayLevelRight, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(658, 307, knob, kParamDelayWet), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw+6, ch).GetTranslated(686-3-2, 311), kParamDelayWet, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");

    // IKnobs Add Green

    knob = pGraphics->LoadBitmap(FN_GREENLW, 31, true);

    pGraphics->AttachControl(new IBKnobControlMidi(135, 116, knob, kParamPModAmt, mappingModAmt), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(161, 118, 184, 133), kParamPModAmt, DEFAULT_TEXT, COLOR_WHITE, true, mappingModAmt), -1, "add");

    pGraphics->AttachControl(new IBKnobControlMidi(150, 236, knob, kParamLfo1Keyf, mappingFunckeyf), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(176, 239), kParamLfo1Keyf, DEFAULT_TEXT, COLOR_WHITE, true, mappingFunckeyf), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(150, 259, knob, kParamLfo1Rmod1Amt, mappingModAmt), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(176, 262), kParamLfo1Rmod1Amt, DEFAULT_TEXT, COLOR_WHITE, true, mappingModAmt), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(150, 282, knob, kParamLfo1Rmod2Amt, mappingModAmt), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(176, 285), kParamLfo1Rmod2Amt, DEFAULT_TEXT, COLOR_WHITE, true, mappingModAmt), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(150, 305, knob, kParamLfo1LevModAmt, mappingModAmt), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(176, 308), kParamLfo1LevModAmt, DEFAULT_TEXT, COLOR_WHITE, true, mappingModAmt), -1, "add");

    pGraphics->AttachControl(new IBKnobControlMidi(150 + dx, 236, knob, kParamLfo2Keyf, mappingFunckeyf), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(176+dx, 239), kParamLfo2Keyf, DEFAULT_TEXT, COLOR_WHITE, true, mappingFunckeyf), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(150 + dx, 259, knob, kParamLfo2Rmod1Amt, mappingModAmt), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(176+dx, 262), kParamLfo2Rmod1Amt, DEFAULT_TEXT, COLOR_WHITE, true, mappingModAmt), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(150 + dx, 282, knob, kParamLfo2Rmod2Amt, mappingModAmt), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(176+dx, 285), kParamLfo2Rmod2Amt, DEFAULT_TEXT, COLOR_WHITE, true, mappingModAmt), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(150 + dx, 305, knob, kParamLfo2LevModAmt, mappingModAmt), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(176+dx, 308), kParamLfo2LevModAmt, DEFAULT_TEXT, COLOR_WHITE, true, mappingModAmt), -1, "add");

    pGraphics->AttachControl(new IBKnobControlMidi(303, 94, knob, kParamFreeEnvTKf, mappingFunckeyf), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(301, 117), kParamFreeEnvTKf, DEFAULT_TEXT, COLOR_WHITE, true, mappingFunckeyf), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(333, 94, knob, kParamFreeEnvTVel, mappingFunckeyf), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(332, 117), kParamFreeEnvTVel, DEFAULT_TEXT, COLOR_WHITE, true, mappingFunckeyf), -1, "add");
    pGraphics->AttachControl(new IBKnobControlMidi(365, 94, knob, kParamFreeEnvLVel), -1, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(0, 0, cw, ch).GetTranslated(364, 117), kParamFreeEnvLVel, DEFAULT_TEXT, COLOR_WHITE, true), -1, "add");
   
    bitmap = pGraphics->LoadBitmap(FN_TIME);
    pGraphics->AttachControl(new IBitmapControl(533, 181, bitmap, kNoParameter), -1, "add");
    pGraphics->AttachControl(new IBitmapControl(533, 246, bitmap, kNoParameter), -1, "add");

    bitmap = pGraphics->LoadBitmap(FN_BMP);
    pGraphics->AttachControl(new IBitmapControl(533, 207, bitmap, kNoParameter), kCtrlTagSkalaL, "add");
    pGraphics->AttachControl(new IBitmapControl(533, 267, bitmap, kNoParameter), kCtrlTagSkalaR, "add");
   
    
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(522, 223, 571, 240), kParamDelayTimeLBPM, DEFAULT_TEXT, COLOR_WHITE, true), kCtrlTagDelayTimeLBPM, "add");
    pGraphics->AttachControl(new ICaptionControlMidi(IRECT(522, 284, 571, 301), kParamDelayTimeRBPM, DEFAULT_TEXT, COLOR_WHITE, true), kCtrlTagDelayTimeRBPM, "add");
   
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
        if(pCaller->GetDelegate()->GetParam(kParamVcfSerPar)->Value()==1) pCaller->GetUI()->ForControlInGroup("main par", [&](IControl& control) {if (pCaller->GetTag() == kCtrlTagMain) control.Hide(false); else control.Hide(true); });
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

          if (pCaller->GetDelegate()->GetParam(kParamLfo1Midi)->Value() == 0) {
            pCaller->GetUI()->GetControlWithTag(kCtrlTagLfo1RateBPM)->Hide(true);
            pCaller->GetUI()->GetControlWithTag(kCtrlTagLfo1RateKnob)->Hide(false);
            pCaller->GetUI()->GetControlWithTag(kCtrlTagLfo1RateText)->Hide(false);

          }
          else {
            pCaller->GetUI()->GetControlWithTag(kCtrlTagLfo1RateBPM)->Hide(false);
            pCaller->GetUI()->GetControlWithTag(kCtrlTagLfo1RateKnob)->Hide(true);
            pCaller->GetUI()->GetControlWithTag(kCtrlTagLfo1RateText)->Hide(true);
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
          if (pCaller->GetDelegate()->GetParam(kParamLfo2Midi)->Value() == 0) {
            pCaller->GetUI()->GetControlWithTag(kCtrlTagLfo2RateBPM)->Hide(true);
            pCaller->GetUI()->GetControlWithTag(kCtrlTagLfo2RateKnob)->Hide(false);
            pCaller->GetUI()->GetControlWithTag(kCtrlTagLfo2RateText)->Hide(false);

          }
          else {
            pCaller->GetUI()->GetControlWithTag(kCtrlTagLfo2RateBPM)->Hide(false);
            pCaller->GetUI()->GetControlWithTag(kCtrlTagLfo2RateKnob)->Hide(true);
            pCaller->GetUI()->GetControlWithTag(kCtrlTagLfo2RateText)->Hide(true);
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

    case kParamOsc1Waveform:
    case kParamOsc2Waveform:
    case kParamOsc1PitchModSrc:
    case kParamOsc2PitchModSrc:
    case kParamMixOsc1AmpModSrc:
    case kParamMixOsc2AmpModSrc:
    case kParamMixOsc1BalanceModSrc:
    case kParamMixOsc2BalanceModSrc:
    case kParamVcf1ModCfSrc:
    case kParamVcf1ModResSrc:
    case kParamVcf2ModCfSrc:
    case kParamVcf2ModResSrc:
    case kParamVcfCutoffModSrc:
    case kParamVcfResModSrc:
    case kParamAmpPanModSrc:
    case kParamAmpPanModSrc1:
    case kParamPModSrc:
    case kParamLfo1Rmod1Src:
    case kParamLfo1Rmod2Src:
    case kParamLfo1LevModSrc:
    case kParamLfo2Rmod1Src:
    case kParamLfo2Rmod2Src:
    case kParamLfo2LevModSrc:
    case kParamVcf1Type:
    case kParamVcf2Type:
    case kParamBendRange:
    case kParamLfo1Wave:
    case kParamLfo2Wave:
    case kParamLfo1RateBPM:
    case kParamLfo2RateBPM:
      msg.mData2 = GetParam(paramIdx)->Value();
      break;
    case kParamCoarse:
    case kParamOsc1Coarse:
    case kParamOsc2Coarse:
      msg.mData2 = 48 + GetParam(paramIdx)->Value();
      break;
    case kParamEffectBypass:
      msg.mData2 = 127-127*GetParam(paramIdx)->Value();
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
      msg.mData2 = 0x06;
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
      msg.mData2 = 0x06;
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
      msg.mData2 = 0x06;
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
      msg.mData2 = 0x06;
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
