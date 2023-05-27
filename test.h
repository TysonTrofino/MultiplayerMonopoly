#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <vector>

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
        void buyProperty();
        void sellProperty();
        void buyHouseAndSellHouse();
        void buyHotelAndSellHotel();
        void payRentSuccessfully();
        void payRentGameOver();




};

#endif