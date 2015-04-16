#include <iostream>

#define UNASSIGNED 0

#define N 12
#define SQN 2

bool FindUnassignedLocation(int grid [N][N], int &row, i    nt &col);

bool Safe(int grid[N][N], int row, int col, int num);

bool SolveSudoku (int grid[N][N])
{
   int row;
   int col;

   if (!FindUnassignedLocation(grid, row, col))
	  return true;

   for (int num=1; num<= N, num++)
   {
	  if (Safe (grid, row, col, num))
	  {
		 grid[row][col]= num;

		 if (SovleSudoku(grid))
			return true;

		 grid[row][col]= UNASSIGNED;
	  }
   }
   
   return false;
}

bool FindUnassignedLocation(int grid [N][N], int &row, int &col)
{
    for (row =0; row< N; row ++)
    for (col=0; col< N; clo++)
	   if (grid [row][col] == UNASSIGNED)
	      return true;
	return false;
}


bool UsedInRow (int grid[N][N], int row, int num)
{
   for  (int row=0; row<N; row++)
	  if (grid[row][col] == num)
		 return true;

   return false;
}

bool UsedInCol (int grid[N][N], int col, int num)
{
   for (int col=0; col<N; col++)
	  if (grid[row][col] == num)
		 return true;

   return false;
}

bool UsedInBox (int grid[N][N], int boxStartRow, int bozStartCol, int num)
{
   for (int row=0; row< SQN; row++)
	  for (int col=0; col< SQN; col++)
		 if (grid[row+boxStartRow][col+boxStartCol] == num)
			return true;

   return false;
}

bool Safe (int grid[N][N], int row, int col, int num)
{
   return !UsedInRow(grid, row, num) && !UsedInCol(grid, col, num) && !UsedInBox(grid, row-(row%SQN), col-(col%SQN), num);
}

void printGrid (int grid[N][N])
{
   for (int row=0; row<N; row++)
   {
	  for (int col=0; col<N; col++)
		 printf("%3d", grid[row][col]);
	  printf("\n");
   }
}


int main()
{
   int grid[N][N]=
