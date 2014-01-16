/*
 * TileSheet.h
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

#include "Resource.h"
#include "ResourceImage.h"
#include <SFML/Graphics.hpp>

class TileSheet: public Resource {
	public:
		TileSheet(const string id, const string imageId, int tileSize);
		TileSheet(const string id, const string imageId);
		virtual ~TileSheet();

		virtual void load();
		virtual bool isLoaded() const;
		virtual Resource::Type getType() const;

		const sf::Texture *getTexture(int offset) const;
		int getSize() const;

		const sf::Texture *operator[](int offset) const;

		int getTileSize() const {
			return tileSize;
		}

	private:
		vector<sf::Texture*> textures;
		int tileSize;
		bool loaded;

};

