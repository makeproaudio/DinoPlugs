#include "Scrollbar.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"
#include "IPlugPaths.h"
#include "IconsForkAwesome.h"

class IVCustomControl : public IControl
                      , public IVectorBase
{
public:
  IVCustomControl(const IRECT& bounds, const char* label, const IVStyle& style)
  : IControl(bounds)
  , IVectorBase(style)
  {
    AttachIControl(this, label);
  }

  void OnInit() override
  {
    mValueStr.Set("Test");
  }
  
  void Draw(IGraphics& g) override
  {
    DrawBackGround(g, mRECT);
    DrawWidget(g);
    DrawLabel(g);
    DrawValue(g, mMouseIsOver);
  }
  
  virtual void DrawWidget(IGraphics& g) override
  {
    g.FillRect(GetColor(kFG), mWidgetBounds);
  }
  
  void OnResize() override
  {
    SetTargetRECT(CalculateRects(mRECT));
  }
};




Scrollbar::Scrollbar(IPlugInstanceInfo instanceInfo)
: IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo)
{
  GetParam(kGain)->InitDouble("Gain", 100., 0., 100.0, 0.01, "%");
 
#if IPLUG_EDITOR // All UI methods and member variables should be within an IPLUG_EDITOR guard, should you want distributed UI
  mMakeGraphicsFunc = [&]() {
    return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS, 1.);
  };
  
  mLayoutFunc = [&](IGraphics* pGraphics) {
    if(pGraphics->NControls())
    {
      //Could handle new layout here
      return;
    }
    
//    pGraphics->EnableLiveEdit(true);
    pGraphics->HandleMouseOver(true);
    pGraphics->AttachCornerResizer(EUIResizerMode::Scale, true);
    pGraphics->AttachPanelBackground(COLOR_GRAY);
    pGraphics->EnableTooltips(true);
    pGraphics->AttachTextEntryControl();
    pGraphics->AttachPopupMenuControl();
    
    IRECT b = pGraphics->GetBounds().GetPadded(-5);
    
    pGraphics->LoadFont("Roboto-Regular", ROBOTO_FN);
    pGraphics->LoadFont("ForkAwesome", FORK_AWESOME_FN);

    mMidiLogger = new MidiMonitor(IRECT(10, 10, 400, 400), "", "", IText(12, COLOR_BLACK, NULL, EAlign::Near), COLOR_WHITE);
    pGraphics->AttachControl(mMidiLogger, kCtrlTagMidiLogger, "midiMonitor");

    IMidiMsg msg;
    for (int k = 0; k < 70; k++) {
      msg.MakeNoteOnMsg(k, 33, 0, 3);
     // WDL_String str;
      //str.Set("Hallo");
      mMidiLoggerSender.SetValRT(msg);
    }
    msg.MakeNoteOnMsg(1, 44, 0, 3);
    mMidiLoggerSender.SetValRT(msg);
    msg.MakeNoteOnMsg(2, 44, 0, 3);
    mMidiLoggerSender.SetValRT(msg);
    msg.MakeNoteOnMsg(3, 44, 0, 3);
    mMidiLoggerSender.SetValRT(msg);

    slider = (new IVSliderControl(IRECT(410, 10, 440, 400), [&](IControl* ctrl) {

      mMidiLogger->setEntrypointerOffset(1. - ctrl->GetValue());

    }));
    pGraphics->AttachControl(slider, kCtrlSlider);



    /////////////////////////////

    /*mPresetMonitor = new PresetMonitor(IRECT(10+500, 10, 400+500, 400), "", "", IText(12, COLOR_BLACK, NULL, EAlign::Near), COLOR_WHITE);
    pGraphics->AttachControl(mPresetMonitor, kCtrlPresetMonitor, "midiMonitor");

    presettext a;

    for (int k = 50; k > 0; k--) {
      char buffer[30];
      sprintf(buffer, "User %d", k);
      strcpy(a.name,buffer);
      mPresetMonitorSender.SetValRT(a);
    }


   


    slider2 = (new IVSliderControl(IRECT(410+500, 10, 440+500, 400), [&](IControl* ctrl) {

      mPresetMonitor->setEntrypointerOffset(1. - ctrl->GetValue());

    }));
    pGraphics->AttachControl(slider2, kCtrlSlider2);*/

    //////////////////////////////////////////////////////////

    /*IVButtonControl* buttCtrl = new IVButtonControl(IRECT(400, 370, 430, 400), [&](IControl*) {
      mMidiLogger->incrementEntrypointerOffset();
      double x = mMidiLogger->GetNormalizedEntryPointerOffset();
      //slider->SetValueFromUserInput(x);
    },

      "-", IVStyle(DEFAULT_SHOW_LABEL, DEFAULT_SHOW_VALUE, {}, IText(12)));

    buttCtrl->SetAnimation(DefaultAnimationFunc);
    pGraphics->AttachControl(buttCtrl, -1, "keyboard");
    */
    //IVButtonControl* buttCtrl2 = new IVButtonControl(IRECT(400, 10, 430, 40), [&](IControl*) {
    //  mMidiLogger->decrementEntrypointerOffset();
    //  double x = mMidiLogger->GetNormalizedEntryPointerOffset();
     // slider->SetValueFromUserInput(x);
    //},

    //  "+", IVStyle(DEFAULT_SHOW_LABEL, DEFAULT_SHOW_VALUE, {}, IText(12)));

    //buttCtrl2->SetAnimation(DefaultAnimationFunc);
    //pGraphics->AttachControl(buttCtrl2, -1, "keyboard");
    

  };
#endif
}

#if IPLUG_DSP
void Scrollbar::OnIdle()
{
  mMidiLoggerSender.TransmitData(*this);
  //mPresetMonitorSender.TransmitData(*this);
}

void Scrollbar::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
  for (int s = 0; s < nFrames; s++) {
    outputs[0][s] = 0.;
    outputs[1][s] = 0.;
  }
}
#endif
