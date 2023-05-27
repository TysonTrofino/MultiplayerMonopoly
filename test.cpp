#include <iostream>
#include <string>
#include <vector>
#include <cassert>

#include "test.h"
#include "properties.h"
#include "money.h"

Test::Test(bool TEST_MODE)
{
    Properties::initializeProperties("prop.csv", TEST_MODE);
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
    runPropertyTests();

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

    delete player1;

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

    delete player1;
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

    delete player1;
}


// Money Tests
void Test::runMoneyTests()
{
    depositMoney();
    withdrawalMoney();
    passGo();
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

    delete player1;
}

void Test::withdrawalMoney()
{
    Player *player1 = new Player("player1", 1);
    assert(player1->getPlayerMoneyAmount() == 500);
    player1->transaction->withdrawal(300);
    assert(player1->getPlayerMoneyAmount() == 200);

    player1->transaction->withdrawal(100);
    player1->transaction->withdrawal(50);
    player1->transaction->withdrawal(1);

    assert(player1->getPlayerMoneyAmount() == 49);

    std::cout << "Passed withdrawalMoney" << std::endl;
    delete player1;
}

void Test::passGo()
{
    Player *player1 = new Player("player1", 1);
    assert(player1->getPlayerMoneyAmount() == 500);
   
    player1->transaction->passGo();

    assert(player1->getPlayerMoneyAmount() == 700);    

    std::cout << "Passed passGo" << std::endl;
    delete player1;
}

void Test::runPropertyTests()
{
    buyProperty();
}

void Test::buyProperty()
{
    Player *player1 = new Player("player1", 1);

    Properties::buyProperty(player1, 2);
    Properties::setTestOptionSelectionList({"-1","4", "1", "1", "2"});
    Properties::buyProperty(player1, 4);

    assert(Properties::getPropertyOwnerIndex(2) == 1);
    assert(Properties::getPropertyOwnerIndex(4) == -1);
    
    std::cout << "Passed buyProperty" << std::endl;
    
}


