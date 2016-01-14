/*
Project: BattleWorms
File: Worm.cpp
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

#include "Worm.hpp"


const sf::Color Worm::color_ = Color::wormYellow;

Worm::Worm()
{
    // create first worm segment
    constexpr float posX = 10.0;  // arbitrary starting position
    constexpr float posY = 10.0;
    segments_.push_front(std::make_unique<Segment>(Segment(posX, posY, Direction::right)));
    segments_.front()->setSize(sf::Vector2f(10 * width_, width_));
}

Worm::Segment::Segment(float startX, float startY, Direction dir)
    : dir_{dir}, length_{1.0}
{
    // set initial position, size, and color
    setPosition(startX, startY);
    setSize(sf::Vector2f(length_, Worm::width_));
    setFillColor(Worm::color_);
}

void Worm::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // draw each segment of the worm
    for (auto& s : segments_)
        target.draw(*s);
}
