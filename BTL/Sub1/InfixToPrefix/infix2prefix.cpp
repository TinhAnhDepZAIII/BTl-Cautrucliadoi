#include <iostream>
#include <string>
#include <cstring>
#include <stack>


using namespace std;
struct Node2
{
    string data;
    Node2 *pLeft;
    Node2 *pRight;
};
bool ComparisonChar1AndChar2Ver2( char a, char b){
    int charA = ((a == '+' || a == '-') ? 1 : ((a == '*' || a == '/') ? 2 : 3));
    int charB = ((b == '+' || b == '-') ? 1 : ((b == '*' || b == '/') ? 2 : 3));
    if( charA <= charB){
        return true;
    }
    return false;
}

typedef Node2 *Tree;
Tree MakeNewNode2 (char x)
{
    Tree p = new Node2;
    p->data = x;
    p->pLeft = p->pRight = NULL;
    return p;
}
Tree MakeNewNode2String (string x)
{
    Tree p = new Node2;
    p->data = x;
    p->pLeft = p->pRight = NULL;
    return p;
}
string Infix2Prefix (string s){
    
    stack<Tree> StackNode;
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
                    Tree t = MakeNewNode2(StackOperator.top());
                    t->pRight = StackNode.top();
                    StackNode.pop();
                    if ( StackNode.empty()) throw "Error: Syntax error";
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
                Tree tmp = MakeNewNode2String(temper);
                StackNode.push(tmp);
            }
            else
            {
                if ( use[i] == '.') throw "Error: Syntax Error";
                bool check = false;
                while ( ComparisonChar1AndChar2Ver2(use[i], StackOperator.top()) && StackOperator.top() != '('){
                    Tree tmp = MakeNewNode2(StackOperator.top());

                    if ( !isdigit(StackOperator.top()) && StackNode.size() <2){
                        if ( (StackOperator.top() != '+' && StackOperator.top() != '-')  && (tmp->data != "+" && tmp->data != "-")){
                            throw "Undefined error";
                        }else 
                        {
                            char temp = StackOperator.top();
                            StackOperator.pop();
                            StackOperator.push((temp == use[i] ? '+' : '-'));
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
    if (StackNode.size() != 1 && !isdigit(StackNode.top()->data[0])) throw "Syntax Error";

    // tree to prefix
    string res ="";
    Tree tmp = StackNode.top();
    StackPrint.push(tmp);
    while(!StackPrint.empty()){
        Tree tmp = StackPrint.top();
        StackPrint.pop();
        res += tmp->data + " ";
        if(tmp->pRight != NULL){
            StackPrint.push(tmp->pRight);
        }
        if(tmp->pLeft != NULL){
            StackPrint.push(tmp->pLeft);
        }
    }
    if (res.back() == ' ') {
        res.pop_back();
    }
    return res;

}

int main (){
    string file = "59+107*83*72*91/(27-(112*153)*(111+76))";
    string res = Infix2Prefix(file);
    cout<<res;
    return 0;
}