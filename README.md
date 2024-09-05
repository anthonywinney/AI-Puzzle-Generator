# AI-Puzzle-Generator

This is a simple AI algorithm intended to design and output a certain kind of solitaire puzzle.

__The Puzzle__

The program will give a _n_ by _n_ grid of numbers, where the user can choose _n_. The starting node is the upper left, the end node is the bottom right. The player may move in any direction by the number of Here is an example _5_ by _5_ puzzle. 

Puzzle:
3 2 1 4 2
3 4 1 2 1
4 3 2 2 1
3 2 1 3 4
1 4 2 3 0

Solution: Yes
Unique: Yes
Solution length: 14
\# of black holes: 1
\# of white holes: 3
\# of forced forward moves: 5
\# of forced backward moves: 9
Puzzle value: 59

The puzzle value and the four characteristics of the puzzle above it are in-house measurements for the quality of the puzzle.


__Running the Program__

This C++ program is designed to be run on Ubuntu.
Execute __make__ in the command line to compile.

To run, execute:

__./PuzzleGenerator [n] [n] [a] [b]__

This will generate a _n_ by _n_ puzzle ranging in values from _a_ to _b_.
