#include <iostream>
#include <string>

#include "player.h"
#include "properties.h"




int main(){
    Properties::initializeProperties("prop.csv");

    Player *player1 = new Player("Trt", 0);
    Player *player2 = new Player("Gabb", 1);

    Properties::buyProperty(player1, 4);
    Properties::buyProperty(player2, 3);

    // Properties::printPropertyInfo(4);
    // Properties::printPropertyInfo(3);
    // Properties::printPropertyInfo(1);

    Properties::payRent(player2, player1, 3);

    std::cout << player1->getName() << std::endl;

    return 0;
}