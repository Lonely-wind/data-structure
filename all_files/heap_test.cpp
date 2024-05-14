#include<iostream>
using namespace std;
void HeapAdJust(int a[],int k,int len){
    a[0] = a[k];
    for(int i = 2*k; i <= len; i*=2){
        if(i < len && a[i] < a[i + 1]){
            i++;
        }//寻找最大的孩子
        if(a[0] >= a[i]) break;
        else{
            a[k] = a[i];
            k = i;
        }
    }
    a[k] = a[0];
}
void BuildHeapMax(int a[], int len){
    for(int i = len / 2; i > 0; i--){
        HeapAdJust(a,i,len);
    }
}
void HeapSort(int a[],int len){
    BuildHeapMax(a,len);
    for(int i = len; i>1; i--){
        swap(a[i],a[1]);
        HeapAdJust(a,1,i - 1);
    }
}
int main(){
    int size;
    cin >> size;
    int *a = new int[size + 1];
    for(int i = 1; i < size + 1; i++){
        cin >> a[i];
    }
    HeapSort(a,size + 1);
    for(int i = 1; i < size + 1; i++){
        cout << a[i] << " ";
    }

}