#include<iostream>
#include<queue>
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
void queuedisplay(avl *top, int size){
    //用队列来进行层序遍历以及层序输出
    queue<avl*> q;
    q.push(top);
    int count = 1;
    while(count < size){
        avl* temp = q.front();
        q.pop();
        if(temp){
            cout << temp->data << " ";
            count++;
            q.push(temp->cleft);
            q.push(temp->cright);
        }
        else if(!temp){
            continue;
        }
    }
    if(q.front()){
        cout << q.front()->data;
    }
    else{
        while(!q.empty()){
            avl* temp = q.front();
            q.pop();
            if(temp){
                cout << temp->data;
                break;
            }
            else if(!temp){
                continue;
            }
        }
    }
}
bool isComplete(avl* top){
    queue<avl*> q;
    q.push(top);
    while(!q.empty()){
        avl *temp = q.front();
        q.pop();
        if(!temp){
            break;
        }
        else{
            q.push(temp->cleft);
            q.push(temp->cright);
        }
    }
    while(!q.empty()){
        if(q.front()){
            return false;
            break;//如果层序遍历队列中有空，证明没有某节点没有子树，但如果将队列继续遍历，即将树层序遍历，仍然存在叶子节点，则不是完全二叉树
        }
        q.pop();
    }
    return true;
}
void avl_display(avl *pot){
    if(pot != nullptr){
        avl_display(pot->cleft);
        cout << pot->data << " ";
        avl_display(pot->cright);
    }
}
int main(){
    int size;
    cin >> size;
    for(int i = 0; i < size; i++){
        int temp;
        cin >> temp;
        avlinsert(temp);
    }
    /*queuedisplay(root,size);
    cout << endl;
    if(isComplete(root)){
        cout << "Yes";
    }
    else{
        cout << "No";
    }*/
    avl_display(root);
}