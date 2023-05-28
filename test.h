#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <vector>
#include "player.h"

extern std::vector<std::string> sequences;

class Test
{
    public:
        Test(bool TEST_MODE);
        ~Test();

    private:

        void runAllTests();
        void runPlayerTests();
        void runMoneyTests();
        void runPropertyTests();

        //player tests
        void playerInitializedCorrectly();
        void updatePlayerLocation();
        void playerPropertys();

        //money tests
        void depositMoney();
        void withdrawalMoney();
        void passGo();

        //property tests
    
        void propertyChecks(int propertyIndex, Player *testPlayer, int numberOfHouses = 0, int numberOfHotels = 0);
        void buyProperty();
        void sellProperty();
        void buyHouseAndSellHouse();
        void buyHotelAndSellHotel();
        void payRentSuccessfully();
        void payRentGameOver();





};

#endif