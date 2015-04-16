#include <iomanip>
#include <iostream>
#include <cstdlib>


#define UNASSIGNED 0

#define N 9
#define SQN 2

using namespace std;

bool FindUnassignedLocation(int grid [N][N], int &row, int &col);

bool Safe(int grid[N][N], int row, int col, int num);

bool SolveSudoku (int grid[N][N])
{
   int row;
   int col;

   if (!FindUnassignedLocation(grid, row, col))
	  return true;

   for (int num=9; num>=0; num--)
   {
	  if (Safe (grid, row, col, num))
	  {
		 grid[row][col]= num;

		 if (SolveSudoku(grid))
			return true;

		 grid[row][col]= UNASSIGNED;
	  }
   }
   
   return false;
}

bool FindUnassignedLocation(int grid [N][N], int &row, int &col)
{
    for (row =0; row< N; row ++)
    for (col=0; col< N; col++)
	   if (grid [row][col] == UNASSIGNED)
	      return true;
	return false;
}


bool UsedInRow (int grid[N][N], int row, int col, int num)
{
   for  (int row=0; row<N; row++)
	  if (grid[row][col] == num)
		 return true;

   return false;
}

bool UsedInCol (int grid[N][N], int row, int col, int num)
{
   for (int col=0; col<N; col++)
	  if (grid[row][col] == num)
		 return true;

   return false;
}

bool UsedInBox (int grid[N][N], int boxStartRow, int boxStartCol, int num)
{
   for (int row=0; row< SQN; row++)
	  for (int col=0; col< SQN; col++)
		 if (grid[row+boxStartRow][col+boxStartCol] == num)
			return true;

   return false;
}

bool Safe (int grid[N][N], int row, int col, int num)
{
   return !UsedInRow(grid, row, col, num) && !UsedInCol(grid, row, col, num) && !UsedInBox(grid, row-(row%SQN), col-(col%SQN), num);
}

void printGrid (int grid[N][N])
{
   for (int row=0; row<N; row++)
   {
	  for (int col=0; col<N; col++)
		 
		 cout << setw(3) << grid[row][col];
	  cout << "\n";
   }
}

int main()
{
   int grid[N][N]={
	  {9,8,5,3,6,1,2,7,4},
	  {7,0,0,8,2,9,3,5,6},
	  {6,3,2,4,5,7,1,9,8},
	  {8,0,0,9,3,6,7,2,5},
	  {3,5,9,2,7,8,6,4,1},
	  {2,7,6,5,1,4,9,8,3},
	  {5,2,7,6,4,3,8,1,9},
	  {4,9,3,1,8,2,5,6,7},
	  {1,6,8,7,9,5,4,3,2}
   };

   if (SolveSudoku(grid) == true)
   {
	  cout << "1" << endl;
	  printGrid(grid);
   }

   else
	  cout << "0" << endl;

   return 0;
}

		 
