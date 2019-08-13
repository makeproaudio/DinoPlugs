#pragma once

const int kNumPrograms = 1;

std::array<int, kNumParams> paramToCC;
std::array<int, kNumParams> paramToMsgType;
std::array<int, 127> ccIsNRPN; // cc 0-127

// Stringbuffer:        .................................................
// entryPointer:                          |
// mValueRect           7,6,5,4,3,2,1|offs|                       |10,9,8,

// das was hier im Template steht IMidiMsg das ist das was vom Realtime thread kommt.
class MidiMonitor : public IRTTextControl<IMidiMsg> {

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
    IRECT valueRect = mRECT.FracRectVertical(maxShowLogSamples / (double)(maxShowLogSamples+1));
    IRECT headerRect = mRECT.FracRectVertical(1.f - maxShowLogSamples / (double)(maxShowLogSamples+1), true);

    mHeaderRect[0] = IRECT(headerRect.L, headerRect.T, headerRect.L+headerRect.W()*0.5, headerRect.B);
    mHeaderRect[1] = IRECT(headerRect.L + 0.5*headerRect.W(), headerRect.T, headerRect.L + 0.6666*headerRect.W(), headerRect.B);
    mHeaderRect[2] = IRECT(headerRect.L + 0.6666*headerRect.W(), headerRect.T, headerRect.L + 0.8333*headerRect.W(), headerRect.B);
    mHeaderRect[3] = IRECT(headerRect.L + 0.8333*headerRect.W(), headerRect.T, headerRect.L + 1.0*headerRect.W(), headerRect.B);

    for (auto r = 0; r < mValueRect.size(); r++) {

      IRECT mHorzRect = valueRect.GetGridCell(r, 0, mValueRect.size(), 1);

      mValueRect[r][0] = IRECT(mHorzRect.L, mHorzRect.T, mHorzRect.L+mHorzRect.W()*0.5, mHorzRect.B);
      mValueRect[r][1] = IRECT(mHorzRect.L+0.5*mHorzRect.W(), mHorzRect.T, mHorzRect.L + 0.6666*mHorzRect.W(), mHorzRect.B);
      mValueRect[r][2] = IRECT(mHorzRect.L + 0.6666*mHorzRect.W(), mHorzRect.T, mHorzRect.L + 0.8333*mHorzRect.W(), mHorzRect.B);
      mValueRect[r][3] = IRECT(mHorzRect.L + 0.8333*mHorzRect.W(), mHorzRect.T, mHorzRect.L + 1.0*mHorzRect.W(), mHorzRect.B);
    }
  }

  // write into current mEntrypointer, and increment
  void OnMsgFromDelegate(int messageTag, int dataSize, const void* pData) override
  {
    if (messageTag == kUpdateMessage && dataSize == sizeof(IMidiMsg))
    {
      WDL_String str;
      IMidiMsg* pTypedData = (IMidiMsg*)pData;
      if (msgToStatusString(*pTypedData) == "None") return; // schutz vor Presetlist
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

      mEntryPointerOffset = 0; // go to head when new data comes in.
      GetUI()->GetControlWithTag(kCtrlSliderMidiMon1)->SetValueFromUserInput(1.);

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
            mActiveRow = r + mEntryPointerOffset;
          }
        }
      }
    }
    SetDirty();
  }

  void OnMouseWheel(float x, float y, const IMouseMod &mod, float d) {

    if (!mRECT.Contains(x, y)) return;

    if (d < 0) incrementEntrypointerOffset();
    else decrementEntrypointerOffset();
    GetUI()->GetControlWithTag(kCtrlSliderMidiMon1)->SetValueFromUserInput(1. - GetNormalizedEntryPointerOffset());
  }

  int GetActiveIdx() {
    return mActiveRow;
  }



  void Draw(IGraphics& g) override {

    bool t = GetIgnoreMouse();
    g.FillRect(mBGColor, mRECT);

    //g.FillRect(IColor(255,255,175,36), mHeaderRect[0]);
    //g.FillRect(IColor(255,255,175,36), mHeaderRect[1]);
    //g.FillRect(IColor(255,255,175,36), mHeaderRect[2]);
    //g.FillRect(IColor(255,255,175,36), mHeaderRect[3]);

  

   // mText.mTextEntryBGColor = IColor(255, 255, 175, 36);

    g.DrawText(mText, "Type", mHeaderRect[0]);
    g.DrawText(mText, "L", mHeaderRect[1]);
    g.DrawText(mText, "H", mHeaderRect[2]);
    g.DrawText(mText, "CH", mHeaderRect[3]);

    decrementEntryPtr(); // get Last Entry

    for (auto r = 0; r < maxShowLogSamples; r++) {
      for (auto c = 0; c < numColumns; c++) {
        int ptr = mEntryPointer - mEntryPointerOffset;
        if (ptr < 0) ptr += maxLogSamples;
        //if (mEntryPointer - mEntryPointerOffset >= 0 && mEntryPointer - mEntryPointerOffset < maxLogSamples) { // nixht überschreiten
          //if (mStrBuf[mEntryPointer][c].GetLength()){
          if (mActiveRow == r + mEntryPointerOffset) {
            //g.FillRect(COLOR_MID_GRAY, mValueRect[r][c]);
          }
          //}
          //if (mStrBuf[ptr][c].GetLength()){
            g.DrawText(mText, mStrBuf[ptr][c].Get(), mValueRect[r][c]);
          //}
      }
      decrementEntryPtr();
    }
    incrementEntryPtr();
    for (auto r = 0; r < maxShowLogSamples; r++) {
      incrementEntryPtr();
    }
  }

  double GetNormalizedEntryPointerOffset() {
    return (double)mEntryPointerOffset / (mNumEntries - maxShowLogSamples);
  }

  int clipEntryPointerOffset(int offs) {
    if (offs > mNumEntries - maxShowLogSamples) offs = mNumEntries - maxShowLogSamples;
    if (offs < 0) offs = 0;
    return offs;
  }

  // Es wird oben der Eintrag 0+offs angezeigt 
  void incrementEntrypointerOffset() {
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
    if (mEntryPointerOffset < 0) mEntryPointerOffset = 0;
    SetDirty();
  }

