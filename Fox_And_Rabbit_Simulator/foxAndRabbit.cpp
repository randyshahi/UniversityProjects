#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;
//these are the two structures--------------------------------------------------------
struct Fox
{
            int xIndex;
            int yIndex;
            int fedLevel;
            bool alive;
};
struct Rabbit
{
            int xIndex;
            int yIndex;
            int age;
            bool alive;
};
//global constants
int const MAX_RABBITS_PER_GRID = 20;
//these are the prototypes----------------------------------------------------------
int GET_INFO(int variable, int MIN, int MAX,string ERROR_tries,string Prompt,string ERROR_Cant_Read,string ERROR_illegal);
void PrintGrids(int **FoxBoard, int **RabbitBoard, ostream& outStream, int numRows, int numCols);
double GET_INFO_DOUBLE(double variable, double MIN, double MAX,string ERROR_tries,string Prompt,string ERROR_Cant_Read,string ERROR_illegal );
bool RabbitStep( int **rabbitBoard, Rabbit *listOfRabbits, int& numberRabbitsTotal, int& numberRabbitsAlive,
				int numRows, int numCols, int rabbitListLength,int maxNumRabbitsPerGrid, int numChildren);
void FoxStep( int **foxBoard, Fox *listOfFoxes, int **rabbitBoard, Rabbit *listOfRabbits, int numberFoxesTotal, int& numberFoxesAlive, int numberRabbitsTotal,
				int& numberRabbitsAlive, int numRows, int numCols, int foxListLength, int rabbitListLength);
//this is the main program

