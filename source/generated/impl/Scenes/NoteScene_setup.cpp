#include "NoteScene.hpp"
#include "NoteScene_p.hpp"
#include "Window.hpp"
#include "SceneLoader.hpp"
#include "IncludeHelper.hpp"
#include "PlatformBridge.hpp"
#include "Fonts.hpp"
#include <array>
#include <memory>
#include <string_view>
#include <utility>
#include <vector>

TestProject::NoteScene::NoteScene(RetroFuturaGUI::Window* parentWindow)
{
    _members = std::make_unique<NoteScene_p>();
    setup(parentWindow);
}

TestProject::NoteScene::~NoteScene()
{
    //Unregister before the scene is freed, or the loader's registry and the window's draw order
    //are left holding a pointer to it.
    if(!_members)
        return;

    if(!_members->_scene)
        return;

    RetroFuturaGUI::SceneLoader::UnregisterScene(RetroFuturaGUI::SceneLoader::GetSceneID(_members->_scene->GetName()));
}

RetroFuturaGUI::Scene* TestProject::NoteScene::GetScene() const
{
    if(!_members)
        return nullptr;

    return _members->_scene.get();
}

void TestProject::NoteScene::setup(RetroFuturaGUI::Window* parentWindow)
{
    if(!parentWindow)
        return;

    RetroFuturaGUI::Projection* projection { parentWindow->GetProjection() };

    if(!projection)
        return;

    GLFWwindow* window { parentWindow->GetGlfwWindow() };

//A row of text effect buttons, and below it the text box, a small margin away from the edges of whatever the window's bar
//leaves - or, while the window sits in a tab, of the tab's content area
    const RetroFuturaGUI::AxisDefinition axisDefinition
    {
        ._RowDefinition = { 0.02f, 0.1f, 0.02f, 0.84f, 0.02f },
        ._ColumnDefinition = { 0.03f, 0.188f, 0.188f, 0.188f, 0.188f, 0.188f, 0.03f },
        ._LayerDefinition = { 1.0f }
    };

    _members->_scene = RetroFuturaGUI::SceneLoader::CreateScene("NoteScene", parentWindow);

    if(!_members->_scene)
        return;

    _members->_scene->SetLasagnaAxis(axisDefinition, projection);
    RetroFuturaGUI::Lasagna* rootLasagna { _members->_scene->GetRootContainer<RetroFuturaGUI::Lasagna>() };

    if(!rootLasagna)
        return;

    _members->_noteTextBox = std::make_unique<RetroFuturaGUI::MultilineTextBox>("NoteTextBox", projection, rootLasagna, RetroFuturaGUI::WidgetTypeID::Lasagna, window);
    RetroFuturaGUI::MultilineTextBox* noteTextBox { _members->_noteTextBox.get() };

    if(!noteTextBox)
        return;

    noteTextBox->SetBackgroundColors(std::array { glm::vec4(0.12f, 0.12f, 0.16f, 1.0f) }, RetroFuturaGUI::ColorState::Enabled);
    noteTextBox->SetBackgroundColors(std::array { glm::vec4(0.15f, 0.15f, 0.2f, 1.0f) }, RetroFuturaGUI::ColorState::Hover);
    noteTextBox->SetBackgroundColors(std::array { glm::vec4(0.15f, 0.15f, 0.2f, 1.0f) }, RetroFuturaGUI::ColorState::Clicked);
    noteTextBox->SetBackgroundColors(std::array { glm::vec4(0.08f, 0.08f, 0.1f, 1.0f) }, RetroFuturaGUI::ColorState::Disabled);
    noteTextBox->SetBorderColors(std::array { glm::vec4(0.35f, 0.35f, 0.45f, 1.0f) }, RetroFuturaGUI::ColorState::Enabled);
    noteTextBox->SetBorderColors(std::array { glm::vec4(0.45f, 0.45f, 0.6f, 1.0f) }, RetroFuturaGUI::ColorState::Hover);
    noteTextBox->SetBorderColors(std::array { glm::vec4(0.55f, 0.55f, 0.75f, 1.0f) }, RetroFuturaGUI::ColorState::Clicked);
    noteTextBox->SetBorderWidth(1.0f);
    noteTextBox->SetCornerRadii(glm::vec4(8.0f));
#if defined(TARGET_PLATFORM_LINUX)
    noteTextBox->SetFontFamily("Noto Sans", 40.0f, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Normal);
#elif defined(TARGET_PLATFORM_WINDOWS)
    noteTextBox->SetFontFamily("Arial", 40.0f, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Normal);
#endif
    //Large enough for the effects to show on the glyph strokes
    noteTextBox->SetText("RetroFuturaGUI\nText effects\nFill, raster, fog\nGlass, metal", false);
    noteTextBox->SetTextAlignment(RetroFuturaGUI::TextAlignment::Left);
    noteTextBox->SetTextPadding(8.0f);
    noteTextBox->SetPlaceholderText("Type here, also while this window sits in a tab...");
    noteTextBox->SetPlaceholderTextColors(std::array { glm::vec4(0.5f, 0.5f, 0.55f, 1.0f) });

    std::vector<glm::vec4> caretColors { glm::vec4(0.85f, 0.85f, 0.9f, 1.0f) };
    noteTextBox->SetCaretColors(caretColors);
    noteTextBox->SetCaretBlinkTime(750.0);

    rootLasagna->AttachWidget(3, 1, 0, noteTextBox, RetroFuturaGUI::SizingMode::FILL_XY, 1, 5);

//Text effects: the gradients drift and turn, and the raster and fog are styled here and switched on by their buttons
    applyTextColors();
    noteTextBox->SetTextGradientAnimationSpeed(0.003f);
    noteTextBox->SetTextGradientRotationSpeed(0.2f);
    noteTextBox->SetTextRasterPattern(RetroFuturaGUI::RasterPattern::Dotted);
    noteTextBox->SetTextPrimaryRasterColor(glm::vec4(0.05f, 0.05f, 0.1f, 0.9f));
    noteTextBox->SetTextRasterSpacing(2.0f);
    noteTextBox->SetTextRasterDegree(35.0f);
    noteTextBox->SetTextDotTransparencyTransfer(0.4f);
    noteTextBox->SetTextRasterAnimationSpeed(-0.05f);
    noteTextBox->SetTextFogAlpha(0.8f);
    noteTextBox->SetTextFogSpeed(0.12f);
    noteTextBox->SetTextFogClearing(0.1f);

//Effect buttons
    _members->_fillButton = std::make_unique<RetroFuturaGUI::Button>("NoteFillButton", projection, rootLasagna, RetroFuturaGUI::WidgetTypeID::Lasagna, window);
    _members->_rasterButton = std::make_unique<RetroFuturaGUI::Button>("NoteRasterButton", projection, rootLasagna, RetroFuturaGUI::WidgetTypeID::Lasagna, window);
    _members->_fogButton = std::make_unique<RetroFuturaGUI::Button>("NoteFogButton", projection, rootLasagna, RetroFuturaGUI::WidgetTypeID::Lasagna, window);
    _members->_glassButton = std::make_unique<RetroFuturaGUI::Button>("NoteGlassButton", projection, rootLasagna, RetroFuturaGUI::WidgetTypeID::Lasagna, window);
    _members->_metalButton = std::make_unique<RetroFuturaGUI::Button>("NoteMetalButton", projection, rootLasagna, RetroFuturaGUI::WidgetTypeID::Lasagna, window);

    const std::pair<RetroFuturaGUI::Button*, std::string_view> buttons[]
    {
        { _members->_fillButton.get(), "Solid" },
        { _members->_rasterButton.get(), "Raster" },
        { _members->_fogButton.get(), "Fog" },
        { _members->_glassButton.get(), "Glass" },
        { _members->_metalButton.get(), "Metal" }
    };
    u32 column { 1 };

    for(const auto& [button, text] : buttons)
    {
        const u32 buttonColumn { column };
        ++column;

        if(!button)
            continue;

        button->SetSize(glm::vec3(110.0f, 36.0f, 0.01f));
        button->SetCornerRadii(glm::vec4(8.0f));
        styleEffectButton(button, false);
        button->SetBackgroundFillType(RetroFuturaGUI::FillType::Solid);
        button->SetBorderColors(std::array { glm::vec4(0.35f, 0.35f, 0.45f, 1.0f) }, RetroFuturaGUI::ColorState::Enabled);
        button->SetBorderWidth(1.0f);
        button->SetFontFamily("Arial", 15.0f, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Normal);
        button->SetText(text, false);
        button->SetTextAlignment(RetroFuturaGUI::TextAlignment::Center);
        rootLasagna->AttachWidget(1, buttonColumn, 0, button, RetroFuturaGUI::SizingMode::FIXED);
    }

    _members->_fillButton->Connect_OnClick([this]() { on_fillButton_click(); }, false);
    _members->_rasterButton->Connect_OnClick([this]() { on_rasterButton_click(); }, false);
    _members->_fogButton->Connect_OnClick([this]() { on_fogButton_click(); }, false);
    _members->_glassButton->Connect_OnClick([this]() { on_glassButton_click(); }, false);
    _members->_metalButton->Connect_OnClick([this]() { on_metalButton_click(); }, false);
}
