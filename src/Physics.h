/*
 * Physics.h
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
#include "PhysicsObject.h"
#include <vector>

using namespace std;


/*
 *
 */
class Physics {
	public:
		static void calculate(vector<PhysicsObject*> &list, float dt);
		static float vecSize(sf::Vector2f &v);
		static float vecSize2(sf::Vector2f &v);
		static sf::Vector2f normalize(sf::Vector2f &v);
		static sf::Vector2f getCentre(sf::FloatRect &r);
		static float accInt(float a, float v, float dt);
		static bool lineIntersect(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f q0, sf::Vector2f q1, float &sr);
		static sf::Vector2f getPoint(sf::FloatRect &rect, int i);

		static const float RepulsionCoef;
};

