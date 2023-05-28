#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>

#include "properties.h"
#include "player.h"

int maxNumberOfHousesPerProperty;
int maxNumberOfHotelsPerProperty;

Properties* Properties::instance = NULL;
std::vector<Properties::PropertyInfo>* Properties::property;
bool Properties::TEST_MODE;
std::vector<std::string> *Properties::testList;
int Properties::count;

Properties* Properties::initializeProperties(std::string propertyFile, bool TEST_MODE)
{
    if(!instance) {
        instance = new Properties(propertyFile, TEST_MODE);
    }
    return instance;
}

Properties::Properties(std::string propertyFile, bool TEST_MODE_)
{
    maxNumberOfHotelsPerProperty = 2;
    maxNumberOfHousesPerProperty = 3;
    property = new std::vector<Properties::PropertyInfo>;
    testList = new std::vector<std::string>;
    TEST_MODE = TEST_MODE_;

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
        
        initializePropertyOwner(*propertyValues);

        property->push_back(*propertyValues);

        dataTransfer.clear();
    }
}

void Properties::initializePropertyOwner(PropertyInfo &info)
{
    info.numberOfHotels = 0;
    info.numberOfHouses = 0;
    info.ownerIndex = -1;
    info.owner = "No Owner";
}

//void Properties::setPropertiesToInitialState()

int Properties::printPropertiesList(std::vector<int>list, std::string printOptions, bool notSelling)
{
    int size = list.size();
    int indexIncrease;
    std::ostringstream oss;

    oss << " | " << std::left << std::setw(5) << "Index";
    oss << " | " << std::left << std::setw(10) << "Owner";
    oss << " | " << std::left << std::setw(20) << "Property";
    oss << " | " << std::left << std::setw(8) << "Houses";
    oss << " | " << std::left << std::setw(8) << "Hotels";
    oss << " | " << std::left << std::setw(10) << "House Cost";
    oss << " | " << std::left << std::setw(10) << "Hotel Cost";
    oss << " | " << std::left << std::setw(11) << "Buy Price";
    oss << " | " << std::left << std::setw(11) << "Rent Price";
    oss << " | " << std::left << std::setw(11) << "Sell Price";
    oss << " | " << std::endl;

    std::vector<std::string>ownersPropertyList = {oss.str()};

    if(!notSelling) {
        ownersPropertyList.push_back(" | 1 --------------------------------- I-DO-NOT-WANT-TO-SELL-ANY-PROPERTIES ---------------------------------");
        indexIncrease = 2;
    } else {
        indexIncrease = 1;
    }

    //std::cout << std::setw(75) << std::setfill('-') << "" << std::endl;

    for(int i = 0; i<size; i++)
    {
        oss.str("");

        oss << " | " << std::left << std::setw(5) << i+indexIncrease;
        oss << " | " << std::left << std::setw(10) << property->at(list[i]).owner;
        oss << " | " << std::left << std::setw(20) << property->at(list[i]).propertyName;
        oss << " | " << std::left << std::setw(8) << property->at(list[i]).numberOfHouses;
        oss << " | " << std::left << std::setw(8) << property->at(list[i]).numberOfHotels;
        oss << " | $" << std::left << std::setw(10) << property->at(list[i]).houseCost;
        oss << "| $" << std::left << std::setw(10) << property->at(list[i]).hotelCost;
        oss << "| $" << std::left << std::setw(11) << property->at(list[i]).buyingCost;
        oss << "| $" << std::left << std::setw(11) << calculateRent(list[i]);
        oss << "| $" << std::left << std::setw(11) << calculateSellingCostProperty(list[i]);
        oss << "| " << std::endl;

        ownersPropertyList.push_back(oss.str());
    }

    return printList(ownersPropertyList, printOptions, 1);
}

void Properties::printPropertyInfo(std::vector<int> propertyIndexs)
{
    std::cout << "here" << std::endl;
    printPropertiesList(propertyIndexs, "", true);
    
}

int Properties::getPropertyOwnerIndex(int propertyIndex)
{
    return property->at(propertyIndex).ownerIndex;
}

