#include<iostream>
using namespace std;
int main(){
    int nsize;
    int num;
    cin >> nsize >> num;
    int **data = new int*[nsize];
    for(int i = 0; i < nsize; i++){
        data[i] = new int[nsize];
    }
    for(int i = 0; i < nsize; i++){
        for(int j = 0; j < nsize; j++){
            if(i == j){
                data[i][j] = 0;
            }
            else{
                data[i][j] = -1;
            }
        }
    }
    if(num == 0){
        for(int i = 0; i < nsize; i++){
            for(int j = 0; j < nsize; j++){
                if(j == nsize - 1){
                    cout << data[i][j];
                }
                else{
                    cout << data[i][j] << " ";
                }
            }
            cout << endl;
        }
    }
    else{
        for(int i = 0; i < num; i++){
            int x,y,temp;
            cin >> x >> y >> temp;
            data[x][y] = temp;
        }
        for(int i = 0; i < nsize; i++){
            for(int j = 0; j < nsize; j++){
                for(int k = 0; k < nsize; k++){
                    if((data[j][i] != -1 && data[i][k] != -1) && data[j][k] == -1 ){
                        data[j][k] = data[j][i] + data[i][k];
                    }
                    else{
                        if(data[j][i] != -1 && data[i][k] != -1){
                            if(data[j][i] + data[i][k] < data[j][k]){
                                data[j][k] = data[j][i] + data[i][k];
                            }
                        }
                    }
                }
            }
        }
        for(int i = 0; i < nsize; i++){
            for(int j = 0; j < nsize; j++){
                if(j == nsize - 1){
                    cout << data[i][j];
                }
                else{
                    cout << data[i][j] << " ";
                }
            }
            cout << endl;
        }
    }
}