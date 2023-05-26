#include "player.h"
#include "money.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

Player::Player(std::string name_, int playerIndex_)
{
    name = name_;
    playerIndex = playerIndex_;
    transaction = new Money(name_);
    playerLocation = 0;
}

Player::~Player()
{
    delete transaction;
}

void Player::printName()
{
    std::cout << name << std::endl;
}

std::string Player::getName()
{
    return name;
}

int Player::getPlayerIndex()
{
    return playerIndex;
}

int Player::getPlayerLocation()
{
    return playerLocation;
}

void Player::updatePlayerLocation(int location)
{
    playerLocation = location;
}

void Player::AddProperty(int propertyLocation)
{
    propertyArray.push_back(propertyLocation);
}

std::vector<int> Player::getPropertyLocations()
{
    return propertyArray;
}

void Player::deleteProperty(int propertyLocation)
{
    auto index = std::find(propertyArray.begin(), propertyArray.end(), propertyLocation);
    propertyArray.erase(propertyArray.begin() + std::distance(propertyArray.begin(), index));
}

int Player::getPlayerMoneyAmount()
{
    return transaction->bankAccountBalance();
}