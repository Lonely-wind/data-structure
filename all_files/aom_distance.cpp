#include<iostream>
#include<string>
using namespace std;
int main(){
    
    int num;
    int **array;
    int *dis;

    cin >> num;

    //对矩阵进行初始化
    array = new int*[num + 1];
    for(int i = 0; i < num + 1; i++){
        array[i] = new int[num + 1];
    }
    for(int i = 0; i < num + 1; i++){
        for(int j = 0; j < num + 1; j++){
            if(i == j){
                array[i][j] = 0;
            }
            else{
                 array[i][j] = -1;
            }
        }
    }


    dis = new int[num + 1];

    int max_ = 0;

    for(int i = 0; i < num + 1; i++){
        dis[i] = 0;//初始每一个权重都赋值为0
    }


    for(int i = 0; i < num; i++){
        int p,d;
        string temp;
        cin >> p >> d;
        if(p > max_){
            max_ = p;
        }
        getline(cin,temp);
        if(temp.empty()){
            array[0][p] = d;
            dis[p] = d;
        }
        else{
            for(int j = 0; j < temp.length() + 1; j++){
                if(temp[j] == ';'){
                    int position = temp[j - 1] - '0';
                    array[position][p] = d;
                    if(dis[position] + d > dis[p]){
                        dis[p] = dis[position] + d;
                    }
                }
            }
        }
    }


    /*for(int i = 0; i < num + 1; i++){
        for(int j = 0; j < num + 1; j++){
            cout << array[i][j] << " ";
        }
        cout << endl;
    }*/
    

    int judge = 0;

    for(int i = 0; i < max_ + 1; i++){
        if(judge == 1){
            break;
        }
        for(int j = 0; j < max_ + 1; j++){
            if(i != j &&array[i][j]!= -1 && array[j][i] != -1){
                cout << "error";
                judge = 1;
            }
            else if(i == j && array[i][j] != 0){
                cout << "error";
                judge = 1;
            }
        }
    }
    if(judge == 0){
        /*for(int i = 0; i < max_; i++){
            for(int j = 0; j < max_ + 1; j++){
                if(i != j && array[i][j] != -1){
                    int temp = dis[i] + array[i][j];
                    if(temp > dis[j]){
                        dis[j] = temp;
                    }
                }
            }
        }*/

        /*for(int i = 0; i < max_ + 1; i++){
            for(int j = 0; j < max_ + 1; j++){
                if(i != j && array[i][j] != -1){
                    break;
                }
            }
            position = i;
        }*/

        int max_1 = 0;
        for(int i = 0; i < max_ + 1; i++){
            if(dis[i] > max_1){
                max_1 = dis[i];
            }
        }
        cout << max_1;

    }
}