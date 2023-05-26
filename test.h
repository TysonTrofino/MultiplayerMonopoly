#ifndef TEST_H
#define TEST_H

class Test
{
    public:
        Test();
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



};

#endif