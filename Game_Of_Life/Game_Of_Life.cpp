//Author:Randeep Shahi, John Ko, James Nicholls
//DOB: November 11, 2014
//the program will similate the game of life using an input from a text file

#include <iostream>
#include <fstream>
using namespace std;
//variables for function------------------------------------------------------------
const int MAX_ARRAY_SIZE = 40;
void PrintGen(char lifeBoard[][MAX_ARRAY_SIZE], ostream& outStream, int numRowsInBoard, int numColsInBoard, int generationNum)
{
	if(generationNum == 0)
	{
		outStream << "LIFE initial game board" << endl <<" " <<endl;
	}
	else
	{
		outStream << "LIFE gameboard: generation " << generationNum <<  endl;
	}
	int i = 0;
	int j = 0;
		for(i=0;i < numRowsInBoard;i++)
		{
			for (j=0; j < numColsInBoard; j++)
			{
				outStream << lifeBoard[i][j];
				if(j != (numColsInBoard-1))
				{
				outStream << " ";
				}
			}
         outStream << endl;
		}
	outStream <<" "<< endl << " "<< endl <<" " << endl ;
	if(generationNum==0)
	{
		outStream << " " <<endl;
	}
}

void NextGen(char lifeBoard[][MAX_ARRAY_SIZE], int numRowsInBoard, int numColsInBoard)
{
	//declare variables
	int i = 0;
	int j = 0;
	int n = 0;
	int m = 0;
	int counter = 0;
	//declare and initialize array
	char nextGenBoard[40][40] = { 0 };
	for(i=0;i<numRowsInBoard;i++)
	{
		for(j=0;j<numColsInBoard;j++)
		{
			nextGenBoard[i][j] = '.';
		}
	}
		//first two for statements stay in the middle
		for(i=1;i < (numRowsInBoard-1);i++)
		{
			for (j=1; j < (numColsInBoard-1); j++)
			{
				//next two for statements check the 8 spaces around
				for (n=(i-1);n<=(i+1);n++)
				{
					for (m=(j-1);m<=(j+1);m++)
					{
						if((n==i) && (m==j))
						{
							continue;
						}
						else if(lifeBoard[n][m] == 'X')
						{
							counter++;
						}
						else
						{
							continue;
						}

					}
				}
				if((counter == 3) && (lifeBoard[i][j] == '.')) //birth
				{
					nextGenBoard[i][j] = 'X';
				}
				else if(((counter < 2) || (counter > 3)) && (lifeBoard[i][j] == 'X'))
				{
					nextGenBoard[i][j] = '.';
				}
				else if(((counter ==2) || (counter ==3)) && (lifeBoard[i][j] == 'X'))//survival
				{
					nextGenBoard[i][j] = 'X';
				}
				counter = 0;
			}
		}
	for(i=0;i < numRowsInBoard;i++)
	{
		for (j=0; j < numColsInBoard; j++)
		{
			lifeBoard[i][j] = nextGenBoard[i][j];
		}
	}

}


//this is the main function-----------------------------------------------------------


int main()
{
		//the code is written taken the assumption that the person who is inputting the file
		//with put integers for the first 3 number and only include blank spaces, .'s, and X's
		//declare variables-----------------------------------------------------------------------------------------------------
		ifstream inStream;
		ofstream outStream;
		char InputFile[80];
		char OutputFile[80];
		int NumRow = 0;
		int NumCol = 0;
		int NumGenerations = 0;
		int i = 0;
		int j = 0;
		int counter = 0;
		char myLifeBoard[40][40];


		//ask for name of input file and open-------------------------------------------------------------------------------

		cout << "Enter the name of the input file: ";
		cin >> InputFile; //this will read the name of the file from the keyboard
		inStream.open(InputFile);//this will open the file

		if ( inStream.fail() ) //this if statement is to check if the file was openned by using its address.
		{
			cerr << "ERROR: input file not opened correctly";
			return 1;
		}

		//ask for name of output file and open-------------------------------------------------------------------------------
		cout << "Enter the name of the output file: ";
		cin >> OutputFile; //this will read the name of the file from the keyboard
		outStream.open(OutputFile);//this will open the file

		if ( outStream.fail() ) //this if statement is to check if the file was openned by using its address.
		{
			cerr << "ERROR: output file not opened correctly";
			return 2;
		}

		//this reads the number of rows in the board game and checks for errors------------------------------------------------

		if(!(inStream >> NumRow))
		{
				cerr << "ERROR: Cannot read number of rows";
				inStream.close();
				return 3;

		}
		if ((NumRow >= 40) || (NumRow <= 0)) //checks if rows are within program range
		{
				cerr << "ERROR: Read an illegal number of rows for the board";
				return 4;
		}

		//this reads the number of cols in the board game and checks for errors------------------------------------------------
		if(!(inStream >> NumCol))
		{
				cerr << "ERROR: Cannot read number of columns";
				return 5;

		}
		if ((NumCol >= 40) || (NumCol <= 0)) //checks if columns are within program range
		{
				cerr << "ERROR: Read an illegal number of columns for the board";
				return 6;
		}

		//this reads the number of generations that will be simulated------------------------------------------------------------
		if(!(inStream >>NumGenerations))
		{
				cerr << "ERROR: Cannot read the number of generations";
				return 7;

		}
		if (NumGenerations < 0)  //checks if columns are within program range
		{
				cerr << "ERROR: Read an illegal number of generations";
				return 8;
		}

		//this will read the gameboard to the game array-------------------------------------------------------------------------
		for(i=0;i < NumRow;i++)
		{

			for (j=0; j < NumCol; j++)
			{
				if(!(inStream >> myLifeBoard[i][j]))
				{
					cerr << "ERROR: Not enough data in the input file";
				}
				if(!((myLifeBoard[i][j] == '.') || (myLifeBoard[i][j] == 'X')))
				{
					cerr << "ERROR: Input data for initial board is incorrect" << endl;
					cerr << "Location (" << i << "," << j << ") is not valid";
					return 9;
				}
				//this checks if the border is all just dots--------------------------------------------------------------------
				for (int rowboarder = 0; rowboarder<NumRow; rowboarder++)
				{
						if (myLifeBoard[0][rowboarder] == 'X' || myLifeBoard[NumRow - 1][rowboarder] == 'X')
						{
							cerr << "ERROR: organisms are present in the border of the board, please correct your input file" << endl;
							return 1;
						}
				}
				for (int colboarder = 0; colboarder<NumCol; colboarder++)
				{
						if (myLifeBoard[colboarder][0] == 'X' || myLifeBoard[colboarder][NumCol - 1] == 'X')
						{
							cerr << "ERROR: organisms are present in the border of the board, please correct your input file" << endl;
							return 1;
						}
				}

			}
		}
		//Printing-----------------------------------------------------------------------------------------------------------------

	PrintGen(myLifeBoard, cout, NumRow, NumCol, 0);
	for (int currentgen = 0; currentgen <= NumGenerations; currentgen++)
	{
		if (currentgen ==1)
		{
			PrintGen(myLifeBoard, cout, NumRow, NumCol, currentgen);
		}
		PrintGen(myLifeBoard, outStream, NumRow, NumCol, currentgen);

		NextGen(myLifeBoard, NumRow, NumCol);


		if (currentgen==14)
		{
			PrintGen(myLifeBoard, cout, NumRow, NumCol, NumGenerations);
		}
	}
	return 0;
}