int Properties::getNumberOfHouses(int propertyIndex)
{
    return property->at(propertyIndex).numberOfHouses;
}

int Properties::getNumberOfHotels(int propertyIndex)
{
    return property->at(propertyIndex).numberOfHotels;
}

std::string Properties::getOwnerName(int propertyIndex)
{
    return property->at(propertyIndex).owner;
}

void Properties::buyProperty(Player *buyer, int propertyIndex)
{
    PropertyInfo & info = property->at(propertyIndex);

    if(checkMoney(buyer->transaction->bankAccountBalance(), info.buyingCost))
    {
        transaction(buyer->getName(), info.propertyName);

        info.owner = buyer->getName();
        info.ownerIndex = buyer->getPlayerIndex();

        buyer->transaction->withdrawal(info.buyingCost);
        buyer->AddProperty(propertyIndex);
        
    } else {

        std::ostringstream cantAffordOption;
        std::ostringstream noPropertiesOption;

        cantAffordOption << "buy " << info.propertyName << std::endl;
        noPropertiesOption << "You do not own any properties. You cannot afford to buy " << info.propertyName <<".  It is the next playes turn." <<std::endl;

        switch(checkNumberOfProperties(buyer, cantAffordOption.str(), noPropertiesOption.str(), {"Sell Properties", "Next Players Turn"}))
        {
            case 1:
                sellProperty(buyer, buyer->getPropertyLocations());
                buyProperty(buyer, propertyIndex);
                break;
            case 2:
                std::cout << buyer->getName()<< " your turn is over." << std::endl;
                break;
        };
        

    }
}

void Properties::sellProperty(Player *seller, std::vector<int>propertiesList)
{
    std::ostringstream printOption;
    printOption << "Which property do you want to sell?  Please enter the appropriate index:" << std::endl;

    int propertyIndex = printPropertiesList(propertiesList, printOption.str())-2;
    if(propertyIndex == -1)
    {
        std::cout << "No properties were sold" << std::endl;
       
    } else {

        PropertyInfo & info = property->at(propertiesList[propertyIndex]);
        std::ostringstream printOption1;
        std::ostringstream printOption2;
        std::ostringstream printOption3;

        printOption.str("");
        printOption << "Which part of " << info.propertyName << "do you want to sell?" << std::endl;
        
        printOption1 << "1. All of " << info.propertyName << " for $" << calculateSellingCostProperty(propertiesList[propertyIndex]) << "." << std::endl;
        printOption2 << "2." << info.numberOfHouses <<" Houses on " << info.propertyName << " for $" << calculateSellingCostHouse(propertiesList[propertyIndex], info.numberOfHouses) << "." << std::endl;
        printOption3 << "3." << info.numberOfHotels <<" Hotels on " << info.propertyName << " for $" << calculateSellingCostHotel(propertiesList[propertyIndex], info.numberOfHotels) << "." << std::endl;
       
        switch(printList({printOption1.str(), printOption2.str(), printOption3.str()}, printOption.str(), 1))
        {
            case 1:
                transaction(seller->getName(), info.propertyName, " you have sold everything on ");
                initializePropertyOwner(info);
                seller->transaction->deposit(calculateSellingCostProperty(propertiesList[propertyIndex]));
                seller->deleteProperty(propertiesList[propertyIndex]);
                break;

            case 2:
                sellHouse(seller, propertiesList[propertyIndex]);
                break;

            case 3:
                sellHotel(seller, propertiesList[propertyIndex]);
                break;
        }
    }

}

