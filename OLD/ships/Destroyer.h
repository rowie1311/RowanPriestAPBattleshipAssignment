#pragma once
#include "Ship.h"
#include <adaship_config.ini>
using namespace std;

class Destroyer : public Ship{

  public:

    Destroyer() : Ship(){
      
      this->size = 3;
      this->label = "D";
    
    }

};