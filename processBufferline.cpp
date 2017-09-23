/* 
CPSC 323 
Group member 
Elhadidy Anas 
Pham Danny 
Zubair Malik 

The program takes the content of a text file and removes any comment that come after the // string. It also inserts a space after any special symbols 
if there were no spaces. The sprcial symbols are defined in a set data struct to improve look up time complexity to O(1) in constant time. 
The methods that checks the special symbol returns aboolean value on wheather if the iterator ofund the // string or not. 
The main logic is done by partitioning each line of the text file , where each line is consedered a buffer line and the method returns a lexeme
for accumulated letter that come before space, comments, or a special character. If a spcial character is found then it is considered a lexeme by
it self if a comment was founf then the method ignores everything after the comment by going to the end of the bufferLine. 

The newley formatted lexeme is then sent to a new output file, to be compiled by the compiler later.  
 
*/
#include <iostream>
#include <fstream> 
#include <string> 
#include <iomanip>
#include <fstream> 
#include <map> 
#include <ctype.h> 
#include <set> 
//******************************* Prototypes
const char   getNextChracter(const std::string&,const int&);
bool isComment (const char&,const int&,const std::string&);
bool isSpecialSymbls (const char&);
std::string processBufferLine(const std::string&,int&);
//************************************* 
const char   getNextChracter(const std::string& bufferLine,const int& cursor)
{
	char NextChracter;
	(cursor < bufferLine.size()) ? NextChracter = bufferLine[cursor+1] : NextChracter = (char)0;
	return  NextChracter;
}
//************************************* 
bool isComment (const char& theCharacter,const int& cursor,const std::string& bufferLine)
{
	char NextChracter =   getNextChracter(bufferLine,cursor) ;
	std::string comparesionString = "";
	comparesionString = comparesionString + NextChracter + theCharacter; // c++ only allows concatenating character if you have a string in the expression 	
    return 	(comparesionString == "//");
}
 //************************************ 
bool isSpecialSymbls (const char& theCharacter)
{
 	 std::set<char>	 symbolSet {'=','+','*','-',';'};
	 std::set<char>::iterator iter = symbolSet.find(theCharacter);	
	 return (theCharacter == (*iter));
}
//*************************************
// Method that returns one lexeme at a time to the caller 
std::string processBufferLine(const std::string& bufferLine,int& cursor)
{
	 int     				stringLength = bufferLine.size();
	 char    				theCharacter = bufferLine[cursor];
	 std::string         	lexeme = "";
	 
	 while (
				bufferLine[cursor] != ' '                          &&//if it is not a space 
				cursor <= stringLength                             &&// if the cursor is not passed the last character of bufferLine 
				!isSpecialSymbls (bufferLine[cursor] )             &&// if the current character is not a symbol 
				!isComment(bufferLine[cursor], cursor, bufferLine)   // if the current character is not par t of the marker
			)
	 {// do the folllowing while loop is valid
		 lexeme = lexeme + bufferLine[cursor];
		 cursor = cursor + 1;			 
	 }// end of while loop  
	 
	 if (isSpecialSymbls(bufferLine[cursor])) // if the loop ended because of special symbol
	 { 
		lexeme = lexeme + ' '  + bufferLine[cursor] + ' '; // add a space before and after the symbol
		return lexeme;
	 }
	 
	 if(isComment(bufferLine[cursor], cursor, bufferLine))	// if the ended because of comments
	 {
    	 lexeme = ""; 
		 cursor = stringLength;
		 return lexeme;
	 }
	 
	 if(bufferLine[cursor] == ' ') // if the loop ended because of a space chracter  
	 {
		 if (lexeme != "" ) // if the space came in the middle of the bufferLine then return what we have accumulated already plus a space
		 {
			 lexeme = lexeme + bufferLine[cursor];
			 return lexeme;
		 }
		 else // if the space was followed by another space then 
		 { 
			lexeme = ""; 
			return lexeme; 
		 }		 
	 }      
}
//*******************************************
int main()
{
	int 				cursor = 0;
	std::ifstream   	inputFileStream; 
	std::ofstream    	outputFileStream;
	std::string     	bufferLine;
	
	inputFileStream.open("data.txt"); 		// input file 
	outputFileStream.open("newdata.txt", std::ofstream::out); 	// output file 
	
	while (!inputFileStream.eof())
	{
		getline(inputFileStream,bufferLine);
		std::string 	partOfBufferLine;
		while (cursor <=bufferLine.size())
		{
			partOfBufferLine = processBufferLine (bufferLine,cursor );
			if (partOfBufferLine != "" )	// to avoid printing the nu,, that comes from the comment line 
			{
				outputFileStream << partOfBufferLine;
			}
			cursor++;			
		}
	}	
	outputFileStream.close();
	inputFileStream.close();	
	return 0;
}