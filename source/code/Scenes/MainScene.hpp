#pragma once
#include "MainScene_p.hpp"

namespace DemoApp
{
    class MainScene final : public MainScene_p
    {
    public:
        explicit MainScene(RetroFuturaGUI::Window* parentWindow) : MainScene_p(parentWindow) {}

    privateSlots:
        void LoadY2KFuturismScene() override;
        void LoadColorfulPopScene() override;
        void LoadNoteScene() override;
    };
}