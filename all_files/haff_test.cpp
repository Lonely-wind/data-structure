#include<iostream>
using namespace std;
struct  HF
{
    int data;
    int parent,lchild,rchild;
};

void find_min(HF *hf,int n, int &s1, int &s2){
    int min_ = 0;
    for(int i = 0; i < n; i++){
        if(hf[i].parent == 0){
            min_ = i;
            break;
        }
    }
    for(int i = 0; i < n; i++){
        if(hf[i].parent == 0 && hf[i].data < hf[min_].data){
            min_ = i;
        }
    }
    s1 = min_;
    int min_2 = 0;
    for(int i = 0; i < n; i++){
        if(hf[i].parent == 0 && i != s1){
            min_2 = i;
            break;
        }
    }
    for(int i = 0; i < n; i++){
        if(hf[i].parent == 0 &&  i!= s1 && hf[i].data < hf[min_2].data ){
            min_2 = i;
        }
    }
    s2 = min_2;
}
int main(){
    int size;;
    cin >> size;
    HF *hf = new HF[2*size + 1];
    for(int i = 0; i < 2*size + 1; i++){
        hf[i].parent = hf[i].data = hf[i].lchild = hf[i].rchild = 0;
    }
    for(int i = 0; i < size; i++){
        int temp;
        cin >> temp;
        hf[i].data = temp;
    }
    for(int i = size; i < 2*size + 1; i++){
        int s1,s2;
        find_min(hf,i,s1,s2);
        hf[i].data = hf[s1].data + hf[s2].data;
        hf[i].lchild = s1;
        hf[i].rchild = s2;
        hf[s1].parent = i;
        hf[s2].parent = i;
    }
    long sum = 0;
    for(int i = size; i < 2*size - 1; i++){
        sum += hf[i].data;
    }
    cout << sum;
}