#include <string>
#include <vector>
#pragma once
using namespace std;

//  Author Information

//  File Information

class Piece{
    private:
      string name;
      int width;
      int height;
      string direction;


    public:

      //constructor
      Piece(string name, int w, int h, string d){
        this->name = name;
        this->width = w;
        this->height = h;
        this->direction = d;
      }

      //determines whether the piece can only move up and down
      bool moveVert(){
        if(direction == "v")  {return true;}
        return false;
      }

      //determines whether the piece can only move horizontally
      bool moveHoriz(){
        if(direction == "h")  {return true;}
        return false;
      }

      //determines whether piece can move horizontally and vertically
      bool moveBoth(){
        if(direction == "b")  {return true;}
        return false;
      }

      int getWidth()    {return width;}

      int getHeight()    {return height;}

      string getName()  {return name;}
};