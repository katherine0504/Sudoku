#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>

#include "Sudoku.h"

#define N 12
#define SQN 2
#define UNASSIGNED 0

using namespace std;

//--------------READ IN--------------------
void Sudoku::ReadIn(void)
{
   int col;
   int row;

   for (col=0; col<N; col++)
	  for (row=0; row<N; row++)
		 cin >> ReadIngrid[col][row];
}
//--------------READ IN--------------------



//--------------SOLVE--------------------
bool Sudoku::FindUnassignedLocation(int &row, int &col)
{
    for (row =0; row< N; row ++)
    for (col=0; col< N; col++)
	   if (ReadIngrid [row][col] == UNASSIGNED)
	      return true;
	return false;
}

bool Sudoku::SolveSudoku ()
{
   int row;
   int col;

   if (!Sudoku::FindUnassignedLocation(row, col))
	  return true;

   for (int num=1; num<=9; num++)
   {
	  if (Sudoku::Safe (row, col, num))
	  {
		 
		 ReadIngrid[row][col]= num;
		 
		 if (Sudoku::SolveSudoku())
			return true;

		 ReadIngrid[row][col]= UNASSIGNED;
	  }
   }
   
   return false;
}

bool Sudoku::SolveBackwards ()
{
   int row;
   int col;

   if (!Sudoku::FindUnassignedLocation(row, col))
	  return true;

   for (int num=9; num>=1; num--)
   {
	  if (Sudoku::Safe (row, col, num))
	  {
		 ReadIngrid[row][col]= num;

		 if (Sudoku::SolveBackwards())
			return true;

		 ReadIngrid[row][col]= UNASSIGNED;
	  }
   }

   return false;
}

bool Sudoku::UsedInRow (int row, int col, int num)
{
   for  (int row=0; row<N; row++)
	  if (ReadIngrid[row][col] == num)
		 return true;

   return false;
}

bool Sudoku::UsedInCol (int row, int col, int num)
{
   for (int col=0; col<N; col++)
	  if (ReadIngrid[row][col] == num)
		 return true;

   return false;
}

bool Sudoku::UsedInBox (int boxStartRow, int boxStartCol, int num)
{
   for (int row=0; row< SQN; row++)
	  for (int col=0; col< SQN; col++)
		 if (ReadIngrid[row+boxStartRow][col+boxStartCol] == num)
			return true;

   return false;
}

bool Sudoku::Safe(int row, int col, int num)
{
     return !Sudoku::UsedInRow(row, col, num) && !Sudoku::UsedInCol(row, col, num) && !Sudoku::UsedInBox(row-(row%SQN), col-(col%SQN), num);
}

void Sudoku::PrintGrid (int grid[N][N])
{
   for (int row=0; row<N; row++)
   {
	  for (int col=0; col<N; col++)
		 
		 cout << setw(3) << grid[row][col];
	  cout << "\n";
   }
}

