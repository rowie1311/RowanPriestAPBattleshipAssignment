#include "Board.h"
#include "Player.h"
#include "Ship.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <cstring>
#include <stdlib.h>
using namespace std;

class Game{
  private:

    string gameState = "start";
    string gameMode;
    string gameOpponent;

    int activePlayer;
    Player player1;
    Player player2;

    int boardWidth = 10;
    int boardHeight = 10;

    int battleshipSize = 0;
    int carrierSize = 0;
    int destroyerSize = 0;
    int patrolBoatSize = 0;
    int submarineSize = 0;

    string action;
    string inputCoordinate;
    string inputDirection;

		int currentShots;
		string currentPlayerLabel;
		string currentPlayerType;
		string winningPlayerLabel;

    Board tempBoard;
    Ship tempShip;
    Player tempPlayer;


		//Simulated pause for the program waiting for a user to press a key
    void pause(){
			cout << endl << endl;
      cout << "Please press [Enter] to continue . . ." << endl << endl;
			cout << endl << endl;
      cin.clear();
      cin.ignore();

    }

    void quit(){
      
      cout << "Bye !" << endl << endl;

      this->gameState = "exit";

    }

		string handlePFCoordinateInput(string command, int currentPlayer){

      //Check command is valid coordinate 
      if(this->player1.getFleetBoard().isValidCoordinateFormat(command)){
        
        return "inputDirection";
      
      }

      int response = this->handlePFGeneralInput(command, currentPlayer);

      if(response == 0){
        
        //Stay on input coordinate
        return "inputCoordinate";

      }else if(response == 1){

        //Auto selected no need to take any more inputs
        return "auto";
      
      }else if(response == 2){

        //Reset
        return "reset";

      }else if(response == -1){

        //Quit
        return "exit";

      }

      return "error";

    }

    string handlePFDirectionInput(string command, int currentPlayer){

      //Check command is valid coordinate 
      if(command == "h" || "v"){
        
        return "placeShip";
      
      }

      int response = this->handlePFGeneralInput(command, currentPlayer);

      if(response == 0){
        
        //Stay on input direction
        return "inputDirection";

      }else if(response == 1){

        //Random selected no need to take any more inputs
        return "auto";
      
      }else if(response == 2){

        //Reset
        return "reset";

      }else if(response == -1){

        //Quit
        return "exit";

      }

      return "error";

    }

    int handlePFGeneralInput(string command, int currentPlayer){

      //Check command is valid coordinate 
      if(command == "auto-place"){
        
				cout << "Auto Placing Remaining Ships..." << endl << endl;

        if(currentPlayer == 1){
          
          this->player1.randomlyPlaceRemainingShips();
        
        }else{
          
          this->player2.randomlyPlaceRemainingShips();
        
        }

        return 1;

      }else if(command == "see fleet"){

        if(currentPlayer == 1){

          this->player1.getFleetBoard().printBoard();
        
        }else{
          
          this->player2.getFleetBoard().printBoard();
        
        }

        return 0;

      }else if(command == "help"){

        this->printPlaceFleetHelp();
        return 0;

      }else if(command == "fleet status"){

        if(currentPlayer == 1){

					cout << "Player 1's Current Fleet Status:" << endl;

          this->player1.printFleetStatus();
        
        }else{

          cout << "Player 2's Current Fleet Status:" << endl;
          
					this->player2.printFleetStatus();
        
        }
				
        return 0;

      }else if(command == "reset"){

        return 2;

      }else if(command == "quit"){

        return -1;

      }else{

        cout << "Invalid command, please try again." << endl << endl;
        return 0;

      }


    }

    void printPlaceFleetHelp(){

      cout << "General commands:" << endl
      << "\"auto-place\" - Places Remaining Ships at Random" << endl
      << "\"reset\" - Resets ships to be placed again" << endl
      << "\"fleet status\" - Displays which ships have been placed and which ones haven't" << endl
      << "\"see fleet\" - Displays Fleet Board" << endl
      << "\"quit\" - Quits the game" << endl << endl;

    }

    string getInput(){
      
      string input = "";
      getline(cin, input);
      cout << endl;

      return input;

    }

    void setGameMode(int value){

      this->gameMode = value;
    
    }

    string getGameState(){

      return this->gameState;

    }

    void resetPlayer1(){
    
      //Build player 1's boards
      this->player1.initializeBoards(this->boardWidth, this->boardHeight);

      //Create player 1's ships
      this->player1.initializeShip(this->battleshipSize, "battleship");
      this->player1.initializeShip(this->carrierSize, "carrier");
      this->player1.initializeShip(this->destroyerSize, "destroyer");
      this->player1.initializeShip(this->patrolBoatSize, "patrolBoat");
      this->player1.initializeShip(this->submarineSize, "submarine");
      
    }

    void resetPlayer2(){
      
      //Build player 2's boards
      this->player2.initializeBoards(this->boardWidth, this->boardHeight);

      //Create player 2's ships
      this->player2.initializeShip(this->battleshipSize, "battleship");
      this->player2.initializeShip(this->carrierSize, "carrier");
      this->player2.initializeShip(this->destroyerSize, "destroyer");
      this->player2.initializeShip(this->patrolBoatSize, "patrolBoat");
      this->player2.initializeShip(this->submarineSize, "submarine");
      
    }

		void autoFire(){

			while(true){

				int xIndex = this->player1.randomXIndex();
				int yIndex = this->player1.randomYIndex();
				string result;

				if(this->activePlayer == 1){
					
					result = this->player2.handleShotFiredAt(xIndex, yIndex, this->player1.getName());

				}else{

					result = this->player1.handleShotFiredAt(xIndex, yIndex, this->player2.getName());

				}

				if(result != "invalid"){

					if(this->activePlayer == 1){
					
						this->player1.recordShotFired(xIndex, yIndex, result);

					}else{

						this->player2.recordShotFired(xIndex, yIndex, result);

					}

					//Successful shot break out of the loop otherwise attempt new shot
					break;

				}

			}

			cout << endl;

		}

