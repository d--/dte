#include "game.h"
#include <iostream>

Game::Game(std::string name) {
    this->name = name;
};

void Game::SayMyName() {
    std::cout << "\"" << this->name << "\"" << std::endl;
    std::cout << "THAT'S THE NAME OF THE GAME" << std::endl;
}

Game::~Game() {}
