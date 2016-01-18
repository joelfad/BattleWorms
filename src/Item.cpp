/*
Project: BattleWorms
File: Item.cpp
Author: Joel McFadden
Created: January 17, 2016
Last Modified: January 17, 2016

Description:
    A remake of the classic game "Nibbles" with new features.

Copyright (C) 2016 Joel McFadden

Usage Agreement:
    This file is part of BattleWorms.

    BattleWorms is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    BattleWorms is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with BattleWorms.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Item.hpp"


Item::Item(Type type, float val, float x, float y, const std::string& filename) : type_{type}, value_{val}
{
    // load texture
    if (!texture_.loadFromFile(filename))
        throw new std::runtime_error("Unable to load " + filename);
    // TODO: Set up a texture map in the game. It is inefficient to load the same texture for each new item.
    setTexture(texture_);

    // set initial position
    setPosition(x, y);
}
