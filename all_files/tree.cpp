#include<iostream>
using namespace std;
int main(){
    int size;
    cin >> size;
    int *stacktree = new int[size + 1];
    stacktree[0] = size;
    for(int i = 1; i < size + 1; i++){
        cin >> stacktree[i];
    }
    int judgemax = 1;
    for(int i = 1; i < size + 1; i++){
        if(2*i < size + 1){
            if(stacktree[2*i] <= stacktree[i]){
                continue;
            }
            else{
                judgemax = 0;
                break; 
            }
        }
        if(2*i + 1 < size + 1){
            if(stacktree[2*i + 1] <= stacktree[i]){
                continue;
            }
            else{
                judgemax = 0;
                break; 
            }
        }
    }
    int judgemin = 1;
    for(int i = 1; i < size + 1; i++){
        if(2*i < size + 1){
            if(stacktree[2*i] >= stacktree[i]){
                continue;
            }
            else{
                judgemin = 0;
                break; 
            }
        }
        if(2*i + 1 < size + 1){
            if(stacktree[2*i + 1] >= stacktree[i]){
                continue;
            }
            else{
                judgemin = 0;
                break; 
            }
        }
    }
    if(judgemax == 1 && judgemin == 0){
        cout << "max ";
        for(int i = size / 2; i >= 1; --i){//遍历树
            int t = stacktree[i];//记录此时的大小
            int c = 2 * i;//找左儿子
            while(c <= size){
                if(c < size && stacktree[c] >= stacktree[c + 1]){
                    c++;//找出子结点中较小的那个
                }
                if(t > stacktree[c]){
                    stacktree[c / 2] = stacktree[c];
                    c *= 2;//继续向下检查
                }
                else{
                    break;
                }
            }
            //最后赋值
            stacktree[c / 2] = t;
        }
        for(int i = 1; i < size; i++){
            cout << stacktree[i] << " ";
        }
        cout << stacktree[size];
    }
    if(judgemin == 1 && judgemax == 0){
        cout << "min ";
        for(int i = size / 2; i >= 1; --i){//遍历树
            int t = stacktree[i];//记录此时的大小
            int c = 2 * i;//找左儿子
            while(c <= size){
                if(c < size && stacktree[c] <= stacktree[c + 1]){
                    c++;//找出子结点中较大的那个
                }
                if(t < stacktree[c]){
                    stacktree[c / 2] = stacktree[c];
                    c *= 2;//继续向下检查
                }
                else{
                    break;
                }
            }
            //最后赋值
            stacktree[c / 2] = t;
        }
        for(int i = 1; i < size; i++){
            cout << stacktree[i] << " ";
        }
        cout << stacktree[size];
    }
    if(judgemax == 1 && judgemin == 1){
        cout << "max min";
    }
    if(judgemax == 0 && judgemin == 0){
        for(int i = size / 2; i >= 1; --i){//遍历树
            int t = stacktree[i];//记录此时的大小
            int c = 2 * i;//找左儿子
            while(c <= size){
                if(c < size && stacktree[c] < stacktree[c + 1]){
                    c++;//找出子结点中较小的那个
                }
                if(t < stacktree[c]){
                    stacktree[c / 2] = stacktree[c];
                    c *= 2;//继续向下检查
                }
                else{
                    break;
                }
            }
            //最后赋值
            stacktree[c / 2] = t;
        }
        for(int i = 1; i < size; i++){
            cout << stacktree[i] << " ";
        }
        cout << stacktree[size];
    }
}