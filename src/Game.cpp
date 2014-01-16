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
#include "ResourceLoader.h"
#include "ResourceImage.h"
#include "ResourceTexture.h"
#include "TileSheet.h"
#include "TileStone.h"

Game::Game()
		: renderer(sf::VideoMode(1280, 720)), running(false), intro(NULL), state(State::Intro) {
}

void Game::run() {
	running = true;

	ResourceImage logo("windsdonLogo", "res/logo.png");
	ResourceImage splash("splash", "res/splash.png");

	font.loadFromFile("res/ARIAL.TTF");

	logo.load();
	splash.load();

	intro = new Intro(&logo, &splash);

	renderer.addLayer("background");
	renderer.addLayer("game");
	renderer.addLayer("gui");

	renderer.addObject(intro, 0);

	Babel::addLanguage(*(new Language("lang/en.lang")));

	renderer.getWindow()->setTitle(Babel::get("game.name"));

	while (running) {
		loop();
	}

	Logger::getInstance().log("Execution terminated");
}

void Game::loop() {

	sf::Window *window = renderer.getWindow();
	sf::Event e;

	while (window->pollEvent(e)) {
		if (e.type == sf::Event::Closed || (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Key::Escape)) {
			window->close();
			running = false;
			return;
		}
	}

	if (state == State::Intro) {
		if (intro->isComplete() || true) {
			renderer.removeObject(intro, 0);
			state = State::Loading;

			loadingScreen = new LoadingScreen(font, font);

			renderer.addObject(loadingScreen, 0);

			load();
		}
	}

	if (state == State::Loading) {
		double complete = ResourceLoader::getCompletion();
		loadingScreen->setCompletion(complete);

		if (complete == 1) {
			state = State::Running; //for testing

			renderer.removeObject(loadingScreen, 0);

			//renderer.addObject(new sf::Sprite(*static_cast<ResourceTexture*>(ResourceLoader::get("texture.gui.menuBackground"))), 0);

			world = new World(32);
			world->setSize(200, 200);
			world->setViewSize(1280, 720);

			sf::FloatRect &camera = renderer.getCamera();

			camera.top = 0;
			camera.left = 0;
			camera.width = 1280;
			camera.height = 720;

			randomizeWorld();

			renderer.setWorld(world, 1);

		}
	}

	if (state == State::Running) {

	}

	renderer.render();
}

void Game::load() {
	ResourceList list;
	list.push_back(new ResourceImage("image.gui.menuBackground", "res/gui/menuBackground.png"));
	list.push_back(new ResourceTexture("texture.gui.menuBackground", "image.gui.menuBackground"));
	list.push_back(new ResourceImage("image.tile.test", "res/tile/test.png"));
	list.push_back(new TileSheet("tilesheet.tile.test", "image.tile.test"));

	ResourceLoader::queue(list);

	ResourceLoader::loadThread();
}

void Game::randomizeWorld() {
	TileSheet *tex = static_cast<TileSheet*>(ResourceLoader::get("tilesheet.tile.test"));

	for (int i = 0; i < world->getWidth(); i++) {
		for (int j = 0; j < world->getHeight(); j++) {
			world->setTile(new TileStone(32, 32, i, j, (rand() % 3 << 8), tex));
		}
	}
}
