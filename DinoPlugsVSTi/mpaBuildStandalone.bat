if exist "%ProgramFiles(x86)%" (goto 64-Bit) else (goto 32-Bit)

:32-Bit
echo 32-Bit O/S detected
call "%ProgramFiles%\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x86_x64 8.1
goto END

:64-Bit
echo 64-Bit Host O/S detected
call "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x86_x64 8.1
goto END
:END

if exist build_errors.log del build_errors.log

msbuild Prodyssey/Prodyssey.sln -target:Prodyssey-app /p:configuration=release /p:platform=x64 /nologo /noconsolelogger /fileLogger /v:quiet /flp:logfile=build_errors.log;errorsonly;append
msbuild Prodyssey/Prodyssey.sln -target:Prodyssey-app /p:configuration=release /p:platform=Win32 /nologo /noconsolelogger /fileLogger /v:quiet /flp:logfile=build_errors.log;errorsonly;append

msbuild Pro12/Pro12.sln -target:Pro12-app /p:configuration=release /p:platform=x64 /nologo /noconsolelogger /fileLogger /v:quiet /flp:logfile=build_errors.log;errorsonly;append
msbuild Pro12/Pro12.sln -target:Pro12-app /p:configuration=release /p:platform=Win32 /nologo /noconsolelogger /fileLogger /v:quiet /flp:logfile=build_errors.log;errorsonly;append

msbuild Minimax/Minimax.sln -target:Minimax-app /p:configuration=release /p:platform=x64 /nologo /noconsolelogger /fileLogger /v:quiet /flp:logfile=build_errors.log;errorsonly;append
msbuild Minimax/Minimax.sln -target:Minimax-app /p:configuration=release /p:platform=Win32 /nologo /noconsolelogger /fileLogger /v:quiet /flp:logfile=build_errors.log;errorsonly;append

msbuild B4000/B4000.sln -target:B4000-app /p:configuration=release /p:platform=x64 /nologo /noconsolelogger /fileLogger /v:quiet /flp:logfile=build_errors.log;errorsonly;append
msbuild B4000/B4000.sln -target:B4000-app /p:configuration=release /p:platform=Win32 /nologo /noconsolelogger /fileLogger /v:quiet /flp:logfile=build_errors.log;errorsonly;append

msbuild Lightwave/Lightwave.sln -target:Lightwave-app /p:configuration=release /p:platform=x64 /nologo /noconsolelogger /fileLogger /v:quiet /flp:logfile=build_errors.log;errorsonly;append
msbuild Lightwave/Lightwave.sln -target:Lightwave-app /p:configuration=release /p:platform=Win32 /nologo /noconsolelogger /fileLogger /v:quiet /flp:logfile=build_errors.log;errorsonly;append


echo ------------------------------------------------------------------
echo Printing log file to console...

type build_errors.log

pause