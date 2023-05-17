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
bool ComparisionString1AndString2( string a, string b){
    int charA = ((a == "->")? 1 : ((a == "<->") ? 2 : (a == "|" ? 3 : (a == "&" ? 3 : 4))));
    int charB = ((b == "->")? 1 : ((b == "<->") ? 2 : (b == "|" ? 3 : (b == "&" ? 3 : 4))));
    if( charA <= charB){
        return true;
    }
    return false;
}
typedef Node *Tree;
Tree MakeNewNode (string x)
{
    Tree p = new Node;
    p->data = x;
    p->pLeft = p->pRight = NULL;
    return p;
}
string LogicInfix2Postfix(string infix){
    stack<Tree> StackNode;
    stack<string> StackOperator;
    stack<Tree> StackPrint;
    string use = infix ;
    use = '(' + use + ')';
    int StringLength = use.length();
    for( int i{0} ; i< StringLength; i++){
        if(use[i] == ' '){
            continue;
        }
        else
        {
            if(use[i] == '('){
                StackOperator.push(use.substr(i,1));
            }
            else if ( use[i] == ')'){
                while(StackOperator.top()!= "("){
                    Tree t = MakeNewNode(StackOperator.top());
                    if ( t->data == "~"){
                        t->pRight = StackNode.top();
                    }
                    else{
                        t->pRight = StackNode.top();
                        StackNode.pop();
                        t->pLeft = StackNode.top();
                    }
                    StackNode.pop();
                    StackNode.push(t);
                    StackOperator.pop();
                }
                StackOperator.pop();
            }
            else if (isalpha(use[i])){
                Tree t = MakeNewNode(use.substr(i,1));
                StackNode.push(t);
            }
            else {
                    string tmp = "";
                    if(use[i] == '<'){
                        tmp = use.substr(i,3);
                        i+=2;
                    }else if(use[i] == '-'){
                        tmp = use.substr(i,2);
                        i+=1;
                    }else{ tmp = use.substr(i, 1);}
                    while(!StackOperator.empty() && ComparisionString1AndString2(tmp, StackOperator.top()) && StackOperator.top() != "("){
                        Tree t = MakeNewNode(StackOperator.top());
                        if ( t->data == "~"){
                            t->pRight = StackNode.top();
                        }
                        else{
                            t->pRight = StackNode.top();
                            StackNode.pop();
                            t->pLeft = StackNode.top();
                        }
                        StackNode.pop();
                        StackNode.push(t);
                        StackOperator.pop();
                    }
                    StackOperator.push(tmp);
            }
        }
    }
    
    string res="";
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
                    res += last->data ;
                }
            }
        }
    }
    return res; 
}
int main (){
    string file = "~t->t&~w|(z&(p&(w&(p|p&q)|y&z&z)<->x&(~p|z)&~y))";
    string res = LogicInfix2Postfix(file);
    cout<<res;
    return 0;
}