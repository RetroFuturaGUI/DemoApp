#pragma once
#include "TitleBarScene_p.hpp"
#include <string>

namespace DemoApp
{
    class TitleBarScene final : public TitleBarScene_p
    {
    public:
        explicit TitleBarScene(RetroFuturaGUI::Window* parentWindow) : TitleBarScene_p(parentWindow) {}

    privateSlots:
        void ShowTitle(std::string title) override;
    };
}