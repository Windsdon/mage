/*
 * ResourceLoader.h
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

#pragma once

#include <vector>
#include <map>
#include "Resource.h"

using namespace std;

typedef vector<Resource*> ResourceList;

class ResourceLoader {
	public:
		static void queue(ResourceList&);
		static void load();
		static double getCompletion();
		static Resource *get(const string id);

		static void loadThread();

	private:
		static ResourceList loadList;
		static map<const string, Resource*> list;
		static bool loading;

		ResourceLoader();
		ResourceLoader(ResourceLoader&);
};

