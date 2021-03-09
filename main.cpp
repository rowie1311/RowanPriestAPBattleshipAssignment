#include <iostream>
#include <cmath>
#include <cstring>
#include <chrono>
using namespace std;

const int rows = 10;
const int elements = 10;

int matrix[rows][elements];

void clearBoard() {
    for (int i=0;i < rows; i++)
    {
      for (int j=0;j < elements; j++)
      {
        matrix[i][j] = 0;
      }
    }
}

void createBoard() {
    for (int i=0;i < rows; i++)
    {
      for (int j=0;j < elements; j++)
      {
        cout << matrix[i][j] << " ";
      }
    cout << endl;
    }
}

class Person {
  private:
    string firstName;
    string lastName;

  public:
    Person() {
    }

    string getName() {
      return this->firstName + " " + this->lastName;
    };

    void setFirstName(string value) {
      this->firstName=value;
    }

    void setLastName(string value) {
      this->lastName=value;
    }

    string getFirstName() {
      return this->firstName;
    }

    string getLastName() {
      return this->lastName;
    }
};

int main() {
  clearBoard();
  createBoard();

  // Person student1;
  // student1.setFirstName("Rowan");
  // student1.setLastName("Priest");

  // Person student2;
  // student2.setFirstName("Jamie");
  // student2.setLastName("Priest");

  // cout << "Hello, My name is " + student1.getName() + "\nNice to meet you, My name is " + student2.getName();

  return 0;

}