#include <iomanip>
#include <iostream>
#include <cstdlib>


#define UNASSIGNED 0

#define N 12
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

   for ( int num=1; num<=9; num++)
   {
	  if (Safe (grid, row, col, num))
	  {
		 grid[row][col]= num;
		 
		 cout << "Once" << " " << row << " " << col << " " << num << endl;

		 if (SolveSudoku(grid))
			return true;

		 grid[row][col]= UNASSIGNED;
	  }
   }
   
   return false;
}

bool SolveBackwards (int grid_1[N][N])
{
   int row;
   int col;

   if (!FindUnassignedLocation(grid_1, row, col))
	  return true;

   for (int num=9; num>=1; num--)
   {
	  if (Safe (grid_1, row, col, num))
	  {
		 grid_1[row][col]= num;

		 cout << "Twice" << " " << row << " " << col << " " << num << endl;

		 if (SolveBackwards(grid_1))
			return true;

		 grid_1[row][col]= UNASSIGNED;
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
   for  ( row=0; row<N; row++)
	  if (grid[row][col] == num)
		 return true;

   return false;
}

bool UsedInCol (int grid[N][N], int row, int col, int num)
{
   for ( col=0; col<N; col++)
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

void PrintGrid (int grid[N][N])
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
	  {4, 0, 6, 8, 7, 3, 9, 5, 0, -1,-1,-1},
	  {0, 0, 3, 9, 5, 0, 6, 0, 4, -1,-1,-1},
	  {9, 0, 0, 6, 0, 4, 8, 0, 0, -1,-1,-1},
	  {-1,-1,-1, 1, 3, 0, 0, 8, 7, 9, 5, 6},
	  {-1,-1,-1, 0, 8, 0, 0, 9, 0, 4, 0, 0},
	  {-1,-1,-1, 4, 9, 6, 0, 3, 0, 8, 7, 1},
	  {0, 0, 0, 0, 4, 0, -1,-1,-1, 6, 9, 5},
	  {0, 0, 4, 0, 6, 0, -1,-1,-1, 0, 3, 7},
	  {6, 9, 5, 0, 0, 7, -1,-1,-1, 0, 8, 4},
	  {3, 0, 0, -1,-1,-1, 7, 4, 0, 5, 0, 9},
	  {7, 4, 8, -1,-1,-1, 0, 6, 9, 3, 0, 0},
	  {0, 6, 0, -1,-1,-1, 3, 0, 0, 7, 0, 8}
   };

   int grid_1[N][N];
   int row;
   int col;
   int check=1;

   for (row= 0; row< N; row++)
   {
	  for (col=0; col< N; col++)
		 grid_1[row][col]=grid[row][col];
   }

   if (SolveSudoku(grid) != true)
   {
	  cout << "0" << endl;
   }

   if ((SolveSudoku(grid)) && (SolveBackwards(grid_1)))
   {
	  for (row= 0; row< N; row++)
	  {
		 for (col=0; col<N; col++)
			if (grid[row][col] != grid_1[row][col])
			{
			   cout << "2" << endl;
			   check=2;
			   break;
			}
		 break;
		 
	  }
   }
   
 if (check == 1)
   {
   if ((SolveSudoku(grid)) && (SolveBackwards(grid_1)))
   {
	  int i=1;

	  for (row= 0; row< N; row++)
	  {
		 for (col=0; col<N; col++)
		 {
			if (grid[row][col] == grid_1[row][col])
			{
			   while (i == 1)
			   {
				  cout << i << endl;
				  i++;
			   }
			   cout << setw(3) << grid[row][col];
			}
		 }
		 cout << "\n";
	  }
   }
   }

   return 0;
}

		 
