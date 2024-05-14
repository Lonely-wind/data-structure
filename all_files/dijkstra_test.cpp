#include<iostream>
using namespace std;
int main(){
    int n,m;
    cin >> n >> m;
    int **matrix = new int*[n];
    for(int i = 0; i < n; i++){
        matrix[i] = new int[n];
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            matrix[i][j] = -1;
        }
    }
    for(int i = 0; i < m; i++){
        int s1,s2,data;
        cin >> s1 >> s2 >> data;
        matrix[s1 - 1][s2 - 1] =data;
    }
    int *dist = new int[n];
    int *path = new int[n];
    int *note = new int[n];
    for(int i = 0; i < n; i++){
        note[i] = path[i] = -1;
        dist[i] = 10000;
    }
    int position;
    cin >> position;
    note[position - 1] = 1;
    for(int i = 0; i < n; i++){
        if(matrix[position - 1][i] != -1 && i != position - 1){
            dist[i] = matrix[position - 1][i];
            path[i] = position - 1;
        }
    }
    for(int i = 0; i < n - 1; i++){
        int min_ = 100000;
        int p = -1;
        for(int j = 0; j < n; j++){
            if(note[j] == -1 && dist[j] != 10000){
                if(dist[j] < min_){
                    min_ = dist[j];
                    p = j;
                }
            }
        }
        if(p == -1){
            break;
        }
        note[p] = 1;
        for(int k = 0; k < n; k++){
            if(note[k] == -1){
                if(matrix[p][k] != -1 && dist[k] == 10000){
                    dist[k] = dist[p] + matrix[p][k];
                    path[k] = p;
                }
                else if(matrix[p][k] != -1){
                    if(dist[k] > dist[p] + matrix[p][k]){
                        dist[k] = dist[p] + matrix[p][k];
                        path[k] = p;
                    }
                }
            }
        }
    }
    for(int i = 0; i < n; i++){
        cout << dist[i] << " ";
    }
}