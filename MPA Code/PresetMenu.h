#pragma once

#include "ParamEnum.h"

#if defined OS_WIN
#include <shlobj.h>
#include <windows.h>
#include <iostream>
#endif

#include "json.hpp"

// avoid some UNICODE issues with VST3 SDK and WDL dirscan
#if defined VST3_API && defined OS_WIN
#ifdef FindFirstFile
#undef FindFirstFile
#undef FindNextFile
#undef WIN32_FIND_DATA
#undef PWIN32_FIND_DATA
#define FindFirstFile FindFirstFileA
#define FindNextFile FindNextFileA
#define WIN32_FIND_DATA WIN32_FIND_DATAA
#define LPWIN32_FIND_DATA LPWIN32_FIND_DATAA
#endif
#endif

/*
Ordner:
Preset:
Windows: VST3: C>users>user name>documents>vst3 presets>steinberg media technologies>(name of effect such as mono delay)>preset.
C>users>user name>documents>vst3 presets>Synsonic Instruments>(name of effect such as mono delay)>preset.
MAC: VST3: /Benutzer/Ihr_Benutzername/Library / Audio / Presets
MAC: AU: [Home]/Library/Audio/Presets/[manufacturer]/[plug-in]/
 (~/)Library/Audio/Presets/VendorName/

Plugin:
MAC: AU: Macintosh HD : / Library / Audio / Plug - Ins / Komponenten / (AU, Dateiendung.component)
Macintosh HD:/Library/Audio/Plug-Ins/VST/ (VST 2, Dateiendung .vst)
Macintosh HD:/Library/Audio/Plug-Ins/VST3/ (VST 3, Dateiendung .vst3)


    C:\Program Files\VSTPlugins - 64-bit VST2 plug-ins.
    C:\Program Files\Common Files\VST3 - 64-bit VST3 plug-ins. (Live 10.1 and later).
    C:\Program Files (x86)\VSTPlugins - 32-bit plug-ins.


*/

#if defined OS_WIN // VST3 & APP
  //TCHAR my_documents[MAX_PATH];

  CHAR my_documents[MAX_PATH];
  HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);

  #ifdef VST3_API
    char str[MAX_PATH];
    int ret = wcstombs(str, my_documents, MAX_PATH);
    const std::string Path(str);
  #else
    const std::string Path(my_documents);
  #endif
    const std::string basePath = Path + "\\Synsonic Instruments\\Apollon\\Presets\\";

#elif defined OS_MAC // AU & VST3
  const std::string basePath = "/Library/Audio/Presets/Synsonic Instruments/Apollon/Presets/";
#endif

#include "dirscan.h"
#include <fstream>  
  static constexpr int kPresetMessage = 5;

class FileBrowser : public IDirBrowseControlBase
{
private:
  WDL_String mLabel;
  IBitmap mBitmap;
  WDL_String mDefaultPreset;
  WDL_String mCurrentPresetName;

public:
  FileBrowser(IRECT bounds)
    : IDirBrowseControlBase(bounds, ".siapreset")
  {
    path.Append(basePath.c_str());
    AddPath(path.Get(), "");

    mShowFileExtensions = false;
 
  }
  bool dEFnOTlOADED = true;

  void loadDefault(const char* defaultPreset) {
    std::string presetName(defaultPreset);
    std::string extension(mExtension.Get());
    std::string defaultP = basePath + presetName + extension;
    mDefaultPreset.Set(defaultP.c_str());
    //loadPreset(mDefaultPreset); // geht nicht da Drumcomputer noch nicht Instanziiert !?
    loadPresetJSON(mDefaultPreset.Get());
  }

  static constexpr int kStepMessage = 3;

  WDL_String path;

  void restorePresetPath(const char* filename) {
    std::string s = SplitFilename(filename, false);
    const char * ss = s.c_str();
    if (this) {
    mLabel.Set(ss);
  }
    SetDirty();
  }

  static constexpr int kUpdateMessage = 0;

 

  const char* getLabel() {
    return mLabel.Get();
  }

  

  void loadPresetJSON(const char * filename) {

    int tag = this->GetTag();
    WDL_String d(filename);
    int dataSize = sizeof(d);
    GetDelegate()->SendArbitraryMsgFromUI(kPresetMessage, tag, dataSize, &d);

    try {

      std::ifstream infile;
      infile.open(filename);
      nlohmann::json j;
      infile >> j;
      infile.close();

      for (int i = 0; i < kNumParams; i++) {
        double val = j.at("parameters").at(GetDelegate()->GetParam(i)->GetNameForHost());
        GetUI()->ForControlWithParam(i, [&](IControl& control) {control.SetValueFromUserInput(val); });
      }

      
      mLabel.Set(SplitFilename(filename, false).c_str());
      SetDirty();
    }
    catch (...) { return; }
  }

  void savePresetJSON(const char * filename) {
    nlohmann::json j;

    j["presetname"] = filename;

    nlohmann::json parameters;
    nlohmann::json parameter;

    for (int i = 0; i < kNumParams; i++)
    { // Params
      parameter[GetDelegate()->GetParam(i)->GetNameForHost()] = GetDelegate()->GetParam(i)->GetNormalized();
    }
    j["parameters"] = parameter;

    

    std::ofstream ofs(filename, std::ofstream::out);
    ofs << j;
    ofs.close();

    mLabel.Set(SplitFilename(filename, false).c_str());
    int tag = this->GetTag();
    WDL_String d(filename);
    int dataSize = sizeof(d);
    GetDelegate()->SendArbitraryMsgFromUI(kPresetMessage, tag, dataSize, &d);
    SetDirty();
    GetDelegate()->DirtyParametersFromUI(); // soll gespeichert werden
  }

