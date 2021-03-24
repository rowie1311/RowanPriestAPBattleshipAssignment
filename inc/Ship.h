#pragma once
#include <iostream>
#include <fstream>
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

    Ship(int size, string label){

      this->placed = false;
      this->hits = 0;
      this->size = size;
      this->label = label;

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

    void setLabel(char value){

      this->label = value;

    }

    bool getPlaced(){

      return this->placed;
    
    }

    void setPlaced(bool value){

      this->placed = value;

    }

    bool exists(){

      if(this->size > 0){
        return true;
      }

      return false;

    }

};