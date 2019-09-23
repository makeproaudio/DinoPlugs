#pragma once

	// MIXER UI

    bitmap = pGraphics->LoadBitmap(FN_MIXERBACK);

    int mixerLeft = HS_W / 2. - bitmap.W() / 2.; // center Mixer

    IControl* mixerBackCtrl = new IBitmapControl(MARGIN_W+ mixerLeft, SYNTH_H+MARGIN_H, bitmap, kNoParameter);
    pGraphics->AttachControl(mixerBackCtrl, -1, "Mixer");

    

    bitmap = pGraphics->LoadBitmap(FN_KNOBMIXER, 91, true);
    pGraphics->AttachControl(new IBKnobControlMidi(mixerLeft+35-11, SYNTH_H+49-11, bitmap, kParamMixerDrive), -1, "Mixer");
    pGraphics->AttachControl(new IBKnobControlMidi(mixerLeft + 35-11, SYNTH_H+104-11, bitmap, kParamMixerBass), -1, "Mixer");
    pGraphics->AttachControl(new IBKnobControlMidi(mixerLeft + 105-11, SYNTH_H+104-11, bitmap, kParamMixerTreble), -1, "Mixer");
    pGraphics->AttachControl(new IBKnobControlMidi(mixerLeft + 105-11, SYNTH_H+49-11, bitmap, kParamMixerBalance), -1, "Mixer");



    IVStyle style;
    style.hideCursor = false;
    style.valueText = IText(0);
    //style.

//#if defined IGRAPHICS_NANOVG
    pGraphics->AttachControl(new IVSliderControlMidi(IRECT(mixerLeft + 147, SYNTH_H + 24, mixerLeft + 147 +15, SYNTH_H + 126), kParamMixerLevel, "", style), -1, "Mixer");

/*#elif defined IGRAPHICS_LICE
    bitmap = pGraphics->LoadBitmap(PNGSLIDER_FN, 1);
    pGraphics->AttachControl(new IBSliderControlScroll(mixerLeft + 147, SYNTH_H + 24, 102, kParamMixerLevel, bitmap), -1, "Mixer");
#endif*/

    IBKnobControlMidi *knobCtrl = new IBKnobControlMidi(mixerLeft + 253-1, SYNTH_H + 49-11, bitmap, kParamLAIGain);
    knobCtrl->SetActionFunction([&](IControl* ctrl) {
      if (GetUI()->GetControlWithTag(kCtrlMixerLink)->GetValue() == 1) {
        GetUI()->GetControlWithTag(kCtrlRAIGain)->SetValueFromUserInput(ctrl->GetValue());
      }
      });
    pGraphics->AttachControl(knobCtrl, kCtrlLAIGain, "Mixer");

    knobCtrl = new IBKnobControlMidi(mixerLeft + 253-1, SYNTH_H + 104-11, bitmap, kParamLAIBass);
    knobCtrl->SetActionFunction([&](IControl* ctrl) {if (GetUI()->GetControlWithTag(kCtrlMixerLink)->GetValue() == 1) { GetUI()->GetControlWithTag(kCtrlRAIBass)->SetValueFromUserInput(ctrl->GetValue()); } });
    pGraphics->AttachControl(knobCtrl, kCtrlLAIBass, "Mixer");

    knobCtrl = new IBKnobControlMidi(mixerLeft + 323-1, SYNTH_H + 104-11, bitmap, kParamLAITreble);
    knobCtrl->SetActionFunction([&](IControl* ctrl) {if (GetUI()->GetControlWithTag(kCtrlMixerLink)->GetValue() == 1) { GetUI()->GetControlWithTag(kCtrlRAITreble)->SetValueFromUserInput(ctrl->GetValue()); } });
    pGraphics->AttachControl(knobCtrl, kCtrlLAITreble, "Mixer");

    pGraphics->AttachControl(new IBKnobControlMidi(mixerLeft + 323-1, SYNTH_H + 49-11, bitmap, kParamLAIPan), kCtrlLAIPan, "Mixer");

    //style.showValue = false;
    IVSliderControlMidi *sliderCtrl = new IVSliderControlMidi(IRECT(mixerLeft + 364+10, SYNTH_H + 24, mixerLeft + 364 +10+15, SYNTH_H + 126), kParamLAILevel, "", style);
    sliderCtrl->SetActionFunction([&](IControl* ctrl) {if (GetUI()->GetControlWithTag(kCtrlMixerLink)->GetValue() == 1) { GetUI()->GetControlWithTag(kCtrlRAILevel)->SetValueFromUserInput(ctrl->GetValue()); } });
    pGraphics->AttachControl(sliderCtrl, kCtrlLAILevel, "Mixer");



    knobCtrl = new IBKnobControlMidi(mixerLeft + 468 +9, SYNTH_H + 49 - 11, bitmap, kParamRAIGain);
    knobCtrl->SetActionFunction([&](IControl* ctrl) {if (GetUI()->GetControlWithTag(kCtrlMixerLink)->GetValue() == 1) { GetUI()->GetControlWithTag(kCtrlLAIGain)->SetValueFromUserInput(ctrl->GetValue()); } });
    pGraphics->AttachControl(knobCtrl, kCtrlRAIGain, "Mixer");

    knobCtrl = new IBKnobControlMidi(mixerLeft + 468 + 10, SYNTH_H + 104 - 11, bitmap, kParamRAIBass);
    knobCtrl->SetActionFunction([&](IControl* ctrl) {if (GetUI()->GetControlWithTag(kCtrlMixerLink)->GetValue() == 1) { GetUI()->GetControlWithTag(kCtrlLAIBass)->SetValueFromUserInput(ctrl->GetValue()); } });
    pGraphics->AttachControl(knobCtrl, kCtrlRAIBass, "Mixer");


    knobCtrl = new IBKnobControlMidi(mixerLeft + 538 + 10, SYNTH_H + 104 - 11, bitmap, kParamRAITreble);
    knobCtrl->SetActionFunction([&](IControl* ctrl) {if (GetUI()->GetControlWithTag(kCtrlMixerLink)->GetValue() == 1) { GetUI()->GetControlWithTag(kCtrlLAITreble)->SetValueFromUserInput(ctrl->GetValue()); } });
    pGraphics->AttachControl(knobCtrl, kCtrlRAITreble, "Mixer");

