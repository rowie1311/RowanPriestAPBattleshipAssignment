#include "inc/Board.h"
#include "inc/Player.h"
#include "inc/ships/Ship.h"
#include "inc/ships/Battleship.h" 
#include "inc/ships/Carrier.h" 
#include "inc/ships/Destroyer.h" 
#include "inc/ships/PatrolBoat.h" 
#include "inc/ships/Submarine.h"

#include <iostream>
#include <cmath>
#include <cstring>
#include <chrono>
#include <string>
using namespace std;

void shipPlacement() {
  string shipPlacementOption;
  while(true) {
    cout << "Please select an option:\n\n 1. Manual ship placement\n 2. Auto Ship Placement\n0. Quit";
    cin >> shipPlacementOption;
    if (shipPlacementOption == "2") {
      cout << "\nauto ship option selected";
      break;
    }
    if (shipPlacementOption == "1") {
      cout << "\nmanual ship option selected";
      break;
    }
    if (shipPlacementOption == "0") {
      cout << "\nOkay, maybe next time. Bye!";
      break;
    }
    else {
      cout << "\nPlease select a valid option";
    };
  };

};


void startMenu() { 
  string option;
  cout << "Welcome to adaships.\n\n" << "Please select an option below: \n\n1. Start Game\n2. Quit\n";
  while(true) { 
  //cin >> option;
  getline(cin, option);
    if (option == "2") {
      cout << "\n Okay, maybe next time. bye!\n";
      break;
    }
    if (option == "1") {
      shipPlacement();
  
    // playerBoard.printBoard(); 
  
    // Battleship p1Battleship;
    // Submarine p1Submarine;
    // Carrier p1Carrier;
    // Destroyer p1Destroyer;
    // PatrolBoat p1PatrolBoat;

    // playerBoard.placeShip(1, 2, 'h', p1Battleship);
    // playerBoard.placeShip(6, 2, 'v', p1Submarine);
    // playerBoard.placeShip(8, 4, 'h', p1Carrier);
    // playerBoard.placeShip(7, 2, 'v', p1Destroyer);
    // playerBoard.placeShip(3, 4, 'h', p1PatrolBoat);

    // playerBoard.printBoard();
    // break;
    }

    else {
      cout << "Please select a valid option\n\nPlease select an option below: \n\n1. Start Game\n2. Quit\n";
    };
  };

};