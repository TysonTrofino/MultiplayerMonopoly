#include <iostream>
#include <string>

#include "money.h"



Money::Money(std::string name_)
{
    balance = 500;
    name = name_;
}

Money::~Money()
{
    balance = 0;
}

int Money::bankAccountBalance()
{
    return balance;
}

void Money::printBankAccountBalance(std::string word)
{
    std::cout << name << word << " has $" << balance << std::endl; 
}

void Money::passGo()
{
    deposit(200);
    std::cout << name << " passed go and collected $200" << std::endl;
    printBankAccountBalance(" now");
}

void Money::deposit(int amount)
{
    balance += amount;
    printBankAccountBalance(" now");

}

void Money::withdrawal(int amount)
{
    balance -=amount;
    printBankAccountBalance(" now");
}