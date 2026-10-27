#include "NoteScene.hpp"
#include "NoteScene_p.hpp"
#include "ResourceManager.hpp"
#include "Texture.hpp"
#include <array>
#include <span>
#include <string_view>

void TestProject::NoteScene::on_fillButton_click()
{
    if(!_members)
        return;

    if(!_members->_noteTextBox)
        return;

    if(!_members->_fillButton)
        return;

    //In FillType's order
    static constexpr std::array<std::string_view, 4> fillNames { "Solid", "Linear Shift", "Radial", "Hue Star" };
    _members->_textFillType = static_cast<RetroFuturaGUI::FillType>((static_cast<uSize>(_members->_textFillType) + 1) % fillNames.size());
    _members->_noteTextBox->SetTextFillType(_members->_textFillType);
    _members->_fillButton->SetText(fillNames[static_cast<uSize>(_members->_textFillType)], false);
}

void TestProject::NoteScene::on_rasterButton_click()
{
    if(!_members)
        return;

    if(!_members->_noteTextBox)
        return;

    _members->_textEffects ^= TextRaster;
    const bool isOn { 0 != (_members->_textEffects & TextRaster) };

    //Dark dots, 3 px at the text's ends and 1 px in its middle, drifting along 35 degrees
    static constexpr std::array dotDiameters { 3.0f, 1.0f, 3.0f };
    _members->_noteTextBox->SetTextPrimaryRasterWidthTransfer(isOn ? std::span<const f32>(dotDiameters) : std::span<const f32>());
    styleEffectButton(_members->_rasterButton.get(), isOn);
}

void TestProject::NoteScene::on_fogButton_click()
{
    if(!_members)
        return;

    if(!_members->_noteTextBox)
        return;

    _members->_textEffects ^= TextFog;
    const bool isOn { 0 != (_members->_textEffects & TextFog) };

    //The main window's fog
    static constexpr std::array fogDensity { 1.0f, 0.55f, 0.3f, 0.15f };
    _members->_noteTextBox->SetTextFogDensity(isOn ? std::span<const f32>(fogDensity) : std::span<const f32>());
    styleEffectButton(_members->_fogButton.get(), isOn);
}

void TestProject::NoteScene::on_glassButton_click()
{
    if(!_members)
        return;

    if(!_members->_noteTextBox)
        return;

    //The window has no background image of its own, so the glass shows a picture in its place
    RetroFuturaGUI::Texture* backdrop { RetroFuturaGUI::ResourceManager::GetTexture("Resources/img/FrutigerAero.png") };

    if(!backdrop)
        return;

    _members->_textEffects ^= TextGlass;
    const bool isOn { 0 != (_members->_textEffects & TextGlass) };

    _members->_noteTextBox->SetTextWindowBackgroundImageTextureID(isOn ? backdrop->GetID() : 0);
    applyTextColors();
    styleEffectButton(_members->_glassButton.get(), isOn);
}

void TestProject::NoteScene::on_metalButton_click()
{
    if(!_members)
        return;

    if(!_members->_noteTextBox)
        return;

    RetroFuturaGUI::Texture* metal { RetroFuturaGUI::ResourceManager::GetTexture("Resources/img/metal.jpg") };

    if(!metal)
        return;

    _members->_textEffects ^= TextMetal;
    const bool isOn { 0 != (_members->_textEffects & TextMetal) };

    _members->_noteTextBox->SetTextBackgroundImageTextureID(isOn ? metal->GetID() : 0);
    applyTextColors();
    styleEffectButton(_members->_metalButton.get(), isOn);
}

void TestProject::NoteScene::applyTextColors()
{
    if(!_members)
        return;

    if(!_members->_noteTextBox)
        return;

    //A solid fill shows the first color, the gradients all three. The metal shows alone, and the glass through a tint
    f32 alpha { 1.0f };

    if(0 != (_members->_textEffects & TextMetal))
        alpha = 0.0f;
    else if(0 != (_members->_textEffects & TextGlass))
        alpha = 0.35f;

    const std::array textColors
    {
        glm::vec4(0.25f, 0.6f, 1.0f, alpha),
        glm::vec4(1.0f, 0.3f, 0.65f, alpha),
        glm::vec4(1.0f, 0.85f, 0.2f, alpha)
    };

    for(const RetroFuturaGUI::ColorState state : { RetroFuturaGUI::ColorState::Enabled, RetroFuturaGUI::ColorState::Hover, RetroFuturaGUI::ColorState::Clicked })
        _members->_noteTextBox->SetTextColors(textColors, state);
}

void TestProject::NoteScene::styleEffectButton(RetroFuturaGUI::Button* button, const bool isOn)
{
    if(!button)
        return;

    button->SetBackgroundColors(std::array { isOn ? glm::vec4(0.25f, 0.45f, 0.85f, 1.0f) : glm::vec4(0.2f, 0.2f, 0.25f, 1.0f) }, RetroFuturaGUI::ColorState::Enabled);
    button->SetBackgroundColors(std::array { isOn ? glm::vec4(0.3f, 0.52f, 0.95f, 1.0f) : glm::vec4(0.28f, 0.28f, 0.35f, 1.0f) }, RetroFuturaGUI::ColorState::Hover);
    button->SetBackgroundColors(std::array { isOn ? glm::vec4(0.35f, 0.6f, 1.0f, 1.0f) : glm::vec4(0.36f, 0.36f, 0.45f, 1.0f) }, RetroFuturaGUI::ColorState::Clicked);
}
