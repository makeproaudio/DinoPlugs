import subprocess
import os
from shutil import copyfile

print("Build VST's")
subprocess.call([r'mpaBuild.bat'])

print("Build Standalones")
subprocess.call([r'mpaBuildStandalone.bat'])

print("Copy Files to WIN folder")
folder = os.getcwd()
os.chdir(folder + '\Installer')

source = "C:/Program Files (x86)/Steinberg/vstplugins/"
copyfile(source + "FMagia.dll", "WIN/FMagia_x86.dll")
copyfile(source + "DrumsNBass.dll", "WIN/DrumsNBass_x86.dll")
copyfile(source + "Lightwave.dll", "WIN/Lightwave_x86.dll")
copyfile(source + "Minimax.dll", "WIN/Minimax_x86.dll")
copyfile(source + "Pro12.dll", "WIN/Pro12_x86.dll")
copyfile(source + "Prodyssey.dll", "WIN/Prodyssey_x86.dll")
copyfile(source + "B4000.dll", "WIN/B4000_x86.dll")

source = "C:/Program Files/Steinberg/VSTPlugins/"
copyfile(source + "FMagia.dll", "WIN/FMagia.dll")
copyfile(source + "DrumsNBass.dll", "WIN/DrumsNBass.dll")
copyfile(source + "Lightwave.dll", "WIN/Lightwave.dll")
copyfile(source + "Minimax.dll", "WIN/Minimax.dll")
copyfile(source + "Pro12.dll", "WIN/Pro12.dll")
copyfile(source + "Prodyssey.dll", "WIN/Prodyssey.dll")
copyfile(source + "B4000.dll", "WIN/B4000.dll")

os.chdir(folder)
copyfile("FMagia/build-win/app/x64/Release/FMagia.exe", "Installer/WIN/FMagia.exe")
copyfile("DrumsNBass/build-win/app/x64/Release/DrumsNBass.exe", "Installer/WIN/DrumsNBass.exe")
copyfile("B4000/build-win/app/x64/Release/B4000.exe", "Installer/WIN/B4000.exe")
copyfile("Pro12/build-win/app/x64/Release/Pro12.exe", "Installer/WIN/Pro12.exe")
copyfile("Prodyssey/build-win/app/x64/Release/Prodyssey.exe", "Installer/WIN/Prodyssey.exe")
copyfile("Lightwave/build-win/app/x64/Release/Lightwave.exe", "Installer/WIN/Lightwave.exe")
copyfile("Minimax/build-win/app/x64/Release/Minimax.exe", "Installer/WIN/Minimax.exe")

copyfile("FMagia/build-win/app/Win32/Release/FMagia.exe", "Installer/WIN/FMagia_x86.exe")
copyfile("DrumsNBass/build-win/app/Win32/Release/DrumsNBass.exe", "Installer/WIN/DrumsNBass_x86.exe")
copyfile("B4000/build-win/app/Win32/Release/B4000.exe", "Installer/WIN/B4000_x86.exe")
copyfile("Pro12/build-win/app/Win32/Release/Pro12.exe", "Installer/WIN/Pro12_x86.exe")
copyfile("Prodyssey/build-win/app/Win32/Release/Prodyssey.exe", "Installer/WIN/Prodyssey_x86.exe")
copyfile("Lightwave/build-win/app/Win32/Release/Lightwave.exe", "Installer/WIN/Lightwave_x86.exe")
copyfile("Minimax/build-win/app/Win32/Release/Minimax.exe", "Installer/WIN/Minimax_x86.exe")

print("Create 32 Bit Installers")
os.chdir(folder + '\Installer')
subprocess.call([r'makensis', "DinoParkPluginsInstaller32Bit"])

print("Create 64 Bit Installers")
subprocess.call([r'makensis', "DinoParkPluginsInstaller64Bit"])

print("Move all To One Folder")
if not os.path.exists("WIN"):
    os.mkdir("WIN")
	
copyfile("DinoParkPlugins32Bit.exe", "WIN\DinoParkPlugins32Bit.exe")
copyfile("DinoParkPlugins64Bit.exe", "WIN\DinoParkPlugins64Bit.exe")

