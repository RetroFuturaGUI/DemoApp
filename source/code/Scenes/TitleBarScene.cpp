#include "TitleBarScene.hpp"

void TestProject::TitleBarScene::ShowTitle(std::string title)
{
    if(!_title)
        return;

    _title->GetText().SetString(title, false);
}