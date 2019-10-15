@echo OFF 
call "C:\Program Files\Microsoft Visual Studio 10.0\VC\vcvarsall.bat" x86
echo "Starting Build for all Projects with proposed changes"
echo .  
devenv "path\to\solutionFile\projectSolution2.sln" /build Debug 
devenv "another\path\to\solutionFile\projectSolution3.sln" /build Debug 
devenv "yet\another\path\to\solutionFile\projectSolution4.sln" /build Debug 
echo . 
echo "All builds completed." 
pause