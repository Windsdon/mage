/*
 * Tile.cpp
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

#include "Tile.h"
#include <iostream>

using namespace std;

unsigned long Tile::getData() const {
	return data;
}

bool Tile::isUpdateScheduled() const {
	return updateScheduled;
}

Tile::Tile(int width, int height, int x, int y, unsigned long data, TileSheet *sheet)
		: data(data), updateScheduled(false), width(width), height(height), tileX(x), tileY(y), sheet(sheet) {
	sprite.setScale(((float) width) / sheet->getTileSize(), ((float) height) / sheet->getTileSize());
	sprite.setOrigin(sheet->getTileSize() / 2.0, sheet->getTileSize() / 2.0);
	sprite.setPosition(x * width + width/2.0, y * height + height/2.0);

	friction = 0;
	mass = 0;

	update();
}

void Tile::setData(unsigned long data) {
	if (this->data != data) {
		updateScheduled = true;
	}

	this->data = data;

}

bool Tile::update() {
	updateScheduled = false;

	sprite.setTexture(*(sheet->getTexture(getOffset())), true);
	sprite.rotate(90 * (getRotation() % 4));

	return false;
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::Vector2f size(32, 32);
	sf::RectangleShape rect(size);
	rect.setPosition(sprite.getPosition());

	target.draw(sprite, states);
	//target.draw(rect, states);
}

void Tile::setUpdateScheduled(bool updateScheduled) {
	this->updateScheduled = updateScheduled;
}

unsigned Tile::getOffset() const {
	return (data & 0xf);
}

bool Tile::getExtend(ExtendDirection dir) const {
	return ((data >> 4) & (1 << (int) dir));
}

unsigned Tile::getRotation() const {
	return ((data >> 8) & 0x3);
}

unsigned long Tile::getExtra() const {
	return (data >> 10);
}
