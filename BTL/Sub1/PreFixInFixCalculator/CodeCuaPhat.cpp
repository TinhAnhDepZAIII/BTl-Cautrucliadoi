#include <iostream>
#include <string>
#include <stack>
#include <sstream>

using namespace std;
struct Node {
    string data;
    Node* parent;
    Node* left;
    Node* right;
};

Node* createNode(string s){
    Node* newNode = new Node;
    newNode->data = s;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

bool isOperator(char c){
    return (c == '+') || (c == '-') || (c == '*') || (c == '/');
}

bool isNumber(string s){
    for(unsigned int i = 0; i < s.size(); i++){
        if(s[i] < '0' || s[i] > '9')
            return false;
    }
    return true;
}

//true nếu đã remove, false nếu ko thể remove thêm nữa
bool removeOuterParenthesis(string& str){
    
    stack<char> paren;
    if (str.length() >= 2 && str.front() == '(' && str.back() == ')') {
        for(int i = 1; i < str.length()-1; i++){
            if(str[i] == ' ') continue;
            if(str[i]== ')' && paren.empty())
                return false;
            if(str[i] == '(')
                paren.push('(');
            if(str[i] == ')')
                paren.pop();
        }
        str = str.substr(1,str.length() - 2);
        str = str.substr(1,str.length());
        str = str.substr(0, str.length()-1);

        return true;
    }
    
    
    return false;
}

Node* buildNumericTree(string infix){
    infix = infix.substr(1,infix.length());
    infix = infix.substr(0, infix.length()-1);
    stack<char> paren;
    while(removeOuterParenthesis(infix)){};
    Node* root = new Node;
    if(isNumber(infix)){
        root->data = infix;
        root->left = root->right = nullptr;
        return root;
    }
    int breakpoint = 0;
    for(int i = infix.size() - 1; i >= 0; i--){
        if(infix[i] ==' ') continue;
        if(infix[i] == ')')
            paren.push(')');
        if(infix[i] == '(')
            paren.pop();
        if((infix[i] == '+' || infix[i] == '-') && paren.empty()){
            root->data = infix[i];
            breakpoint = i;
            break;
        }
    }
    if(breakpoint != 0){
        root->left = buildNumericTree(infix.substr(0,breakpoint-1));
        root->right = buildNumericTree(infix.substr(breakpoint + 2));
        root->left->parent = root->right->parent = root;
    }
    else{
        for(int i = infix.size() - 1; i >= 0; i--){
            if(infix[i] == ')')
                paren.push(')');
            if(infix[i] == '(')
                paren.pop();
            if((infix[i] == '*' || infix[i] == '/') && paren.empty()){
                root->data = infix[i];
                breakpoint = i;
                break;
            }
        }
        if(breakpoint != 0) {
            root->left = buildNumericTree(infix.substr(0, breakpoint-1));
            root->right = buildNumericTree(infix.substr(breakpoint + 2));
            root->left->parent = root->right->parent = root;
        }
        else{
            for(int i = infix.size() - 1; i >= 0; i--){
                if(infix[i] == ')')
                    paren.push(')');
                if(infix[i] == '(')
                    paren.pop();
                if((infix[i] == '^' ) && paren.empty()){
                    root->data = infix[i];
                    breakpoint = i;
                    break;
                }
            }
            root->left = buildNumericTree(infix.substr(0, breakpoint-1));
            root->right = buildNumericTree(infix.substr(breakpoint + 2));
            root->left->parent = root->right->parent = root;
        }
    }
    root->parent = nullptr;
    return root;
}

void deleteTree(Node* root) {
    if (root == nullptr) {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

string Infix2Postfix(string infix){
    Node* root = buildNumericTree(infix);
    Node* temp;
    string postfix;
    stack<Node*> ns; //ns = node stack;
    ns.push(root);
    while(!ns.empty()){
        temp = ns.top();
        if(temp->right == nullptr && temp->left == nullptr) {
            if(temp->parent != nullptr) {
                if (temp->parent->right == temp)
                    temp->parent->right = nullptr;
                if (temp->parent->left == temp)
                    temp->parent->left = nullptr;
            }
            ns.pop();
            postfix = postfix + temp->data + ' ';
        }
        else{
            if(temp->right != nullptr)
                ns.push(temp->right);
            if(temp->left != nullptr)
                ns.push(temp->left);
        }
    }
    deleteTree(root);
    return postfix.substr(0,postfix.length()-1);
}

int main(){
    string s =" 24 / ( 6 + 2 ) - 3 ";  
    cout<<Infix2Postfix(s)<<endl;
    return 0;
}