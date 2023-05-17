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
bool ComparisionString1AndString2( string a, string b){
    int charA = ((a == "->")? 1 : ((a == "<->") ? 2 : (a == "|" ? 3 : (a == "&" ? 3 : 4))));
    int charB = ((b == "->")? 1 : ((b == "<->") ? 2 : (b == "|" ? 3 : (b == "&" ? 3 : 4))));
    if( charA <= charB){
        return true;
    }
    return false;
}
typedef Node2 *Tree;
Tree MakeNewNode (string x)
{
    Tree p = new Node2;
    p->data = x;
    p->pLeft = p->pRight = NULL;
    return p;
}
string LogicInfix2Prefix(string infix){
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
                        t->pLeft = StackNode.top();
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
                            t->pLeft = StackNode.top();
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
    
    string res ="";
    Tree tmp = StackNode.top();
    StackPrint.push(tmp);
    while(!StackPrint.empty()){
        Tree tmp = StackPrint.top();
        StackPrint.pop();
        res += tmp->data ;
        if(tmp->pRight != NULL){
            StackPrint.push(tmp->pRight);
        }
        if(tmp->pLeft != NULL){
            StackPrint.push(tmp->pLeft);
        }
    }
    return res;
}
int main (){
    string file = "~t->t&~w|(z&(p&(w&(p|p&q)|y&z&z)<->x&(~p|z)&~y))";
    string res = LogicInfix2Prefix(file);
    cout<<res;
    return 0;
}