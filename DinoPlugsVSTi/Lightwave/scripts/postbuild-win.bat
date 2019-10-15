@echo off

REM - CALL "$(SolutionDir)scripts\postbuild-win.bat" "$(TargetExt)" "$(BINARY_NAME)" "$(Platform)" "$(COPY_VST2)" "$(TargetPath)" "$(VST2_32_PATH)" "$(VST2_64_PATH)" "$(VST3_32_PATH)" "$(VST3_64_PATH)" "$(AAX_32_PATH)" "$(AAX_64_PATH)" "$(BUILD_DIR)" "$(VST_ICON)" "$(AAX_ICON)" "
REM $(CREATE_BUNDLE_SCRIPT)"

set FORMAT=%1
set NAME=%2
set PLATFORM=%3
set COPY_VST2=%4
set BUILT_BINARY=%5
set VST2_32_PATH=%6
set VST2_64_PATH=%7 
set VST3_32_PATH=%8
set VST3_64_PATH=%9
shift
shift 
shift
shift
shift 
shift
set AAX_32_PATH=%4
set AAX_64_PATH=%5
set BUILD_DIR=%6
set VST_ICON=%7
set AAX_ICON=%8
set CREATE_BUNDLE_SCRIPT=%9

echo POSTBUILD SCRIPT VARIABLES -----------------------------------------------------
echo FORMAT %FORMAT% 
echo NAME %NAME% 
echo PLATFORM %PLATFORM% 
echo COPY_VST2 %COPY_VST2% 
echo BUILT_BINARY %BUILT_BINARY% 
echo VST2_32_PATH %VST2_32_PATH% 
echo VST2_64_PATH %VST2_64_PATH% 
echo VST3_32_PATH %VST3_32_PATH% 
echo VST3_64_PATH %VST3_64_PATH% 
echo BUILD_DIR %BUILD_DIR%
echo VST_ICON %VST_ICON% 
echo AAX_ICON %AAX_ICON% 
echo CREATE_BUNDLE_SCRIPT %CREATE_BUNDLE_SCRIPT%
echo END POSTBUILD SCRIPT VARIABLES -----------------------------------------------------

