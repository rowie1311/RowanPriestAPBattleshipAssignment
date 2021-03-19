#pragma once
#include "Board.h"
#include "ships/Battleship.h" 
#include "ships/Carrier.h" 
#include "ships/Destroyer.h" 
#include "ships/PatrolBoat.h" 
#include "ships/Submarine.h"

#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>

class Player{
  
  private:
    char type;
    string name;
    int shipCount = 5;

    //The players ships
    Battleship battleship;
    Carrier carrier;
    Destroyer destroyer;
    PatrolBoat patrolBoat;
    Submarine submarine;
    
    Board fleetBoard;
    Board targetBoard;
  
  public:
    Player(char type, string name){
      
      this->type = type;
      this->name = name;

      //Set up the boards
      this->fleetBoard = Board(10, 10);
      this->targetBoard = Board(10, 10);

    }

    string handleShotFiredAt(int x, int y){
      
      if(this->fleetBoard.isValidShot(x,y)){

        string targetedLocation = this->fleetBoard.getBoardPosition(x,y);
       
        //Check where on the board was hit
        if(targetedLocation == this->fleetBoard.getEmptyMarker()){
          
          // Shot has missed
          this->fleetBoard.addMissedShot(x,y);

          cout << "Miss !" << endl;

          //Return the missed marker for the other player's target board
          return this->fleetBoard.getMissMarker();
        
        }else if(targetedLocation == this->battleship.getLabel()){

          // Shot has hit battleship
          this->fleetBoard.addHitShot(x,y);
          this->battleship.registerHit();

          if(this->battleship.sunk()){
            
            this->shipCount--;
            cout << "You sunk my battleship !" << endl;
          
          }else{

            cout << "Hit !" << endl;

          }

          return this->fleetBoard.getHitMarker();

        }else if(targetedLocation == this->carrier.getLabel()){

          // Shot has hit carrier
          this->fleetBoard.addHitShot(x,y);
          this->carrier.registerHit();

          if(this->carrier.sunk()){
            
            this->shipCount--;
            cout << "You sunk my carrier !" << endl;
          
          }else{

            cout << "Hit !" << endl;

          }

          return this->fleetBoard.getHitMarker();

        }else if(targetedLocation == this->destroyer.getLabel()){
          
          // Shot has hit destroyer
          this->fleetBoard.addHitShot(x,y);
          this->destroyer.registerHit();
          
          if(this->destroyer.sunk()){
            
            this->shipCount--;
            cout << "You sunk my destroyer !" << endl;
          
          }else{

            cout << "Hit !" << endl;

          }
          
          return this->fleetBoard.getHitMarker();

        }else if(targetedLocation == this->patrolBoat.getLabel()){
          
          // Shot has hit patrol boat
          this->fleetBoard.addHitShot(x,y);
          this->patrolBoat.registerHit();

          if(this->patrolBoat.sunk()){
            
            this->shipCount--;
            cout << "You sunk my patrol boat !";
          
          }else{

            cout << "Hit !";

          }

          return this->fleetBoard.getHitMarker();

        }else if(targetedLocation == this->submarine.getLabel()){
          
          // Shot has hit submarine
          this->fleetBoard.addHitShot(x,y);
          this->submarine.registerHit();
          
          if(this->submarine.sunk()){

            this->shipCount--;
            cout << "You sunk my submarine !";
          
          }else{

            cout << "Hit !";

          }
          
          return this->fleetBoard.getHitMarker();

        }
        
      }
      
      return "invalid";

    }

    bool recordShotFired(int x, int y, string marker){
      
      return this->targetBoard.setBoardPosition(x, y, marker);
      
    }

    bool isAlive(){

      if(this->shipCount > 0){

        return true;

      }

      return false;

    }

};