/*
 * Intro.cpp
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

#include "Intro.h"
#include "Logger.h"

Intro::Intro(ResourceImage *logo, ResourceImage *splash): logoTime(sf::seconds(2)), splashTime(sf::seconds(2)) {
	sf::Vector2u sizeLogo = logo->getSize();

	logoTop.loadFromImage(*logo, sf::IntRect(0, 0, sizeLogo.x, sizeLogo.y/2));
	logoBottom.loadFromImage(*logo, sf::IntRect(0, sizeLogo.y/2, sizeLogo.x, sizeLogo.y/2));
	
	splashTexture.loadFromImage(*splash);
}

bool Intro::isComplete() const {
	return time.getElapsedTime() > (logoTime + splashTime);
}

void Intro::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::Vector2u size = target.getSize();

	if(time.getElapsedTime() > logoTime){
		if(time.getElapsedTime() - logoTime < splashTime){
			sf::Sprite splashSprite(splashTexture);
			sf::FloatRect splashSize = splashSprite.getLocalBounds();

			splashSprite.setScale((float) (size.x/splashSize.width), (float) (size.y/splashSize.height));

			target.draw(splashSprite, states);
		}
	}else{
		sf::Sprite topSprite(logoTop);
		sf::Sprite bottomSprite(logoBottom);

		sf::FloatRect topSize = topSprite.getLocalBounds();
		sf::FloatRect bottomSize = bottomSprite.getLocalBounds();

		topSprite.setScale(size.x/topSize.width, size.y/(topSize.height * 2));
		bottomSprite.setScale(size.x/bottomSize.width, size.y/(bottomSize.height * 2));

		topSprite.setPosition(0, 0);
		bottomSprite.setPosition(0, size.y/2.0f);

		target.draw(topSprite);
		target.draw(bottomSprite);

	}
}
