#pragma once
#include "Ship.h"
#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <ctype.h>

using namespace std;

class Board {//Create board class
  
  private: //private variables
    int width; //width of board
    int height; //height of board
    string label; //labels for the side of the board
    vector <vector<string>> boardRows;
    string emptyMarker = ".";
    string hitMarker = "H";
    string missMarker = "M";

  public:
    //Default Constructor
    Board() {}

    //Constructor - with width and height
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

    bool placeShip(int x, int y, string direction, Ship ship){

      if(this->checkShipPlacement(x, y, direction, ship)){

        //Get the ship's length
        int shipLength = ship.getSize();

        //Get the start position this is just where the ship was placed
        int startX = x;
        int startY = y;

        //intiialize endY and endX
        int endX;
        int endY;

        //Get the end position - this depends on what direction of the ship was Vertical or Horizontal
        if(direction == "v"){

          endX = x; //When vertical the ship's ending x position stays the same
          endY = y + (shipLength - 1); //When vertical the ship's ending y position will be moved along the y axis based on it's length 

        }
        else if(direction == "h"){

          endX = x + (shipLength - 1); //When horizontal the ship's ending x position will be moved along the x axis based on it's length 
          endY = y; //When horizontal the ship's ending y position stays the same

        }

        //2 - Place the Ship
        if(direction == "v"){
          
          int xIndex = startX;

          for(int yIndex = startY; yIndex <= endY; yIndex++){

            this->boardRows[yIndex][xIndex] = ship.getLabel();

          }

          return true;

        }else if(direction == "h"){
          
          int yIndex = startY;

          for( int xIndex = startX; xIndex <= endX; xIndex++){

            this->boardRows[yIndex][xIndex] = ship.getLabel();

          }

          return true;

        }
        
      }
      
      return false;

    }

    //Check's the placement of a ship on a board is valid
    bool checkShipPlacement(int x, int y, string direction, Ship ship){

      //Get the ship's length
      int shipLength = ship.getSize();
      
      //1 - Check the placement fits on the board by checking the position of the end of the ship and the start of the ship and making sure they are both in the bonds of the board
      
      //Get the start position this is just where the ship was placed
      int startX = x;
      int startY = y;

      //intiialize endY and endX
      int endX;
      int endY;

      //Get the end position - this depends on what direction of the ship was Vertical or Horizontal
      if(direction == "v"){

        endX = x; //When vertical the ship's ending x position stays the same
        endY = y + (shipLength - 1); //When vertical the ship's ending y position will be moved along the y axis based on it's length 

      }
      else if(direction == "h"){

        endX = x + (shipLength - 1); //When horizontal the ship's ending x position will be moved along the x axis based on it's length 
        endY = y; //When horizontal the ship's ending y position stays the same

      }

      //Make sure the positions fit on the board
      if(!this->boardPositionExists(startX, startY) || !this->boardPositionExists(endX, endY)){

        //One of the positions does not fit on the board  
        return false;

      }

      //2 - Check that placing the ship does not overlap any other ships
      if(direction == "v"){
        
        int xIndex = startX;

        for( int yIndex = startY; yIndex <= endY; yIndex++){

          string currentCoord = this->boardRows[yIndex][xIndex];

          if(currentCoord != this->emptyMarker){

            return false;

          }

        }

      }
      else if(direction == "h"){
        
        int yIndex = startY;
        
        for(int xIndex = startX; xIndex <= endX; xIndex++){

          string currentCoord = this->boardRows[yIndex][xIndex];

          if(currentCoord != this->emptyMarker){

            return false;

          }

        }

      }

      return true;

    }

    bool boardPositionExists(int x, int y){

      if(y >= 0 && y < this->boardRows.size()){

        if(x >= 0 && x < this->boardRows[y].size()){
          
          return true;
        
        }

      }

      return false;

    }

    string getBoardPosition(int x, int y){
      
      if(this->boardPositionExists(x, y)){

        return this->boardRows[y][x];

      }else{

        return "";
      
      }

    }

