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



enum ECtrlTags
{
  kCtrlTagMeter = 0,

  kCtrlOct1,
  kCtrlOct2,
  kCtrlOct3,

  kCtrlTagMidiLogger,
  kCtrlTagPresetList,

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
  kCtrlTagSkalaL,
  kCtrlTagSkalaR,
  kCtrlMainAdd,
  kCtrlTagMain,
  kCtrlTagAdd,

  kCtrlSave,
  kCtrlLoad,
  kCtrlProgram,

  

  kCtrlSliderMidiMon1,
  kCtrlSliderPresetList,

  kCtrlTimeL,
  kCtrlTimeR,
  kCtrlLengthL,
  kCtrlLengthR,
  kNumCtrlTags
};

#include "../MPA Code/Global.h" // must know paramToMsgType

class B4000 : public IPlug
{
public:
  B4000(IPlugInstanceInfo instanceInfo);

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

  MidiMonitor::Sender<100> mMidiLoggerSender{ kCtrlTagMidiLogger };

  MidiMonitor *mMidiLogger;
  PresetList *mPresetList;

  IVKeyboardControl* keybCtrl;
  ICaptionControl *captionCtrl;

	//FileBrowser* mPresetMenu;
    WDL_String mCurrentPresetPath;

  bool mMidiActive = true;

  int mChannel = 0;
#endif
};