public:
  static const int maxLogSamples = 100;
  static const int maxShowLogSamples = 5;
  static const int numColumns = 4;
  int mActiveRow = 0;
  std::array<std::array<WDL_String, numColumns>, maxLogSamples> mStrBuf;
  //std::array<IText, numColumns> mEntryText;
  std::array<std::array<IRECT, numColumns>, maxShowLogSamples> mValueRect;
  std::array<IRECT, numColumns> mHeaderRect;
  int mEntryPointer = 0; // zeigt auf oberstes, aktuellen Eintrag
  //std::array<int, 4> proportion = { 2,1,1,1 }; // . ././././
  int mEntryPointerOffset = 0; // scrollen.
  int mNumEntries = 0; // how many written entries? Only scroll until the last are shown.
};

class PresetList : public ITextControl {

public:
  PresetList(IRECT bounds, int maxSamplesToShow, const char* fmtStr = "%f", const char* initStr = "", const IText& text = DEFAULT_TEXT, const IColor& BGColor = DEFAULT_BGCOLOR)
    : ITextControl(bounds, initStr, text,  BGColor)
  {
    mIgnoreMouse = false;
    maxShowLogSamples = maxSamplesToShow;
    if (maxShowLogSamples > 50) maxShowLogSamples = 50;
    makeRects();
    
  }

  void makeRects() {
    IRECT valueRect = mRECT.FracRectVertical(maxShowLogSamples / (maxShowLogSamples+1.));
    IRECT headerRect = mRECT.FracRectVertical(1.f - maxShowLogSamples / (maxShowLogSamples + 1.), true);

    mHeaderRect = IRECT(headerRect.L, headerRect.T, headerRect.L+ headerRect.W(), headerRect.B);

    for (auto r = 0; r < maxShowLogSamples; r++) {
      IRECT mHorzRect = valueRect.GetGridCell(r, 0, maxShowLogSamples, 1);
      mValueRect[r] = IRECT(mHorzRect.L, mHorzRect.T, mHorzRect.L + mHorzRect.W(), mHorzRect.B);
    }
  }

