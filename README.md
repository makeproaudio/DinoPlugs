IPlug-MPA

This is IPlug2 with Projects of MPA Synth Controller VST's 

====================================================================================================================

iPlug 2
C++ audio plug-in framework for desktop, mobile (soon) and web

Build Status

iPlug 2 is a simple-to-use C++ framework for developing cross platform audio plug-ins/apps and targeting multiple plug-in APIs with the same minimalistic code. It abstracts an audio plug-in (IPlug) and it's drawing engine/GUI toolkit (IGraphics), although IPlug can be used in bring-your-own GUI library mode without IGraphics. IGraphics uses a retained mode paradigm and contains a collection of common controls well suited for audio plug-in GUIs, either using bitmap or vector graphics.

The original version of iPlug was developed by John Schwartz aka schwa and released in 2008 as part of Cockos' WDL library. iPlug 2 (2018) is a substantial reworking that brings multiple vector graphics backends to IGraphics (including GPU accelerated options and HiDPI/scaling), a better approach to concurrency, support for distributed plug-in formats and compiling to WebAssembly via emscripten, amongst many other things.

iPlug 2 targets the VST2, VST3, AudioUnit, AAX (Native) and the Web Audio Module (WAM) plug-in APIs. It can also produce standalone win32/macOS apps with audio and MIDI I/O, as well as Reaper extensions.

iPlug 2 includes support for the FAUST programming language, and the libfaust JIT compiler. It was the winner of the 2018 FAUST award.

You can discuss iPlug 2 on the WDL forum or on the iPlug user's slack channel.

Please consider supporting the project by helping out with bug fixes, features or documentation. You can support the project financially via patreon.

NOTE: THIS IS NOT YET PRODUCTION READY - zero commercial/free plug-ins are shipping with iPlug 2 - there are many bugs still to fix and a few features to add!

You may like to check out the Web Audio Module version of VirtualCZ which has been made using iPlug 2.

patreon paypalslack

--------------------------------------------

Cockos WDL License

Copyright (C) 2005 and later Cockos Incorporated

Portions copyright other contributors, see each source file for more information

This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
1. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
1. This notice may not be removed or altered from any source distribution.

WDL includes the following 3rd party libraries (which are all similarly licensed):

* JNetLib http://www.nullsoft.com/free/jnetlib
* LibPNG http://www.libpng.org/pub/png
* GifLib http://sourceforge.net/projects/libungif
* JPEGLib http://www.ijg.org
* zlib http://www.zlib.net