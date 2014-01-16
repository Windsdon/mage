/*
 * Tile.h
 *
 *  Created on: 16/01/2014
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
#include <SFML/Graphics.hpp>
#include "PhysicsObject.h"
#include "TileSheet.h"

/*
 *
 */
class Tile: public sf::Drawable, public PhysicsObject {
	public:
		Tile(int width, int height, int x, int y, unsigned long data, TileSheet *sheet);

		/*
		 * Note: this will also set update to true if data is different
		 * from the the current value
		 */
		virtual void setData(unsigned long data);

		/*
		 * This will update the sprite for this tile and set updateScheduled to false.
		 * Returns true if adjacent tiles need to be updated.
		 */
		virtual bool update();

		virtual int getTileId() const = 0;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		unsigned long getData() const;
		bool isUpdateScheduled() const;
		void setUpdateScheduled(bool updateScheduled);

		virtual bool isAlwaysTop() const = 0;

		/*struct DataMask {
				unsigned offset :4;
				bool extendN :1;
				bool extendS :1;
				bool extendE :1;
				bool extendW :1;
				unsigned rotation :2;
		};

		union Data {
				DataMask mask;
				unsigned long data;
		};*/

		enum ExtendDirection {
				North,
				South,
				East,
				West
		};

		unsigned getOffset() const;
		bool getExtend(ExtendDirection dir) const;
		unsigned getRotation() const;
		unsigned long getExtra() const;

		int getTileX() const {
			return tileX;
		}

		int getTileY() const {
			return tileY;
		}

		virtual const sf::FloatRect &getCollisionBox() const {
			return cb;
		}

	private:
		/*
		 * data structure is as follows: (least significant bits first)
		 * - 4 bits for offset in the tile sheet (for random tiles, or special tiles)
		 * - 4 bits for extension (connected tiles):
		 * -- format: WESN
		 * - 2 bits for rotation
		 * the remaining bits can be used for special purposes
		 */
		unsigned long data;
		/*
		 * if this has an update scheduled
		 */
		bool updateScheduled;

		int width;
		int height;

		int tileX;
		int tileY;

		TileSheet *sheet;

		sf::Sprite sprite;

		sf::FloatRect cb;
};

