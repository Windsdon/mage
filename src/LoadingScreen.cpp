/*
 * LoadingScreen.cpp
 *
 *  Created on: 15/01/2014
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

#include "LoadingScreen.h"
#include "Babel.h"
#include "Logger.h"

ostream &operator<<(ostream &left, sf::FloatRect &right){
	left << "[" << right.left << ", " << right.top << ", " << right.width << ", " << right.height << "]";

	return left;
}

LoadingScreen::LoadingScreen(sf::Font& loadingFont, sf::Font& textFont)
		: bgTop(56, 138, 255), bgBottom(17, 77, 255), loadBg(5, 13, 255), loadColor(0, 85, 255), complete(0) {

	loading.setFont(loadingFont);
	loading.setString(Babel::get("gui.loading"));

	loading.setCharacterSize(32);

	sf::FloatRect bounds = loading.getLocalBounds();

	cout << bounds << endl;

	loading.setOrigin((int)(bounds.width/2 + bounds.left), bounds.height/2 + bounds.top);
	loading.setPosition(0, 0);
	loading.setColor(sf::Color(0, 125, 225));
}

void LoadingScreen::setText(const string& str) {
}

void LoadingScreen::setCompletion(double val) {
	complete = val;
}

void LoadingScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::Vector2u size = target.getSize();

	//draw the background
	sf::VertexArray bg(sf::Quads, 4);

	bg.append(sf::Vertex(sf::Vector2f(0, 0), bgTop));
	bg.append(sf::Vertex(sf::Vector2f(size.x, 0), bgTop));
	bg.append(sf::Vertex(sf::Vector2f(size.x, size.y), bgBottom));
	bg.append(sf::Vertex(sf::Vector2f(0, size.y), bgBottom));

	target.draw(bg, states);

	//the loading bar is 2/3 of the width and 50px high
	sf::Vector2f loadOrig(size.x / 2.0 - 2 * size.x / 6.0, size.y / 2.0 - 50 / 2.0);
	sf::RectangleShape barBg(sf::Vector2f(2.0 * size.x / 3.0, 50));
	barBg.setFillColor(loadBg);
	barBg.setPosition(loadOrig);

	target.draw(barBg, states);

	sf::Vector2f barSize = sf::Vector2f(2.0 * size.x / 3.0 * complete, 50) - sf::Vector2f(6, 6);
	if (barSize.x < 0) {
		barSize.x = 0;
	}
	sf::RectangleShape bar(barSize);
	bar.setFillColor(loadColor);
	bar.setPosition(loadOrig + sf::Vector2f(3, 3));

	target.draw(bar, states);

	sf::Transform posLoad(states.transform);
	sf::RenderStates loadState(states);

	posLoad.translate(size.x/2, size.y/2);

	loadState.transform *= posLoad;

	target.draw(loading, loadState);
/*
	sf::RectangleShape r1(sf::Vector2f(size.x / 2, size.y));
	sf::RectangleShape r2(sf::Vector2f(size.x, size.y / 2));

	r1.setFillColor(sf::Color::Transparent);
	r1.setOutlineColor(sf::Color::Red);
	r1.setOutlineThickness(1.0f);

	r2.setFillColor(sf::Color::Transparent);
	r2.setOutlineColor(sf::Color::Red);
	r2.setOutlineThickness(1.0f);

	target.draw(r1, states);
	target.draw(r2, states);*/

}
