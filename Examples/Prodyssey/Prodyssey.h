#pragma once


#include "IPlug_include_in_plug_hdr.h"


//#include "PresetMenu.h"

#include "IRTTextControl.h"
#include "IControls.h"

#include "ParamEnum.h"

#include <array>

#include "../MPA Code/PresetMenu.h"


const int kNumPrograms = 1;

std::array<int, kNumParams> paramToCC;
std::array<int, kNumParams> paramToMsgType;

#include "../MPA Code/Global.h" // must know paramToMsgType

enum ECtrlTags
{
  kCtrlTagMeter = 0,
  kCtrlTagMidiLogger,
  kCtrlTagKeyboard,
  kCtrlTagKeybHide,
  kCtrlTagMidiMonHide,
  kCtrlTagMidiBack,
  kCtrlTagClear,
  kCtrlTagPresetMenu,
  kCtrlTagDelayTimeLMS,
  kCtrlTagDelayTimeRMS,
  kCtrlTagDelayTimeLBPM,
  kCtrlTagDelayTimeRBPM,
  kCtrlTagDelayTimeLMSCaption,
  kCtrlTagDelayTimeRMSCaption,
  kCtrlTagFaderBg1,
  kCtrlTagFaderBg2,
  kCtrlMainAdd,
  kCtrlTagMain,
  kCtrlTagAdd,
  kNumCtrlTags
};

class Prodyssey : public IPlug
{
public:
  Prodyssey(IPlugInstanceInfo instanceInfo);

#if IPLUG_DSP // All DSP methods and member variables should be within an IPLUG_DSP guard, should you want distributed UI
public:
  void ProcessBlock(sample** inputs, sample** outputs, int nFrames) override;
  void ProcessMidiMsg(const IMidiMsg& msg) override;
  void OnReset() override;
  void OnParamChange(int paramIdx) override;
  void OnIdle() override;
  void OnUIOpen() override;
  bool OnMessage(int messageTag, int controlTag, int dataSize, const void *pData) override;
  bool SerializeState(IByteChunk& chunk) const;
  int UnserializeState(const IByteChunk& chunk, int startPos);
  //void SendMidiMsgFromUI(const IMidiMsg& msg) override;
private:

  MidiLoggerControl::Sender<64> mMidiLoggerSender{ kCtrlTagMidiLogger };

  IVKeyboardControl* keybCtrl;
  MidiLoggerControl *mMidiLogger;
  ICaptionControl *captionCtrl;

  FileBrowser* mPresetMenu;
  WDL_String mCurrentPresetPath;

  bool mMidiActive = true;

  int mChannel = 0;
#endif
};
