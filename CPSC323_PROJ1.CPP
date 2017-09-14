<<<<<<< HEAD
/*
CSUF
CPSC 323   Project 1 
Dr Ray Ahmadina
Team Members: 
Anas Elhadidy 
Danny Pham 
Malik  ... 

This program reads a postfix expression and cmputes its value, where all the variables are single letters of type integers, and their value must be entered by the user. 
The program will read the string of characters entered by the user, and the stores this string in an array of characters, where it breaks 
it looks at every single , and prompts the user to enter the value if it was an alpha, or refrain from askin if the alpha value has been
collected befor, or perform the infix operation if it was an operator. The programs halts this process if the chracter wass a dollar sign. 

The program also checks if there were still oprators left that did not get to calulate any other number, due to wrong input from user, and throws an error if it was the case. 

The algorithim is done utilizing a stack, where we only push numbers and pop 2 out once we encouter an operator, and the result of the operators calculation is pushed back to the stack until we encounter the dollar sign. 

There is a method that calculated the 2 operator, and returns the results of the calculation based on the operator, and another method that checks if we prompted for this letter before, so that we do not ask for it again, and only push the number to the stack without asking 
This is done by storing the letter in a hashtable and then checking the value in constant time 
*/



#include <iostream> 
#include <stack> 
#include <string> 
#inclide <sstream>
#include <map>

//**************
using namespace std; 