int main()
{
//these are all the variables---------------------------------------------------------
	char output_file[80];
	ofstream outfile;
	int counter = 0;
	int numRows = 0;
	int numCols = 0;
	int generations = 0;
	int seed = 0;
	double fracFox = 0;
	double fracRabbit = 0;
	int maxFoxes = 0;
	int maxRabbits = 0;
	int maxChildren = 0;
	int numberRabbitsTotal = 0;
	int numberRabbitsAlive = 0;
	int numberFoxsTotal = 0;
	int numberFoxsAlive = 0;
	int LengthOfRabbitList = 0;
	int foxListLength = 0;
	bool Valid;


	//these are the constants for part 1
	const int MINCOL = 0;
	const int MAXCOL = 15;
	const int MINROW = 0;
	const int MAXROW = 15;
	const int MINGEN = 0;
	const int MAXGEN = 40;
	const int MINSEED = 0;
	const int MAXSEED = RAND_MAX;
	const double MINFOX = 0.05;
	const double MAXFOX = 0.95;
	const double MINRABBIT = 0.05;
	const double MAXRABBIT = 0.95;
	const int MINFOX_INITIAL = 0;
	const int MAXFOX_INITIAL = 9;
	const int MIN_RABBITS_PER_GRID = 0;
	const int MAX_RABBITS_PER_GRID = 20;

	//these are random counting variables and others
	int i = 0;
	int j = 0;
	int XX = 0;
	int MM = 0;
	int YY = 0;
	int ff = 0;
	int m = 0;
	int n = 0;
	double increment = 0;
	double prob = 0;

	//dynamic grids
	int** foxGrid = NULL;
	int** rabbitGrid = NULL;
	Fox* foxList = NULL;
	Rabbit* rabbitList = NULL;

	//prompts--------------------------------------------------------------
	string Rows_Prompt = "Enter the number of rows in the simulation grid: ";
	string Cols_Prompt = "Enter the number of columns in the simulation grid: ";
	string Gens_Prompt = "Enter the number of generations: ";
	string Seed_Prompt = "Enter the seed for the random number generator: ";
	string Fox_Frac_Prompt = "Enter the initial fraction of squares in the grid containing foxes: ";
	string Rabbit_Frac_Prompt = "Enter the initial fraction of squares in the grid containing rabbits: ";
	string Fox_Initial_Prompt = "Enter the initial maximum number of foxes per grid: ";
	string Rabbit_Initial_Prompt = "Enter the initial maximum number of rabbits per grid: ";
	string Children_Prompt = "Enter the maximum number of children produced when rabbits breed: ";
	//6 tries error----------------------------------------------------------
	string Rows_Tries = "ERROR: could not read number of rows after 6 tries";
	string Cols_Tries = "ERROR: could not read number of columns after 6 tries";
	string Gens_Tries = "ERROR: could not read number of generations after 6 tries";
	string Seed_Tries = "ERROR: could not read the seed for the random number generator after 6 tries";
	string Fox_Frac_Tries = "ERROR: could not read the initial fraction of squares in the grid containing foxes after 6 tries";
	string Rabbit_Frac_Tries = "ERROR: could not read the initial fraction of squares in the grid containing rabbits after 6 tries";
	string Fox_Initial_Tries = "ERROR: could not read the initial maximum number of foxes per square after 6 tries";
	string Rabbit_Initial_Tries = "ERROR: could not read the initial maximum number of rabbits per grid after 6 tries";
	string Children_Tries = "ERROR: could not read the maximum number of children produced when rabbits breed after 6 tries";
	//cant read error---------------------------------------------------------
	string Rows_Read = "ERROR: Cannot read number of rows";
	string Cols_Read = "ERROR: Cannot read number of columns";
	string Gens_Read = "ERROR: Cannot read the number of generations";
	string Seed_Read = "ERROR: Cannot read the seed for the random number generator";
	string Fox_Frac_Read = "ERROR: Cannot read the initial fraction of squares in the grid containing foxes";
	string Rabbit_Frac_Read = "ERROR: Cannot read the initial fraction of squares in the grid containing rabbits";
	string Fox_Initial_Read = "ERROR: Cannot read the initial maximum number of foxes per grid";
	string Rabbit_Initial_Read = "ERROR: Cannot read the initial maximum number of rabbits per grid";
	string Children_Read = "ERROR: Cannot read the maximum number of children produced when rabbits breed";
	//illegal read error-------------------------------------------------------
	string Rows_Illegal = "ERROR: Read an illegal number of rows for the board";
	string Cols_Illegal = "ERROR: Read an illegal number of columns for the grid";
	string Gens_Illegal = "ERROR: Read an illegal number of generations";
	string Seed_Illegal= "ERROR: Read an illegal seed";
	string Fox_Frac_Illegal = "ERROR: Read an illegal initial fraction of squares in the grid with foxes";
	string Rabbit_Frac_Illegal = "ERROR: Read an illegal initial fraction of squares in the grid containing rabbits";
	string Fox_Initial_Illegal = "ERROR: Read an illegal initial maximum number of foxes per square";
	string Rabbit_Initial_Illegal = " ERROR: Cannot read the initial maximum number of rabbits per grid";
	string Children_Illegal = "ERROR: Read an illegal maximum number of children produced when rabbits breed";

//-----------------------------------PART 1----------------------------------------------------------------------------------
	//ask for name of output file and open(6 tries)-------------------------------------------------------------------------------

		while(true)
		{
			if(counter == 6)
			{
				cerr << "ERROR: could not open output file after 6 tries: ";
				return 1;
			}
			cout << "Enter the name of the output file: ";
			cin >> output_file; //this will read the name of the file from the keyboard
			outfile.open(output_file);//this will open the file

			if ( outfile.fail() ) //this if statement is to check if the file was openned by using its address.
			{
				cerr << "ERROR: output file not opened correctly";
				counter++;
				continue;
			}
			else
			{
				break;
			}

		}
	//ask for the number of rows in the simulation grid------------------------------------------------------------------


	numRows = GET_INFO(numRows,MINROW,MAXROW,Rows_Tries,Rows_Prompt,Rows_Read,Rows_Illegal);
		if((numRows == 69))
		{
			return 1;
		}
	//ask for the number of cols in the simulation grid------------------------------------------------------------------

	numCols = GET_INFO(numCols,MINCOL,MAXCOL,Cols_Tries,Cols_Prompt,Cols_Read,Cols_Illegal);
		if((numCols == 69))
		{
			return 2;
		}
	//ask for the number of generations----------------------------------------------------------------------------------
	generations = GET_INFO(generations,MINGEN,MAXGEN,Gens_Tries,Gens_Prompt,Gens_Read,Gens_Illegal);
	//ask for the seed for the random number generator--------------------------------------------------------------------
	seed = GET_INFO(seed,MINSEED,MAXSEED,Seed_Tries,Seed_Prompt,Seed_Read,Seed_Illegal);
	//ask the the initial fraction of squares containing foxes----------------------------------------------------------
	fracFox = GET_INFO_DOUBLE(fracFox, MINFOX,MAXFOX,Fox_Frac_Tries,Fox_Frac_Prompt,Fox_Frac_Read,Fox_Frac_Illegal);
	//ask for the initial fraction or squares containning rabbits----------------------------------------------------------
	fracRabbit = GET_INFO_DOUBLE(fracRabbit,MINRABBIT,MAXRABBIT,Rabbit_Frac_Tries,Rabbit_Frac_Prompt,Rabbit_Frac_Read,Rabbit_Frac_Illegal);
	//ask for the maximum initial number of foxes per square---------------------------------------------------------------
	maxFoxes = GET_INFO(maxFoxes,MINFOX_INITIAL,MAXFOX_INITIAL,Fox_Initial_Tries,Fox_Initial_Prompt,Fox_Initial_Read,Fox_Initial_Illegal);
	//ask for the maximum initial number of rabbits per square------------------------------------------------------------
	maxRabbits = GET_INFO(maxRabbits,MIN_RABBITS_PER_GRID,MAX_RABBITS_PER_GRID,Rabbit_Initial_Tries,Rabbit_Initial_Prompt,Rabbit_Initial_Read,Rabbit_Initial_Illegal);
	//ask for the max number of children rabbits that can be produced-----------------------------------------------------
	maxChildren = GET_INFO(maxChildren,MIN_RABBITS_PER_GRID,MAX_RABBITS_PER_GRID,Children_Tries,Children_Prompt,Children_Read,Children_Illegal);
	srand(seed);//THIS IS THE PART WHERE SRAND IS INITIALIZED

//--------------------------------------------------------------------------PART 2----------------------------------------

	//sets dynamic array
	foxGrid = new int*[numRows];
	for(i = 0;i <numRows;i++)
	{
		foxGrid[i]= new int[numCols];
	}

	//does part 2 lel
	for (i = 0; i < numRows; i++)
	{
		for(j = 0; j < numCols; j++)
		{
			foxGrid[i][j] = maxFoxes;
			XX = rand();
				increment = (double)fracFox/(double)maxFoxes;
				prob = (double)XX / (double)RAND_MAX;
				if(XX < (1.0-fracFox)*RAND_MAX)
				{
					foxGrid[i][j] = 0;
				}
				else
				{
					for (MM = 1;MM<=maxFoxes;MM++)
					{
						if(prob < (1-fracFox) + MM * increment)
						{
							foxGrid[i][j]=MM;
							break;
						}
					}
				}

		}
	}
//--------------------------------------------------------------------------PART 3---------------------------------------
	foxList = new Fox[numRows*numCols*maxFoxes*2];

	for(i = 0;i <numRows; i++)
	{
		for(j = 0; j <numCols; j++)
		{
			for(ff = 0; ff <foxGrid[i][j]; ff++)
			{
			     foxList[m].xIndex = j;
				 foxList[m].yIndex = i;
				 foxList[m].fedLevel  = rand()%10;
				 foxList[m].alive = true;
				 m++;
			}
		}
	}
//---------------------------------------------------------------------------PART 4--------------------------------------
	//sets dynamic array
	rabbitGrid = new int*[numRows];
	for(i = 0;i <numRows;i++)
	{
		rabbitGrid[i]= new int[numCols];
	}

	//does part 4 lel
	for (i = 0; i < numRows; i++)
	{
		for(j = 0; j < numCols; j++)
		{
			rabbitGrid[i][j] = maxRabbits;
				YY = rand();
				increment = (double)fracRabbit/(double)maxRabbits;
				prob = (double)YY / (double)RAND_MAX;
				if(YY < (1.0-fracRabbit)*RAND_MAX)
				{
					rabbitGrid[i][j] = 0;
				}
				else
				{
					for (MM = 1;MM<=maxRabbits;MM++)
					{
						if(prob < ((1-fracRabbit) + MM * increment))
						{
							rabbitGrid[i][j]=MM;
							break;
						}
					}
				}

		}
	}
//---------------------------------------------------------------------------PART 5--------------------------------------
	rabbitList = new Rabbit[numRows*numCols*maxRabbits*2];

	for(i = 0;i < numRows; i++)
	{
		for(j = 0; j <numCols; j++)
		{
			for(ff = 0; ff <rabbitGrid[i][j]; ff++)
			{
				rabbitList[n].xIndex = j;
				rabbitList[n].yIndex = i;
				rabbitList[n].age  = rand() % 10;
				rabbitList[n].alive = true;
			    n++;
			}
		}
	}
//---------------------------------------------------------------------------PART 6--------------------------------------
	//calculate number of rabbits------------------
	for(i=0;i<numRows;i++)
	{
		for(j=0;j<numCols;j++)
		{
			numberRabbitsTotal +=rabbitGrid[i][j];
			numberRabbitsAlive = numberRabbitsTotal;
		}
	}
	//length of foxlist-----------------------------------
		for(i=0;i<numRows;i++)
	{
		for(j=0;j<numCols;j++)
		{
			numberFoxsTotal +=foxGrid[i][j];
			numberFoxsAlive = numberFoxsTotal;
		}
	}

	//length of rabbit list--------------------------------
		LengthOfRabbitList = numRows*numCols*maxRabbits*2;

	//length of fox list----------------------------------
		for(i=0;i<numRows;i++)
		{
			for(j=0;j<numCols;j++)
			{
				foxListLength +=foxGrid[i][j];
			}
		}
	//-----------------------------creates and prints all the arrays-----------------------------------------------------------
		//1. print the initial array
		cout << endl <<"after initialization" << endl;
		outfile << "after initialization" << endl;
		PrintGrids(foxGrid,rabbitGrid,cout,numRows,numCols);
		PrintGrids(foxGrid,rabbitGrid,outfile,numRows,numCols);
		//2. use for loop and do the rest
		for(i=0;i<generations;i++)
		{
			Valid = RabbitStep(rabbitGrid,rabbitList,numberRabbitsTotal,numberRabbitsAlive,numRows,numCols,LengthOfRabbitList,MAX_RABBITS_PER_GRID,
				maxChildren);
			cout<< endl<< endl<< endl;
			cout<<"after rabbits die of old age and breed"<<endl;
			PrintGrids(foxGrid,rabbitGrid,cout,numRows,numCols);

			FoxStep(foxGrid,foxList,rabbitGrid,rabbitList,numberFoxsTotal,numberFoxsAlive,numberRabbitsTotal,numberRabbitsAlive,
			numRows,numCols,foxListLength,LengthOfRabbitList);
				outfile << endl<< endl<< endl;
				cout << endl<< endl<< endl;
				//
				cout << "after foxes move" << endl;
			PrintGrids(foxGrid,rabbitGrid,cout,numRows,numCols);
			//
				outfile << "after foxes eat and move" << endl;
			PrintGrids(foxGrid,rabbitGrid,outfile,numRows,numCols);
		}
		delete[] foxGrid;
		delete[] rabbitGrid;
		delete[] foxList;
		delete[] rabbitList;
		foxGrid = NULL;
		rabbitGrid = NULL;
		foxList = NULL;
		rabbitList = NULL;
	return 0;
	}


