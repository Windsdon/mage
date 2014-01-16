/*
 * TileSheet.cpp
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

#include "TileSheet.h"
#include "ResourceLoader.h"
#include "Logger.h"

TileSheet::TileSheet(const string id, const string imageId, int tileSize)
		: Resource(id, imageId), tileSize(tileSize), loaded(false) {
}

TileSheet::TileSheet(const string id, const string imageId): TileSheet(id, imageId, -1) {
}

TileSheet::~TileSheet() {
	for (vector<sf::Texture*>::iterator it = textures.begin(); it != textures.end(); ++it) {
		delete *it;
	}
	textures.clear();
}

void TileSheet::load() {

	Resource *res = ResourceLoader::get(getFile());

	if (res == NULL) {
		LogEntry e(Logger::Severity::WARNING, "The required source is not loaded: " + getFile(), "TileSheet");
		Logger::getInstance().log(e);
		return;
	}

	if (res->getType() != Resource::Type::Image) {
		LogEntry e(Logger::Severity::WARNING, "The required source is not an image: " + getFile(), "TileSheet");
		Logger::getInstance().log(e);
		return;
	}

	ResourceImage *image = static_cast<ResourceImage*>(res);

	sf::Vector2u size = image->getSize();

	if(tileSize < 0){
		tileSize = size.x;
	}

	if (size.x < tileSize || size.y < tileSize) {
		LogEntry e(Logger::Severity::WARNING, "The image is not big enough: " + getFile(), "TileSheet");
		Logger::getInstance().log(e);
		return;
	}

	int count = size.y / tileSize;

	for (int i = 0; i < count; i++) {
		sf::Texture *tex = new sf::Texture();
		tex->loadFromImage(*image, sf::IntRect(0, tileSize * i, tileSize, tileSize));
		textures.push_back(tex);
	}

	loaded = true;
}

bool TileSheet::isLoaded() const {
	return loaded;
}

Resource::Type TileSheet::getType() const {
	return Resource::Type::TileSheet;
}

const sf::Texture* TileSheet::getTexture(int offset) const {
	if (offset >= getSize() || offset < 0) {
		LogEntry e(Logger::Severity::WARNING, getId() + ": Offset out of bounds", "TileSheet");
		Logger::getInstance().log(e);
		return getTexture(0);
	}

	return textures.at(offset);
}

int TileSheet::getSize() const {
	return textures.size();
}

const sf::Texture* TileSheet::operator [](int offset) const {
	return getTexture(offset);
}
