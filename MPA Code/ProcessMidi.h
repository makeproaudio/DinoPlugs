#pragma once

if (msg.mOffset != -2)
{
  // Bankselect -> MIDIactive
  if (msg.StatusMsg() == IMidiMsg::kControlChange)
  {
    if (msg.ControlChangeIdx() == 0)
    { // Bankselect
      if (msg.mData2 == PLUGIN_ID)
      {
        if (GetUI() && GetUI()->GetControlWithTag(kCtrlMidiActive))
        {
          GetUI()->GetControlWithTag(kCtrlMidiActive)->SetValue(1);
          GetUI()->GetControlWithTag(kCtrlMidiActive)->SetDirty(); // false setzt dirty aber ruft nicht onParamCHange auf.
          mMidiActive = true;
        }
      }
      else
      {
        if (GetUI() && GetUI()->GetControlWithTag(kCtrlMidiActive))
        {
          GetUI()->GetControlWithTag(kCtrlMidiActive)->SetValue(0);
          GetUI()->GetControlWithTag(kCtrlMidiActive)->SetDirty(); // false setzt dirty aber ruft nicht onParamCHange auf.
          mMidiActive = false;
        }
      }

      if (!mMidiActive)
      {
        if (GetUI())
        {
          for (auto c = 0; c < GetUI()->NControls(); c++) // TODO: could keep a map
          {
            IControl* pControl = GetUI()->GetControl(c);
            pControl->SetWantsMidi(false);
          }
        }
      }
      else
      {
        if (GetUI())
        {
          for (auto c = 0; c < GetUI()->NControls(); c++) // TODO: could keep a map
          {
            IControl* pControl = GetUI()->GetControl(c);
            pControl->SetWantsMidi(true);
          }
        }
      }
    }
  }
}

if (mMidiActive) {

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


    if (msg.StatusMsg() == IMidiMsg::kControlChange)
    {
      if (msg.ControlChangeIdx() == 32)
      { // Bankselect
        if (GetUI() && GetUI()->GetControlWithTag(kCtrlUserFactory))
        {
          if (msg.mData2 == 0) // factory
          {
            GetUI()->GetControlWithTag(kCtrlUserFactory)->SetValue(0);
            GetUI()->GetControlWithTag(kCtrlUserFactory)->SetDirty(false); // false setzt dirty aber ruft nicht onParamCHange auf.
            GetParam(kParamUserFactory)->Set(0);
          }
          else if (msg.mData2 == 1)
          {
            GetUI()->GetControlWithTag(kCtrlUserFactory)->SetValue(1);
            GetUI()->GetControlWithTag(kCtrlUserFactory)->SetDirty(false); // false setzt dirty aber ruft nicht onParamCHange auf.
            GetParam(kParamUserFactory)->Set(1);
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