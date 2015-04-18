#include <iostream>
#include <cstdlib>
#include <iomanip>

#define N 12
#define SQN 2

using namespace std;

int main()
{
   int col;
   int row;
   int grid[N][N];

   for (col=0; col<N; col++)
	  for (row=0; row<N; row++)
		 cin >> grid[col][row];

   for (col=0; col<N; col++)
   {
	  for (row=0; row<N; row++)
		 cout << setw(3) << grid[col][row];
	  
	  cout << endl;
   }


   return 0;
}



