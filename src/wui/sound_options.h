/*
 * Copyright (C) 2019-2023 by the Widelands Development Team
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
 */

#ifndef WL_WUI_SOUND_OPTIONS_H
#define WL_WUI_SOUND_OPTIONS_H

#include "graphic/styles/text_panel_style.h"
#include "ui_basic/box.h"
#include "ui_basic/checkbox.h"

/**
 * A box with all sound options.
 * All changes to the sound settings take effect immediately, but are not saved to config.
 */
struct SoundOptions : public UI::Box {
	SoundOptions(UI::Panel& parent, UI::SliderStyle style);

private:
	UI::Checkbox custom_songset_;
};

#endif  // end of include guard: WL_WUI_SOUND_OPTIONS_H
