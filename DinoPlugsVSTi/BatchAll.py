import subprocess
import os
from shutil import copyfile

print("Build VST's")
subprocess.call([r'mpaBuild.bat'])

print("Build Standalones")
subprocess.call([r'mpaBuildStandalone.bat'])

print("Create Installers")
folder = os.getcwd()
os.chdir(folder + '\Installer')
subprocess.call([r'makensis', "configMPA"])

print("Move all To One Folder")
if not os.path.exists("WIN"):
    os.mkdir("WIN")
	
copyfile("Make Pro Audio VSTs Installer 64 Bit.exe", "WIN\Make Pro Audio VSTs Installer 64 Bit.exe")

source = "C:/Program Files (x86)/Steinberg/vstplugins/"
copyfile(source + "Lightwave.dll", "WIN/Lightwave_x86.dll")
copyfile(source + "Minimax.dll", "WIN/Minimax_x86.dll")
copyfile(source + "Pro12.dll", "WIN/Pro12_x86.dll")
copyfile(source + "Prodyssey.dll", "WIN/Prodyssey_x86.dll")
copyfile(source + "B4000.dll", "WIN/B4000_x86.dll")

source = "C:/Program Files/Steinberg/VSTPlugins/"
copyfile(source + "Lightwave.dll", "WIN/Lightwave.dll")
copyfile(source + "Minimax.dll", "WIN/Minimax.dll")
copyfile(source + "Pro12.dll", "WIN/Pro12.dll")
copyfile(source + "Prodyssey.dll", "WIN/Prodyssey.dll")
copyfile(source + "B4000.dll", "WIN/B4000.dll")

source = "C:/Program Files/Steinberg/VSTPlugins/"
copyfile(source + "Lightwave.dll", "WIN/Lightwave.dll")
copyfile(source + "Minimax.dll", "WIN/Minimax.dll")
copyfile(source + "Pro12.dll", "WIN/Pro12.dll")
copyfile(source + "Prodyssey.dll", "WIN/Prodyssey.dll")
copyfile(source + "B4000.dll", "WIN/B4000.dll")

os.chdir(folder)
copyfile("B4000/build-win/app/x64/Release/B4000.exe", "Installer/WIN/B4000.exe")
copyfile("Pro12/build-win/app/x64/Release/Pro12.exe", "Installer/WIN/Pro12.exe")
copyfile("Prodyssey/build-win/app/x64/Release/Prodyssey.exe", "Installer/WIN/Prodyssey.exe")
copyfile("Lightwave/build-win/app/x64/Release/Lightwave.exe", "Installer/WIN/Lightwave.exe")
copyfile("Minimax/build-win/app/x64/Release/Minimax.exe", "Installer/WIN/Minimax.exe")