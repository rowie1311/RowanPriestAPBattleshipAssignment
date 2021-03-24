#pragma once
#include "Ship.h"
#include <adaship_config.ini>
using namespace std;

class Submarine : public Ship{

  public:

    Submarine() : Ship(){
      
      this->size = 3;
      this->label = "S";
    
    }

};