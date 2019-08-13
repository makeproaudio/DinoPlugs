#define PLUG_NAME "B4000"
#define PLUG_MFR "MakeProAudio"
#define PLUG_VERSION_HEX 0x00010000
#define PLUG_VERSION_STR "1.0.0"
#define PLUG_UNIQUE_ID 'yncC'
#define PLUG_MFR_ID 'Acme'
#define PLUG_URL_STR "https://iplug2.github.io"
#define PLUG_EMAIL_STR "spam@me.com"
#define PLUG_COPYRIGHT_STR "Copyright 2019 Acme Inc"
#define PLUG_CLASS_NAME B4000

#define BUNDLE_NAME "B4000"
#define BUNDLE_MFR "MakeProAudio"
#define BUNDLE_DOMAIN "com"

#define PLUG_CHANNEL_IO "0-2"

/************************************/

#define HEADER_H 0
#define SYNTH_H 414
#define MARGIN_H 0
#define MARGIN_W 0
#define KEYBOARD_H 134
//#define MIDILOG_H 100
#define PRESET_H 240
#define MIDILOG_H 237
#define HS_H HEADER_H+SYNTH_H
#define HSK_H HEADER_H+SYNTH_H+KEYBOARD_H+MARGIN_H*2
#define HS_W 799
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
#define PLUG_WIDTH 799
#define PLUG_HEIGHT 414
#define PLUG_FPS 60
#define PLUG_SHARED_RESOURCES 0

#define AUV2_ENTRY B4000_Entry
#define AUV2_ENTRY_STR "B4000_Entry"
#define AUV2_FACTORY B4000_Factory
#define AUV2_VIEW_CLASS B4000_View
#define AUV2_VIEW_CLASS_STR "B4000_View"

#define AAX_TYPE_IDS 'EFN1', 'EFN2'
#define AAX_PLUG_MFR_STR "Acme"
#define AAX_PLUG_NAME_STR "B4000\nIPIS"
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
#define PNGPANEL_FN "panel.png"
#define PNGMAINPANEL_FN "mainpanel.png"
#define PNGADDPANEL_FN "addpanel.png"
#define PNGMAIN_FN "main.png"
#define PNGADD_FN "add.png"
#define PNGB4000KNOB_FN "B4000knob.png"
#define PNGTICKTICK_FN "ticktick.png"
#define PNGB4000KNOB1_FN "B4000knob1.png"
#define PNGTOPKNOB_FN "topknob.png"
#define PNGOCT_FN "oct.png"
#define PNGBROWNDRAWBARKNOB_FN "browndrawbarKnob.png"
#define PNGGREYDRAWBARKNOB_FN "greydrawbarKnob.png"
#define PNGWHITEDRAWBARKNOB_FN "whitedrawbarKnob.png"
#define PNGDRIVE_FN "drive.png"
#define PNGVELOCITY_FN "velocity.png"
#define PNGVIBRALO_FN "vibralo.png"
#define PNGVIBRAHI_FN "vibrahi.png"
#define PNGROTOR_FN "rotor.png"
#define PNGPERCUSSION_FN "percussion.png"
#define PNGTICKTICK3_FN "ticktick3.png"
#define PNGFASTSLOW_FN "fastslow.png"
#define PNGKNOB2_FN "knob2.png"
#define PNGLENGTH_FN "length.png"
#define PNGTIME_FN "time.png"
#define PNGPLUS_FN  "plus.png"
#define PNGMINUS_FN  "minus.png"
#define PNGMIDIACTIVE_FN  "midiactive.png"
#define PNGKEYB_FN  "keyb.png"
#define PNGMIDIMONITOR_FN  "midiMonitor.png"
#define PNGTICKTICKBYPASS_FN "ticktickBypass.png"
#define PNGHEADER_FN "header.png"
#define PNGCLEAR_FN "clear.png"
#define PNGOVERWRITE_FN "overwrite.png"
#define PNGRECALL_FN "recall.png"
#define PNGLOAD_FN "load.png"
#define PNGSAVE_FN "save.png"
#define PNGSLIDER_FN "slider.png"
#define PNGMIDIMONBACK_FN  "midiMonBack.png"
#define PNGMIXERBACK_FN "mixerback.png"
#define PNGKNOBMIXER_FN "knobmixer.png"
#define PNGMIXER_FN "mixer.png"
#define PNGLINK_FN "link.png"
#define PNGDEVELOPER_FN "developer.png"
#define PNGMPA_FN "mpa.png"
#define PNGALLNOTESOFF_FN "allnotesoff.png"
#define PNGRESET_FN "reset.png"

