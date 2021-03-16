#include "inc/Board.h"
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

using namespace std;

int main() {
  
  Board playerBoard(10, 10);
  
  playerBoard.printBoard(); 
  
  Battleship p1Battleship;
  Submarine p1Submarine;

  playerBoard.placeShip(1, 2, 'h', p1Battleship);
  playerBoard.placeShip(6, 2, 'v', p1Submarine);

  playerBoard.printBoard();

  return 0;

}