#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <iostream>
#include <string>
#include <vector>

#include "player.h"
#include "money.h"




class Properties
{
    public:

        static Properties* initializeProperties(std::string propertyFile);

        static void printPropertiesList();
        static void printPropertyInfo(int propertyIndex);
        
        static int getPropertyCost(int propertyIndex);
        static void printPropertyOwner();
        static int getPropertyOwnerIndex(int propertyIndex);

        static void buyProperty(Player *buyer, int propertyIndex);
        static void sellProperty(Player *seller, int propertyIndex, int required = 0);

        static void payRent(Player *owner, Player *renter, int propertyIndex);

        static void buyHouse(Player owner, int propertyIndex);
        static void buyHotel(Player owner, int propertyIndex);

        static void sellHouse(Player owner, int propertyIndex);
        static void sellHotel(Player owner, int propertyIndex);

        static void rentIncrease(int propertyIndex);

        static int calculateRent(int propertyIndex);
        static int calculateSellingCost(int propertyIndex);

    
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

        static bool checkMoney(int playerWealth, int price);
        static void initializePropertyOwner(PropertyInfo &info);
        
        static int printList(std::vector<std::string>list);
        static void cantAfford(std::string name, std::string phrase = "");
        static void transaction(std::string owner, std::string property, std::string phrase = ", you have bought ");
        static void printPropertiesList(std::vector<int>list);
        static void welcomeTo(std::string property, std::string phrase, int price);
    protected:    
        Properties(std::string propertyFile);




        
};

#endif