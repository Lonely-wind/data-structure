#include<iostream>
using namespace std;
void initmatrix(int row[],int size){
    for(int i = 0; i < size; i++){
        row[i] = 0;
    }
}
int main(){
    int size;
    cin >> size;
    int **boolmatrix = (int **)malloc(sizeof(int *) * size);
    for(int i = 0; i < size; i++){
        boolmatrix[i] = (int *)malloc(sizeof(int) * size);
    }
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            cin >> boolmatrix[i][j];
        }
    }
    int row[size];
    int col[size];
    initmatrix(row,size);
    initmatrix(col,size);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            row[i] += boolmatrix[i][j];
            col[i] += boolmatrix[j][i];
        }
    }
    int rcount = 0;
    int ccount = 0;
    for(int i = 0; i < size; i++){
        if(row[i] % 2 == 1){
            rcount++;
        }
        if(col[i] % 2 == 1){
            ccount++;
        }
    }
    if(rcount == 1 && ccount == 1){
        int rtemp;
        int ctemp;
        for(int i = 0; i < size; i++){
            if(row[i] % 2 == 1){
                rtemp = i;
                break;
            }
        }
        for(int i = 0; i < size; i++){
            if(col[i] % 2 == 1){
                ctemp = i;
                break;
            }
        }
        cout << "Change bit (" << rtemp + 1 << "," << ctemp + 1 << ")" << endl;
    }
    else if(rcount == 0 && ccount == 0){
        cout << "OK";
    }
    else{
        cout << "Corrupt";
    }
    /*for(int i = 0; i < size; i++){
        if(row[i] % 2 == 0){
            int temp;
            for(int j = 0; j < size; j++){
                if(col[j] %2 == 0){
                    continue;
                }
                else{
                    temp = j;
                    break;
                }
            }
        }
        else if(row[i] % 2 == 1){
            if(col[i] % 2 == 1){
                cout << "Change bit (" << 
            }
        }
    }*/
}