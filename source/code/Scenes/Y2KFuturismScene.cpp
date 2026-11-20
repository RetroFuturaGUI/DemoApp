#include "Y2KFuturismScene.hpp"
#include <span>

void DemoApp::Y2KFuturismScene::SetUpWidgets()
{
    addFinishes();
    addModes();
    showSamples();
}

void DemoApp::Y2KFuturismScene::LoadMainScene()
{
    loadScene("MainScene");
}

void DemoApp::Y2KFuturismScene::addFinishes()
{
    if(!_finish)
        return;

    for(const std::string_view finish : { "Chrome", "Neon", "Liquid metal" })
        _finish->AddItem(finish);
}

void DemoApp::Y2KFuturismScene::addModes()
{
    if(!_mode)
        return;

    std::array rows { 0.5f, 0.5f };
    std::array columns { 1.0f };
    _mode->SetAxisDefinitions(rows, columns);
    addMode("Turbo", 0);
    addMode("Cruise", 1);
}

void DemoApp::Y2KFuturismScene::addMode(std::string_view mode, const i64 row)
{
    if(!_mode)
        return;

    RetroFuturaGUI::RadioButton* radioButton { _mode->AddRadioButton(mode, glm::i64vec2(row, 0)) };

    if(!radioButton)
        return;

    styleModeButton(*radioButton);
    radioButton->SetValue(0 == row, false);
    RetroFuturaGUI::Label* label { _mode->GetRadioButtonLabel(mode) };

    if(!label)
        return;

    styleModeLabel(*label);
    _mode->SetLabel(mode, mode, false); //last, since it lays the group out again with the label's final width
}

void DemoApp::Y2KFuturismScene::styleModeButton(RetroFuturaGUI::RadioButton& radioButton)
{
    static constexpr std::array dotColors { glm::vec4(0.25f, 0.85f, 1.0f, 1.0f) };
    static constexpr std::array wellColors { glm::vec4(0.02f, 0.06f, 0.18f, 1.0f) };
    static constexpr std::array rimColors { glm::vec4(0.95f, 0.96f, 0.97f, 1.0f), glm::vec4(0.37f, 0.39f, 0.44f, 1.0f) };

    radioButton.SetSize(glm::vec3(32.0f, 32.0f, 0.05f));

    for(const RetroFuturaGUI::ColorState state : { RetroFuturaGUI::ColorState::Enabled, RetroFuturaGUI::ColorState::Hover, RetroFuturaGUI::ColorState::Clicked })
    {
        radioButton.SetIndicatorColors(dotColors, state);
        radioButton.GetBackground().SetColors(wellColors, state);
        radioButton.GetBorder().SetColors(rimColors, state);
    }

    radioButton.GetBorder().SetFillType(RetroFuturaGUI::FillType::LinearShift);
    radioButton.GetBorder().SetGradientDegree(90.0f);
    radioButton.GetBorder().SetWidth(4.0f);
    radioButton.GetBackground().SetCornerRadii(glm::vec4(16.0f));
    radioButton.GetBorder().SetCornerRadii(glm::vec4(16.0f));
    radioButton.SetIndicatorPadding(6.0f);
}

void DemoApp::Y2KFuturismScene::styleModeLabel(RetroFuturaGUI::Label& label)
{
    static constexpr std::array labelColors { glm::vec4(0.87f, 0.98f, 1.0f, 1.0f) };

    label.SetSize(glm::vec3(160.0f, 40.0f, 0.01f));
    label.GetText().SetFontFamily("Arial", 24.0f, RetroFuturaGUI::FontSizeUnit::Pixels, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Black);
    label.GetText().SetColors(labelColors, RetroFuturaGUI::ColorState::Enabled);
    label.GetText().SetPadding(12.0f);
}

void DemoApp::Y2KFuturismScene::showSamples()
{
    if(!_speed)
        return;

    if(!_boost)
        return;

    _speed->SetMinValue(0.0f);
    _speed->SetMaxValue(1.0f);
    _speed->SetLineColor(0, glm::vec4(0.36f, 0.88f, 1.0f, 1.0f));
    _speed->SetLineThickness(3.0f);
    _speed->SetData(0, std::span<const f32>(_speedSamples), false);

    _boost->SetMinValue(0.0f);
    _boost->SetMaxValue(1.0f);
    _boost->SetData(std::span<const f32>(_boostSamples), false);
}