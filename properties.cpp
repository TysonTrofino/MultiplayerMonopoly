#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>

#include "properties.h"
#include "player.h"


Properties* Properties::instance = NULL;
std::vector<Properties::PropertyInfo>* Properties::property;

Properties* Properties::initializeProperties(std::string propertyFile)
{
    if(!instance) {
        instance = new Properties(propertyFile);
    }
    return instance;
}

Properties::Properties(std::string propertyFile)
{
    property = new std::vector<Properties::PropertyInfo>;

    std::fstream inFile;
    std::string lineOfData;
    std::string data;

    std::vector<std::string>dataTransfer;

    inFile.open(propertyFile);

    while(getline(inFile, lineOfData))
    {
        std::stringstream line(lineOfData);

        while(getline(line,data,','))
        {
            dataTransfer.push_back(data);
        }

        PropertyInfo *propertyValues = new PropertyInfo;

        propertyValues->propertyName = dataTransfer[0];
        propertyValues->buyingCost = std::stoi(dataTransfer[1]);
        propertyValues->houseCost = std::stoi(dataTransfer[2]);
        propertyValues->hotelCost = std::stoi(dataTransfer[3]);
        propertyValues->numberOfHotels = 0;
        propertyValues->numberOfHouses = 0;
        propertyValues->ownerIndex = -1;

        property->push_back(*propertyValues);

        dataTransfer.clear();
    }
}

void Properties::printPropertiesList(std::vector<int>list)
{
   
}

void Properties::printPropertyInfo(int propertyIndex)
{
    PropertyInfo info = property->at(propertyIndex);

//     int setValBeforeProp = 10;
//     int setValAfterProp = info.propertyName.size() + 10;
//     int setValAfterCost = 10;

//     std::cout<< std::setw(10) << std::left << "Owner" << std::setw(setValAfterProp) << std::left <<"Property"; 
//     if(info.ownerIndex == -1)
//     {
//         std::cout << std::setw(setValAfterCost) << std::left << "Cost to Buy" << std::setw(setValAfterProp) << std::left << "Cost of Houses" << std::setw(setValAfterProp) << std::left << "Cost of Hotels" << std::endl; 
//         std::cout << "-------------------------------------------------------------------------------" << std::endl;
//         std::cout << std::setw(10) << std::left << "No Owner" << std::setw(setValAfterProp) << std::left << info.propertyName << std::setw(setValAfterCost) << std::left << info.buyingCost << std::setw(setValAfterProp) << std::left << info.houseCost << std::setw(setValAfterProp) << std::left << info.hotelCost << std::endl;
//     }

    std::cout << "Property: " << info.propertyName << std::endl;
    if(info.ownerIndex == -1) {
        std::cout << "Cost to Buy: $" << info.buyingCost << std::endl;
    } else {
        std::cout << "Owner: " << info.owner << std::endl;
        std::cout << "Number of Houses " <<info.numberOfHouses << std::endl;
        std::cout << "Rent: $" << calculateRent(propertyIndex) << std::endl;
        std::cout << "Sell Price: $" << calculateSellingCost(propertyIndex) << std::endl;
    }

//     // std::cout << "Cost "
}

void Properties::buyProperty(Player *buyer, int propertyIndex)
{
    PropertyInfo & info = property->at(propertyIndex);

    if(checkMoney(buyer->transaction->getMoneyAmount(), info.buyingCost))
    {
        transaction(buyer->getName(), info.propertyName);

        info.owner = buyer->getName();
        info.ownerIndex = buyer->getPlayerIndex();

        buyer->transaction->subtractMoney(info.buyingCost);
        buyer->AddProperty(propertyIndex);
        
    } else {
        cantAfford(buyer->getName(), "buy this property.");
    }
}

void Properties::payRent(Player *owner, Player *renter, int propertyIndex)
{
    PropertyInfo & info = property->at(propertyIndex);
    int rent = calculateRent(propertyIndex);

    if(checkMoney(renter->transaction->getMoneyAmount(), rent))
    {
        transaction(renter->getName(), info.propertyName, " you have landed on ");
        std::cout<< "The rent is: $" << rent << std::endl;
        
        renter->transaction->subtractMoney(rent);
        owner->transaction->addMoney(rent);

    } else {
        cantAfford(renter->getName(), " pay the rent.  You have the following options:");
        std::vector<std::string> list = {"Sell Properties", "Quit Game"};
        printList(list);

        std::string option;

        std::cout<<"Choice"<<endl;

        getline(cin, option);

        switch(std::stoi(option))
        {
            case 1: 
        }


    }
}

int Properties::calculateRent(int propertyIndex)
{
    PropertyInfo rent = property->at(propertyIndex);

    return ((rent.buyingCost / 5) + (rent.houseCost * rent.numberOfHouses) + (2 * rent.hotelCost * rent.numberOfHotels));
}

int Properties::calculateSellingCost(int propertyIndex)
{
    PropertyInfo sell = property->at(propertyIndex);

    return ((sell.buyingCost / 10) + (sell.houseCost * sell.numberOfHouses)/10 + (sell.hotelCost * sell.numberOfHotels)/5);
}


bool Properties::checkMoney(int playerWealth, int price)
{
    if(playerWealth >= price)
    {
        return true;
    }
    
    return false;
}

void Properties::printList(std::vector<str::string> list)
{
    int size = list.size();
    std::cout << "------Menu------" << std::endl;
    for(int i = 0; i < size; i++)
    {
        std::cout << i+1 << ". " << list[i] << std::endl;
    }
}

void Properties::cantAfford(std::string name, std::string phrase)
{
    std::cout << name << ", you cannot afford to " << phrase << std::endl;
}

void Properties::transaction(std::string owner, std::string property, std::string phrase)
{
    std::cout << owner << phrase << property << std::endl;
}


