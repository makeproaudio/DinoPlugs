#define PLUG_NAME "Lightwave"
#define PLUG_MFR "MakeProAudio"
#define PLUG_VERSION_HEX 0x00010000
#define PLUG_VERSION_STR "1.0.0"
#define PLUG_UNIQUE_ID 'rpWK'
#define PLUG_MFR_ID 'Acme'
#define PLUG_URL_STR "https://iplug2.github.io"
#define PLUG_EMAIL_STR "spam@me.com"
#define PLUG_COPYRIGHT_STR "Copyright 2019 Acme Inc"
#define PLUG_CLASS_NAME Lightwave

#define BUNDLE_NAME "Lightwave"
#define BUNDLE_MFR "MakeProAudio"
#define BUNDLE_DOMAIN "com"

#define PLUG_CHANNEL_IO "0-2"

/************************************/

#define HEADER_H 0
#define SYNTH_H 382
#define MARGIN_H 0
#define MARGIN_W 0
#define KEYBOARD_H 134
//#define MIDILOG_H 100
#define PRESET_H 240
#define MIDILOG_H 237
#define HS_H HEADER_H+SYNTH_H
#define HSK_H HEADER_H+SYNTH_H+KEYBOARD_H+MARGIN_H*2
#define HS_W 969
#define MIDIPRESET_W 240
#define HSM_W HS_W + MIDIPRESET_W
//#define HSM_H HEADER_H+SYNTH_H+MIDILOG_H+MARGIN_H*2
//#define HSKM_H HEADER_H+SYNTH_H+KEYBOARD_H+MIDILOG_H+MARGIN_H*4

/*************************/

#define PLUG_LATENCY 0
#define PLUG_TYPE 1
#define PLUG_DOES_MIDI_IN 1
#define PLUG_DOES_MIDI_OUT 1
#define PLUG_DOES_MPE 1
#define PLUG_DOES_STATE_CHUNKS 0
#define PLUG_HAS_UI 1
#define PLUG_WIDTH 969
#define PLUG_HEIGHT 382
#define PLUG_FPS 60
#define PLUG_SHARED_RESOURCES 0

#define AUV2_ENTRY Lightwave_Entry
#define AUV2_ENTRY_STR "Lightwave_Entry"
#define AUV2_FACTORY Lightwave_Factory
#define AUV2_VIEW_CLASS Lightwave_View
#define AUV2_VIEW_CLASS_STR "Lightwave_View"

#define AAX_TYPE_IDS 'EFN1', 'EFN2'
#define AAX_PLUG_MFR_STR "Acme"
#define AAX_PLUG_NAME_STR "Lightwave\nIPIS"
#define AAX_DOES_AUDIOSUITE 0
#define AAX_PLUG_CATEGORY_STR "Synth"

#define VST3_SUBCATEGORY "Instrument|Synth"

#define APP_NUM_CHANNELS 2
#define APP_N_VECTOR_WAIT 0
#define APP_MULT 1
#define APP_COPY_AUV3 0
#define APP_RESIZABLE 0
#define APP_SIGNAL_VECTOR_SIZE 64



#define ROBOTTO_FN "Roboto-Regular.ttf"
#define CALIBRI_FN "calibrib.ttf"
#define CALIBRID_FN "calibri.ttf"
#define PNGSWITCHBLUEH_FN "switchBlueH.png"
#define PNGSWITCHBLUEV_FN "switchBlueV.png"
#define PNGSWITCHREDH_FN "switchRedH.png"
#define PNGSWITCHREDV_FN "switchRedV.png"
#define PNGSWITCHSILVERH_FN "switchSilverH.png"
#define PNGPITCHWHEEL14_FN "pitchwheel14.png"
#define PNGADD_FN "add.png"
#define PNGMAIN_FN "main.png"
#define PNGPANELADD_FN "paneladd.png"
#define PNGPANELMAIN_FN "panelmain.png"
#define PNGKEYBACK_FN "keyback.png"
#define PNGKEYB_FN "keyb.png"
#define PNGMIDIMONITOR_FN "midiMonitor.png"
#define PNGMIDIMONBACK_FN "midiMonBack.png"
#define PNGBACK_FN "back.png"
#define PNGPLUS_FN  "plus.png"
#define PNGMINUS_FN  "minus.png"
#define PNGMIDIACTIVE_FN  "midiactive.png"
#define PNGKNOB2_FN "knob2.png"
#define PNGKNOB6_FN "knob6.png"
#define PNGKNOB32_FN "knob32.png"
#define PNGKNOB34_FN "knob34.png"
#define PNGKNOBBG_FN "knobbg.png"
#define PNGSWITCHREDHBYPASS_FN "switchRedHBypass.png"
#define PNGSWITCHSILVERH2_FN "switchSilverH2.png"
#define PNGHEADER_FN "header.png"
#define PNGCLEAR_FN "clear.png"
#define PNGOVERWRITE_FN "overwrite.png"
#define PNGRECALL_FN "recall.png"
#define PNGLOAD_FN "load.png"
#define PNGSAVE_FN "save.png"
#define PNGSLIDER_FN "slider.png"
#define PNGMIXERBACK_FN "mixerback.png"
#define PNGKNOBMIXER_FN "knobmixer.png"
#define PNGMIXER_FN "mixer.png"
#define PNGLINK_FN "link.png"
#define PNGDEVELOPER_FN "developer.png"
#define PNGMPA_FN "mpa.png"
#define PNGALLNOTESOFF_FN "allnotesoff.png"
#define PNGRESET_FN "reset.png"