void Sudoku::Solve(void)
{
   int grid[N][N];
   int grid_1[N][N];
   int grid_2[N][N];
   int grid_temp[N][N];
   int row;
   int col;
   int check=1;
   
   for (row= 0; row< N; row++)
   {
	  for (col=0; col< N; col++)
	  {
//		 grid_1[row][col]=ReadIngrid[row][col];
//		 grid_2[row][col]=ReadIngrid[row][col];
		 grid_temp[row][col]=ReadIngrid[row][col];
	  }
   }

   Sudoku::SolveSudoku();
   for (row= 0; row< N; row++)
   {
	  for (col=0; col< N; col++)
	  {
		 grid_1[row][col]=ReadIngrid[row][col];
		 ReadIngrid[row][col]=grid_temp[row][col];
	  }
   }

   Sudoku::SolveBackwards();
   for (row= 0; row< N; row++)
   {
	  for (col=0; col< N; col++)
	  {
		 grid_2[row][col]=ReadIngrid[row][col];
		 ReadIngrid[row][col]=grid_temp[row][col];
	  }
   }

   if (Sudoku::SolveSudoku() != true)
   {
	  cout << "0" << endl;
   }

   if ((Sudoku::SolveSudoku()) && (Sudoku::SolveBackwards()))
   {
	  for (row= 0; row< N; row++)
	  {
		 for (col=0; col<N; col++)
			if (grid_1[row][col] != grid_2[row][col])
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
   if ((Sudoku::SolveSudoku()) && (Sudoku::SolveBackwards()))
   {
	  int i=1;

	  for (row= 0; row< N; row++)
	  {
		 for (col=0; col<N; col++)
		 {
			if (grid_1[row][col] == grid_2[row][col])
			{
			   while (i == 1)
			   {
				  cout << i << endl;
				  i++;
			   }
			   cout << setw(3) << grid_1[row][col];
			}
		 }
		 cout << "\n";
	  }
   }
  }
}

//--------------SOLVE--------------------   



//--------------GIVE QUESTION--------------------  
void Sudoku::InitialGrid(int grid[N][N])
{
	for (int row=0; row< N; row++)
	{
		for (int col=0; col< N; col++)
		{	
			if(row <=2 && col >= 9)
				grid[row][col] = -1;
			else if(row >= 3 && row <= 5 && col <=2)
				grid[row][col] = -1;
			else if(row >= 6 && row <= 8 && col >= 6 && col <= 8)
				grid[row][col] = -1;
			else if(row >= 9 && row<= 11 && col >= 3 && col <= 5)
				grid[row][col] = -1;
			else if(row <= 11)
				grid[row][col] = 0;
		}
	}
}

void Sudoku::PrintGrid2 (int grid[N][N])
{
	for (int row=0; row< N; row++)
	{
		for (int col=0; col< N; col++)
		{
			cout << setw(3) << grid[row][col];
		}
		cout << "\n";
	}
}

int Sudoku::getBoxStartCol(int range)
{
	int BoxStartCol;

	if(range <= 2)
		BoxStartCol = range*3;
	else if(range <= 5)
		BoxStartCol = (range%3+1)*3;
	else if(range <= 8)
	{
		if(range == 6)
			BoxStartCol = 0;
		else if(range == 7)
			BoxStartCol = 3;
		else
			BoxStartCol = 9;
	}
	else if(range <= 11)
	{
		if(range == 9)
			BoxStartCol = 0;
		else if(range  == 10)
			BoxStartCol = 6;
		else
			BoxStartCol = 9;
	}
	return BoxStartCol;
}

bool Sudoku::isSafe (int grid[N][N], int row, int col, int num)
{
	for(int i=0; i<N; i++)
	{
		if(grid[row][i] == num && i != col)
			return false;
		if(grid[i][col] == num && i != row)
			return false;
	}
	
	return true;
}

bool Sudoku::Create(int grid[N][N])
{
	int BoxStartRow;
	int BoxStartCol;
	int pos;
	int row;
	int col;
	int error_count;
	bool restart = 1;
	do
	{
///////////////////////////////////////////////////// initial the array all elements
		Sudoku::InitialGrid(grid);
		int num = 1;
		error_count = 0;  // we give the 100 chance for a num
/////////////////////////////////////////////////////
		for (int i = 0; i < 9; i++)
		{
			if(error_count >= 30)
				break;
			for(int j = 0; j< 12; j++)//go 9 boxes
			{
				if(error_count >= 30)
					break;
				BoxStartRow = ((j/3)*3);
				BoxStartCol = getBoxStartCol(j);
				error_count = 0;
				do
				{
					pos = rand()%9;
					int row_offset = pos/3;
					int col_offset = pos%3;
					row = BoxStartRow + row_offset;
					col = BoxStartCol + col_offset;
					if(Sudoku::isSafe(grid, row, col, num) && grid[row][col] == 0)
					{
						if(i == 8 && j == 11 && error_count < 30)
							restart = 0; // the last element so end the restart

						grid[row][col] = num;						
						break;
					}
					else
					{
						error_count++;
					}
				}while(error_count < 30);
			}
			num++;// num = 1 2 3 4 ... 9
		}		
	}while(restart);
	return true;
}

void Sudoku::Blank(int grid[N][N], int BlankNum)
{
	int pos, row, col;
	for(int i=0; i< BlankNum; i++)
	{
		while(1)
		{
			pos = rand()%144; // 12*12
			row = pos/12;
			col = pos%12;
			if(grid[row][col] != -1 && grid[row][col] != 0)
			{
				grid[row][col] = 0;
				break;
			}
		}
	}
}

void Sudoku::GiveQuestion(void)
{
	srand(time(NULL));
	int grid[N][N];
	int grid_1[N][N];
	int grid_2[N][N];
	int row;
	int col;
	int restart=1;

	do 
	{
	   if (Sudoku::Create(grid) != true)
		  cout << "DNE" << endl;
	   
	   Sudoku::Blank(grid, 30);
	   
	   for (row=0; row<N; row++)
	   {
		  for (col=0; col<N; col++)
		  {
			 ReadIngrid[row][col]= grid[row][col];
		  }
	   }

	   Sudoku::SolveSudoku();
	   for (row=0; row<N; row++)
	   {
		  for (col=0; col<N; col++)
		  {
			 grid_1[row][col]=ReadIngrid[row][col];
			 ReadIngrid[row][col]=grid[row][col];
		  }
	   }

	   Sudoku::SolveBackwards();
	   for (row=0; row<N; row++)
	   {
		  for (col=0; col<N; col++)
		  {
			 grid_2[row][col]=ReadIngrid[row][col];
			 ReadIngrid[row][col]=grid[row][col];
		  }
	   }

	   cout << "---grid_2---" <<endl;
	   Sudoku::PrintGrid(grid_2);
   
	   if ( (Sudoku::SolveSudoku()) && (Sudoku::SolveBackwards()) )
	   {
		  for (row=0; row<N; row ++)
		  {
			 for (col=0; col<N; col++)
			 {
				if (grid_1[row][col] != grid_2[row][col])
				   restart=0;
			 }
		  }
	   }
	}while(restart);

	cout << endl << "---Answer---" <<endl;
	Sudoku::PrintGrid2(grid);

}

//--------------GIVE QUESTION--------------------
