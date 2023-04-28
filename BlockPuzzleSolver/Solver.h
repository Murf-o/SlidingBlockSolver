#include "Grid.h"
#include "Snapshot.h"
#include <queue>
#include <set>
using namespace std;
#pragma once


class Solver : public Grid{
    private:
      Snapshot* root; //initial grid
      set<string> arrangements; 
      int totalMoves;
      Snapshot* solution;

    public:
      Solver(int rowSize, int colSize) : Grid(rowSize, colSize){
        root = nullptr;
        solution = nullptr;
      }

      //deconstructor
      ~Solver(){
        int size = pList.size();
        for(int i = 0; i < size; i++) {delete pList[i];}  //delete piece list
        if(solution != nullptr){delete solution;}
      }

      //returns a list of moves. returns null if a solution doesn't exist
      vector<vector<Piece*>> solvePuzzle(vector<string>& moveListAns){
        bool solutionFound = false;
        root = new Snapshot(0, pList, grid, rowSize, colSize);
        Snapshot* cur;
        queue<Snapshot*> q;
        q.push(root);

        while(!q.empty()){
          cur = q.front();
          q.pop();
          vector<Snapshot*> snaps = cur->createAllPossibleMoves(solutionFound);
          delete cur;
          if(solutionFound) {//SOLUTION found 
            moveListAns = snaps[0]->getMoveList(); 
            totalMoves = snaps[0]->getTotalMoves(); 
            solution = snaps[0];
            while(!q.empty()) {cur = q.front(); delete cur; q.pop();} //delete snaps from queue
            return solution->getGrid();
          } /////////////
          int size = snaps.size();
          for(int i = 0; i < size; i++) {   //push new snaps into queue
            if(arrangements.count(snaps[i]->toString()) == 0){  //only push snaps that haven't already been made before
                q.push(snaps[i]);
                arrangements.insert(snaps[i]->toString());
            }
            else{delete snaps[i];}  //delete the ones that have been made
          }
        }
        //NO SOLUTION
        vector<vector<Piece*>> emptyGrid;
        return emptyGrid; //ans is empty, NO SOLUTION
      }

      //addblock to grid
      int add(string pieceName, int r, int c, int w, int h, string movement){
        int handler = validPlacement(pieceName, r, c, w, h, movement);
        if(handler != 1){ return handler;}  //return errorHandler
        addBlock(pieceName, r, c, w, h, movement);
        return 1; //SUCCESS
      }

      //called in from 'add' method, used to check if block was placed correctly
      //  -1:  falls outside grid
      //  -2:  invalid movement
      //  -3: overlaps with other piece
      int validPlacement(string pieceName, int r, int c, int w, int h, string movement){
        if(r >= rowSize || c >= colSize || r+h-1 >= rowSize || c+w-1 >= colSize || r < 0 || c < 0){return -1;}
        else if(movement != "b" && movement != "v" && movement != "h" && movement != "n"){return -2;}
        else{
          for(int i = 0; i < w; i++){  //width
              if(grid[r][c+i] != nullptr) {return -3;}
          } 
          for(int i = 0; i < h; i++){  //height
              if(grid[r+i][c] != nullptr) {return -3;}
          } 
        }
        return 1; //VALID
      }

      int getTotalMoves() {return this->totalMoves;}

};