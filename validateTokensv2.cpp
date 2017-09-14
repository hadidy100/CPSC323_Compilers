/* 
California State University
CPSC 323 Project # 3  
Dr Ray Ahmadenia
Team Members: 
			Anas Elhadidy 
			Danny Pham 
			Malik Zubair  

The code reads the users input and parses each word from the statement that was entered the user to determine i the word is a legal word in the language
or not. If the word was legal, the code displays the token under which each legal word belongs to. If the word is not legal then the code prints a message for 
such a token. The algorithm that we implemented starts by populating 2 hash tables, one for the RESERVED WORDS tokens, and one for SPECIAL SYMBOLS token. 
This is to speed up the lookup process to O(log(n)) time complicity, rather than O(n) time complicity for lookup had it been an array. 

The main function calls  main_helper function which controls calling the other methods for the rest of the program. Each call to main_helper is to
handle ONE input statement that is entered by the user, and then the main method takes over to ask if the user wants to continue or not. 
 
main_helper method calls askForStatement method, where this method only asks for the statement and return that string back to main_helpe as a pass by reference 
parameter to save memory space. main_helper then send this returned string to partitionTheString method, which in turn breaks the input statement into words 
calls lexeme, where each lexeme starts as soon as the methods encounters a space delimiter. partitionTheString method returns this lexeme back to main_helper 
as pass by constant reference parameter. Once lexeme is return to main_helper, the method then goes through a series of if statements in the following way: 
1. send the lexeme to a method called isReservedWord where that function returns true if the lexeme was in the hash table that contains the reserved words
2. if it was not a reserved word then main_helper sends lexeme to isSpecialSymbol methods where the method returns true if the lexeme was in the hash table.
3. main_helper then sends lexeme to isIdentifier methods where it returns true if lexeme starts with a letter
4. if it was not then it sends lexeme to isNumber methods where it returns true if lexeme consisted of inly numbers. 
5. if non of the above were true then this is no an identifier. 
*/

#include <iostream>
#include <iomanip>
#include <fstream> 
#include <string> 
#include <map>
#include <ctype.h>
//******************************************* prototypes
std::string 	askForStatement (std::string&  );
bool 			isReservedWord (const std::string& , const std::map<std::string, std::string>& );
bool 			isSpecialSymbol (const std::string& , const std::map<std::string, std::string>& );
bool 			isIdentifier (const std::string& );
bool 			isNumber (const std::string& );
const 			std::string partitionTheString (const std::string& theInitialStatement, int& cursor);
void 			mainHelper ( std::map<std::string, std::string>& ,  std::map<std::string, std::string>&  );
//**************************************************
std::string askForStatement (std::string&  theInitialStatement)
{
	std::cout << "Enter a statement: ";
	std::getline (std::cin, theInitialStatement);
	std::cout.flush();
    return theInitialStatement;
}
//**********************************************
bool isReservedWord (const std::string& lexeme, const std::map<std::string, std::string>& myHashtable)
{
	std::map<std::string,std::string>::const_iterator   iter;
	iter = myHashtable.find(lexeme);
	if (iter != myHashtable.end()) 
	{
		 return (iter->second ==  "reserved word") ;
	}
	else
	{
		return false;
	}
}
//**********************************************
bool isSpecialSymbol (const std::string& lexeme, const std::map<std::string, std::string>& myHashtable)
{
	std::map<std::string,std::string>::const_iterator   iter = myHashtable.find(lexeme);
	//iter = myHashtable.find(lexeme);
	if (iter != myHashtable.end()) 
	{
		 return (iter->second == "special symbol");
	}
    else 
	{
       return false;	
	}
}
//**********************************************
bool isIdentifier (const std::string& lexeme)
{
	return (std::isalpha(lexeme[0]));
}

//**********************************************
bool isNumber (const std::string& lexeme)
{
	std::size_t found;
	found  = lexeme.find_first_not_of("0123456789");
	return(found == std::string::npos ) ;
}
//**********************************************

const std::string partitionTheString (const std::string& 	theInitialStatement, int& cursor)
{
		std::string lexeme = "";	
		while (theInitialStatement[cursor] != ' ' && cursor < theInitialStatement.size())
		{
			lexeme = lexeme + theInitialStatement[cursor];
			cursor= cursor +1;
		} 
	return lexeme;
}
//*************************************************

void mainHelper ( std::map<std::string, std::string>& specialSymbolsHashtable,  std::map<std::string, std::string>& reservedWordsHashtable )
{
	int 			cursor = 0;
	std::string  	numberToken = "number ";
	std::string  	identifierToken = "identifier "; 
	std::string  	notIdentifierToken =  "not identifier";	
	std::string 	theInitialStatement, lexeme; 
	
	askForStatement(theInitialStatement);
	lexeme = partitionTheString(theInitialStatement,cursor);
    while (cursor < theInitialStatement.size())
	{
		if (isReservedWord(lexeme, reservedWordsHashtable ))
		{	
			std::cout  << std::setw(60) << std::left << lexeme << std::setw(30) << std::left << reservedWordsHashtable[lexeme] << std::endl;
		}
		
		else if (isSpecialSymbol(lexeme,   specialSymbolsHashtable))
		{
			std::cout  << std::setw(60) << std::left << lexeme << std::setw(30) << std::left << specialSymbolsHashtable[lexeme]  <<std::endl;

		}
		else if (isNumber(lexeme)  )
		{
			std::cout  << std::setw(60) << std::left << lexeme << std::setw(30) << std::left << numberToken << std::endl;

		}
		else if (std::isalpha(lexeme[0]))
		{
			std::cout  << std::setw(60) << std::left << lexeme << std::setw(30) << std::left << identifierToken << std::left <<std::endl;

		}
		else 
		{
			std::cout  << std::setw(60) << std::left << lexeme << std::setw(30) << std:: left << notIdentifierToken << std::endl;
		}
		cursor = cursor + 1;
		lexeme = partitionTheString(theInitialStatement,cursor);
	}
}
//*************************************************
int main()
{
	std::map<std::string, std::string>  		rservedWordsHashtable, specialSymbolsHashtable;
	std::string 								answerToContinue = "Y";

//**************************************************
	rservedWordsHashtable["cout<<"]= "reserved word";
	rservedWordsHashtable["for"] 	= "reserved word";
	rservedWordsHashtable["int"] 	= "reserved word";
	rservedWordsHashtable["while"] = "reserved word";
//**************************************************
	specialSymbolsHashtable["="]  = "special symbol";
	specialSymbolsHashtable["*"]  = "special symbol";
	specialSymbolsHashtable["-"]  = "special symbol";
	specialSymbolsHashtable[";"]  = "special symbol";
	specialSymbolsHashtable["("]  = "special symbol";
	specialSymbolsHashtable[")"]  = "special symbol";
	specialSymbolsHashtable["<="] = "special symbol";
	specialSymbolsHashtable["+"]  = "special symbol";
	mainHelper(specialSymbolsHashtable,rservedWordsHashtable);
	std::cout << "CONTINUE(y/n)?";
	std::getline(std::cin,answerToContinue);
	
	while (std::toupper(answerToContinue[0]) != 'N')
	{
		mainHelper(specialSymbolsHashtable,rservedWordsHashtable);
		std::cout << "CONTINUE(y/n)?";
		std::getline(std::cin, answerToContinue);		
	}
}