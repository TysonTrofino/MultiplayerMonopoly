#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <iostream>
#include <string>
#include <vector>

#include "player.h"
#include "money.h"


extern int maxNumberOfHousesPerProperty;
extern int maxNumberOfHotelsPerProperty;

class Properties
{
    public:

        static Properties* initializeProperties(std::string propertyFile, bool TEST_MODE = false);

        static void printPropertiesList();
        static void printPropertyInfo(std::vector<int> propertyIndexs);
        
        static int getPropertyCost(int propertyIndex);
        static void printPropertyOwner();
        static int getPropertyOwnerIndex(int propertyIndex);
        static int getNumberOfHouses(int propertyIndex);
        static int getNumberOfHotels(int propertyIndex);
        static std::string getOwnerName(int propertyIndex);

        static void buyProperty(Player *buyer, int propertyIndex);
        static void sellProperty(Player *seller, std::vector<int>propertiesList);

        static void payRent(Player *owner, Player *renter, int propertyIndex);

        static void buyHouse(Player *owner, int propertyIndex);
        static void buyHotel(Player *owner, int propertyIndex);

        static void sellHouse(Player *owner, int propertyIndex);
        static void sellHotel(Player *owner, int propertyIndex);

        static void rentIncrease(int propertyIndex);

        static int calculateRent(int propertyIndex);
        static int calculateSellingCostProperty(int propertyIndex);
        static int calculateSellingCostHotel(int propertyIndex, int numberOfHotels);
        static int calculateSellingCostHouse(int propertyIndex, int numberOfHouses);
        
        static void setTestOptionSelectionList(std::vector<std::string> testList_);

    
    private:
        struct PropertyInfo
        {
            std::string propertyName;
            std::string owner;
            int ownerIndex;
            int buyingCost;
            int houseCost;
            int hotelCost;
            int numberOfHouses;
            int numberOfHotels;
        };
        
        static Properties* instance;
        static std::vector<PropertyInfo>*property;
        static bool TEST_MODE;
        static std::vector<std::string>* testList;
        static int count;

        static bool checkMoney(int playerWealth, int price);
        static void initializePropertyOwner(PropertyInfo &info);
        
        static int printList(std::vector<std::string>list, std::string printOptions, bool indexIncluded = 0);
        static void cantAfford(std::string name, std::string phrase = "");
        static void transaction(std::string owner, std::string property, std::string phrase = ", you have bought ");
        static int printPropertiesList(std::vector<int>list, std::string printOptions = "", bool notSelling = false);
        static void welcomeTo(std::string property, std::string phrase, int price);

        static int checkNumberOfProperties(Player *player_, std::string cantAffordOption, std::string noPropertiesOption, std::vector<std::string>printListOptions, std::string printListPhrase="");
        
    
    protected:    
        Properties(std::string propertyFile, bool TEST_MODE_);




        
};

#endif