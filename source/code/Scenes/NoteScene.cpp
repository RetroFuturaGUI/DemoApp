#include "NoteScene.hpp"
#include "ResourceManager.hpp"
#include "Texture.hpp"
#include <array>
#include <span>
#include <string_view>

void DemoApp::NoteScene::SwitchFill()
{
    if(!_noteTextBox)
        return;

    if(!_fillButton)
        return;

    static constexpr std::array<std::string_view, 4> fillNames { "Solid", "Linear Shift", "Radial", "Hue Star" };
    _textFillType = static_cast<RetroFuturaGUI::FillType>((static_cast<uSize>(_textFillType) + 1) % fillNames.size());
    _noteTextBox->GetText().SetFillType(_textFillType);
    _fillButton->GetText().SetString(fillNames[static_cast<uSize>(_textFillType)], false);
}

void DemoApp::NoteScene::SwitchRaster()
{
    if(!_noteTextBox)
        return;

    _textEffects ^= TextRaster;
    const bool isOn { 0 != (_textEffects & TextRaster) };
    static constexpr std::array dotDiameters { 3.0f, 1.0f, 3.0f };
    _noteTextBox->GetText().SetPrimaryRasterWidthTransfer(isOn ? std::span<const f32>(dotDiameters) : std::span<const f32>());
    styleEffectButton(_rasterButton.Get(), isOn);
}

void DemoApp::NoteScene::SwitchFog()
{
    if(!_noteTextBox)
        return;

    _textEffects ^= TextFog;
    const bool isOn { 0 != (_textEffects & TextFog) };

    static constexpr std::array fogDensity { 1.0f, 0.55f, 0.3f, 0.15f };
    _noteTextBox->GetText().SetFogDensity(isOn ? std::span<const f32>(fogDensity) : std::span<const f32>());
    styleEffectButton(_fogButton.Get(), isOn);
}

void DemoApp::NoteScene::SwitchGlass()
{
    if(!_noteTextBox)
        return;

    RetroFuturaGUI::Texture* backdrop { RetroFuturaGUI::ResourceManager::GetTexture("Resources/Images/FrutigerAero.png") };

    if(!backdrop)
        return;

    _textEffects ^= TextGlass;
    const bool isOn { 0 != (_textEffects & TextGlass) };
    _noteTextBox->GetText().SetWindowBackgroundImageTextureID(isOn ? backdrop->GetID() : 0);
    applyTextColors();
    styleEffectButton(_glassButton.Get(), isOn);
}

void DemoApp::NoteScene::SwitchMetal()
{
    if(!_noteTextBox)
        return;

    RetroFuturaGUI::Texture* metal { RetroFuturaGUI::ResourceManager::GetTexture("Resources/Images/metal.jpg") };

    if(!metal)
        return;

    RetroFuturaGUI::Texture* chrome { RetroFuturaGUI::ResourceManager::GetTexture("Resources/Images/chrome_mask.png") };

    if(!chrome)
        return;

    _textEffects ^= TextMetal;
    const bool isOn { 0 != (_textEffects & TextMetal) };

    //The metal keeps its proportions as the text grows, and the mask's bright sky, dark horizon and rising ground shade each line into chrome
    _noteTextBox->GetText().SetImageTextureID(isOn ? metal->GetID() : 0);
    _noteTextBox->GetText().SetImageFit(RetroFuturaGUI::ImageFit::Fill);
    _noteTextBox->GetText().SetMaskTextureID(isOn ? chrome->GetID() : 0);
    _noteTextBox->GetText().SetMaskMode(RetroFuturaGUI::MaskMode::Shade);
    _noteTextBox->GetText().SetMaskSpan(RetroFuturaGUI::MaskSpan::EachLine);
    applyTextColors();
    styleEffectButton(_metalButton.Get(), isOn);
}

void DemoApp::NoteScene::SwitchOutline()
{
    if(!_noteTextBox)
        return;

    _textEffects ^= TextOutline;
    const bool isOn { 0 != (_textEffects & TextOutline) };

    static constexpr std::array outlineColors { glm::vec4(0.05f, 0.05f, 0.2f, 1.0f) };

    for(const RetroFuturaGUI::ColorState state : { RetroFuturaGUI::ColorState::Enabled, RetroFuturaGUI::ColorState::Hover, RetroFuturaGUI::ColorState::Clicked })
        _noteTextBox->GetText().GetOutline().SetColors(outlineColors, state);

    _noteTextBox->GetText().GetOutline().SetWidth(isOn ? 3.0f : 0.0f);
    styleEffectButton(_outlineButton.Get(), isOn);
}

void DemoApp::NoteScene::ShowEffectsSample()
{
    showSample(TextSample::Effects);
}

void DemoApp::NoteScene::ShowEmojiSample()
{
    showSample(TextSample::Emoji);
}

void DemoApp::NoteScene::ShowKanjiSample()
{
    showSample(TextSample::Kanji);
}

void DemoApp::NoteScene::ShowThaiSample()
{
    showSample(TextSample::Thai);
}

void DemoApp::NoteScene::ShowMixedSample()
{
    showSample(TextSample::Mixed);
}

void DemoApp::NoteScene::ShowRightToLeftSample()
{
    showSample(TextSample::RightToLeft);
}

void DemoApp::NoteScene::ShowVerticalSample()
{
    showSample(TextSample::Vertical);
}

void DemoApp::NoteScene::LoadMainScene()
{
    loadScene("MainScene");
}

