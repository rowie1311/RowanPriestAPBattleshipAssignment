#include "Board.h"
#include "Player.h"
#include "Ship.h"

#include <iostream>
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

    int boardWidth;
    int boardHeight;

    int battleshipSize;
    int carrierSize;
    int destroyerSize;
    int patrolBoatSize;
    int submarineSize;

    string action;
    string inputCoordinate;
    string inputDirection;

    Board tempBoard;
    Ship tempShip;
    Player tempPlayer;

		//Simulated pause for the program waiting for a user to press a key
    void pause(){

      cout<<"Please press [Enter] to continue . . ." << endl;
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

  public:
    //Default constructor
    Game(){};



    //Run the game and get the game mode
    int run(){
      
      //Read file and get settings
      this->boardWidth = 10;
      this->boardHeight = 10;
      this->battleshipSize = 4;
      this->carrierSize = 5;
      this->destroyerSize = 3;
      this->patrolBoatSize = 2;
      this->submarineSize = 3;

      //Set the current gamestate
      this->gameState = "selectMode";

      //Output start message
      cout << "Welcome to Ada Ships !" << endl 
      << "A Battle of Boats, Brains and Bravery!" << endl << endl;
      
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

            //Move game onto select opponent
            this->gameState = "confirmSettings";

          }else if(input == "2"){
            
            //VS Human selected
            cout << endl << "VS Human selected" << endl << endl;
            this->gameOpponent = "human";//set game mode to salvo mode

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
          
          //Reset player 1
          this->resetPlayer1();

          //Set player 2 to selected opponent type
          this->player2.setType(this->gameOpponent);
          
          //Reset player 2
          this->resetPlayer2();

          this->gameState = "player1PlaceFleet";

        }

        if(this->gameState == "player1PlaceFleet"){
          
          cout << "Player 1 please position your fleet:" << endl
          << "(Note: for help at any time, type \"help\")" << endl << endl;

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

						cout << "Player 2 please position your fleet:" << endl
          	<< "(Note: for help at any time, type \"help\")" << endl << endl;

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

							this->player1.getFleetBoard().printBoard();

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

          cout << "Ada Ships Begin!" << endl << endl;
          

					return 0;

        }

        if(this->gameState == "quit"){

          cout << "Bye !" << endl << endl;
          return 0;

        }

      }

    }

    

};