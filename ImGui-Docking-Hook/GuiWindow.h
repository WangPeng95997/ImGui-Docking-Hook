#pragma once
#include <Windows.h>
#include <string>
#include "ImGui/imgui.h"
#include "Imgui/imgui_impl_dx11.h"
#include "Imgui/imgui_impl_win32.h"
#include "Imgui/imgui_internal.h"

constexpr const CHAR* AUTHOR_INFO = "Created by l4kkS41 On ";
constexpr const CHAR* WINDOW_NAME = "Dear ImGui";
constexpr float FONT_SIZE = 20.0f;
constexpr float WINDOW_WIDTH = 600.0f;
constexpr float WINDOW_HEIGHT = 400.0f;
constexpr ImGuiID CLOSE_BUTTON_ID = 0x1000;
constexpr ImGuiID CHILD_FRAME_ID = 0x2000;

class GuiWindow
{
public:
    enum GuiState : DWORD
    {
        None = 0,
        Reset = 1,
        Exiting = 2,
        Detach = 4
    };

    HWND hWnd;
    HMODULE hModule;
    HANDLE hProcess;
    std::string FontPath;
    std::string WindowTitle;
    LPBYTE lpBuffer;
    ImVec2 StartPos;
    DWORD State;
    bool IsShowMenu;

    GuiWindow();
    ~GuiWindow();

    void ExitButton();
    void Initialize();
    void Update();
};