#pragma once
#include "Scene.hpp"
#include "Button.hpp"
#include "MultilineTextBox.hpp"
#include <memory>

namespace TestProject
{
    /// @brief The effects the effect buttons have switched on for the note's text, as bits of one mask.
    enum NoteTextEffects : u32
    {
        NoTextEffects = 0,
        TextRaster = 1,
        TextFog = 1 << 1,
        TextGlass = 1 << 2,
        TextMetal = 1 << 3
    };

    class NoteScene_p
    {
    public:
        std::unique_ptr<RetroFuturaGUI::Scene> _scene { nullptr };

        //Attached to the scene's root Lasagna, which only borrows them
        std::unique_ptr<RetroFuturaGUI::MultilineTextBox> _noteTextBox { nullptr };
        std::unique_ptr<RetroFuturaGUI::Button>
            _fillButton { nullptr },
            _rasterButton { nullptr },
            _fogButton { nullptr },
            _glassButton { nullptr },
            _metalButton { nullptr };

        //What the effect buttons have set on the note's text
        RetroFuturaGUI::FillType _textFillType { RetroFuturaGUI::FillType::Solid };
        u32 _textEffects { NoTextEffects };
    };
}
