#include<iostream>
#include<stdlib.h>
#include<stack>
using namespace std;
int main() {
	int nsize;
	int num;
	cin >> nsize >> num;
	int** data = new int* [nsize];
	for (int i = 0; i < nsize; i++) {
		data[i] = new int[nsize];
	}
	//使用邻接矩阵来存放路程
	//对矩阵初始化
	for (int i = 0; i < nsize; i++) {
		for (int j = 0; j < nsize; j++) {
			data[i][j] = -1;
		}
	}
	for (int i = 0; i < num; i++) {
		int x, y, temp;
		cin >> x >> y >> temp;
		data[x - 1][y - 1] = temp;
	}
	int* path = new int[nsize];
	int* dist = new int[nsize];
	int* note = new int[nsize];
	for (int i = 0; i < nsize; i++) {
		path[i] = -1;
		dist[i] = 100000;//代表无穷大
		note[i] = -1;//-1代表该节点未被使用
	}
	int position;
	cin >> position;
	note[position - 1] = 1;
	dist[position - 1] = 0;
	/*for(int i = 0; i < nsize; i++){
		for(int j = 0; j < nsize; j++){
			cout << data[i][j] << " ";
		}
		cout << endl;
	}*/
	for (int i = 0; i < nsize; i++) {
		if (data[position - 1][i] != -1 && i != (position - 1)) {
			dist[i] = data[position - 1][i];
			path[i] = position - 1;
		}
	}
	for (int i = 1; i < nsize; i++) {
		//开始遍历
		int min = 1000;
		int p = -1;
		for (int j = 0; j < nsize; j++) {
			if (note[j] == -1 && dist[j] < min) {
				min = dist[j];
				p = j;
			}
		}
		if (p == -1) {
			break;
		}
		note[p] = 1;
		//更新距离
		for (int k = 0; k < nsize; k++) {
			if (note[k] != 1) {
				if (data[p][k] != -1 && (dist[p] + data[p][k] < dist[k] || dist[k] == 100000)) {
					dist[k] = dist[p] + data[p][k];
					path[k] = p;
				}
			}
		}
		/*for (int i = 0; i < nsize; i++) {
			cout << dist[i] << " ";
		}
		cout << " ";
		for (int i = 0; i < nsize; i++) {
			cout << note[i] << " ";
		}
		cout << endl;*/
	}
    int count = 0;
    for(int i = 0; i < nsize; i++){
        if(dist[i] != 100000 && dist[i] != 0){
            count++;
        }
    }//找出一共有多少个通路
    for(int i = 0; i < count; i++){
        int min1 = 1000;
        int temp;
        for(int j = 0; j < nsize; j++){
            if(dist[j] != -1 && dist[j] != 0 && dist[j] < min1 ){
                temp = j;
                min1 = dist[j];
            }
        }
        int judge = temp;
        stack<int> s;
        while(judge != -1){
            s.push(judge);
            judge = path[judge];
        }
		cout << "No." << i + 1 << " : ";
		int size = s.size();
		int countsize = 0;
        while(!s.empty()){
			if(countsize == size - 1){
				cout << s.top() + 1 << " " << "," << " " << "d = " << dist[temp];
				break;
			}
            cout << s.top() + 1 << " -> ";
			s.pop();
			countsize++;
        }
		//cout << s.top();
        cout << endl;
        dist[temp] = -1;
    }
	int ejudge = 0;
	for(int i = 0; i < nsize; i++){
		if(dist[i] == 100000){
			ejudge = 1;
			break;
		}
	}
	if(ejudge == 1){
		cout << "No." << count + 1 << " : " << "No Path to";
		for(int i = 0; i < nsize; i++){
			if(dist[i] == 100000){
				cout << " " << i + 1;
			}
		}
	}
	return 0;
}