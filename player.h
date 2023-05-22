#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <string>

#include "money.h"

class Player
{
    public:
        Player(std::string name_, int playerIndex_);
        ~Player();

        void printName();
        std::string getName();

        int getPlayerIndex();

        std::vector<int> getPropertyIndexes();
        int getPlayerLocation();
        void updatePlayerLocation(int location);

        void AddProperty(int propertyLocation);
        void deleteProperty(int propertyLocation);

        Money *transaction;
        
    private:
        std::string name;
        int playerIndex;
        std::vector<int>propertyArray;
        int playerLocation;
        
        
        



};

#endif
