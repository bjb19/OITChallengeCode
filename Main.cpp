#include <iostream>
#include <string>

//Converts an int to a string reperesentation in Roman Numerals
std::string convertToNumeral(int number);
//Converts to an int represenattion in arabic numerals
int convertToNumber(std::string numeral);
//Returns the int value of a numeral
int numeralValue(char numeral);
//Determines the tens place of a numeral
int deteminePrecedence(char checkChar);
//Pushs back the value in numerals onto string in regards to a specific tens places
void conversionPerPlace(std::string& returnNumeral, char lowVal, char medVal, char highVal, int counter);
//Checks a string for non number chars
bool isNumber(std::string checkString);
//Checks a string for non valid numeral chars
bool isValidNumeral(std::string checkString);

int main()
{
	std::cout << "Hello!" << std::endl << "If you would like to convert to a Roman Numeral enter Number" << std::endl;
	std::cout << "If you would like to convert to a Number enter Numeral" << std::endl;
	std::cout << "Enter Done when you have no further values to convert" << std:: endl << std::endl;

	std::string userCommand = "";
	std::cin >> userCommand;
	std::cout << std::endl;

	while (userCommand != "Done" && userCommand != "done")
	{
		try
		{
			if (userCommand == "Numeral" || userCommand == "numeral")
			{
				std::string convertStr = "";
				std::cout << "Enter the number to be converted" << std::endl;
				std::cin >> convertStr;
				if (!isNumber(convertStr)) { throw std::string("That is not a valid whole number value"); }
				int convertNumber = stoi(convertStr);
				if (convertNumber == 0) { throw std::string("0 does not have a Roman Numeral value"); }
				std::cout << std::endl << "Here is your new numeral!" << std::endl;
				std::cout << convertToNumeral(convertNumber) << std::endl;
			}

			else if (userCommand == "Number" || userCommand == "number")
			{
				std::string convertNumeral = "";
				std::cout << "Enter the numeral to be converted" << std::endl;
				std::cin >> convertNumeral;
				if (!isValidNumeral(convertNumeral)) { throw std::string("That is not a valid numeral acceptable values are \"MDCLXVI\""); }
				std::cout << std::endl << "Here is your new number!" << std::endl;
				int numberValue = convertToNumber(convertNumeral);
				std::cout << numberValue << std::endl;
			}
			else
			{
				std::cout << "Sorry that is an Invalid command please try again!" << std::endl;
			}
		}
		catch(std::string errorMsg) { std::cerr << errorMsg << std::endl; }
		std::cout << std::endl << "Enter your next Command" << std::endl;
		std::cin >> userCommand;
		std::cout << std::endl;
	}

	std::cout << "Goodbye!";
	return 0;
}

std::string convertToNumeral(int number)
{
	std::string returnNumeral = "";
	if (number / 1000 != 0)
	{
		unsigned int counter = number / 1000;
		while (counter != 0)
		{
			returnNumeral.push_back('M');
			--counter;
		}
	}
	number = number % 1000;

	if (number / 100 != 0)
	{
		unsigned int counter = number / 100;
		conversionPerPlace(returnNumeral, 'C', 'D', 'M', counter);
	}
	number = number % 100;

	if (number / 10 != 0)
	{
		unsigned int counter = number / 10;
		conversionPerPlace(returnNumeral, 'X', 'L', 'C', counter);
	}
	number = number % 10;

	if (number != 0)
	{
		unsigned int counter = number;
		conversionPerPlace(returnNumeral, 'I', 'V', 'X', counter);
	}
	return returnNumeral;
}

int convertToNumber(std::string numeral)
{
	int returnNumber = 0;
	for (unsigned int i = 0; i < numeral.size(); ++i)
	{
		if (i == numeral.size() - 1) { returnNumber = returnNumber + numeralValue((numeral.at(i))); }
		else
		{
			if (deteminePrecedence(numeral.at(i)) < deteminePrecedence(numeral.at(i + 1)))
			{
				returnNumber = returnNumber + numeralValue(numeral.at(i + 1)) - numeralValue(numeral.at(i));
				++i;
			}
			else { returnNumber = returnNumber + numeralValue(numeral.at(i)); }
		}
	}
	return returnNumber;
}

int deteminePrecedence(char checkChar)
{
	const std::string ORDER_OF_NUMERALS = "IVXLCDM";
	return ORDER_OF_NUMERALS.find(checkChar);
}

int numeralValue(char numeral)
{
	if (numeral == 'I') { return 1; }
	if (numeral == 'V') { return 5; }
	if (numeral == 'X') { return 10; }
	if (numeral == 'L') { return 50; }
	if (numeral == 'C') { return 100; }
	if (numeral == 'D') { return 500; }
	if (numeral == 'M') { return 1000; }
}

void conversionPerPlace(std::string& returnNumeral, char lowVal, char medVal, char highVal, int counter)
{
	if (counter == 4)
	{
		returnNumeral.push_back(lowVal);
		returnNumeral.push_back(medVal);
	}
	else if (counter == 9)
	{
		returnNumeral.push_back(lowVal);
		returnNumeral.push_back(highVal);
	}
	else if (counter > 4)
	{
		returnNumeral.push_back(medVal);
		counter = counter % 5;
		while (counter != 0)
		{
			returnNumeral.push_back(lowVal);
			--counter;
		}
	}
	else if (counter < 4)
	{
		while (counter != 0)
		{
			returnNumeral.push_back(lowVal);
			--counter;
		}
	}
}

bool isNumber(std::string checkString)
{
	const std::string NUMBER_VALUES = "0123456789";
	for (int i = 0; i < checkString.size(); ++i)
	{
		if (NUMBER_VALUES.find(checkString.at(i)) == std::string::npos) { return false; }
	}
	return true;
}

bool isValidNumeral(std::string checkString)
{
	const std::string VALID_VALUE = "MDCLXVI";
	for (int i = 0; i < checkString.size(); ++i)
	{
		if (VALID_VALUE.find(checkString.at(i)) == std::string::npos) { return false; }
	}
	return true;
}
