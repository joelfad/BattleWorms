/*
Project: BattleWorms
File: Worm.cpp
Author: Joel McFadden
Created: January 14, 2016
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

#include "Worm.hpp"
#include "Game.hpp"


const sf::Color Worm::color_ = Color::wormYellow;

Worm::Worm(Game& game, float startX, float startY, float startLen) : game_(game)
{
    // create first worm segment
    segments_.push_front(std::make_unique<Segment>(*this, startX, startY, Direction::right, startLen));
}

Worm::Segment::Segment(Worm& worm, float startX, float startY, Direction dir, float length)
        : worm_(worm), dir_{dir}
{
    // set initial position, size, and color
    setPosition(startX, startY);
    setSize(sf::Vector2f(length, Worm::width_));
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
    float newLength = getSize().x + worm_.speed_;

    switch (dir_) {
        case Direction::right:
            return getPosition().x + newLength > worm_.game_.getWindow().getSize().x;
        case Direction::down:
            return getPosition().y + newLength > worm_.game_.getWindow().getSize().y;
        case Direction::left:
            return getPosition().x - newLength < 0.0;
        case Direction::up:
            return getPosition().y - newLength < 0.0;
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
    segments_.push_front(std::make_unique<Segment>(*this, newX, newY, dir));
}

void Worm::move()
{
    Segment& head = *segments_.front();
    Segment& tail = *segments_.back();

    // grow head segment
    if (!head.isOutOfBounds())
        head.resize(speed_);
    else {
    // wrap worm if it attempts to cross a display boundary
        wrap();
    }

    // shrink and move tail segment
    tail.resize(-speed_);
    tail.move(speed_);

    // destroy tail if it becomes too small
    float len = tail.getSize().x;   // get length of tail (may be negative)
    if (len <= 0.0) {
        segments_.pop_back();       // remove tail
        Segment& newTail = *segments_.back();
        newTail.resize(len);        // shrink and move new tail
        newTail.move(-len);
    }
}

void Worm::wrap()
{
    Segment& s = *segments_.front();

    float posX = s.getPosition().x;
    float posY = s.getPosition().y;
    float newX = posX;
    float newY = posY;

    switch (s.dir_) {
        case Direction::right:  // new segment on left
            newX = 0.0;
            break;
        case Direction::down:   // new segment at top
            newY = 0.0;
            break;
        case Direction::left:   // new segment on right
            newX = game_.getWindow().getSize().x;
            break;
        case Direction::up:     // new segment at bottom
            newY = game_.getWindow().getSize().y;
            break;
    }

    segments_.push_front(std::make_unique<Segment>(*this, newX, newY, s.dir_, speed_));
}

bool Worm::collisionSelf()
{
    Segment* head = segments_.front().get();
    for (auto& s : segments_) {
        sf::FloatRect i;    // intersection area - required because of floating point inaccuracy
        if (s.get() != head && head->getGlobalBounds().intersects(s->getGlobalBounds(), i) &&
                (i.height > 0.1 && i.width > 0.1))
            return true;
    }
    return false;
}