  //*
  // Add Item, only until buffer is full, and save mNumEntries
  void addItem(WDL_String str) {
    if (mNumEntries < maxLogSamples) {
      mStrBuf[mNumEntries] = str;
      mNumEntries++;
      SetDirty(false);
    }
  }

  //*
  void Clear() {
    for (auto r = 0; r < maxLogSamples; r++) {
        mStrBuf[r].Set("", 32);
    }
    mNumEntries = 0;
    SetDirty(false);
  }

  //*
  void OnMouseDown(float x, float y, const IMouseMod& mod) {

    if (mod.L) {
      for (auto r = 0; r < maxShowLogSamples; r++) {
          if (mValueRect[r].Contains(x, y)) {
            mSelectedRow = r + mFirstRowToShow;
          } 
      }
    }
    SetDirty(false);
  }

  //*
  void OnMouseDblClick(float x, float y, const IMouseMod &mod){

    if (mod.L) {
      for (auto r = 0; r < maxShowLogSamples; r++) {
        if (mValueRect[r].Contains(x, y)) {
          mSelectedRow = r + mFirstRowToShow;
          mActiveRow = mSelectedRow;
          //this->EditorDataModified();
          GetUI()->GetControlWithTag(kCtrlProgram)->SetValue((double)mActiveRow/(maxLogSamples-1.));
          GetUI()->GetControlWithTag(kCtrlProgram)->SetDirty();
        }
      }
    }
    SetDirty(false);
  }

  //*
  bool OnKeyDown(float x, float y, const IKeyPress &key) override {

      switch (key.VK)
      {
      case 38: // up
          decrementSelectedRow();
        break;
      case 40: // down
          incrementSelectedRow();
          break;
      case kVK_RETURN: // enter
        mActiveRow = mSelectedRow;
        GetUI()->GetControlWithTag(kCtrlProgram)->SetValue((double)mActiveRow / (maxLogSamples - 1.));
        GetUI()->GetControlWithTag(kCtrlProgram)->SetDirty();
        break;
      default:
        break;
      }
      return true;
  }

  //*
  // MouseWheel modifies firstRowToShow
  void OnMouseWheel(float x, float y, const IMouseMod &mod, float d) {
    if (!mRECT.Contains(x, y)) return;
    if (d < 0) incrementFirstRowToShow();
    else decrementFirstRowToShow();
    updateSlider();
  }

  //*
  void SnapToRow(int row) {
    if (row < mFirstRowToShow) mFirstRowToShow = row;
    if (row >= mFirstRowToShow + maxShowLogSamples) mFirstRowToShow = row - maxShowLogSamples+1;
    SetDirty(false);
    updateSlider();
  }

  //*
  void Draw(IGraphics& g) override {

    bool t = GetIgnoreMouse();
    g.FillRect(mBGColor, mRECT);

    g.DrawText(mText, "Preset", mHeaderRect);

    // Show all rows from firstRowToShow on.
    for (auto r = mFirstRowToShow; r < mFirstRowToShow + maxShowLogSamples; r++) {
      int valueRectIdx = r - mFirstRowToShow; // Idx of draw rect [0,9]
        if (mSelectedRow == r) {
          g.FillRect(COLOR_MID_GRAY, mValueRect[valueRectIdx]); // grey is selected
        }
        g.DrawText(mText, mStrBuf[r].Get(), mValueRect[valueRectIdx]);
    }
  }

  //*
  // scroll nach unten
  void incrementFirstRowToShow() {
    if (mFirstRowToShow < mNumEntries - maxShowLogSamples) {
      mFirstRowToShow++;
      SetDirty(false);
    }
  }

  //*
  // scroll nach oben
  void decrementFirstRowToShow() {
    if (mFirstRowToShow > 0) {
      mFirstRowToShow--;
      SetDirty(false);
    }
  }

