#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;
int main(){
    queue<int> a;
    int n;
    cin >> n;
    int *s = new int[n];
    for(int i = 0; i < n; i++){
        cin >> s[i];
    }
    sort(s,s+n);//第一次
    long sum = 0;
    int size = n - 1;
    for(int i = 0; i < n - 1; i++){
        sum += s[0] + s[1];
        s[0] = s[0] + s[1];
        for(int j = 1; j < size; j++){
            s[j] = s[j + 1];
        }
        size--;
        sort(s,s+size);
    }
    cout << sum << endl;
    //for(int i = 0; i < n; i++)cout << s[i] << " ";
}