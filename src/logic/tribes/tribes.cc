/*
 * Copyright (C) 2006-2014 by the Widelands Development Team
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
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include "logic/tribes/tribes.h"

namespace Widelands {

Tribes::Tribes(EditorGameBase& egbase) :
	egbase_(egbase),
	buildings_(new DescriptionMaintainer<BuildingDescr>()),
	immovables_(new DescriptionMaintainer<ImmovableDescr>()),
	ships_(new DescriptionMaintainer<ShipDescr>()),
	wares_(new DescriptionMaintainer<WareDescr>()),
	workers_(new DescriptionMaintainer<WorkerDescr>()),
	tribes_(new DescriptionMaintainer<TribeDescr>()) {
}

void Tribes::add_constructionsite_type(const LuaTable& t) {
	buildings_->add(new ConstructionSiteDescr(t));
}

void Tribes::add_dismantlesite_type(const LuaTable& t) {
	buildings_->add(new DismantleSiteDescr(t));
}

void Tribes::add_militarysite_type(const LuaTable& t) {
	buildings_->add(new MilitarySiteDescr(t));
}

void Tribes::add_productionsite_type(const LuaTable& t) {
	buildings_->add(new ProductionSiteDescr(t, egbase_));
}

void Tribes::add_trainingsite_type(const LuaTable& t) {
	buildings_->add(new TrainingSiteDescr(t, egbase_));
}

void Tribes::add_warehouse_type(const LuaTable& t) {
	buildings_->add(new WarehouseDescr(t));
}

void Tribes::add_immovable_type(const LuaTable& t) {
	immovables_->add(new ImmovableDescr(t, egbase_.world(), MapObjectDescr::OwnerType::kTribe));
}

void Tribes::add_ship_type(const LuaTable& t) {
	ships_->add(new ShipDescr(t));
}

void Tribes::add_ware_type(const LuaTable& t) {
	wares_->add(new WareDescr(t));
}

void Tribes::add_carrier_type(const LuaTable& t) {
	CarrierDescr& worker_descr = new CarrierDescr(t);
	WareIndex const worker_idx = workers_->add(worker_descr);
	if (worker_descr.buildcost().empty()) {
		worker_types_without_cost_.push_back(worker_idx);
	}
}

void Tribes::add_soldier_type(const LuaTable& t) {
	SoldierDescr& worker_descr = new SoldierDescr(t);
	WareIndex const worker_idx = workers_->add(worker_descr);
	if (worker_descr.buildcost().empty()) {
		worker_types_without_cost_.push_back(worker_idx);
	}
}

void Tribes::add_worker_type(const LuaTable& t) {
	WorkerDescr& worker_descr = new WorkerDescr(t);
	WareIndex const worker_idx = workers_->add(worker_descr);
	if (worker_descr.buildcost().empty()) {
		worker_types_without_cost_.push_back(worker_idx);
	}
}

void Tribes::add_tribe(const LuaTable& t) {
	tribes_->add(new TribeDescr(t, egbase_));
}

WareIndex Tribes::nrwares() const {
	return wares_.size();
}

WareIndex Tribes::nrworkers() const {
	return workers_.size();
}


BuildingIndex Tribes::safe_building_index(const std::string& buildingname) const {
	const BuildingIndex result = building_index(buildingname);
	if (result == -1) {
		throw GameDataError("Unknown building type \"%s\"", buildingname.c_str());
	}
	return result;
}

int Tribes::safe_immovable_index(const std::string& immovablename) const {
	const int result = immovable_index(immovablename);
	if (result == -1) {
		throw GameDataError("Unknown immovable type \"%s\"", immovablename.c_str());
	}
	return result;
}

int safe_ship_index(const std::string& shipname) const {
	const int result = ship_index(shipname);
	if (result == -1) {
		throw GameDataError("Unknown ship type \"%s\"", shipname.c_str());
	}
	return result;
}

WareIndex Tribes::safe_ware_index(const std::string& warename) const {
	const WareIndex result = ware_index(warename);
	if (result == -1) {
		throw GameDataError("Unknown ware type \"%s\"", warename.c_str());
	}
	return result;
}

WareIndex Tribes::safe_worker_index(const std::string& workername) const {
	const WareIndex result = worker_index(workername);
	if (result == -1) {
		throw GameDataError("Unknown worker type \"%s\"", workername.c_str());
	}
	return result;
}

BuildingIndex Tribes::building_index(const std::string& buildingname) const {
	int result = -1;
	for (size_t i = 0; i < buildings_.size(); ++i) {
		if (buildings_.get(i)->name() == buildingname.name()) {
			return result;
		}
	}
}

int Tribes::immovable_index(const std::string& immovablename) const {
	return immovables_.get_index(immovablename);
}

int Tribes::ship_index(const std::string& shipname) const {
	return ships_.get_index(shipname);
}

WareIndex Tribes::ware_index(const std::string& warename) const {
	int result = -1;
	for (size_t i = 0; i < wares_.size(); ++i) {
		if (wares_.get(i)->name() == warename.name()) {
			return result;
		}
	}
}

WareIndex Tribes::worker_index(const std::string& workername) const {
	int result = -1;
	for (size_t i = 0; i < workers_.size(); ++i) {
		if (workers_.get(i)->name() == workername.name()) {
			return result;
		}
	}
}

BuildingDescr const * Tribes::get_building_descr(BuildingIndex building_index) const {
	return buildings_.get(building_index);
}

ImmovableDescr const * Tribes::get_immovable_descr(const std::string& immovablename) const {
	return immovables_.get(immovable_index(immovablename));
}

ShipDescr const * Tribes::get_ship_descr(const std::string& shipname) const {
	return ships_.get(ship_index(shipname));
}


WareDescr const * Tribes::get_ware_descr(WareIndex ware_index) const {
	return wares_.get(ware_index);
}

WorkerDescr const * Tribes::get_worker_descr(WareIndex worker_index) const {
	return workers_.get(worker_index);
}

void Tribes::set_ware_type_has_demand_check(WareIndex ware_index, const std::string& tribename) const {
	wares_.get(ware_index)->set_has_demand_check(tribename);
}

void Tribes::set_worker_type_has_demand_check(WareIndex worker_index, const std::string& tribename) const {
	workers_.get(worker_index)->set_has_demand_check(tribename);
}

const std::vector<WareIndex>& Tribes::worker_types_without_cost() const {
	return worker_types_without_cost_;
}

} // namespace Widelands
