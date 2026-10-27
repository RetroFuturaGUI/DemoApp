#pragma once
#include "ISceneHost.hpp"
#include <memory>
#define privateSlots private

namespace RetroFuturaGUI { class Window; class Button; }

namespace TestProject
{
    class NoteScene_p;

    /// @brief A scene with one multiline text box filling the window, to type into while the window sits in a tab. A row of
    ///        buttons above it switches the text's fill, raster, fog, glass and a metal image, to test the text effects.
    class NoteScene final : public RetroFuturaGUI::ISceneHost
    {
    public:
        explicit NoteScene(RetroFuturaGUI::Window* parentWindow);
        NoteScene() = delete;
        NoteScene(const NoteScene&) = delete;
        NoteScene(NoteScene&&) = delete;
        auto operator =(const NoteScene&) = delete;
        auto operator =(NoteScene&&) = delete;
        //Out of line: NoteScene_p is incomplete here
        ~NoteScene() override;

        RetroFuturaGUI::Scene* GetScene() const override;

    privateSlots:
        void on_fillButton_click();
        void on_rasterButton_click();
        void on_fogButton_click();
        void on_glassButton_click();
        void on_metalButton_click();

    private:
        std::unique_ptr<NoteScene_p> _members;
        void setup(RetroFuturaGUI::Window* parentWindow);

        /// @brief Gives the note's text its colors in every state: opaque, see-through while the glass is on so the backdrop
        ///        shows in the glyphs, or clear while the metal image is on so it shows alone.
        void applyTextColors();

        /// @brief Shows whether an effect button's effect is on: an accent background while it is.
        static void styleEffectButton(RetroFuturaGUI::Button* button, const bool isOn);
    };
}
