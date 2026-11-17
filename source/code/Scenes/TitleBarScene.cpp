#include "TitleBarScene.hpp"

void DemoApp::TitleBarScene::ShowTitle(std::string title)
{
    if(!_title)
        return;

    _title->GetText().SetString(title, false);
}