//    knobCtrl = new IBKnobControlMidi(625, SYNTH_H + 104, bitmap, kParamRAITrebleFreq);
//    knobCtrl->SetActionFunction([&](IControl* ctrl) {if (GetUI()->GetControlWithTag(kCtrlMixerLink)->GetValue() == 1) { GetUI()->GetControlWithTag(kCtrlLAITrebleFreq)->SetValueFromUserInput(ctrl->GetValue()); } });
//    pGraphics->AttachControl(knobCtrl, kCtrlRAITrebleFreq, "Mixer");

//    knobCtrl = new IBKnobControlMidi(559, SYNTH_H + 104, bitmap, kParamRAIBassFreq);
//    knobCtrl->SetActionFunction([&](IControl* ctrl) {if (GetUI()->GetControlWithTag(kCtrlMixerLink)->GetValue() == 1) { GetUI()->GetControlWithTag(kCtrlLAIBassFreq)->SetValueFromUserInput(ctrl->GetValue()); } });
//    pGraphics->AttachControl(knobCtrl, kCtrlRAIBassFreq, "Mixer");


    pGraphics->AttachControl(new IBKnobControlMidi(mixerLeft + 538 + 9, SYNTH_H + 49 - 11, bitmap, kParamRAIPan), kCtrlRAIPan, "Mixer");

    sliderCtrl = new IVSliderControlMidi(IRECT(mixerLeft + 580+20, SYNTH_H + 24, mixerLeft + 580 +20+15, SYNTH_H + 126), kParamRAILevel, "", style);
    sliderCtrl->SetActionFunction([&](IControl* ctrl) {if (GetUI()->GetControlWithTag(kCtrlMixerLink)->GetValue() == 1) { GetUI()->GetControlWithTag(kCtrlLAILevel)->SetValueFromUserInput(ctrl->GetValue()); } });
    pGraphics->AttachControl(sliderCtrl, kCtrlRAILevel, "Mixer");

    bitmap = pGraphics->LoadBitmap(FN_LINK,2);
    IBSwitchControlMidi *switchCtrl = new IBSwitchControlMidi(mixerLeft + 393+20, SYNTH_H + 5, bitmap, kParamMixerLink);
    switchCtrl->SetActionFunction([&](IControl* ctrl) {if (ctrl->GetValue() == 1) {
      GetUI()->GetControlWithTag(kCtrlRAIPan)->SetValueFromUserInput(1.); GetUI()->GetControlWithTag(kCtrlRAIPan)->GrayOut(true);  GetUI()->GetControlWithTag(kCtrlLAIPan)->SetValueFromUserInput(0.); GetUI()->GetControlWithTag(kCtrlLAIPan)->GrayOut(true);
    }
    else {
      GetUI()->GetControlWithTag(kCtrlLAIPan)->GrayOut(false); GetUI()->GetControlWithTag(kCtrlRAIPan)->GrayOut(false);
    }
      });
    pGraphics->AttachControl(switchCtrl, kCtrlMixerLink, "Mixer");