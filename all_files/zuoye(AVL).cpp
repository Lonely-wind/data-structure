#include<iostream>
#include<cstdio>
#include<algorithm>
#include<ctime>
#include<random>
#include<windows.h>
#include<stdlib.h>
#include<limits.h>
using namespace std;
struct avl{
    int data;
    int bf = 0;
    avl *cleft = nullptr;
    avl *cright = nullptr;
    avl *parent = nullptr;
};
avl *root = nullptr;
void Lrotate(avl *top){
    avl *sur = top->cright;
    avl *surl = sur->cleft;
    avl *pparent = top->parent;
    sur->cleft = top;
    top->cright = surl;
    if(surl){
        surl->parent = top;
    }
    top->parent = sur;
    if(root == top){
        root = sur;
        sur->parent = nullptr;
    }
    else{
        if(pparent->cleft == top){
            pparent->cleft = sur;
        }
        else if(pparent->cright == top){
            pparent->cright = sur;
        }
        sur->parent = pparent;
    }
    sur->bf = 0;
    top->bf = 0;
}
void Rrotate(avl *top){
    avl *sur = top->cleft;
    avl *surl = sur->cright;
    avl *pparent = top->parent;
    sur->cright = top;
    top->cleft = surl;
    if(surl){
        surl->parent = top;
    }
    top->parent = sur;
    if(root == top){
        root = sur;
        sur->parent = nullptr;
    }
    else{
        if(pparent->cleft == top){
            pparent->cleft = sur;
        }
        else if(pparent->cright == top){
            pparent->cright = sur;
        }
        sur->parent = pparent;
    }
    sur->bf = 0;
    top->bf = 0;
}
void LRrotate(avl *top){
    avl *sur = top->cleft;
    avl *surl = sur->cright;
    int bf = surl->bf;
    Lrotate(top->cleft);
    Rrotate(top);
    surl->bf = 0;
    if(bf == 1){
        top->bf = 0;
        sur->bf = -1;
    }
    else if(bf == -1){
        top->bf = 1;
        sur->bf = 0;
    }
    else if(bf == 0){
        top->bf = 0;
        sur->bf = 0;
    }
}
void RLrotate(avl *top){
    avl *sur = top->cright;
    avl *surl = sur->cleft;
    int bf = surl->bf;
    Rrotate(top->cright);
    Lrotate(top);
    surl->bf = 0;
    if(bf == 1){
        top->bf = -1;
        sur->bf = 0;
    }
    else if(bf == -1){
        top->bf = 0;
        sur->bf = 1;
    }
    else if(bf == 0){
        top->bf = 0;
        sur->bf = 0;
    }
}
bool avlinsert(int num){
    if(root == nullptr){
        root = new avl;
        root->data = num;//建立根结点
        return true;
    }
    if(root != nullptr){
        avl *cur = root;
        avl *parent = nullptr;
        while(cur){
            parent = cur;
            if(num < cur->data){
                cur = cur->cleft;
            }
            else if(num > cur->data){
                cur = cur->cright;
            }
            else{
                return false;
            }
        }
        cur = new avl;
        cur->data = num;
        if(num < parent->data){
            parent->cleft = cur;
        }
        else{
            parent->cright = cur;
        }
        //构造平衡树
        //构造avl树
        cur->parent = parent;
        while(parent){
            if(cur == parent->cright){
                parent->bf++;
            }
            else if(cur == parent->cleft){
                parent->bf--;
            }
            if(abs(parent->bf) == 0){
                break;
            }
            else if(abs(parent->bf) == 1){
                parent = parent->parent;//移动parent，寻找差值为2的点
                cur = cur->parent;
            }
            else if(abs(parent->bf) == 2){
                //寻找成功，开始旋转
                if(parent->bf == 2 && cur->bf == 1){
                    //左旋
                    Lrotate(parent);
                }
                else if(parent->bf == -2 && cur->bf == -1){
                    //右旋
                    Rrotate(parent);
                }
                else if(parent->bf == 2 && cur->bf == -1){
                    //右左旋
                    RLrotate(parent);
                }
                else if(parent->bf == -2 && cur->bf == 1){
                    //左右旋
                    LRrotate(parent);
                }
                break;
            }
        }
        return true;
    }
}
void trans_bf(avl *pp, avl *cur){//调整之前的赋值
    while(pp){
        if(cur == pp->cleft){
            pp->bf++;
        }
        else if(cur == pp->cright){
            pp->bf--;
        }
        if(abs(pp->bf) == 1){
            break;
        }
        else if(pp->bf == 0){
            cur = pp;
            pp = pp->parent;
        }
        else if(pp->bf == 2){
            if(pp->cright->bf == 0){
                //左旋
                avl *pr = pp->cright;
                Lrotate(pp);
                pp->bf = 1;
                pr->bf = -1;
                break;
            }
            else if(pp->cright->bf == 1){
                Lrotate(pp);
            }
            else {
                RLrotate(pp);
            }
            cur = pp->parent;
            pp = cur->parent;
        }
        else if(pp->bf == -2){
            if(pp->cleft->bf == 0){
                avl *pl = pp->cleft;
                Rrotate(pp);
                pp->bf = -1;
                pl->bf = 1;
            }
            else if(pp->cleft->bf == -1){
                Rrotate(pp);
            }
            else{
                LRrotate(pp);
            }
            cur = pp->parent;
            pp = pp->parent;
        }
    }
}
void AVLdelete(int num){
    avl *position = root;//position代表需要删除的位置
    while(position != nullptr){
        if(num < position->data){
            position = position->cleft;
        }
        if(num > position->data){
            position = position->cright;
        }
        if(num == position->data){
            break;//找到所在结点
        }
    }
    /*左右孩子都没有*/
    if(!position->cleft && !position->cright){
        avl *pp = position->parent;
        if(root = position){
            root = nullptr;
        }   
        else{
            avl *pp = position->parent;
            avl *in = position;
            trans_bf(pp,position);//向上更新bf的值
            position = in;
            pp = position->parent;
            if(pp->cleft == position){
                pp->cleft = nullptr;
            }
            else{
                pp->cright = nullptr;
            }
        }
        delete position;
    }
    /*若只有左孩子*/
    else if(position->cleft && !position->cright){
        avl *pp = position->parent;
        if(pp = root){
            avl *pl = position->cleft;
            root = pl;
            pl->parent = nullptr;
        }
        else{//非根节点
            trans_bf(pp,position);//向上更新bf的值
            pp = position->parent;
            avl *pl = position->cleft;
            if(pp->cleft = position){
                pp->cleft = pl;
                pl->parent = pp;
            }
            else{
                pp->cright = pl;
                pl->parent = pp;
            }
        }
        //position为根节点
        delete position;
    }
    /*只有右孩子*/
    else if(position->cright && !position->cleft){
        avl *pp = position->parent;
        if(pp = root){
            avl *pr = position->cright;
            root = pr;
            pr->parent = nullptr;
        }
        else{//非根节点
            trans_bf(pp,position);//向上更新bf的值
            pp = position->parent;
            avl *pr = position->cright;
            if(pp->cleft = position){
                pp->cleft = pr;
                pr->parent = pp;
            }
            else{
                pp->cright = pr;
                pr->parent = pp;
            }
        }
        //position为根节点
        delete position;
    }
    else if(position->cleft && position->cright){
        avl *ml = position->cleft;
        while(ml != nullptr && ml->cright != nullptr){
            ml = ml->cright;
        }
        //找到需要替换的点
        avl *pp = ml->parent;
        trans_bf(pp,ml);
        if(ml == position->cleft){//就在position的左边
            if(ml->cleft){
                ml->cleft->parent = position;
                position->cleft = ml;
            }
            else{
                position->cleft = nullptr;
            }
        }
        else{
            //并不在左边。删除ml即可
            if(ml->cleft){
                ml->cleft->parent = pp;
                pp->cright = ml->cleft;
            }
            else{
                pp->cright = ml->cright;
            }
        }
        delete ml;
    }
}
void avl_display(avl *pot){
    if(pot != nullptr){
        avl_display(pot->cleft);
        cout << pot->data << " ";
        avl_display(pot->cright);
    }
}
bool avl_Search(int num){
    avl *s = root;
    while(s != nullptr){
        if(num < s->data){
            s = s->cleft;
        }
        else if(num > s->data){
            s = s->cright;
        }
        else{
            return true;
        }
    }
    return false;
}
int data[4000005];
int main(){
     for(int i = 0; i < 400000; i++){
        data[i]=i;
    }

    random_shuffle(data,data+400000);

    srand((int) time (NULL));

    double time1 = 0;
	double count1s = 0;
	LARGE_INTEGER nFreq1;
	LARGE_INTEGER nBeginTime1;
	LARGE_INTEGER nEndTime1;
	QueryPerformanceFrequency(&nFreq1);
	QueryPerformanceCounter(&nBeginTime1);


    for(int i = 0; i < 400000; i++){
        avlinsert(data[i]);
    }
    
    QueryPerformanceCounter(&nEndTime1);  
	time1 = (double)(nEndTime1.QuadPart - nBeginTime1.QuadPart) / (double)nFreq1.QuadPart;
    cout << time1 * 1000  << endl;

    random_shuffle(data,data+1000);

    double time2 = 0;
	double count2s = 0;
	LARGE_INTEGER nFreq2;
	LARGE_INTEGER nBeginTime2;
	LARGE_INTEGER nEndTime2;
    QueryPerformanceFrequency(&nFreq2);
	QueryPerformanceCounter(&nBeginTime2);

    for(int i = 0; i < 1000; i++){
        AVLdelete(data[i]);
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
        avl_Search(data[i]);
    }

    QueryPerformanceCounter(&nEndTime3);
	time3 = (double)(nEndTime3.QuadPart - nBeginTime3.QuadPart) / (double)nFreq3.QuadPart; 
	cout << time3 * 1000 << endl;

    //avl_display(root);
}