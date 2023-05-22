#ifndef MONEY_H
#define MONEY_H

#include <string>

class Money
{
    public:
        Money(std::string name_);
        ~Money();

        int getMoneyAmount();
        void printMoneyAmount(std::string word = "");

        void passGo();

        void addMoney(int amount);
        void subtractMoney(int amount);

    private:
        int moneyAmount;
        std::string name;
};

#endif