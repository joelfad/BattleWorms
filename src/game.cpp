/*
Project: BattleWorms
File: game.cpp
Author: Joel McFadden
Created: December 21, 2015
Last Modified: December 21, 2015

Description:
    A remake of the classic game "Nibbles" with new features.

Copyright (C) 2015 Joel McFadden

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

#include "game.hpp"
#include "constants.hpp"


Game::Game() : window_(sf::VideoMode(640, 480), "BattleWorms")
{
}

void Game::run()
{
    // one iteration of this loop is a single frame (or tick)
    while (window_.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window_.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window_.close();
        }
    }
}

void Game::update()
{
}

void Game::render()
{
    window_.clear(Color::backgroundBlue);
    window_.display();
}