#pragma once

#include "IPlug_include_in_plug_hdr.h"

// 0: Minimax, 1: Pro12, 2: Proddy, 3: B4000, 4: FMagia 6: Lightwave used in Global.h Bankselect
#define PLUGIN_ID 5

#include "ParamEnum.h"
#include <array>

enum ECtrlTags
{
  #include "../MPA Code/CommonCtrlEnum.h"

  kCtrlTagEditOperator1,
  kCtrlTagEditOperator2,
  kCtrlTagEditOperator3, 
  kCtrlTagEditOperator4,
  kCtrlLfoWaveform,
  kCtrlOperator1Waveform,
  kCtrlOperator2Waveform,
  kCtrlOperator3Waveform,
  kCtrlOperator4Waveform,
  kCtrlAlgorithm,
  kNumCtrlTags
};

#include "../MPA Code/Global.h" // must know paramToMsgType

class InvisibleButtonControl : public IControl {

public:
  InvisibleButtonControl(const IRECT& bounds, IActionFunction actionFunc) : IControl(bounds, kNoParameter, actionFunc) {
    mDblAsSingleClick = true;
  }

  void OnMouseDown(float x, float y, const IMouseMod& mod)
  {
    SetValue(1.);
    SetDirty(true);
  }

  void OnMouseUp(float x, float y, const IMouseMod& mod)
  {
    SetValue(0.);
    SetDirty(true);
  }

  void Draw(IGraphics& g){
  }

};


class IBSwitchControlF : public IBSwitchControl {
public:
  IBSwitchControlF(float x, float y, const IBitmap& bitmap, IActionFunction actionFunc) : IBSwitchControl(x, y, bitmap) {
    SetActionFunction(actionFunc);
    mDblAsSingleClick = true;
  }

  void OnMouseDown(float x, float y, const IMouseMod& mod)
  {
    SetValue(1.);
    SetDirty(true);
  }

  void OnMouseUp(float x, float y, const IMouseMod& mod)
  {
    SetValue(0.);
    SetDirty(true);
  }
};

class FMagia : public IPlug
{
public:
  FMagia(IPlugInstanceInfo instanceInfo);

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
