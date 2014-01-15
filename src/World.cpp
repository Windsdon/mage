/*
 * World.cpp
 *
 *  Created on: 14/01/2014
 *      Author: Windsdon
 *  
 *   mage
 *   Copyright (C) 2014 Windsdon
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License along
 *    with this program; if not, write to the Free Software Foundation, Inc.,
 *    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.  
 *
 */

#include "World.h"
#include "Logger.h"

World::World() {

}

void World::tick() {

}

bool World::hasEntity(Entity* e, vector<Entity*>::iterator *p = NULL) {
	for (vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it) {
		if ((*it) == e) {
			if (p) {
				*p = it;
			}
			return true;
		}
	}

	return false;
}

void World::addEntity(Entity* e) {
	if (!hasEntity(e)) {
		entities.push_back(e);
	} else {
		LogEntry entry(Logger::Severity::WARNING, "Tried to added entity already in list");
		Logger::getInstance().log(entry);
	}
}

void World::removeEntity(Entity* e) {
	vector<Entity*>::iterator p;
	if (hasEntity(e, &p)) {
		entities.erase(p);
	} else {
		LogEntry entry(Logger::Severity::WARNING, "Tried to remove entity that is not from this world");
		Logger::getInstance().log(entry);
	}
}

void World::draw(sf::RenderTarget& target, sf::View& view) const {
	for (vector<Entity*>::const_iterator it = entities.begin(); it != entities.end(); ++it) {
		target.draw(**it);
	}
}

World::~World() {

}
