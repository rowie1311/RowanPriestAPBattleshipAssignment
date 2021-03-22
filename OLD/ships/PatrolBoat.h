#pragma once
#include "Ship.h"
using namespace std;

class PatrolBoat : public Ship{

  public:

    PatrolBoat() : Ship(){
      
      this->size = 2;
      this->label = "P";
    
    }

};