//Author: Randeep Shahi
//DOB:OCT 7, 2014
//This code is to be used by atleast 1000 people to calculate
//their personal income taxes


#include <iostream>
#include <iomanip>
using namespace std;

 int main ()
{
////////////////First I will set all variables that will be used/////////////////////////
	double Gross_Income = 0;
	double Number_Of_Dependents = 0;
	double Income_Tax = 0;
	double check = 0;
	double Taxable_Income = 0;
	double Calculated_Tax_20000 = 0;
	double Calculated_Tax_50000=  0;
	double Calculated_Tax_Remaining = 0;
	double Calculated_Tax_Surtax = 0;
	double Remaining_Tax = 0;
	double Refund = 0;
	double Net_Tax = 0;
	double Total_Calculated_Tax = 0;
	const int CURRENCY_1 = 12000;
	const int CURRENCY_2 = 20000;
	const int CURRENCY_3 = 50000;
	const int CURRENCY_4 = 100000;
	const int CURRENCY_5 = 10000000;
	const double TAX_15 = 0.15;
	const double TAX_20 = 0.20;
	const double TAX_18 = 0.18;
	const double TAX_SURTAX = 0.035;
	const int MAX_DEPENDENTS = 10;
	const int CHILDREN_TAX = 5000;

//////////////////////Take in the three numbers needed for the calculation ///////

cout << "Please enter your total income before any deductions for income tax ";
cin  >> Gross_Income;

//The number of children entered must be an integer or the program will not work properly
//If the number isnt an integer, the program won't work properly
cout << "Please enter the number of children you support ";
cin >> Number_Of_Dependents;

cout << "Please enter the amount of income tax your employer already deducted ";
cin >> Income_Tax;

//Check if income entered is valid and if the program can handle it
if (Gross_Income < 0)
	{
		cout << "Error entering income, your income cannot be < 0";
		return 1;
	}
//Check if the Income_Tax is a valid number or not
if (Income_Tax < 0)
	{
		cout << "You cannot prepay negative amounts of tax";
		return 2;
	}
//check to make sure the number of dependents is positive and if greater than 10 set to 10

if (Number_Of_Dependents > 10)
	{
		Number_Of_Dependents = 10;
	}
if (Number_Of_Dependents < 0 )
	{
		cout << "You cannot have a negative number of dependents";
		return 3;
	}

//check to see if the user has prepaid more in Income_Tax than their Gross_Income

		check = Gross_Income - Income_Tax;
 if (check < 0)
 {
	 cout << "You cannot prepay more in tax than you receive in income";
	   return 4;
 }

////////////////calculate Taxable Income/////////////////////////////////////////



//This just calculates the Taxable_Income and makes sure its lowest bound possible is 0

		Taxable_Income = Gross_Income - (Number_Of_Dependents * CHILDREN_TAX);

	if (Taxable_Income < 0)
	{
		Taxable_Income = 0;
	}


	if (Taxable_Income > CURRENCY_5)
	{
		cout  << "Your income is too high to use this method of calculation";
		return 5;
	}

/////////////////Display the Informations///////////////////////////////////////
	cout << endl;
	cout << endl;
	cout << fixed << setw(39) << left << "Amount of income:" << "$" << right << setw(12) << setprecision(2) << Gross_Income;
	cout << endl;

	cout << setw(39) << left << "Number of qualifying dependents:" <<" " << right<< setw(12) << setprecision(0) << Number_Of_Dependents;
	cout << endl;

	cout << setw(39) << left << "Taxable income:" << "$" << right <<setw(12) << setprecision(2) << Taxable_Income;
	cout << endl;

	cout << setw(39) << left << "Amount of income tax deducted:" << "$" << right << setw(12) << Income_Tax;
	cout << endl;
	cout << endl;
	cout << endl;
//////////////////////////(   2   )//////////////////////////////////////
	if (Taxable_Income < CURRENCY_1)
	{
		cout << "You do not owe any income tax" << endl
			<< left << setw(39) <<"You will receive a refund of" << "$" << right << setw(12) << Income_Tax;


		return 6;
	}
//////////////////////////(   3   )//////////////////////////////////////
	else if (Taxable_Income >= CURRENCY_1 && Taxable_Income <= CURRENCY_2)
	{
		Calculated_Tax_20000 = Taxable_Income * TAX_15;
	}
//////////////////////////(   4   )////////////////////////////////////
	else if (Taxable_Income > CURRENCY_2 && Taxable_Income <= CURRENCY_3)
	{
		Calculated_Tax_20000 = CURRENCY_2 * TAX_15;
		Calculated_Tax_50000 = (Taxable_Income - CURRENCY_2) * TAX_20;
	}
//////////////////////////(   5   )////////////////////////////////////
	else if (Taxable_Income > CURRENCY_3 && Taxable_Income <= CURRENCY_4)
	{
		Calculated_Tax_20000 = CURRENCY_2 * TAX_18;
		Calculated_Tax_50000 = (CURRENCY_3 - CURRENCY_2) * TAX_18;
		Calculated_Tax_Remaining = (Taxable_Income - CURRENCY_3) * TAX_18;
	}
//////////////////////////(   6   )////////////////////////////////////
	else if (Taxable_Income > CURRENCY_4 && Taxable_Income <= CURRENCY_5)
	{
		Calculated_Tax_20000 = CURRENCY_2 * TAX_18;
		Calculated_Tax_50000 = (CURRENCY_3-CURRENCY_2) * TAX_18;
		Calculated_Tax_Remaining = (Taxable_Income - CURRENCY_3) * TAX_18;
		Calculated_Tax_Surtax = (Taxable_Income - CURRENCY_4) * TAX_SURTAX;
	}
	else
	{
		cout << "This string shouldn't print";
	}
/////////////////////////( Final Calculations)/////////////////////////

Total_Calculated_Tax =  Calculated_Tax_20000 + Calculated_Tax_50000 + Calculated_Tax_Remaining +
	Calculated_Tax_Surtax;
Net_Tax = Total_Calculated_Tax - Income_Tax;

if (Net_Tax > 0)
{
	Remaining_Tax = Net_Tax;
}

if (Net_Tax < 0)
{
	Refund = -1 * Net_Tax;
}


		cout << left << setw(39) << "Tax on first $20,000 of taxable income" << "$" << right << setw(12) << Calculated_Tax_20000 << endl;
		cout << left << setw(39) << "Tax on next $30,000 of taxable income"  << "$" << right << setw(12) << Calculated_Tax_50000 << endl;
		cout << left << setw(39) << "Tax on remaining taxable income" << "$" << right << setw(12) <<  Calculated_Tax_Remaining << endl;
		cout << left << setw(39) << "Income Tax surtax" << "$" << right << setw(12) << Calculated_Tax_Surtax << endl;
		cout << left << setw(39) << "You must pay a balance of" << "$" << right << setw(12) << Remaining_Tax << endl;
		cout << left << setw(39) << "You will receive a refund of" << "$" << right <<setw(12) << Refund;


return 0;
}
