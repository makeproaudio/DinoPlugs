#pragma once

// offset -2: von GUI, offset -3: bank change program change soll immer gesendet werden.
if (msg.mOffset != -2 && msg.mOffset != -3)
{  
  // Wenn Bankselect, mit korrektem Plugin ID dann aktiviere midi -> MIDIactive
  if (msg.StatusMsg() == IMidiMsg::kControlChange)
  {
    if (msg.ControlChangeIdx() == 0)
    { // Bankselect
      if (msg.mData2 == PLUGIN_ID)
      {
        //if (GetUI() && GetUI()->GetControlWithTag(kCtrlMidiActive)) GetUI()->GetControlWithTag(kCtrlMidiActive)->SetValueFromUserInput(1.); // wird nur geupdated (WantsMIDI) wenn neuer Wert != alter Wert
        GetUI()->GetControlWithTag(kCtrlMidiActive)->SetValue(1.);
        GetUI()->GetControlWithTag(kCtrlMidiActive)->SetDirty(true);
      }
      else
      {
        if (GetUI() && GetUI()->GetControlWithTag(kCtrlMidiActive)) GetUI()->GetControlWithTag(kCtrlMidiActive)->SetValueFromUserInput(0.);
      }
    }
  }
}

if (msg.mOffset == -3) { // bank change program change immer senden

  int status = msg.StatusMsg();

  switch (status)
  {
  case IMidiMsg::kNoteOn:
  case IMidiMsg::kNoteOff:
  case IMidiMsg::kPolyAftertouch:
  case IMidiMsg::kControlChange:
  case IMidiMsg::kProgramChange:
  case IMidiMsg::kChannelAftertouch:
  case IMidiMsg::kPitchWheel:
  {
    SendMidiMsg(msg); // nach außen
    mMidiLoggerSender.SetValRT(msg);
  }
  default:
    return;
  }
}

if (GetParam(kParamMidiActive)->Value()) {

  if (msg.mOffset == -2) { // From UI

    int status = msg.StatusMsg();

    switch (status)
    {
    case IMidiMsg::kNoteOn:
    case IMidiMsg::kNoteOff:
    case IMidiMsg::kPolyAftertouch:
    case IMidiMsg::kControlChange:
    case IMidiMsg::kProgramChange:
    case IMidiMsg::kChannelAftertouch:
    case IMidiMsg::kPitchWheel:
    {
      SendMidiMsg(msg); // nach außen
      mMidiLoggerSender.SetValRT(msg);
    }
    default:
      return;
    }
  }
  else { // From MIDI IN

    int status = msg.StatusMsg();

    if (status == IMidiMsg::kNoteOn)
    {
      SendMidiMsg(msg); // nach außen
      mMidiLoggerSender.SetValRT(msg);
    }
    if (status == IMidiMsg::kNoteOff)
    {
      SendMidiMsg(msg); // nach außen
      mMidiLoggerSender.SetValRT(msg);
    }
	  if (status == IMidiMsg::kChannelAftertouch)
    {
      SendMidiMsg(msg); // nach außen
      mMidiLoggerSender.SetValRT(msg);
    }


    if (msg.StatusMsg() == IMidiMsg::kControlChange)
    {
      if (msg.ControlChangeIdx() == 32)
      { // Bankselect
        if (GetUI() && GetUI()->GetControlWithTag(kCtrlUserFactory))
        {
          if (msg.mData2 == 0) // factory
          {
            GetUI()->GetControlWithTag(kCtrlUserFactory)->SetValueFromUserInput(0.);
          }
          else if (msg.mData2 == 1)
          {
            GetUI()->GetControlWithTag(kCtrlUserFactory)->SetValueFromUserInput(1.);
          }
        }
      }
    }

    if (msg.StatusMsg() == IMidiMsg::kProgramChange)
    {
      if (GetUI() && GetUI()->GetControlWithTag(kCtrlProgram))
      {
        GetUI()->GetControlWithTag(kCtrlProgram)->SetValue((double)msg.mData1 / (mPresetList->maxLogSamples - 1.));
        GetUI()->GetControlWithTag(kCtrlProgram)->SetDirty(false); // false setzt dirty aber ruft nicht onParamCHange auf.
        GetParam(kParamProgram)->Set(msg.mData1);
        mPresetList->setActiveRow(GetParam(kParamProgram)->Value());
      }
    }
  }
}