#include<iostream>
#include<algorithm>
using namespace std;
int *b = new int[100];
void select_sort(int a[],int n){
    for(int i = 0; i < n - 1; i++){
        int min_ = i;
        for(int j = i + 1; j < n; j++){
            if(a[j] < a[min_]){
                min_ = a[j];
            }
        }
        if(min_ != i){
            swap(a[i],a[min_]);
        }
    }
}
void bubble(int a[], int n){
    for(int i = 0; i < n - 1; i++){
        int count = 0;
        for(int j = n - 1; j >= i; j--){
            if(a[j - 1] > a[j]){
                swap(a[j - 1], a[j]);
                count = 1;
            }
        }
        if(count == 0){
            break;
        }
    }
}
void insert_sort(int a[], int n){
    int i,j;
    for(int i = 2; i <= n; i++){
        if(a[i] < a[i - 1]){
            a[0] = a[i];
            for(int j = i - 1;a[0] < a[j]; j--){
                a[j + 1] = a[j];
            }
            a[j + 1] = a[0];
        }
    }
}
void shell_sort(int a[], int n){
    int d,i,j;
    for(d = n/2; d>=1; d/=2){
        for(i = d + 1; i <= n; i++){
            if(a[i] < a[i - d]){
                a[0] = a[i];
            }
            for(j = i - d; j > 0 && a[0] < a[j]; j-= d){
                a[j + d] = a[j];
            }
            a[j + d] = a[0];
        }
    }
}
void Merge(int a[], int low, int mid, int high){
    int i,j,k;
    for(k = low;k <= high; k++){
        b[k] = a[k];
    }
    for(i = low,j = mid + 1, k = i; i <= mid && j <= high; k++){
        if(b[i] <= b[j]){
            a[k] = b[i++];
        }
        else{
            a[k] = b[j++];
        }
    }
    while(i <= mid) a[k++] = b[i++];
    while(j <= high) a[k++] = b[j++];
}
void MergeSort(int a[], int low, int high){
    if(low < high){
        int mid = (low + high) / 2;
        MergeSort(a,low,mid);
        MergeSort(a,mid + 1,high);
        Merge(a,low,mid,high);
    }
}
int main(){
    //int a[5] = {5,3,1,2,4};
    /*int k = 0;
    for(int i = 0; i < 5; i++){
        int min_ = a[k];
        int p = k;
        for(int j = k; j < 5; j++){
            if(a[j] < min_){
                min_ = a[j];
                p = j;
            }
        }
        swap(a[k],a[p]);
        k++;
    }
    for(int i = 0; i < 5; i++){
        cout << a[i] << " ";
    }*/
    /*for(int i = 1; i < 5; i++){
        if(a[i] < a[i - 1]){
            int temp = a[i];
            int j;
            for(j = i - 1; j >= 0; j--){
                if(a[j] > temp){
                    a[j + 1] = a[j];
                }
                else{
                    break;
                }
            }
            a[j + 1] = temp;
        }
    }
    for(int i = 0; i < 5; i++){
        cout << a[i] << " ";
    }*/
    /*int size;
    cin >> size;
    int *a = new int[size];
    for(int i = 0; i < size; i++){
        cin >> a[i];
    }
    for(int i = size / 2; i >= 1; i/=2){
        for(int d = i; d < size; d++){
            if(a[d] < a[d - i]){
                int temp = a[d];
                int j;
                for(j = d - i; j >= 0; j-=i){
                    if(a[j] > temp){
                        a[j + i] = a[j];
                    }
                    else{
                        break;
                    }
                }
                a[j + i] = temp;
            }
        }
    }
    for(int i = 0; i < size; i++){
        cout << a[i] << " ";
    }*/
    /*int size;
    cin >> size;
    int *a = new int[size];
    for(int i = 0; i < size; i++){
        cin >> a[i];
    }
    for(int i = 0; i < size - 1; i++){
        int count = 0;
        for(int j = size - 1; j >= i + 1; j--){
            if(a[j - 1] > a[j]){
                swap(a[j - 1], a[j]);
                count = 1;
            }
        }
        if(count == 0){
            break;
        }
    }
    for(int i = 0; i < size; i++){
        cout << a[i] << " ";
    }*/
    int size;
    cin >> size;
    int *a = new int[size];
    for(int i = 0; i < size; i++){
        cin >> a[i];
    }
    MergeSort(a,0,size - 1);
    for(int i = 0; i < size; i++){
        cout << a[i] << " ";
    }
}