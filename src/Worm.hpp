/*
Project: BattleWorms
File: Worm.hpp
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

#ifndef BATTLEWORMS_WORM_HPP
#define BATTLEWORMS_WORM_HPP

#include <SFML/Graphics.hpp>
#include <deque>
#include "Constants.hpp"

class Game;

class Worm : public sf::Sprite {
public:
    Worm(Game& game);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void changeDirection(Direction dir);
    void move();
    void wrap();
    // TODO: Document functions

private:
    struct Segment : public sf::RectangleShape {
        Segment(Worm& worm, float startX, float startY, Direction dir, float length = width_);
        void move(float offset);
        void resize(float amount);
        bool isOutOfBounds();
        Worm& worm_;
        Direction dir_;
    };

private:
    using SegPtr = std::unique_ptr<Segment>;
    std::deque<SegPtr> segments_;
    Game& game_;
    float speed_ = 4.0;  // amount to move head and tail by each frame
    static constexpr float width_ = 10.0;
    static const sf::Color color_;
};


#endif //BATTLEWORMS_WORM_HPP
