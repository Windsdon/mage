/*
 * InvisibleWall.h
 *
 *  Created on: 19/01/2014
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

#include "PhysicsObject.h"

/*
 *
 */
class InvisibleWall: public PhysicsObject {
	public:
		InvisibleWall(float x, float y, float w, float h)
				: cb(x, y, w, h) {

		}

		virtual const sf::FloatRect &getCollisionBox() const {
			return cb;
		}

		virtual bool isFixed() const {
			return true;
		}

		virtual void moveDelta(float dx, float dy) {
			return;
		}

		virtual void draw(sf::RenderTarget&, sf::RenderStates) const {
			return;
		}

	private:
		sf::FloatRect cb;
};