void Properties::payRent(Player *owner, Player *renter, int propertyIndex)
{
    PropertyInfo & info = property->at(propertyIndex);
    int rent = calculateRent(propertyIndex);
    int option;

    welcomeTo(info.propertyName, "The rent is", rent);

    if(checkMoney(renter->transaction->bankAccountBalance(), rent))
    {
        transaction(renter->getName(), info.propertyName, " you have landed on ");
        std::cout<< "The rent is: $" << rent << std::endl;
        
        renter->transaction->withdrawal(rent);
        owner->transaction->deposit(rent);

    } else {
        
        int renterPropSize = renter->getPropertyLocations().size();
        std::vector<int> renterPropertys = renter->getPropertyLocations();

        std::ostringstream cantAffordOption;
        std::ostringstream noPropertiesOption;

        cantAffordOption << "the rent at " << info.propertyName << "because you have $" <<renter->transaction->bankAccountBalance() << std::endl;
        noPropertiesOption << "pay the rent and have no properties to sell.  You have gone bankrupt." << std::endl;
        std::string printListPhrase = "choice";

        switch(checkNumberOfProperties(renter, cantAffordOption.str(), noPropertiesOption.str(), {"Sell Properties", "Quit Game"}, printListPhrase))
        {
            case 1: 
                sellProperty(renter, renterPropertys);
                payRent(owner, renter, propertyIndex);
                break;

            case 2:
                if(renterPropSize > 0)
                {
                    for(int i = 0; i<renterPropSize; i++)
                    {
                        PropertyInfo &info = property->at(renterPropertys[i]);
                        initializePropertyOwner(info);
                    }
                }

                std::cout << renter->getName() << ", the game is over for you." << std::endl;
                gameOver(renter);

                break;
        };
    }
}

void Properties::buyHouse(Player *owner, int propertyIndex)
{
    PropertyInfo & info = property->at(propertyIndex);
    std::ostringstream oss;
    
    std::vector<std::string>costPerProperty;
    int houseQuantity;

    if(owner->transaction->bankAccountBalance() < info.houseCost)
    {   
        oss << "buy a house on " << info.propertyName << "." << std::endl;
        oss << "1 house costs $" <<info.houseCost << " and you have $" << owner->transaction->bankAccountBalance() << " in your bank account." << std::endl; 
        cantAfford(owner->getName(), oss.str());
        return;
    }

    if(info.numberOfHouses == maxNumberOfHousesPerProperty) {
        std::cout << "You have bought the max number of houses for " << info.propertyName << std::endl;
        return;
    } else {
        std::cout << "There are currently " << info.numberOfHouses << " houses and you can have up to " << maxNumberOfHousesPerProperty <<" houses."<<std::endl; 
        std::cout << owner->getName() << ", you currently have $" << owner->transaction->bankAccountBalance() << "." << std::endl;
    }

    for(int i = info.numberOfHouses; i<maxNumberOfHousesPerProperty; i++)
    {
        if(info.numberOfHouses == 0)
        {
            houseQuantity = i+1;
        } else {
            houseQuantity = i;
        }
        oss << houseQuantity << " house will cost $" << houseQuantity*info.houseCost << std::endl;
        costPerProperty.push_back(oss.str());
        oss.str("");
    }

    int numberOfHousesToPurchase = printList(costPerProperty, "How many houses would you like to purchase?", 1);

    if(checkMoney(owner->transaction->bankAccountBalance(), info.houseCost * numberOfHousesToPurchase))
    {
        transaction(owner->getName(), info.propertyName, ", you have bought a house on ");

        owner->transaction->withdrawal(info.houseCost * numberOfHousesToPurchase);
        info.numberOfHouses += numberOfHousesToPurchase;

    } else {
        oss << "to purchase " << numberOfHousesToPurchase << " houses" << std::endl;
        cantAfford(owner->getName(), oss.str());
        int option = printList({"Yes", "No"}, "Would you like to try again?");

        switch (option)
        {
        case 1:
            buyHouse(owner, propertyIndex);
            break;
        
        case 2:
            std::cout << "No houses were bought."  << owner->getName() << ", your turn is over" << std::endl;
            break;
        }
        
    }
}

