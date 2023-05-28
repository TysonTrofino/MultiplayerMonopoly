#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <string>

#include "player.h"

class Game
{
    public:
        Game(std::string file);
        ~Game();

    private:
        void playGame();
        int rollDice();


        std::vector<Player>* playerVector;
        std::string input;
        int numPlayers;
        
};

#endif