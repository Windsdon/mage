/*
 * Renderer.cpp
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

#include "Renderer.h"
#include "Logger.h"
#include "Babel.h"

Renderer::Renderer(sf::VideoMode videoMode)
		: world(NULL), worldLayer(0), track(NULL) {
	window = new sf::RenderWindow(videoMode, Babel::get("game.name"), sf::Style::Close);
}

void Renderer::addObject(sf::Drawable* object, unsigned int layer) {
	if (layer >= layers.size() || layer < 0) {
		return;
	}
	layers.at(layer)->addObject(object);
}

void Renderer::removeObject(sf::Drawable* object) {
	for (LayerIterator it = layers.begin(); it != layers.end(); ++it) {
		if ((*it)->hasObject(object)) {
			(*it)->removeObject(object);
			break;
		}
	}
}

void Renderer::removeObject(sf::Drawable* object, unsigned int layer) {
	if (layer >= layers.size() || layer < 0) {
		return;
	}

	layers.at(layer)->removeObject(object);
}

int Renderer::addLayer(const std::string &name) {
	layers.push_back(new RenderingLayer(layers.size(), name));
	return layers.size() - 1;
}

void Renderer::removeLayer(unsigned int number) {
	if (number < 0 || number >= layers.size()) {
		return;
	}

	layers.erase(layers.begin() + number);
	for (unsigned int i = 0; i < layers.size(); i++) {
		layers.at(i)->setNumber(i);
	}
}

void Renderer::render() const {
	window->clear(sf::Color::Black);

	for (LayerIteratorConst it = layers.begin(); it != layers.end(); ++it) {
		if (*it == 0) {
			continue;
		}
		if ((*it)->isActive()) {
			(*it)->render(window);
			if ((*it)->getNumber() == worldLayer && world != NULL) {
				world->draw(*window, camera);
			}
		}
	}

	window->display();
}

void Renderer::setWorld(World* world, unsigned int layer) {
	this->world = world;
	this->worldLayer = layer;
}

sf::RenderWindow* Renderer::getWindow() const {
	return window;
}

void RenderingLayer::render(sf::RenderWindow* window) {
	for (ObjectIterator it = objects.begin(); it != objects.end(); ++it) {
		if (*it == 0) {
			cout << "Failed to render object: NullPointer" << endl;
			continue;
		}

		window->draw(**it);
	}
}

int RenderingLayer::getNumber() const {
	return number;
}

void RenderingLayer::setNumber(int number) {
	this->number = number;
}

const std::string& RenderingLayer::getName() const {
	return name;
}

bool RenderingLayer::hasObject(sf::Drawable* object) {
	return (std::find(objects.begin(), objects.end(), object) != objects.end());
}

void RenderingLayer::addObject(sf::Drawable* object) {
	objects.push_back(object);
}

void RenderingLayer::removeObject(sf::Drawable* object) {
	ObjectIterator it = std::find(objects.begin(), objects.end(), object);
	if (it != objects.end()) {
		objects.erase(it);
	}
}

bool RenderingLayer::isActive() const {
	return active;
}

void RenderingLayer::setActive(bool active) {
	this->active = active;
}

void RenderingLayer::setName(const std::string& name) {
}

sf::FloatRect &Renderer::getCamera() {
	return camera;
}

void Renderer::cameraTrackEntity(Entity* e) {
	track = e;
}

void Renderer::updateCamera() {
	if (track != NULL) {
		sf::Vector2f centre = track->getVisualCentre();
		camera.left = centre.x - camera.width / 2;
		camera.top = centre.y - camera.height / 2;

		//cout << "Camera: " << camera.left << ", " << camera.top << ", " << camera.width << ", " << camera.height << endl;

		if (camera.left < 0) {
			camera.left = 0;
		}
		if (camera.top < 0) {
			camera.top = 0;
		}

		if (world != NULL) {
			//cout << "World size: " << world->getPixelWidth() << ", " << world->getPixelHeight() << endl;
			if (camera.left + camera.width > world->getPixelWidth()) {
				camera.left = world->getPixelWidth() - camera.width;
			}
			if (camera.top + camera.height > world->getPixelHeight()) {
				camera.top = world->getPixelHeight() - camera.height;
			}
		}
	}

	//cout << "Camera updated to " << camera.left << ", " << camera.top << ", " << camera.width << ", " << camera.height << endl;
}
