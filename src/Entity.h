/*
 * Entity.h
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

#include <SFML/Graphics/Drawable.hpp>

class World;
class Entity: public sf::Drawable {
	public:
		Entity(World*);
		virtual ~Entity();

		/*
		 * Called every world tick
		 */
		virtual void onUpdate(float) = 0;

		/*
		 * Notifies the World that this entity should not be updated anymore.
		 * Should always be called by derived classes.
		 */
		virtual void onDestory();

	private:
		World *world;

};

