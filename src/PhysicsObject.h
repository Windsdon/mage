/*
 * PhysicsObject.h
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

class PhysicsObject {
	public:
		virtual ~PhysicsObject() {};

		/*
		 * The collision box, in world coordinates
		 */
		virtual const sf::FloatRect &getCollisionBox() const = 0;
		virtual void moveDelta(float dx, float dy) = 0;
		virtual bool isFixed() const = 0;

		sf::Vector2f velocity;
		sf::Vector2f acceleration;
		sf::Vector2f direction;
		sf::Vector2f force;
		sf::Vector2f ds;
		float mass;
		float friction;

};

