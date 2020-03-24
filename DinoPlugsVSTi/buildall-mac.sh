#! /bin/sh

#bash shell script to build all the plugin projects in this directory for OSX. 
#you may need to modify this if you don't have the AAX SDK, or only want to build vst2 etc
#since the build will cancel if there are any errors

BASEDIR=$(dirname $0)

#here you can choose a target to build
#TARGET="All"
TARGET="APP"
#TARGET="VST2"
#TARGET="VST3"
#TARGET="AU"
#TARGET="AAX"

cd $BASEDIR

echo "building all example plugins..."

if [ -f build_errors.log ]
then
  rm build_errors.log
fi

echo "building B4000"
xcodebuild -project "B4000/projects/B4000-macOS.xcodeproj" -target "APP" -configuration Release 2> ./build_errors.log
xcodebuild -project "B4000/projects/B4000-macOS.xcodeproj" -target "VST2" -configuration Release 2> ./build_errors.log

echo "building Prodyssey"
xcodebuild -project "Prodyssey/projects/Prodyssey-macOS.xcodeproj" -target "APP" -configuration Release 2> ./build_errors.log
xcodebuild -project "Prodyssey/projects/Prodyssey-macOS.xcodeproj" -target "VST2" -configuration Release 2> ./build_errors.log

echo "building Pro12"
xcodebuild -project "Pro12/projects/Pro12-macOS.xcodeproj" -target "APP" -configuration Release 2> ./build_errors.log
xcodebuild -project "Pro12/projects/Pro12-macOS.xcodeproj" -target "VST2" -configuration Release 2> ./build_errors.log

echo "building Minimax"
xcodebuild -project "Minimax/projects/Minimax-macOS.xcodeproj" -target "APP" -configuration Release 2> ./build_errors.log
xcodebuild -project "Minimax/projects/Minimax-macOS.xcodeproj" -target "VST2" -configuration Release 2> ./build_errors.log

echo "building Lightwave"
xcodebuild -project "Lightwave/projects/Lightwave-macOS.xcodeproj" -target "APP" -configuration Release 2> ./build_errors.log
xcodebuild -project "Lightwave/projects/Lightwave-macOS.xcodeproj" -target "VST2" -configuration Release 2> ./build_errors.log

echo "building DrumsNBass"
xcodebuild -project "DrumsNBass/projects/DrumsNBass-macOS.xcodeproj" -target "APP" -configuration Release 2> ./build_errors.log
xcodebuild -project "DrumsNBass/projects/DrumsNBass-macOS.xcodeproj" -target "VST2" -configuration Release 2> ./build_errors.log

echo "building FMagia"
xcodebuild -project "FMagia/projects/FMagia-macOS.xcodeproj" -target "APP" -configuration Release 2> ./build_errors.log
xcodebuild -project "FMagia/projects/FMagia-macOS.xcodeproj" -target "VST2" -configuration Release 2> ./build_errors.log



echo "done"
