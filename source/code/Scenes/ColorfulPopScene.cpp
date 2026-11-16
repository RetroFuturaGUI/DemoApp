#include "ColorfulPopScene.hpp"
#include <cmath>
#include <span>

void TestProject::ColorfulPopScene::ShowText()
{
    showView(View::Text);
}

void TestProject::ColorfulPopScene::ShowBars()
{
    if(!_bars)
        return;

    _bars->SetMinValue(0.0f);
    _bars->SetMaxValue(1.0f);
    showView(View::Bars);
}

void TestProject::ColorfulPopScene::ShowColor()
{
    showView(View::Color);
}

void TestProject::ColorfulPopScene::MoveBars()
{
    if(!_rootLasagna)
        return;

    if(!_bars)
        return;

    if(!_rootLasagna->IsWidgetShown("Bars"))
        return;

    //Each bar bounces at its own pace, between a tenth of the height and the top
    const f32 seconds { std::chrono::duration<f32>(std::chrono::steady_clock::now() - _start).count() };

    for(uSize index { 0 }; _barValues.size() > index; ++index)
    {
        const f32 bar { static_cast<f32>(index) };
        _barValues[index] = 0.55f + 0.45f * std::sin(seconds * (1.6f + 0.23f * bar) + bar);
    }

    _bars->SetData(std::span<const f32>(_barValues), false);
}

void TestProject::ColorfulPopScene::PaintHair()
{
    if(!_picker)
        return;

    if(!_lawnmeower)
        return;

    _lawnmeower->SetPathFill("ColorTailAndHair", RetroFuturaGUI::SvgPathFill
    {
        ._FillType = RetroFuturaGUI::FillType::Solid,
        ._Colors = { _picker->GetColorRGBAF() },
        ._GradientDegree = 0.0f,
        ._GradientOffset = 0.0f,
        ._GradientAnimationSpeed = 0.0f,
        ._GradientRotationSpeed = 0.0f
    });
}

void TestProject::ColorfulPopScene::LoadMainScene()
{
    loadScene("MainScene");
}

void TestProject::ColorfulPopScene::showView(const View view)
{
    if(!_rootLasagna)
        return;

    _rootLasagna->ShowWidget("TextPanel", View::Text == view);
    _rootLasagna->ShowWidget("Bars", View::Bars == view);
    _rootLasagna->ShowWidget("Picker", View::Color == view);
}