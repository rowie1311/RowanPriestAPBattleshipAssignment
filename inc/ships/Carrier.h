#pragma once
#include "Ship.h"
using namespace std;

class Carrier : public Ship{

  public:

    Carrier() : Ship(){
      
      this->size = 5;
      this->label = "C";
    
    }

};