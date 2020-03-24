#pragma once

#include "IPlug_include_in_plug_hdr.h"

// 0: Minimax, 1: Pro12, 2: Proddy, 3: B4000, 4: DrumsNBass 6: Lightwave used in Global.h Bankselect
#define PLUGIN_ID 4

#include "ParamEnum.h"
#include <array>

enum ECtrlTags
{
  #include "../MPA Code/CommonCtrlEnum.h"

  kCtrlTagMain,
  kCtrlTagAdd,

  kCtrlTagBD1Inst,
  kCtrlTagBD2Inst,
  kCtrlTagSD1Inst,
  kCtrlTagCLInst,
  kCtrlTagSD2Inst,
  kCtrlTagTO1Inst,
  kCtrlTagHHInst,
  kCtrlTagTO2Inst,
  kCtrlTagCBInst,
  kCtrlTagCOWInst,
  kCtrlTagCYInst,

  kCtrlTagBD1InstButton,
  kCtrlTagBD2InstButton,
  kCtrlTagSD1InstButton,
  kCtrlTagCLInstButton,
  kCtrlTagSD2InstButton,
  kCtrlTagTO1InstButton,
  kCtrlTagHHInstButton,
  kCtrlTagTO2InstButton,
  kCtrlTagCBInstButton,
  kCtrlTagCOWInstButton,
  kCtrlTagCYInstButton,

  kCtrlGlowBD1,
  kCtrlGlowBD2,
  kCtrlGlowSD1,
  kCtrlGlowCL,
  kCtrlGlowSD2,
  kCtrlGlowTO1,
  kCtrlGlowHH,
  kCtrlGlowTO2,
  kCtrlGlowCB, 
  kCtrlGlowCOW,
  kCtrlGlowCY, 
  
  kCtrlBlitzBD1,
  kCtrlBlitzBD2,
  kCtrlBlitzSD1,
  kCtrlBlitzCL,
  kCtrlBlitzSD2,
  kCtrlBlitzTO1,
  kCtrlBlitzHH,
  kCtrlBlitzTO2,
  kCtrlBlitzCB,
  kCtrlBlitzCOW,
  kCtrlBlitzCY,

  kCtrlTagHH,
  kCtrlTagBD1,
  kCtrlTagBD2,
  kCtrlTagCB,
  kCtrlTagCY,
  kCtrlTagCL,
  kCtrlTagSD1,
  kCtrlTagSD2,
  kCtrlTagCow,
  kCtrlTagTO1,
  kCtrlTagTO2,
  kCtrlTagBasssynth,
  kCtrlTagEditHH,
  kCtrlTagEditBD1,
  kCtrlTagEditBD2,
  kCtrlTagEditCB,
  kCtrlTagEditCY,
  kCtrlTagEditCL,
  kCtrlTagEditSD1,
  kCtrlTagEditSD2,
  kCtrlTagEditCow,
  kCtrlTagEditTO1,
  kCtrlTagEditTO2,
  kCtrlTagEditBasssynth,

  kCtrlTagBD1Wave,
  kCtrlTagBD2Wave,
  kCtrlTagSD1Wave,
  kCtrlTagSD2Wave,
  kCtrlTagTO1Wave,
  kCtrlTagTO2Wave,
  kCtrlTagCowWave,
  kCtrlCymbalWave,
  kCtrlTagFilterType,

  kCtrlTagBasssynthHide,

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
    //g.DrawRect(COLOR_WHITE, mRECT);
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

class DrumsNBass : public IPlug
{
public:
  DrumsNBass(IPlugInstanceInfo instanceInfo);

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

  int mBlitzCnt1 = 0;
  int mBlitzCnt2 = 0;
  int mBlitzCnt3 = 0;
  int mBlitzCnt4 = 0;
  int mBlitzCnt5 = 0;
  int mBlitzCnt6 = 0;
  int mBlitzCnt7 = 0;
  int mBlitzCnt8 = 0;
  int mBlitzCnt9 = 0;
  int mBlitzCnt10 = 0;
  int mBlitzCnt11 = 0;
  int mBlitzCnt12 = 0;

  bool mMidiActive = false;
  int mLightOnOff = 1;

#endif
};
