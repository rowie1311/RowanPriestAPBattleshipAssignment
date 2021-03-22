#pragma once
#include "Ship.h" //includes contents from ship.h file 
using namespace std;

class Battleship : public Ship{ //creates class 'Battleship' from parent class 'ship'

  public:

    Battleship() : Ship(){
      
      this->size = 4;
      this->label = "B";
    
    }

};