#include <vector>
#include <iostream>
#include <string>
#include "Piece.h"
using namespace std;

#pragma once
//  Author Information

//  File Information

class Grid{

  protected:
    int rowSize;
    int colSize;
    vector<vector<Piece*>> grid;
    vector<Piece*> pList;

  public:

    //constructor
    Grid(int row, int col) : grid(row, vector<Piece*>(col)){
      this->colSize = col;
      this->rowSize = row;
      for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
          grid[i][j] = nullptr;
        }
      }
    }


    //adds block to the grid
    void addBlock(string pieceName, int r, int c, int w, int h, string movement){
        Piece* p = new Piece(pieceName, w, h, movement);

        //add Piece* p to everywhere its locates to grid -- depends on w and h
        for(int i = 0; i < h; i++){
          for(int j = 0; j < w; j++){
            grid[r+i][c+j] = p;
          }
        }
        pList.push_back(p);
    }

    Piece* get(int r, int c){
      return grid[r][c];
    }

    //returns grid
    vector<vector<Piece*>> getGrid(){ 
      return grid;
    }
};