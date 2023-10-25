#include<iostream>
using namespace std;
int main(){
    int n,m;
    cin >> n >> m;//矩阵大小
    int **rollmatrix = (int **)malloc(sizeof(int *) * n);
    for(int i = 0; i < n; i++){
        rollmatrix[i] = (int *)malloc(sizeof(int) * m);
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> rollmatrix[i][j];
        }
    }
    /*for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout << rollmatrix[i][j];
        }
        cout << endl;
    }
    cout << endl;*/
    int up = 0, left = 0, down = n - 1, right = m - 1;//定义左右，上下边界
    int judge = 0;//判断是顺时针还是逆时针
    int k = 0;
    int num = 0;//已输出的元素个数
    int firstjudge = 0;
    while(up <= down && left <= right){
        //顺时针移动
        if(judge % 2 == 0){
            /*if(firstjudge == 0){
                firstjudge == 1;
            }
            else{
                cout << rollmatrix[up][left];
                
            }*/
            //向右移动
            for(k = left; k <= right; k++){
                cout << rollmatrix[up][k];
                num++;
                if(num < n * m){
                    cout << " ";
                }
            }
            up++;
            if(num == n*m){
                break;
            }
            //向下移动
            for(k = up; k <= down; k++){
                cout << rollmatrix[k][right];
                num++;
                if(num < n * m){
                    cout << " ";
                }
            }
            right--;
            if(num == n*m){
                break;
            }
            //向左移动
            for(k = right; k >= left; k--){
                cout << rollmatrix[down][k];
                num++;
                if(num < n * m){
                    cout << " ";
                }
            }
            down--;
            if(num == n*m){
                break;
            }
            //向上移动
            for(k = down; k >= up; k--){
                cout << rollmatrix[k][left];
                num++;
                if(num < n * m){
                    cout << " ";
                }
            }
            left++;
            if(num == n * m){
                break;
            }
            judge++;//下一步采取逆时针操作
        }
        //逆时针移动
        else if(judge % 2 == 1){
            /*cout << rollmatrix[up][left] << " ";
            up++;*/
            //向下移动
            for(k = up; k <= down; k++){
                cout << rollmatrix[k][left];
                num++;
                if(num < n * m){
                    cout << " ";
                }
            }
            left++;
            if(num == n*m){
                break;
            }
            //向右移动
            for(k = left; k <= right; k++){
                cout << rollmatrix[down][k];
                num++;
                if(num < n * m){
                    cout << " ";
                }
            }
            down--;
            if(num == n*m){
                break;
            }
            //向上移动
            for(k = down; k >= up; k--){
                cout << rollmatrix[k][right];
                num++;
                if(num < n * m){
                    cout << " ";
                }
            }
            right--;;
            if(num == n * m){
                break;
            }
            //向左移动
            for(k = right; k >= left; k--){
                cout << rollmatrix[up][k];
                num++;
                if(num < n * m){
                    cout << " ";
                }
            }
            up++;
            if(num == n * m){
                break;
            }
            judge++;
        }
    }
}