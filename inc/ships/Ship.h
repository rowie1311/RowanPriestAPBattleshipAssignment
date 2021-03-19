#pragma once
#include <iostream>
using namespace std;

class Ship{

  protected:
    int size;
    int hits;
    string label;
    bool placed;

  public:
    Ship(){

      this->placed = false;
      this->hits = 0;

    }

    bool sunk(){

      if(this->hits >= this->size){
      
        return true;
      
      }else{
      
        return false;
      
      }

    }

    void registerHit(){

      this->hits++;

    }

    int getSize(){

      return this->size;

    }

    string getLabel(){

      return this->label;

    }

    void setPlaced(bool value){

      this->placed = value;

    }

};