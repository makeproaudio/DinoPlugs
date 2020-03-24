import subprocess
import os
from distutils.dir_util import copy_tree
import shutil

print("Build ALL")
#subprocess.Popen(["bash", "buildall-mac.sh"])

print("Copy Files to MAC folder")

# remove all files before manually!
shutil.rmtree("Installer/MAC/FMagia.vst")
shutil.rmtree("Installer/MAC/DrumsNBass.vst")
shutil.rmtree("Installer/MAC/B4000.vst")
shutil.rmtree("Installer/MAC/Pro12.vst")
shutil.rmtree("Installer/MAC/Prodyssey.vst")
shutil.rmtree("Installer/MAC/Lightwave.vst")
shutil.rmtree("Installer/MAC/Minimax.vst")

shutil.rmtree("Installer/MAC/FMagia.app")
shutil.rmtree("Installer/MAC/DrumsNBass.app")
shutil.rmtree("Installer/MAC/B4000.app")
shutil.rmtree("Installer/MAC/Pro12.app")
shutil.rmtree("Installer/MAC/Prodyssey.app")
shutil.rmtree("Installer/MAC/Lightwave.app")
shutil.rmtree("Installer/MAC/Minimax.app")

source = "/Users/Ane/Library/Audio/Plug-Ins/VST/"
copy_tree(source + "FMagia.vst", "Installer/MAC/FMagia.vst")
copy_tree(source + "DrumsNBass.vst", "Installer/MAC/DrumsNBass.vst")
copy_tree(source + "B4000.vst", "Installer/MAC/B4000.vst")
copy_tree(source + "Pro12.vst", "Installer/MAC/Pro12.vst")
copy_tree(source + "Prodyssey.vst", "Installer/MAC/Prodyssey.vst")
copy_tree(source + "Lightwave.vst", "Installer/MAC/Lightwave.vst")
copy_tree(source + "Minimax.vst", "Installer/MAC/Minimax.vst")

source = "/Users/Ane/Applications/"
copy_tree(source + "FMagia.app", "Installer/MAC/FMagia.app")
copy_tree(source + "DrumsNBass.app", "Installer/MAC/DrumsNBass.app")
copy_tree(source + "B4000.app", "Installer/MAC/B4000.app")
copy_tree(source + "Pro12.app", "Installer/MAC/Pro12.app")
copy_tree(source + "Prodyssey.app", "Installer/MAC/Prodyssey.app")
copy_tree(source + "Lightwave.app", "Installer/MAC/Lightwave.app")
copy_tree(source + "Minimax.app", "Installer/MAC/Minimax.app")

# ab hier manuelle machen, da Befehl CreateInstaller nicht funzt.

print("Create Installer")
subprocess.Popen(["bash", "/Applications/PackageMaker.app/Contents/MacOs/PackageMaker --doc \"Installer/MAC/configDinoParkInstaller.pmdoc\" --title \"DinoPark Plugin Installer\" --out \"Installer/MAC/DinoParkPluginInstaller.pkg\""])

print("Sign Installer")
subprocess.Popen(["bash", "productsign --sign \"Developer ID Installer: MakeProAudio GmbH (2KPF2E33GE)\" Installer/MAC/DinoParkPluginInstaller.pkg Installer/MAC/DinoParkPluginInstaller.pkg"])



