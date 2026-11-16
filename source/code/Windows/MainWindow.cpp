#include "MainWindow.hpp"
#include "FontManager.hpp"
#include "UnicodeBlocks.hpp"
#include <array>

TestProject::MainWindow::MainWindow()
{
    //The scripts the test app shows. A block comes into a font and size the first time a text there needs it.
    RetroFuturaGUI::FontManager::AddCharset("Latin", std::array { Latin1SupplementFirst });
    RetroFuturaGUI::FontManager::AddCharset("Japanese", std::array { CJKRadicalsSupplementFirst, HiraganaFirst, KatakanaFirst, CJKSymbolsandPunctuationFirst, CJKUnifiedIdeographsFirst, HalfwidthandFullwidthFormsFirst }); //⻱, 、。「」 and 々, the kanji, ！？：（） and full-width letters
    RetroFuturaGUI::FontManager::AddCharset("Thai", std::array { ThaiFirst });
    RetroFuturaGUI::FontManager::AddCharset("Emoji", std::array { MiscellaneousSymbolsFirst, EnclosedAlphanumericSupplementFirst, DingbatsFirst, EmoticonsFirst, MiscellaneousSymbolsAndPictographsFirst, TransportAndMapSymbolsFirst, SupplementalSymbolsandPictographsFirst, SymbolsandPictographsExtendedAFirst }); //☕ ❤ 🇫🇮 😀 🚀

#if defined(TARGET_PLATFORM_LINUX)
    RetroFuturaGUI::FontManager::SetCharsetFont("Japanese", "Noto Sans CJK JP");
    RetroFuturaGUI::FontManager::SetCharsetFont("Thai", "Noto Sans Thai");
    RetroFuturaGUI::FontManager::SetCharsetFont("Emoji", "Noto Color Emoji"); //no common Linux font has 𰻝 (Extension G), so it gets no character set here
#elif defined(TARGET_PLATFORM_WINDOWS)
    RetroFuturaGUI::FontManager::AddCharset("ChineseExtensionG", std::array { CJKUnifiedIdeographsExtensionGFirst }); //𰻝
    RetroFuturaGUI::FontManager::SetCharsetFont("Japanese", "Noto Serif JP"); //rather than Yu Mincho, as it also has Chinese forms like 龟 and radicals like ⻱
    RetroFuturaGUI::FontManager::SetCharsetFont("ChineseExtensionG", "SimSun-ExtG");
    RetroFuturaGUI::FontManager::SetCharsetFont("Thai", "Leelawadee UI"); //which Windows ships
    RetroFuturaGUI::FontManager::SetCharsetFont("Emoji", "Segoe UI Emoji");
#endif
}