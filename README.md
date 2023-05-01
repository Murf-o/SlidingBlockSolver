# SlidingBlockSolver


This is a program that finds the shortest possible solution to a sliding block puzzle. 
The blocks are assumed to be rectangular shapes. The program is seperated into multiple files:
slidingBlock.cpp, Solver.h, Snapshot.h, Grid.h, Movement.h, Piece.h.
The Goal Piece is labeled as "Z" on the grid. A puzzle is solved when the Goal Block is moved to the rightside of the grid. //can be changed
The direction parameter of a block represents the directions it can move.
Valid Movement:
  * "b" --  Can move horizontally and vertically
  * "h" --  Can only move horizontally
  * "v" --  Can only move vertically
  * "n" --  No movement

The input for a puzzle is read from a seperate file in the following format:

[rowSize] [colSize]
[rowPos]  [colPos]  [width] [height]  [direction]   //Goal Piece is the first block entered. If invalid, the program will use the next valid one.
[rowPos]  [colPos]  [width] [height]  [direction]   //next block
/*          other blocks...         */

If a block is invalid, it won't be entered into the puzzle's configuration
A block is invalid when:
  * Falls outside of grid
  * Invalid direction of movement
  * Overlaps with other piece
  
To solve the "What is shortest solution to this puzzle?" question, this program was designed using BFS.
I would implement that "Snapshot" class.
A snapshot is an object that holds data of the current state of the puzzle.
The current state is the current position of all pieces in the puzzle and what moves it took to reach the current state from the initial state.
Each time the program created a new Snapshot that moved a piece towards the goal, it would check whether this Snapshot was a solution.
If it was, then it immediately returns that solution and we print it out.
This guarantees us the shortest solution.
CURRENTLY DEVELOPING FRONT-END :) Enjoy.

