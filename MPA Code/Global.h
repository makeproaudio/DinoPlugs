#pragma once

// SetDirty False: triggert nciht doppelt, true: nur dann funz ICaption

// Switch with Actionfunction e.g. for enabling different Views
class IBSwitchControlFunc : public IBSwitchControl {
public:
  IBSwitchControlFunc(float x, float y, const IBitmap& bitmap, std::function<void(IControl*)> func, int paramIdx = kNoParameter)
    : IBSwitchControl(x, y, bitmap, paramIdx) {
    mFunc = func;
  }

  void OnMouseDown(float x, float y, const IMouseMod& mod) {

    if (mBitmap.N() > 1)
      SetValue(GetValue() + 1.0 / (double)(mBitmap.N() - 1));
    else
      SetValue(GetValue() + 1.0);

    if (GetValue() > 1.001)
      SetValue(0.);
    
    if (mFunc) mFunc(this);

    SetDirty();
  }

  std::function<void(IControl*)> mFunc;
};

class MidiLoggerControl : public IRTTextControl<IMidiMsg> {

public:
  MidiLoggerControl(IRECT bounds, const char* fmtStr = "%f", const char* initStr = "", const IText& text = DEFAULT_TEXT, const IColor& BGColor = DEFAULT_BGCOLOR)
    : IRTTextControl<IMidiMsg>(bounds, fmtStr, initStr, text, BGColor)
  {
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

    // for (auto c = 0; c < mHeaderRect.size(); c++) {
     //  mHeaderRect[c] = headerRect.GetGridCell(0, c, 1, numColumns);
    // }
    for (auto r = 0; r < mValueRect.size(); r++) {
      //for (auto c = 0; c < mValueRect[0].size(); c++) {
      //  mValueRect[r][c] = valueRect.GetGridCell(r, c, mValueRect.size(), mValueRect[0].size());
      //}
      IRECT mHorzRect = valueRect.GetGridCell(r, 0, mValueRect.size(), 1);

      mValueRect[r][0] = IRECT(mHorzRect.L, mHorzRect.T, mHorzRect.W()*0.4, mHorzRect.B);
      mValueRect[r][1] = IRECT(mHorzRect.L + 0.4*mHorzRect.W(), mHorzRect.T, mHorzRect.L + 0.6*mHorzRect.W(), mHorzRect.B);
      mValueRect[r][2] = IRECT(mHorzRect.L + 0.6*mHorzRect.W(), mHorzRect.T, mHorzRect.L + 0.8*mHorzRect.W(), mHorzRect.B);
      mValueRect[r][3] = IRECT(mHorzRect.L + 0.8*mHorzRect.W(), mHorzRect.T, mHorzRect.L + 1.0*mHorzRect.W(), mHorzRect.B);
    }
  }

  void Clear() {
    for (auto r = 0; r < maxLogSamples; r++) {
      for (auto c = 0; c < numColumns; c++) {
        mStrBuf[r][c].Set("", 32);
      }
    }
    mEntryPointer = 0;
    SetDirty(false);
  }

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

      //mEntryText = 

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

  void Draw(IGraphics& g) override {
    g.FillRect(mBGColor, mRECT);

    g.DrawText(mText, "Type", mHeaderRect[0]);
    g.DrawText(mText, "L", mHeaderRect[1]);
    g.DrawText(mText, "H", mHeaderRect[2]);
    g.DrawText(mText, "CH", mHeaderRect[3]);

    decrementEntryPtr(); // get Last Entry

    for (auto r = 0; r < maxShowLogSamples; r++) {
      for (auto c = 0; c < numColumns; c++) {
        if (mStrBuf[mEntryPointer][c].GetLength())
          g.DrawText(mText, mStrBuf[mEntryPointer][c].Get(), mValueRect[r][c]);
      }
      decrementEntryPtr();
    }
    incrementEntryPtr();
    for (auto r = 0; r < maxShowLogSamples; r++) {
      incrementEntryPtr();
    }
  }

private:
  static const int maxLogSamples = 64;
  static const int maxShowLogSamples = 10;
  static const int numColumns = 4;
  std::array<std::array<WDL_String, numColumns>, maxLogSamples> mStrBuf;
  std::array<IText, numColumns> mEntryText;
  std::array<std::array<IRECT, numColumns>, maxShowLogSamples> mValueRect;
  std::array<IRECT, numColumns> mHeaderRect;
  int mEntryPointer = 0;
  std::array<int, 4> proportion = { 2,1,1,1 }; // . ././././

};

