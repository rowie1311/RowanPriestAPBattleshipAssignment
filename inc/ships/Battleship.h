#pragma once
#include "Ship.h"
using namespace std;

class Battleship : public Ship{

  public:

    Battleship() : Ship(){
      
      this->size = 4;
      this->label = "B";
    
    }

};