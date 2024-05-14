#include<iostream>
#include<math.h>
using namespace std;
int find_(int *un, int x1){
    if(un[x1] == x1){
        return x1;
    }
    return find_(un,un[x1]);
}
int main(){
    int size;
    cin >> size;
    int size2;
    cin >> size2;
    int edges[size2][2];
    for(int i = 0; i < size2; i++){
        cin >> edges[i][0] >> edges[i][1];
    }
    int un[size];
    for(int i = 0; i < size; i++){
        un[i] = i;
    }
    int judge = 0;
    for(int i = 0; i < size2; i++){
        int x = find_(un,edges[i][0]);
        int y = find_(un,edges[i][1]);
        if(x == y){
            judge = 1;
            break;
        }
        else{
            un[find_(un,edges[i][0])] = find_(un,edges[i][1]);
        }
    }
    if(judge == 1){
        cout << "yes";
    }
    else{
        cout << "no";
    }
    return 0;
}