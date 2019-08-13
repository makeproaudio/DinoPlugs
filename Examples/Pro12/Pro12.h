#pragma once


#include "IPlug_include_in_plug_hdr.h"

// 0: Minimax, 1: Pro12, 2: Proddy, 3: B4000
// used in Global.h Bankselect
#define PLUGIN_ID 1

//#include "PresetMenu.h"

#include "IRTTextControl.h"
#include "IControls.h"

#include "ParamEnum.h"

#include <array>
#include "../MPA Code/PresetMenu.h"

enum ECtrlTags
{

  #include "../MPA Code/CommonCtrlEnum.h"
 
  kCtrlTagHideL,
  kCtrlTagHideR,
  kCtrlTagMain,
  kCtrlTagAdd,
  kCtrlTagEffects,
  kNumCtrlTags
};

bool mMidiActive = true;

#include "../MPA Code/Global.h" // must know paramToMsgType

class Pro12 : public IPlug
{
public:
  Pro12(IPlugInstanceInfo instanceInfo);

#if IPLUG_DSP // All DSP methods and member variables should be within an IPLUG_DSP guard, should you want distributed UI
public:
  void ProcessBlock(sample** inputs, sample** outputs, int nFrames) override;
  void ProcessMidiMsg(const IMidiMsg& msg) override;
  void OnReset() override;
  void OnParamChange(int paramIdx) override;
  void OnIdle() override;
  void OnUIOpen() override;
  void OnUIClose() override;
  bool OnMessage(int messageTag, int controlTag, int dataSize, const void *pData) override;
  bool SerializeState(IByteChunk& chunk) const;
  int UnserializeState(const IByteChunk& chunk, int startPos);
  //void SendMidiMsgFromUI(const IMidiMsg& msg) override;
private:

  //MidiLoggerControl::Sender<64> mMidiLoggerSender{ kCtrlTagMidiLogger };

  IVKeyboardControl* keybCtrl;
  //MidiLoggerControl *mMidiLogger;
  ICaptionControl *captionCtrl;

  MidiMonitor::Sender<100> mMidiLoggerSender{ kCtrlTagMidiLogger };
  MidiMonitor *mMidiLogger;
  PresetList *mPresetList;

	//FileBrowser* mPresetMenu;
    WDL_String mCurrentPresetPath;	

 
  int mDeveloperActive = 1;
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
  
#endif
};
