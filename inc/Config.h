#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Board.h"
#include "Ship.h"
#include "Player.h"

using namespace std;

int boardConfig() {
	int boardWidth, boardHeight, shipSize;
  string line, type, width, height, row, boatType, sizeOfBoats;
  ifstream getBoardSize ("adaship_config.ini");
  if (getBoardSize.is_open())
  {
    while ( getline (getBoardSize,line) )
    {
     stringstream row(line);
        getline(row, type, ':');
				getline(row, boatType, ',');
        if (type == "Board"){
          getline (row, width, 'x');
          getline (row, height, '\n');
          boardWidth = stoi(width);
          boardHeight = stoi(height);
					cout << width;
					cout << height;
					cout << boardWidth;
					cout << boardHeight;
				};
				if (boatType == "Carrier") {
				//getline(row, type, ':');
				//getline(row, boatType, ',');
        getline(row, sizeOfBoats, '\n');
				shipSize = stoi(sizeOfBoats);
				cout << shipSize;
				cout << sizeOfBoats;
				};
				
    }
    getBoardSize.close();
  }

  else cout << "Unable to open file"; 

  return 0;
}

int shipConfig() {
	int shipSize;
  string line, type, row, boatType, sizeOfBoats;
  ifstream getShipSizes ("adaship_config.ini");
  if (getShipSizes.is_open())
  {
    while ( getline (getShipSizes,line) )
    {
     stringstream row(line);
        getline(row, type, ':');
				getline(row, boatType, ',');
        if (boatType == "Carrier"){
          getline (row, sizeOfBoats, '\n');
         // getline (row, height, '\n');
          shipSize = stoi(sizeOfBoats);
         // boardHeight = stoi(height);
					cout << shipSize;
					// cout << height;
					// cout << boardWidth;
					// cout << boardHeight;
				};
				// if (boatType == "Carrier") {
				// //getline(row, type, ':');
				// //getline(row, boatType, ',');
        // getline(row, sizeOfBoats, '\n');
				// shipSize = stoi(sizeOfBoats);
				// cout << shipSize;
				// cout << sizeOfBoats;
				// };
				
    }
    getShipSizes.close();
  }

  else cout << "Unable to open file"; 

  return 0;
}

