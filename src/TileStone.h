/*
 * TileStone.h
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

#include "Tile.h"

/*
 *
 */
class TileStone: public Tile {
	public:
		TileStone(int width, int height, int x, int y, unsigned long data, TileSheet *sheet)
				: Tile(width, height, x, y, data, sheet) {
		}

		virtual bool isAlwaysTop() const {
			return false;
		}

		virtual int getTileId() const {
			return 1;
		}
};

