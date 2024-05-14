#include<iostream>
#include<string.h>
using namespace std;
int position = 0;
struct tree{
    int data;
    tree* leftchi;
    tree* rightchi;

};
int visit(tree *a){
    return a->data;
}
void displayTree(tree *root){
    if(root != NULL){
        cout << root->data << " ";
        displayTree(root->leftchi);
        displayTree(root->rightchi);
    }
}
void preDisplay(tree *root){
    if(root != NULL){
        cout << root->data;
    }
}
void pre(char *tree, int pos, string input){
    if(pos <= input.length()){
        tree[pos] = input[position];
        position++;
        pre(tree,2*pos,input);//向左
        pre(tree,2*pos + 1,input);
    }
}
void display(char *tree, int pos, int length){
    if(pos <= length){
        display(tree, pos*2, length);
        cout << tree[pos];
        display(tree, pos*2 + 1, length);
    }
}//建立一个完全二叉树
int main(){
    string input;
    cin >> input;
    char *tree = new char[input.length() + 1];//用来盛放完全二叉树
    int pos = 1;
    pre(tree, pos, input);
    int position1 = input.length();
    display(tree,pos, position1);
}