#include<iostream>
#include<string>
using namespace std;
int main(){
    char a[10];
    cin.get(a,10);
    for(int i = 0; i < 10; i++){
        cout << a[i];
    }
}