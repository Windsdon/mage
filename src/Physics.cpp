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
#include <cmath>
using namespace std;

const float Physics::RepulsionCoef = 3000.0f;
const float Physics::MaximumTimeStep = 0.01f;

/*
 * this function assumes that there is no residual forces from last iteration
 * and that the forces that are acting are self generated or external,
 * therefore, no cleaning is done on the force.
 * Friction is calculated here.
 */
void Physics::calculate(vector<PhysicsObject*> &list, float dt) {
	while (dt > Physics::MaximumTimeStep) {
		dt -= Physics::MaximumTimeStep;
		calculate(list, Physics::MaximumTimeStep);
	}
	PhysicsObject *o1;
	sf::FloatRect r1;
	PhysicsObject *o2;
	sf::FloatRect r2;

	sf::Vector2f v;
	sf::Vector2f o1c;
	sf::Vector2f o2c;
	sf::Vector2f d;

	vector<PhysicsObject*>::iterator it;
	vector<PhysicsObject*>::iterator it2;

	for (it = list.begin(); it != list.end(); ++it) {
		o1 = *it;

		if (o1->isFixed() || o1->mass <= 0) {
			continue;
		}

		r1 = o1->getCollisionBox();

		for (it2 = list.begin(); it2 != list.end(); ++it2) {
			o2 = *it2;

			if (o1 == o2 || o2->isFixed()) {
				continue;
			}

			r2 = o2->getCollisionBox();

			if (!r1.intersects(r2)) {
				continue;
			}

			o1c = getCentre(r1);
			o2c = getCentre(r2);

			v = o1c - o2c;

			o1->force += normalize(v) * RepulsionCoef;

		}

		o1->force += -o1->friction * o1->velocity * vecSize(o1->velocity);

		//calculate acceleration
		o1->acceleration = o1->force / o1->mass;

		//calculate ds
		o1->ds.x = accInt(o1->acceleration.x, o1->velocity.x, dt);
		o1->ds.y = accInt(o1->acceleration.y, o1->velocity.y, dt);

		//calculate velocity
		o1->velocity += (o1->acceleration * dt);

	}

	//now that we updated all the objects, we can calculate the collisions with fixed objects
	for (it = list.begin(); it != list.end(); ++it) {
		o1 = *it;

		if (o1->isFixed()) {
			continue;
		}

		d = o1->ds;

		bool collidesX = false, collidesY = false;

		for (it2 = list.begin(); it2 != list.end(); ++it2) {
			o2 = *it2;

			if (o1 == o2 || !o2->isFixed()) {
				continue;
			}

			r2 = o2->getCollisionBox();

			/*
			 * Check x and y collisions separately
			 */

			float extra;

			r1 = o1->getCollisionBox();
			r1.left += d.x;
			if (r1.intersects(r2)) {
				collidesX = true;
				if (d.x > 0) {
					extra = r1.left + r1.width - r2.left;
					d.x -= extra;
				} else if (d.x != 0) {
					extra = r1.left - r2.left - r2.width;
					d.x -= extra;
				}
			}

			r1 = o1->getCollisionBox();
			r1.top += d.y;

			if (r1.intersects(r2) && abs(r1.left + r1.width - r2.left) > 0.005) {
				collidesY = true;
				if (d.y > 0) {
					extra = r1.top + r1.height - r2.top;
					d.y -= extra;
				} else if (d.y != 0) {
					extra = r1.top - r2.top - r2.height;
					d.y -= extra;
				}
			}

		}

		if (collidesX) {
			o1->velocity.x = 0;
		}

		if (collidesY) {
			o1->velocity.y = 0;
		}

		o1->moveDelta(d.x, d.y);
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

sf::Vector2f Physics::getCentre(const sf::FloatRect &r) {
	return sf::Vector2f(r.left + r.width / 2, r.top + r.height / 2);
}

float Physics::accInt(float a, float v, float dt) {
	return (v * dt + 0.5f * a * pow(dt, 2));
}

bool Physics::lineIntersect(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f q0, sf::Vector2f q1, float &sr) {
	sf::Vector2f u = p1 - p0;
	sf::Vector2f v = q1 - q0;

	float det = (u.x * v.y - u.y * v.x);

	if (det == 0) {
		return false;
	}

	float s = ((p0.y - q0.y) * v.x + (q0.x - p0.x) * v.y) / det;
	float t = ((q0.x - p0.x) * u.y + (p0.y - q0.y) * u.x) / det;

	if (s <= 0 || s >= 1 || t <= 0 || t >= 1) {
		return false;
	}

	sr = s;

	return true;
}

sf::Vector2f Physics::getPoint(sf::FloatRect& rect, int i) {
	switch (i) {
		case 0:
			return sf::Vector2f(rect.left, rect.top);

		case 1:
			return sf::Vector2f(rect.left + rect.width, rect.top);

		case 2:
			return sf::Vector2f(rect.left + rect.width, rect.top + rect.height);

		case 3:
			return sf::Vector2f(rect.left, rect.top + rect.height);
	}

	return sf::Vector2f();
}
