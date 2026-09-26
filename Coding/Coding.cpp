#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
using namespace std;

long long ReadNumber()
{
	long long Number;
	cout << "\nPlease enter a number ";
	cin >> Number;
	return Number;

}

string NumberToText(long long Number)
{
	if (Number == 0)
	{
		return "";
	}

	if (Number >= 1 && Number <= 19)
	{
		string arr[] = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight",
			"Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen",
			"Seventeen", "Eighteen", "Nineteen" };

		return arr[Number] + " ";
	}

	if (Number >= 20 && Number <= 99)
	{
	 
		string arr[] = { "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };
		return arr[Number / 10] + " " + NumberToText(Number % 10);
	}

	if (Number >= 100 && Number <= 999)
	{
		return NumberToText(Number / 100) + " Hundred " + NumberToText(Number % 100);
	}

	if (Number >= 1000 && Number <= 999999)
	{
		return NumberToText(Number / 1000) + " Thousand " + NumberToText(Number % 1000);
	}
	if (Number >= 1000000 && Number <= 999999999)
	{
		return NumberToText(Number / 1000000) + " Million " + NumberToText(Number % 1000000);
	}
	if (Number >= 1000000000)
	{
		return NumberToText(Number / 1000000000) + " Billion " + NumberToText(Number % 1000000000);
	}
}


int main()
{
	long long Number = ReadNumber();
	cout <<"\n" << NumberToText(Number);
	cout << '\n';
	system("pause");
}


