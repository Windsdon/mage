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
#include "TileGrass.h"
#include "Mob.h"
#include "InvisibleWall.h"

Game::Game()
		: renderer(sf::VideoMode(1280, 720)), running(false), intro(NULL), state(State::Intro) {
}

void Game::run() {
	running = true;

	ResourceImage logo("windsdonLogo", "res/logo.png");
	ResourceImage splash("splash", "res/splash.png");

	font.loadFromFile("res/visitor1.ttf");

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

			renderer.getWindow()->setIcon(32, 32, static_cast<ResourceImage*>(ResourceLoader::get("image.game.icon"))->getPixelsPtr());

			renderer.removeObject(loadingScreen, 0);

			//renderer.addObject(new sf::Sprite(*static_cast<ResourceTexture*>(ResourceLoader::get("texture.gui.menuBackground"))), 0);

			world = new World(32);
			world->setSize(50, 50);
			world->setViewSize(1280, 720);

			sf::FloatRect &camera = renderer.getCamera();

			camera.top = 0;
			camera.left = 0;
			camera.width = 1280;
			camera.height = 720;

			randomizeWorld();

			player = new Player(world, 100, 100, 64, 64, static_cast<TileSheet*>(ResourceLoader::get("tilesheet.mob.player")));

			world->addEntity(player);

			renderer.setWorld(world, 1);
			renderer.cameraTrackEntity(player);

		}
	}

	if (state == State::Running) {
		player->force = sf::Vector2f(0, 0);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
			player->force += sf::Vector2f(0, -3000);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			player->force += sf::Vector2f(-3000, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			player->force += sf::Vector2f(0, 3000);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			player->force += sf::Vector2f(3000, 0);
		}

		if (player->force.x == 0) {
			player->velocity.x = 0;
		}
		if (player->force.y == 0) {
			player->velocity.y = 0;
		}

		world->tick();
	}

	renderer.updateCamera();
	renderer.render();
}

void Game::load() {
	ResourceList list;
	list.push_back(new ResourceImage("image.game.icon", "res/icon.png"));
	list.push_back(new ResourceImage("image.gui.menuBackground", "res/gui/menuBackground.png"));
	list.push_back(new ResourceTexture("texture.gui.menuBackground", "image.gui.menuBackground"));
	list.push_back(new ResourceImage("image.tile.stone", "res/tile/stone.png"));
	list.push_back(new ResourceImage("image.tile.grass", "res/tile/grass.png"));
	list.push_back(new ResourceImage("image.mob.player", "res/mob/hero.png"));
	list.push_back(new TileSheet("tilesheet.tile.stone", "image.tile.stone"));
	list.push_back(new TileSheet("tilesheet.tile.grass", "image.tile.grass"));
	list.push_back(new TileSheet("tilesheet.mob.player", "image.mob.player"));

	ResourceLoader::queue(list);

	ResourceLoader::loadThread();
}

void Game::randomizeWorld() {
	TileSheet *stoneTex = static_cast<TileSheet*>(ResourceLoader::get("tilesheet.tile.stone"));
	TileSheet *grassTex = static_cast<TileSheet*>(ResourceLoader::get("tilesheet.tile.grass"));

	for (unsigned int i = 0; i < world->getWidth(); i++) {
		for (unsigned int j = 0; j < world->getHeight(); j++) {
			if (!(rand() % 20)) {
				world->setTile(new TileStone(32, 32, i, j, (rand() % 3 << 8), stoneTex));
			} else {
				world->setTile(new TileGrass(32, 32, i, j, (rand() % 3 << 8) + rand() % 3, grassTex));
			}
		}
	}

	world->addPhysicsObject(new InvisibleWall(0, 0, 32, world->getHeight() * 32));
	world->addPhysicsObject(new InvisibleWall(0, 0, 32 * world->getWidth(), 32));
	world->addPhysicsObject(new InvisibleWall(world->getWidth() * 32 - 32, 0, 32, world->getHeight() * 32));
	world->addPhysicsObject(new InvisibleWall(0, world->getHeight()*32 - 32, 32 * world->getWidth(), 32));

	for (int i = 0; i < 20; i++) {
		world->addEntity(new Player(world, rand() % 700 + 40, rand() % 700 + 40, 64, 64, static_cast<TileSheet*>(ResourceLoader::get("tilesheet.mob.player"))));
	}
}