  //*
  // 0-1 mapped to 0-mNumEntries-maxShowLogSamples, important for Slider
  void setFirstRowToShowNormalized(double valNormalized) {
    mFirstRowToShow = round((mNumEntries - maxShowLogSamples) - (mNumEntries - maxShowLogSamples)*valNormalized);
    SetDirty(false);
  }

  //*
  void updateSlider() {
    GetUI()->GetControlWithTag(kCtrlSliderPresetList)->SetValue(1. - (double)mFirstRowToShow / (mNumEntries - maxShowLogSamples));
    GetUI()->GetControlWithTag(kCtrlSliderPresetList)->SetDirty(false);
  }

  //*
  void setActiveRow(int row) {
    mActiveRow = row;
    mSelectedRow = row;
    SnapToRow(row);
  }

  //*
  void incrementSelectedRow() { 
    if (mSelectedRow < maxLogSamples - 1) {
      mSelectedRow++;
      SnapToRow(mSelectedRow);
    } 
  }

  //*
  void decrementSelectedRow() {
    if (mSelectedRow > 0) {
      mSelectedRow--;
      SnapToRow(mSelectedRow);
    }
  }

public:
  static const int maxLogSamples = 50;
  int maxShowLogSamples = 0;
  static const int numColumns = 4;
  int mFirstRowToShow = 0;
  int mActiveRow = 0; // Aktives Preset
  int mSelectedRow = 0; // only selected not recalled
  std::array<WDL_String, maxLogSamples> mStrBuf;
  IText mEntryText;
  std::array<IRECT, 50> mValueRect;
  IRECT mHeaderRect;
  //int mEntryPointer = 0; // zeigt auf oberstes, aktuellen Eintrag
  //std::array<int, 4> proportion = { 2,1,1,1 }; // . ././././
  //int mEntryPointerOffset = 0; // scrollen.
  int mNumEntries = 0; // how many written entries? Only scroll until the last are shown.
};


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

  void OnMouseWheel(float x, float y, const IMouseMod &mod, float d) {
    //double gearing = IsFineControl(mod, true) ? 0.001 : 0.01;
    double gearing = 0.02;
    SetValue(GetValue() + gearing * d);
    SetDirty(true);
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
  std::function<double(double)> mFunc;
  int nrpnCC;
  int nrpnVal;
};

class IBSliderControlScroll : public IBSliderControl
{
public:

  IBSliderControlScroll(float x, float y, int len, int paramIdx, const IBitmap& bitmap, EDirection dir = EDirection::Vertical)
    : IBSliderControl(x, y, len, paramIdx, bitmap, dir) {
  }

  void OnMouseWheel(float x, float y, const IMouseMod &mod, float d) {
    //double gearing = IsFineControl(mod, true) ? 0.001 : 0.01;
    double gearing = 0.02;
    SetValue(GetValue() + gearing * d);
    SetDirty(true);
  }

};

class IVSliderControlMidi : public IVSliderControl
{
public:

  IVSliderControlMidi(const IRECT& bounds, int paramIdx = kNoParameter,
    const char* label = "",
    const IVStyle& style = DEFAULT_STYLE,
    bool valueIsEditable = false,
    EDirection dir = EDirection::Vertical, bool onlyHandle = false, float handleSize = 8.f, float trackSize = 2.f, std::function<double(double)> func = NULL)
    : IVSliderControl(bounds, paramIdx ,
      label,
       style,
      valueIsEditable,
       dir , onlyHandle, handleSize , trackSize  ) {
    SetWantsMidi(true);
    mFunc = func;
  }

