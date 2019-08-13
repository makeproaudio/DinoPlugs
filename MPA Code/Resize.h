#pragma once

auto resizeFunc = [&](IControl* pCaller)
    {

      if (pCaller->GetUI()) {

        mKeybHide = pCaller->GetUI()->GetControlWithTag(kCtrlTagKeybHide)->GetValue();
        mPresetHide = pCaller->GetUI()->GetControlWithTag(kCtrlTagMidiMonHide)->GetValue();
        mMixerHide = pCaller->GetUI()->GetControlWithTag(kCtrlTagMixerHide)->GetValue();

        if (mPresetHide == 1 && (mKeybHide == 1 || mMixerHide == 1)) {
          pCaller->GetUI()->Resize(HSM_W, HSK_H, 1);
        }
        else if (mPresetHide == 1 && (mKeybHide == 0 && mMixerHide == 0)) {
          pCaller->GetUI()->Resize(HSM_W, HS_H, 1);
        }
        else if (mPresetHide == 0 && (mKeybHide == 0 && mMixerHide == 0)) {
          pCaller->GetUI()->Resize(HS_W, HS_H, 1);
        }
        else if (mPresetHide == 0 && (mKeybHide == 1 || mMixerHide == 1)) {
          pCaller->GetUI()->Resize(HS_W, HSK_H, 1);
        }
      }

      if (pCaller->GetTag() == kCtrlTagMixerHide) {
        pCaller->GetUI()->ForControlInGroup("keyboard", [&](IControl& control) {control.Hide(true); });
        pCaller->GetUI()->ForControlInGroup("Mixer", [&](IControl& control) {control.Hide(false); });
        if (pCaller->GetUI()->GetControlWithTag(kCtrlTagKeybHide)->GetValue() == 1) {
          pCaller->GetUI()->GetControlWithTag(kCtrlTagKeybHide)->SetValue(0);
          pCaller->GetUI()->GetControlWithTag(kCtrlTagKeybHide)->SetDirty(false);
        }
        mKeybHide = 0;
      }
      else if (pCaller->GetTag() == kCtrlTagKeybHide) {
        pCaller->GetUI()->ForControlInGroup("keyboard", [&](IControl& control) {control.Hide(false); });
        pCaller->GetUI()->ForControlInGroup("Mixer", [&](IControl& control) {control.Hide(true); });
        if (pCaller->GetUI()->GetControlWithTag(kCtrlTagMixerHide)->GetValue() == 1) {
          pCaller->GetUI()->GetControlWithTag(kCtrlTagMixerHide)->SetValue(0);
          pCaller->GetUI()->GetControlWithTag(kCtrlTagMixerHide)->SetDirty(false);
        }
        mMixerHide = 0;
      }
      pCaller->SetDirty(false);
    };