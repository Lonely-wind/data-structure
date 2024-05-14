#include<iostream>
#include<string>
using namespace std;
int *getNext(string a, int size){
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
int kmp(string s1, string s2){
    int n = (int)s1.size();
    int ans = -1;
    int i = 0;
    int j = 0;
    int *next = getNext(s2,(int)s2.size());
    while(i < (int)s1.size()){
        if(j == -1 || s1[i] == s2[j]){
            j++;
            i++;
        }
        else{
            j = next[j];
        }
        if(j == (int)s2.size()){
            ans = i - (int)s2.size();
            break;
        }
    }
    return ans;
}
int main(){
    /*int head,tail;
    int size;
    cin >> head >> tail >> size;
    int *next = new int[size];
    for(int i = 0; i < size; i++){
        cin >> next[i];
    }
    int *judge = new int[size];
    judge[0] = head;
    judge[size - 1] = tail;
    for(int i = 1; i < size - 1; i++){
        if(next[i + 1] - next[i] > 1){
            cout << "ERROR";
            return 0;
        }
        if(next[i + 1] - 1 == -1){
            if(head == 1){
                judge[i] = 0;
            }
            else{
                judge[i] = 1;
            }
        }
        else{
            judge[i] = judge[next[i + 1] - 1];
        }
    }
    int *judge2;
    judge2 = getNext(judge,size);
    /*for(int i = 0; i < size; i++){
        cout << judge2[i] << " ";
    }*/
    /*for(int i = 0; i < size; i++){
        if(judge2[i] != next[i]){
            cout << "ERROR";
            return 0;
        }
    }
    for(int i = 0; i < size; i++){
        cout << judge[i];
    }*/
    string a,b;
    cin >> a >> b;
    cout << kmp(a,b);
}