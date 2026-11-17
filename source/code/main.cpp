#include <config.hpp>
#include "IncludeHelper.hpp"

#ifdef DYNLIB_MODE

#include "DynamicLibWidgetManager.hpp"
#include "FontManager.hpp"
#include "GeneratedWindow.hpp"
#include "MainWindow.hpp"
#include "PlatformBridge.hpp"
#include "RetroFuturaGuiInit.hpp"
#include <memory>
#include <span>
#include <vector>

//The binding opens the windows and runs their frames. The start window is the first one
static std::vector<std::unique_ptr<DemoApp::GeneratedWindow>> windows {};

extern "C" EXPORT_API void SetWorkingDirectory(const char* dir)
{
    PlatformBridge::Paths::SetWorkingDir(dir);
}

extern "C" EXPORT_API void InitRetroFuturaGUI()
{
    PlatformBridge::RefreshPlatformBridge();
    RetroFuturaGUI::GlfwInit();
    RetroFuturaGUI::FontManager::Init();
    windows.push_back(DemoApp::GeneratedWindow::Create<DemoApp::MainWindow>());
}

extern "C" EXPORT_API void Draw()
{
    DemoApp::GeneratedWindow::RunFrames(windows);

    //The windows go while their contexts exist, the start window last; left to the library's unloading, they crash it
    while(!windows.empty())
        windows.pop_back();

    RetroFuturaGUI::GlfwTerminate();
}

extern "C" EXPORT_API void ConnectSlot(const char* id, RetroFuturaGUI::CallbackType callback, const i32 action, const bool async)
{
    RetroFuturaGUI::DynamicLibWidgetManager::ConnectSlot(id, callback, action, async);
}

extern "C" EXPORT_API void DisconnectSlot(const char* id, RetroFuturaGUI::CallbackType callback, const i32 action)
{
    RetroFuturaGUI::DynamicLibWidgetManager::DisconnectSlot(id, callback, action);
}

extern "C" EXPORT_API void SetRotation(const char* id, f32 x, f32 y, f32 z)
{
    RetroFuturaGUI::DynamicLibWidgetManager::SetRotation(id, glm::vec3(x, y, z));
}

extern "C" EXPORT_API void SetPosition(const char* id, f32 x, f32 y, f32 z)
{
    RetroFuturaGUI::DynamicLibWidgetManager::SetPosition(id, glm::vec3(x, y, z));
}

extern "C" EXPORT_API void SetSize(const char* id, f32 width, f32 height)
{
    RetroFuturaGUI::DynamicLibWidgetManager::SetSize(id, width, height);
}

extern "C" EXPORT_API void SetBackgroundColors(const char* id, f32* colors, u32 colorCount, RetroFuturaGUI::ColorState colorState)
{
    std::span<glm::vec4> col(reinterpret_cast<glm::vec4*>(colors), colorCount);
    RetroFuturaGUI::DynamicLibWidgetManager::SetBackgroundColors(id, col, colorState);
}

extern "C" EXPORT_API void SetBackgroundFillType(const char* id, RetroFuturaGUI::FillType fillType)
{
    RetroFuturaGUI::DynamicLibWidgetManager::SetBackgroundFillType(id, fillType);
}

extern "C" EXPORT_API void SetBackgroundGradientOffset(const char* id, f32 gradientOffset)
{
    RetroFuturaGUI::DynamicLibWidgetManager::SetBackgroundGradientOffset(id, gradientOffset);
}

extern "C" EXPORT_API void SetBackgroundGradientAnimationSpeed(const char* id, f32 animationSpeed)
{
    RetroFuturaGUI::DynamicLibWidgetManager::SetBackgroundGradientAnimationSpeed(id, animationSpeed);
}

extern "C" EXPORT_API void SetBackgroundGradientDegree(const char* id, f32 degree)
{
    RetroFuturaGUI::DynamicLibWidgetManager::SetBackgroundGradientDegree(id, degree);
}

