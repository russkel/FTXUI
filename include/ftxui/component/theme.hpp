// Copyright 2021 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
#ifndef FTXUI_COMPONENT_THEME_HPP
#define FTXUI_COMPONENT_THEME_HPP

#include "ftxui/component/component_options.hpp"  // for ButtonOption, MenuOption, etc.

namespace ftxui {
namespace theme {

/// @brief DOS-era D-Flat v20 inspired theme factory functions.
/// @ingroup component
///
/// These functions return pre-configured component options that mimic the
/// look and feel of the D-Flat v20 DOS library, featuring:
/// - DOS box-drawing borders (single line normal, double line focused)
/// - Classic DOS color palette (LIGHTGRAY, BLUE, CYAN, BLACK, etc.)
/// - High-contrast focused/active states
///
/// Usage example:
/// @code
///   auto button = Button("OK", callback, theme::Dflat20Button());
///   auto menu = Menu(&entries, &selected, theme::Dflat20Menu());
/// @endcode

/// @brief Create a ButtonOption with D-Flat v20 styling.
/// - Normal: BLACK text on CYAN background with single border
/// - Focused: WHITE text (inverted)
/// - Active: Bold text
ButtonOption Dflat20Button();

/// @brief Create a MenuOption with D-Flat v20 styling.
/// - Normal: BLACK text on LIGHTGRAY background
/// - Selection: LIGHTGRAY text on BLACK background (inverted)
/// - Focused: Bold text
MenuOption Dflat20Menu();

/// @brief Create a CheckboxOption with D-Flat v20 styling.
/// - Uses [X] / [ ] checkbox markers
/// - Normal: LIGHTGRAY text on BLUE background
/// - Focused: Inverted colors (BLACK on LIGHTGRAY)
CheckboxOption Dflat20Checkbox();

/// @brief Create a RadioboxOption with D-Flat v20 styling.
/// - Uses (*) / ( ) radio button markers
/// - Normal: LIGHTGRAY text on BLUE background
/// - Focused: Inverted colors (BLACK on LIGHTGRAY)
RadioboxOption Dflat20Radiobox();

/// @brief Create an InputOption with D-Flat v20 styling.
/// - Normal: BLACK text on LIGHTGRAY background with frame
/// - Focused: WHITE text on CYAN background
InputOption Dflat20Input();

/// @brief Create a decorator for window-like containers with D-Flat v20
/// styling.
/// @param title The window title to display in the top border
/// @param focused Whether the window is focused (uses double border if true)
/// @return A decorator that applies D-Flat v20 window styling
Decorator Dflat20Window(const std::string& title, bool focused = false);

}  // namespace theme
}  // namespace ftxui

#endif  // FTXUI_COMPONENT_THEME_HPP
