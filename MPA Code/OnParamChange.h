#pragma once

if (msg.mStatus != msgAlt.mStatus || msg.mData1 != msgAlt.mData1 || msg.mData2 != msgAlt.mData2) {
  if (mDeveloperActive == 1 && paramToMsgType[paramIdx] == 1 && ccIsNRPN[paramToCC[paramIdx]] == 1) { // developer mode
    IMidiMsg msg2;
    msg2.Clear();
    msg2.mStatus = mChannel | (IMidiMsg::kControlChange << 4);
    msg2.mData1 = 99;
    msg2.mData2 = 0;
    msg2.mOffset = -2;
    SendMidiMsgFromUI(msg2);
    msg2.Clear();
    msg2.mStatus = mChannel | (IMidiMsg::kControlChange << 4);
    msg2.mData1 = 98;
    msg2.mData2 = paramToCC[paramIdx];
    msg2.mOffset = -2;
    SendMidiMsgFromUI(msg2);
    msg2.Clear();
    msg2.mStatus = mChannel | (IMidiMsg::kControlChange << 4);
    msg2.mData1 = 6;
    msg2.mData2 = 0;
    msg2.mOffset = -2;
    SendMidiMsgFromUI(msg2);
    msg2.Clear();
    msg2.mStatus = mChannel | (IMidiMsg::kControlChange << 4);
    msg2.mData1 = 38;
    msg2.mData2 = msg.mData2;
    msg2.mOffset = -2;
    SendMidiMsgFromUI(msg2);
  }
  else {
    SendMidiMsgFromUI(msg);
  }
}
  msgAlt = msg;
