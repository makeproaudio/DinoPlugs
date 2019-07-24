#pragma once

#include "IPlug_include_in_plug_hdr.h"
#include "IControls.h"
#include "IControl.h"

const int kNumPrograms = 1;

enum EParams
{
  kGain = 0,
  kNumParams
};

enum ECtrlTags
{
  kCtrlTagDialogResult = 0,
  kCtrlTagMidiLogger,
  kCtrlPresetMonitor,
  kCtrlTagScope,
  kCtrlTagMeter,
  kCtrlSlider,
  kCtrlSlider2,
  kCtrlTags
};

#include <array>


// Stringbuffer:        .................................................
// entryPointer:                          |
// mValueRect           7,6,5,4,3,2,1|offs|                       |10,9,8,

// das was hier im Template steht IMidiMsg das ist das was vom Realtime thread kommt.
class MidiMonitor : public IRTTextControl<IMidiMsg>{

public:
  MidiMonitor(IRECT bounds, const char* fmtStr = "%f", const char* initStr = "", const IText& text = DEFAULT_TEXT, const IColor& BGColor = DEFAULT_BGCOLOR)
    : IRTTextControl<IMidiMsg>(bounds, fmtStr, initStr, text, BGColor)
  {
    mIgnoreMouse = false;
    makeRects();
  }

  void SetTargetAndDrawRECTs(const IRECT& bounds) {
    mRECT = mTargetRECT = bounds;
    mMouseIsOver = false; OnResize();
    makeRects();
  }

  void makeRects() {
    IRECT valueRect = mRECT.FracRectVertical(maxShowLogSamples / 11.f);
    IRECT headerRect = mRECT.FracRectVertical(1.f - maxShowLogSamples / 11.f, true);

    mHeaderRect[0] = IRECT(headerRect.L, headerRect.T, headerRect.W()*0.4, headerRect.B);
    mHeaderRect[1] = IRECT(headerRect.L + 0.4*headerRect.W(), headerRect.T, headerRect.L + 0.6*headerRect.W(), headerRect.B);
    mHeaderRect[2] = IRECT(headerRect.L + 0.6*headerRect.W(), headerRect.T, headerRect.L + 0.8*headerRect.W(), headerRect.B);
    mHeaderRect[3] = IRECT(headerRect.L + 0.8*headerRect.W(), headerRect.T, headerRect.L + 1.0*headerRect.W(), headerRect.B);

    for (auto r = 0; r < mValueRect.size(); r++) {

      IRECT mHorzRect = valueRect.GetGridCell(r, 0, mValueRect.size(), 1);

      mValueRect[r][0] = IRECT(mHorzRect.L, mHorzRect.T, mHorzRect.W()*0.4, mHorzRect.B);
      mValueRect[r][1] = IRECT(0.4*mHorzRect.W(), mHorzRect.T, mHorzRect.L + 0.6*mHorzRect.W(), mHorzRect.B);
      mValueRect[r][2] = IRECT(mHorzRect.L + 0.6*mHorzRect.W(), mHorzRect.T, mHorzRect.L + 0.8*mHorzRect.W(), mHorzRect.B);
      mValueRect[r][3] = IRECT(mHorzRect.L + 0.8*mHorzRect.W(), mHorzRect.T, mHorzRect.L + 1.0*mHorzRect.W(), mHorzRect.B);
    }
  }

  // write into current mEntrypointer, and increment
  void OnMsgFromDelegate(int messageTag, int dataSize, const void* pData) override
  {
    if (messageTag == kUpdateMessage && dataSize == sizeof(IMidiMsg))
    {
      WDL_String str;
      IMidiMsg* pTypedData = (IMidiMsg*)pData;
      str.SetFormatted(32, "%s", msgToStatusString(*pTypedData));
      mStrBuf[mEntryPointer][0] = str;
      str.SetFormatted(32, "%d", (*pTypedData).mData1);
      mStrBuf[mEntryPointer][1] = str;
      str.SetFormatted(32, "%d", (*pTypedData).mData2);
      mStrBuf[mEntryPointer][2] = str;
      str.SetFormatted(32, "%d", (*pTypedData).Channel());
      mStrBuf[mEntryPointer][3] = str;

      if (mNumEntries < maxLogSamples) mNumEntries++;

      incrementEntryPtr();

      SetDirty(false);
    }
  }

