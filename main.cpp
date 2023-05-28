#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

#include "player.h"
#include "properties.h"
#include "test.h"
#include "game.h"


bool TEST_MODE = false;


int main(){

    //bool TEST_MODE = true;
    if(TEST_MODE) {
        Test cases = Test(TEST_MODE);
        return 0;
    } 

    Game g1 = Game("prop.csv");

    // for(int i = 0; i < numPlayers; i++)
    // {
    //     std::cout << playerVector->at(i).getName() << std::endl;
    // }


    




    return 0;
}