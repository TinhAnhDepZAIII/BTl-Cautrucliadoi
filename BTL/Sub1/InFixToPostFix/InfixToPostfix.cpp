#include <iostream>
#include <string>
#include <cstring>
#include <stack>


using namespace std;
struct Node 
{
    string data;
    Node *pLeft;
    Node *pRight;
};
bool ComparisonChar1AndChar2( char a, char b){
    int charA = ((a == '+' || a == '-') ? 1 : ((a == '*' || a == '/') ? 2 : 3));
    int charB = ((b == '+' || b == '-') ? 1 : ((b == '*' || b == '/') ? 2 : 3));
    if( charA <= charB){
        return true;
    }
    return false;
}

typedef Node *Tree;
Tree MakeNewNode (char x)
{
    Tree p = new Node;
    p->data = x;
    p->pLeft = p->pRight = NULL;
    return p;
}
Tree MakeNewNodeString (string x)
{
    Tree p = new Node;
    p->data = x;
    p->pLeft = p->pRight = NULL;
    return p;
}
string Infix2Postfix (string s){
    
    stack<Tree> StackNode;
    stack<Tree> StackNodeTemp; // for handling errors testcases.

    stack<char> StackOperator;
    stack<Tree> StackPrint;
    
    string use = s;
    use = '(' + use + ')';
    int StringLength = use.length();
    for(int i =0; i<StringLength; i++){
        if (use[i] == ' '){
            continue;
        }else
        {
            if(use[i] == '(')
            {    // special open bracket operator
                StackOperator.push(use[i]);
            }
            else if (use[i] == ')')
            {  // special open bracklet operator
                while(StackOperator.top() != '('){
                    Tree t = MakeNewNode(StackOperator.top());
                    t->pRight = StackNode.top();
                    StackNode.pop();
                    t->pLeft = StackNode.top();
                    StackNode.pop();

                    if ( t->data == "/" && t->pRight->data == "0") throw "Error: Divide by zero";
                    if ( t->data == "^" && t->pRight->data == "0" && t->pLeft->data == "0") throw "Error: Undefined error";

                    StackNode.push(t);
                    StackOperator.pop();
                }
                StackOperator.pop();
            }
            else if( isdigit(use[i])){
                string temper ="";   
                while(isdigit(use[i])){
                    temper += use[i];
                    if ( !isdigit(use[i+1])){break;}
                    i++;
                }
                Tree tmp = MakeNewNodeString(temper);
                StackNode.push(tmp);
            }
            else
            {
                if ( use[i] == '.') throw "Error: Syntax Error";
                bool check = false;
                while ( ComparisonChar1AndChar2(use[i], StackOperator.top()) && StackOperator.top() != '('){
                    Tree tmp = MakeNewNode(StackOperator.top());

                    if ( !isdigit(StackOperator.top()) && StackNode.size() <2){
                        if ( (StackOperator.top() != '+' && StackOperator.top() != '-')  && (tmp->data != "+" && tmp->data != "-")){
                            throw "Undefined error";
                        }else 
                        {
                            char tempp = StackOperator.top();
                            StackOperator.pop();
                            StackOperator.push((tmp->data[0] == tempp ? '+' : '-'));
                        }   
                        check = true;   
                        break;
                    }
                    else {
                        tmp->pRight = StackNode.top(); StackNode.pop();
                        tmp->pLeft = StackNode.top(); StackNode.pop();
                        if ( tmp->data == "/" && tmp->pRight->data == "0") throw "Error: Divide by zero";
                        if ( tmp->data == "^" && tmp->pRight->data == "0" && tmp->pLeft->data == "0") throw "Error: Undefined error";
                        StackNode.push(tmp);
                        StackOperator.pop();
                    }
                }
                if ( !check) StackOperator.push(use[i]);         
            }
        }
    }
    if (StackOperator.size() != 0) throw "Syntax Error";

    string res = "";
    Tree temp = StackNode.top();
    while(true){
        if(temp != nullptr){
            StackPrint.push(temp);
            temp= temp->pLeft;
        }else{
            if(StackPrint.empty()) break;
            temp = StackPrint.top()->pRight;
            if ( temp == nullptr){
                Tree last  = nullptr;
                while( !StackPrint.empty() && StackPrint.top()->pRight == last){
                    last = StackPrint.top();
                    StackPrint.pop();
                    res += last->data + " ";
                }
            }
        }
    }
    if (res.back() == ' ') {
        res.pop_back();
    }
    return res;   
}
int main (){
    try {
    string file = "1++1";
    string res = Infix2Postfix(file);
    cout<<res;
    }
    catch(const char* msg) {
        cerr << msg << endl;
    }
    return 0;
}