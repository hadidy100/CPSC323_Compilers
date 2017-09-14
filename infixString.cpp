/*
CSUF
CPSC 323   Project 1 
Dr Ray Ahmadina
Team Members: 
	Anas Elhadidy 
	Danny Pham 
	Malik  Zubair

This program reads a postfix expression and computes its value, where all the variables are integers, and their value must be entered by the user. 
The program will read the string of characters, and segments the string when it has a space delimiter. It prompt the user to enter the value that 
corresponds to the string if it was alpha, and refrains from askin for the value again, If the alpha value has been collected before, ot the 
segmented string was actually a number.  It performs an infix operation if it was an operator, and then the programs halts this process if the 
end of the string was a dollar sign. The program also checks if there were still oprators left that did not get to calulate any other number, due to a wrong input 
from user, and throws an error if it was the case. 


The algorithim is done utilizing a stack, and a map, where we only push numbers to the stack as they come in, and pop 2 out at a time once we encouter an operator. The result
of the operator's calculation is pushed back to the stack until we encounter another operator. This process repeats until the dollr sign terminator.   

Method isOperator checks to se if the character that is being parsed from the strin is operator and retruns a boolean based on that. 
Method isAlpha checks to se if the character that is being parsed from the strin is operator and retruns a boolean based on that. 
Method exists takes a map data structur and a chracter to check if that chracter exists in the  map, and returns a boolean based on that.
Method calculate gives the result of calculating the 2 poped numbers from the stack in a double data type, incae if there was a division operator for the 2 operands. 
Method stringIsValid takes the actual string that was entered by the user and checks if it had a dollar sign at the tail, and returns boolean based on that.

The list of the variable and their usage is as follows: 

	std::stack <double>		 theStack  
    Stack stores double for possible division calculations 
	
	std::string 			theInitialString;
    The initial string that the user entered. 
	
	int 			 		cursor = 0;
    Integer to iterate through the std::string that was entered	
	
    The numbers that will be calculated by the operators and the result of the calculation  
	int 			 		operand1 = 0;
	int 					operand2 = 0;
	double 					result = 0;

    map to lookup values for letter that we visited before	
	std::map<char,int>		myHashTable; 

	Each single character that is going to point to numbers in the hashtable	
	char 					theCharThatMapsToEachNum;
	
    Each single number that is going to be pointed to by theCharThatMapsToEachNum 		
	int 					theNumberThatsMapsToEachChar;	
	
	
    the number that we will push into the stack 
	double 					valueToBePushed = 0;
*/
#include <iostream> 
#include <stack> 
#include <string> 
#include <sstream>
#include <map>
#include <string>
#include <ctype.h>
#include <stdlib.h>
//*****************************************************************************************
//prototypes 
	void pushTheData(std::map<std::string, int>&, const std::string&, std::stack<double>& ); 
    void parseTheString (std::string& ,std::string& ,const int& , const std::string&  );
	bool isAlpha (const char& );
	bool isOperator(const char&);
	double calculate(const int&,const int&,const char&);	
	bool exists(const std::map<std::string,int>&,  const std::string&);
	int mainHelper( std::map<std::string, int> &,  std::stack<double>& );
	bool stringHasAlpha (const std::string& );
	bool stringIsValid (const std::string&);	