class IBSliderControlMidi : public IBSliderControl
{
public:

  IBSliderControlMidi(float x, float y, int len, int paramIdx, const IBitmap& bitmap, std::function<double(double)> func = NULL, EDirection dir = EDirection::Vertical)
    : IBSliderControl(x, y, len, paramIdx, bitmap, dir) {
    SetWantsMidi(true);
    mFunc = func;
  }

  void OnMidi(const IMidiMsg& msg) override {
    if (paramToMsgType[GetParamIdx()] == 0) { //CC
      if (msg.StatusMsg() == IMidiMsg::kControlChange) {
        if (msg.ControlChangeIdx() == paramToCC[GetParamIdx()]) {
          double x = msg.mData2 / 127.;
          if (mFunc) x = mFunc(x);
          SetValue(x);
          SetDirty(); // false setzt dirty aber ruft nicht onParamCHange auf.
        }
      }
    }
    else if (paramToMsgType[GetParamIdx()] == 1) { // Aftertouch
      if (msg.StatusMsg() == IMidiMsg::kPolyAftertouch) {
        if (msg.mData1 == paramToCC[GetParamIdx()]) {
          double x = msg.mData2 / 127.;
          if (mFunc) x = mFunc(x);
          SetValue(x);
          SetDirty(); // false setzt dirty aber ruft nicht onParamCHange auf.;
        }
      }
    }
  }
private:
  std::function<double(double)> mFunc;
};

class IBSwitchControlMidi : public IBSwitchControl
{
public:

  IBSwitchControlMidi(float x, float y, const IBitmap& bitmap, int paramIdx = kNoParameter, std::function<double(double)> func = NULL)
    : IBSwitchControl(x, y, bitmap, paramIdx) {
    SetWantsMidi(true);
    mFunc = func;
  }

  void OnMidi(const IMidiMsg& msg) override {
    if (paramToMsgType[GetParamIdx()] == 0) { //CC
      if (msg.StatusMsg() == IMidiMsg::kControlChange) {
        if (msg.ControlChangeIdx() == paramToCC[GetParamIdx()]) {
          double x = msg.mData2 / 127.;
          if (mFunc) x = mFunc(x);
          SetValue(x);
          SetDirty(); // false setzt dirty aber ruft nicht onParamCHange auf.
        }
      }
    }
    else if (paramToMsgType[GetParamIdx()] == 1) { // Aftertouch
      if (msg.StatusMsg() == IMidiMsg::kPolyAftertouch) {
        if (msg.mData1 == paramToCC[GetParamIdx()]) {
          double x = msg.mData2 / 127.;
          if (mFunc) x = mFunc(x);
          SetValue(x);
          SetDirty(); // false setzt dirty aber ruft nicht onParamCHange auf.
        }
      }
    }
  }
private:
  std::function<double(double)> mFunc;
};

class ICaptionControlMidi : public ICaptionControl
{
public:

  ICaptionControlMidi(const IRECT& bounds, int paramIdx, const IText& text = DEFAULT_TEXT, const IColor& BGColor = DEFAULT_BGCOLOR, bool showParamLabel = true, std::function<double(double)> func = NULL)
    : ICaptionControl(bounds, paramIdx, text, BGColor, showParamLabel) {
    SetWantsMidi(true);
    mFunc = func;
  }

  void OnMidi(const IMidiMsg& msg) override {
    if (paramToMsgType[GetParamIdx()] == 0) { //CC
      if (msg.StatusMsg() == IMidiMsg::kControlChange) {
        if (msg.ControlChangeIdx() == paramToCC[GetParamIdx()]) {
          double x = msg.mData2 / 127.;
          if (mFunc) x = mFunc(x);
          SetValue(x);
          SetDirty(); // false setzt dirty aber ruft nicht onParamCHange auf.
        }
      }
    }
    else if (paramToMsgType[GetParamIdx()] == 1) { // Aftertouch
      if (msg.StatusMsg() == IMidiMsg::kPolyAftertouch) {
        if (msg.mData1 == paramToCC[GetParamIdx()]) {
          double x = msg.mData2 / 127.;
          if (mFunc) x = mFunc(x);
          SetValue(x);
          SetDirty(); // false setzt dirty aber ruft nicht onParamCHange auf.
        }
      }
    }
  }
private:
  std::function<double(double)> mFunc;
};

