#pragma once
#include "ships/Ship.h"
#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
#include <map>
#include <stdexcept>

using namespace std;

class Board {
  
  private: 
    int width;
    int height; 
    string label;
    vector <vector<string>> boardRows;
    string emptyMarker = ".";

  public:

    //Constructor
    Board(int width, int height) {
      
      //Set width and height
      this->width = width;
      this->height = height;

      //Build the board (based off width and height)
      this->buildBoard();

    }

    //Builds the board based on set width and height by pushing values to a 2D vector
    void buildBoard() {

      //Height is the amount of rows
      for (int h = 0; h < this->height; h++) {

        //Create temp vector to represent the current row that will have cols added to it
        vector <string> currentRow;

        //Width represents the cols
        for (int w = 0; w < this->width; w++) {
          
          //Add a value to the currrent row to represent the col (use 0 for now to represent empty space)
          currentRow.push_back(this->emptyMarker);

        }

        //Add the newly populated row to the vector storing all of the board rows
        this->boardRows.push_back(currentRow);

      }

    }

    bool placeShip(int x, int y, char orientation, Ship ship){

      if(this->checkShipPlacement(x, y, orientation, ship)){
        
        //Get the ship's length
        int shipLength = ship.getSize();

        //Get the start position this is just where the ship was placed
        int startX = x;
        int startY = y;

        //intiialize endY and endX
        int endX;
        int endY;

        //Get the end position - this depends on what orientation of the ship was Vertical or Horizontal
        if(orientation == 'v'){

          endX = x; //When vertical the ship's ending x position stays the same
          endY = y + (shipLength - 1); //When vertical the ship's ending y position will be moved along the y axis based on it's length 

        }
        else if(orientation == 'h'){

          endX = x + (shipLength - 1); //When horizontal the ship's ending x position will be moved along the x axis based on it's length 
          endY = y; //When horizontal the ship's ending y position stays the same

        }

        //2 - Check that placing the ship does not overlap any other ships
        if(orientation == 'v'){
          
          int xIndex = startX - 1;

          for(int yIndex = startY - 1; yIndex < endY; yIndex++){

            this->boardRows[yIndex][xIndex] = ship.getLabel();

          }

        }
        else if(orientation == 'h'){
          
          int yIndex = startY - 1;

          for( int xIndex = startX - 1; xIndex < endX; xIndex++){

            this->boardRows[yIndex][xIndex] = ship.getLabel();

          }

        }
        
      }
      
      return false;

    }

    //Check's the placement of a ship on a board is valid
    bool checkShipPlacement(int x, int y, char orientation, Ship ship){

      //Get the ship's length
      int shipLength = ship.getSize();
      
      //1 - Check the placement fits on the board by checking the position of the end of the ship and the start of the ship and making sure they are both in the bonds of the board
      
      //Get the start position this is just where the ship was placed
      int startX = x;
      int startY = y;

      //intiialize endY and endX
      int endX;
      int endY;

      //Get the end position - this depends on what orientation of the ship was Vertical or Horizontal
      if(orientation == 'v'){

        endX = x; //When vertical the ship's ending x position stays the same
        endY = y + (shipLength - 1); //When vertical the ship's ending y position will be moved along the y axis based on it's length 

      }
      else if(orientation == 'h'){

        endX = x + (shipLength - 1); //When horizontal the ship's ending x position will be moved along the x axis based on it's length 
        endY = y; //When horizontal the ship's ending y position stays the same

      }

      //Make sure the positions fit on the board
      if(!this->boardPositionExists(startX, startY) || !this->boardPositionExists(endX, endY)){

        //One of the positions does not fit on the board  
        return false;

      }

      //2 - Check that placing the ship does not overlap any other ships
      if(orientation == 'v'){
        
        int xIndex = startX - 1;

        for( int yIndex = startY - 1; yIndex < endY; yIndex++){

          string currentCoord = this->boardRows[yIndex][xIndex];

          if(currentCoord != this->emptyMarker){

            return false;

          }

        }

      }
      else if(orientation == 'h'){
        
        int yIndex = startY - 1;
        
        for(int xIndex = startX - 1; xIndex < endX; xIndex++){

          string currentCoord = this->boardRows[yIndex][xIndex];

          if(currentCoord != this->emptyMarker){

            return false;

          }

        }

      }

      return true;

    }