  void OnMouseWheel(float x, float y, const IMouseMod &mod, float d) {
    //double gearing = IsFineControl(mod, true) ? 0.001 : 0.01;
    double gearing = 0.02;
    SetValue(GetValue() + gearing * d);
    SetDirty(true);
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
          SetDirty(true); // false setzt dirty aber ruft nicht onParamCHange auf.
        }
      }
    }
    else if (paramToMsgType[GetParamIdx()] == 1) { // Aftertouch
      if (msgTmp.StatusMsg() == IMidiMsg::kPolyAftertouch) {
        if (msgTmp.mData1 == paramToCC[GetParamIdx()]) {
          double x = msgTmp.mData2 / 127.;
          if (mFunc) x = mFunc(x);
          SetValue(x);
          SetDirty(true); // false setzt dirty aber ruft nicht onParamCHange auf.;
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
  std::function<double(double)> mFunc;
  int nrpnCC;
  int nrpnVal;
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
          SetDirty(); // false setzt dirty aber ruft nicht onParamCHange auf.
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
  std::function<double(double)> mFunc;
  int nrpnCC;
  int nrpnVal;
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
          if (GetParamIdx() == kParamDelayTimeLBPM || GetParamIdx() == kParamDelayTimeRBPM) {
            x = msg.mData2/18.; //
          }
          if (mFunc) x = mFunc(x);
          SetValue(x);
          SetDirty(); // false setzt dirty aber ruft nicht onParamCHange auf.
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
  std::function<double(double)> mFunc;
  int nrpnCC;
  int nrpnVal;
};

class IBKnobControlMidi : public IBKnobControl
{
public:

  IBKnobControlMidi(float x, float y, const IBitmap& bitmap, int paramIdx, std::function<double(double)> func = NULL, EDirection direction = EDirection::Vertical, double gearing = DEFAULT_GEARING)
    : IBKnobControl(x, y, bitmap, paramIdx, EDirection::Vertical, gearing) {
    SetWantsMidi(true);
    mFunc = func;
  }

  void OnMidi(const IMidiMsg& msg) override
  {
    IMidiMsg msgTmp = msg; // msg const :/
    msgTmp = parseNrpn(msgTmp); // if nrpn generate polyAT, if not nrpn passthrough

    if (paramToMsgType[GetParamIdx()] == 0) { //CC
      if (msgTmp.StatusMsg() == IMidiMsg::kControlChange) {
        if (msgTmp.ControlChangeIdx() == paramToCC[GetParamIdx()]) {
          double x = msgTmp.mData2/127.;
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
          SetDirty();
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
  std::function<double(double)> mFunc;
  int nrpnCC;
  int nrpnVal;
};

class IVKnobControlMidi : public IVKnobControl
{
public:

  IVKnobControlMidi(const IRECT& bounds, int paramIdx,
    const char* label = "",
    const IVStyle& style = DEFAULT_STYLE,
    bool valueIsEditable = false,
    float aMin = -135.f, float aMax = 135.f,
    EDirection direction = EDirection::Vertical, double gearing = DEFAULT_GEARING)

    : IVKnobControl(bounds, paramIdx, label, style, valueIsEditable, aMin, aMax, direction, gearing) {
    SetWantsMidi(true);
    //mFunc = func;
  }

  void OnMidi(const IMidiMsg& msg) override {

    IMidiMsg msgTmp = msg; // msg const :/
    msgTmp = parseNrpn(msgTmp); // if nrpn generate polyAT, if not nrpn passthrough

    if (paramToMsgType[GetParamIdx()] == 0) { //CC
      if (msgTmp.StatusMsg() == IMidiMsg::kControlChange) {
        if (msgTmp.ControlChangeIdx() == paramToCC[GetParamIdx()]) {
          double x = msgTmp.mData2 / 127.;
          //if (mFunc) x = mFunc(x);
          SetValue(x);
          SetDirty(true); // false setzt dirty aber ruft nicht onParamCHange auf.
        }
      }
    }
    else if (paramToMsgType[GetParamIdx()] == 1) { // Aftertouch
      if (msgTmp.StatusMsg() == IMidiMsg::kPolyAftertouch) {
        if (msgTmp.mData1 == paramToCC[GetParamIdx()]) {
          double x = msgTmp.mData2 / 127.;
          //if (mFunc) x = mFunc(x);
          SetValue(x);
          SetDirty(true);
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
  //std::function<double(double)> mFunc;
  int nrpnCC;
  int nrpnVal;
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
          SetDirty(); // false setzt dirty aber ruft nicht onParamCHange auf.
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
  std::function<double(double)> mFunc;
  int nrpnCC;
  int nrpnVal;
};

