/*
 * Copyright (C) 2015-2023 by the Widelands Development Team
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <https://www.gnu.org/licenses/>.
 *
 */

#ifndef WL_EDITOR_UI_MENUS_HELP_H
#define WL_EDITOR_UI_MENUS_HELP_H

#include "scripting/lua_interface.h"
#include "ui_basic/unique_window.h"
#include "wui/encyclopedia_window.h"

class EditorInteractive;

struct EditorHelp : public UI::EncyclopediaWindow {
	EditorHelp(EditorInteractive&, UI::UniqueWindow::Registry&, LuaInterface* lua);
};

#endif  // end of include guard: WL_EDITOR_UI_MENUS_HELP_H
