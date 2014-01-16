/*
 * World.cpp
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

#include "World.h"
#include "Logger.h"
#include <algorithm>

World::World(int tileSize)
		: tileSize(tileSize), width(0), height(0) {

}

void World::tick() {

}

bool World::hasEntity(Entity* e, vector<Entity*>::iterator *p = NULL) {
	for (vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it) {
		if ((*it) == e) {
			if (p) {
				*p = it;
			}
			return true;
		}
	}

	return false;
}

void World::addEntity(Entity* e) {
	if (!hasEntity(e)) {
		entities.push_back(e);
	} else {
		LogEntry entry(Logger::Severity::WARNING, "Tried to added entity already in list", "World");
		Logger::getInstance().log(entry);
	}
}

void World::removeEntity(Entity* e) {
	vector<Entity*>::iterator p;
	if (hasEntity(e, &p)) {
		entities.erase(p);
	} else {
		LogEntry entry(Logger::Severity::WARNING, "Tried to remove entity that is not from this world", "World");
		Logger::getInstance().log(entry);
	}
}

void World::setSize(unsigned int width, unsigned int height) {
	this->width = width;
	this->height = height;

	while (tiles.size() < height) {
		tiles.push_back(*(new vector<Tile*>()));
	}

	for(vector<vector<Tile*> >::iterator it = tiles.begin(); it != tiles.end(); ++it){
		(*it).resize(width);
		fill((*it).begin(), (*it).end(), static_cast<Tile*>(NULL));
	}
}

void World::setTileAt(unsigned int tileX, unsigned int tileY, Tile* tile) {
	if (tileX > width || tileY > height) {
		LogEntry entry(Logger::Severity::WARNING, "Tried to set tile out of this world", "World");
		Logger::getInstance().log(entry);
		return;
	} else {
		Tile* oldTile = tiles[tileY][tileX];
		if (oldTile != NULL) {
			delete oldTile;
		}
		tiles[tileY][tileX] = tile;

		cout << "Tile at " << tileX << ", " << tileY << " is now " << tiles[tileY][tileX] << endl;
	}
}

void World::setTile(Tile* tile) {
	setTileAt(tile->getTileX(), tile->getTileY(), tile);
}

void World::setViewSize(unsigned int width, unsigned int height) {
	backgroundLayer.create(width, height, false);
	foregroundLayer.create(width, height, false);
}

void World::draw(sf::RenderTarget& target, const sf::FloatRect& view) {
	backgroundLayer.clear(sf::Color::Transparent);
	foregroundLayer.clear(sf::Color::Transparent);

	sf::Transform tr;
	sf::Vector2f top(view.left, view.top);

	tr.translate(top);
	sf::RenderStates rs(tr);

	int startx = view.left / tileSize;
	int endx = startx + (view.width) / tileSize + 1;
	int starty = view.top / tileSize;
	int endy = starty + (view.height) / tileSize + 1;

	for (vector<vector<Tile*> >::iterator ity = tiles.begin() + starty; ity != tiles.begin() + endy; ++ity) {
		vector<Tile*> tilex = *ity;
		for (vector<Tile*>::iterator itx = tilex.begin() + startx; itx != tilex.begin() + endx; ++itx) {
			Tile *tile = *itx;

			if(tile == NULL){
				continue;
			}
			if (tile->isAlwaysTop()) {
				foregroundLayer.draw(*tile, rs);
			} else {
				backgroundLayer.draw(*tile, rs);
			}
		}
	}

	backgroundLayer.display();
	foregroundLayer.display();

	sf::Sprite bgSprite(backgroundLayer.getTexture());

	target.draw(bgSprite);

	// entities should be sorted in back to front order
	for (vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it) {
		target.draw(**it);
	}

	sf::Sprite fgSprite(foregroundLayer.getTexture());
	target.draw(bgSprite);

}

World::~World() {

}
