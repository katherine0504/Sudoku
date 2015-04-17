#include <iostream>
#include <iomanip>
#include <cstdlib>

#define N 12
#define SQN 2
#define UNASSIGNED 0

using namespace std;

bool FindLocation (int grid[N][N], int &row, int &col)
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
	  if (grid [row][col] == num)
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

void PrintGrid (int grid[N][N])
{
   for (int row=0; row< N; row++)
   {
	  for (int col=0; col< N; col++)

		 cout << setw(3) << grid[row][col];

	  cout << "\n";
   }
}

int main()
{
   int grid[N][N]={
	  {-1,-1,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	  {-1,-1,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	  {-1,-1,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	  {0, 0, 0, -1,-1,-1, 0, 0, 0, 0, 0, 0 },
	  {0, 0, 0, -1,-1,-1, 0, 0, 0, 0, 0, 0 },
	  {0, 0, 0, -1,-1,-1, 0, 0, 0, 0, 0, 0 },
	  {0, 0, 0, 0, 0, 0, -1,-1,-1, 0, 0, 0 },
	  {0, 0, 0, 0, 0, 0, -1,-1,-1, 0, 0, 0 },
	  {0, 0, 0, 0, 0, 0, -1,-1,-1, 0, 0, 0 },
	  {0, 0, 0, 0, 0, 0, 0, 0, 0, -1,-1,-1 },
	  {0, 0, 0, 0, 0, 0, 0, 0, 0, -1,-1,-1 },
	  {0, 0, 0, 0, 0, 0, 0, 0, 0, -1,-1,-1 }
   };

   PrintGrid(grid);

   return 0;
}
