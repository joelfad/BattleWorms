/*
Project: BattleWorms
File: Game.hpp
Author: Joel McFadden
Created: December 21, 2015
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

#ifndef BATTLEWORMS_GAME_HPP
#define BATTLEWORMS_GAME_HPP

#include <SFML/Graphics.hpp>
#include "Worm.hpp"


class Game {
public:
    Game();
    void run();
    const sf::RenderWindow& getWindow() const;

private:
    void processEvents();
    void update();
    void render();
    void handlePlayerInput(sf::Keyboard::Key key);

private:
    sf::RenderWindow window_;
    sf::Texture backgroundTile_;
    sf::Sprite background_;
    Worm player_;
    unsigned score_;    // TODO: Track and display score
    static constexpr unsigned windowWidth_ = 1024;
    static constexpr unsigned windowHeight_ = 768;
    static constexpr unsigned fps_ = 60;
};


#endif //BATTLEWORMS_GAME_HPP
