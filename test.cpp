/*

 Parser - an expression parser

 Author:  Nick Gammon 
          http://www.gammon.com.au/ 

(C) Copyright Nick Gammon 2004. Permission to copy, use, modify, sell and
distribute this software is granted provided this copyright notice appears
in all copies. This software is provided "as is" without express or implied
warranty, and with no claim as to its suitability for any purpose.
 
*/
#include "parser.h"

#include <iostream>

static const string SPACES = " \t\r\n";           // what gets removed when we trim

// get rid of leading and trailing spaces from a string
const string trim (const string & sInput, const string & t = SPACES)
{
  string s = sInput; 
  string::size_type i = s.find_last_not_of (t);
  if (i == string::npos)
    return "";
  else
   return s.erase (i + 1).erase (0, sInput.find_first_not_of (t)) ; 
} // end of trim

// remove backspaces from a string  
const string removeBackspaces (const string & sInput)
  {
  string s = sInput;
  string::size_type i;
  while ((i = s.find ('\b')) != string::npos)
    if (i == 0)
      s.erase (0, 1);  // backspace at start, just erase it
    else
      s.erase (i - 1, 2);   // erase character before backspace (and backspace)
  return s;
  }     // end of removeBackspaces

int main ()

  {
  string inputLine;

  
  try
    {
    while (true)
      {
      cout << "Enter expression ... ";
      getline (cin, inputLine);
      
      // remove backspaces entered while typing, get rid of leading/trailing spaces
      inputLine = trim (removeBackspaces (inputLine));
        
      if (inputLine.empty ())
        return 0;
      
      // create instance of parser, using entered input line
      Parser p (inputLine);
       
      // example of pre-loading a symbol
      p ["abc"] = 42;

      // parse entered expression, return result into "value
      double value = p.Evaluate ();
      
      // display result
      cout << "Result = " << value << endl;

      // example of retrieving a symbol
      double abc = p ["abc"]; 
      
      } // end of input loop
    
    } // end of try block
  
  // catch parse and runtime errors
  catch (exception & e)
    {
    cout << "exception: " << e.what ();
    return 1;
    }
  
  } // end of main
