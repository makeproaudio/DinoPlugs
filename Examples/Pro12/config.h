#define PLUG_NAME "Pro12"
#define PLUG_MFR "MakeProAudio"
#define PLUG_VERSION_HEX 0x00010000
#define PLUG_VERSION_STR "1.0.0"
#define PLUG_UNIQUE_ID 'Zlg6'
#define PLUG_MFR_ID 'Acme'
#define PLUG_URL_STR "https://iplug2.github.io"
#define PLUG_EMAIL_STR "spam@me.com"
#define PLUG_COPYRIGHT_STR "Copyright 2019 Acme Inc"
#define PLUG_CLASS_NAME Pro12

#define BUNDLE_NAME "Pro12"
#define BUNDLE_MFR "MakeProAudio"
#define BUNDLE_DOMAIN "com"

#define PLUG_CHANNEL_IO "0-2"

/************************************/

#define HEADER_H 0
#define SYNTH_H 430
#define MARGIN_H 0
#define MARGIN_W 0
#define KEYBOARD_H 134
//#define MIDILOG_H 100
#define PRESET_H 240
#define MIDILOG_H 237
#define HS_H HEADER_H+SYNTH_H
#define HSK_H HEADER_H+SYNTH_H+KEYBOARD_H+MARGIN_H*2
#define HS_W 990
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
#define PLUG_WIDTH 990
#define PLUG_HEIGHT 430
#define PLUG_FPS 60
#define PLUG_SHARED_RESOURCES 0

#define AUV2_ENTRY Pro12_Entry
#define AUV2_ENTRY_STR "Pro12_Entry"
#define AUV2_FACTORY Pro12_Factory
#define AUV2_VIEW_CLASS Pro12_View
#define AUV2_VIEW_CLASS_STR "Pro12_View"

#define AAX_TYPE_IDS 'EFN1', 'EFN2'
#define AAX_PLUG_MFR_STR "Acme"
#define AAX_PLUG_NAME_STR "Pro12\nIPIS"
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
#define PNGPANELMAIN_FN "panelmain.png"
#define PNGPANELADD_FN "paneladd.png"
#define PNGPANELEFFECTS_FN "paneleffects.png"
#define PNGBASE_FN "base.png"
#define PNGPITCHWHEEL_FN  "pitchwheel.png"
#define PNGSWITCH_FN  "switch.png"
#define PNGKEYBACK_FN  "keyback.png"
#define PNGKEYB_FN  "keyb.png"
#define PNGMIDIMONITOR_FN  "midiMonitor.png"
#define PNGMIDIMONBACK_FN  "midiMonBack.png"
#define PNGBACK_FN  "back.png"
#define PNGPLUS_FN  "plus.png"
#define PNGMINUS_FN  "minus.png"
#define PNGMIDIACTIVE_FN  "midiactive.png"
#define PNGADD_FN "add.png"
#define PNGMAIN_FN "main.png"
#define PNGEFFECTS_FN "effects.png"
#define PNGKNOB1_FN "knob1.png"
#define PNGKNOB2_FN "knob2.png"
#define PNGHIDE_FN "hide.png"
#define PNGSWITCHBYPASS_FN  "switchBypass.png"
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

