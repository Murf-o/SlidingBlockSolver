//    Author Information
/*
  Sebastian Barroso
  sbarr9
  661337995
*/

//    Program information

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "Solver.h"

using namespace std;

int main(int argc, char** argv){
  if ( argc != 2 ) { // argc should be 2 for correct execution
    // We print argv[0] assuming it is the program name
    cout<<"usage: "<< argv[0] <<" <filename>\n";
    exit(0);
  }
 
  // We assume argv[1] is a filename to open
  ifstream the_file ( argv[1] );
  // Always check to see if file opening succeeded
  if ( !the_file.is_open() ) {
    cout<<"Could not open file: " << argv[1] << "\n";
    exit(0);
  }

  cout << "Welcome to Sliding Block Puzzle\n";
  cout << "Using data from puzzle: " << argv[1] << endl;
  
  bool firstLine = false; //used to read size of grid
  bool secondLine = false;
  string line;
  string input;
  int colSize, rowSize;
  int blockRow, blockCol;
  int blockWidth, blockHeight;
  string movement;
  int handler;

  //used to determine name of pieces
  string numNames[60] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y"};
  int ind = 0;
  //object used for game
  Solver* game; 

  

  // read in input file and set up initial puzzle configuration
  while (std::getline(the_file, line)) {
    std::istringstream iss(line);
    cout << line << endl;    // this is to verify data input and should not be part of final code
    
    if(!firstLine){ //read grid sizes
      firstLine = true;
      iss >> rowSize;
      iss >> colSize;
      //validate size
      if(rowSize <= 0)  {cout << "Error: Number of rows must be greater than zero" << endl;   return -1;}
      if(colSize <= 0)  {cout << "Error: Number of columns must be greater than zero" << endl;  return -1;}
      game = new Solver(rowSize, colSize);
    }////////////////////

    else if(!secondLine){  //read position of goal piece
      secondLine = true;
      iss >> blockRow;
      iss >> blockCol;
      iss >> blockWidth;
      iss >> blockHeight;
      iss >> movement;

      handler = game->add("Z", blockRow-1, blockCol-1, blockWidth, blockHeight, movement);
      //if invalid piece, set secondLine to false -- next piece becomes goal piece
      if(handler == -1)  {
        cout << "Warning: Piece with starting position of " << blockRow << ", " << blockCol << " falls outside of grid" << endl; 
        secondLine = false;
      }
      else if (handler == -2){ //movement not valid
        cout << "Warning: Piece with starting position of " << blockRow << ", " << blockCol << " has invalid movement" << endl;
        secondLine = false;
      }
      else if(handler == -3){  //if overlaps with other space
        cout << "Warning: Piece with starting position of " << blockRow << ", " << blockCol << " overlaps with another piece" << endl;
        secondLine = false;
      }
    }////////////////
    else{ //read position of other pieces
    if(ind >= 60){  //too many pieces
      cout << "Warning: grid has exceeded max number of blocks (60)" << endl;
      continue;
    }
      iss >> blockRow;
      iss >> blockCol;
      iss >> blockWidth;
      iss >> blockHeight;
      iss >> movement;
      handler = game->add(numNames[ind++], blockRow-1, blockCol-1, blockWidth, blockHeight, movement);
      //if invalid piece, set secondLine to false -- next piece becomes goal piece
      if(handler == -1)  {
        cout << "Warning: Piece with starting position of " << blockRow << ", " << blockCol << " falls outside of grid" << endl; 
        --ind;
      }
      else if (handler == -2){ //movement not valid
        cout << "Warning: Piece with starting position of " << blockRow << ", " << blockCol << " has invalid movement" << endl;
        --ind;
      }
      else if(handler == -3){  //if overlaps with other space
        cout << "Warning: Piece with starting position of " << blockRow << ", " << blockCol << " overlaps with another piece" << endl;
        --ind;
      }
    }
  }

  //  print out initial puzzle configuration
  cout << "\nInitial puzzle configuration:\n" << endl;
  for(int i = 0; i < colSize + 2; i++){
    cout << "*";
  }
  cout << endl;
  for(int i = 0; i < rowSize; i++){
    cout << "*";
    for(int j = 0; j < colSize; j++){
      if(game->getGrid()[i][j] == nullptr){cout << ".";}
      else{cout << game->getGrid()[i][j]->getName();}
    }
    cout << "*" << endl;
  }  

  for(int i = 0; i < colSize + 2; i++){
    cout << "*";
  }
  cout << endl;
  
  //  find solution if one exists
  vector<string> moves;
  vector<vector<Piece*>> grid = game->solvePuzzle(moves);
  if(grid.empty())  {cout << "This puzzle has no solution" << endl; delete game; return 1;}
  
  cout << "This puzzle is solvable in " << game->getTotalMoves() << " steps" << endl;
  for(string str: moves){
    cout << str << endl;
  }

  cout << "Final puzzle configuration: " << endl;
  for(int i = 0; i < colSize + 2; i++){
    cout << "*";
  }
  cout << endl;
  for(int i = 0; i < rowSize; i++){
    cout << "*";
    for(int j = 0; j < colSize; j++){
      if(grid[i][j] == nullptr){cout << ".";}
      else{cout << grid[i][j]->getName();}
    }
    cout << "*" <<  endl;
  }
  for(int i = 0; i < colSize + 2; i++){
    cout << "*";
  }
  cout << endl;
  delete game;
  return 1;
}
