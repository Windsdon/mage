/*
 * Mob.h
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

#pragma once

#include "Entity.h"
#include "TileSheet.h"
#include "World.h"
#include <SFML/Graphics.hpp>

/*
 *
 */
class Mob: public Entity {
	public:
		Mob(World *world, float x, float y, float width, float height, TileSheet *sheet);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void moveDelta(float dx, float dy);

		virtual void onUpdate(float dt);

	private:
		unsigned int frame;
		sf::Sprite sprite;
		TileSheet *sheet;
};
