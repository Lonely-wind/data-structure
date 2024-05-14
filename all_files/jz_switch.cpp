#include<iostream>
#include<stack>
using namespace std;
int main(){
    int n1,n2;
    cin >> n1 >> n2;
    stack<char> a;
    //判断共有几位数
    int size;
    if(n1 >= 0){
        while(1){
            int temp1 = n1 % n2;
            if(temp1 >= 10){
                a.push(temp1 - 10 + 65);
            }
            else{
                a.push(temp1 + 48);
            }
            if(n1 < n2 && n1 / n2 == 0){
                break;
            }
            n1 = n1 / n2;
        }
    }
    else if(n1 < 0){
        n1 = abs(n1);
        while(1){
            int temp1 = n1 % n2;
            if(temp1 >= 10){
                a.push(temp1 - 10 + 65);
            }
            else{
                a.push(temp1 + 48);
            }
            if(n1 < n2 && n1 / n2 == 0){
                break;
            }
            n1 = n1 / n2;
        }
        a.push('-');
    }
    while(!a.empty()){
        cout << a.top();
        a.pop();
    }
}