/*
 * Language.cpp
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

#include "Language.h"

#include "Logger.h"

#include <fstream>
#include <iostream>

using namespace std;

Language::Language(const string &filename)
		: name(NULL) {
	ifstream reader(filename);

	if (!reader.is_open()) {
		Logger::getInstance().log("Could not find language file " + filename);
		return;
	}

	string line;
	string key, value;

	int i = 0;
	while (getline(reader, line)) {
		if (i == 0) {
			name = new const string(line);
		} else {
			bool finishedKey = false;
			bool foundSet = false;
			bool startedValue = false;

			key.clear();
			value.clear();
			for (unsigned int j = 0; j < line.size(); j++) {
				char c = line.at(j);

				if (c == ' ') {
					if (!finishedKey) {
						finishedKey = true;
					} else if (foundSet) {
						if (startedValue) {
							value += c;
						} else {
							continue;
						}
					} else {
						continue;
					}
				} else {
					if (c == '=') {
						if(foundSet){
							value += c;
						}
						finishedKey = true;
						foundSet = true;
					} else {
						if (!finishedKey) {
							key += c;
						}else{
							startedValue = true;
							value += c;
						}
					}
				}
			}

			dicio.insert(pair<const string, const string>(*(new const string(key)), *(new const string(value))));
		}

		i++;
	}

}

bool Language::get(const string &id, const string *&result) const {
	map<const string, const string>::const_iterator it;

	if ((it = dicio.find(id)) == dicio.end()) {
		return false;
	}

	result = &((*it).second);

	return true;
}

const string& Language::getName() const {
	return *name;
}