    bool setBoardPosition(int x, int y, string value){
      
      if(this->boardPositionExists(x, y)){

        this->boardRows[y][x] = value;
        
        return true;

      }else{

        return false;
      
      }

    }

    string getEmptyMarker(){
      
      return this->emptyMarker;

    }

    string getMissMarker(){
      
      return this->missMarker;

    }

    string getHitMarker(){
      
      return this->hitMarker;

    }

    bool addMissedShot(int x, int y){

      if(this->setBoardPosition(x, y, this->missMarker)){

        return true;

      }

      return false;
      
    }

    bool addHitShot(int x, int y){

      if(this->setBoardPosition(x, y, this->hitMarker)){

        return true;

      }

      return false;

    }

    bool isValidShot(int x, int y){

      string shot = this->getBoardPosition(x, y);

      if(shot != this->hitMarker && shot != this->missMarker && shot != ""){
        
        return true;
      
      }else{

        return false;
      
      }

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
              
              string currentLabel = convertNumberToLetters(col);

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

    //Converts a coordinate e.g. A5 to either the X or Y index for the boardRows vector
    int convertCoordinateToIndex(string coordinate, char type){
      
      bool alphaEnd = false;
      string numbers = "";
      string letters = "";
      
      for(int x = 0; x < coordinate.length(); x++){
      
        //Grab current coordinate
        char currentChar = coordinate[x];

        if(isalpha(currentChar) && alphaEnd == false){
          
          letters = letters + currentChar;
        
        }else if(isdigit(currentChar)){

          //Once the first int has been encountered in the string there should be no more letters e.g. E5B6 is an invalid coordinate
          if(alphaEnd == false){
            
            //Set alphaEnd to true to stop allowing any more letters and only allow numbers
            alphaEnd = true;

          }

          numbers = numbers + currentChar;

        }else{

          //Unexpected char value not valid coordinate
          return -1;

        }

      }

      if(type == 'y' && numbers != ""){
        
        //-1 to make it an index
        return stoi(numbers) - 1;
       
      }else if(type == 'x' && letters != ""){

        return this->convertLettersToNumbers(letters);
      
      }

      return -1;

    }

    //Make sure coordinate is in format A5, AA10, BC9
    bool isValidCoordinateFormat(string coordinate){

      //Make sure coordinate is not blank
      if(coordinate == ""){

        return false;

      } 

      //Coordinate must consist of letters and numbers
      bool lettersFound = false;
      bool numbersFound = false;

      //Set alphaEnd to false - this will allow letter chars until the first number char is encountered then if another letter char is encountered
      //after the first number char the coordinate is not valid
      bool alphaEnd = false;

      for(int x = 0; x < coordinate.length(); x++){
        
        //Grab current coordinate
        char currentChar = coordinate[x];

        if(isalpha(currentChar) && alphaEnd == false){
          
          //Do nothing and let loop continue
          lettersFound = true;
        
        }else if(isdigit(currentChar)){

          //Once the first int has been encountered in the string there should be no more letters e.g. E5B6 is an invalid coordinate
          if(alphaEnd == false){
            
            //Set alphaEnd to true to stop allowing any more letters and only allow numbers
            alphaEnd = true;

          }

          numbersFound = true;

        }else{

          //Unexpected char value not valid coordinate
          return false;

        }

      }

      //All char values passed and atleast one number andd letter was found coordinate is valid
      if(lettersFound && numbersFound){

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
      

      number++;

      string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
      string letterString = "";

      while(number >= 1){
        
        int currentNumber = number;
        number = floor(currentNumber / 26);
        int remainder = currentNumber % 26;

        if (remainder == 0) {
          
          remainder = 26;
          number = number - 1;
        
        };
        
        letterString = letters.at(remainder-1) + letterString;
      
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

		int getWidth(){

      return this->width;
    
    }

    void setWidth(int value){

      this->width = value;
    
    }

		int getHeight(){

      return this->height;
    
    }

    void setHeight(int value){
      
      this->height = value;
    
    }

};