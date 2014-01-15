/*
 * Game.cpp
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

#include "Game.h"
#include "Logger.h"
#include "Language.h"
#include "Babel.h"

Game::Game()
		: renderer(sf::VideoMode(1280, 720)), running(false), intro(NULL), state(State::Intro) {
}

void Game::run(){
	running = true;

	ResourceImage logo("windsdonLogo", "res/logo.png");
	ResourceImage splash("splash", "res/splash.png");

	logo.load();
	splash.load();

	intro = new Intro(&logo, &splash);

	renderer.addLayer("background");

	renderer.addObject(intro, 0);

	Babel::addLanguage(*(new Language("lang/en.lang")));

	renderer.getWindow()->setTitle(Babel::get("game.name"));

	while(running){
		loop();
	}

	Logger::getInstance().log("Execution terminated");
}

void Game::loop(){

	sf::Window *window = renderer.getWindow();
	sf::Event e;

	while(window->pollEvent(e)){
		if(e.type == sf::Event::Closed || (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Key::Escape)){
			window->close();
			running = false;
			return;
		}
	}

	if(state == State::Intro){
		if(intro->isComplete()){
			renderer.removeObject(intro, 0);
			state = State::Loading;
		}
	}

	renderer.render();
}