		bool loadConfig(string fileName){

			string rowString;
			string lineType;
			
			string boardWidthString;
			string boardHeightString;
			
			string shipType;
			string shipSizeString;
			
			ifstream configFile(fileName);

			if(configFile.is_open()){
				
				while(getline(configFile, rowString)){
					
					stringstream row(rowString);
					
					getline(row, lineType, ':');

					if(lineType == "Board"){
						
						//Grab the board width and height
						getline(row, boardWidthString, 'x');
						getline(row, boardHeightString, '\n');
						
						//Store the width and height
						this->boardWidth = stoi(boardWidthString);
						this->boardHeight = stoi(boardHeightString);

					}

					if(lineType == "Boat"){
						
						getline(row, shipType, ',');
						getline(row, shipSizeString, '\n');

						if(shipType == "Battleship"){

							this->battleshipSize = stoi(shipSizeString);

						}else if(shipType == "Carrier"){

							this->carrierSize = stoi(shipSizeString);

						}else if(shipType == "Destroyer"){
						
							this->destroyerSize = stoi(shipSizeString);

						}else if(shipType == "Patrol Boat"){
						
							this->patrolBoatSize = stoi(shipSizeString);

						}else if(shipType == "Submarine"){

							this->submarineSize = stoi(shipSizeString);

						}

					}
						
				}

				configFile.close();

			}else{

				return false;

			}

			return true;

		}

  public:
    //Default constructor
    Game(){};

