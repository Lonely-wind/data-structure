#include<iostream>
#include<cstdio>
#include<algorithm>
#include<ctime>
#include<random>
#include<windows.h>
#include<stdlib.h>
#include<limits.h>
using namespace std;
struct  Btree{
    int *keys;//存放有效数据
    Btree **child;//存放有效子节点
    Btree *parent;
    int datanum;//关键字个数
    int childnum;//孩子的数量
    int level;//树的阶数
};
Btree* initBtree(int level){
    Btree *node = new Btree;
    node->level = level;
    node->datanum = 0;
    node->childnum = 0;
    node->keys = new int[level + 1];//level+1方便后续进行合并操作，0位置不
    node->child = new Btree*[level];
    node->parent = nullptr;
    int i;
    for(i = 0; i < level; i++){
        node->keys[i] = 0;//将数据域归0
        node->child[i] = nullptr;
    }
    //node->keys[i] = 0;
    return node;
}
int findSuiteIndex(Btree* node, int data){
    int index;
    for(index = 1; index <= node->datanum; index++){//因为从1开始存储的，所以index等于1
        if(data < node->keys[index]){
            break;
        }
    }
    return index;//实际存储的是index-1的位置
}
//找到合适的叶子结点
Btree* findSuiteNode(Btree* T, int data){
    if(T->childnum == 0){
        return T;
    }
    else{
        int index = findSuiteIndex(T,data);
        return findSuiteNode(T->child[index - 1], data);//通过不断地递归，寻找可以插入的叶子节点
    }
}
void addData(Btree* node, int data, Btree** T){
    int index = findSuiteIndex(node, data);
     for(int i = node->datanum; i >= index; i--){
        node->keys[i + 1] = node->keys[i];//空出需要插入的地方
     }
     node->keys[index] = data;
     node->datanum++;
     //判断是否需要进行分裂
     if(node->datanum == node->level){
        //找到分裂位置
        int mid = node->level / 2 + node->level % 2;//找中间值
        //进行分裂
        Btree* lchild = initBtree(node->level);
        Btree* rchild = initBtree(node->level);
        for(int i = 1; i < mid; i++){
            lchild->keys[i] = node->keys[i];
            lchild->datanum++;
        }
        for(int i = mid + 1 , k = 1; i <= node->datanum; i++,k++){
            rchild->keys[k] = node->keys[i];
            rchild->datanum++;
        }
        for(int i = 0; i < mid; i++){
            lchild->child[i] = node->child[i];
            if(node->child[i] != nullptr){
                node->child[i]->parent = lchild;
                lchild->childnum++;
            }
        }   
        int index = 0;
        for(int i = mid; i < node->childnum; i++){
            rchild->child[index++] = node->child[i];
            if(node->child[i] != nullptr){
                node->child[i]->parent = rchild;
                rchild->childnum++;
            }
        }
        //讨论父亲结点的各种情况
        if(node->parent == nullptr){//插入的节点是根节点
            Btree* newparent = initBtree(node->level);
            addData(newparent,node->keys[mid], T);
            newparent->child[0] = lchild;
            newparent->child[1] = rchild;
            newparent->childnum = 2;
            lchild->parent = newparent;
            rchild->parent = newparent;
            *T = newparent;//T代表根节点，此时分裂出了一个新的根节点，那么就让T指向这个新节点
        } 
        else{
            int index = findSuiteIndex(node->parent,node->keys[mid]);
            lchild->parent = node->parent;
            rchild->parent = node->parent;
            node->parent->child[index - 1] = lchild;
            if(node->parent->child[index] != nullptr){
                for(int i = node->parent->childnum - 1; i >= index; i--){
                    node->parent->child[i + 1] = node->parent->child[i];
                }
            }
            node->parent->child[index] = rchild;
            node->parent->childnum++;
            addData(node->parent,node->keys[mid], T);
        }
    }
}
void insert(Btree **T, int data){
    Btree *position = findSuiteNode(*T,data);
    addData(position,data,T);
}
Btree* B_find(Btree *T, int data){
    if(T != nullptr){
        for(int i = 1; i <= T->datanum; i++){
            if(data == T->keys[i]){
                return T;
            }
            else if(data < T->keys[i]){
                return B_find(T->child[i - 1], data);
            }
            else{
                if(i != T->datanum && data < T->keys[i + 1]){
                    return B_find(T->child[i], data);
                }
            }
        }
    }
    return B_find(T->child[T->datanum], data);
}
void B_display(Btree *T){
    if(T != nullptr){
        for(int i = 1; i <= T->datanum; i++){
            cout << T->keys[i] << " "; 
        }
        cout << endl;
        for(int i = 0; i < T->childnum; i++){
            B_display(T->child[i]);
        }
    }
}
Btree* F_front(Btree *T){
    while(T->childnum != 0){
        T = T->child[T->childnum - 1];
    }
    return T;
}
void B_delete(Btree *T, int data){
    Btree *pposition = B_find(T, data);//找到需要删除的节点
    Btree *position;
    position = pposition;
    if(pposition->childnum != 0){
        int pposition_index;
        for(int i = 1; i <= pposition->datanum; i++){
            if(data = pposition->keys[i]){
                pposition_index = i;    
                break;
            }
        }
        position = F_front(pposition);//寻找mostleft，将mostleft变为实际要删除的点
        position->keys[position->datanum] = pposition->keys[pposition_index];
        data = position->keys[position->datanum];
    }
    if(position->childnum == 0){
        int index;//代表需要删除的位置
        for(int i = 1; i <= position->datanum; i++){
            if(data == position->keys[i]){
                index = i;
                break;
            }
        }
        int judge = position->level / 2;//取每个节点最小的关键字个数
        if(position->datanum > judge){
            //直接删除
            for(int i = index; i <= position->datanum; i++){
                position->keys[i] = position->keys[i + 1];
            }
            position->datanum--;
        }
        //需要进行合并
        else if(position->datanum == judge){
            //关键字已经到了最小，需要进行合并操作
            Btree *pp = position->parent;
            int pindex;
            for(int i = 0; i < pp->childnum; i++){
                if(pp->child[i] == position){
                    pindex = i;
                    break;
                }
            }//找到子节点在父亲中的位置
            int ljudge;
            int rjudge;
            //尝试向左边进行借取
            int pbrindex = ++pindex;
            cout << pbrindex;
            Btree *pr = pp->child[pbrindex];
            if(pbrindex < pp->childnum){
                if(pr->datanum > judge){
                    //可以借取
                    rjudge = 1;
                }
                else{
                    rjudge = 0;
                }
            }
            int pblindex = --pindex;
            Btree *pl = pp->child[pblindex];
            if(pblindex >= 0){
                if(pl->datanum > judge){
                    //可以借取
                    ljudge = 1;
                }
                else{
                    ljudge = 0;
                }
            }
            cout << rjudge << " " << ljudge;
            if((ljudge == 1 && rjudge == 0) || (ljudge == 1 && rjudge == 1)){
                cout << "ceshi";
                position->keys[index] = pp->keys[pindex - 1];
                pp->keys[pindex - 1] = pl->keys[pl->datanum];
                pl->datanum--;
            }
            else if(ljudge == 0 && rjudge == 1){
                cout << "ceshi";
                position->keys[index] = pp->keys[pindex + 1];
                pp->keys[pindex + 1] = pr->keys[1];
                for(int i = 1; i < pr->datanum; i++){
                    pr->keys[i] = pr->keys[i + 1];
                }
                pr->datanum--;
            }
            else{

            }
        }
    }
}
int data[4000005];
int main(){
    for(int i = 0; i < 400000; i++){
        data[i]=i;
    }
    srand((int) time (NULL));
    //random_shuffle(data,data+400000);
    Btree *T = initBtree(512);
    /*insert(&T ,10);
    insert(&T ,1);
    insert(&T ,2);
    insert(&T ,3);
    insert(&T ,5);
    insert(&T ,6);
    insert(&T ,7);
    insert(&T ,8);*/

    double time2 = 0;
	double count2s = 0;
	LARGE_INTEGER nFreq2;
	LARGE_INTEGER nBeginTime2;
	LARGE_INTEGER nEndTime2;
    QueryPerformanceFrequency(&nFreq2);
	QueryPerformanceCounter(&nBeginTime2);

    for(int i = 0; i < 400000; i++){
        insert(&T,data[i]);
    }
    
    QueryPerformanceCounter(&nEndTime2);
	time2 = (double)(nEndTime2.QuadPart - nBeginTime2.QuadPart) / (double)nFreq2.QuadPart; 
	cout << time2 * 1000 << endl;
    
    //B树查找

    double time1 = 0;
	double count1s = 0;
	LARGE_INTEGER nFreq1;
	LARGE_INTEGER nBeginTime1;
	LARGE_INTEGER nEndTime1;
	QueryPerformanceFrequency(&nFreq1);
	QueryPerformanceCounter(&nBeginTime1);

    for(int i = 0; i < 1000; i++){
        Btree *temp = B_find(T, data[i]);
    }

    QueryPerformanceCounter(&nEndTime1);  
	time1 = (double)(nEndTime1.QuadPart - nBeginTime1.QuadPart) / (double)nFreq1.QuadPart;
    cout << time1 * 1000  << endl;

    //B_delete(T,6);
}