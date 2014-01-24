/*
 * Renderer.h
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

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "World.h"
#include "Entity.h"

class RenderingLayer {
	public:
		RenderingLayer(unsigned int number, const std::string &name)
				: number(number), name(name), active(true) {
		}

		int getNumber() const;
		void setNumber(int number);
		bool hasObject(sf::Drawable* object);
		void addObject(sf::Drawable* object);
		void removeObject(sf::Drawable* object);
		const std::string& getName() const;
		void setName(const std::string& name);
		bool isActive() const;
		void setActive(bool active);
		void render(sf::RenderWindow *window);

	private:
		unsigned int number;
		const std::string name;
		bool active;
		std::vector<sf::Drawable*> objects;
};

typedef std::vector<RenderingLayer*>::iterator LayerIterator;
typedef std::vector<RenderingLayer*>::const_iterator LayerIteratorConst;
typedef std::vector<sf::Drawable*>::iterator ObjectIterator;

/*
 *
 */
class Renderer {
	public:
		Renderer(sf::VideoMode);

		void addObject(sf::Drawable *object, unsigned int layer);
		void setWorld(World *world, unsigned int layer);
		void removeObject(sf::Drawable *object, unsigned int layer);
		void removeObject(sf::Drawable *object);
		int addLayer(const std::string &name);
		void removeLayer(unsigned int number);

		void render() const;
		sf::RenderWindow* getWindow() const;

		sf::FloatRect &getCamera();

		/*
		 * Note: this requires a World to be set.
		 */
		void cameraTrackEntity(Entity*);
		void updateCamera();

	private:
		sf::RenderWindow *window;
		std::vector<RenderingLayer*> layers;

		World *world;
		unsigned int worldLayer;
		sf::FloatRect camera;

		Entity* track;

};

