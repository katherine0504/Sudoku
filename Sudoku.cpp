#include <iostream>
#include <string>
#include <cstdlib>

#include "Sudoku.h"

#define N 12 //總共為12*12的數獨
#define SQN 3 //每個box是3*3
#define UNASSIGNED 0 //要被填入數字的地方設為0(UNASSIGNED)

using namespace std;

//--------------READ IN--------------------

//把數獨 讀入 ReadIngrid
void Sudoku::ReadIn(void)
{
   int col;
   int row;

   for (row=0; row<N; row++)
	  for (col=0; col<N; col++)
		 cin >> ReadIngrid[row][col];
}

//--------------READ IN--------------------



//--------------SOLVE--------------------

// 找到需要被填入數字的地方
bool Sudoku::FindUnassignedLocation(int &row, int &col)
{
    for (row =0; row< N; row++)
    for (col=0; col< N; col++)
	   if (ReadIngrid [row][col] == UNASSIGNED)
	      return true;
	return false;
}

//從1~9解數獨
bool Sudoku::SolveSudoku ()
{
   int row;
   int col;

   //如果沒有找到需要被填入數字的地方，表示數獨已經完成
   if (!Sudoku::FindUnassignedLocation(row, col))
	  return true;

   // 找到需要被填入的地方後，從1~9開始試
   // 帶入後到行、列、大方格中檢查
   // 若有重複的則把格子歸0後重新開始
   // 並用recursive解其他的數字
   for (int num=1; num<=9; num++)
   {
	  if (Sudoku::Safe(row, col, num))
	  { 
		 ReadIngrid[row][col]= num;
		 
		 if (Sudoku::SolveSudoku())
			return true;
	  }
   }
   ReadIngrid[row][col]=UNASSIGNED;
   return false;
}

//從9~1解數獨
bool Sudoku::SolveBackwards ()
{
   int row;
   int col;

   //如果沒有找到需要被填入數字的地方，表示數獨已經完成
   if (!Sudoku::FindUnassignedLocation(row, col))
	  return true;

   // 找到需要被填入的地方後，從1~9開始試
   // 帶入後到行、列、大方格中檢查
   // 若有重複的則把格子歸0後重新開始
   // 並用recursive解其他的數字
   for (int num=9; num>=1; num--)
   {
	  if (Sudoku::Safe (row, col, num))
	  {
		 ReadIngrid[row][col]= num;

		 if (Sudoku::SolveBackwards())
			return true;
	  }
   }
   ReadIngrid[row][col]=UNASSIGNED;
   return false;
}

//檢查數字是否在row中被用過
bool Sudoku::UsedInRow (int row, int col, int num)
{
   for  (int row=0; row<N; row++)
	  if (ReadIngrid[row][col] == num)
		 return true;

   return false;
}

//檢查數字是否在column中被用過
bool Sudoku::UsedInCol (int row, int col, int num)
{
   for (int col=0; col<N; col++)
	  if (ReadIngrid[row][col] == num)
		 return true;

   return false;
}

//檢查數字是否在大格子中被用過
bool Sudoku::UsedInBox (int boxStartRow, int boxStartCol, int num)
{
   for (int row=0; row< SQN; row++)
	  for (int col=0; col< SQN; col++)
		 if (ReadIngrid[row+boxStartRow][col+boxStartCol] == num)
			return true;

   return false;
}

//檢查數字是否是正確的
//如果數字沒有在row column和格子中被用過
//表示數字是正確的
bool Sudoku::Safe(int row, int col, int num)
{
     return !Sudoku::UsedInRow(row, col, num) && !Sudoku::UsedInCol(row, col, num) && !Sudoku::UsedInBox(row-(row%SQN), col-(col%SQN), num);
}

//印出數獨
void Sudoku::PrintGrid (int grid[N][N])
{
   for (int row=0; row<N; row++)
   {
	  for (int col=0; col<N; col++)
		 
		 cout << grid[row][col] << " ";
	  cout << "\n";
   }
}

//解數獨的function
void Sudoku::Solve(void)
{
   int grid_1[N][N]; //存solvesudoku的結果
   int grid_2[N][N]; //存solvebackwards的結果
   int grid_temp[N][N]; //暫存讀進來的原始數獨
   int row;
   int col;
   
   // 把原始讀進來的數獨存到grid_temp中
   for (row= 0; row< N; row++)
   {
	  for (col=0; col< N; col++)
	  {
		 grid_temp[row][col]=ReadIngrid[row][col];
	  }
   }

   //從1~9解數獨 並先宣告check儲存"是不是有解"的判斷
   bool check = Sudoku::SolveSudoku();
   
   //把第一次解完的數獨存到grid_1中
   //把原始的數獨存回ReadIngrid中
   for (row= 0; row< N; row++)
   {
	  for (col=0; col< N; col++)
	  {
		 grid_1[row][col]=ReadIngrid[row][col];
		 ReadIngrid[row][col]=grid_temp[row][col];
	  }
   }

   //從9~1解數獨 並先宣告check2儲存"是不是有解"的判斷
   bool check2 = Sudoku::SolveBackwards();
   
   //把第二次解完的數獨存到grid_2中
   //把原始的數獨存回ReadIngrid中
   for (row= 0; row< N; row++)
   {
	  for (col=0; col< N; col++)
	  {
		 grid_2[row][col]=ReadIngrid[row][col];
		 ReadIngrid[row][col]=grid_temp[row][col];
	  }
   }

   //如果沒有解 就輸出0 並結束程式
   if (check != true)
   {
	  cout << "0" << endl;
	  exit(0);
   }

   //如果有解 且從1~9和從9~1解出來的解不同 表示為多重解
   //輸出2並結束程式
   if (check && check2)
   {
	  for (row= 0; row< N; row++)
	  {
		 for (col=0; col<N; col++)
			if (grid_1[row][col] != grid_2[row][col])
			{
			   cout << "2" << endl;
			   exit(0);
			}
	  }
   }

   //若都不符合前兩者 即為唯一解
   //先輸出1 之後 再將數獨印出來
   cout << "1" << endl;
   for (row= 0; row< N; row++)
   {
	  for (col=0; col<N; col++)
	  {
		 cout << grid_1[row][col] << " ";
	  }
	  cout << "\n";
   }
}

