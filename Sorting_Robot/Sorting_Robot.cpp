//Author: Randeep Singh Shahi
//DOB: OCT 30,2014
//This program will determine whether an object picked up is a green bottle,
//a brown bottle, a clear bottle, or a trash bottle

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main ()
{
//errors will be outputed with cerr
//the following code will declare and initiate variables

		char InputFile[80]; //name of input file
		char OutputFile[80];//name of output file
		int NameCounter = 0;//counter
		int ClearCounter = 0;
		int GreenCounter = 0;
		int BrownCounter = 0;
		int WeightVar = 0;
		int ColourVar = 0;
		int Counter = 0;
		double NumberOfPairs = 0;//the rest of the variables are all double for simplicity with calculations
		double WeightInGrams = 0;//weight of each bottle
		double WasteContainer = 0;
		double TotalWeight = 0;//total weight of waste
		double WeightInKg = 0;
		const double MAXWEIGHT = 500;
		const double WEIGHTCONSTANT = 12.0;
		const double G_TO_KG = 1000;
		const double WEIGHTMAX = 255;
		const double MAXWEIGHT_BROWN = 59;
		const double MINWEIGHT_BROWN = 53;
		const double MAXWEIGHT_GREEN = 41;
		const double MINWEIGHT_GREEN = 35;
		const double MAXWEIGHT_CLEAR = 21;
		const double MINWEIGHT_CLEAR = 15;
		const double MIN_PAIRS = 1;
		const double MAX_PAIRS = 10000;
		const double MAX_ATTEMPTS = 6;
		const double MIN_VAR = 0;
		const double MAX_VAR = 255;
		const double MAXCOLOUR_CLEAR = 255;
		const double MINCOLOUR_CLEAR = 240;
		const double MAXCOLOUR_GREEN = 175;
		const double MINCOLOUR_GREEN = 150;
		const double MAXCOLOUR_BROWN = 90;
		const double MINCOLOUR_BROWN = 20;
		const double LENGTH_CONSTANT = 5.00;
		double Rotation = 0;
		double NEGRotation = 0;
		ifstream MyInputStream;
		ofstream MyOutputStream;

//ask for the name of the input file
		while (NameCounter < MAX_ATTEMPTS) // this allows a maximum of 6 tries
		{
			NameCounter++;
			cout << "Please enter the name of the input file containing sensor readings: " << endl ;
			cin >> InputFile; //this will read the name of the file from the keyboard
			MyInputStream.open(InputFile);//this will open the file


			if ( MyInputStream.fail() ) //this if statement is to check if the file was openned by using its address.
			{
				cerr << "The input file " << InputFile << " could not be opened" <<endl;
				if (NameCounter == MAX_ATTEMPTS) //this checks if the maximum amount of tires has been reached
				{
					cerr << "You exceeded maximum number of tries allowed for entering the input fileName";
					return 1;
				}
				continue;
			}


			else //if the file was openned, program will leave the loop and continue
			{
				break;
			}
		}

		NameCounter = 0; // this will set the counting variable to 0 for future use.



//ask for the name of the output file
		while (NameCounter < MAX_ATTEMPTS) //this allows a maximun of 6 tries
		{
			cout << "Please enter the name of the output file containing simulation results: " << endl ;
			cin >> OutputFile; //this will read the name of the output file
			MyOutputStream.open(OutputFile);//this will open the file


			if (NameCounter == MAX_ATTEMPTS) //this checks if the naximun amount of tries has been reached
			{
				cerr << "You exceeded maximun number of tries allowed for entering the output filename";
				return 2;
			}

			if (MyOutputStream.fail()) //this if statement is to chekc if the file was actually oppened using its address
			{
				cerr << "The output file " << OutputFile << " could not be opened" <<endl;
				NameCounter++;
				continue;
			}
			else //if the file was openned, program will leave the loop and continue
			{
				break;
			}
		}

		NameCounter = 0; //this will se the counting variable to 0 for future use


		if( !(MyInputStream >> NumberOfPairs) ) //reads the number of pair and checks if it actually read anything
		{
			if (MyInputStream.eof() ) //checks if end of file and if true prints and exits program
			{
				cerr << "Data file is empty";
				MyInputStream.close();
				return 3;
			}
			else  //if not end of file, the input to variable wasn't a correct format
			{
				cerr << "Unable to read the number of sensor readings";
				MyInputStream.close();
				return 4;
			}
		}

		if ((NumberOfPairs < MIN_PAIRS) || (NumberOfPairs > MAX_PAIRS)) //this checks if the number of pairs is within range
		{
			cerr << "The number of sensor readings is out of range";
			MyInputStream.close();
			return 5;
		}

		for (NameCounter = 0; NameCounter < NumberOfPairs; NameCounter++) //for loops that does everything
		{
			//this if statment only concerns the WeightVariable-------------------------------------------------
			if( !(MyInputStream >> WeightVar) ) //checks if weight variable was inputed properly
			{
				if (MyInputStream.eof() ) //if end of file, end and show results
				{
					cout << "No more data, simulation completed early at line " << NameCounter + 2
						<< " of input" << endl;
					MyInputStream.close();
					break;
				}

				else //if bad input, prints message and ends program
				{
					cerr << "The number read on line " << NameCounter + 2 << " of your input file is not an integer" <<endl
						 <<  "Please correct your data file and then rerun";
						MyInputStream.close();
						 return 6;
				}

			}

		//this if statement only concerns the ColourVariable-----------------------------------------------
		if(!(MyInputStream >> ColourVar)) //this check if the colour variable was inputed properly
		{
			if (MyInputStream.eof() ) //if end of file, end code
			{
				cerr << "No light sensor measurement to match final weight measurement" <<endl;
				break;
			}
						else //if bad input, prints message and ends program
			{
				cerr << "The number read on line " << NameCounter + 2 << " of your input file is not an integer" << endl
					 <<  "Please correct your data file and then rerun";
		    	MyInputStream.close();
					 return 7;
			}
		}

		//this checks if both Variables are within range---------------------------------------------------
		if ((WeightVar > MAX_VAR) || (WeightVar < MIN_VAR) ||(ColourVar > MAX_VAR) || (ColourVar < MIN_VAR))
		{
			cerr << "Sensor reading out of range, ignoring line " << NameCounter + 2 << " of input" <<endl;
			continue; //continue to next pair of inputs
		}

		//following code will sepeate the bottles----------------------------------------------------------


		WeightInGrams = WEIGHTCONSTANT * ((WeightVar/WEIGHTMAX)*LENGTH_CONSTANT); //this will calculate the actual weight


		if ((ColourVar <= MAXCOLOUR_CLEAR) && (ColourVar >= MINCOLOUR_CLEAR) && (WeightInGrams >= MINWEIGHT_CLEAR) && (WeightInGrams <= MAXWEIGHT_CLEAR))
		{
			Rotation = 90;
			NEGRotation = -90;
			ClearCounter++;
			//this prints to the screen
			cout << "The robot has rotated " << setprecision(0) << Rotation << " degrees to face the clear glass conveyor belt" << endl;
			cout << "The robot has placed " << ClearCounter << " clear bottles on the conveyor belt" << endl;
			cout << "The robot rotates " << NEGRotation << " degrees" << endl;
			//this prints to the text
			MyOutputStream << "The robot has rotated " << setprecision(0) << Rotation << " degrees to face the clear glass conveyor belt" << endl;
			MyOutputStream << "The robot has placed " << ClearCounter << " clear bottles on the conveyor belt" << endl;
			MyOutputStream << "The robot rotates " << NEGRotation << " degrees" << endl;

		}

		else if ((ColourVar <=MAXCOLOUR_GREEN) && (ColourVar >= MINCOLOUR_GREEN) && (WeightInGrams >= MINWEIGHT_GREEN) && (WeightInGrams <= MAXWEIGHT_GREEN))
		{
			Rotation = 150;
			NEGRotation = -150;
			GreenCounter++;

			//this prints to the screen
			cout << "The robot has rotated " << setprecision(0)<< Rotation << " degrees to face the green glass conveyor belt" << endl;
			cout << "The robot has placed " << GreenCounter << " green bottles on the conveyor belt" << endl;
			cout << "The robot rotates " << NEGRotation << " degrees" << endl;
			//this prints to the text
			MyOutputStream << "The robot has rotated " << setprecision(0)<< Rotation << " degrees to face the green glass conveyor belt" << endl;
			MyOutputStream << "The robot has placed " << GreenCounter << " green bottles on the conveyor belt" << endl;
			MyOutputStream << "The robot rotates " << NEGRotation << " degrees" << endl;
		}

		else if ((ColourVar <= MAXCOLOUR_BROWN) && (ColourVar >= MINCOLOUR_BROWN) && (WeightInGrams >= MINWEIGHT_BROWN) && (WeightInGrams <= MAXWEIGHT_BROWN))
		{
			Rotation = 210;
			NEGRotation = -210;
			BrownCounter++;
			//this prints to the screen
			cout << "The robot has rotated " << setprecision(0)<< Rotation << " degrees to face the brown glass conveyor belt" << endl;
			cout << "The robot has placed " << BrownCounter << " brown bottles on the conveyor belt" << endl;
			cout << "The robot rotates " << NEGRotation << " degrees" << endl;
			//this prints to the text
			MyOutputStream << "The robot has rotated " << setprecision(0)<< Rotation << " degrees to face the brown glass conveyor belt" << endl;
			MyOutputStream << "The robot has placed " << BrownCounter << " brown bottles on the conveyor belt" << endl;
			MyOutputStream << "The robot rotates " << NEGRotation << " degrees" << endl;
		}

		else
		{
			cout << "The robot has rotated 270 degrees to face the waste container" << endl;
			MyOutputStream << "The robot has rotated 270 degrees to face the waste container" << endl;


				if ((WasteContainer += WeightInGrams)  > MAXWEIGHT)
				{
					WasteContainer -= WeightInGrams;
					MyOutputStream << "A new waste container is needed" << endl
						<< "Stop the incoming conveyor belt" << endl;

					cout << "A new waste container is needed" << endl
						<< "Stop the incoming conveyor belt" << endl;

					TotalWeight = TotalWeight + WasteContainer;
					WasteContainer = 0;
					WasteContainer += WeightInGrams;

					cout << "A new waste container is ready for use" << endl;
					cout << "The waste container now contains " << setw(8) << setprecision(3) << WasteContainer <<  " grams of glass" << endl;
					cout << "The robot rotates -270 degrees" << endl;
					cout << "Start the incoming conveyor belt" << endl;

					MyOutputStream << "A new waste container is ready for use" << endl;
					MyOutputStream << "The waste container now contains " << setw(8) << setprecision(3) << WasteContainer <<  " grams of glass" << endl;
					MyOutputStream << "The robot rotates -270 degrees" << endl;
					MyOutputStream << "Start the incoming conveyor belt" << endl;
				}
				else
				{
					cout << "The waste container now contains " << fixed << setw(8) << setprecision(3) << WasteContainer <<  " grams of glass" << endl;
					cout << "The robot rotates -270 degrees" << endl;

					MyOutputStream << "The waste container now contains " << fixed << setw(8) << setprecision(3) << WasteContainer <<  " grams of glass" << endl;
					MyOutputStream << "The robot rotates -270 degrees" << endl;
				}
		}


	}
		MyInputStream.close();//close the input stream
		cout << endl << endl << endl <<endl;
		MyOutputStream << endl << endl << endl<<endl;

		cout << "SUMMARY" << endl;//for the summary I chose not to pre allocate space for the number of each type of bottle
		MyOutputStream << "SUMMARY" << endl;
		// the following is a summary
		TotalWeight = TotalWeight + WasteContainer; //this is the total final weight processed of waste
		WeightInKg = TotalWeight/G_TO_KG;
		//this prints to the screen
		cout << "The robot processed " <<  fixed << setprecision(0) << ClearCounter << " clear bottles" << endl;
		cout << "The robot processed " << GreenCounter << " green bottles" << endl;
		cout << "The robot processed " << BrownCounter << " brown bottles" << endl;
		cout << "The robot processed " << setprecision(4) << right << setw(12) << WeightInKg << " kg  of waste glass";
		//this prints to the output file
		MyOutputStream << "The robot processed " <<  fixed << setprecision(0) << ClearCounter << " clear bottles" << endl;
		MyOutputStream << "The robot processed " << GreenCounter << " green bottles" << endl;
		MyOutputStream << "The robot processed " << BrownCounter << " brown bottles" << endl;
		MyOutputStream << "The robot processed " << right << setw(12) << setprecision(4) << WeightInKg << " kg  of waste glass";
		MyOutputStream.close();//closes the output stream
		return 0;
}
