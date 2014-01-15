/*
 * Babel.h
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

#include "Language.h"

#include <string>
#include <map>

using namespace std;


/*
 *
 */
class Babel {
	public:
		static void addLanguage(Language& lang);

		static const string &get(const string &id);
		static const string &get(const string &id, const string &lang);

	private:
		static Language *defaultLanguage;
		static map<const string, Language&> dicio;

		static const string fallbackString;

		Babel();
		Babel(Babel&);

};