void DemoApp::NoteScene::showSample(const TextSample sample)
{
    if(!_noteTextBox)
        return;

    //Columns run right to left, so they start at the box's right edge, and Hebrew and Arabic are set against it too. Every other sample reads from the left
    const bool
        isVertical { TextSample::Vertical == sample },
        isRightAligned { isVertical || TextSample::RightToLeft == sample };
    _noteTextBox->GetText().SetFlow(isVertical ? RetroFuturaGUI::TextFlow::VerticalRightToLeft : RetroFuturaGUI::TextFlow::Horizontal);
    _noteTextBox->GetText().SetAlignment(isRightAligned ? RetroFuturaGUI::TextAlignment::Right : RetroFuturaGUI::TextAlignment::Left);
    _noteTextBox->GetText().SetString(getSampleText(sample), false);
    styleEffectButton(getSampleButton(_textSample), false);
    _textSample = sample;
    styleEffectButton(getSampleButton(sample), true);
}

RetroFuturaGUI::Button* DemoApp::NoteScene::getSampleButton(const TextSample sample) const
{
    switch(sample)
    {
        case TextSample::Emoji:
            return _emojiSampleButton.Get();
        case TextSample::Kanji:
            return _kanjiSampleButton.Get();
        case TextSample::Thai:
            return _thaiSampleButton.Get();
        case TextSample::Mixed:
            return _mixedSampleButton.Get();
        case TextSample::RightToLeft:
            return _rightToLeftSampleButton.Get();
        case TextSample::Vertical:
            return _verticalSampleButton.Get();
        default: //Effects
            return _effectsSampleButton.Get();
    }
}

std::string_view DemoApp::NoteScene::getSampleText(const TextSample sample)
{
    switch(sample)
    {
        case TextSample::Emoji:
            return "Emoji 😀 😂 🥰 🤔\n"
                   "👍🏽 👋🏿 🙌🏼\n"
                   "👨‍👩‍👧 👩‍💻 🧑‍🚀\n"
                   "🐱 🍕 🚀 ☕ ❤️ ✨";
        case TextSample::Kanji:
            return "漢字と仮名\n"
                   "日本語の文章です。\n"
                   "東京・京都・大阪\n"
                   "春夏秋冬、花鳥風月！";
        case TextSample::Thai:
            return "ภาษาไทย\n"
                   "สวัสดีครับ\n"
                   "ขอบคุณมาก น้ำใจ\n"
                   "กรุงเทพมหานคร";
        case TextSample::Mixed:
            return "Jalapeño 🌶️, Paloma 🕊️\n"
                   "Coração 💜, Olá 👋🏽\n"
                   "แมว 🐈‍⬛, ศักดิ์สิทธิ์ ☘️\n"
                   "大山猫 🐱, あぢさゐ 🌺\n"
                   "𰻝𰻝面 🍜, ⻱龜亀龟 🐢\n"
                   "Fußgängerübergänge 🚶🏽\n"
                   "👩🏾‍👩🏾‍👧🏾‍👦🏾🏳️‍⚧️🇫🇮🫘, Unicode 18 test: 🪋";
        case TextSample::RightToLeft:
            return "שלום עולם!\n"
                   "مرحبا بالعالم\n"
                   "עברית and العربية\n"
                   "(גרסה 2.0) نسخة 3";
        case TextSample::Vertical:
            return "縦書きの\n"
                   "「テスト」です。\n"
                   "二列目、三列目";
        default: //Effects
            return "RetroFuturaGUI\nText effects\nFill, raster, fog\nGlass, metal, outline";
    }
}

void DemoApp::NoteScene::applyTextColors()
{
    if(!_noteTextBox)
        return;

    //A solid fill shows the first color, the gradients all three. The metal shows alone, and the glass through a tint
    f32 alpha { 1.0f };

    if(0 != (_textEffects & TextMetal))
        alpha = 0.0f;
    else if(0 != (_textEffects & TextGlass))
        alpha = 0.35f;

    const std::array textColors
    {
        glm::vec4(0.25f, 0.6f, 1.0f, alpha),
        glm::vec4(1.0f, 0.3f, 0.65f, alpha),
        glm::vec4(1.0f, 0.85f, 0.2f, alpha)
    };

    for(const RetroFuturaGUI::ColorState state : { RetroFuturaGUI::ColorState::Enabled, RetroFuturaGUI::ColorState::Hover, RetroFuturaGUI::ColorState::Clicked })
        _noteTextBox->GetText().SetColors(textColors, state);
}

void DemoApp::NoteScene::styleEffectButton(RetroFuturaGUI::Button* button, const bool isOn)
{
    if(!button)
        return;

    button->GetBackground().SetColors(std::array { isOn ? glm::vec4(0.25f, 0.45f, 0.85f, 1.0f) : glm::vec4(0.2f, 0.2f, 0.25f, 1.0f) }, RetroFuturaGUI::ColorState::Enabled);
    button->GetBackground().SetColors(std::array { isOn ? glm::vec4(0.3f, 0.52f, 0.95f, 1.0f) : glm::vec4(0.28f, 0.28f, 0.35f, 1.0f) }, RetroFuturaGUI::ColorState::Hover);
    button->GetBackground().SetColors(std::array { isOn ? glm::vec4(0.35f, 0.6f, 1.0f, 1.0f) : glm::vec4(0.36f, 0.36f, 0.45f, 1.0f) }, RetroFuturaGUI::ColorState::Clicked);
}