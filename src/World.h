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
#include "Tile.h"
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
		explicit World(int tileSize);
		~World();

		/*
		 * The size of this world, in tiles
		 */
		void setSize(unsigned int width, unsigned int height);

		void setTileAt(unsigned int tileX, unsigned int tileY, Tile* tile);

		void setTile(Tile* tile);

		/*
		 * This will recreate the internal layers to fit the new size
		 */
		void setViewSize(unsigned int width, unsigned int height);

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
		void draw(sf::RenderTarget&, const sf::FloatRect&);

		int getHeight() const {
			return height;
		}
		
		int getWidth() const {
			return width;
		}

	private:
		World(World&);
		vector<Entity*> entities;
		vector<vector<Tile*> > tiles;

		sf::RenderTexture backgroundLayer;
		sf::RenderTexture foregroundLayer;

		int tileSize;
		int width;
		int height;
};

