#include "GuiWindow.h"

GuiWindow::GuiWindow()
{
    // Initialize settings
    this->hWnd = nullptr;
    this->hModule = nullptr;
    this->hProcess = nullptr;
    this->lpModuleAddress = nullptr;
    this->initialPostion = ImVec2(0.0f, 0.0f);
    this->uiStatus = GuiState::Reset;
    this->showMenu = true;

    // Set font path
    this->fontPath = new char[MAX_PATH] {};
    ::GetEnvironmentVariable("WINDIR", this->fontPath, MAX_PATH);
    ::strcat_s(this->fontPath, MAX_PATH, "\\Fonts\\segoeui.ttf");

    // Set window title
    std::string strText{};
    strText = strText.append(WINDOWNAME).append(" v") +
        std::to_string(MAJORVERSION) +
        std::string().append(".") +
        std::to_string(MINORVERSION) +
        std::string().append(".") +
        std::to_string(REVISIONVERSION);
    size_t nLength = strText.length() + 1;
    this->windowTitle = new char[nLength] {};
    ::memcpy(this->windowTitle, strText.c_str(), strText.length());

    // Allocate memory
    this->lpBuffer = (LPBYTE)::VirtualAlloc(NULL, 0x1000, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    ::memset(this->lpBuffer, 0xCC, 0x1000);
}

GuiWindow::~GuiWindow()
{
    if (this->lpBuffer)
        ::VirtualFree(this->lpBuffer, 0, MEM_RELEASE);

    delete[] this->fontPath;
    delete[] this->windowTitle;
}

void GuiWindow::Init()
{
    this->hProcess = ::GetCurrentProcess();
    this->hModule = ::GetModuleHandle(MODULENAME);
    this->lpModuleAddress = (LPBYTE)this->hModule;
}

void GuiWindow::Update()
{
    const ImGuiWindowFlags windowflags =
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoScrollWithMouse |
        ImGuiWindowFlags_NoSavedSettings;
    ImGui::Begin(WINDOWNAME, nullptr, windowflags);
    if (this->uiStatus & GuiState::Reset)
    {
        ImGui::SetWindowPos(this->initialPostion);
        ImGui::SetWindowSize(ImVec2(WIDTH, HEIGHT));
        this->uiStatus &= ~GuiState::Reset;
    }

    ImVec2 windowPostion = ImGui::GetWindowPos();
    ImGui::Text(this->windowTitle);
    if (ImGui::CloseButton(0x1000, ImVec2(windowPostion.x + WIDTH - 20.0f, windowPostion.y)))
        this->uiStatus |= GuiState::Exiting;

    const std::string authorInfo(AUTHOR);
    ImVec2 textSize = ImGui::CalcTextSize(authorInfo.c_str());
    ImVec2 windowPadding = ImGui::GetStyle().WindowPadding;
    ImGui::SetCursorPosY(HEIGHT - windowPadding.y - textSize.y);
    ImGui::Text(authorInfo.c_str());

    const std::string hotKey = std::string("INSERT to Show/Hide UI");
    textSize = ImGui::CalcTextSize(hotKey.c_str());
    ImGui::SetCursorPos(ImVec2(WIDTH - windowPadding.x - textSize.x, HEIGHT - windowPadding.y - textSize.y));
    ImGui::Text(hotKey.c_str());

    if (this->uiStatus & GuiState::Exiting)
        this->ButtonExit();

    ImGui::End();
}

void GuiWindow::ButtonExit()
{
    ImGui::SetCursorPos(ImVec2(0, 0));
    ImGui::BeginChildFrame(0x2000, ImVec2(WIDTH, HEIGHT), ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    ImGui::SetCursorPos(ImVec2(0, 0));
    ImGui::BeginChild("Exiting", ImVec2(WIDTH, HEIGHT));

    std::string strText = std::string("Do you want to exit this program?");
    ImVec2 textSize = ImGui::CalcTextSize(strText.c_str());
    ImGui::SetCursorPos(ImVec2((WIDTH - textSize.x) * 0.5f, HEIGHT * 0.382f - textSize.y * 0.5f));
    ImGui::Text(strText.c_str());

    ImGui::SetCursorPos(ImVec2(WIDTH * 0.5f - 120, HEIGHT * 0.618f));
    if (ImGui::Button("Confirm", ImVec2(100.0f, 50.0f)))
        ::PostMessage(this->hWnd, WM_QUIT, 0, 0);

    ImGui::SetCursorPos(ImVec2(WIDTH * 0.5f + 20, HEIGHT * 0.618f));
    if (ImGui::Button("Cancel", ImVec2(100.0f, 50.0f)))
        this->uiStatus &= ~GuiState::Exiting;

    ImGui::EndChild();
    ImGui::EndChildFrame();
}