  void Draw(IGraphics& g) override
  {
    g.FillRect(COLOR_LIGHT_GRAY, mRECT);
    g.DrawText(IText(16, IColor(255, 255, 255, 255), nullptr, EAlign::Center, EVAlign::Middle), mLabel.Get(), mRECT);
  }

  void saveDialog() {
    WDL_String fileName;
    if(GetUI())
    GetUI()->PromptForFile(fileName, path, EFileAction::Save, "siapreset");
    if (fileName.GetLength()) {
      savePresetJSON(fileName.Get());
    }
  }

  void loadDialog() {
    WDL_String fileName;
    GetUI()->PromptForFile(fileName, path, EFileAction::Open, "siapreset");
    loadPresetJSON(fileName.Get());
  }

  void OnMouseDown(float x, float y, const IMouseMod& mod) override
  {
    mFiles.Empty(true);
    mItems.Empty(false);

    mMainMenu.Clear();
    mSelectedIndex = -1;

    mMainMenu.AddItem("Save Preset..."); 
    mMainMenu.AddItem("Load Preset...");
    mMainMenu.AddSeparator();

    int idx = 0;

    if (mPaths.GetSize() == 1)
    {
      ScanDirectory(mPaths.Get(0)->Get(), mMainMenu);
    }
    else
    {
      for (int p = 0; p < mPaths.GetSize(); p++)
      {
        IPopupMenu* pNewMenu = new IPopupMenu();
        mMainMenu.AddItem(mPathLabels.Get(p)->Get(), idx++, pNewMenu);
        ScanDirectory(mPaths.Get(p)->Get(), *pNewMenu);
      }
    }

    CollectSortedItems(&mMainMenu);

    GetUI()->CreatePopupMenu(*this, mMainMenu, x, y);
  }

  std::string SplitFilename(const char* filename, bool withExtension)
  {
    std::string str = filename;
    std::size_t found = str.find_last_of("/\\");
    str = str.substr(found + 1);
    if (!withExtension) {
      size_t lastindex = str.find_last_of(".");
      str = str.substr(0, lastindex);
    }
    return str;
  }


  std::string removeExtension(WDL_String filename) {
    std::string str = filename.Get();
    size_t lastindex = str.find_last_of(".");
    str = str.substr(0, lastindex);
    return str;
  }

  void loadPreset(WDL_String fileName) {
    FILE* fp = fopen(fileName.Get(), "r");
    if (fp) {
      for (int i = 0; i < kNumParams; i++) {
        char keyname[32];
        char line[256];
        double val;
        fgets(line, sizeof(line), fp);
        sscanf(line, "%32[^=]=%lf", keyname, &val);

        GetUI()->ForControlWithParam(i, [&](IControl& control) { GetDelegate()->GetParam(i)->SetNormalized(val);  control.SetValueFromUserInput(val); });
      }
     
      fclose(fp);
      mLabel.Set(SplitFilename(fileName.Get(), false).c_str());
    }
  }

  void OnPopupMenuSelection(IPopupMenu* pSelectedMenu, int valIdx) override
  {
    if (pSelectedMenu)
    {
      IPopupMenu::Item* pItem = pSelectedMenu->GetChosenItem();

      if (pSelectedMenu->GetChosenItemIdx() == 0) { // Save
        
        saveDialog();
        
      }
      else if (pSelectedMenu->GetChosenItemIdx() == 1) { // Load
        loadDialog();
      }
      else {
        WDL_String fileName = mFiles.Get(pItem->GetTag());
        loadPresetJSON(fileName.Get());
      }
    }
  }

  void ScanDirectory(const char* path, IPopupMenu& menuToAddTo)
     {
   #if !defined OS_IOS
       WDL_DirScan d;
       IPopupMenu& parentDirMenu = menuToAddTo;

       if (!d.First(path))
       {
         do
         {
           const char* f = d.GetCurrentFN();
           if (f && f[0] != '.')
           {
             if (d.GetCurrentIsDirectory())
             {
               WDL_String subdir;
               d.GetCurrentFullFN(&subdir);
               IPopupMenu* pNewMenu = new IPopupMenu();
               parentDirMenu.AddItem(d.GetCurrentFN(), pNewMenu, -1);
               ScanDirectory(subdir.Get(), *pNewMenu);
             }
             else
             {
               const char* a = strstr(f, mExtension.Get());
               if (a && a > f && strlen(a) == strlen(mExtension.Get()))
               {
                 WDL_String menuEntry{ f };

                 if (!mShowFileExtensions)
                   menuEntry.Set(f, (int)(a - f));

                 IPopupMenu::Item* pItem = new IPopupMenu::Item(menuEntry.Get(), IPopupMenu::Item::kNoFlags, mFiles.GetSize());
                 parentDirMenu.AddItem(pItem, -1 /* sort alphabetically */);
                   WDL_String* pFullPath = new WDL_String("");
                   d.GetCurrentFullFN(pFullPath);
                   mFiles.Add(pFullPath);
                 }
               }
             }
           } while (!d.Next());

           menuToAddTo = parentDirMenu;
         }

         if (!mShowEmptySubmenus)
           parentDirMenu.RemoveEmptySubmenus();

     #endif
       }

  void CollectSortedItems(IPopupMenu* pMenu)
  {
    int nItems = pMenu->NItems();

    for (int i = 0; i < nItems; i++)
    {
      IPopupMenu::Item* pItem = pMenu->GetItem(i);
      if (pItem->GetSubmenu())
         CollectSortedItems(pItem->GetSubmenu());
       else
         mItems.Add(pItem);
    }
  }
};


