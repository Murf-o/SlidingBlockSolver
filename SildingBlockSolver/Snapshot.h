#include "Piece.h"
#include "Movement.h"
#include <vector>
#pragma once

class Snapshot{
  private:
    int totalMoves;
    vector<Piece*> pList;  //vector of all pieces in list, used to check if moveable, then move -- same for all objects
    int rowSize;
    int colSize;
    vector<string> moveList;
    vector<vector<Piece*>> grid;
  
  public:

    Snapshot(int totalMoves, vector<Piece*> pList, vector<vector<Piece*>> grid, int r, int c){
      this->totalMoves = totalMoves;
      this->pList = pList;
      this->grid = grid;
      this->rowSize = r;
      this->colSize = c;
    }

    //constructor with moveList
    Snapshot(int totalMoves, vector<string> moveList, vector<vector<Piece*>> grid, vector<Piece*> pList, int r, int c){
      this->totalMoves = totalMoves;
      this->pList = pList;
      this->moveList = moveList;
      this->grid = grid;
      this->rowSize = r;
      this->colSize = c;
    }


    void setRowColSize(int r, int c){
      rowSize = r;
      colSize = c;
    }

    //sets Plist
    void setPlist(vector<Piece*> pList){
      this->pList = pList;
    }

    //creates all new possible snaps from current snap. If it returns vector of size 1, it's possible that that snapshot is a solution
    vector<Snapshot*> createAllPossibleMoves(bool &solution){
      vector<Snapshot*> newSnaps;
      Snapshot* sTmp;
      vector<vector<Piece*>> gridCpy;
      Piece* p;
      int size = pList.size();
      vector<string> movesTmp;
      for(int i = 0; i < size; i++){
        p = pList[i];
        int r, c;
        findPiece(r, c, p);   //find piece location -- r and c are passed by reference
        gridCpy = this->grid;
        //if can move up block up, add to 'newSnaps', if can move down add... (do for all pieces)
        movesTmp = this->moveList;
        int movesTowardsDirection = 0;  //used to see how many moves a block moved in one direction
        //if its a block that moves both ways
        if(p->moveBoth()){
         
          while(possibleMoveUp(r-movesTowardsDirection, c, p->getWidth(), p->getHeight(), p)){
            gridCpy = Movement::moveUp(gridCpy, r-movesTowardsDirection, c, p->getWidth(), p->getHeight(), p);
            string str = "Piece " + p->getName() + " moves up " + to_string(movesTowardsDirection+1) + " space(s)";
            movesTmp.push_back(str);
            sTmp = new Snapshot(this->totalMoves+1, movesTmp, gridCpy, this->pList, this->rowSize, this->colSize);
            newSnaps.push_back(sTmp);
            ++movesTowardsDirection;
            movesTmp = this->moveList;
          }
          gridCpy = this->grid;
          movesTowardsDirection = 0;
          movesTmp = this->moveList;
          while(possibleMoveDown(r+movesTowardsDirection, c, p->getWidth(), p->getHeight(), p)){
            gridCpy = Movement::moveDown(gridCpy, r+movesTowardsDirection, c, p->getWidth(), p->getHeight(), p);
            string str = "Piece " + p->getName() + " moves down " + to_string(movesTowardsDirection+1) + " space(s)";
            movesTmp.push_back(str);
            sTmp = new Snapshot(this->totalMoves+1, movesTmp, gridCpy, this->pList, this->rowSize, this->colSize);
            newSnaps.push_back(sTmp);
            ++movesTowardsDirection;
            movesTmp = this->moveList;
          }
          gridCpy = this->grid;
          movesTowardsDirection = 0;
          movesTmp = this->moveList;
          while(possibleMoveLeft(r, c-movesTowardsDirection, p->getWidth(), p->getHeight(), p)){         
            gridCpy = Movement::moveLeft(gridCpy, r, c-movesTowardsDirection, p->getWidth(), p->getHeight(), p);
            string str = "Piece " + p->getName() + " moves left " + to_string(movesTowardsDirection+1) + " space(s)";
            movesTmp.push_back(str);
            sTmp = new Snapshot(this->totalMoves+1, movesTmp, gridCpy, this->pList, this->rowSize, this->colSize);
            newSnaps.push_back(sTmp);
            ++movesTowardsDirection;
            movesTmp = this->moveList;
          }
          gridCpy = this->grid;
          movesTowardsDirection = 0;
          movesTmp = this->moveList;
          while(possibleMoveRight(r, c+movesTowardsDirection, p->getWidth(), p->getHeight(), p)){

            gridCpy = Movement::moveRight(gridCpy, r, c+movesTowardsDirection, p->getWidth(), p->getHeight(), p);
            string str = "Piece " + p->getName() + " moves right " + to_string(movesTowardsDirection+1) + " space(s)";
            movesTmp.push_back(str);
            sTmp = new Snapshot(this->totalMoves+1, movesTmp, gridCpy, this->pList, this->rowSize, this->colSize);
            newSnaps.push_back(sTmp);           
            //check if first block was moved to a solution spot, if true return that single snap
            if(isSolution(gridCpy)){
              solution = true;
              sTmp = new Snapshot(this->totalMoves+1, movesTmp, gridCpy, this->pList, this->rowSize, this->colSize);
              //delete all snaps from vector 'newSnaps'
              int newSnapsSize = newSnaps.size();
              for(int i = 0; i < newSnapsSize; i++)  {delete newSnaps[i];} 
              vector<Snapshot*> ans;
              ans.push_back(sTmp);
              return ans;
            }
             movesTmp = this->moveList;
             ++movesTowardsDirection;
          }
          gridCpy = this->grid;
          movesTowardsDirection = 0;
          movesTmp = this->moveList;
        }
        /////////////////////////////////////////////////////
        //else, if it's a block that only moves vertically
        else if(p->moveVert()){
          while(possibleMoveUp(r-movesTowardsDirection, c, p->getWidth(), p->getHeight(), p)){
            gridCpy = Movement::moveUp(gridCpy, r-movesTowardsDirection, c, p->getWidth(), p->getHeight(), p);
            string str = "Piece " + p->getName() + " moves up " + to_string(movesTowardsDirection+1) + " space(s)";
            movesTmp.push_back(str);
            sTmp = new Snapshot(this->totalMoves+1, movesTmp, gridCpy, this->pList, this->rowSize, this->colSize);
            newSnaps.push_back(sTmp);
            ++movesTowardsDirection;
            movesTmp = this->moveList;
          }
          gridCpy = this->grid;
          movesTowardsDirection = 0;
          movesTmp = this->moveList;
          while(possibleMoveDown(r+movesTowardsDirection, c, p->getWidth(), p->getHeight(), p)){
            gridCpy = Movement::moveDown(gridCpy, r+movesTowardsDirection, c, p->getWidth(), p->getHeight(), p);
            string str = "Piece " + p->getName() + " moves down " + to_string(movesTowardsDirection+1) + " space(s)";
            movesTmp.push_back(str);
            sTmp = new Snapshot(this->totalMoves+1, movesTmp, gridCpy, this->pList, this->rowSize, this->colSize);
            newSnaps.push_back(sTmp);
            ++movesTowardsDirection;
            movesTmp = this->moveList;
          }
          gridCpy = this->grid;
          movesTowardsDirection = 0;
          movesTmp = this->moveList;
        }
        /////////////////////////////////////////////
        //else, if it's a block that only moves horizontally
        else if(p->moveHoriz()){
          while(possibleMoveLeft(r, c-movesTowardsDirection, p->getWidth(), p->getHeight(), p)){
            gridCpy = Movement::moveLeft(gridCpy, r, c-movesTowardsDirection, p->getWidth(), p->getHeight(), p);
            string str = "Piece " + p->getName() + " moves left " + to_string(movesTowardsDirection+1) + " space(s)";
            movesTmp.push_back(str);
            sTmp = new Snapshot(this->totalMoves+1, movesTmp, gridCpy, this->pList, this->rowSize, this->colSize);
            newSnaps.push_back(sTmp);
            ++movesTowardsDirection;
            movesTmp = this->moveList;
          }
          movesTowardsDirection = 0;
          movesTmp = this->moveList;
          gridCpy = this->grid;
          while(possibleMoveRight(r, c+movesTowardsDirection, p->getWidth(), p->getHeight(), p)){
            gridCpy = Movement::moveRight(gridCpy, r, c+movesTowardsDirection, p->getWidth(), p->getHeight(), p);
            string str = "Piece " + p->getName() + " moves right " + to_string(movesTowardsDirection+1) + " space(s)";
            movesTmp.push_back(str);
            sTmp = new Snapshot(this->totalMoves+1, movesTmp, gridCpy, this->pList, this->rowSize, this->colSize);
            newSnaps.push_back(sTmp);
            //check if first block was moved to a solution spot, if true return that single snap
             if(isSolution(gridCpy)){
              solution = true;
              sTmp = new Snapshot(this->totalMoves+1, movesTmp, gridCpy, this->pList, this->rowSize, this->colSize);
              //delete all snaps from vector 'newSnaps'
              int newSnapsSize = newSnaps.size();
              for(int i = 0; i < newSnapsSize; i++)  {delete newSnaps[i];} 
              vector<Snapshot*> ans;
              ans.push_back(sTmp);
              return ans;
            }
            movesTmp = this->moveList;
            ++movesTowardsDirection;
          }
          gridCpy = this->grid;
          movesTowardsDirection = 0;
          movesTmp = this->moveList;
        }
        /////////////////////////////////////////////////////////
        else{}  //cannot move piece, no new snapshots with it
        movesTowardsDirection = 0;
        movesTmp = this->moveList;
      }
      return newSnaps;
    }

