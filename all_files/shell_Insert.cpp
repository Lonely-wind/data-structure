#include<iostream>
#include<stdlib.h>
#include<algorithm>
using namespace std;

void Swap(int &a, int &b){
	int temp = a;
	a = b;
	b = temp;
}

bool Compare_fb(int *f, int *b, int N){
	int judge = 0;
	for(int i = 0; i < N; i++){
		if(f[i] != b[i]){
			judge = 1;
			break;
		}	
	}
	if(judge == 0){
		return true;
	}
	else{
		return false;
	}
}

void Merge(int *f, int low, int mid, int high, int *B){
    int i,j,k;
    for(k = low; k <= high; k++)B[k] = f[k];
    for(i = low,j = mid + 1, k = i; i <= mid && j <= high; k++){
        if(B[i] <= B[j]) f[k] = B[i++];
        else f[k] = B[j++];
    }
    while(i <= mid) f[k++] = B[i++];
    while(j <= high) f[k++] = B[j++];
}
void MergeSort(int *f, int low, int high, int*B, int N){
    if(low < high){
        int mid = (low + high) / 2;
        MergeSort(f,low,mid,B,N);
        MergeSort(f,mid + 1,high,B,N);
        Merge(f,low,mid,high,B);
        for(int i = 0; i < N; i++)cout << f[i] << " ";
        cout << endl;
    }
}

int Select_sort_judge(int *f,int *b,int N, int &position){
	int judge = 1;
	int temp, i, j;
	for(i = 1; i < N; i++){
		if(f[i] < f[i - 1]){
			temp = f[i];
			for(j = i - 1; j >= 0 && f[j] > temp; j--){
				f[j + 1] = f[j];
			}
			f[j + 1] = temp;
		}
		position = i + 1;
		if(Compare_fb(f,b,N)){
			judge = 0;
			break;
		}
	}
	return judge;
}

int main(){
	int N;
	cin >> N;
	int *f = new int[N];
    int *f1 = new int[N];
	int *b = new int[N];
	for(int i = 0; i < N; i++)cin >> f[i];
	for(int i = 0; i < N; i++)cin >> b[i];
    for(int i = 0; i < N; i++)f1[i] = f[i];
	int position;
	if( Select_sort_judge(f,b,N, position) == 0){
		cout << "Insertion Sort";
		if(f[position] < f[position - 1]){
			int temp = f[position];
			int j;
			for(j = position - 1; j >= 0 && f[j] > temp; j--){
				f[j + 1] = f[j];
			}
			f[j + 1] = temp;
		}
		cout << endl;
		for(int i = 0; i < N - 1; i++)cout << f[i] << " ";
		cout << f[N - 1];
	}
    else{
        int key = 0;
        for (int i = 2;; i *= 2) {   //这里不给结束条件，是因为当i>n时还要进行一次排序
            for (int j = 0; j < N; j += i) {
                sort(f1 + j, f1 + (j + i < N ? j + i : N));  //注意确定边界
            }
            if (key) {
                cout << "Merge Sort" << endl;
                cout << f1[0];
                for (int j = 1; j < N; j++)
                    cout << " " << f1[j];
                return 0;
            }
            if (equal(f1, f1 + N, b))
                key = 1;
            if (i > N)
                break;
        }
    }
	return 0;
}