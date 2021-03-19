#include "Game.h"
#include "inc/Player.h"
#include <iostream>
#include <cmath>
#include <cstring>
#include <chrono>

using namespace std;

int main() {

  //startMenu();
  
  //Player p1('h',"Test PLayer");


  Board playerBoard(30, 30);
  
  cout << playerBoard.convertNumberToLetters(29) << endl;
  cout << playerBoard.convertLettersToNumbers("AI") << endl;

  playerBoard.printBoard(); 
  
  Battleship p1Battleship;
  Submarine p1Submarine;
  Carrier p1Carrier;
  Destroyer p1Destroyer;
  PatrolBoat p1PatrolBoat;

  playerBoard.placeShip(9, 6, 'v', p1Battleship);
  playerBoard.placeShip(6, 2, 'v', p1Submarine);
  playerBoard.placeShip(2, 5, 'h', p1Carrier);
  playerBoard.placeShip(7, 2, 'v', p1Destroyer);
  playerBoard.placeShip(3, 4, 'h', p1PatrolBoat);

  playerBoard.printBoard();
  
  cout << "END";
  
  return 0;

}