/*
 * Physics.cpp
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

#include "Physics.h"
#include <iostream>
using namespace std;


const float Physics::RepulsionCoef = 10000.0f;

/*
 * this function assumes that there is no residual forces from last iteration
 * and that the forces that are acting are self generated or external,
 * therefore, no cleaning is done on the force.
 * Friction is calculated here.
 */
void Physics::calculate(vector<PhysicsObject*> &list, float dt) {
	for (vector<PhysicsObject*>::iterator it = list.begin(); it != list.end(); ++it) {
		PhysicsObject *o1 = *it;

		if (o1->isFixed() || o1->mass <= 0) {
			continue;
		}

		sf::FloatRect r1 = o1->getCollisionBox();

		for (vector<PhysicsObject*>::iterator it2 = list.begin(); it2 != list.end(); ++it2) {
			PhysicsObject *o2 = *it2;

			if (o1 == o2) {
				continue;
			}

			sf::FloatRect r2 = o2->getCollisionBox();

			if (!r1.intersects(r2)) {
				continue;
			}

			sf::Vector2f o1c = getCentre(r1);
			sf::Vector2f o2c = getCentre(r2);

			sf::Vector2f v = o1c - o2c;

			o1->force += normalize(v) * RepulsionCoef;

		}

		sf::Vector2f vn = normalize(o1->velocity);
		sf::Vector2f friction = o1->friction * vn * vecSize(o1->velocity);

		o1->force -= friction;

		//calculate acceleration
		o1->acceleration = o1->force / o1->mass;

		//calculate ds
		o1->ds.x = accInt(o1->acceleration.x, o1->velocity.x, dt);
		o1->ds.y = accInt(o1->acceleration.y, o1->velocity.y, dt);

		//calculate velocity
		o1->velocity = o1->acceleration * dt;

	}



	//now that we updated all the objects, we can calculate the collisions with fixed objects
	for (vector<PhysicsObject*>::iterator it = list.begin(); it != list.end(); ++it) {
		PhysicsObject *o1 = *it;

		if (o1->isFixed()) {
			continue;
		}

		o1->moveDelta(o1->ds.x, o1->ds.y);
	}
}

float Physics::vecSize(sf::Vector2f &v) {
	return sqrt(vecSize2(v));
}

float Physics::vecSize2(sf::Vector2f &v) {
	return (pow(v.x, 2) + pow(v.y, 2));
}

sf::Vector2f Physics::normalize(sf::Vector2f &v) {
	float size = vecSize(v);
	if (size == 0) {
		return sf::Vector2f(0, 0);
	}

	return (v / size);
}

sf::Vector2f Physics::getCentre(sf::FloatRect &r) {
	return sf::Vector2f(r.left + r.width / 2, r.top + r.height / 2);
}

float Physics::accInt(float a, float v, float dt) {
	return (v * dt + 0.5f * a * pow(dt, 2));
}
