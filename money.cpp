#include <iostream>
#include <string>

#include "money.h"



Money::Money(std::string name_)
{
    moneyAmount = 500;
    name = name_;
}

Money::~Money()
{
    moneyAmount = 0;
}

int Money::getMoneyAmount()
{
    return moneyAmount;
}

void Money::printMoneyAmount(std::string word)
{
    std::cout << name << word << " has $" << moneyAmount << std::endl; 
}

void Money::passGo()
{
    addMoney(200);
    std::cout << name << " passed go and collected $200" << std::endl;
    printMoneyAmount(" now");
}

void Money::addMoney(int amount)
{
    moneyAmount += amount;
    printMoneyAmount(" now");

}

void Money::subtractMoney(int amount)
{
    moneyAmount -=amount;
    printMoneyAmount(" now");
}