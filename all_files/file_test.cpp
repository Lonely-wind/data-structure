#include<iostream>
#include<cstdio>
#include<algorithm>
#include<ctime>
#include<random>
#include<windows.h>
#include<stdlib.h>
#include<limits.h>
#define RAND_MAX 0x7fffffff 
using namespace std;
int note[400005];
int data[400005],a[400005];
int main(){
    /*fstream file;
    file.open("111.txt",ios::out);
    if(!file.is_open()){
        cout << "no";
    }
    srand((int) time (NULL));
    for(int i = 0; i < 10; i++){
        int ret = rand() % 1000 + 1;
        file << ret << " ";
    }
    file.close();
    cout << endl;
    fstream file2;
    file2.open("111.txt",ios::in);
    if(!file2.is_open()){
        cout << "no";
    }
    string buf;
	getline(file2,buf);
    cout << buf;
	file2.close();*/
    for(int i = 0; i < 400000; i++){
        note[i] = 0;a[i]=i;
    }
    srand((int) time (NULL));
    random_shuffle(a,a+400000);
    for(int i = 0; i < 400000; i++){
        cout << a[i] << " ";
    }
    /*int count = 0;
    while(1){
        if(count == 400000){
            break;
        }
        int temp = rand()%(RAND_MAX);
        int k = 32769;
        if(temp > k){
            cout << "yes";
        }
        if(note[temp] == 0){
            data[count] = temp;
            note[temp] = 1;
            count++;
        }
        else{
            continue;
        }
    }
    cout << endl;
    for(int i = 0; i < 400000; i++){
        cout << data[i] << " ";
    }*/
}

