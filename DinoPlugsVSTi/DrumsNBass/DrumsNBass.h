#pragma once

#include "IPlug_include_in_plug_hdr.h"

// 0: DrumsNBass, 1: Pro12, 2: Proddy, 3: B4000, 4: DrumsNBass used in Global.h Bankselect
#define PLUGIN_ID 6

#include "ParamEnum.h"
#include <array>

enum ECtrlTags
{
  #include "../MPA Code/CommonCtrlEnum.h"
  kCtrlTagSkalaL,
  kCtrlTagSkalaR,
  kCtrlTagMain,
  kCtrlTagAdd,
  kCtrlTagLfo1RateBPM,
  kCtrlTagLfo2RateBPM,
  kCtrlTagLfo1RateKnob,
  kCtrlTagLfo2RateKnob,
  kCtrlTagLfo1RateText,
  kCtrlTagLfo2RateText,
  kCtrlTagLfo1Midi,
  kCtrlTagLfo2Midi,
  kCtrlTagVcfLink,
  kCtrlTagVcf1Cf,
  kCtrlTagVcf2Cf,
  kNumCtrlTags
};

#include "../MPA Code/Global.h" // must know paramToMsgType

class ExclusiveSwitchControl : public IControl, public IBitmapBase
{
public:
  ExclusiveSwitchControl(float x, float y, const IBitmap& bitmap, int paramIdx, IActionFunction actionFunc = nullptr) :
    IControl(IRECT(x, y, bitmap), paramIdx, actionFunc), IBitmapBase(bitmap)
  {
    mDblAsSingleClick = true;
  }

  void OnMouseDown(float x, float y, const IMouseMod& mod) override
  {
    double val = Clip((y - mRECT.T)/mRECT.H(), 0.f, 1.f);
    SetValue(val);
    SetDirty(true);
  }

  void Draw(IGraphics& g) override {

    int i = 1;
    if (mBitmap.N() > 1)
    {
      i = 1 + int(0.5 + GetValue() * (double)(mBitmap.N() - 1));
      i = Clip(i, 1, mBitmap.N());
    }

    g.DrawBitmap(mBitmap, mRECT, i, &mBlend);
  }

  void OnMidi(const IMidiMsg& msg) override {

    IMidiMsg msgTmp = msg; // msg const :/
    msgTmp = parseNrpn(msgTmp); // if nrpn generate polyAT, if not nrpn passthrough

    if (paramToMsgType[GetParamIdx()] == 0) { //CC
      if (msgTmp.StatusMsg() == IMidiMsg::kControlChange) {
        if (msgTmp.ControlChangeIdx() == paramToCC[GetParamIdx()]) {
          double x = msgTmp.mData2 / 127.;
          if (mFunc) x = mFunc(x);
          SetValue(x);
          SetDirty(); // false setzt dirty aber ruft nicht onParamCHange auf.
        }
      }
    }
    else if (paramToMsgType[GetParamIdx()] == 1) { // Aftertouch
      if (msgTmp.StatusMsg() == IMidiMsg::kPolyAftertouch) {
        if (msgTmp.mData1 == paramToCC[GetParamIdx()]) {
          double x = msgTmp.mData2 / 127.;
          if (mFunc) x = mFunc(x);
          SetValue(x);
          SetDirty(); // false setzt dirty aber ruft nicht onParamCHange auf.;
        }
      }
    }
  }

  // receive nrpn and create a AT message, returns msg if no nrpn, returns converted msg if nrpn.
  IMidiMsg parseNrpn(IMidiMsg msg)
  {
    if (msg.StatusMsg() == IMidiMsg::kControlChange)
    {
      if (msg.ControlChangeIdx() == 98) { // NRPN 1
        nrpnCC = msg.mData2;
      }
      else if (msg.ControlChangeIdx() == 38) { // NRPN 1
        nrpnVal = msg.mData2;
        msg.MakePolyATMsg(nrpnCC, nrpnVal, 0, 0);
        return msg;
      }
    }
    return msg;
  }

private:
  int mNColumns = 0;
  int nrpnCC;
  int nrpnVal;
  std::function<double(double)> mFunc;
};

class WaveSwitchControl : public IControl, public IBitmapBase
{
public:
  WaveSwitchControl(float x, float y, int NColumns, int paramIdx, const IBitmap& bitmap, IActionFunction actionFunc) :
    IControl(IRECT(x, y, bitmap), paramIdx, actionFunc), IBitmapBase(bitmap)
  {
    mNColumns = NColumns;
    mDblAsSingleClick = true;
  }

  void OnMouseDown(float x, float y, const IMouseMod& mod) override
  {
    double g = (x - mRECT.L) / mRECT.W();
    double val = Clip(-0.1+1.2* g , 0., 1.);
    SetValue(val);
    SetDirty(true);
  }

  void Draw(IGraphics& g) override
  {
    int i = 1;
    if (mBitmap.N() > 1)
    {
      i = 1 + int(0.5 + GetValue() * (double)(mBitmap.N() - 1));
      i = Clip(i, 1, mBitmap.N());
    }

    g.DrawBitmap(mBitmap, mRECT, i, &mBlend);
  }

  void OnMidi(const IMidiMsg& msg) override {

    IMidiMsg msgTmp = msg; // msg const :/
    msgTmp = parseNrpn(msgTmp); // if nrpn generate polyAT, if not nrpn passthrough

    if (paramToMsgType[GetParamIdx()] == 0) { //CC
      if (msgTmp.StatusMsg() == IMidiMsg::kControlChange) {
        if (msgTmp.ControlChangeIdx() == paramToCC[GetParamIdx()]) {
          double x = msgTmp.mData2 / 5.;
          if (mFunc) x = mFunc(x);
          SetValue(x);
          SetDirty(); // false setzt dirty aber ruft nicht onParamCHange auf.
        }
      }
    }
    else if (paramToMsgType[GetParamIdx()] == 1) { // Aftertouch
      if (msgTmp.StatusMsg() == IMidiMsg::kPolyAftertouch) {
        if (msgTmp.mData1 == paramToCC[GetParamIdx()]) {
          double x = msgTmp.mData2 / 5.;
          if (mFunc) x = mFunc(x);
          SetValue(x);
          SetDirty(); // false setzt dirty aber ruft nicht onParamCHange auf.;
        }
      }
    }
  }

  // receive nrpn and create a AT message, returns msg if no nrpn, returns converted msg if nrpn.
  IMidiMsg parseNrpn(IMidiMsg msg)
  {
    if (msg.StatusMsg() == IMidiMsg::kControlChange)
    {
      if (msg.ControlChangeIdx() == 98) { // NRPN 1
        nrpnCC = msg.mData2;
      }
      else if (msg.ControlChangeIdx() == 38) { // NRPN 1
        nrpnVal = msg.mData2;
        msg.MakePolyATMsg(nrpnCC, nrpnVal, 0, 0);
        return msg;
      }
    }
    return msg;
  }

private:
  int mNColumns = 0;
  int nrpnCC;
  int nrpnVal;
  std::function<double(double)> mFunc;
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
#endif
};
