#ifndef MONEY_H
#define MONEY_H

#include <string>

class Money
{
    public:
        Money(std::string name_);
        ~Money();

        int bankAccountBalance();
        void printBankAccountBalance(std::string word = "");

        void passGo();

        void deposit(int amount);
        void withdrawal(int amount);

    private:
        int balance;
        std::string name;
};

#endif