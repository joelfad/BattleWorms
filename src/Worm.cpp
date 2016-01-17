/*
Project: BattleWorms
File: Worm.cpp
Author: Joel McFadden
Created: January 14, 2016
Last Modified: January 16, 2016

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

#include <iostream>
#include "Worm.hpp"
#include "Game.hpp"


const sf::Color Worm::color_ = Color::wormYellow;

Worm::Worm(Game& game) : game_(game)
{
    // create first worm segment
    constexpr float posX = 0.0;     // arbitrary starting position
    constexpr float posY = 200.0;
    segments_.push_front(std::make_unique<Segment>(Segment(*this, posX, posY, Direction::right)));
    segments_.front()->setSize(sf::Vector2f(20 * width_, width_));
}

Worm::Segment::Segment(Worm& worm, float startX, float startY, Direction dir) : worm_(worm), dir_{dir}
{
    // set initial position, size, and color
    setPosition(startX, startY);
    setSize(sf::Vector2f(Worm::width_, Worm::width_));
    setFillColor(Worm::color_);

    // set orientation (rotate CCW)
    setRotation(static_cast<int>(dir) * 90);
}

void Worm::Segment::move(float offset)
{
    switch (dir_) {
        case Direction::up:
            sf::RectangleShape::move(0.0, -offset);
            break;
        case Direction::down:
            sf::RectangleShape::move(0.0, +offset);
            break;
        case Direction::right:
            sf::RectangleShape::move(+offset, 0.0);
            break;
        case Direction::left:
            sf::RectangleShape::move(-offset, 0.0);
            break;
    }
}

inline void Worm::Segment::resize(float amount)
{
    setSize(sf::Vector2f(getSize().x + amount, getSize().y));
}

bool Worm::Segment::isOutOfBounds()
{
    switch (dir_) {
        case Direction::right:
            return getPosition().x + getSize().x > worm_.game_.getWindow().getSize().x;
        case Direction::down:
            return getPosition().y + getSize().x > worm_.game_.getWindow().getSize().y;
        case Direction::left:
            return getPosition().x - getSize().x < 0.0;
        case Direction::up:
            return getPosition().y - getSize().x < 0.0;
    }
}

void Worm::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // draw each segment of the worm
    for (auto& s : segments_)
        target.draw(*s, states);
}

void Worm::changeDirection(Direction dir)
{
    Segment& s = *segments_.front();

    // any change in direction must be orthogonal to current direction
    if (static_cast<int>(s.dir_) % 2 == static_cast<int>(dir) % 2)
        return;

    float length = s.getSize().x;
    float posX = s.getPosition().x;
    float posY = s.getPosition().y;
    float newX = posX;
    float newY = posY;

    // moving right
    if (s.dir_ == Direction::right) {
        // turn up
        if (dir == Direction::up) {
            newX += length - width_;
            newY += width_;
        }
        // turn down
        else {
            newX += length;
        }
    }
    // moving left
    else if (s.dir_ == Direction::left) {
        // turn up
        if (dir == Direction::up) {
            newX -= length;
        }
        // turn down
        else {
            newX -= length - width_;
            newY -= width_;
        }
    }
    // moving up
    else if (s.dir_ == Direction::up) {
        // turn right
        if (dir == Direction::right) {
            newY -= length;
        }
        // turn left
        else {
            newY -= length - width_;
            newX += width_;
        }
    }
    // moving down
    else if (s.dir_ == Direction::down) {
        // turn right
        if (dir == Direction::right) {
            newY += length - width_;
            newX -= width_;
        }
        // turn left
        else {
            newY += length;
        }
    }

    s.resize(-width_);  // create space for new square segment
    segments_.push_front(std::make_unique<Segment>(Segment(*this, newX, newY, dir)));
}

void Worm::move()
{
    Segment& head = *segments_.front();
    Segment& tail = *segments_.back();

    // move head and tail segments
    head.resize(speed_);
    tail.resize(-speed_);
    tail.move(speed_);

    // wrap worm if it attempts to cross a display boundary
    if (head.isOutOfBounds())
        head.move(-100);

    // destroy tail if it becomes too small
    if (tail.getSize().x <= 0.0)
        segments_.pop_back();
}