    bool boardPositionExists(int x, int y){

      if(y >= 1 && y <= this->boardRows.size()){

        int yIndex = y - 1;

        if(x >= 1 && x <= this->boardRows[yIndex].size()){
          
          return true;
        
        }

      }

      return false;

    }


    //Prints the board to the console as a grid with letter labels for the cols and number labels for the rows
    bool printBoard() {
      
      //Make sure the board exists
      if(this->boardRows.size() > 0)
      {
        //Loop through the built rows
        for (int row = 0; row < this->boardRows.size(); row++) {
          
          //Store the current row of the board
          vector <string> currentRow = this->boardRows[row];
          
          //Print col labels ( if this is the first row )
          if(row == 0)
          {
            //Space out the first 3 chars (keeps it inline with the row labels)
            cout << "   ";
            
            for(int col=0; col < currentRow.size(); col++) {
              
              string currentLabel = convertNumberToLetters(col + 1);

              this->printStringValue(currentLabel);

            }

            //Start new line
            cout << endl << endl;

          }        

          //Print the label for the current row (adding 1 as row is the index)
          this->printIntValue(row + 1, "left");

          // Loop through the row and print out it's cols
          for(int col=0; col < currentRow.size(); col++) {
            
            this->printStringValue(currentRow[col]);
    
          }

          this->printEndOfRow();
        
        }

        return true;

      }
      else{

        return false;

      }

    }

    //Consistantly output end of row as to maintain the grid like appearance in the console
    void printEndOfRow(){

      cout << endl << endl;

    }

    //Consistantly output int values as to maintain the grid like appearance in the console
    void printIntValue(int value, string alignment = "center") {

      //Determine length of the int as to appropriately space the output
      if(value < 10) {

        if(alignment == "center"){

          cout << " " << value << " ";
        
        }
        else if (alignment == "left"){

          cout << value << "  ";

        }
        else{

          cout << "  " << value;

        }

      }
      else if (value < 100){

        if (alignment == "right" || alignment == "center" ){

          cout << " " << value ;

        }
        else{

          cout << value << " ";

        }

      }else{

        cout << "   ";
      
      }

    }

    //Consistantly output string values as to maintain the grid like appearance in the console
    void printStringValue(string value, string alignment = "center") {
      
      //Determine length of string as to appropriately space the output
      if(value.length() == 1)
      {
        if(alignment == "center"){

          cout << " " << value << " ";
        
        }
        else if (alignment == "left"){

          cout << value << "  ";

        }
        else{

          cout << "  " << value;

        }
      }
      else if(value.length() == 2){
        
        if (alignment == "right" || alignment == "center" ){

          cout << " " << value ;

        }
        else{

          cout << value << " ";

        }

      }
      else if(value.length() == 0){

        cout << "   ";
      
      }

    }
    
    string convertNumberToLetters(int number) {

      string letters = "#ABCDEFGHIJKLMNOPQRSTUVWXYZ";
      string letterString = "";

      while(number >= 1){
        
        int currentNumber = number;
        number = floor(currentNumber / 26);
        int remainder = currentNumber % 26;

        if (remainder == 0) {
          
          remainder = 26;
          number = number-1;
        
        };
        
        letterString = letters.at(remainder) + letterString;
      
      };
      
      return letterString;

    }


    //MIKE'S convert letters to numbers function
    int convertLettersToNumbers(string letters){
      
      //convert 'column reference' (A[a] = 0, B[b] = 2, .. Z[a] = 25, AA[aa], AB[bb]..ZZ[zz] = 701) to an index (0..701)
      //returns valid index (0..701), any negative values represent invalid column references i.e., not A[a]..ZZ[zz]
      
      if(letters.length() == 1) {
        //deal with single letter value (A = 0, B = 2 .. Z = 25)
        return toupper(int(letters[0])) - 65; // 65 represents ASCII 'A' 'A' - 65 = 0

      } else if(letters.length() == 2) {
        //deal with pair values (AA = 26, BA = 52, CA = 78 .. ZZ = 701)
        return ((toupper(int(letters[1])) - 65) + (toupper(int(letters[0])) - 64) * 26); // -64 to get base 1 thus avoiding 0 * n = 0 issue
      }

      return -1; //no match

    }

};