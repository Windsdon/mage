/*
 * World.h
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

#pragma once

#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

/*
 * World holds all entities and information about the tiles.
 * Has it's own internal clock to correctly update entities.
 */
class World {
	public:
		/*
		 * Creates a blank world, with neither tiles nor entities
		 */
		World();
		~World();

		/*
		 * Updates every entity and tiles
		 */
		void tick();

		/*
		 * Adds an entity to the list
		 */
		void addEntity(Entity*);

		void removeEntity(Entity*);

		bool hasEntity(Entity*, vector<Entity*>::iterator*);

		/*
		 * Draws visible entities and tiles
		 */
		void draw(sf::RenderTarget&, sf::View&) const;

	private:
		World(World&);
		vector<Entity*> entities;
};

