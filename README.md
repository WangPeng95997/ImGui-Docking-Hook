# ImGui-DirectX9-Hook

## Getting Started
[Dllmain.cpp](https://github.com/WangPeng95997/ImGui-Docking-Hook/blob/master/ImGui-Docking-Hook/Dllmain.cpp#L267-L270)
```C++
if (g_GuiWindow->showMenu) {
	ImGui::ShowDemoWindow();
	//g_GuiWindow->Update();
}
```
## Screenshot
![Image](https://github.com/WangPeng95997/ImGui-Docking-Hook/blob/master/Screenshot/Image.png)

## Credits
* ImGui   https://github.com/ocornut/imgui
* kiero https://github.com/Rebzzel/kiero
* MinHook https://github.com/TsudaKageyu/minhook
* UniversalHookX https://github.com/bruhmoment21/UniversalHookX