extern "C" EXPORT_API void SetBackgroundGradientRotationSpeed(const char* id, f32 rotationSpeed)
{
    RetroFuturaGUI::DynamicLibWidgetManager::SetBackgroundGradientRotationSpeed(id, rotationSpeed);
}

extern "C" EXPORT_API void SetWindowBackgroundImageTextureID(const char* id, u32 textureID)
{
    RetroFuturaGUI::DynamicLibWidgetManager::SetWindowBackgroundImageTextureID(id, textureID);
}

extern "C" EXPORT_API void SetBorderColors(const char* id, f32* colors, u32 colorCount, RetroFuturaGUI::ColorState colorState)
{
    std::span<glm::vec4> col(reinterpret_cast<glm::vec4*>(colors), colorCount);
    RetroFuturaGUI::DynamicLibWidgetManager::SetBorderColors(id, col, colorState);
}

extern "C" EXPORT_API void SetBorderFillType(const char* id, RetroFuturaGUI::FillType fillType)
{
    RetroFuturaGUI::DynamicLibWidgetManager::SetBorderFillType(id, fillType);
}

extern "C" EXPORT_API void SetBorderGradientOffset(const char* id, f32 gradientOffset)
{
    RetroFuturaGUI::DynamicLibWidgetManager::SetBorderGradientOffset(id, gradientOffset);
}

extern "C" EXPORT_API void SetBorderGradientAnimationSpeed(const char* id, f32 animationSpeed)
{
    RetroFuturaGUI::DynamicLibWidgetManager::SetBorderGradientAnimationSpeed(id, animationSpeed);
}

extern "C" EXPORT_API void SetBorderGradientDegree(const char* id, f32 degree)
{
    RetroFuturaGUI::DynamicLibWidgetManager::SetBorderGradientDegree(id, degree);
}

extern "C" EXPORT_API void SetBorderGradientRotationSpeed(const char* id, f32 rotationSpeed)
{
    RetroFuturaGUI::DynamicLibWidgetManager::SetBorderGradientRotationSpeed(id, rotationSpeed);
}

extern "C" EXPORT_API void SetWindowBorderImageTextureID(const char* id, u32 textureID)
{
    RetroFuturaGUI::DynamicLibWidgetManager::SetWindowBorderImageTextureID(id, textureID);
}

extern "C" EXPORT_API void SetEnabled(const char* id, bool enabled, bool emitSignal)
{
    RetroFuturaGUI::DynamicLibWidgetManager::SetEnabled(id, enabled, emitSignal);
}

extern "C" EXPORT_API void SetTextColors(const char* id, f32* colors, u32 colorCount, RetroFuturaGUI::ColorState colorState)
{
    std::span<glm::vec4> col(reinterpret_cast<glm::vec4*>(colors), colorCount);
    RetroFuturaGUI::DynamicLibWidgetManager::SetTextColors(id, col, colorState);
}

extern "C" EXPORT_API void SetTextFillType(const char* id, RetroFuturaGUI::FillType fillType)
{
    RetroFuturaGUI::DynamicLibWidgetManager::SetTextFillType(id, fillType);
}

extern "C" EXPORT_API void SetText(const char* id, const char* text, bool emitSignal)
{
    RetroFuturaGUI::DynamicLibWidgetManager::SetText(id, text, emitSignal);
}


extern "C" EXPORT_API bool OpenFileExplorer(const char* title, i32 width, i32 height, const char* startPath, u32 flags, const char* extensions, RetroFuturaGUI::PathsCallbackType onResult, RetroFuturaGUI::CallbackType onDismiss)
{
    if(windows.empty())
        return false;

    if(!windows.front())
        return false;

    return RetroFuturaGUI::DynamicLibWidgetManager::OpenFileExplorer(windows.front()->GetWindow(), title ? title : "", width, height, startPath ? startPath : "", flags, extensions ? extensions : ".*", onResult, onDismiss);
}

#else

#include "Start.hpp"

i32 main()
{
    return DemoApp::Start();
}

#endif