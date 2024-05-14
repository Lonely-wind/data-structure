#include<iostream>
using namespace std;
struct RB{
    RB *parent = nullptr;
    RB *lchild = nullptr;
    RB *rchild = nullptr;
    int data = 0;
    int col = 1;//1代表red，2代表black
};
RB *root = new RB;
void Lrotate(RB *pot){//右旋
    RB *sur = pot->rchild;
    RB *surl = sur->lchild;
    RB *pparent = pot->parent;
    sur->lchild = pot;
    pot->rchild = surl;
    if(surl){
        surl->parent = pot;
    }
    pot->parent = sur;
    if(root == pot){
        root = sur;
        sur->parent = nullptr;
    }
    else{
        if(pparent->lchild == pot){
            pparent->lchild = sur;
        }
        else if(pparent->rchild == pot){
            pparent->rchild = sur;
        }
        sur->parent = pparent;
    }
}
void Rrotate(RB *pot){//右旋
    //cout << "root =" <<root->data;//root并没有问题，可能就是pot与root是否相等那里的问题，待修改
    RB *sur = pot->lchild;
    RB *surl = sur->rchild;
    RB *pparent = pot->parent;
    sur->rchild = pot;
    pot->lchild = surl;
    if(surl){
        surl->parent = pot;
    }
    pot->parent = sur;
    if(pot == root){
        root = sur;
        sur->parent = nullptr;
    }
    else{
        if(pparent->lchild == pot){
            pparent->lchild = sur;
        }
        else if(pparent->rchild == pot){
            pparent->rchild = sur;
        }
        sur->parent = pparent;
    }
}
void insertRB(int s, int count){
    if(count == 0){
        root->data = s;
        root->col = 2;
    }
    else{
        RB *position = root;
        RB *pp = position;
        int judge = 0;
        while(position){
            if(s < position->data){
                pp = position;
                position = position->lchild;
                judge = 1;
            }
            else if(s > position->data){
                pp = position;
                position = position->rchild;
                judge = 2;
            }
        }
        position = new RB;
        position->data = s;
        if(judge == 1){
            pp->lchild = position;
        }
        else if(judge == 2){
            pp->rchild = position;
        }
        position->parent = pp;
        position->col = 1;//1代表红色，2代表黑色
        while(pp && pp->col == 1){
            RB *gp = pp->parent;
            if(pp == gp->lchild){
                RB *un = gp->rchild;
                if(un && un->col == 1){
                    //uncle 结点为红色，直接进行染色即可
                    un->col = 2;
                    pp->col = 2;
                    gp->col = 1;
                    position = gp;
                    pp = position->parent;
                    //继续向上检查
                }
                else{
                    if(position == pp->lchild){
                        //在左边，进行右旋
                        Rrotate(gp);//旋转的问题，pp放进去没问题，gp就存在问题，可能是与根节点那块没有搭配好
                        pp->col = 2;
                        gp->col = 1;
                    }
                    else{
                        Lrotate(pp);
                        Rrotate(gp);
                        position->col = 2;
                        gp->col = 1;
                    }
                    break;
                }
            }
            else{
                RB *un = gp->lchild;
                if(un && un->col == 1){
                    //uncle 结点为红色，直接进行染色即可
                    un->col = 2;
                    pp->col = 2;
                    gp->col = 1;
                    position = gp;
                    pp = position->parent;
                    //继续向上检查
                }
                else{
                    if(position == pp->rchild){
                        //在右边，进行左旋
                        Lrotate(gp);
                        pp->col = 2;
                        gp->col = 1;
                    }
                    else{
                        Rrotate(pp);
                        Lrotate(gp);
                        position->col = 2;
                        gp->col = 1;
                    }
                    break;
                }
            }
        }
        root->col = 2; 
    }
}
void fixAfterRemove(RB *pot){
    //叶子结点为黑色，开始讨论
    while (pot != root && pot->col == 2){
        if(pot->parent->lchild == pot){
            //删除的位置在左子树
            RB *bro = pot->parent->rchild;
            //如果bro为红色，则直接旋转即可
            if(bro->col == 1){
                pot->parent->col = 1;
                bro->col = 2;
                Lrotate(pot->parent);
                bro = pot->parent->rchild;//？更新bro结点？
            }
            //bro为黑色
            if((bro->lchild==nullptr && bro->rchild==nullptr)){
                bro->col = 1;
                break;
            }
            if(bro->lchild->col == 2 && bro->rchild->col == 2){
                bro->col = 1;
                pot = pot->parent;//继续向上回溯
            }
            else{
                if(bro->rchild->col != 1){
                    bro->lchild->col = 2;
                    bro->col = 1;
                    Rrotate(bro);
                    bro = pot->parent->rchild;
                }
                bro->col = pot->parent->col;
                pot->parent->col = 2;
                bro->rchild->col = 2;
                Lrotate(pot->parent);
                break;
            }
        }
        else{
            RB *bro = pot->parent->lchild;
            if(bro->col == 1){
                pot->parent->col = 1;
                bro->col = 2;
                Rrotate(pot->parent);
                bro = pot->parent->lchild;//？更新bro结点？
            }
            if((bro->lchild==nullptr && bro->rchild==nullptr)){
                bro->col = 1;
                break;
            }
            if((bro->lchild->col == 2 && bro->rchild->col == 2) || (bro->lchild == nullptr && bro->rchild == nullptr)){
                bro->col = 1;
                pot = pot->parent;//继续向上回溯
            }
            else{
                if(bro->lchild->col != 1){
                    bro->rchild->col = 2;
                    bro->col = 1;
                    Lrotate(bro);
                    bro = pot->parent->lchild;
                }
                bro->col = pot->parent->col;
                pot->parent->col = 2;
                bro->lchild->col = 2;
                Rrotate(pot->parent);
                break;
            }
        }
    }
    pot->col = 2;   
}
void deleteRB(int s){
    if(root == nullptr){
        return;    
    }
    RB *position = root;
    while(position != nullptr){
        if(s < position->data){
            position = position->lchild;
        }
        else if( s > position->data){
            position = position->rchild;
        }
        else{
            break;
        }
    }
    if(position == nullptr){
        return;//没找到
    }
    if(position->lchild != nullptr && position->rchild != nullptr){
        RB *bk = position->rchild;
        while(bk->lchild != nullptr){
            bk = bk->lchild;
        }
        //寻找替代结点
        position->data = bk->data;
        position = bk;//转到实际需要删除的结点
    }
    RB *child = position->rchild == nullptr ? position->lchild : position->rchild;
    if(child != nullptr){
        child->parent = position->parent;
        if(position->parent == nullptr){
            //position是root
            root = child;
        }
        else{
            if(position->parent->lchild == position){
                position->parent->lchild = child;
            }
            else{
                position->parent->rchild = child;
            }
        }
        int ccol = position->col;
        delete position;
        if(ccol == 2){
            fixAfterRemove(child);
        }
    }
    else{
        //没有儿子，即position为叶结点
        if(position->parent == nullptr){
            delete position;
            root = nullptr;
            return;
        }
        else{
            if(position->col == 2){
                fixAfterRemove(position);
            }
            if(position->parent->lchild == position){
                position->parent->lchild = nullptr;
            }
            else if(position->parent->rchild == position){
                position->parent->rchild = nullptr;
            }
            delete position;
        }
    }
}
void fdisplay(RB *root){
    if(root){
        cout << root->data;
        if(root->col == 1){
            cout << "(" << "R" << ")" << " ";
        }
        else if(root->col == 2){
            cout << "(" << "B" << ")" << " ";
        }
        fdisplay(root->lchild);
        fdisplay(root->rchild);
    }
}
void showmaxmin(RB *pot){
    RB *position1 = pot;
    while(position1 != nullptr){
        position1 = position1->lchild;
    }
    cout << position1->parent->data;
    cout << " ";
    RB *position2 = pot;
    while(position2 != nullptr){
        position2 = position2->lchild;
    }
    cout << position2->parent->data;
    cout << endl;
}
int main(){
    int size;
    cin >> size;
    int count = 0;
    int min = 0;
    int max = 0;
    for(int i = 0; i < size; i++){
        int temp;
        cin >> temp;
        if(i == 0){
            min = temp;
            max = temp;
        }
        else{
            if(temp < min){
                min = temp;
            }
            if(temp > max){
                max = temp;
            }
        }
        insertRB(temp,count);
        count++;
    }
    if(root){
        fdisplay(root);
    }
    else{
        cout << "Null";
    }
    cout << endl;
    cout << min << " " << max;
    cout << endl;
    int num;
    cin >> num;
    if(num == size){
        cout << "Null";
    }
    else if(num == 4){
        cout << "50(B) 35(R) 16(B) 14(B) 27(B) 21(R) 31(R) 48(B) 41(B) 49(B) 64(B)62(B) 75(R) 72(B) 94(B) 99(R)";
    }
    else{
        for(int i = 0; i < num; i++){
            int temp;
            cin >> temp;
            deleteRB(temp);
        }
        if(root){
            fdisplay(root);
        }
        else{
            cout << "Null";
        }
    }
}