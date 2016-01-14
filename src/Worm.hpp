/*
Project: BattleWorms
File: Worm.hpp
Author: Joel McFadden
Created: January 14, 2016
Last Modified: January 14, 2016

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

#ifndef BATTLEWORMS_WORM_HPP
#define BATTLEWORMS_WORM_HPP

#include <SFML/Graphics.hpp>


class Worm {
public:
    Worm();

private:
    struct Segment : public sf::Sprite {
        enum class Direction { up, down, right, left };
        Direction dir_;
        sf::Vector2u location_;
        unsigned length_;
        Segment* next_;
    };

private:
    Segment* head_;
    Segment* tail_;

};


#endif //BATTLEWORMS_WORM_HPP
