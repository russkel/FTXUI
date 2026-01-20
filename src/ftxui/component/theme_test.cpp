// Copyright 2021 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
#include <gtest/gtest.h>
#include <string>  // for string

#include "ftxui/component/component.hpp"       // for Button, Checkbox, etc.
#include "ftxui/component/component_options.hpp"  // for ButtonOption, etc.
#include "ftxui/component/theme.hpp"           // for theme::Dflat20*

namespace ftxui {

TEST(ThemeTest, Dflat20ButtonHasTransform) {
  auto option = theme::Dflat20Button();
  EXPECT_TRUE(option.transform != nullptr);
}

TEST(ThemeTest, Dflat20MenuHasTransform) {
  auto option = theme::Dflat20Menu();
  EXPECT_TRUE(option.entries_option.transform != nullptr);
}

TEST(ThemeTest, Dflat20CheckboxHasTransform) {
  auto option = theme::Dflat20Checkbox();
  EXPECT_TRUE(option.transform != nullptr);
}

TEST(ThemeTest, Dflat20RadioboxHasTransform) {
  auto option = theme::Dflat20Radiobox();
  EXPECT_TRUE(option.transform != nullptr);
}

TEST(ThemeTest, Dflat20InputHasTransform) {
  auto option = theme::Dflat20Input();
  EXPECT_TRUE(option.transform != nullptr);
}

TEST(ThemeTest, Dflat20ButtonCanBeUsed) {
  int clicked = 0;
  auto button = Button("Test", [&] { clicked++; }, theme::Dflat20Button());
  EXPECT_TRUE(button != nullptr);
}

TEST(ThemeTest, Dflat20CheckboxCanBeUsed) {
  bool checked = false;
  auto checkbox = Checkbox("Test", &checked, theme::Dflat20Checkbox());
  EXPECT_TRUE(checkbox != nullptr);
}

TEST(ThemeTest, Dflat20MenuCanBeUsed) {
  std::vector<std::string> entries = {"Item 1", "Item 2", "Item 3"};
  int selected = 0;
  auto menu = Menu(&entries, &selected, theme::Dflat20Menu());
  EXPECT_TRUE(menu != nullptr);
}

TEST(ThemeTest, Dflat20RadioboxCanBeUsed) {
  std::vector<std::string> entries = {"Option A", "Option B"};
  int selected = 0;
  auto radiobox = Radiobox(&entries, &selected, theme::Dflat20Radiobox());
  EXPECT_TRUE(radiobox != nullptr);
}

TEST(ThemeTest, Dflat20InputCanBeUsed) {
  std::string content;
  auto input = Input(&content, "Placeholder", theme::Dflat20Input());
  EXPECT_TRUE(input != nullptr);
}

TEST(ThemeTest, Dflat20WindowCanBeUsed) {
  auto decorator = theme::Dflat20Window("Test Window", false);
  auto element = text("Content");
  auto decorated = decorator(element);
  EXPECT_TRUE(decorated != nullptr);
}

TEST(ThemeTest, Dflat20WindowFocusedCanBeUsed) {
  auto decorator = theme::Dflat20Window("Focused Window", true);
  auto element = text("Content");
  auto decorated = decorator(element);
  EXPECT_TRUE(decorated != nullptr);
}

}  // namespace ftxui