//sexy function that asks everything else---------------------------------------------------------------------------------------
int GET_INFO(int variable, int MIN, int MAX,string ERROR_tries,string Prompt,string ERROR_Cant_Read,string ERROR_illegal )
{
	int counter = 0;
	while(counter <= 6)
	{
		if(counter == 6)
		{
			cerr <<  ERROR_tries << endl;
			return 69;

		}
			cout << Prompt;
			if(!(cin >> variable))
			{
				cerr <<  ERROR_Cant_Read << endl;
				counter++;
				variable = 0;
				cin.clear();
				cin.sync();
			}
			else if ((variable<=MIN)||(variable>=MAX))
			{
				cerr << ERROR_illegal << endl;
				counter++;
			}
			else
			{
				return variable;
				break;
			}
	}

}
void PrintGrids(int **FoxBoard, int **RabbitBoard, ostream& outStream, int numRows, int numCols)

{
	int i = 0;
	int j = 0;
	int temp1 = 0;
	int temp2 = 0;
	 for(i = 0; i < numRows; i++)
		{
			for( j = 0; j < numCols; j++)
			 {
				temp1 = FoxBoard[i][j];
				temp2 = RabbitBoard[i][j];
				outStream << setw(3)<<temp1 << "," << setw(2) << temp2;

			 }
		outStream << endl;
		}
	 outStream << endl;
}
double GET_INFO_DOUBLE(double variable, double MIN, double MAX,string ERROR_tries,string Prompt,string ERROR_Cant_Read,string ERROR_illegal )
{
	int counter = 0;
	while(counter <= 6)
	{
		if(counter == 6)
		{
			cerr <<  ERROR_tries;
			return 69;
		}
			cout << Prompt;
			if(!(cin >> variable))
			{
				cerr <<  ERROR_Cant_Read << endl;
				counter++;
				variable = 0;
				cin.clear();
				cin.sync();
			}
			else if ((variable<=MIN)||(variable>=MAX))
			{
				cerr << ERROR_illegal << endl;
				counter++;
			}
			else
			{
				return variable;
				break;
			}
	}

}


