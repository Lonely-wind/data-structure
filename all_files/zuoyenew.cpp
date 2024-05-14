#include<iostream>
#include<queue>
#include<time.h>
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
        root->data = num;//建立根结�?
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
        //构造avl�?
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
                //寻找成功，开始旋�?
                if(parent->bf == 2 && cur->bf == 1){
                    //左旋
                    Lrotate(parent);
                }
                else if(parent->bf == -2 && cur->bf == -1){
                    //右旋
                    Rrotate(parent);
                }
                else if(parent->bf == 2 && cur->bf == -1){
                    //右左�?
                    RLrotate(parent);
                }
                else if(parent->bf == -2 && cur->bf == 1){
                    //左右�?
                    LRrotate(parent);
                }
                break;
            }
        }
        return true;
    }
}
void trans_bf(avl *pp, avl *cur){//调整之前的赋�?
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
    while(position){
        if(num < position->data){
            position = position->cleft;
        }
        if(num > position->data){
            position = position->cright;
        }
        if(num == position->data){
            break;//找到所在结�?
        }
    }
    /*左右孩子都没�?*/
    if(position->cleft == nullptr && position->cright == nullptr){
        avl *pp = position->parent;
        if(root == position){
            root = nullptr;
        }   
        else{
            cout << "ceshi";
            avl *pp = position->parent;
            trans_bf(pp,position);//向上更新bf的�?
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
            trans_bf(pp,position);//向上更新bf的�?
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
    /*只有右孩�?*/
    else if(position->cright && !position->cleft){
        avl *pp = position->parent;
        if(pp = root){
            avl *pr = position->cright;
            root = pr;
            pr->parent = nullptr;
        }
        else{//非根节点
            trans_bf(pp,position);//向上更新bf的�?
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
        cout << "ceshi";
        avl *ml = position->cleft;
        while(ml != nullptr && ml->cright != nullptr){
            ml = ml->cright;
        }
        //找到需要替换的�?
        avl *pp = ml->parent;
        position->data = ml->data;
        trans_bf(pp,ml);
        if(ml == position->cleft){//就在position的左�?
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
void avl_display_mid(avl *pot){
    if(pot != nullptr){
        avl_display_mid(pot->cleft);
        cout << pot->data << " ";
        avl_display_mid(pot->cright);
    }
}
void avl_display_fro(avl *pot){
    if(pot != nullptr){
        cout << pot->data << " ";
        avl_display_mid(pot->cleft);
        avl_display_mid(pot->cright);
    }
}
int main(){
    int note[2000];
    for(int i = 0; i < 2000; i++){
        note[i] = 0;
    }
    srand((int) time (NULL));
    int count = 0;
    int data[2000];
    while(1){
        if(count == 1000){
            break;
        }
        int temp = rand()%2000 + 1;
        if(note[temp] == 0){
            data[count] = temp;
            note[temp] = 1;
            count++;
        }
        else{
            continue;
        }
    }
    /*for(int i = 0; i < 10; i++){
        cout << data[i] << " ";
    }*/
    for(int i = 0; i <1000; i++){
        int temp;
        temp = data[i];
        avlinsert(temp);
    }
    /*int k1 = 8;
    AVLdelete(k1);
    int k2 = 10;
    AVLdelete(k2);*/
    avl_display_mid(root);   
    avl_display_fro(root);
    cout << "600�ɹ�" << endl;
    for(int i = 100; i < 200; i++){
        int temp;
        temp = data[i];
        AVLdelete(temp);
    }
    avl_display_fro(root);
}