#pragma once
#include "NoteScene_p.hpp"
#include "IncludeHelper.hpp"
#include <string_view>

namespace DemoApp
{
    /// @brief A multiline text box to type into. A row of buttons above it switches the text's fill, raster, fog, glass, a metal
    ///        image and an outline, to test the text effects, and a second row puts sample texts into it: emoji, kanji, Thai,
    ///        mixed scripts, right to left and vertical Japanese.
    class NoteScene final : public NoteScene_p
    {
    public:
        explicit NoteScene(RetroFuturaGUI::Window* parentWindow) : NoteScene_p(parentWindow) {}

    privateSlots:
        void SwitchFill() override;
        void SwitchRaster() override;
        void SwitchFog() override;
        void SwitchGlass() override;
        void SwitchMetal() override;
        void SwitchOutline() override;
        void ShowEffectsSample() override;
        void ShowEmojiSample() override;
        void ShowKanjiSample() override;
        void ShowThaiSample() override;
        void ShowMixedSample() override;
        void ShowRightToLeftSample() override;
        void ShowVerticalSample() override;
        void LoadMainScene() override;

    private:
        /// @brief The effects the effect buttons have switched on for the note's text, as bits of one mask.
        enum TextEffects : u32
        {
            NoTextEffects = 0,
            TextRaster = 1,
            TextFog = 1 << 1,
            TextGlass = 1 << 2,
            TextMetal = 1 << 3,
            TextOutline = 1 << 4
        };

        /// @brief The texts the sample buttons put into the note, in the buttons' order.
        enum class TextSample : u32
        {
            Effects, // the effects' names, as the note starts
            Emoji, // faces, skin tones and sequences joined into one glyph
            Kanji, // kanji with kana and Japanese punctuation
            Thai, // vowels and tone marks stacked over and under the letters
            Mixed, // several scripts and emoji on a line, and kerning
            RightToLeft, // Hebrew and Arabic, and English mixed into them
            Vertical // Japanese in columns from right to left, with vertical punctuation
        };

        /// @brief Puts a sample into the note, and shows its button as the one that's on.
        void showSample(const TextSample sample);

        /// @brief The button that puts the sample into the note, or nullptr when it couldn't be built.
        RetroFuturaGUI::Button* getSampleButton(const TextSample sample) const;

        /// @brief Returns a sample's text, in UTF-8.
        static std::string_view getSampleText(const TextSample sample);

        /// @brief Gives the note's text its colors in every state: opaque, see-through while the glass is on so the backdrop
        ///        shows in the glyphs, or clear while the metal image is on so it shows alone.
        void applyTextColors();

        /// @brief Shows whether an effect button's effect is on: an accent background while it is.
        static void styleEffectButton(RetroFuturaGUI::Button* button, const bool isOn);

        //What the effect buttons have set on the note's text, and which sample it shows
        RetroFuturaGUI::FillType _textFillType { RetroFuturaGUI::FillType::Solid };
        u32 _textEffects { NoTextEffects };
        TextSample _textSample { TextSample::Effects };
    };
}
