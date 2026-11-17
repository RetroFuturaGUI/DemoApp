#pragma once
#include "ColorfulPopScene_p.hpp"
#include "IncludeHelper.hpp"
#include <array>
#include <chrono>

namespace DemoApp
{
    /// @brief The ColorfulPop scene
    class ColorfulPopScene final : public ColorfulPopScene_p
    {
    public:
        explicit ColorfulPopScene(RetroFuturaGUI::Window* parentWindow) : ColorfulPopScene_p(parentWindow) {}

    privateSlots:
        void ShowText() override;
        void ShowBars() override;
        void ShowColor() override;
        void MoveBars() override;
        void PaintHair() override;
        void LoadMainScene() override;

    private:
        /// @brief What the area shows
        enum class View : u32
        {
            Text,
            Bars,
            Color
        };

        /// @brief Shows one of the area's views and hides the others
        void showView(const View view);

        std::array<f32, 16> _barValues {};
        std::chrono::steady_clock::time_point _start { std::chrono::steady_clock::now() };
    };
}