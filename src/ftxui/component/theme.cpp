// Copyright 2021 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
#include "ftxui/component/theme.hpp"

#include <string>  // for string

#include "ftxui/dom/elements.hpp"  // for text, border, borderDouble, hbox, window, Element
#include "ftxui/screen/color.hpp"  // for Color

namespace ftxui {
namespace theme {

/// @brief Create a ButtonOption with D-Flat v20 styling.
/// Mimics DOS button style: BLACK on CYAN, single border, inverted when focused
ButtonOption Dflat20Button() {
  ButtonOption option;
  option.transform = [](const EntryState& s) {
    // D-Flat buttons: BLACK text on CYAN background
    auto element = text(s.label) | color(Color::Black) | bgcolor(Color::Cyan);

    // Add single line border
    element |= borderLight;

    // Focused state: inverted colors (similar to WHITE on CYAN effect)
    if (s.focused) {
      element |= inverted;
    }

    // Active/pressed state: bold text
    if (s.active) {
      element |= bold;
    }

    return element;
  };
  return option;
}

/// @brief Create a MenuOption with D-Flat v20 styling.
/// Mimics DOS menu style with high-contrast selection
MenuOption Dflat20Menu() {
  auto option = MenuOption::Vertical();

  option.entries_option.transform = [](const EntryState& state) {
    Element e = text(state.label);

    // Normal state: BLACK text on LIGHTGRAY background
    e |= color(Color::Black);
    e |= bgcolor(Color::GrayLight);

    // Selected/Active state: LIGHTGRAY text on BLACK background
    if (state.active) {
      e = text(state.label);  // Reset to avoid double application
      e |= color(Color::GrayLight);
      e |= bgcolor(Color::Black);
      e |= bold;
    }

    // Focused state: add extra emphasis
    if (state.focused && !state.active) {
      e |= bold;
    }

    return e;
  };

  return option;
}

/// @brief Create a CheckboxOption with D-Flat v20 styling.
/// Uses [X] / [ ] markers with DOS color scheme
CheckboxOption Dflat20Checkbox() {
  auto option = CheckboxOption();
  option.transform = [](const EntryState& s) {
    // D-Flat checkbox markers: [X] or [ ]
    auto prefix = text(s.state ? "[X] " : "[ ] ");
    auto label = text(s.label);

    // Normal state: LIGHTGRAY text on BLUE background
    auto element = hbox({prefix, label});
    element |= color(Color::GrayLight);
    element |= bgcolor(Color::Blue);

    // Focused state: inverted to BLACK on LIGHTGRAY
    if (s.focused) {
      element = hbox({prefix, label});  // Reset
      element |= color(Color::Black);
      element |= bgcolor(Color::GrayLight);
      element |= bold;
    }

    // Active state: bold
    if (s.active && !s.focused) {
      element |= bold;
    }

    return element;
  };
  return option;
}

/// @brief Create a RadioboxOption with D-Flat v20 styling.
/// Uses (*) / ( ) markers with DOS color scheme
RadioboxOption Dflat20Radiobox() {
  auto option = RadioboxOption();
  option.transform = [](const EntryState& s) {
    // D-Flat radiobox markers: (*) or ( )
    auto prefix = text(s.state ? "(*) " : "( ) ");
    auto label = text(s.label);

    // Normal state: LIGHTGRAY text on BLUE background
    auto element = hbox({prefix, label});
    element |= color(Color::GrayLight);
    element |= bgcolor(Color::Blue);

    // Focused state: inverted to BLACK on LIGHTGRAY
    if (s.focused) {
      element = hbox({prefix, label});  // Reset
      element |= color(Color::Black);
      element |= bgcolor(Color::GrayLight);
      element |= bold;
    }

    // Active state: bold
    if (s.active && !s.focused) {
      element |= bold;
    }

    return element;
  };
  return option;
}

/// @brief Create an InputOption with D-Flat v20 styling.
/// Mimics DOS text input fields with frame and high-contrast focus
InputOption Dflat20Input() {
  InputOption option;
  option.transform = [](InputState state) {
    // Add light border frame for D-Flat look
    state.element |= borderLight;

    // Normal state: BLACK text on LIGHTGRAY background
    state.element |= color(Color::Black);
    state.element |= bgcolor(Color::GrayLight);

    // Placeholder text: dimmed
    if (state.is_placeholder) {
      state.element |= dim;
    }

    // Focused state: inverted to simulate WHITE on CYAN
    // (Since inverted swaps fg/bg, we get LIGHTGRAY on BLACK,
    // but we override with specific colors for better effect)
    if (state.focused) {
      // Apply focus colors directly
      state.element |= color(Color::White);
      state.element |= bgcolor(Color::Cyan);
      state.element |= bold;
    }

    return state.element;
  };
  return option;
}

/// @brief Create a decorator for window-like containers with D-Flat v20
/// styling.
/// @param title The window title to display
/// @param focused Whether the window is focused (uses double border if true)
Decorator Dflat20Window(const std::string& title, bool focused) {
  return [title, focused](Element element) {
    // D-Flat windows use double-line borders when focused, single-line
    // otherwise
    auto title_element =
        text(title) | color(Color::Black) | bgcolor(Color::Cyan);

    Element result;
    if (focused) {
      // Focused window: double-line border with title
      result = window(title_element, element, BorderStyle::DOUBLE);
      result |= color(Color::GrayLight);
      result |= bgcolor(Color::Blue);
    } else {
      // Normal window: single-line border with title
      result = window(title_element, element, BorderStyle::LIGHT);
      result |= color(Color::GrayLight);
      result |= bgcolor(Color::Blue);
    }

    return result;
  };
}

}  // namespace theme
}  // namespace ftxui
