// Copyright 2021 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
#include <memory>   // for allocator, __shared_ptr_access
#include <string>   // for string, basic_string, operator+, to_string
#include <vector>   // for vector

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"       // for Button, Checkbox, Horizontal, Renderer, Vertical, Input, Menu, Radiobox
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/component/theme.hpp"  // for theme::Dflat20Button, theme::Dflat20Checkbox, etc.
#include "ftxui/dom/elements.hpp"  // for separator, gauge, text, Element, operator|, vbox, border, hbox, filler

/// @example ./examples/component/dflat20_theme.cpp
/// Demonstration of the D-Flat v20 DOS-era theme for FTXUI components.
/// This example shows how to use the theme::Dflat20* functions to create
/// components with a classic DOS look and feel, including:
/// - Buttons with BLACK on CYAN styling
/// - Menus with LIGHTGRAY on BLACK selection
/// - Checkboxes and Radioboxes with [X]/[ ] and (*)/( ) markers
/// - Input fields with bordered frames
/// - Window-like containers with title bars
///
/// All components support focused, active, and normal states with
/// high-contrast DOS color schemes and box-drawing borders.

using namespace ftxui;

int main() {
  auto screen = ScreenInteractive::TerminalOutput();

  // Button state
  int button_clicked_count = 0;
  std::string button_status = "Not clicked yet";

  // Menu state
  std::vector<std::string> menu_entries = {
      "File",
      "Edit",
      "View",
      "Tools",
      "Help",
  };
  int menu_selected = 0;

  // Checkbox states
  bool checkbox1 = false;
  bool checkbox2 = true;
  bool checkbox3 = false;

  // Radiobox states
  std::vector<std::string> radiobox_entries = {
      "Option A",
      "Option B",
      "Option C",
  };
  int radiobox_selected = 0;

  // Input field state
  std::string input_content = "";

  // Progress gauge value
  int progress = 30;

  // Create themed components
  auto button = Button(
      "OK",
      [&] {
        button_clicked_count++;
        button_status = "Clicked " + std::to_string(button_clicked_count) +
                        " time" + (button_clicked_count > 1 ? "s" : "");
      },
      theme::Dflat20Button());

  auto cancel_button = Button(
      "Cancel", [&] { screen.ExitLoopClosure()(); }, theme::Dflat20Button());

  auto menu = Menu(&menu_entries, &menu_selected, theme::Dflat20Menu());

  auto checkbox1_component =
      Checkbox("Enable feature A", &checkbox1, theme::Dflat20Checkbox());
  auto checkbox2_component =
      Checkbox("Enable feature B", &checkbox2, theme::Dflat20Checkbox());
  auto checkbox3_component =
      Checkbox("Enable feature C", &checkbox3, theme::Dflat20Checkbox());

  auto radiobox =
      Radiobox(&radiobox_entries, &radiobox_selected, theme::Dflat20Radiobox());

  auto input_component = Input(&input_content, "Enter text...", theme::Dflat20Input());

  // Less/More buttons for progress
  auto less_button = Button(
      "Less", [&] { progress = std::max(0, progress - 10); },
      theme::Dflat20Button());
  auto more_button = Button(
      "More", [&] { progress = std::min(100, progress + 10); },
      theme::Dflat20Button());

  // Layout components in containers
  auto button_container = Container::Horizontal({button, cancel_button});
  auto checkbox_container = Container::Vertical(
      {checkbox1_component, checkbox2_component, checkbox3_component});
  auto progress_buttons = Container::Horizontal({less_button, more_button});

  auto main_container = Container::Vertical({
      menu,
      button_container,
      checkbox_container,
      radiobox,
      input_component,
      progress_buttons,
  });

  // Create the main renderer with D-Flat v20 styled layout
  auto renderer = Renderer(main_container, [&] {
    // Create individual component renderings
    auto menu_box = vbox({
        text("Menu:") | bold,
        separator(),
        menu->Render(),
    }) | theme::Dflat20Window("Main Menu", false);

    auto button_box = vbox({
        text("Buttons:") | bold,
        separator(),
        hbox({
            button->Render(),
            text("  "),
            cancel_button->Render(),
        }),
        text(""),
        text("Status: " + button_status),
    }) | theme::Dflat20Window("Button Demo", false);

    auto checkbox_box = vbox({
        text("Checkboxes:") | bold,
        separator(),
        checkbox_container->Render(),
    }) | theme::Dflat20Window("Options", false);

    auto radiobox_box = vbox({
        text("Radio Buttons:") | bold,
        separator(),
        radiobox->Render(),
    }) | theme::Dflat20Window("Select One", false);

    auto input_box = vbox({
        text("Input Field:") | bold,
        separator(),
        input_component->Render(),
        text(""),
        text("Current: " + (input_content.empty() ? "(empty)" : input_content)),
    }) | theme::Dflat20Window("Text Input", false);

    auto progress_box = vbox({
        text("Progress:") | bold,
        separator(),
        hbox({
            text("Value: "),
            text(std::to_string(progress) + "%"),
        }),
        gauge(progress / 100.0f),
        text(""),
        hbox({
            less_button->Render(),
            text("  "),
            more_button->Render(),
        }),
    }) | theme::Dflat20Window("Progress Bar", false);

    // Main application layout with title
    return vbox({
        text("╔═══════════════════════════════════════════════════════════╗") | color(Color::GrayLight) | bgcolor(Color::Blue),
        text("║  FTXUI - D-Flat v20 Theme Demonstration                  ║") | color(Color::GrayLight) | bgcolor(Color::Blue) | bold,
        text("╚═══════════════════════════════════════════════════════════╝") | color(Color::GrayLight) | bgcolor(Color::Blue),
        text(""),
        hbox({
            vbox({
                menu_box,
                text(""),
                button_box,
                text(""),
                checkbox_box,
            }),
            text("  "),
            vbox({
                radiobox_box,
                text(""),
                input_box,
                text(""),
                progress_box,
            }),
        }),
        text(""),
        text("Press Tab to switch focus, Enter to activate, Esc to quit") | dim,
    }) | color(Color::GrayLight) | bgcolor(Color::Blue);
  });

  screen.Loop(renderer);
  return 0;
}
