#pragma once
#include "Y2KFuturismScene_p.hpp"
#include "IncludeHelper.hpp"
#include <array>
#include <string_view>

namespace DemoApp
{
    /// @brief The Y2KFuturism scene
    class Y2KFuturismScene final : public Y2KFuturismScene_p
    {
    public:
        explicit Y2KFuturismScene(RetroFuturaGUI::Window* parentWindow) : Y2KFuturismScene_p(parentWindow) {}

    privateSlots:
        void SetUpWidgets() override;
        void LoadMainScene() override;

    private:
        /// @brief Adds the finishes to choose from
        void addFinishes();

        /// @brief Lays the mode group out in two rows, with a labeled radio button in each
        void addModes();

        /// @brief Adds a radio button named and labeled after the mode to the given row of the mode group; the first row's starts out chosen
        void addMode(std::string_view mode, const i64 row);

        /// @brief Sizes a mode's radio button and gives it a round metal rim around a cyan dot
        static void styleModeButton(RetroFuturaGUI::RadioButton& radioButton);

        /// @brief Sizes a mode's label and sets its font and colors
        static void styleModeLabel(RetroFuturaGUI::Label& label);

        /// @brief Shows the sample values in the line diagram and the histogram
        void showSamples();

        //The diagrams read these every frame without copying them, so they have to outlive the scene
        static constexpr std::array<f32, 12> _speedSamples { 0.2f, 0.35f, 0.3f, 0.55f, 0.5f, 0.7f, 0.65f, 0.85f, 0.8f, 0.9f, 0.75f, 0.95f };
        static constexpr std::array<f32, 10> _boostSamples { 0.4f, 0.65f, 0.9f, 0.55f, 0.75f, 1.0f, 0.6f, 0.8f, 0.45f, 0.7f };
    };
}