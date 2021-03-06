/*
 * Mob.cpp
 *
 *  Created on: 17/01/2014
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

#include "Mob.h"
#include <iostream>

Mob::Mob(World* world, float x, float y, float width, float height, TileSheet* sheet)
		: Entity(world, x, y, width, height), frame(0), sheet(sheet) {

	sprite.setTexture(*(sheet->getTexture(frame)), true);

	sprite.setScale(((float) width) / sheet->getTileSize(), ((float) height) / sheet->getTileSize());
	sprite.setOrigin(sheet->getTileSize() / 2.0, sheet->getTileSize() / 2.0);
	sprite.setPosition(x, y);
}

void Mob::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite, states);
}

void Mob::moveDelta(float dx, float dy) {
	Entity::moveDelta(dx, dy);
	sprite.move(dx, dy);
}

void Mob::onUpdate(float dt) {
}
