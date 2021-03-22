#pragma once
#include "Ship.h"
using namespace std;

class Destroyer : public Ship{

  public:

    Destroyer() : Ship(){
      
      this->size = 3;
      this->label = "D";
    
    }

};