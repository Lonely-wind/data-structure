#include<iostream>
using namespace std;
int **matrixMultiply(int **&matrix1, int **&matrix2,int row1,int col1,int row2,int col2){
    int **finmatrix = (int **)malloc(sizeof(int *) * row1);
    for(int i = 0; i < row1; i++){
        finmatrix[i] = (int *)malloc(sizeof(int) * col2);
    }
    for(int i = 0; i < row1; i++){
        for(int k = 0; k < col1; k++){
            for(int j = 0; j < col2; j++){
                finmatrix[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return finmatrix;
}
int main(){
    int **matrix1;//第一个矩阵
    int **matrix2;//第二个矩阵
    int row1,col1,count1;
    cin >> row1 >> col1 >> count1;
    matrix1 = (int **)malloc(sizeof(int*) * (row1));
    for(int i = 0; i < row1; i++){
        matrix1[i] = (int *)malloc(sizeof(int) * (col1));
    }
    for(int i = 0; i < row1; i++){
        for(int j = 0; j < col1; j++){
            matrix1[i][j] = 0;
        }
    }
    for(int i = 0; i < count1; i++){
        int row;
        int col;
        int data;
        cin >> row >> col >> data;
        matrix1[row - 1][col - 1] = data;
    }
    /*for(int i = 0; i < row1; i++){
        for(int j = 0; j < col1; j++){
            cout << matrix1[i][j];
        }
        cout << endl;
    }*/
    cout << endl;
    int row2,col2,count2;
    cin >> row2 >> col2 >> count2;
    matrix2 = (int **)malloc(sizeof(int*) * (row2));
    for(int i = 0; i < row2; i++){
        matrix2[i] = (int *)malloc(sizeof(int) * (col2));
    }
    for(int i = 0; i < row2; i++){
        for(int j = 0; j < col2; j++){
            matrix2[i][j] = 0;
        }
    }
    for(int i = 0; i < count2; i++){
        int row;
        int col;
        int data;
        cin >> row >> col >> data;
        matrix2[row - 1][col - 1] = data;
    }
    if(row1 == col2 && row2 == col1){
        int **finmatrix = (int **)malloc(sizeof(int *) * row1);
        for(int i = 0; i < row1; i++){
            finmatrix[i] = (int *)malloc(sizeof(int) * col2);
        }
        for(int i = 0; i < row1; i++){
            for(int j = 0; j < col2; j++){
                finmatrix[i][j] = 0;
                for(int k = 0; k < col1; k++){
                    finmatrix[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
        }
        int judge = 0;
        for(int i = 0; i < row1; i++){
            for(int j = 0; j < col2; j++){
                if(finmatrix[i][j] != 0){
                    cout << i+1 << " " << j+1 << " " << finmatrix[i][j] << endl;
                    judge = 1;
                }
            }
        }
        if(judge == 0){
            cout << "The answer is a Zero Matrix" ;
        }
    }
    else{
        cout << "ERROR" << endl;
    }
}