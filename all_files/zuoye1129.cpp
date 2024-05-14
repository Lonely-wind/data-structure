#include<iostream>
using namespace std;
int find(int t, int *s){
    if(t == s[t]){
        return t;
    }
    else{
        return find(s[t],s);
    }
}
int main(){
    int num;
    int dis;
    cin >> num >> dis;
    int *un = new int[num];
    for(int i = 0; i < num; i++){
        un[i] = i;
    }
    for(int i = 0; i < dis; i++){
        int temp1,temp2;
        cin >> temp1 >> temp2;
        if(find(temp1,un) == find(temp2,un)){
            continue;
        }
        else{
            un[find(temp1,un)] = find(temp2,un);
        }
    }
    int size;
    cin >> size;
    for(int i = 0; i < size; i++){
        int temp1,temp2;
        cin >> temp1 >> temp2;
        if(find(temp1,un) == find(temp2,un)){cout << "true" << endl;}
        else{cout << "false" << endl;}
    }
    return 0;
}