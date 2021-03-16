#pragma once
#include "Ship.h"
using namespace std;

class Submarine : public Ship{

  public:

    Submarine() : Ship(){
      
      this->size = 3;
      this->label = "S";
    
    }

};