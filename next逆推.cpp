#include<iostream>
#include<cstdio>
#include<string.h>
using namespace std;
int *getNext(int *a,int size){
    int j = 0;
    int k = -1;
    int *next = new int[size];
    next[j] = k;
    while(j < size - 1){
        if(k == -1 || a[j] == a[k]){
            j++;
            k++;
            next[j] = k;
        }
        else{
            k = next[k];
        }
    }
    return next;
}
int main(){
    int head;
    int tail;
    int size;
    cin >> head >> tail >> size;
    int *Next = new int[size];
    for(int i = 0; i < size; i++){
        cin >> Next[i];
    }
    int *s = new int[size];
    s[0] = head;
    s[size - 1] = tail;
    for(int i = 2; i < size; i++){
        if(Next[i] - Next[i - 1] > 1){
            cout << "ERROR";
            return 0;
        }
        else if(Next[i] == 0){
            if(head == 1){
                s[i - 1] = 0;
            }
            else{
                s[i - 1] = 1;
            }
        }
        else{
            s[i - 1] = s[(Next[i] - 0) - 1];

        }
    }
    int *judge = getNext(s,size);//求所得数组的next数组
    for(int i = 0; i < size; i++){
        if(judge[i] != Next[i]){
            cout << "ERROR";
            return 0;
        }
        else{
            continue;
        }
    }
    for(int i = 0; i < size; i++){
        cout << s[i];
    }
}