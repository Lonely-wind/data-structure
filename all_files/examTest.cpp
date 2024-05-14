#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main(){
    /*int *a = new int[5];
    for(int i = 0; i < 5; i++){
        cin >> a[i];
    }
    for(int i = 0; i <  5 - 1; i++){
        int count = 0;
        for(int j = 0; j < 5 - i - 1; j++){
            if(a[j] > a[j + 1]){
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                count = 1;
            }
        }
        if(count == 0){
            break;
        }
    }
    for(int i = 0; i < 5; i++){
        cout << a[i] << " ";
    }*/
    /*int a,b;
    cin >> a >> b;
    if(a < b){
        int temp = a;
        a = b;
        b = temp;
    }
    while(b != 0){
        int temp = b;
        b = a % b;
        a = temp;
    }
    cout << a;*/
    vector<int>a;
    int size;
    cin >> size;
    for(int i = 0; i < size; i++){
        int temp;
        cin >> temp;
        a.push_back(temp);
    }
    sort(a.begin(),a.end());
    for(unsigned int i = 0; i < a.size(); i++){
        cout << a[i] << " ";
    }
}