int main () 
{ 
    // Even though the input are integers, we might get double from calclating a division, theirfor; stack stores doubles
	stack <double>   theStack; 
	string theString; 
	int cursor = 0;
	int counter = 0;
	int operand1 = 0;
	int operand2 = 0;
	int result = 0;
	int sSize = 0;
	int theNumber;
	int valueToBePushed = 0;
	// map to lookup values for letter that we visited before
	map <string, int> myHashTable; 
	  
	count << " Enter a postfix expresion with a $ at the end: "; 
    cin >> theString; 
	sSize = theString.size();
    if (stringIsValid(theString))
	{
		while (theString[counter] != "$"
		{
			if (isAlpha(theString[counter]))
			{
				if (!exists (theString[counter]))
				{
					cout << "Enter the value of " ;
					cin >> theNumber;
					// Store the value in the hashtable incase if we need to retreive it again 							
					myHashTable[theString[counter]] = theNumber;
					valueToBePushed = theNumber;
				}
				else // if we asked for his letter before 
				{
						valueToBePushed = myHashTable[theString[counter]];
				}
				// now that we got the number we can just push it to the stack 
				theStack.push(valueToBePushed);
			} // end of isLetter
			else if (isOperator(theString[counter])
			{
				if theStack.size() < 2 
				{
					// throw an error 
					cout << " soething went wrong in your input of the  numbers, please retern again. " << endl; 
					return 0;
				}
				else 
				{
					operand2 = theStack.top(); 
					theStack.pop(); 
					operand1 = theStack.top(); 
					theStack.pop(); 
					result = calculate (oprand1, operand2, theString[counter]); 
					theStack.push(result);
				}
			}// end if isOperator
			counter = counter + 1; 
			cursor = cursor + 1;
		}// end of while loop
		theStack.pop();
		if (theStack.empty()) 
		{
			cout << "Final value = " << result;
		}
		else 
		{
			cout << " You must have entered a wrong expression, please try again ! " << endl; 
			return 0;
		}
		
	} // end of  if (stringIsValid(theString))
	else 
	{
		// throw an error
		cout << " You need a dollar sign at the end, please try again! " << endl;
	}
	return 0;
}// end of main
//*************************************************
bool isOperator (const string& input) 
{
	string ops[] == {"-","+","*","/"};
	for int (i=0; i<4; i++)
	{
		if (input == ops[i])
		{
			return true;
		}
		return false;
	}
}
//********************************************************
bool isAlpha (const string& input) 
{
	if isalpha(input[0]) return true;
	return false;
}
//*********************************************************
bool exists (const string& theLetter, const string& theString, int cursor)
{
	if cursor>0
	{
		for (int counter=cursor-1; counter< theString.size();  counter++)
		{
			if (theString[counter] == theLetter) return true;
		}
	}
	return false;
}
//***********************************************************
double calculate (const int& input1, const int& input2, const char& theoperator)
{
	double result; 	
	if (theOperator == "-")
	{
		result = input1 - input2;		
	}
	else if (theOperator == "+")
	{
		result = input1 + input2;		
	}	
	else if (theOperator == "*")
	{
		result = input1 * input2;		
	}
	else if (theOperator == "/") 
	{
		result = input1 / input2;		
	}
	return result
}
//**************************************************
bool stringIsValid (const string& theString)
{
	int theSize = theString.size(); 
	if (theString[theSize-1] == "$") return true; 
	return false;
=======
/*
CSUF
CPSC 323   Project 1 
Dr Ray Ahmadina
Team Members: 
Anas Elhadidy 
Danny Pham 
Malik  ... 

This program reads a postfix expression and cmputes its value, where all the variables are single letters of type integers, and their value must be entered by the user. 
The program will read the string of characters entered by the user, and the stores this string in an array of characters, where it breaks 
it looks at every single , and prompts the user to enter the value if it was an alpha, or refrain from askin if the alpha value has been
collected befor, or perform the infix operation if it was an operator. The programs halts this process if the chracter wass a dollar sign. 

The program also checks if there were still oprators left that did not get to calulate any other number, due to wrong input from user, and throws an error if it was the case. 

The algorithim is done utilizing a stack, where we only push numbers and pop 2 out once we encouter an operator, and the result of the operators calculation is pushed back to the stack until we encounter the dollar sign. 

There is a method that calculated the 2 operator, and returns the results of the calculation based on the operator, and another method that checks if we prompted for this letter before, so that we do not ask for it again, and only push the number to the stack without asking 
This is done by storing the letter in a hashtable and then checking the value in constant time 
*/



#include <iostream> 
#include <stack> 
#include <string> 
#inclide <sstream>
#include <map>

//**************
using namespace std; 

int main () 
{ 
    // Even though the input are integers, we might get double from calclating a division, theirfor; stack stores doubles
	stack <double>   theStack; 
	string theString; 
	int cursor = 0;
	int counter = 0;
	int operand1 = 0;
	int operand2 = 0;
	int result = 0;
	int sSize = 0;
	int theNumber;
	int valueToBePushed = 0;
	// map to lookup values for letter that we visited before
	map <string, int> myHashTable; 
	  
	count << " Enter a postfix expresion with a $ at the end: "; 
    cin >> theString; 
	sSize = theString.size();
    if (stringIsValid(theString))
	{
		while (theString[counter] != "$"
		{
			if (isAlpha(theString[counter]))
			{
				if (!exists (theString[counter]))
				{
					cout << "Enter the value of " ;
					cin >> theNumber;
					// Store the value in the hashtable incase if we need to retreive it again 							
					myHashTable[theString[counter]] = theNumber;
					valueToBePushed = theNumber;
				}
				else // if we asked for his letter before 
				{
						valueToBePushed = myHashTable[theString[counter]];
				}
				// now that we got the number we can just push it to the stack 
				theStack.push(valueToBePushed);
			} // end of isLetter
			else if (isOperator(theString[counter])
			{
				if theStack.size() < 2 
				{
					// throw an error 
					cout << " soething went wrong in your input of the  numbers, please retern again. " << endl; 
					return 0;
				}
				else 
				{
					operand2 = theStack.top(); 
					theStack.pop(); 
					operand1 = theStack.top(); 
					theStack.pop(); 
					result = calculate (oprand1, operand2, theString[counter]); 
					theStack.push(result);
				}
			}// end if isOperator
			counter = counter + 1; 
			cursor = cursor + 1;
		}// end of while loop
		theStack.pop();
		if (theStack.empty()) 
		{
			cout << "Final value = " << result;
		}
		else 
		{
			cout << " You must have entered a wrong expression, please try again ! " << endl; 
			return 0;
		}
		
	} // end of  if (stringIsValid(theString))
	else 
	{
		// throw an error
		cout << " You need a dollar sign at the end, please try again! " << endl;
	}
	return 0;
}// end of main
//*************************************************
bool isOperator (const string& input) 
{
	string ops[] == {"-","+","*","/"};
	for int (i=0; i<4; i++)
	{
		if (input == ops[i])
		{
			return true;
		}
		return false;
	}
}
//********************************************************
bool isAlpha (const string& input) 
{
	if isalpha(input[0]) return true;
	return false;
}
//*********************************************************
bool exists (const string& theLetter, const string& theString, int cursor)
{
	if cursor>0
	{
		for (int counter=cursor-1; counter< theString.size();  counter++)
		{
			if (theString[counter] == theLetter) return true;
		}
	}
	return false;
}
//***********************************************************
double calculate (const int& input1, const int& input2, const char& theoperator)
{
	double result; 	
	if (theOperator == "-")
	{
		result = input1 - input2;		
	}
	else if (theOperator == "+")
	{
		result = input1 + input2;		
	}	
	else if (theOperator == "*")
	{
		result = input1 * input2;		
	}
	else if (theOperator == "/") 
	{
		result = input1 / input2;		
	}
	return result
}
//**************************************************
bool stringIsValid (const string& theString)
{
	int theSize = theString.size(); 
	if (theString[theSize-1] == "$") return true; 
	return false;
>>>>>>> 6c002fb14cf1c4565068f685a73a85294ef596fb
}