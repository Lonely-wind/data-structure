#include<iostream>
#include<string.h>
using namespace std;
int *buildNext(string t){
    int *Next = new int[t[0]];
    int j = 0;
    int k = -1;
    Next[j] = k;
    while(j < t[0] - 1){
        if(k == -1 || t[j] == t[k]){
            Next[++j] = ++k;
        }
        else{
            k = Next[k];
        }
    }
    return Next;
}
int kmp(string a,string b){
    int i = 0;
    int j = 0;
    int alen = a.length();
    int blen = b.length();
    int *next = new int[b.length()];
    next = buildNext(b);
    while(i < alen && j < blen){
        if(j == -1 || a[i] == b[j]){
            i++;
            j++;
        }
        else{
            j = next[j];
        }
    }
    if(j == blen){
        return i - j;
    }
    else{
        return -1;
    }
}
int main(){
    string a;
    string b;
    cin >> a >> b;
    int k = kmp(a,b);
    if(k != -1){
        cout << k << endl;
    }
    else{
        cout << "no";
    }
}