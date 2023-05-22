#include <iostream>
#include <string>

#include "player.h"
#include "properties.h"




int main(){
    Properties::initializeProperties("prop.csv");

    Player *player1 = new Player("Trt", 0);

    Properties::buyProperty(player1, 5);
    Properties::printPropertyInfo(5);

    return 0;
}