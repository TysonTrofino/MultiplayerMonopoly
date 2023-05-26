#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

#include "player.h"
#include "properties.h"
#include "test.h"


bool TEST_MODE = true;


int main(){

    if(TEST_MODE) {
        Test cases;
        

    } else {


        Properties::initializeProperties("prop.csv");

        Player *player1 = new Player("Trt", 0);
        Player *player2 = new Player("Gabb", 1);

        Properties::buyProperty(player1, 2);
        //Properties::buyProperty(player1, 1);

        Properties::buyHouse(player1, 2);

        Properties::buyProperty(player2, 3);
        
        

        //Properties::printPropertyInfo(4);
        // Properties::printPropertyInfo(3);
        // Properties::printPropertyInfo(1);

        Properties::payRent(player2, player1, 3);

        Properties::printPropertyInfo({1,2,3});

        //std::cout << player1->getName() << std::endl;
    }

    return 0;
}