    //returns whether is possible for a block to move up from its current spot
    bool possibleMoveUp(int r, int c, int w, int h, Piece* p){
      if(r-1 < 0)  {return false;}
      for(int i = 0; i < w; i++){
        if(grid[r-1][c+i] != nullptr) {return false;} 
      }
      return true;
    }

    //returns whether is possible for a block to move down from its current spot
    bool possibleMoveDown(int r, int c, int w, int h, Piece* p){
      if(r+h >= rowSize)  {return false;}
      for(int i = 0; i < w; i++){
        if(grid[r+h][c+i] != nullptr) {return false;} 
      }
      return true;
    }

    //returns whether is possible for a block to move left from its current spot
    bool possibleMoveLeft(int r, int c, int w, int h, Piece* p){
      if(c-1 < 0)  {return false;}
      for(int i = 0; i < h; i++){
        if(grid[r+i][c-1] != nullptr) {return false;} 
      }
      return true;
    }

     //returns whether is possible for a block to move Right from its current spot
    bool possibleMoveRight(int r, int c, int w, int h, Piece* p){
      if(c+w >= colSize)  {return false;}
      for(int i = 0; i < h; i++){
        if(grid[r+i][c+w] != nullptr) {return false;} 
      }
      return true;
    }

    //locates where a piece is and puts that value into 'r' and 'c'
    void findPiece(int &r, int &c, Piece* p){
      for(int i = 0; i < rowSize; i++){
            for(int j = 0; j < colSize; j++){
              if(grid[i][j] == p){r = i; c = j; return;}
            }
      }
      //if somehow not found
      cout << "piece: " << p->getName() << " not found." << endl;
    }

      //converts grid to it's string equivalent
     string toString(){
        string ans;
        string c;
        for(int i = 0; i < rowSize; i++){
          for(int j = 0; j < colSize; j++){
            if(grid[i][j] == nullptr){c = " ";}
            else  {c = grid[i][j]->getName();}
            ans += c;
          }
        }
        return ans;
      }

      //returns true if grid is a solution to the puzzle, false otherwise
      bool isSolution(vector<vector<Piece*>> g){
        for(int i = 0; i < rowSize; i++){
          if(g[i][colSize-1] != nullptr && g[i][colSize-1]->getName() == "Z")  {return true;}
        }
        return false;
      }

      vector<string> getMoveList()  {return this->moveList;}

      vector<vector<Piece*>> getGrid()  {return this->grid;}

      int getTotalMoves() {return this->totalMoves;}

      //used to help debug, prints grid out
      void printGrid(vector<vector<Piece*>> g){

        for(int i = 0; i < rowSize; i++){
          for(int j = 0; j < colSize; j++){
            if(g[i][j] == nullptr){cout << ".";}
            else{cout << g[i][j]->getName();}
          }
          cout << endl;
        }
      }

};