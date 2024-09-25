#pragma once
#include "ImGui/imgui.h"
#include "Imgui/imgui_impl_dx9.h"
#include "Imgui/imgui_impl_win32.h"
#include "Imgui/imgui_internal.h"
#include <Windows.h>
#include <string>

#define AUTHOR              "by l4kkS41"
#define WINDOWNAME          "ImGui Window"
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
        Reset = 1 << 0,
        Exiting = 1 << 1
    };

    HWND        hWnd;
    HMODULE     hModule;
    HANDLE      hProcess;
    PCHAR       fontPath;
    PCHAR       windowTitle;
    LPBYTE      lpModuleAddress;
    LPBYTE      lpBuffer;
    ImVec2      initialPostion;
    DWORD       uiStatus;

    GuiWindow();
    ~GuiWindow();

    void Init(HWND hWnd);
    void Update();
    
    void ButtonExit();
};