/*
Project: BattleWorms
File: Game.cpp
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

#include "Game.hpp"


Game::Game() : window_(sf::VideoMode(windowWidth_, windowHeight_), "BattleWorms"),
               player_{*this}, state_{State::running}, score_{0}
{
    // limit the framerate
    window_.setFramerateLimit(fps_);
    // TODO: Use fixed time steps for more accuracy

    // load background texture into sprite
    if (!backgroundTile_.loadFromFile("res/img/background/dirt_tile.png"))
        throw new std::runtime_error("Unable to load background texture.");
        // TODO: Catch this runtime error
    backgroundTile_.setRepeated(true);
    background_.setTexture(backgroundTile_);
    background_.setTextureRect(sf::IntRect(0, 0, windowWidth_, windowHeight_));

    // test loading items
    // TODO: Randomly generate items
    // TODO: Specific items should share the same properties (e.g. a tomato should always grow the worm 30.f)
    items_.push_back(std::make_unique<Item>(Item::Type::grow, 30.f, 40.f, 100.f, "res/img/sprites/garden/tomato.png"));
    items_.push_back(std::make_unique<Item>(Item::Type::grow, 20.f, 600.f, 700.f, "res/img/sprites/garden/raddish.png"));
    items_.push_back(std::make_unique<Item>(Item::Type::grow, 25.f, 200.f, 450.f, "res/img/sprites/garden/carrot.png"));
    items_.push_back(std::make_unique<Item>(Item::Type::accelerate, 1.f, 950.f, 300.f, "res/img/sprites/garden/pepper.png"));
}

void Game::run()
{
    // one iteration of this loop is a single frame (or tick)
    while (window_.isOpen() && isRunning()) {
        processEvents();
        update();
        render();
    }
}

void Game::end()
{
    while (window_.isOpen())    // TODO: Replace with handling
        processEvents();        //       different game endings
}

const sf::RenderWindow& Game::getWindow() const
{
    return window_;
}

void Game::processEvents()
{
    sf::Event event;
    while (window_.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code);
                break;
            case sf::Event::Closed:
                window_.close();
                break;
        }
    }
}

inline void Game::update()
{
    player_.move();
    if (player_.collisionSelf())
        state_ = State::lost;
}

void Game::render()
{
    window_.clear();
    window_.draw(background_);
    for (auto& i : items_)
        window_.draw(*i);
    window_.draw(player_);
    window_.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key)
{
    switch (key) {
        case sf::Keyboard::Up:
            player_.changeDirection(Direction::up);
            break;
        case sf::Keyboard::Down:
            player_.changeDirection(Direction::down);
            break;
        case sf::Keyboard::Right:
            player_.changeDirection(Direction::right);
            break;
        case sf::Keyboard::Left:
            player_.changeDirection(Direction::left);
            break;
    }
}

inline bool Game::isRunning()
{
    return state_ == State::running;
}
