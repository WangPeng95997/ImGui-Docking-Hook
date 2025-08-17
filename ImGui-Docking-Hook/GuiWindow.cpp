#include "GuiWindow.h"

GuiWindow::GuiWindow()
{
    // Initialize settings
    this->hWnd = nullptr;
    this->hModule = nullptr;
    this->hProcess = nullptr;
    this->initialPos = ImVec2(0.0f, 0.0f);
    this->uiState = static_cast<DWORD>(GuiState::GuiState_Reset);
    this->showMenu = true;

    // Set font path
    char szBuffer[MAX_PATH]{};
    ::GetEnvironmentVariable("WINDIR", szBuffer, MAX_PATH);
    this->strFontPath = std::string(szBuffer) + "\\Fonts\\segoeui.ttf";

    // Set window title
    this->strWindowTitle = WINDOW_NAME;

    // Allocate memory
    this->lpBuffer = (LPBYTE)::VirtualAlloc(NULL, 0x1000, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
}

GuiWindow::~GuiWindow()
{
    if (this->lpBuffer) {
        ::VirtualFree(this->lpBuffer, 0, MEM_RELEASE);
        this->lpBuffer = nullptr;
    }
}

void GuiWindow::Initialize()
{
    this->hProcess = ::GetCurrentProcess();
    this->hModule = ::GetModuleHandle(nullptr);
}

void GuiWindow::Update()
{
    // Set window flags to disable title bar, resizing, scrollbars, mouse wheel scrolling, and saved settings
    const ImGuiWindowFlags windowflags =
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoScrollWithMouse |
        ImGuiWindowFlags_NoSavedSettings;
    ImGui::Begin(WINDOW_NAME, nullptr, windowflags);

    // Check if the window state needs to be reset
    if (this->uiState & static_cast<DWORD>(GuiState::GuiState_Reset))
    {
        ImGui::SetWindowPos(this->initialPos);
        ImGui::SetWindowSize(ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT));
        this->uiState &= ~static_cast<DWORD>(GuiState::GuiState_Reset);
    }

    // Get window padding and position
    ImVec2& windowPadding = ImGui::GetStyle().WindowPadding;
    ImVec2 windowPosition = ImGui::GetWindowPos();

    // Display CloseButton in the top-right corner
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    if (ImGui::CloseButton(CLOSE_BUTTON_ID, ImVec2(windowPosition.x + WINDOW_WIDTH - FONT_SIZE, windowPosition.y)))
        this->uiState |= static_cast<DWORD>(GuiState::GuiState_Exiting);
    ImGui::PopStyleVar();

    // Display shortcut hint in the bottom-right corner
    const std::string hotKey = std::string("Press INSERT to Toggle Menu");
    ImVec2 textSize = ImGui::CalcTextSize(hotKey.c_str());
    ImGui::SetCursorPos(ImVec2(WINDOW_WIDTH - windowPadding.x - textSize.x, WINDOW_HEIGHT - windowPadding.y - textSize.y));
    ImGui::Text(hotKey.c_str());

    // Display author information and build date in the bottom-left corner
    const std::string authorInfo = std::string(AUTHOR_INFO) + __DATE__;
    ImGui::SetCursorPosY(WINDOW_HEIGHT - windowPadding.y - textSize.y);
    ImGui::Text(authorInfo.c_str());

    // Check if an exit operation is required
    if (this->uiState & static_cast<DWORD>(GuiState::GuiState_Exiting))
        this->ExitButton();

    // Display the window title at the top of the ImGui window
    ImGui::SetCursorPos(ImVec2(windowPadding.x, windowPadding.y));
    ImGui::Text(strWindowTitle.c_str());

    // Insert your code here
    ImGui::Text("Hello World");
    ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "TextColored");
    ImGui::TextDisabled("TextDisabled");
    ImGui::TextLinkOpenURL("Hyperlink", "https://github.com/ocornut/imgui");
    ImGui::Button("Button", ImVec2(100.0f, 20.0f));
    ImGui::Checkbox("Checkbox", (bool*)this->lpBuffer);
    
    ImGui::End();
}

void GuiWindow::ExitButton()
{
    ImGui::SetCursorPos(ImVec2(0, 0));
    ImGui::BeginChildFrame(CHILD_FRAME_ID, ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT), ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    ImGui::SetCursorPos(ImVec2(0, 0));
    ImGui::BeginChild("Exiting", ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT));
    
    std::string strText = std::string("Do you want to unload this DLL?");
    ImVec2 textSize = ImGui::CalcTextSize(strText.c_str());
    ImGui::SetCursorPos(ImVec2((WINDOW_WIDTH - textSize.x) * 0.5f, WINDOW_HEIGHT * 0.382f - textSize.y * 0.5f));
    ImGui::Text(strText.c_str());
    
    ImGui::SetCursorPos(ImVec2(WINDOW_WIDTH * 0.5f - 100, WINDOW_HEIGHT * 0.618f));
    if (ImGui::Button("Confirm", ImVec2(80.0f, 40.0f)))
        ::PostMessage(this->hWnd, WM_QUIT, 0, 0);

    ImGui::SetCursorPos(ImVec2(WINDOW_WIDTH * 0.5f + 20, WINDOW_HEIGHT * 0.618f));
    if (ImGui::Button("Cancel", ImVec2(80.0f, 40.0f)))
        this->uiState &= ~static_cast<DWORD>(GuiState::GuiState_Exiting);

    ImGui::EndChild();
    ImGui::EndChildFrame();
}