/*
Project: BattleWorms
File: Worm.hpp
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

#ifndef BATTLEWORMS_WORM_HPP
#define BATTLEWORMS_WORM_HPP

#include <SFML/Graphics.hpp>
#include <deque>
#include "Constants.hpp"

class Game;

class Worm : public sf::Sprite {
public:
    Worm(Game& game, float startX = 0.0, float startY = 200.0, float startLen = 20 * width_);
    /* Create a new worm */
    // Optional: starting position and length may be specified

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    /* Render each worm segment */

    void changeDirection(Direction dir);
    /* Point the worm in a new direction (creates a new segment) */
    // Requires: dir must be orthogonal to current direction

    void move();
    /* Move worm the distance it travels in one frame at its current speed */

    bool collisionSelf();
    /* Detect when the worm head hits its body */
    // Returns: true on collision, false otherwise

private:
    void wrap();
    /* Wrap worm body around the edge of game display area */

private:
    struct Segment : public sf::RectangleShape {
        Segment(Worm& worm, float startX, float startY, Direction dir, float length = width_);
        /* Create a new worm segment with given absolute coordinates and direction */
        // Requires: position relative to other segments must be taken into account

        void move(float offset);
        /* Move segment a distance of given offset in its current direction */

        void resize(float amount);
        /* Change the length of the segment by a given amount */

        bool isOutOfBounds();
        /* Detect if part of the segment has crossed a game display boundary */
        // Return: true if over the boundary, false otherwise

        Worm& worm_;
        Direction dir_;
    };

private:
    using SegPtr = std::unique_ptr<Segment>;
    std::deque<SegPtr> segments_;   // worm segments
    Game& game_;
    float speed_ = 4.0;             // amount to move head and tail by each frame
    static constexpr float width_ = 10.0;
    static const sf::Color color_;
};


#endif //BATTLEWORMS_WORM_HPP
