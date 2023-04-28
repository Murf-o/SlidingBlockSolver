//  Author Information

//  File Information

#include "Piece.h"
#include <vector>
#pragma once

class Movement{

  public:

    //returns grid, grid with piece moved up.
    //int r, c are the location of the piece. int w, h are the width and height
     static vector<vector<Piece*>> moveUp(vector<vector<Piece*>> grid, int r, int c, int w, int h, Piece* p){
        int i = r-1;
        for(int j = c; j < c+w; j++){
          grid[i][j] = p;
          grid[i+h][j] = nullptr;
        }
        return grid;
    }

    //returns grid, grid with piece moved down. 
    //int r, c are the location of the piece. int w, h are the width and height
     static vector<vector<Piece*>> moveDown(vector<vector<Piece*>> grid, int r, int c, int w, int h, Piece* p){
        int i = r+h;
        for(int j = c; j < c+w; j++){
          grid[i][j] = p;
          grid[i-h][j] = nullptr;
        }
        
        return grid;
    }

    //returns grid, grid with piece moved right. 
    //int r, c are the location of the piece. int w, h are the width and height
     static vector<vector<Piece*>> moveRight(vector<vector<Piece*>> grid, int r, int c, int w, int h, Piece* p){
        int i = c+w;
        for(int j = r; j < r+h; j++){
          grid[j][i] = p;
          grid[j][i-w] = nullptr;
        }
        
        return grid;
    }

    //returns grid, grid with piece moved left. 
    //int r, c are the location of the piece. int w, h are the width and height
     static vector<vector<Piece*>> moveLeft(vector<vector<Piece*>> grid, int r, int c, int w, int h, Piece* p){
        int i = c-1;
        for(int j = r; j < r+h; j++){
          grid[j][i] = p;
          grid[j][i+w] = nullptr;
        }
        return grid;
    }

};