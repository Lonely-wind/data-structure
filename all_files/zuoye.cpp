#include<iostream>
#include<cstdio>
#include<algorithm>
#include<ctime>
#include<random>
#include<windows.h>
#include<stdlib.h>
#include<limits.h>
using namespace std;
//测试平衡树
struct tree{
    int data;
    tree *parent = nullptr;
    tree *lchild = nullptr;
    tree *rchild = nullptr;
};
void pingdp(tree *root){
    if(root != nullptr){
        pingdp(root->lchild);
        cout << root->data;
        pingdp(root->rchild);
    }
}//对平衡树进行输出
int pingfind(tree *root, int num){
    tree *fp = root;
    while(fp != nullptr){
        if(num < fp->data){
            fp = fp->lchild;
        }
        else if(num > fp->data){
            fp = fp->rchild;
        }
        else{
            return 1;
            break;
        }
    }
    return 0;    
}//平衡树查找

void tree_insert(tree *root, int num){
    static int count = 0;
    tree *position = root;
    if(count == 0){
        root->data = num;
         count++;
    }//输入根结点
    else{
        int judge = 0;//判断是左孩子还是右孩子
        tree *pposition;//记住父节点
        while(position != nullptr){
            if(num < position->data){
                pposition = position;
                position = position->lchild;
                judge = 1;
            }
            else{
                pposition = position;
                position = position->rchild;
                judge = 2;
            }
        }//进行插入结点的寻找
        position = new tree;
        position->data = num;
        if(judge == 1){
            pposition->lchild = position;
        }
        else{
            pposition->rchild = position;
        }
        position->parent = pposition;
    }
        position = root;//每一次插入完，使position归位
}

bool tree_delete(tree *root, int num){
    if (root == nullptr) {
		return false;
	}
	if (num < root->data) {
		tree_delete(root->lchild, num);
	}
	else if (num > root->data) {
		tree_delete(root->rchild, num);
	}
	else
	{
		//找到要删除的节点

		if (root->lchild == nullptr) {
			tree* temp = root->rchild;
			delete root;
			return true;
		}
		else if (root->rchild == nullptr) {
			tree* temp = root->rchild;
			delete root;
			return true;
		}

		tree *s = root->rchild;
        while(s != nullptr){
            if(s->lchild != nullptr){
                s = s->lchild;
            }
        }
        s = s->parent;
		root->data = s->data;
		tree_delete(root->rchild, s->data);
	}
}

int data[400005];

int main(){
    tree *root = new tree;

    for(int i = 0; i < 400000; i++){
        data[i]=i;
    }
    srand((int) time (NULL));
    random_shuffle(data,data+400000);

    double time1 = 0;
	double count1s = 0;
	LARGE_INTEGER nFreq1;
	LARGE_INTEGER nBeginTime1;
	LARGE_INTEGER nEndTime1;
	QueryPerformanceFrequency(&nFreq1);
	QueryPerformanceCounter(&nBeginTime1);

    for(int i = 0; i < 400000; i++){
        tree_insert(root,data[i]);
    }

    QueryPerformanceCounter(&nEndTime1);  
	time1 = (double)(nEndTime1.QuadPart - nBeginTime1.QuadPart) / (double)nFreq1.QuadPart;
	cout << time1 * 1000 << endl;

    double time2 = 0;
	double count2s = 0;
	LARGE_INTEGER nFreq2;
	LARGE_INTEGER nBeginTime2;
	LARGE_INTEGER nEndTime2;
    QueryPerformanceFrequency(&nFreq2);
	QueryPerformanceCounter(&nBeginTime2);

    random_shuffle(data,data + 400000);

    for(int i = 0; i < 1000; i++){
        pingfind(root,data[i]);
    }

    QueryPerformanceCounter(&nEndTime2);
	time2 = (double)(nEndTime2.QuadPart - nBeginTime2.QuadPart) / (double)nFreq2.QuadPart; 
	cout << time2 * 1000 << endl;

    double time3 = 0;
	double count3s = 0;
	LARGE_INTEGER nFreq3;
	LARGE_INTEGER nBeginTime3;
	LARGE_INTEGER nEndTime3;
    QueryPerformanceFrequency(&nFreq3);
	QueryPerformanceCounter(&nBeginTime3);
    
    for(int i = 0; i < 1000; i++){
        tree_delete(root,data[i]);
    }

    QueryPerformanceCounter(&nEndTime3);
	time3 = (double)(nEndTime3.QuadPart - nBeginTime3.QuadPart) / (double)nFreq3.QuadPart; 
	cout << time3 * 1000 << endl;

}