class IBKnobControlMidi : public IBKnobControl
{
public:

  IBKnobControlMidi(float x, float y, const IBitmap& bitmap, int paramIdx, std::function<double(double)> func = NULL, EDirection direction = EDirection::Vertical, double gearing = DEFAULT_GEARING)
    : IBKnobControl(x, y, bitmap, paramIdx, EDirection::Vertical, gearing) {
    SetWantsMidi(true);
    mFunc = func;
  }

  void OnMidi(const IMidiMsg& msg) override {
    if (paramToMsgType[GetParamIdx()] == 0) { //CC
      if (msg.StatusMsg() == IMidiMsg::kControlChange) {
        if (msg.ControlChangeIdx() == paramToCC[GetParamIdx()]) {
          double x = msg.mData2/127.;
          if (mFunc) x = mFunc(x);
          SetValue(x);
          SetDirty(); // false setzt dirty aber ruft nicht onParamCHange auf.
        }
      }
    }
    else if (paramToMsgType[GetParamIdx()] == 1) { // Aftertouch
      if (msg.StatusMsg() == IMidiMsg::kPolyAftertouch) {
        if (msg.mData1 == paramToCC[GetParamIdx()]) {
          double x = msg.mData2 / 127.;
          if (mFunc) x = mFunc(x);
          SetValue(x);
          SetDirty();
        }
      }
    }
  }

private:
  std::function<double(double)> mFunc;
};

class IBDrawbarControlMidi : public IBKnobControl
{
public:

  IBDrawbarControlMidi(float x, float y, const IBitmap& bitmap, int paramIdx, EDirection direction = EDirection::Vertical, double gearing = DEFAULT_GEARING, std::function<double(double)> func = NULL)
    : IBKnobControl(x, y, bitmap, paramIdx, EDirection::Vertical, gearing) {
    SetWantsMidi(true);
    mFunc = func;
  }

  void OnMouseDrag(float x, float y, float dX, float dY, const IMouseMod& mod) override
  {
    double gearing = IsFineControl(mod, false) ? mGearing * 10.0 : mGearing;

    if (mDirection == EDirection::Vertical)
      SetValue(1.-(1.-GetValue() + (double)dY / (double)(mRECT.T - mRECT.B) / gearing));
    else
      SetValue(1.-(1.-GetValue() + (double)dX / (double)(mRECT.R - mRECT.L) / gearing));

    SetDirty();
  }

  void Draw(IGraphics& g) override
  {
    int i = 1 + int(0.5 + (1.-GetValue()) * (double)(mBitmap.N() - 1));
    g.DrawBitmap(mBitmap, mRECT, i, &mBlend);
  }

  void OnMidi(const IMidiMsg& msg) override {
    if (paramToMsgType[GetParamIdx()] == 0) { //CC
      if (msg.StatusMsg() == IMidiMsg::kControlChange) {
        if (msg.ControlChangeIdx() == paramToCC[GetParamIdx()]) {
          double x = msg.mData2 / 127.;
          if (mFunc) x = mFunc(x);
          SetValue(x);
          SetDirty(); // false setzt dirty aber ruft nicht onParamCHange auf.
        }
      }
    }
    else if (paramToMsgType[GetParamIdx()] == 1) { // Aftertouch
      if (msg.StatusMsg() == IMidiMsg::kPolyAftertouch) {
        if (msg.mData1 == paramToCC[GetParamIdx()]) {
          double x = msg.mData2 / 127.;
          if (mFunc) x = mFunc(x);
          SetValue(x);
          SetDirty(); // false setzt dirty aber ruft nicht onParamCHange auf.
        }
      }
    }
  }
private:
  std::function<double(double)> mFunc;
};


