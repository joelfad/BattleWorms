/*
Project: BattleWorms
File: game.hpp
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

#ifndef BATTLEWORMS_GAME_HPP
#define BATTLEWORMS_GAME_HPP

#include <SFML/Graphics.hpp>


class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();

private:
    sf::RenderWindow window_;
};


#endif //BATTLEWORMS_GAME_HPP