//*****************************************************************************************
int main()
{
	char 								answerToContinue = 'Y';
	std::stack <double>					theStack; 
	std::map<std::string,int>			myHashTable; 
	mainHelper(myHashTable, theStack);
	while (toupper(answerToContinue) != 'N')
	{
		std::cout << "Continue (y/n)? " ;
		std::cin >> answerToContinue;
		std::cout << answerToContinue << std::endl;
		if (toupper(answerToContinue == 'Y'))
		{
			mainHelper(myHashTable, theStack);
		}			
		while (   toupper(answerToContinue) != 'N'  &&  toupper(answerToContinue) != 'Y'  )
		{
			std::cout << "Please enter only y or n " ;
			std::cin >> answerToContinue;
		}			
	}
	return 0;
}
//****************************************************************************************	
int	mainHelper(std::map<std::string, int> & myHashTable, std::stack<double>& theStack)
{ 
	std::string 					theInitialString; 
	std::string 					lettersCollected = "";
	std::string 					digitsCollected ="";
	int 			 				cursor = 0;
	std::string 					theStringThatMapsToEachNum;
	int 							theNumberThatsMapsToEachChar;	
	double 							valueToBePushed = 0;
	double 							finalValue = 0;
    theInitialString = "";
	std::cout << " Enter a postfix expresion with a $ at the end: "; 
    std::getline(std::cin , theInitialString); 
    if (stringIsValid(theInitialString))
	{
		while (theInitialString[cursor] != '$') 
		{
			if (theInitialString[cursor] == ' ' || theInitialString[cursor] == '$')
			{
				if (lettersCollected != "")
				{
					pushTheData(myHashTable, lettersCollected, theStack); 
					lettersCollected = "";
				}
			}
			else 
			{				
				parseTheString (lettersCollected,digitsCollected,cursor,theInitialString);
			}
			cursor = cursor + 1;
		}
		finalValue = theStack.top();
		theStack.pop();
		if (theStack.empty()) 
		{
			std::cout << "Final value = " << finalValue << std::endl;
		}
		else 
		{
			std::cout << " You must have entered a wrong expression, please try again ! " << std::endl; 
			return 0;
		}	
	}
	return 0;
}
//*****************************************************************************************
void pushTheData( std::map<std::string, int>& myHashTable,const std::string& lettersCollected, std::stack<double>& theStack)
{
	int 			 				operand1 = 0;
	int 							operand2 = 0;
	double 							result = 0;
	double 							theMapedNumber = 0;
	std::string   					copyOfString;	
	if (stringHasAlpha(lettersCollected) )
	{
		if (exists (myHashTable,lettersCollected))
		{
			theMapedNumber = myHashTable[lettersCollected];
		}
		else 
		{
			std::cout << "Enter the value for " << lettersCollected << " : ";
			std::cin >> theMapedNumber;
			myHashTable[lettersCollected] = theMapedNumber;
		}
	}
	else if (isOperator(lettersCollected[0]))
	{
		if (theStack.size() < 2 )
		{
			std::cout << " something went wrong in your input of the numbers, please reenter again. " << std::endl; 
		}
		else 
		{
			operand2 = theStack.top(); 
			theStack.pop(); 
			operand1 = theStack.top(); 
			theStack.pop(); 
			result = calculate (operand1, operand2, lettersCollected[0]); 
			theMapedNumber = result;
		}
	}// end if isOperator	
	else 
	{
		copyOfString = lettersCollected;
		theMapedNumber = atof(copyOfString.c_str());
	}
		theStack.push(theMapedNumber);	
}	
//*****************************************************************************************
 void parseTheString (std::string& lettersCollected, std::string& digitsCollected,const int& cursor, const std::string& theInitialString)
{
	lettersCollected = lettersCollected + theInitialString[cursor] ;
}
//*****************************************************************************************
bool isAlpha (const char& theInput) 
{
	return (isalpha(theInput));
}
//*****************************************************************************************
bool exists(const std::map<std::string,int>&   myHashTable,  const std::string&  theStringThatMapsToEachNum)
{
	std::map<std::string,int>::const_iterator    iter = myHashTable.find(theStringThatMapsToEachNum);
	return  (myHashTable.end() != iter);
}
//*****************************************************************************************
bool stringIsValid (const std::string& theInitialString)
{
	int theSize = theInitialString.size(); 
	return (theInitialString[theSize-1] == '$'); 
}
//*****************************************************************************************
bool stringHasAlpha (const std::string& lettersCollected)
{ 
	std::size_t found;
	found  = lettersCollected.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcefghijklmnopqrstuvwxyz");
	return(found != std::string::npos ) ;
}
//*****************************************************************************************
double calculate (const int& input1, const int& input2,  const char& theOperator)
{
	double result;   	
	if ( theOperator == '-')
	{
		result = input1 - input2;		
	}
	else if (theOperator == '+')
	{
		result = input1 + input2;		
	}	
	else if (theOperator == '*')
	{
		result = input1 * input2;		
	}
	else if (theOperator == '/') 
	{
		result = input1 / input2;		
	}
	return result;
}
//*****************************************************************************************
bool isOperator(const char& theOperator) 
{
	return (theOperator == '+' or theOperator == '-' or theOperator == '*' or theOperator == '/');
}