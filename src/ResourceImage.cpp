/*
 * ResourceImage.cpp
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

#include "ResourceImage.h"
#include "Logger.h"

ResourceImage::ResourceImage(const string id, const string file): Resource(id, file), loaded(false) {
	
}

ResourceImage::~ResourceImage() {
}

void ResourceImage::load() {
	loaded = loadFromFile(getFile());

	if(!loaded){
		LogEntry e(Logger::Severity::ALERT, "Could not load " + getFile(), "Image Load");
		Logger::getInstance().log(e);
	}
}

bool ResourceImage::isLoaded() const {
	return loaded;
}
