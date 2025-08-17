# ImGui-Docking-Hook

## Getting Started
[Dllmain.cpp](https://github.com/WangPeng95997/ImGui-Docking-Hook/blob/master/ImGui-Docking-Hook/Dllmain.cpp#L278-L279)
```C++
ImGui::ShowDemoWindow();
//g_GuiWindow->Update();
```
[GuiWindow.cpp](https://github.com/WangPeng95997/ImGui-Docking-Hook/blob/master/ImGui-Docking-Hook/GuiWindow.cpp#L87-L93)
```C++
// Insert your code here
ImGui::Text("Hello World");
ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "TextColored");
ImGui::TextDisabled("TextDisabled");
ImGui::TextLinkOpenURL("Hyperlink", "https://github.com/ocornut/imgui");
ImGui::Button("Button", ImVec2(100.0f, 20.0f));
ImGui::Checkbox("Checkbox", (bool*)this->lpBuffer);
```
## Screenshot
![Image](https://github.com/WangPeng95997/ImGui-Docking-Hook/blob/master/Screenshot/Image.png)

## Credits
* ImGui https://github.com/ocornut/imgui
* kiero https://github.com/Rebzzel/kiero
* MinHook https://github.com/TsudaKageyu/minhook
* UniversalHookX https://github.com/bruhmoment21/UniversalHookX