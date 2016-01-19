/*
Project: BattleWorms
File: Game.hpp
Author: Joel McFadden
Created: December 21, 2015
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

#ifndef BATTLEWORMS_GAME_HPP
#define BATTLEWORMS_GAME_HPP

#include <list>
#include <SFML/Graphics.hpp>
#include "Worm.hpp"
#include "Item.hpp"


class Game {
public:
    Game();
    /* Create and initialize a new game */

    void run();
    /* Main game loop - play the game */

    void end();
    /* Game Over loop - wait for user to close window */

    const sf::RenderWindow& getWindow() const;
    /* Return: game display window */

private:
    void processEvents();
    /* Respond to user interaction with game display window */

    void update();
    /* Handle game logic during frame */

    void render();
    /* Draw frame on display window (i.e. draw background, worm, items, etc.) */

    void handlePlayerInput(sf::Keyboard::Key key);
    /* Respond to user pressing a key */

    bool isRunning();
    /* Check if game is running */
    // Return: true if game is running, false otherwise

private:
    enum class State { running, paused, quit, lost, won };
    static constexpr unsigned windowWidth_ = 1024;
    static constexpr unsigned windowHeight_ = 768;
    static constexpr unsigned fps_ = 60;

private:
    sf::RenderWindow window_;       // game display window
    sf::Texture backgroundTile_;    // a single seamless background tile
    sf::Sprite background_;         // entire background
    Worm player_;                   // worm controlled by player
    using ItemPtr = std::unique_ptr<Item>;
    std::list<ItemPtr> items_;      // game items
    State state_;                   // game state
    unsigned score_;    // TODO: Track and display score
};


#endif //BATTLEWORMS_GAME_HPP
