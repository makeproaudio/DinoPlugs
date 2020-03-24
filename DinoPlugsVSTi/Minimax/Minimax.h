#pragma once

#include "IPlug_include_in_plug_hdr.h"

// 0: Minimax, 1: Pro12, 2: Proddy, 3: B4000, used in Global.h Bankselect
#define PLUGIN_ID 0

#include "ParamEnum.h"
#include <array>

enum ECtrlTags
{
  #include "../MPA Code/CommonCtrlEnum.h"
  kCtrlTagSkalaL,
  kCtrlTagSkalaR,
  kCtrlTagMain,
  kCtrlTagAdd,
  kNumCtrlTags
};

#include "../MPA Code/Global.h" // must know paramToMsgType

class Minimax : public IPlug
{
public:
  Minimax(IPlugInstanceInfo instanceInfo);

#if IPLUG_DSP // All DSP methods and member variables should be within an IPLUG_DSP guard, should you want distributed UI

public:
  void ProcessBlock(sample** inputs, sample** outputs, int nFrames) override;
  void ProcessMidiMsg(const IMidiMsg& msg) override;
  void OnReset() override;
  void OnParamChange(int paramIdx) override;
  void OnIdle() override;
  void OnUIOpen() override;
  void OnUIClose() override;
  bool SerializeState(IByteChunk& chunk) const;
  int UnserializeState(const IByteChunk& chunk, int startPos);

private:
  IVKeyboardControl* keybCtrl;
  MidiMonitor::Sender<100> mMidiLoggerSender{ kCtrlTagMidiLogger };
  MidiMonitor *mMidiLogger;
  PresetList *mPresetList;
  int mChannel = 0;
  // save Button states
  int mPresetHide = 0;
  int mKeybHide = 0;
  int mMixerHide = 0;
  IMidiMsg msgAlt;
  int activeRowUser = 0;
  int activeRowFactory = 0;
  std::array<std::array<WDL_String, 4>, 100> mStrBufSave; // für reopen
  int mEntryPtrSave = 0;
  WDL_String presetname[50];
  ICaptionControl *captionCtrl;
  bool mMidiActive = false;
#endif
};
