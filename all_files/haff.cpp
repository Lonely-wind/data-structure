#include<iostream>
using namespace std;
struct tree{
    int data;
    int parent,lchild,rchildl;
};
void findmin(tree *HT, int n, int &s1, int &s2){
    int min1 = 0;
    for(int i = 0; i < n; i++){
        if(HT[i].parent == 0){
            min1 = i;
            break;//找出第一个最小的点
        }
    }
    for(int i = 0; i < n; i++){
        if(HT[i].parent == 0 && HT[i].data < HT[min1].data){
            min1 = i;//更新min1的值
        }
    }
    s1 = min1;
    int min2 = 0;
    for(int i = 0; i < n; i++){
        if(HT[i].parent == 0 && i != s1){
            min2 = i;
            break;
        }
    }
    for(int i = 0; i < n; i++){
        if(HT[i].parent == 0 && i != s1 && HT[i].data < HT[min2].data){
            min2 = i;
        }
    }
    s2 = min2;
}
int main(){
    int size;
    cin >> size;
    tree *HT = new tree[2*size - 1];
    for(int i = 0; i < 2*size - 1; i++){
        HT[i].data = 0;
        HT[i].lchild = 0;
        HT[i].rchildl = 0;
        HT[i].parent = 0;
    }
    for(int i = 0; i < size; i++){
        cin >> HT[i].data;
    }
    int s1,s2;
    for(int i = size; i < 2*size - 1; i++){
        findmin(HT,i,s1,s2);
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchildl = s2;
        HT[i].data = HT[s1].data + HT[s2].data;
    }
    long sum = 0;
    for(int i = size; i < 2*size - 1; i++){
        sum += HT[i].data;
    }
    cout << sum;
}