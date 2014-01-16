/*
 * ResourceLoader.cpp
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

#include "ResourceLoader.h"
#include <SFML/System.hpp>
#include "Logger.h"

bool ResourceLoader::loading = false;
ResourceList ResourceLoader::loadList;
map<const string, Resource*> ResourceLoader::list;

void ResourceLoader::queue(ResourceList& allocator) {
	if (loading) {
		LogEntry e(Logger::Severity::WARNING, "Cannot queue while loading", "ResourceLoader");
		Logger::getInstance().log(e);
	}
	for (ResourceList::iterator it = allocator.begin(); it != allocator.end(); ++it) {
		bool has = false;
		for (ResourceList::iterator it2 = loadList.begin(); it2 != loadList.end(); ++it2) {
			if (*it2 == *it) {
				has = true;
				break;
			}
		}
		if (!has) {
			loadList.push_back(*it);

			LogEntry e(Logger::Severity::INFO, "Queued " + (*it)->getId(), "ResourceLoader");
			Logger::getInstance().log(e);
		}
	}

}

void ResourceLoader::load() {
	loading = true;

	Resource* elem;

	for (ResourceList::iterator it = loadList.begin(); it != loadList.end(); ++it) {
		elem = *it;

		if (list.find(elem->getId()) != list.end()) {
			LogEntry e(Logger::Severity::WARNING, "Tried to load id that is already loaded: " + elem->getId(), "ResourceLoader");
			Logger::getInstance().log(e);
			continue;
		}

		elem->load();

		if (!elem->isLoaded()) {
			LogEntry e(Logger::Severity::WARNING, "Loaded item reports not being loaded: " + elem->getId(), "ResourceLoader");
			Logger::getInstance().log(e);
			continue;
		}

		LogEntry e(Logger::Severity::INFO, "Loaded: " + elem->getId(), "ResourceLoader");
		Logger::getInstance().log(e);

		list.insert(pair<const string, Resource*>(elem->getId(), elem));

	}

	loadList.clear();

	loading = false;
}

double ResourceLoader::getCompletion() {
	int total = list.size() + loadList.size();
	if (total == 0) {
		return 1;
	}
	return (((double) list.size()) / (total));
}

Resource* ResourceLoader::get(const string id) {
	map<const string, Resource*>::iterator elem;

	if ((elem = list.find(id)) == list.end()) {
		LogEntry e(Logger::Severity::WARNING, "Requested unloaded element: " + id, "ResourceLoader");
		Logger::getInstance().log(e);
		return NULL;
	}

	return elem->second;
}

void ResourceLoader::loadThread() {
	sf::Thread *thread = new sf::Thread(&ResourceLoader::load);

	thread->launch();
}