  const char* msgToStatusString(IMidiMsg msg) {
    switch (msg.StatusMsg())
    {
    case IMidiMsg::EStatusMsg::kNone: return "None";
    case IMidiMsg::EStatusMsg::kNoteOff: return "Note Off";
    case IMidiMsg::EStatusMsg::kNoteOn: return "Note On";
    case IMidiMsg::EStatusMsg::kPolyAftertouch: return "Aftertouch";
    case IMidiMsg::EStatusMsg::kControlChange: return "Control Change";
    case IMidiMsg::EStatusMsg::kProgramChange: return "Program Change";
    case IMidiMsg::EStatusMsg::kChannelAftertouch: return "Channel Aftertouch";
    case IMidiMsg::EStatusMsg::kPitchWheel: return "Pitchwheel";
    default:  return "Unknown";
    }
  }

  void Clear() {
    for (auto r = 0; r < maxLogSamples; r++) {
      for (auto c = 0; c < numColumns; c++) {
        mStrBuf[r][c].Set("", 32);
      }
    }
    mEntryPointer = 0;
    mNumEntries = 0;
    SetDirty(false);
  }

  // increment, decrement with wrap
  void incrementEntryPtr() {
    mEntryPointer++;
    if (mEntryPointer >= maxLogSamples) {
      mEntryPointer = 0;
    }
  }
  void decrementEntryPtr() {
    mEntryPointer--;
    if (mEntryPointer < 0) {
      mEntryPointer = maxLogSamples - 1;
    }
  }

  void OnMouseDown(float x, float y, const IMouseMod& mod) {

    if (mod.L) {
      for (auto r = 0; r < maxShowLogSamples; r++) {
        for (auto c = 0; c < numColumns; c++) {
          if (mValueRect[r][c].Contains(x, y)) {
            mActiveRow = r+mEntryPointerOffset;
          }
        }
      }
    }
    SetDirty();
  }

  void OnMouseWheel(float x, float y, const IMouseMod &mod, float d) {

    if (!mRECT.Contains(x, y)) return;

    if (d == -1) incrementEntrypointerOffset();
    else decrementEntrypointerOffset();
    GetUI()->GetControlWithTag(kCtrlSlider)->SetValueFromUserInput(1.-GetNormalizedEntryPointerOffset());
  }

  int GetActiveIdx() {
    return mActiveRow;
  }

  void Draw(IGraphics& g) override {

    bool t = GetIgnoreMouse();
    g.FillRect(mBGColor, mRECT);

    g.DrawText(mText, "Type", mHeaderRect[0]);
    g.DrawText(mText, "L", mHeaderRect[1]);
    g.DrawText(mText, "H", mHeaderRect[2]);
    g.DrawText(mText, "CH", mHeaderRect[3]);

    decrementEntryPtr(); // get Last Entry

    for (auto r = 0; r < maxShowLogSamples; r++) {
      for (auto c = 0; c < numColumns; c++) {
        if (mEntryPointer - mEntryPointerOffset >= 0 && mEntryPointer - mEntryPointerOffset < maxLogSamples) { // nixht überschreiten
          //if (mStrBuf[mEntryPointer][c].GetLength()){
            if (mActiveRow == r+mEntryPointerOffset) {
              //g.FillRect(COLOR_MID_GRAY, mValueRect[r][c]);
            }
          //}
          g.DrawText(mText, mStrBuf[mEntryPointer - mEntryPointerOffset][c].Get(), mValueRect[r][c]);
        }
      }
      decrementEntryPtr();
    }
    incrementEntryPtr();
    for (auto r = 0; r < maxShowLogSamples; r++) {
      incrementEntryPtr();
    }
  }