//--------------SOLVE--------------------   



//--------------GIVE QUESTION--------------------  

//把數獨初始化
//將-1的位置固定 其他的位置先歸0
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

//印出數獨
void Sudoku::PrintGrid2 (int grid[N][N])
{
	for (int row=0; row< N; row++)
	{
		for (int col=0; col< N; col++)
		{
			cout << grid[row][col] << " ";
		}
		cout << "\n";
	}
}


//找出每個大格子最左上角的那格的位置
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

//因為是在每一個大格子裡面填數字 所以格子裡的數字一定不會重複
//所以只要檢查在行跟列中有沒有重複就可以
bool Sudoku::isSafe (int grid[N][N], int row, int col, int num)
{
	for(int i=0; i<N; i++)
	{
		if((grid[row][i] == num) && (i != col))
			return false;
		if((grid[i][col] == num) && (i != row))
			return false;
	}
	
	return true;
}

bool Sudoku::Create(int grid[N][N])
{
	int BoxStartRow;
	int BoxStartCol;
	int pos; //在大格子中的位子
	int row;
	int col;
	int error_count; //計算每個數字填失敗的次數
	bool restart = 1; //判斷是否要重新產生數獨
	do
	{
		Sudoku::InitialGrid(grid); //把數獨初始化
		int num = 1; //數字從1開始填
		error_count=0;
		
		for (int i = 0; i < 9; i++)
		{
			if(error_count >= 30)
				break; //如果填不進去的次數超過30次就整個重新產生數獨
			for(int j = 0; j< 12; j++) //在大格子中一個一個填同一個數字
			{
				if(error_count >= 30)
					break;
				BoxStartRow = ((j/3)*3);
				BoxStartCol = getBoxStartCol(j);// 找到每個大格子最左上的那格的位置
				error_count = 0;
				do
				{
					pos = rand()%9; //隨機產生一個亂數 代表他在大格子中的相對位置
					//找出他在整個數獨的絕對位置
					int row_offset = pos/3;
					int col_offset = pos%3; 
					row = BoxStartRow + row_offset;
					col = BoxStartCol + col_offset;
					if(Sudoku::isSafe(grid, row, col, num) && grid[row][col] == 0)
					{
						if(i == 8 && j == 11 && error_count < 30)
							restart = 0; // 因為最後一個數字都填完 而且錯誤次數小於30 就結束產生數獨

						grid[row][col] = num; //把值填進去						
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

// 挖空格的function
void Sudoku::Blank(int grid[N][N], int BlankNum) //BlankNum 就是要挖的空格數
{
	int pos, row, col;
	for(int i=0; i< BlankNum; i++)
	{
		while(1)
		{
			pos = rand()%144; //隨機產生一個position 再把position轉換為數獨中的位置
			row = pos/12;
			col = pos%12;
			//如果那格不是-1或是0(已經挖過的格子) 就把他挖掉
			if((grid[row][col] != -1) && (grid[row][col] != 0))
			{
				grid[row][col] = 0;
				break;
			}
		}
	}
}

//產生問題的function
void Sudoku::GiveQuestion(void)
{
	srand(time(NULL));
	int grid[N][N];
	int grid_1[N][N];
	int grid_2[N][N];
	int row;
	int col;
	int restart=0; //判斷是否要重新

	do 
	{
	   //如果無法產生數獨 輸出DNE
	   if (Sudoku::Create(grid) != true)
		  cout << "DNE" << endl;
	   
	   // 產生數獨後挖10個空格
	   Sudoku::Blank(grid, 10);
	   
	   //把grid的數值複製到ReadIngrid
	   for (row=0; row<N; row++)
	   {
		  for (col=0; col<N; col++)
		  {
			 ReadIngrid[row][col]= grid[row][col];
		  }
	   }

	   //拿ReadIngrid去解
	   //並用check去暫存是否有成功
	   bool check= Sudoku::SolveSudoku();
	   
	   //把第一次解的結果存到grid_1
	   //把原始的grid複製到ReadIngrid裡面
	   for (row=0; row<N; row++)
	   {
		  for (col=0; col<N; col++)
		  {
			 grid_1[row][col]=ReadIngrid[row][col];
			 ReadIngrid[row][col]=grid[row][col];
		  }
	   }

	   //拿ReadIngrid去解
	   //並用check2去暫存是否有成功
	   bool check2= Sudoku::SolveBackwards();
	   
	   //把第二次解的結果存到grid_2
	   //把原始的grid複製到ReadIngrid裡面
	   for (row=0; row<N; row++)
	   {
		  for (col=0; col<N; col++)
		  {
			 grid_2[row][col]=ReadIngrid[row][col];
			 ReadIngrid[row][col]=grid[row][col];
		  }
	   }
   
	   //若兩者都有解但是卻是多重解的話重新產生題目	   
	   if (check && check2)
	   {
		  for (row=0; row<N; row ++)
		  {
			 for (col=0; col<N; col++)
			 {
				if (grid_1[row][col] != grid_2[row][col])
				   restart=1;
			 }
		  }
	   }
	}while(restart);

	//把最後產生好的數獨印出來
	Sudoku::PrintGrid2(grid);

}

//--------------GIVE QUESTION--------------------
