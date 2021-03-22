//below is code from Mike about the Letter coord issue

// #include <iostream>





// std::string index_colref(int idx) {
// //convert index to 'column reference'; valid range 0 to 702 (ZZ)
// //invalid indexes return and empty string
// std::string coords = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
// std::string reference = ""; //set default return

// if(idx >= 0 && idx <= ((26*26)+26)) { //check in valid range
// int x = idx/26; //check range; 0 if A..Z
// if(x == 0) {
// reference = coords[idx]; //return reference
// } else {
// idx = idx - (x * 26); //update index
// reference = coords[(x-1)]; //add initial column ref; A..Z
// reference += coords[idx]; //add secondary column ref; AA..ZZ
// }
// }
// return reference;
// }

// int main() {
// int idx = colref_index("A");
// std::string colref = index_colref(idx);

// std::cout << "\nindex value: " << idx;
// std::cout << "\ncolumn reference: " << colref;
// std::cout << "\n";
// }

// const int rows = 10;
// const int elements = 10;
// int maxShips = 10;

// int matrix[rows][elements];

// void clearBoard() {
//     for (int i=0;i < rows; i++)
//     {
//       for (int j=0;j < elements; j++)
//       {
//         matrix[i][j] = 0;
//       }
//     }
// }

// void createBoard() {
//     for (int i=0;i < rows; i++)
//     {
//       for (int j=0;j < elements; j++)
//       {
//         cout << matrix[i][j] << " ";
//       }
//     cout << endl;
//     }
// }

// void placeShips() {
//   int s = 0;
//   while(s < maxShips)
//   {
//     int x = rand() % rows;
//     int y = rand() % elements;
//     if (matrix[x][y] != 1) {
//         s++;
//         matrix[x][y] = 1;

//     }
//   }
// }

// class Person {
//   private:
//     string firstName;
//     string lastName;

//   public:
//     Person() {
//     }

//     string getName() {
//       return this->firstName + " " + this->lastName;
//     };

//     void setFirstName(string value) {
//       this->firstName=value;
//     }

//     void setLastName(string value) {
//       this->lastName=value;
//     }

//     string getFirstName() {
//       return this->firstName;
//     }

//     string getLastName() {
//       return this->lastName;
//     }
// };