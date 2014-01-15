/*
 * Babel.cpp
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

#include "Babel.h"
#include "Logger.h"

const string Babel::fallbackString = "<missing>";
Language *Babel::defaultLanguage = NULL;
map<const string, Language&> Babel::dicio;

void Babel::addLanguage(Language& lang) {
	if(dicio.size() == 0){
		defaultLanguage = &lang;
	}
	dicio.insert(pair<const string, Language&>(lang.getName(), lang));
}

const string& Babel::get(const string& id) {
	const string *str;

	if(defaultLanguage == NULL){
		return fallbackString;
	}

	if(!defaultLanguage->get(id, str)){
		Logger::getInstance().log("Could not find string " + id);

		return fallbackString;
	}

	return *str;
}

const string& Babel::get(const string& id, const string& lang) {
	map<const string, Language&>::const_iterator it;

	const string *str;

	if((it = dicio.find(id)) == dicio.end()){
		return get(id);
	}

	if(!(*it).second.get(id, str)){
		return get(id);
	}

	return *str;
}