  double GetNormalizedEntryPointerOffset(){
    return (double)mEntryPointerOffset/(mNumEntries - maxShowLogSamples);
  }

  int clipEntryPointerOffset(int offs) {
    if (offs > mNumEntries - maxShowLogSamples) offs = mNumEntries - maxShowLogSamples;
    if (offs < 0) offs = 0;
    return offs;
  }

  // Es wird oben der Eintrag 0+offs angezeigt 
  void incrementEntrypointerOffset( ) {
    mEntryPointerOffset += 1;
    mEntryPointerOffset = clipEntryPointerOffset(mEntryPointerOffset);
    SetDirty();
  }

  // Es wird oben der Eintrag 0+offs angezeigt 
  void decrementEntrypointerOffset() {
    mEntryPointerOffset -= 1;
    mEntryPointerOffset = clipEntryPointerOffset(mEntryPointerOffset);
    SetDirty();
  }

  // normalizedOffset 0: oberste Reihe ist aktuellst, 1: Zeige die letzen 
  void setEntrypointerOffset(double normalizedOffset) {
    mEntryPointerOffset = normalizedOffset * (mNumEntries - maxShowLogSamples);
    SetDirty();
  }

public:
  static const int maxLogSamples = 100;
  static const int maxShowLogSamples = 10;
  static const int numColumns = 4;
  int mActiveRow = 0;
  std::array<std::array<WDL_String, numColumns>, maxLogSamples> mStrBuf;
  std::array<IText, numColumns> mEntryText;
  std::array<std::array<IRECT, numColumns>, maxShowLogSamples> mValueRect;
  std::array<IRECT, numColumns> mHeaderRect;
  int mEntryPointer = 0; // zeigt auf oberstes, aktuellen Eintrag
  std::array<int, 4> proportion = { 2,1,1,1 }; // . ././././
  int mEntryPointerOffset = 0; // scrollen.
  int mNumEntries = 0; // how many written entries? Only scroll until the last are shown.
};

/*

struct presettext {
  char name[30];
};

class PresetMonitor : public Scrolllist<presettext> {
public:
  PresetMonitor(IRECT bounds, const char* fmtStr = "%f", const char* initStr = "", const IText& text = DEFAULT_TEXT, const IColor& BGColor = DEFAULT_BGCOLOR)
    : Scrolllist(bounds, fmtStr, "", text, BGColor)

  {}

  // write into current mEntrypointer, and increment
  void OnMsgFromDelegate(int messageTag, int dataSize, const void* pData) override
  {
    if (messageTag == kUpdateMessage && dataSize == sizeof(presettext))
    {

      presettext* pTypedData = (presettext*)pData;

      WDL_String s;
      s.Set((*pTypedData).name);
      mStrBuf[mEntryPointer][2] = s;

      if (mNumEntries < maxLogSamples) mNumEntries++;

      incrementEntryPtr();

      SetDirty(false);
    }
  }
};


*/

class Scrollbar : public IPlug
{
public:
  Scrollbar(IPlugInstanceInfo instanceInfo);

#if IPLUG_DSP // All DSP methods and member variables should be within an IPLUG_DSP guard, should you want distributed UI
  void ProcessBlock(sample** inputs, sample** outputs, int nFrames) override;
  void OnIdle() override;
private:

  IVSliderControl *slider;
  MidiMonitor *mMidiLogger;
  // Attention Queue size must be the elements which are initialzed, if to small you will lost at initialization.
  MidiMonitor::Sender<100> mMidiLoggerSender{ kCtrlTagMidiLogger };

  //IVSliderControl *slider2;
  //PresetMonitor *mPresetMonitor;
  // Attention Queue size must be the elements which are initialzed, if to small you will lost at initialization.
  //PresetMonitor::Sender<100> mPresetMonitorSender{ kCtrlPresetMonitor };
#endif
};
