#include "inc/Game.h"
#include <iostream>
#include <cmath>
#include <cstring>
#include <chrono>

using namespace std;

void test() {
  
  //Create a Game
  Game game;

  Board testBoard = Board(10,10);
  Ship testShip = Ship(5,"B");
  string coordinate = "";

  int xIndex = testBoard.convertCoordinateToIndex(coordinate, 'x');
  int yIndex = testBoard.convertCoordinateToIndex(coordinate, 'y');

  testBoard.placeShip(xIndex, yIndex, "h", testShip);

  testBoard.printBoard();

  cout << "xIndex: " << xIndex << " " << "yIndex: " << yIndex; 

	Player test;
	test.setFleetBoard(Board(10,10));
	int i = 0;

	while (i != 10){
		i = test.randomXIndex();
		cout << i;

	}

}

int main() {

  //Create a Game
  Game game;
  
  game.run();
  
  //test();



}