		//Run the game and get the game mode
    int run(){
      
			//Read file and get settings
			if(this->loadConfig("adaship_config.ini") == false){

				cout << "Error reading config !" << endl;
				
				this->pause();

				cout << "Forced to exit" << endl << endl;

				return 0;

			}

      //Set the current gamestate
      this->gameState = "selectMode";

      //Output start message
			cout << "---------------------------------------------------------" << endl << endl;
      
			cout << "Welcome to Ada Ships !" << endl 
      << "A Battle of Boats, Brains and Bravery!" << endl << endl;

      cout << "---------------------------------------------------------" << endl << endl;

      while(true){

        //User selects the game mode
        while(this->gameState == "selectMode"){
          
          cout << "Please select a game mode (to select a game mode input the corresponding number):" << endl << endl
          << "1. Classic Battleships - 1 Shot Per turn, you better make it count!" << endl
          << "2. Salvo Mode - Each turn, get a shot per ship you have left standing. The more ships you lose the harder it gets." << endl
          << "3. Quit - Live to fight another day." << endl << endl;

          string input = this->getInput();
      
          if(input == "1"){
            
            //Classic Mode selected
            cout << endl << "Classic battleships selected" << endl << endl;
            this->gameMode = "classic";//set game mode to classic

            //Move game onto select opponent
            this->gameState = "selectOpponent";

          }else if(input == "2"){
            
            //Salvo mode selected
            cout << endl << "Salvo mode selected" << endl << endl;
            this->gameMode = "salvo";//set game mode to salvo mode

            //Move game onto select opponent
            this->gameState = "selectOpponent";

          }else if(input == "3"){
            
            this->gameState = "quit";

          }else{
            
            //Invalid input
            cout << "Invalid input, please try again." << endl << endl;

          }

        }

        while(this->gameState == "selectOpponent"){

          cout << "Please select an opponent:" << endl << endl
          << "1. VS Computer - Play against the formidable admiral Crunch" << endl
          << "2. VS Human - Play with a friend" << endl
          << "3. Change Game Mode - Made a mistake don't worry we got you" << endl
          << "4. Retreat (Quit) - Live to fight another day." << endl << endl;

          string input = this->getInput();
      
          if(input == "1"){
            
            //VS Computer selected
            cout << endl << "VS Computer Selected" << endl << endl;
            this->gameOpponent = "computer";//set game mode to classic
						this->player2.setName("Admiral Crunch");
            
						//Move game onto select opponent
            this->gameState = "confirmSettings";

          }else if(input == "2"){
            
            //VS Human selected
            cout << endl << "VS Human selected" << endl << endl;
            this->gameOpponent = "human";//set game mode to salvo mode
						this->player2.setName("Player 2");

            //Move game onto select opponent
            this->gameState = "confirmSettings";

          }else if(input == "3"){
            
            //Reselect Gamemode selected
            cout << endl << "Reselect Game Mode" << endl << endl;

            //Move game back to select gameMode
            this->gameState = "selectMode";

          }else if(input == "4"){
            
            //Quit selected
            cout << endl << "Retreat - What a shame you had so much promise, farewell." << endl << endl;
            this->pause();
            
            return 0; 

          }else{
            
            //Invalid input
            cout << "Invalid input, please try again." << endl << endl;

          }

        }

        while(this->gameState == "confirmSettings"){

          cout << "Please confirm your chosen settings (y for Yes, n for No):" << endl << endl;

          if(this->gameMode == "classic"){

            cout << "Game Mode: Classic" << endl;
          
          }else if(this->gameMode == "salvo"){

            cout << "Game Mode: Salvo" << endl;

          }else{

            cout << "Unknown Error" << endl;
            this->pause();
            return 0; 

          }

          if(this->gameOpponent == "computer"){

            cout << "Opponent: Computer (Admiral crunch)" << endl;
          
          }else if(this->gameOpponent == "human"){

            cout << "Opponent: Human" << endl;

          }else{

            cout << "Unknown Error" << endl;
            this->pause();
            return 0; 
            
          }

          cout << endl << endl;

          string input = this->getInput();

          if(input == "y"){
            
            //Settings Confirmed
            cout << "Excellent !" << endl << endl;

            //Move game onto select opponent
            this->gameState = "setup";

          }else if(input == "n"){
            
            //Settings have not been confirmed
            this->gameMode = "";//set game mode default
            this->gameOpponent = "";//set game opponent default

            //Move game onto select opponent
            this->gameState = "selectMode";

          }else{
            
            //Invalid input
            cout << "Invalid input, please try again." << endl << endl;

          }

        }

        while(this->gameState == "setup"){
          
          //Set player 1 to Human
          this->player1.setType("human");

					this->player1.setName("Player 1");
          
          //Reset player 1
          this->resetPlayer1();

          //Set player 2 to selected opponent type
          this->player2.setType(this->gameOpponent);
          
          //Reset player 2
          this->resetPlayer2();

          this->gameState = "player1PlaceFleet";

        }

        if(this->gameState == "player1PlaceFleet"){

          cout << "---------------------------------------------------------" << endl << endl;
          
					cout << "Player 1 please position your fleet:" << endl
          << "(Note: for help at any time, type \"help\")" << endl << endl;

					cout << "---------------------------------------------------------" << endl << endl;

          //Player 1 inputs coordinates to place their fleet
          while(this->gameState == "player1PlaceFleet"){

            //PLACE PLAYER 1 - BATTLESHIP
            //While the battleship is not placed ask for input so it can be placed
            while(this->player1.getBattleship().exists() && this->player1.getBattleship().getPlaced() == false){

              cout << "Player 1 - Please place your Battleship (Size: " << this->player1.getBattleship().getSize() << ")" << endl << endl;
              
              this->action = "inputCoordinate";

              //Ask for a cordinate first and keep asking until a valid coordinate has been provided
              while(this->action == "inputCoordinate"){ 
                
                cout << "Input a starting Coordinate for your Battleship (Size: " << this->player1.getBattleship().getSize() << ") (e.g. A4) : ";
                
                this->inputCoordinate = this->getInput();

                //Handle the input coordinate and set action to the appropriate value
                this->action = this->handlePFCoordinateInput(inputCoordinate, 1);

              }

              //Ask for a direction next and keep asking until a valid direction has been provided
              while(this->action == "inputDirection"){ 
                
                cout << "Input a direction for your Battleship (Size: " << this->player1.getBattleship().getSize() << ") (e.g. \"h\" or \"v\") : ";

                this->inputDirection = this->getInput();

                //Handle the input orinetation and set action to the appropriate value
                this->action = this->handlePFDirectionInput(inputDirection, 1);

              }

              //Quit
              if(this->action == "quit"){
                
                this->gameState = "quit";

              }

              //Reset
              if(this->action == "reset"){
                
                this->resetPlayer1();
                cout << "Player 1 Ships Reset." << endl << endl;

              }

              //Both inputs accepted - attempt to place the ship
              if(this->action == "placeShip"){
                
                //Get the board and ship from player 1
                this->tempBoard = this->player1.getFleetBoard();
                this->tempShip = this->player1.getBattleship();

                //Convert inputCoordinate into valid X and Y indexs
                int xIndex = this->tempBoard.convertCoordinateToIndex(inputCoordinate, 'x');
                int yIndex = this->tempBoard.convertCoordinateToIndex(inputCoordinate, 'y');

                //Place the ship
                bool response = this->tempBoard.placeShip(xIndex, yIndex, this->inputDirection, this->tempShip);

                //Make sure the ship has been placed successfully
                if(response){
                  
                  //Set ship to placed
                  this->tempShip.setPlaced(true);
                  
                  //Update player 1's fleet board and ship with the new temp variables
                  this->player1.setFleetBoard(tempBoard);
                  this->player1.setBattleship(tempShip);

                  cout << "Battleship placed successfully." << endl << endl;

                  this->player1.getFleetBoard().printBoard();
                
                }else{
                  
                  cout << "Invalid Ship Placement, please try again." << endl << endl;

                }

              }

            }

            //PLACE PLAYER 1 - Carrier
            //While the carrier is not placed ask for input so it can be placed
            while(this->player1.getCarrier().exists() && this->player1.getCarrier().getPlaced() == false){

              cout << "Player 1 - Please place your Carrier (Size: " << this->player1.getCarrier().getSize() << ")" << endl << endl;
              
              this->action = "inputCoordinate";

              //Ask for a cordinate first and keep asking until a valid coordinate has been provided
              while(this->action == "inputCoordinate"){ 
                
                cout << "Input a starting Coordinate for your Carrier (Size: " << this->player1.getCarrier().getSize() << ") (e.g. A4) : ";
                
                this->inputCoordinate = this->getInput();

                //Handle the input coordinate and set action to the appropriate value
                this->action = this->handlePFCoordinateInput(inputCoordinate, 1);

              }

              //Ask for a direction next and keep asking until a valid direction has been provided
              while(this->action == "inputDirection"){ 
                
                cout << "Input a direction for your Battleship (Size: " << this->player1.getCarrier().getSize() << ") (e.g. \"h\" or \"v\") : ";

                this->inputDirection = this->getInput();

                //Handle the input orinetation and set action to the appropriate value
                this->action = this->handlePFDirectionInput(inputDirection, 1);

              }

              //Quit
              if(this->action == "quit"){
                
                this->gameState = "quit";

              }

              //Reset
              if(this->action == "reset"){
                
                this->resetPlayer1();
                cout << "Player 1 Ships Reset." << endl << endl;

              }

              //Both inputs accepted - attempt to place the ship
              if(this->action == "placeShip"){
                
                //Get the board and ship from player 1
                this->tempBoard = this->player1.getFleetBoard();
                this->tempShip = this->player1.getCarrier();

                //Convert inputCoordinate into valid X and Y indexs
                int xIndex = this->tempBoard.convertCoordinateToIndex(inputCoordinate, 'x');
                int yIndex = this->tempBoard.convertCoordinateToIndex(inputCoordinate, 'y');

                //Place the ship
                bool response = this->tempBoard.placeShip(xIndex, yIndex, this->inputDirection, this->tempShip);

                //Make sure the ship has been placed successfully
                if(response){
                  
                  //Set ship to placed
                  this->tempShip.setPlaced(true);
                  
                  //Update player 1's fleet board and ship with the new temp variables
                  this->player1.setFleetBoard(tempBoard);
                  this->player1.setCarrier(tempShip);

                  cout << "Carrier placed successfully." << endl << endl;

                  this->player1.getFleetBoard().printBoard();
                
                }else{
                  
                  cout << "Invalid Ship Placement, please try again." << endl << endl;

                }

              }

            }

            //PLACE PLAYER 1 - Destroyer
            //While the Destroyer is not placed ask for input so it can be placed
            while(this->player1.getDestroyer().exists() && this->player1.getDestroyer().getPlaced() == false){

              cout << "Player 1 - Please place your Destroyer (Size: " << this->player1.getDestroyer().getSize() << ")" << endl << endl;
              
              this->action = "inputCoordinate";

              //Ask for a cordinate first and keep asking until a valid coordinate has been provided
              while(this->action == "inputCoordinate"){ 
                
                cout << "Input a starting Coordinate for your Destroyer (Size: " << this->player1.getDestroyer().getSize() << ") (e.g. A4) : ";
                
                this->inputCoordinate = this->getInput();

                //Handle the input coordinate and set action to the appropriate value
                this->action = this->handlePFCoordinateInput(inputCoordinate, 1);

              }

              //Ask for a direction next and keep asking until a valid direction has been provided
              while(this->action == "inputDirection"){ 
                
                cout << "Input a direction for your Destroyer (Size: " << this->player1.getDestroyer().getSize() << ") (e.g. \"h\" or \"v\") : ";

                this->inputDirection = this->getInput();

                //Handle the input orinetation and set action to the appropriate value
                this->action = this->handlePFDirectionInput(inputDirection, 1);

              }

              //Quit
              if(this->action == "quit"){
                
                this->gameState = "quit";

              }

              //Reset
              if(this->action == "reset"){
                
                this->resetPlayer1();
                cout << "Player 1 Ships Reset." << endl << endl;

              }

              //Both inputs accepted - attempt to place the ship
              if(this->action == "placeShip"){
                
                //Get the board and ship from player 1
                this->tempBoard = this->player1.getFleetBoard();
                this->tempShip = this->player1.getDestroyer();

                //Convert inputCoordinate into valid X and Y indexs
                int xIndex = this->tempBoard.convertCoordinateToIndex(inputCoordinate, 'x');
                int yIndex = this->tempBoard.convertCoordinateToIndex(inputCoordinate, 'y');

                //Place the ship
                bool response = this->tempBoard.placeShip(xIndex, yIndex, this->inputDirection, this->tempShip);

                //Make sure the ship has been placed successfully
                if(response){
                  
                  //Set ship to placed
                  this->tempShip.setPlaced(true);
                  
                  //Update player 1's fleet board and ship with the new temp variables
                  this->player1.setFleetBoard(tempBoard);
                  this->player1.setDestroyer(tempShip);

                  cout << "Destroyer placed successfully." << endl << endl;

                  this->player1.getFleetBoard().printBoard();
                
                }else{
                  
                  cout << "Invalid Ship Placement, please try again." << endl << endl;

                }

              }
  
            }

            //PLACE PLAYER 1 - Patrol Boat
            //While the patrol boat is not placed ask for input so it can be placed
            while(this->player1.getPatrolBoat().exists() && this->player1.getPatrolBoat().getPlaced() == false){

              cout << "Player 1 - Please place your Patrol Boat (Size: " << this->player1.getPatrolBoat().getSize() << ")" << endl << endl;
              
              this->action = "inputCoordinate";

              //Ask for a cordinate first and keep asking until a valid coordinate has been provided
              while(this->action == "inputCoordinate"){ 
                
                cout << "Input a starting Coordinate for your Patrol Boat (Size: " << this->player1.getPatrolBoat().getSize() << ") (e.g. A4) : ";
                
                this->inputCoordinate = this->getInput();

                //Handle the input coordinate and set action to the appropriate value
                this->action = this->handlePFCoordinateInput(inputCoordinate, 1);

              }

              //Ask for a direction next and keep asking until a valid direction has been provided
              while(this->action == "inputDirection"){ 
                
                cout << "Input a direction for your Patrol Boat (Size: " << this->player1.getPatrolBoat().getSize() << ") (e.g. \"h\" or \"v\") : ";

                this->inputDirection = this->getInput();

                //Handle the input orinetation and set action to the appropriate value
                this->action = this->handlePFDirectionInput(inputDirection, 1);

              }

              //Quit
              if(this->action == "quit"){
                
                this->gameState = "quit";

              }

              //Reset
              if(this->action == "reset"){
                
                this->resetPlayer1();
                cout << "Player 1 Ships Reset." << endl << endl;

              }

              //Both inputs accepted - attempt to place the ship
              if(this->action == "placeShip"){
                
                //Get the board and ship from player 1
                this->tempBoard = this->player1.getFleetBoard();
                this->tempShip = this->player1.getPatrolBoat();

                //Convert inputCoordinate into valid X and Y indexs
                int xIndex = this->tempBoard.convertCoordinateToIndex(inputCoordinate, 'x');
                int yIndex = this->tempBoard.convertCoordinateToIndex(inputCoordinate, 'y');

                //Place the ship
                bool response = this->tempBoard.placeShip(xIndex, yIndex, this->inputDirection, this->tempShip);

                //Make sure the ship has been placed successfully
                if(response){
                  
                  //Set ship to placed
                  this->tempShip.setPlaced(true);
                  
                  //Update player 1's fleet board and ship with the new temp variables
                  this->player1.setFleetBoard(tempBoard);
                  this->player1.setPatrolBoat(tempShip);

                  cout << "Patrol Boat placed successfully." << endl << endl;

                  this->player1.getFleetBoard().printBoard();
                
                }else{
                  
                  cout << "Invalid Ship Placement, please try again." << endl << endl;

                }

              }
  
            }

            //PLACE PLAYER 1 - Submarine
            //While the submarine is not placed ask for input so it can be placed
            while(this->player1.getSubmarine().exists() && this->player1.getSubmarine().getPlaced() == false){

              cout << "Player 1 - Please place your Submarine (Size: " << this->player1.getSubmarine().getSize() << ")" << endl << endl;
              
              this->action = "inputCoordinate";

              //Ask for a cordinate first and keep asking until a valid coordinate has been provided
              while(this->action == "inputCoordinate"){ 
                
                cout << "Input a starting Coordinate for your Submarine (Size: " << this->player1.getSubmarine().getSize() << ") (e.g. A4) : ";
                
                this->inputCoordinate = this->getInput();

                //Handle the input coordinate and set action to the appropriate value
                this->action = this->handlePFCoordinateInput(inputCoordinate, 1);

              }

              //Ask for a direction next and keep asking until a valid direction has been provided
              while(this->action == "inputDirection"){ 
                
                cout << "Input a direction for your Patrol Boat (Size: " << this->player1.getSubmarine().getSize() << ") (e.g. \"h\" or \"v\") : ";

                this->inputDirection = this->getInput();

                //Handle the input orinetation and set action to the appropriate value
                this->action = this->handlePFDirectionInput(inputDirection, 1);

              }

              //Quit
              if(this->action == "quit"){
                
                this->gameState = "quit";

              }

              //Reset
              if(this->action == "reset"){
                
                this->resetPlayer1();
                cout << "Player 1 Ships Reset." << endl << endl;

              }

              //Both inputs accepted - attempt to place the ship
              if(this->action == "placeShip"){
                
                //Get the board and ship from player 1
                this->tempBoard = this->player1.getFleetBoard();
                this->tempShip = this->player1.getSubmarine();

                //Convert inputCoordinate into valid X and Y indexs
                int xIndex = this->tempBoard.convertCoordinateToIndex(inputCoordinate, 'x');
                int yIndex = this->tempBoard.convertCoordinateToIndex(inputCoordinate, 'y');

                //Place the ship
                bool response = this->tempBoard.placeShip(xIndex, yIndex, this->inputDirection, this->tempShip);

                //Make sure the ship has been placed successfully
                if(response){
                  
                  //Set ship to placed
                  this->tempShip.setPlaced(true);
                  
                  //Update player 1's fleet board and ship with the new temp variables
                  this->player1.setFleetBoard(tempBoard);
                  this->player1.setSubmarine(tempShip);

                  cout << "Submarine placed successfully." << endl << endl;

                  this->player1.getFleetBoard().printBoard();
                
                }else{
                  
                  cout << "Invalid Ship Placement, please try again." << endl << endl;

                }

              }
  
            }
						
						//Make sure all of player 1 ships are placed
						if(this->player1.shipsPlaced()){

							cout << "Player 1 - All Ships Placed Successfully" << endl << endl;
							this->gameState = "player1CofirmPlacement";

						}

          }

        }

				while(this->gameState == "player1CofirmPlacement"){

					this->player1.getFleetBoard().printBoard();

					cout << "Player 1 - Please Confirm you are happy with current ship placement:"<< endl
					<< "1. Confirm ship placement" << endl
					<< "2. Place Ships again" << endl
					<< "3. Quit" << endl << endl;
					
					string input = this->getInput();

					if(input == "1"){

						this->gameState = "player2PlaceFleet";

					}else if(input == "2"){
						
						this->resetPlayer1();
						
						cout << "Player 1 Ships Reset." << endl << endl;
						
						this->gameState = "player1PlaceFleet";

					}else if(input == "3"){

						this->gameState = "quit";

					}else{

						cout << "Invalid input, please try again." << endl << endl;

					}

				}

				if(this->gameState == "player2PlaceFleet"){
          
					//Check if human or computer player
					if(this->player2.getType() == "human"){

						//Human player
						cout << "---------------------------------------------------------" << endl << endl;

						cout << "Player 2 please position your fleet:" << endl
          	<< "(Note: for help at any time, type \"help\")" << endl << endl;

						cout << "---------------------------------------------------------" << endl << endl;

						//Player 2 inputs coordinates to place their fleet
						while(this->gameState == "player2PlaceFleet"){

							//PLACE PLAYER 2 - BATTLESHIP
							//While the battleship is not placed ask for input so it can be placed
							while(this->player2.getBattleship().exists() && this->player2.getBattleship().getPlaced() == false){

								cout << "Player 2 - Please place your Battleship (Size: " << this->player2.getBattleship().getSize() << ")" << endl << endl;
								
								this->action = "inputCoordinate";

								//Ask for a cordinate first and keep asking until a valid coordinate has been provided
								while(this->action == "inputCoordinate"){ 
									
									cout << "Input a starting Coordinate for your Battleship (Size: " << this->player2.getBattleship().getSize() << ") (e.g. A4) : ";
									
									this->inputCoordinate = this->getInput();

									//Handle the input coordinate and set action to the appropriate value
									this->action = this->handlePFCoordinateInput(inputCoordinate, 2);

								}

								//Ask for a direction next and keep asking until a valid direction has been provided
								while(this->action == "inputDirection"){ 
									
									cout << "Input a direction for your Battleship (Size: " << this->player2.getBattleship().getSize() << ") (e.g. \"h\" or \"v\") : ";

									this->inputDirection = this->getInput();

									//Handle the input orinetation and set action to the appropriate value
									this->action = this->handlePFDirectionInput(inputDirection, 2);

								}

								//Quit
								if(this->action == "quit"){
									
									this->gameState = "quit";

								}

								//Reset
								if(this->action == "reset"){
									
									this->resetPlayer2();
									cout << "Player 2 Ships Reset." << endl << endl;

								}

								//Both inputs accepted - attempt to place the ship
								if(this->action == "placeShip"){
									
									//Get the board and ship from Player 2
									this->tempBoard = this->player2.getFleetBoard();
									this->tempShip = this->player2.getBattleship();

									//Convert inputCoordinate into valid X and Y indexs
									int xIndex = this->tempBoard.convertCoordinateToIndex(inputCoordinate, 'x');
									int yIndex = this->tempBoard.convertCoordinateToIndex(inputCoordinate, 'y');

									//Place the ship
									bool response = this->tempBoard.placeShip(xIndex, yIndex, this->inputDirection, this->tempShip);

									//Make sure the ship has been placed successfully
									if(response){
										
										//Set ship to placed
										this->tempShip.setPlaced(true);
										
										//Update Player 2's fleet board and ship with the new temp variables
										this->player2.setFleetBoard(tempBoard);
										this->player2.setBattleship(tempShip);

										cout << "Battleship placed successfully." << endl << endl;

										this->player2.getFleetBoard().printBoard();
									
									}else{
										
										cout << "Invalid Ship Placement, please try again." << endl << endl;

									}

								}

							}

							//PLACE Player 2 - Carrier
							//While the carrier is not placed ask for input so it can be placed
							while(this->player2.getCarrier().exists() && this->player2.getCarrier().getPlaced() == false){

								cout << "Player 2 - Please place your Carrier (Size: " << this->player2.getCarrier().getSize() << ")" << endl << endl;
								
								this->action = "inputCoordinate";

								//Ask for a cordinate first and keep asking until a valid coordinate has been provided
								while(this->action == "inputCoordinate"){ 
									
									cout << "Input a starting Coordinate for your Carrier (Size: " << this->player2.getCarrier().getSize() << ") (e.g. A4) : ";
									
									this->inputCoordinate = this->getInput();

									//Handle the input coordinate and set action to the appropriate value
									this->action = this->handlePFCoordinateInput(inputCoordinate, 2);

								}

								//Ask for a direction next and keep asking until a valid direction has been provided
								while(this->action == "inputDirection"){ 
									
									cout << "Input a direction for your Battleship (Size: " << this->player2.getCarrier().getSize() << ") (e.g. \"h\" or \"v\") : ";

									this->inputDirection = this->getInput();

									//Handle the input orinetation and set action to the appropriate value
									this->action = this->handlePFDirectionInput(inputDirection, 2);

								}

								//Quit
								if(this->action == "quit"){
									
									this->gameState = "quit";

								}

								//Reset
								if(this->action == "reset"){
									
									this->resetPlayer2();
									cout << "Player 2 Ships Reset." << endl << endl;

								}

								//Both inputs accepted - attempt to place the ship
								if(this->action == "placeShip"){
									
									//Get the board and ship from Player 2
									this->tempBoard = this->player2.getFleetBoard();
									this->tempShip = this->player2.getCarrier();

									//Convert inputCoordinate into valid X and Y indexs
									int xIndex = this->tempBoard.convertCoordinateToIndex(inputCoordinate, 'x');
									int yIndex = this->tempBoard.convertCoordinateToIndex(inputCoordinate, 'y');

									//Place the ship
									bool response = this->tempBoard.placeShip(xIndex, yIndex, this->inputDirection, this->tempShip);

									//Make sure the ship has been placed successfully
									if(response){
										
										//Set ship to placed
										this->tempShip.setPlaced(true);
										
										//Update Player 2's fleet board and ship with the new temp variables
										this->player2.setFleetBoard(tempBoard);
										this->player2.setCarrier(tempShip);

										cout << "Carrier placed successfully." << endl << endl;

										this->player2.getFleetBoard().printBoard();
									
									}else{
										
										cout << "Invalid Ship Placement, please try again." << endl << endl;

									}

								}

							}

							//PLACE Player 2 - Destroyer
							//While the Destroyer is not placed ask for input so it can be placed
							while(this->player2.getDestroyer().exists() && this->player2.getDestroyer().getPlaced() == false){

								cout << "Player 2 - Please place your Destroyer (Size: " << this->player2.getDestroyer().getSize() << ")" << endl << endl;
								
								this->action = "inputCoordinate";

								//Ask for a cordinate first and keep asking until a valid coordinate has been provided
								while(this->action == "inputCoordinate"){ 
									
									cout << "Input a starting Coordinate for your Destroyer (Size: " << this->player2.getDestroyer().getSize() << ") (e.g. A4) : ";
									
									this->inputCoordinate = this->getInput();

									//Handle the input coordinate and set action to the appropriate value
									this->action = this->handlePFCoordinateInput(inputCoordinate, 2);

								}

								//Ask for a direction next and keep asking until a valid direction has been provided
								while(this->action == "inputDirection"){ 
									
									cout << "Input a direction for your Destroyer (Size: " << this->player2.getDestroyer().getSize() << ") (e.g. \"h\" or \"v\") : ";

									this->inputDirection = this->getInput();

									//Handle the input orinetation and set action to the appropriate value
									this->action = this->handlePFDirectionInput(inputDirection, 2);

								}

								//Quit
								if(this->action == "quit"){
									
									this->gameState = "quit";

								}

								//Reset
								if(this->action == "reset"){
									
									this->resetPlayer2();
									cout << "Player 2 Ships Reset." << endl << endl;

								}

								//Both inputs accepted - attempt to place the ship
								if(this->action == "placeShip"){
									
									//Get the board and ship from Player 2
									this->tempBoard = this->player2.getFleetBoard();
									this->tempShip = this->player2.getDestroyer();

									//Convert inputCoordinate into valid X and Y indexs
									int xIndex = this->tempBoard.convertCoordinateToIndex(inputCoordinate, 'x');
									int yIndex = this->tempBoard.convertCoordinateToIndex(inputCoordinate, 'y');

									//Place the ship
									bool response = this->tempBoard.placeShip(xIndex, yIndex, this->inputDirection, this->tempShip);

									//Make sure the ship has been placed successfully
									if(response){
										
										//Set ship to placed
										this->tempShip.setPlaced(true);
										
										//Update Player 2's fleet board and ship with the new temp variables
										this->player2.setFleetBoard(tempBoard);
										this->player2.setDestroyer(tempShip);

										cout << "Destroyer placed successfully." << endl << endl;

										this->player2.getFleetBoard().printBoard();
									
									}else{
										
										cout << "Invalid Ship Placement, please try again." << endl << endl;

									}

								}
		
							}

							//PLACE Player 2 - Patrol Boat
							//While the patrol boat is not placed ask for input so it can be placed
							while(this->player2.getPatrolBoat().exists() && this->player2.getPatrolBoat().getPlaced() == false){

								cout << "Player 2 - Please place your Patrol Boat (Size: " << this->player2.getPatrolBoat().getSize() << ")" << endl << endl;
								
								this->action = "inputCoordinate";

								//Ask for a cordinate first and keep asking until a valid coordinate has been provided
								while(this->action == "inputCoordinate"){ 
									
									cout << "Input a starting Coordinate for your Patrol Boat (Size: " << this->player2.getPatrolBoat().getSize() << ") (e.g. A4) : ";
									
									this->inputCoordinate = this->getInput();

									//Handle the input coordinate and set action to the appropriate value
									this->action = this->handlePFCoordinateInput(inputCoordinate, 2);

								}

								//Ask for a direction next and keep asking until a valid direction has been provided
								while(this->action == "inputDirection"){ 
									
									cout << "Input a direction for your Patrol Boat (Size: " << this->player2.getPatrolBoat().getSize() << ") (e.g. \"h\" or \"v\") : ";

									this->inputDirection = this->getInput();

									//Handle the input orinetation and set action to the appropriate value
									this->action = this->handlePFDirectionInput(inputDirection, 2);

								}

								//Quit
								if(this->action == "quit"){
									
									this->gameState = "quit";

								}

								//Reset
								if(this->action == "reset"){
									
									this->resetPlayer2();
									cout << "Player 2 Ships Reset." << endl << endl;

								}

								//Both inputs accepted - attempt to place the ship
								if(this->action == "placeShip"){
									
									//Get the board and ship from Player 2
									this->tempBoard = this->player2.getFleetBoard();
									this->tempShip = this->player2.getPatrolBoat();

									//Convert inputCoordinate into valid X and Y indexs
									int xIndex = this->tempBoard.convertCoordinateToIndex(inputCoordinate, 'x');
									int yIndex = this->tempBoard.convertCoordinateToIndex(inputCoordinate, 'y');

									//Place the ship
									bool response = this->tempBoard.placeShip(xIndex, yIndex, this->inputDirection, this->tempShip);

									//Make sure the ship has been placed successfully
									if(response){
										
										//Set ship to placed
										this->tempShip.setPlaced(true);
										
										//Update Player 2's fleet board and ship with the new temp variables
										this->player2.setFleetBoard(tempBoard);
										this->player2.setPatrolBoat(tempShip);

										cout << "Patrol Boat placed successfully." << endl << endl;

										this->player2.getFleetBoard().printBoard();
									
									}else{
										
										cout << "Invalid Ship Placement, please try again." << endl << endl;

									}

								}
		
							}

							//PLACE Player 2 - Submarine
							//While the submarine is not placed ask for input so it can be placed
							while(this->player2.getSubmarine().exists() && this->player2.getSubmarine().getPlaced() == false){

								cout << "Player 2 - Please place your Submarine (Size: " << this->player2.getSubmarine().getSize() << ")" << endl << endl;
								
								this->action = "inputCoordinate";

								//Ask for a cordinate first and keep asking until a valid coordinate has been provided
								while(this->action == "inputCoordinate"){ 
									
									cout << "Input a starting Coordinate for your Submarine (Size: " << this->player2.getSubmarine().getSize() << ") (e.g. A4) : ";
									
									this->inputCoordinate = this->getInput();

									//Handle the input coordinate and set action to the appropriate value
									this->action = this->handlePFCoordinateInput(inputCoordinate, 2);

								}

								//Ask for a direction next and keep asking until a valid direction has been provided
								while(this->action == "inputDirection"){ 
									
									cout << "Input a direction for your Patrol Boat (Size: " << this->player2.getSubmarine().getSize() << ") (e.g. \"h\" or \"v\") : ";

									this->inputDirection = this->getInput();

									//Handle the input orinetation and set action to the appropriate value
									this->action = this->handlePFDirectionInput(inputDirection, 2);

								}

								//Quit
								if(this->action == "quit"){
									
									this->gameState = "quit";

								}

								//Reset
								if(this->action == "reset"){
									
									this->resetPlayer2();
									cout << "Player 2 Ships Reset." << endl << endl;

								}

								//Both inputs accepted - attempt to place the ship
								if(this->action == "placeShip"){
									
									//Get the board and ship from Player 2
									this->tempBoard = this->player2.getFleetBoard();
									this->tempShip = this->player2.getSubmarine();

									//Convert inputCoordinate into valid X and Y indexs
									int xIndex = this->tempBoard.convertCoordinateToIndex(inputCoordinate, 'x');
									int yIndex = this->tempBoard.convertCoordinateToIndex(inputCoordinate, 'y');

									//Place the ship
									bool response = this->tempBoard.placeShip(xIndex, yIndex, this->inputDirection, this->tempShip);

									//Make sure the ship has been placed successfully
									if(response){
										
										//Set ship to placed
										this->tempShip.setPlaced(true);
										
										//Update Player 2's fleet board and ship with the new temp variables
										this->player2.setFleetBoard(tempBoard);
										this->player2.setSubmarine(tempShip);

										cout << "Submarine placed successfully." << endl << endl;

										this->player2.getFleetBoard().printBoard();
									
									}else{
										
										cout << "Invalid Ship Placement, please try again." << endl << endl;

									}

								}
		
							}
							
							//Make sure all of Player 2 ships are placed
							if(this->player2.shipsPlaced()){

								cout << "Player 2 - All Ships Placed Successfully" << endl << endl;
								this->gameState = "player2CofirmPlacement";

							}

						}

						while(this->gameState == "player2CofirmPlacement"){

							this->player2.getFleetBoard().printBoard();

							cout << "Player 2 - Please Confirm you are happy with current ship placement:"<< endl
							<< "1. Confirm ship placement" << endl
							<< "2. Place Ships again" << endl
							<< "3. Quit" << endl << endl;
							
							string input = this->getInput();

							if(input == "1"){

								this->gameState = "mainGame";

							}else if(input == "2"){
								
								this->resetPlayer2();
								
								cout << "Player 2 Ships Reset." << endl << endl;
								
								this->gameState = "player2PlaceFleet";

							}else if(input == "3"){

								this->gameState = "quit";

							}else{

								cout << "Invalid input, please try again." << endl << endl;

							}

						}

					}else{
						
						//Computer player
						cout << "Admiral Crunch is positioning his fleet..." << endl << endl;

						//Randomly place computer's
						this->player2.randomlyPlaceRemainingShips();

						//Computer player
						cout << "Admiral Crunch is ready..." << endl << endl;

						this->gameState = "mainGame";

						this->pause();

					}
 
        }

				if(this->gameState == "mainGame"){
					
					cout << "---------------------------------------------------------" << endl << endl;
          
					cout << "Ada Ships Begin!" << endl << endl;
          
					cout << "---------------------------------------------------------" << endl << endl;
					
					//Set the active player to player 1 for the start of the game
					this->activePlayer = 1;

					while(this->gameState == "mainGame"){

						//Determine the active player
						if(this->activePlayer == 1){
							
							this->currentPlayerLabel = "Player 1";
							this->currentPlayerType = this->player1.getType();

						}else{

							this->currentPlayerType = this->player2.getType();

							if(this->currentPlayerType == "human"){

								this->currentPlayerLabel = "Player 2";

							}
							else{

								this->currentPlayerLabel = "Admiral Crunch";

							}

						}

						//Output message
						cout << "---------------------------------------------------------" << endl << endl;

						cout << this->currentPlayerLabel << "'s Turn:" << endl;
						cout << "(Note: for help at any time, type \"help\")" << endl << endl;
						
						cout << "---------------------------------------------------------" << endl << endl;

						//Determine if the game mode is Salvo or Classic mode 
						if(this->gameMode == "salvo"){
							
							//Set the amount of shots to the amount of ships the active player has remaining
							if(this->activePlayer == 1){

								this->currentShots = this->player1.getShipCount();
							
							}else{

								this->currentShots = this->player2.getShipCount();

							}

						}else{
							
							//Classic mode so just set shots to 1
							this->currentShots = 1;

						}

						bool autoFireAll;

						if(this->currentPlayerType == "computer"){
							
							//Current player is computer so auto fire
							autoFireAll = true;

						}else{

							autoFireAll = false;
						
						}
						
						//Loop through the appropriate shot
						for(int i = 0; i < this->currentShots; i++){

							if(autoFireAll == true){

								//Auto fire
								this->autoFire();

							}else{

								//Manual Fire

								bool currentShot = true;

								while(currentShot){

									if(this->gameMode == "salvo"){
										
										string shotWording = "shot";

										if(this->currentShots - i > 1){
											
											shotWording = "shots";
										
										}

										cout << this->currentPlayerLabel << " you have " << this->currentShots - i << " " << shotWording << " remaining please enter a coordinate to fire shot at e.g (A5) : ";

									}else{

										cout << this->currentPlayerLabel << " please enter a coordinate to fire at e.g (A5) : ";

									}

									string input = this->getInput();

									//Check if current shot was valid
									if(this->player1.getFleetBoard().isValidCoordinateFormat(input)){

										if(this->activePlayer == 1){
											
											//Convert inputCoordinate into valid X and Y indexs
											int xIndex = this->player1.getFleetBoard().convertCoordinateToIndex(input, 'x');
											int yIndex = this->player1.getFleetBoard().convertCoordinateToIndex(input, 'y');

											//Player 2 needs to handle the shot player 1 just fired
											string response = this->player2.handleShotFiredAt(xIndex, yIndex, this->player1.getName());

											cout << endl;

											if(response != "invalid"){

												//Player 2 records their successful shot
												this->player1.recordShotFired(xIndex, yIndex, response);

												currentShot = false;

											}else{
												
												cout << "Invalid Shot, please try again" << endl << endl;
											
											}
										
										}else{
											
											//Convert inputCoordinate into valid X and Y indexs
											int xIndex = this->player1.getFleetBoard().convertCoordinateToIndex(input, 'x');
											int yIndex = this->player1.getFleetBoard().convertCoordinateToIndex(input, 'y');

											//Player 1 needs to handle the shot player 2 just fired
											string response = this->player1.handleShotFiredAt(xIndex, yIndex, this->player2.getName());

											cout << endl;

											if(response != "invalid"){

												//Player 2 records their successful shot
												this->player2.recordShotFired(xIndex, yIndex, response);

												currentShot = false;

											}else{

												cout << "Invalid Shot, please try again" << endl << endl;

											}
										}

									}else if(input == "auto-fire"){
										
										//Auto Fire
										this->autoFire();
										
										currentShot = false;

									}else if(input == "auto-fire all"){
										
										//Auto Fire current shot
										this->autoFire();

										//Set auto fire all to true so all subsequent shots fire automatically
										autoFireAll = true;

										currentShot = false;

									}else if(input == "help"){
										
										cout << "Additional Player Commands: " << endl 
										<< "\"auto-fire\" - Fires current shot at random" << endl;

										if(this->gameMode == "salvo"){

											cout << "\"auto-fire all\" - Fires all remaining shots at random" << endl;
										
										}

										cout << "\"see target board\" - Displays board tracking previous shots" << endl
										<< "\"see fleet\" - Displays Fleet Board" << endl
										<< "\"quit\" - Quits the game" << endl << endl;
										
									}else if(input == "see fleet"){

										if(this->activePlayer == 1){

											this->player1.getFleetBoard().printBoard();
										
										}else{
											
											this->player2.getFleetBoard().printBoard();
										}

									}else if(input == "see target board"){

										if(this->activePlayer == 1){

											this->player1.getTargetBoard().printBoard();
										
										}else{
											
											this->player2.getTargetBoard().printBoard();
										
										}

									}else if(input == "quit"){

										currentShot = false;

										//Break out of shots Loop
										i = this->currentShots + 2;

										this->gameState = "quit";

									}else{

										cout << "Invalid command please try again." << endl << endl;

									}

								}

							}

							//Check for player's Death
							if(this->player1.isAlive() == false){
								
								//Break out of shots Loop
								i = this->currentShots + 2;
								
								this->winningPlayerLabel = this->player2.getName();

								cout << this->player1.getName() << " has been defeated !" << endl << endl;

								//player 2 is dead
								this->gameState = "victory";


							}else if(this->player2.isAlive() == false){

								//Player 2 is dead
								//Break out of shots Loop
								i = this->currentShots + 2;
								
								this->winningPlayerLabel = this->player1.getName();
								
								cout << this->player2.getName() << " has been defeated !" << endl << endl;

								//player 1 is dead
								this->gameState = "victory";

							}

						}

						if(this->activePlayer == 1){
								
							//Player 1's turn is over set player 2 to the active player
							this->activePlayer = 2;
						
						}else{
							
							//Player 2's turn is over set player 1 to the active player
							this->activePlayer = 1;
						
						}

						//Don't pause if player has selected quit 
						if(this->gameState != "quit"){
							
							//Pause the game
							this->pause();
						
						}

					}

        }

        if(this->gameState == "quit"){

          cout << "Bye !" << endl << endl;
          return 0;

        }

				if(this->gameState == "victory"){

          cout << "/========================================================/" << endl << endl;
					cout << "  CONGRATULATIONS " << this->winningPlayerLabel << ", YOU'RE WINNER" << endl;
					cout << "/========================================================/" << endl << endl;
          
					this->pause();

					return 0;

        }


      }

    }

    

};