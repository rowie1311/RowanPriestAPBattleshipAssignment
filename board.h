#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
#include <map>
using namespace std;

class Board {
  private: 
    int width;
    int height; 
    string label;
    vector <vector<string>> boardRows;

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
          currentRow.push_back("0");

        }

        //Add the newly populated row to the vector storing all of the board rows
        this->boardRows.push_back(currentRow);

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