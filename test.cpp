#include <iostream>
#include <string>
#include <vector>
#include <cassert>

#include "test.h"
#include "properties.h"
#include "money.h"

Test::Test()
{
    Properties::initializeProperties("prop.csv");
    runAllTests();

}

Test::~Test()
{
    return;
}

void Test::runAllTests()
{
    runPlayerTests();
    runMoneyTests();

}


// Player tests
void Test::runPlayerTests()
{
    playerInitializedCorrectly();
    updatePlayerLocation();
    playerPropertys();
}

void Test::playerInitializedCorrectly()
{
    Player *player1 = new Player("player1", 1);

    assert(player1->getName() == "player1");
    assert(player1->getPlayerIndex() == 1); 
    assert(player1->getPlayerLocation() == 0);
    assert(player1->getPlayerMoneyAmount() == 500);

    std::cout << "Passed playerInitializedCorrectly" << std::endl;

}

void Test::updatePlayerLocation()
{
    Player *player1 = new Player("player1", 1);

    assert(player1->getPlayerLocation() == 0);
    player1->updatePlayerLocation(2);
    assert(player1->getPlayerLocation() == 2);
    player1->updatePlayerLocation(4);
    player1->updatePlayerLocation(7);
    assert(player1->getPlayerLocation() == 7);

    std::cout << "Passed updatePlayerLocation" << std::endl;
}

void Test::playerPropertys()
{
    Player *player1 = new Player("player1",1);
    player1->AddProperty(2);
    player1->AddProperty(5);
    player1->AddProperty(4);

    std::vector<int> testCheck1 = {2,5,4};
    assert(player1->getPropertyLocations() == testCheck1);

    player1->deleteProperty(5);
    std::vector<int> testCheck2 = {2,4};
    assert(player1->getPropertyLocations() == testCheck2);

    player1->deleteProperty(4);
    std::vector<int> testCheck3 = {2};
    assert(player1->getPropertyLocations() == testCheck3);

    std::cout << "Passed playerPropertys" << std::endl;
}


// Money Tests
void Test::runMoneyTests()
{
    depositMoney();
}

void Test::depositMoney()
{
    Player *player1 = new Player("player1",1);
    
    assert(player1->getPlayerMoneyAmount() == 500);
    player1->transaction->deposit(300);
    assert(player1->getPlayerMoneyAmount() == 800);
    player1->transaction->deposit(200);
    player1->transaction->deposit(50);
    player1->transaction->deposit(1);
    player1->transaction->deposit(0);
    
    assert(player1->getPlayerMoneyAmount() == 1051);

    std::cout << "Passed depositMoney" << std::endl;


}



