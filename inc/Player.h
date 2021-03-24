#pragma once
#include "Board.h"
#include "Ship.h"

#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
#include <time.h>  

class Player{
  
  private:
    string type;
    string name;
    
    int randomAttemptsLimit = 50;

    //The players ships
    Ship battleship;
    Ship carrier;
    Ship destroyer;
    Ship patrolBoat;
    Ship submarine;
    
    Board fleetBoard;
    Board targetBoard;
  
  public:

    Player(){};

    string handleShotFiredAt(int x, int y, string firingPlayersLabel){
      
			//cout << "X = " << x << "Y = " << y << endl;

      if(this->fleetBoard.isValidShot(x, y)){

				string coordinate = this->fleetBoard.convertNumberToLetters(x) + to_string(y + 1); //Convert X and Y Index to coordinate 

				cout << firingPlayersLabel << " fires at " << coordinate << "!" << endl;

        string targetedLocation = this->fleetBoard.getBoardPosition(x, y);
       
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
            
            cout << this->name << "'s battleship has been sunk!" << endl;
          
          }else{

            cout << "Hit !" << endl;

          }

          return this->fleetBoard.getHitMarker();

        }else if(targetedLocation == this->carrier.getLabel()){

          // Shot has hit carrier
          this->fleetBoard.addHitShot(x,y);
          this->carrier.registerHit();

          if(this->carrier.sunk()){
            
            cout << this->name << "'s carrier has been sunk!" << endl;
          
          }else{

            cout << "Hit !" << endl;

          }

          return this->fleetBoard.getHitMarker();

        }else if(targetedLocation == this->destroyer.getLabel()){
          
          // Shot has hit destroyer
          this->fleetBoard.addHitShot(x,y);
          this->destroyer.registerHit();
          
          if(this->destroyer.sunk()){
            
            cout << this->name << "'s destroyer has been sunk!" << endl;
          
          }else{

            cout << "Hit !" << endl;

          }
          
          return this->fleetBoard.getHitMarker();

        }else if(targetedLocation == this->patrolBoat.getLabel()){
          
          // Shot has hit patrol boat
          this->fleetBoard.addHitShot(x,y);
          this->patrolBoat.registerHit();

          if(this->patrolBoat.sunk()){
            
            cout << this->name << "'s patrol boat has been sunk!" << endl;
          
          }else{

            cout << "Hit !"<< endl;

          }

          return this->fleetBoard.getHitMarker();

        }else if(targetedLocation == this->submarine.getLabel()){
          
          // Shot has hit submarine
          this->fleetBoard.addHitShot(x,y);
          this->submarine.registerHit();
          
          if(this->submarine.sunk()){

           cout << this->name << "'s submarine has been sunk!" << endl;
          
          }else{

            cout << "Hit !"<< endl;

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

      if(this->getShipCount() > 0){

        return true;

      }

      return false;

    }



    void randomlyPlaceRemainingShips(){

      while(this->battleship.getPlaced() == false && this->battleship.exists()){
				
				int xIndex = this->randomXIndex();
				int yIndex = this->randomYIndex();
				string direction = this->randomDirection();

				//cout << "Attempting to place Battleship at (" << xIndex << ", " << yIndex << ") Direction: " << direction << endl;

				if(this->fleetBoard.placeShip(xIndex, yIndex, direction, this->battleship)){

					this->battleship.setPlaced(true);
				
				}

      }

      while(this->carrier.getPlaced() == false && this->carrier.exists()){
        
				int xIndex = this->randomXIndex();
				int yIndex = this->randomYIndex();
				string direction = this->randomDirection();

				//cout << "Attempting to place Carrier at (" << xIndex << ", " << yIndex << ") Direction: " << direction << endl;

				if(this->fleetBoard.placeShip(xIndex, yIndex, direction, this->carrier)){

					this->carrier.setPlaced(true);
				
				}

      }

      while(this->destroyer.getPlaced() == false && this->destroyer.exists()){

				int xIndex = this->randomXIndex();
				int yIndex = this->randomYIndex();
				string direction = this->randomDirection();

				//cout << "Attempting to place Destroyer at (" << xIndex << ", " << yIndex << ") Direction: " << direction << endl;

				if(this->fleetBoard.placeShip(yIndex,  yIndex, direction, this->destroyer)){

					this->destroyer.setPlaced(true);
				
				}
 
      }

      while(this->patrolBoat.getPlaced() == false && this->patrolBoat.exists()){
        
				int xIndex = this->randomXIndex();
				int yIndex = this->randomYIndex();
				string direction = this->randomDirection();

				//cout << "Attempting to place Patrol Boat at (" << xIndex << ", " << yIndex << ") Direction: " << direction << endl;

				if(this->fleetBoard.placeShip(xIndex, yIndex, direction, this->patrolBoat)){

					this->patrolBoat.setPlaced(true);
				
				}

      }

      while(this->submarine.getPlaced() == false && this->submarine.exists()){

				int xIndex = this->randomXIndex();
				int yIndex = this->randomYIndex();
				string direction = this->randomDirection();
				
				//cout << "Attempting to place Submarine at (" << xIndex << ", " << yIndex << ") Direction: " << direction << endl;

				if(this->fleetBoard.placeShip(xIndex, yIndex, direction, this->submarine)){

					this->submarine.setPlaced(true);
				
				}

      }

    }

		int randomXIndex(){

			//Need to do seed in nano seconds (otherwise multiple attempts are made to place ship invalidly as time(null) is too slow)
			struct timespec ts;
			clock_gettime(CLOCK_MONOTONIC, &ts);

			/* using nano-seconds instead of seconds */
			srand((time_t)ts.tv_nsec);

			return rand() % (this->fleetBoard.getWidth());

		}

		int randomYIndex(){

			//Need to do seed in nano seconds (otherwise multiple attempts are made to place ship invalidly as time(null) is too slow)
			struct timespec ts;
			clock_gettime(CLOCK_MONOTONIC, &ts);

			/* using nano-seconds instead of seconds */
			srand((time_t)ts.tv_nsec);

			return rand() % (this->fleetBoard.getHeight());

		}

		string randomDirection(){
			
			//Need to do seed in nano seconds (otherwise multiple attempts are made to place ship invalidly as time(null) is too slow)
			struct timespec ts;
			clock_gettime(CLOCK_MONOTONIC, &ts);

			/* using nano-seconds instead of seconds */
			srand((time_t)ts.tv_nsec);
			
			int direction = rand() % 50;

			if(direction >= 25){
				
				return "h";

			}else{
				
				return "v";

			}

		}

    void initializeBoards(int width, int height){
      
      //Set up the boards
      this->fleetBoard = Board(width, height);
      this->targetBoard = Board(width, height);

    }


    void initializeShip(int size, string name){

      if(name == "battleship"){

        this->battleship = Ship(size, "B");

      }else if(name == "carrier"){

        this->carrier = Ship(size, "C");

      }else if(name == "destroyer"){

        this->destroyer = Ship(size, "D");

      }else if(name == "patrolBoat"){

        this->patrolBoat = Ship(size, "P");

      }else if(name == "submarine"){

        this->submarine = Ship(size, "S");

      }

    }

		bool shipsPlaced(){

			if(this->battleship.exists() && this->battleship.getPlaced() == false){
				
				return false;
			
			}

			if(this->carrier.exists() && this->carrier.getPlaced() == false){
				
				return false;
			
			}

			if(this->destroyer.exists() && this->destroyer.getPlaced() == false){
				
				return false;
			
			}

			if(this->patrolBoat.exists() && this->patrolBoat.getPlaced() == false){

				return false;

			}

			if(this->submarine.exists() && this->submarine.getPlaced() == false){
				
				return false;
			
			}

			return true;

		}

		void printFleetStatus(){

			if(this->battleship.exists()){

				if(this->battleship.getPlaced()){

					cout << "Battleship - Placed" << endl;
				
				}else{
					
					cout << "Battleship - Not Placed" << endl;
				
				}
			
			}

			if(this->carrier.exists()){

				if(this->carrier.getPlaced()){

					cout << "Carrier - Placed" << endl;
				
				}else{
					
					cout << "Carrier - Not Placed" << endl;
				
				}
			
			}

			if(this->destroyer.exists()){

				if(this->destroyer.getPlaced()){

					cout << "Destroyer - Placed" << endl;
				
				}else{
					
					cout << "Destroyer - Not Placed" << endl;
				
				}
			
			}

			if(this->patrolBoat.exists()){

				if(this->patrolBoat.getPlaced()){

					cout << "Patrol Boat - Placed" << endl;
				
				}else{
					
					cout << "Patrol Boat - Not Placed" << endl;
				
				}
			
			}

			if(this->submarine.exists()){

				if(this->submarine.getPlaced()){

					cout << "Submarine - Placed" << endl;
				
				}else{
					
					cout << "Submarine - Not Placed" << endl;
				
				}
			
			}

			cout << endl;

		}

		int getShipCount(){

			int count = 0;

			if(this->battleship.exists()){

				if(this->battleship.sunk() == false){

					count++;

				}
			
			}

			if(this->carrier.exists()){

				if(this->carrier.sunk() == false){

					count++;

				}
			
			}

			if(this->destroyer.exists()){

				if(this->destroyer.sunk() == false){

					count++;

				}
			
			}

			if(this->patrolBoat.exists()){

				if(this->patrolBoat.sunk() == false){

					count++;

				}
			
			}

			if(this->submarine.exists()){

				if(this->submarine.sunk() == false){

					count++;

				}
			
			}

			return count;

		}


    Ship getBattleship(){

      return this->battleship;

    }

    void setBattleship(Ship value){

      this->battleship = value;

    }

    Ship getCarrier(){

      return this->carrier;

    }

    void setCarrier(Ship value){

      this->carrier = value;

    }

    Ship getDestroyer(){

      return this->destroyer;

    }

    void setDestroyer(Ship value){

      this->destroyer = value;

    }

    Ship getPatrolBoat(){

      return this->patrolBoat;

    }

    void setPatrolBoat(Ship value){

      this->patrolBoat = value;

    }

    Ship getSubmarine(){

      return this->submarine;

    }

    void setSubmarine(Ship value){

      this->submarine = value;

    }

    Board getFleetBoard(){

      return this->fleetBoard;

    }

    void setFleetBoard(Board value){

      this->fleetBoard = value;

    }

    Board getTargetBoard(){

      return this->targetBoard;

    }

    void setTargetBoard(Board value){

      this->targetBoard = value;

    }
		
    void setType(string value){

      this->type = value;
    
    }

		string getType(){

			return this->type;

		}

		string getName(){

      return this->name;

    }

    void setName(string value){

      this->name = value;

    }

};