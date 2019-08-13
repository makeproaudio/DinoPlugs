#pragma once

IRECT keybRect = IRECT(MARGIN_W, HS_H + MARGIN_H, PLUG_WIDTH - MARGIN_W, HS_H + MARGIN_H + KEYBOARD_H);
IRECT keys = keybRect.FracRectHorizontal(0.85);
keybCtrl = new IVKeyboardControl(keys, 36, 91);
pGraphics->AttachControl(keybCtrl, kCtrlTagKeyboard, "keyboard");

IRECT rect2 = keybRect.GetReducedFromLeft(keys.W());

IText tx(10, COLOR_WHITE, "Calibrib");
pGraphics->AttachControl(new ICaptionControl(IRECT(rect2.MW() - 20, HS_H +50, rect2.MW() + 20, HS_H + 70), kParamKeyboardOctave, tx, COLOR_BLACK, true), -1, "keyboard");
IText text(14, COLOR_WHITE, "Calibrib");
pGraphics->AttachControl(new ITextControl(IRECT(rect2.MW() - 25, HS_H + 10, rect2.MW() + 25, HS_H + 50), "Octave", text), -1, "keyboard");

bitmap = pGraphics->LoadBitmap(PNGALLNOTESOFF_FN);
IBButtonControl* buttCtrl = new IBButtonControl(rect2.MW() - bitmap.W() / 2., HS_H + 90, bitmap, [&](IControl*) {
  IMidiMsg msg;
  msg.Clear();
  msg.mStatus = mChannel | (IMidiMsg::kControlChange << 4);
  msg.mData1 = IMidiMsg::kAllNotesOff;
  msg.mData2 = 0;
  msg.mOffset = -2;
  SendMidiMsgFromUI(msg);
  }

);
pGraphics->AttachControl(buttCtrl, -1, "keyboard");