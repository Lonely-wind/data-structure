#include<iostream>
#include<algorithm>
using namespace std;
int find_(int *pre, int data){
    int p = data;
    while(pre[p] != p){
        p = pre[p];
    }
    return p;
}
int main(){
    int size;
    cin >> size;
    int *pre = new int[size];
    for(int i = 0; i < size; i++){
        pre[i] = i;
    }
    pre[5] = 4;
    pre[4] = 3;
    cout << find_(pre,5);
    /*while(pre[p] != p){
        p = pre[p];
        cout << p <<" ";
    }*/
    //cout << p <<" ";
}