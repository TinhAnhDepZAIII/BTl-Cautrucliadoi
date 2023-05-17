#include "MyLib.h"


/* * * Implemenation of Infix to PostFix with numbers * * */
bool ComparisonChar1AndChar2Ver1( char a, char b){
    int charA = ((a == '+' || a == '-') ? 1 : ((a == '*' || a == '/') ? 2 : 3));
    int charB = ((b == '+' || b == '-') ? 1 : ((b == '*' || b == '/') ? 2 : 3));
    if( charA <= charB){
        return true;
    }
    return false;
}
Tree1 MakeNewNode1 (char x)
{
    Tree1 p = new Node1;
    p->data = x;
    p->pLeft = p->pRight = NULL;
    return p;
}
Tree1 MakeNewNode1String (string x)
{
    Tree1 p = new Node1;
    p->data = x;
    p->pLeft = p->pRight = NULL;
    return p;
}
string Infix2Postfix (string s){
    
    stack<Tree1> StackNode;
    stack<char> StackOperator;
    stack<Tree1> StackPrint;
    
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
                    Tree1 t = MakeNewNode1(StackOperator.top());
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
                Tree1 tmp = MakeNewNode1String(temper);
                StackNode.push(tmp);
            }
            else
            {
                if ( use[i] == '.') throw "Error: Syntax Error";
                bool check = false;
                while ( ComparisonChar1AndChar2Ver1(use[i], StackOperator.top()) && StackOperator.top() != '('){
                    Tree1 tmp = MakeNewNode1(StackOperator.top());

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

    string res = "";
    Tree1 temp = StackNode.top();
    while(true){
        if(temp != nullptr){
            StackPrint.push(temp);
            temp= temp->pLeft;
        }else{
            if(StackPrint.empty()) break;
            temp = StackPrint.top()->pRight;
            if ( temp == nullptr){
                Tree1 last  = nullptr;
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
/* * * End implementation of Infix to PostFix wit numbers * * */

/* * * Implemenation of Infix to PreFix with numbers * * */
bool ComparisonChar1AndChar2Ver2( char a, char b){
    int charA = ((a == '+' || a == '-') ? 1 : ((a == '*' || a == '/') ? 2 : 3));
    int charB = ((b == '+' || b == '-') ? 1 : ((b == '*' || b == '/') ? 2 : 3));
    if( charA <= charB){
        return true;
    }
    return false;
}
Tree2 MakeNewNode2 (char x)
{
    Tree2 p = new Node2;
    p->data = x;
    p->pLeft = p->pRight = NULL;
    return p;
}
Tree2 MakeNewNode2String (string x)
{
    Tree2 p = new Node2;
    p->data = x;
    p->pLeft = p->pRight = NULL;
    return p;
}
string Infix2Prefix (string s){
    
    stack<Tree2> StackNode;
    stack<char> StackOperator;
    stack<Tree2> StackPrint;
    
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
                    Tree2 t = MakeNewNode2(StackOperator.top());
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
                Tree2 tmp = MakeNewNode2String(temper);
                StackNode.push(tmp);
            }
            else
            {
                if ( use[i] == '.') throw "Error: Syntax Error";
                bool check = false;
                while ( ComparisonChar1AndChar2Ver2(use[i], StackOperator.top()) && StackOperator.top() != '('){
                    Tree2 tmp = MakeNewNode2(StackOperator.top());

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

    // Tree2 to prefix
    string res ="";
    Tree2 tmp = StackNode.top();
    StackPrint.push(tmp);
    while(!StackPrint.empty()){
        Tree2 tmp = StackPrint.top();
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
/* * * End implementation of Infix to PreFix with numbers * * */


/* * * Evaluation PostFix or PreFix * * */
string PostfixPrefixCalculator(string s){
    double a;
    stringstream ss(s);
    string tmp;
    ss>>tmp;
    if(isdigit(tmp[0]) ){
        a = PostFixCalculator(s);
    }
    else {
        a = PreFixCalculator(s);
    }

    string res {};
    stringstream stream;
    stream << fixed <<setprecision(4)<<a;
    res = stream.str();
    while (res.back() == '0') {
        res.pop_back();
    }
    while( res.back() == '.'){res.pop_back();}
    return res;
}
double PostFixCalculator(string k){
    
    stack<string> Stack;
    stack<string> Stack2;
    stack<string> StackRes;
    stringstream ss(k);
    string tmp;
    while ( ss>>tmp){
        Stack.push(tmp);
    }
    while( !Stack.empty()){
        Stack2.push(Stack.top());
        Stack.pop();
    }
    while (!Stack2.empty()){
        string tmp = Stack2.top();
        Stack2.pop();
        if(tmp == "+" || tmp == "-" || tmp == "*" || tmp == "/" || tmp == "^"){
            double a = stod(StackRes.top());
            StackRes.pop();
            double b = stod(StackRes.top());
            StackRes.pop();
            double c =0;
            if(tmp == "+"){
                c = b + a;
            }
            else if(tmp == "-"){
                c = b - a;
            }
            else if(tmp == "*"){
                c = b * a;
            }
            else if(tmp == "/"){
                c = b / a;
                
            }else if (tmp == "^"){
                c = pow(b,a);
            }
            ostringstream oss;
            oss.precision(18);
            oss << c;
            string s = oss.str();
            StackRes.push(s);
        }
        else{
            StackRes.push(tmp);
        }
    }
    double res = stod(StackRes.top());
    StackRes.pop();
    return res;
}
double PreFixCalculator(string s){
    stack<string> Stack;
    stack<string> StackRes;
    stringstream ss(s);
    string tmp;
    while( ss>>tmp){
        Stack.push(tmp);
    }  
    while(!Stack.empty()){
        string tmp = Stack.top();
        Stack.pop();
        if(tmp == "+" || tmp == "-" || tmp == "*" || tmp == "/" || tmp == "^"){
            double a = stod(StackRes.top());
            StackRes.pop();
            double b = stod(StackRes.top());
            StackRes.pop(); 
            double c =0;
            if(tmp == "+"){
                c = a + b;
            }
            else if(tmp == "-"){
                c = a - b;
            }
            else if(tmp == "*"){
                c = a * b;
            }
            else if(tmp == "/"){
                c = a / b;
            }
            else if(tmp == "^"){
                c = pow(a,b);
            }
            ostringstream oss;
            oss.precision(18);
            oss << c;
            string s = oss.str();
            StackRes.push(s);
        }
        else {
            StackRes.push(tmp);
        }
        
    }
    double res = stod(StackRes.top());
    StackRes.pop();
    return res;
}
/* * * End Evaluation PostFix or PreFix * * */