void Properties::sellHouse(Player *owner, int propertyIndex)
{
    PropertyInfo & info = property->at(propertyIndex);
    std::ostringstream listOption;
    std::vector<std::string>list;
    int numberOfHousesSold = 0;
    std::ostringstream printOption;

    printOption << "How many houses would you like to sell?" << std::endl;

    for(int i = 0; i < info.numberOfHouses; i++)
    {
        listOption << i+1 << ". house for $" << calculateSellingCostHouse(propertyIndex, i+1);
        list.push_back(listOption.str());
        listOption.str("");
    }

    numberOfHousesSold = printList(list, printOption.str(), 1);
    printOption.str("");
    printOption << " you have sold "<< numberOfHousesSold << " Houses on " << std::endl;
    transaction(owner->getName(), info.propertyName, printOption.str());
    owner->transaction->deposit(calculateSellingCostHouse(propertyIndex, numberOfHousesSold));
    info.numberOfHouses = info.numberOfHouses - numberOfHousesSold;
}

void Properties::buyHotel(Player *owner, int propertyIndex)
{
    PropertyInfo & info = property->at(propertyIndex);
    std::ostringstream oss;
    
    std::vector<std::string>costPerProperty;
    int hotelQuantity;

    if(owner->transaction->bankAccountBalance() < info.hotelCost)
    {   
        oss << "buy a hotel on " << info.propertyName << "." << std::endl;
        oss << "1 hotel costs $" <<info.hotelCost << " and you have $" << owner->transaction->bankAccountBalance() << " in your bank account." << std::endl; 
        cantAfford(owner->getName(), oss.str());
        return;
    }

    if(info.numberOfHotels == maxNumberOfHotelsPerProperty) {
        std::cout << "You have bought the max number of hotels for " << info.propertyName << std::endl;
        return;
    } else {
        std::cout << "There are currently " << info.numberOfHotels << " hotels and you can have up to " << maxNumberOfHotelsPerProperty <<" hotels."<<std::endl; 
        std::cout << owner->getName() << ", you currently have $" << owner->transaction->bankAccountBalance() << "." << std::endl;
    }

    for(int i = info.numberOfHotels; i<maxNumberOfHotelsPerProperty; i++)
    {
        if(info.numberOfHotels == 0)
        {
            hotelQuantity = i+1;
        } else {
            hotelQuantity = i;
        }
        oss << hotelQuantity << " hotels will cost $" << hotelQuantity*info.hotelCost << std::endl;
        costPerProperty.push_back(oss.str());
        oss.str("");
    }

    int numberOfHotelsToPurchase = printList(costPerProperty, "How many hotels would you like to purchase?", 1);

    if(checkMoney(owner->transaction->bankAccountBalance(), info.hotelCost * numberOfHotelsToPurchase))
    {
        transaction(owner->getName(), info.propertyName, ", you have bought hotels on ");

        owner->transaction->withdrawal(info.hotelCost * numberOfHotelsToPurchase);
        info.numberOfHotels += numberOfHotelsToPurchase;

    } else {
        oss << "to purchase " << numberOfHotelsToPurchase << " hotels" << std::endl;
        cantAfford(owner->getName(), oss.str());
        int option = printList({"Yes", "No"}, "Would you like to try again?");

        switch (option)
        {
        case 1:
            buyHotel(owner, propertyIndex);
            break;
        
        case 2:
            std::cout << "No hotels were bought."  << owner->getName() << ", your turn is over" << std::endl;
            break;
        }
        
    }
}

void Properties::sellHotel(Player *owner, int propertyIndex)
{
    PropertyInfo & info = property->at(propertyIndex);
    std::ostringstream listOption;
    std::vector<std::string>list;
    int numberOfHotelsSold = 0;
    std::ostringstream printOption;

    printOption << "How many hotels would you like to sell?" << std::endl;

    for(int i = 0; i < info.numberOfHotels; i++)
    {
        listOption << i+1 << ". hotel for $" << calculateSellingCostHotel(propertyIndex, i+1);
        list.push_back(listOption.str());
        listOption.str("");
    }

    numberOfHotelsSold = printList(list, printOption.str(), 1);
    printOption.str("");
    printOption << " you have sold "<< numberOfHotelsSold << " Hotel on " << std::endl;
    transaction(owner->getName(), info.propertyName, printOption.str());
    owner->transaction->deposit(calculateSellingCostHotel(propertyIndex, numberOfHotelsSold));
    info.numberOfHotels = info.numberOfHotels - numberOfHotelsSold;
}


