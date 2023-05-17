#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <cmath>
using namespace std;
double stringToDouble(string s) {
    double result = 0.0;
    int decimalPosition = s.size();
    bool decimalFound = false;
    int power = 1;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '.') {
            decimalPosition = i;
            decimalFound = true;
        } else if (s[i] >= '0' && s[i] <= '9') {
            result = result * 10 + (s[i] - '0');
            if (decimalFound) {
                power *= 10;
            }
        } else {
            // Handle invalid characters
            return 0.0;
        }
    }
    if (decimalFound) {
        result /= power;
    }
    return result;
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
            double a = stringToDouble(StackRes.top());
            StackRes.pop();
            double b = stringToDouble(StackRes.top());
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
            oss.precision(11);
            oss << c;
            string s = oss.str();
            StackRes.push(s);
        }
        else {
            StackRes.push(tmp);
        }
        
    }
    double res = stod(StackRes.top());
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
            double a = stringToDouble(StackRes.top());
            StackRes.pop();
            double b = stringToDouble(StackRes.top());
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
            oss.precision(11);
            oss << c;
            string s = oss.str();
            StackRes.push(s);
        }
        else{
            StackRes.push(tmp);
        }
    }
    double res = stod(StackRes.top());
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

    double b = round(a * 10000)/10000;
    string res = to_string(b);
    while (res.back() == '0') {
        res.pop_back();
    }
    if (res.back() == '.') {
        res.pop_back();
    }
    size_t MarkDot = res.find('.');
    int ResL = res.length();
    if( MarkDot == string::npos){
        return res;
    }else {
        if( ResL - MarkDot>4){
            res = res.substr(0, MarkDot+5);
        }else if( ResL - MarkDot == 4){
            res = res.substr(0, MarkDot+4);
        }else if (ResL - MarkDot == 3){
            res = res.substr(0, MarkDot+3);
        }else if (ResL - MarkDot == 2){
            res = res.substr(0, MarkDot+2);
        }else if( ResL - MarkDot == 1){
            res = res.substr(0, MarkDot+1);
        }
    }
    return res;
}
int main(){
    string s ="  25496 100000 /";  // input nhu cc, cach nhieu vcl
    cout<<PostfixPrefixCalculator(s)<<endl;
    return 0;
}
  