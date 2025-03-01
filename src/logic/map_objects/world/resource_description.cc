/*
 * Copyright (C) 2006-2023 by the Widelands Development Team
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

#include "logic/map_objects/world/resource_description.h"

#include <memory>

#include "logic/game_data_error.h"
#include "scripting/lua_table.h"

namespace Widelands {

ResourceDescription::ResourceDescription(const LuaTable& table)
   : name_(table.get_string("name")),
     descname_(table.get_string("descname")),
     detectable_(table.get_bool("detectable")),
     timeout_ms_(table.get_int("timeout_ms")),
     timeout_radius_(table.get_int("timeout_radius")),
     max_amount_(table.get_int("max_amount")),
     representative_image_(table.get_string("representative_image")) {

	std::unique_ptr<LuaTable> st = table.get_table("editor_pictures");
	const std::set<int> keys = st->keys<int>();
	for (int upper_limit : keys) {
		editor_pictures_.emplace_back(st->get_string(upper_limit), upper_limit);
	}
	if (editor_pictures_.empty()) {
		throw GameDataError("Resource %s has no editor_pictures.", name_.c_str());
	}
}

const std::string& ResourceDescription::editor_image(uint32_t const amount) const {
	if (amount > editor_pictures_.back().second) {
		throw wexception("Resource %s has no image for amount %u (highest amount is %u)",
		                 name().c_str(), amount, editor_pictures_.back().second);
	}

	const std::string* result = nullptr;
	for (const auto& pair : editor_pictures_) {
		result = &pair.first;
		if (pair.second >= amount) {
			break;
		}
	}

	assert(result != nullptr);
	return *result;
}

const std::string& ResourceDescription::name() const {
	return name_;
}

const std::string& ResourceDescription::descname() const {
	return descname_;
}

bool ResourceDescription::detectable() const {
	return detectable_;
}

uint32_t ResourceDescription::timeout_ms() const {
	return timeout_ms_;
}

uint32_t ResourceDescription::timeout_radius() const {
	return timeout_radius_;
}

ResourceAmount ResourceDescription::max_amount() const {
	return max_amount_;
}

}  // namespace Widelands
