#include <iostream>
#include <vector>
#include <string>
#include <ctime>

#include "game.h"
#include "player.h"
#include "properties.h"

Game::Game(std::string file)
{
    Properties::initializeProperties(file);
    playerVector = new std::vector<Player>;

    std::cout << "Welcome to Monopoly" <<  std::endl;
    std::cout << "Please enter the number of player that would like to play:" << std::endl;
    getline(std::cin,input);
    numPlayers = std::stoi(input);

    std::cout << "Please enter each players name that would like to play:" << std::endl;
    for(int i = 0; i<numPlayers; i++)
    {
        std::cout << "Enter Player " << i+1 << "'s name:" << std::endl;
        getline(std::cin, input);
        Player *player = new Player(input, i);
        playerVector->push_back(*player);
    }
    playGame();

}

Game::~Game()
{

}

void Game::playGame()
{
    std::cout << rollDice() << std::endl;
}

int Game::rollDice()
{
    std::srand(time(0));
    return std::rand() % 6 + 1;
}