bool RabbitStep( int **rabbitBoard, Rabbit *listOfRabbits, int& numberRabbitsTotal, int& numberRabbitsAlive,
				int numRows, int numCols, int rabbitListLength,int maxNumRabbitsPerGrid, int numChildren)
{
	int i = 0;
	int j = 0;
	int k = 0;//this variable used for the iterations for how many rabbits per square
	int index = 0;//this is the index for the listOfRabbits
	int Ran_Children = 0;
	int Pairs = 0;
	int start = 0;
	int end = 0;
	int added_children = 0;
	int iterations = 0;

	for(i=0; i<numRows; i++)
	{
		for(j=0; j<numCols;j++)
	//DEATHS--------------------------------------------
		{
			/////////////
			for(index=0;index<numberRabbitsTotal;index++)
			{
				if((listOfRabbits[index].alive = true)&&(listOfRabbits[index].xIndex==j)
						&&(listOfRabbits[index].yIndex==i))
				{
					listOfRabbits[index].age++; //increase age by one
						if(listOfRabbits[index].age==11) //checks if the rabbits is going do die
						{
							listOfRabbits[index].alive = false;//sets dead
							rabbitBoard[i][j]--;//decrements the rabbitBoard
							numberRabbitsAlive--;//decrements the number of rabbits alive
							break;
						}
				}
				continue;
			}

			//////////////////
	//BIRTHS-------------------------------------------------
			iterations = rabbitBoard[i][j]/2;//this is how many couples there are
			for(Pairs = 0; Pairs < iterations;Pairs++)//this does each couples babies
			{
				Ran_Children = rand()%(numChildren) + 1;//this generates how many babies each couple spawns
					if((rabbitBoard[i][j] +=Ran_Children)>20)//this makes sure limit isnt exceeded
				{
					Ran_Children= (20 -(rabbitBoard[i][j] -=Ran_Children));//how many babies that can be fit into square.
					rabbitBoard[i][j] = maxNumRabbitsPerGrid;	//set rabbitBoard to maxRabbits
				}
				//this creates the new stuctures in the rabbit list
					if(rabbitListLength<(numberRabbitsTotal+Ran_Children))
					{
						return false;
					}
					for(index = numberRabbitsTotal;index<(numberRabbitsTotal+Ran_Children);index++)
					{
						listOfRabbits[index].xIndex = j;
						listOfRabbits[index].yIndex = i;
						listOfRabbits[index].age  = 1;
						listOfRabbits[index].alive = true;
					}
				numberRabbitsAlive +=Ran_Children;//these statements just increment
				numberRabbitsTotal +=Ran_Children;

			}
			Ran_Children = 0;
		}
	}
}
void FoxStep( int **foxBoard, Fox *listOfFoxes, int **rabbitBoard, Rabbit *listOfRabbits, int numberFoxesTotal, int& numberFoxesAlive, int numberRabbitsTotal,
int& numberRabbitsAlive, int numRows, int numCols, int foxListLength, int rabbitListLength)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;
	int index_fox = 0;
	int index_rabbit = 0;
	int movement = 0;
	int movement_x = 0;
	int movement_y = 0;
	int x = 0;
	int y = 0;

	for(i = 0; i < numRows; i++)//y
	{
		for(j = 0; j < numCols; j++)//x
		{
			//EAT----------------------------------------------------------------------------------------------
			for(index_fox = 0;index_fox<numberFoxesTotal;index_fox++)
			{
				if(foxBoard[i][j]==0)
				{
					break;//no foxes in the square, next square
				}
				else if(rabbitBoard[i][j]==0  && listOfFoxes[index_fox].xIndex==j
					&& listOfFoxes[index_fox].yIndex==i)//there are foxes but no rabbits, fedlevel decreases
				{
					listOfFoxes[index_fox].fedLevel--;
					if(listOfFoxes[index_fox].fedLevel<=0)//if fedlevel 0 or less, fox dies.
					{
						listOfFoxes[index_fox].alive = false;
						numberFoxesAlive--;
						index_fox++;
					}
					continue;
				}
				else if(listOfFoxes[index_fox].alive == true && listOfFoxes[index_fox].xIndex==j
					&& listOfFoxes[index_fox].yIndex==i)//if there is an alive fox in the square
				{
					for(index_rabbit=0;index_rabbit<numberRabbitsTotal;index_rabbit++)
					{
						if(listOfRabbits[index_rabbit].alive==true && listOfRabbits[index_rabbit].xIndex==j
							&& listOfRabbits[index_rabbit].yIndex==i)
						{
							//fox eats rabbit
								listOfRabbits[index_rabbit].alive = false;
								numberRabbitsAlive--;
								rabbitBoard[i][j]--;
								listOfFoxes[index_fox].fedLevel++;
								break;
						}
					}
				}
			}
		}
	}
