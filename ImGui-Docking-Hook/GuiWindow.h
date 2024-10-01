#pragma once
#include "ImGui/imgui.h"
#include "Imgui/imgui_impl_dx9.h"
#include "Imgui/imgui_impl_win32.h"
#include "Imgui/imgui_internal.h"
#include <Windows.h>
#include <string>

#define AUTHOR              "by l4kkS41"
#define WINDOWNAME          "Dear ImGui"
#define MAJORVERSION        1
#define MINORVERSION        0
#define REVISIONVERSION     0

#define WIDTH               600
#define HEIGHT              400

#define MODULENAME          NULL

class GuiWindow
{
public:
    enum GuiState : DWORD
    {
        None = 0,
        Reset = 1,
        Exiting = 2
    };

    HWND        hWnd;
    HMODULE     hModule;
    HANDLE      hProcess;
    PCHAR       fontPath;
    PCHAR       windowTitle;
    LPBYTE      lpBuffer;
    LPBYTE      lpModuleAddress;
    ImVec2      initialPostion;
    DWORD       uiStatus;
    bool        showMenu;

    GuiWindow();
    ~GuiWindow();

    void Init();
    void Update();
    
    void ButtonExit();
};