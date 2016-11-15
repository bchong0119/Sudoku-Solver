Sudoku Solver
Borah Chong
3/4/16

The purpose of this program is to read in an unfinished Sudoku puzzle and to attempt to solve the puzzle using different algorithms. The user can enter the name of a sudoku puzzle to solve, and the program will then try to solve it. If it cannot be solved, then it will print that the problem could not be solved, and will display the puzzle up to where the programs algorithms could solve it to. If it can be solved, it will print that the problem can be solved and will also show the finished Sudoku puzzle. 

The Sudoku puzzle files are just text files that contain each row of numbers for the puzzle, where each column is separated by a space, and each row is separated by a new line. In positions that are empty, a 0 is inputted as a placeholder. 

To implement this, a 3D vector was used to keep track of what possible values could go inside each element in the 9x9 Sudoku puzzle. 2 different algorithms were used to attempt to solve the puzzle. The first was a simple algorithm that looks through all the possible values at each position, and if there is only one possible value, then that value is placed on the board, and the rest of the possible values in the 3D array are updated. The second algorithm is called the "singleton" algorithm. It is an algorithm that looks within each row, column, and minigrid (3x3 section) to check if there is a "singleton" value" - one that only appears once in one cell within a row, column, or minigrid. If one is found, it places that value onto the board and updates the 3D vector of possible values. These two algorithms can solve many, but not all, Sudoku puzzles. 
