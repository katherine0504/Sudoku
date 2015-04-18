#include <iostream>

#define N 12

#ifndef Sudoku_h
#define Sudoku_h

class Sudoku
{
   public:
	  void GiveQuestion(void);
	  void ReadIn(void);
	  void Solve(void);
	  
	  bool FindUnassignedLocation(int grid [N][N], int &row, int &col);
	  bool Safe(int grid[N][N], int row, int col, int num);
	  bool SolveSudoku (int grid[N][N]);
	  bool SolveBackwards (int grid_1[N][N]);
	  bool UsedInRow (int grid[N][N], int row, int col, int num);
	  bool UsedInCol (int grid[N][N], int row, int col, int num);
	  bool UsedInBox (int grid[N][N], int boxStartRow, int boxStartCol, int num);
      void PrintGrid (int grid[N][N]);
      
      void InitialGrid(int grid[N][N]);
      void PrintGrid2 (int grid[N][N]);
      int getBoxStartCol(int range);
      bool isSafe (int grid[N][N], int row, int col, int num);
      bool Create(int grid[N][N]);
      void Blank(int grid[N][N], int BlankNum);

   private:

};

#endif
