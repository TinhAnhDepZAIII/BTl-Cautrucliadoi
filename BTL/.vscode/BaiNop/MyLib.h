#include <iostream>
#include <string>
#include <cstring>
#include <stack>
#include <cmath>
#include <iomanip>
using namespace std;

// TODO: NUMBERS
/* * * Infix to PostFix with numbers * * */
struct Node1 
{
    string data;
    Node1 *pLeft;
    Node1 *pRight;
};
bool ComparisonChar1AndChar2Ver1( char a, char b);
typedef Node1 *Tree1;
Tree1 MakeNewNode1 (char x);
Tree1 MakeNewNode1String (string x);
string Infix2Postfix (string s);
/* * * End implemenation of Infix to PostFix with numbers * * */


/* * * Infix to PreFix with numbers * * */
struct Node2
{
    string data;
    Node2 *pLeft;
    Node2 *pRight;
};
bool ComparisonChar1AndChar2Ver2( char a, char b);
typedef Node2 *Tree2;
Tree2 MakeNewNode2 (char x);
Tree2 MakeNewNode2String (string x);
string Infix2Prefix (string s);
/* * * End Infix to PreFix with numbers * * */

/* * * Evaluation PostFix and PreFix * * */
double PreFixCalculator(string s);
double PostFixCalculator(string k);
string PostfixPrefixCalculator(string s);
/* * * End Evaluation PostFix and PreFix * * */
// tODO: END NUMBERS



// TODO: LOGICAL EXPRESSION
/* * * Infix to PostFix with logical expression * * */

/* * * End InFix to PostFix with logical expression*/