int Properties::calculateRent(int propertyIndex)
{
    PropertyInfo rent = property->at(propertyIndex);

    return ((rent.buyingCost / 5) + (rent.houseCost * rent.numberOfHouses) + (2 * rent.hotelCost * rent.numberOfHotels));
}

int Properties::calculateSellingCostProperty(int propertyIndex)
{
    PropertyInfo sell = property->at(propertyIndex);

    return (sell.buyingCost / 10) + calculateSellingCostHouse(propertyIndex, sell.numberOfHouses) + calculateSellingCostHotel(propertyIndex, sell.numberOfHotels);
}

int Properties::calculateSellingCostHotel(int propertyIndex, int numberOfHotels)
{
    PropertyInfo sell = property->at(propertyIndex);
    return (sell.hotelCost * numberOfHotels)/5;
}

int Properties::calculateSellingCostHouse(int propertyIndex, int numberOfHouses)
{
    PropertyInfo sell = property->at(propertyIndex);
    return (sell.houseCost * numberOfHouses)/10;
}

bool Properties::checkMoney(int playerWealth, int price)
{
    if(playerWealth >= price)
    {
        return true;
    }
    
    return false;
}

int Properties::printList(std::vector<std::string> list, std::string printOptions, bool indexIncluded)
{
    int size = list.size();
    std::string option = "0";
    bool validAns = 0;

    do
    {
        if(indexIncluded)
        {
            for(int i = 0; i< size; i++)
            {
                std::cout << list[i] << std::endl;
            }

        } else {
            std::cout << "------Menu------" << std::endl;
            for(int i = 0; i < size; i++)
            {
                std::cout << i+1 << ". " << list[i] << std::endl;
            }
        }

        if(TEST_MODE)
        {
            std::cout<<printOptions<<std::endl;
            option = testList->at(count);

            std::cout<<option << std::endl;
            count++;
            

        } else {
            std::cout<<printOptions<<std::endl;
            getline(std::cin, option);
        }
               

        if(std::stoi(option) < 1 || std::stoi(option) > size) {
            std::cout << "Please enter a valid number between 1 and " << size << std::endl;
        } else {
            validAns = 1;
        }
            
    }while(!validAns);


    
    return std::stoi(option);

}

void Properties::cantAfford(std::string name, std::string phrase)
{
    std::cout << name << ", you cannot afford to " << phrase << std::endl;
}

void Properties::transaction(std::string owner, std::string property, std::string phrase)
{
    std::cout << owner << phrase << property << std::endl;
}

void Properties::welcomeTo(std::string property, std::string phrase, int price)
{
    std::cout << "Welcome to "<< property <<"! " << phrase << " $" << price << std::endl;
}

int Properties::checkNumberOfProperties(Player *player_, std::string cantAffordOption, std::string noPropertiesOption, std::vector<std::string>printListOptions, std::string printListPhrase)
{
    if(player_->getPropertyLocations().size() > 0)
    {
        cantAfford(player_->getName(), cantAffordOption);
        std::cout << "Here are the following options:" << std::endl;
        return printList(printListOptions, printListPhrase);

    } else {
        cantAfford(player_->getName(), noPropertiesOption);
    }

    return 2;
}

void Properties::gameOver(Player *loser)
{
    std::vector<int>loserPropertys = loser->getPropertyLocations();
    for(int i = 0; i<loserPropertys.size(); i++)
    {
       initializePropertyOwner(property->at(loserPropertys[i]));
       loser->deleteProperty(loserPropertys[i]);
    }

    if(!TEST_MODE)
    {
        delete loser;
        loser = NULL;
    }
    
}

void Properties::setTestOptionSelectionList(std::vector<std::string>testList_)
{
    if(!testList)
    {
        testList->clear();
        delete testList;
        testList = NULL;
    }
    
    if(TEST_MODE)
    {
        count = 0;
        testList = new std::vector<std::string>(testList_);
    } else {
        std::cout << "You are not in testing mode " << std::endl;
    }
}