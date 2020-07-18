# Minesweeper-implementation-using-C-
Minesweeper game is implemented. Purely coded in c++.

The approach used was similiar to finding the number of connected components of a graph using DFS.
Two matrices are created. One for the user(myBoard) and the other(realBoard) was used to store mines positions.

After every user move, the input row and column index is matched with realBoard.
If a mine is found at the place,message is displayed conveying the user that the match is lost.

A cheatsheet has been implemented as well. It displays the location of all the mines in the board.
In the uploaded file, the cheatsheet function has not been commented out so running the program will display the realBoard.

Thank You!
