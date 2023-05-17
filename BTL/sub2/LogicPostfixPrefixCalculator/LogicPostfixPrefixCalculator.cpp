#include <iostream>
#include <sstream>
#include <cstring>
#include <stack>

using namespace std;
struct NodeVal
{
    string Symb;
    bool val;
};
NodeVal InputValue(string s, bool value){
    NodeVal p;
    p.Symb = s;
    p.val = value;
    return p;
}
bool PostFixCalculator ( string s, NodeVal arr[], int sizeArr){
    stack<string> Stack;
    stack<string> Stack2;
    stack<bool> StackRes;
    int n = s.length();
    for( int i =0; i<n; i++){
        if( !(s[i] == ' ')){
           if(s[i] == '<'){
                Stack.push(s.substr(i, 3));
                i+=2;
           } else if(s[i] == '-'){
                Stack.push(s.substr(i, 2));
                i+=1;
           } else {
                Stack.push(s.substr(i, 1));
           } 
        }  
    }
    while (!Stack.empty()){
        Stack2.push(Stack.top());
        Stack.pop();
    }
    while(!Stack2.empty()){
        string tmp = Stack2.top();
        Stack2.pop();
        if(tmp == "~" || tmp == "&" || tmp == "|" || tmp == "<->" || tmp == "->"){
            if( tmp == "~"){
                bool a = StackRes.top();
                StackRes.pop();
                a = !a;
                StackRes.push(a);
            }
            else
            {
                bool a = StackRes.top();
                StackRes.pop();
                bool b = StackRes.top();
                StackRes.pop();
                bool res = true;
                if ( tmp == "&"){
                    res = a && b;
                }
                else if ( tmp == "|"){
                    res = a || b;
                }
                else if ( tmp == "<->"){
                    res = (a == b)? true: false;
                }
                else if ( tmp == "->"){
                    res = ( b == true && a == false)? false : true;
                }
                StackRes.push(res);
            }
        }
        else {
            for( int i =0; i<sizeArr; i++){
                if(arr[i].Symb == tmp ){
                    StackRes.push(arr[i].val);
                    break;
                }
            }
        }
    }
    return StackRes.top();
    
}
bool PreFixCalculator (string s, NodeVal arr[], int sizeArr){
    stack<string> Stack;
    stack<bool> StackRes;
    int n = s.length();
    for( int i =0; i<n; i++){
        if( !(s[i] == ' ')){
           if(s[i] == '<'){
                Stack.push(s.substr(i,3));
                i+=2;
           } else if(s[i] == '-'){
                Stack.push(s.substr(i,2));
                i+=1;
           } else {
                Stack.push(s.substr(i,1));
           } 
        }  
    }
    while(!Stack.empty()){
        string tmp = Stack.top();
        Stack.pop();
        if(tmp == "~" || tmp == "&" || tmp == "|" || tmp == "<->" || tmp == "->"){
            if( tmp == "~"){
                bool a = StackRes.top();
                StackRes.pop();
                a = !a;
                StackRes.push(a);
            }
            else
            {
                bool a = StackRes.top();
                StackRes.pop();
                bool b = StackRes.top();
                StackRes.pop();
                bool res = true;
                if ( tmp == "&"){
                    res = a && b;
                }
                else if ( tmp == "|"){
                    res = a || b;
                }
                else if ( tmp == "<->"){
                    res = (a == b)? true: false;
                }
                else if ( tmp == "->"){
                    res = ( a == true && b == false)? false : true;
                }
                StackRes.push(res);
            }
        }
        else {
            for( int i =0; i<sizeArr; i++){
                if(arr[i].Symb == tmp ){
                    StackRes.push(arr[i].val);
                    break;
                }
            }
        }
    }
    return StackRes.top();
 
}

string LogicPostfixPrefixCalculator(string input, string value){
    int CntTotalInValue = 0;
    stringstream s1(value);
    stringstream s2(value);  
    string temp;
    string temp2;
    while(getline(s1, temp, ' ')){
        CntTotalInValue++;
    }
    int Middle = CntTotalInValue / 2;
    int i = CntTotalInValue;
    NodeVal arr[Middle];
    while(i > Middle){
        int k = CntTotalInValue - i;
        getline(s2, temp2, ' ');
        arr[k].Symb = temp2;
        i --;
    }
    i = CntTotalInValue;
    while (i > Middle){
        int k = CntTotalInValue - i;
        getline(s2, temp2, ' ');
        arr[k].val = (temp2 == "1")? true : false;
        i --;
    }
    
    int n = input.length();
    bool res {true};
    if(isalpha(input[0]) && !isalpha(input[n-1])){
        res = PostFixCalculator(input, arr, CntTotalInValue/2);
    }
    else if ( !isalpha(input[0]) && isalpha(input[n-1])){
        res = PreFixCalculator(input, arr, CntTotalInValue/2);
    }
    return (res)? "TRUE":"FALSE";
}

int main (){
    string s = "t~tw~&zpwpp|q&&y|z&z&&xp~z|&y~&<->&|->";
    string value = "t w z p q y x 1 1 1 1 1 1 1";
    cout<<LogicPostfixPrefixCalculator(s, value);
    return 0;
}