//print current grid now----------------------------------------------------------------------------------
	cout << endl<< endl<< endl;
	cout << "after foxes eat rabbits"<<endl;
		PrintGrids(foxBoard,rabbitBoard,cout,numRows,numCols);
		//MOVE------------------------------------------------
	for(index_fox = 0;index_fox <numberFoxesTotal;index_fox++)
	{
			x = listOfFoxes[index_fox].xIndex;
			y = listOfFoxes[index_fox].yIndex;
		if(foxBoard[y][x]==0)
		{
			continue;
		}
		//////this moves the fox
		else if(listOfFoxes[index_fox].alive == true)
		{
		foxBoard[y][x]--;
		movement = rand()%8;
		//right edge
		if ( movement == 1 || movement == 2 || movement == 3 )
		{
			if ( listOfFoxes[index_fox].xIndex == (numCols - 1) )
			{
				listOfFoxes[index_fox].xIndex = 0;
			}
			else
			{
				listOfFoxes[index_fox].xIndex = listOfFoxes[index_fox].xIndex + 1;
			}
		}
		//top edge
		if ( movement == 5 || movement == 4 || movement == 3)
		{
			if ( listOfFoxes[index_fox].yIndex == 0 )
			{
				listOfFoxes[index_fox].yIndex = numRows - 1;
			}
			else
			{
				listOfFoxes[index_fox].yIndex = listOfFoxes[index_fox].yIndex - 1;
			}
		}
		//left edge
		if ( movement == 5 || movement == 6 || movement == 7 )
		{
			if ( listOfFoxes[index_fox].xIndex == 0 )
			{
				listOfFoxes[index_fox].xIndex = numCols - 1;
			}
			else
			{
				listOfFoxes[index_fox].xIndex = listOfFoxes[index_fox].xIndex - 1;
			}
		}
		//bottom edge
		if ( movement == 7 || movement == 0 || movement == 1 )
		{
			if ( listOfFoxes[index_fox].yIndex == numRows - 1 )
			{
				listOfFoxes[index_fox].yIndex = 0;
			}
			else
			{
				listOfFoxes[index_fox].yIndex = listOfFoxes[index_fox].yIndex + 1;
			}
		}
		foxBoard[listOfFoxes[index_fox].yIndex][listOfFoxes[index_fox].xIndex]++;

		}
		else if(listOfFoxes[index_fox].alive==false)
		{
			foxBoard[y][x]--;
		}

	}

}
