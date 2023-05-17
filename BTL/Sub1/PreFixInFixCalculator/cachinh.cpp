#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;
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
int main(){
    string s ="  + * * / 23 40 21 ^ 27 6 40 ";  // input nhu cc, cach nhieu vcl
    cout<<PostfixPrefixCalculator(s)<<endl;
    return 0;
}
  