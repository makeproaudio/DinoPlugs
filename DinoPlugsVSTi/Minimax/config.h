#define PLUG_NAME "Minimax"
#define PLUG_MFR "MakeProAudio"
#define PLUG_VERSION_HEX 0x00010000
#define PLUG_VERSION_STR "1.0.0"
#define PLUG_UNIQUE_ID 'vLnZ'
#define PLUG_MFR_ID 'MPA'
#define PLUG_URL_STR "https://iplug2.github.io"
#define PLUG_EMAIL_STR "spam@me.com"
#define PLUG_COPYRIGHT_STR "Copyright 2019 MPA Inc"
#define PLUG_CLASS_NAME Minimax

#define BUNDLE_NAME "Minimax"
#define BUNDLE_MFR "MakeProAudio"
#define BUNDLE_DOMAIN "com"

#define PLUG_CHANNEL_IO "0-0"

/************************************/

#define HEADER_H 0
#define SYNTH_H 382
#define MARGIN_H 0
#define MARGIN_W 0
#define KEYBOARD_H 134
#define PRESET_H 240
#define MIDILOG_H 237
#define HS_H HEADER_H+SYNTH_H
#define HSK_H HEADER_H+SYNTH_H+KEYBOARD_H+MARGIN_H*2
#define HS_W 969
#define MIDIPRESET_W 240
#define HSM_W HS_W + MIDIPRESET_W

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

#define AUV2_ENTRY Minimax_Entry
#define AUV2_ENTRY_STR "Minimax_Entry"
#define AUV2_FACTORY Minimax_Factory
#define AUV2_VIEW_CLASS Minimax_View
#define AUV2_VIEW_CLASS_STR "Minimax_View"

#define AAX_TYPE_IDS 'EFN1', 'EFN2'
#define AAX_PLUG_MFR_STR "Acme"
#define AAX_PLUG_NAME_STR "Minimax\nIPIS"
#define AAX_DOES_AUDIOSUITE 0
#define AAX_PLUG_CATEGORY_STR "Synth"

#define VST3_SUBCATEGORY "Instrument|Synth"

#define APP_NUM_CHANNELS 0
#define APP_N_VECTOR_WAIT 0
#define APP_MULT 1
#define APP_COPY_AUV3 0
#define APP_RESIZABLE 0
#define APP_SIGNAL_VECTOR_SIZE 64

#include "resourceconfig.h"
