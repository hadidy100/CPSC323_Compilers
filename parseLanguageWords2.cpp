/*
CPSC 323 Project # 5 
Team members: 

Elhadidy Anas 
Pham Danny 
Zubair Malik 

The following program takes an input form the user and validates it by checking if it has a dollar sign at the end or not. If it does, it 
removes the dollar sign and assign that to lexeme. 
The program then goes throug hthe grammer that is represented by the FA below for the Langaudge that is given below. The grammer consists of 3 states {S} the initial state, and 2 final states {b} and {S,B}. 
If the very first letter in lexeme is either a or b then that makes state S valid, and the program goes on to check state {B} OR state {s,B}. If the first letter in lexeme was b then we can only go to state {B} and accept only c(s) or stop at the first letter, but if the first letter in lexeme was a then the program goes to state {S,B} and then every letter thereafter has to be all a(s) or [a(s) and one b and zero or more c(s)]  or [a(s) and zero or more c(s)]. 


Language = a* (a+b) c* is NDFA so we convert it to DFA as bellow based on the following table 


     |  a  |  b  |  c  |
=========================
{S}  |{s,b}| {B} | { } |
=========================
{B}  | { } | { } | {B} |
========================= 
{S,B}|{S,B}| {B} | {B} |
=========================




                        State {S,b}

    state {s}             /---\
     /---\               /     \
    /     \              |  +  |======>> b or c going to {b} >>======>>
    |  -  |===== a ====>>|     |                                       )
    |     |              \     /                                      )
    \     /               \___/                                      )
     \___/\\                ()                                      )
           \\                a  loop                               )
            \\                                                    )
             \\                                                  )
              \\                                                )
               \\                                              )
                 b                                            )
                 \\                                          )
                  \\                                        )
                   \\                                      )
                    \\                                    )
                     VV                                  )
                    /---\                               )
                   /     \===>()c loop                 )
                   |  +  |                            )
                   |     |                           /
                   \     /<<====== b or c <<========/
                    \---/
                           
                   State{b}                                                                   
*/
#include <iostream>
#include <string> 
#include <iomanip>
#include <ctype.h> 
//***********************prototypes 
bool validateStateB  (const char&);
bool validateStateSB (const std::string&, int&);
bool stringIsValid   (const std::string&); 
std::string removeDollarSignFromString(std::string&);
//********************************************
bool stringIsValid (const std::string& theInitialString)
{
 int theSize = theInitialString.size(); 
 return (theInitialString[theSize-1] == '$'); 
}
//*****************************************************************************************
std::string removeDollarSignFromString(std::string& theInitialString)
{
 std::string  newString = "";
 for (int cursor =0; cursor < theInitialString.size()-1; cursor++) 
 {
  newString = newString + theInitialString[cursor];
 }
 return newString; 
}
//*****************************************************************************************
bool validateStateB(const char& theCharacter)
{
  return (theCharacter == 'c');
}
//********************************************
bool validateStateSB(const std::string& lexeme, int& cursor)
{
  /*
  if lexeme[0] = 'b' 
  {
   return validateStateB(lexeme[cursor]);
  }
  */
  //else if lexeme[0] = 'a' 
  //{
   if (lexeme[cursor] == 'a') 
   {
    return true; 
   }
   else if (lexeme[cursor] == 'b' || lexeme[cursor] == 'c') 
   {
   if ( cursor+1 < lexeme.size() ) 
   {
    return validateStateB(lexeme[cursor+1]); // manipulate the status of stateB within stateSB
   }
   else 
   {
    return validateStateB(lexeme[cursor]); // manipulate the status of stateB within stateSB
   }
   }
   else 
    return false;
 // }
     
}
//***********************************************
int main()
{
  bool     stateS  = false; 
  bool     stateB  = true; 
  bool     stateSB = true;
  std::string   lexeme  = "";
  int     cursor  = 0;
//*************************************************
  std::cout << "Enter a word to be parse: " ; 
  std::getline (std::cin, lexeme); 
  if (stringIsValid(lexeme))
  {
   lexeme = removeDollarSignFromString(lexeme);  
   (lexeme[0] == 'a' || lexeme[0] == 'b') ? stateS = true : stateS = false;
   while (stateS && stateB && stateSB && cursor < lexeme.size())
   {
    cursor++; 
    if (lexeme[0] == 'b')
    {
     stateB = validateStateB( lexeme[cursor] );
    }
    else if (lexeme[0] == 'a')
    {
     validateStateSB (lexeme,cursor); 
    }
    else 
    {
     stateS = false; stateB = false; stateSB = false;  // not necesssary but why not 
    }
    
   }// end while loop 
   
   if (stateS && stateB && stateSB) 
   {
    std::cout << "The word: " << lexeme << " that you entered is accepted! " << std::endl;
   }
   else 
   {
    std::cout << "The word: " << lexeme << " that you entered is not accepted! " << std::endl;
   }
  }
  else // if string is not valid 
  { 
   std::cout << "The string that you entered is not valid, you need to end it with a dollar sign" << std::endl;
  }

}