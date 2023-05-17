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
            {  // specia; open bracklet operator
                while(StackOperator.top() != '('){
                    Tree t = MakeNewNode(StackOperator.top());
                    t->pRight = StackNode.top();
                    StackNode.pop();
                    t->pLeft = StackNode.top();
                    StackNode.pop();
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
                while ( ComparisonChar1AndChar2(use[i], StackOperator.top()) && StackOperator.top() != '('){
                    Tree tmp = MakeNewNode(StackOperator.top());
                    tmp->pRight = StackNode.top(); StackNode.pop();
                    tmp->pLeft = StackNode.top(); StackNode.pop();
                    StackNode.push(tmp);
                    StackOperator.pop();
                }
                StackOperator.push(use[i]);
            }       
        }
    }

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