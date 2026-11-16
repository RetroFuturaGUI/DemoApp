#pragma once
#include "MainWindow_p.hpp"

namespace TestProject
{
    class MainWindow final : public MainWindow_p
    {
    public:
        /// @brief Gives FontManager the scripts the Note scene's samples show. They belong in App Settings once Roux generates them
        MainWindow();

    privateSlots:
    };
}