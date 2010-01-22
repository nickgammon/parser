#ifndef PARSER_H
#define PARSER_H

#ifdef WIN32
  
// disable warnings about long names
  #pragma warning( disable : 4786)

  // under Visual C++ 6 these do not seem to exist
  template <typename T> 
  inline T min (const T a, const T b)
    {
    return (a < b) ? a : b;
    } // end of min

  template <typename T> 
  inline T max (const T a, const T b)
    {
    return (a > b) ? a : b;
    } // end of max

  template <typename T> 
  inline T abs (T i)
    {
    return (i < 0) ? -i : i;
    } // end of abs

#endif

#include <string>
#include <map>
#include <stdexcept>
#include <sstream>

#include <math.h>
#include <time.h>

using namespace std;

// make a string on-the-fly
#define MAKE_STRING(msg) \
   (((ostringstream&) (ostringstream() << boolalpha << msg)).str())

class Parser
  {
  
  public:
    
  typedef enum TokenType
    {
    NONE,
    NAME,
    NUMBER,
    END,
    PLUS='+',
    MINUS='-',
    MULTIPLY='*',
    DIVIDE='/',
    ASSIGN='=',
    LHPAREN='(',
    RHPAREN=')',
    COMMA=',',
    NOT='!',
    
    // comparisons
    LT='<',
    GT='>',
    LE,     // <=
    GE,     // >=
    EQ,     // ==
    NE,     // !=
    AND,    // &&
    OR,      // ||
    
    // special assignments
    
    ASSIGN_ADD,  //  +=
    ASSIGN_SUB,  //  +-
    ASSIGN_MUL,  //  +*
    ASSIGN_DIV   //  +/
    
    };

  private:
    
  string program_;
  
  const char * pWord_;
  const char * pWordStart_;
  // last token parsed
  TokenType type_;
  string word_;
  double value_;
     
  public:
 
  // ctor
  Parser (const string & program) 
    : program_ (program), pWord_ (program_.c_str ()), type_ (NONE)
      {  
      // insert pre-defined names:
      symbols_ ["pi"] = 3.1415926535897932385;
      symbols_ ["e"]  = 2.7182818284590452354;      
      }
  
  const double Evaluate ();  // get result
  const double Evaluate (const string program);  // get result

  // access symbols with operator []
  double & operator[] (const string & key) { return symbols_ [key]; }

  // symbol table - can be accessed directly (eg. to copy a batch in)
  map<string, double> symbols_;

  private:

  const TokenType GetToken (const bool ignoreSign = false);  
  const double CommaList (const bool get);
  const double Expression (const bool get);
  const double Comparison (const bool get);
  const double AddSubtract (const bool get);
  const double Term (const bool get);      // multiply and divide
  const double Primary (const bool get);   // primary (base) tokens

  inline void CheckToken (const TokenType wanted)
    {
    if (type_ != wanted)
      throw runtime_error (MAKE_STRING ("'" << static_cast <char> (wanted) << "' expected."));    
    }
  };  // end of Parser


#endif // PARSER_H
