/*
Project: BattleWorms
File: Item.hpp
Author: Joel McFadden
Created: January 17, 2016
Last Modified: January 18, 2016

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

#ifndef BATTLEWORMS_ITEM_HPP
#define BATTLEWORMS_ITEM_HPP

#include <SFML/Graphics.hpp>


class Item : public sf::Sprite {
public:
    enum class Type { grow, accelerate };   // effect item has on worms

public:
    Item(Type type, float val, float x, float y, const std::string& filename);
    /* Create a new item with specified type, value, coordinates, and image */

private:
    sf::Texture texture_;   // TODO: Refactor this out
    Type type_;         // property the item affects
    float value_;       // amount to adjust property by
    unsigned points_;   // point value
};


#endif //BATTLEWORMS_ITEM_HPP
