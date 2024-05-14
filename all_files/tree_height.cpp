#include<iostream>
#include<string>
using namespace std;
int GetHeight(char *pre, char *in, int position){
    if(position == 0){
        return 0;
    }
    int i;
    for(i = 0; i < position; i++){
        if(in[i] == pre[0]){
            break;
        }
    }
    int k1 = GetHeight(pre + 1, in, i);
    int k2 = GetHeight(pre + 1 + i, in + 1 + i, position - i - 1);
    return max(k1,k2) + 1;
}
int main(){
    int n;
    cin >> n;
    char pre[n + 1],in[n + 1];
    cin >>  pre >> in;
    cout << GetHeight(pre,in,n);

}