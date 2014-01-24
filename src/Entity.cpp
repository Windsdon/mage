/*
 * Entity.cpp
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
#include "Entity.h"
#include "World.h"
#include "Physics.h"

Entity::~Entity() {
}

const sf::FloatRect& Entity::getCollisionBox() const {
	return cb;
}

void Entity::moveDelta(float dx, float dy) {
	cb.left += dx;
	cb.top += dy;
}

bool Entity::isFixed() const {
	return false;
}

void Entity::onDestory() {
	world->removeEntity(this);
}

Entity::Entity(World* world, float x, float y, float width, float height): world(world), cb(x - width/2, y - height/2, width, height) {
}

sf::Vector2f Entity::getVisualCentre() {
	return Physics::getCentre(getCollisionBox());
}
