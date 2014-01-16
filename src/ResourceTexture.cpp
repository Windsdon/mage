/*
 * ResourceTexture.cpp
 *
 *  Created on: 16/01/2014
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

#include "ResourceTexture.h"
#include "ResourceLoader.h"
#include "ResourceImage.h"
#include "Logger.h"

ResourceTexture::ResourceTexture(const string id, const string imageId)
		: Resource(id, imageId), loaded(false) {
}

ResourceTexture::~ResourceTexture() {
}

void ResourceTexture::load() {
	Resource *image = ResourceLoader::get(getFile());

	if (image == NULL) {
		LogEntry e(Logger::Severity::WARNING, "The required source is not loaded: " + getFile(), "ResourceTexture");
		Logger::getInstance().log(e);
		return;
	}

	if (image->getType() != Resource::Type::Image) {
		LogEntry e(Logger::Severity::WARNING, "The required source is not an image: " + getFile(), "ResourceTexture");
		Logger::getInstance().log(e);
		return;
	}

	loaded = loadFromImage(*(static_cast<ResourceImage*>(image)));
}

bool ResourceTexture::isLoaded() const {
	return loaded;
}

Resource::Type ResourceTexture::getType() const {
	return Resource::Type::Texture;
}
