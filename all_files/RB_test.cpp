#include<iostream>
#include<time.h>
using namespace std;

enum Color
{
RED, BLACK
};

struct node
{
int data;
node* parent;
node* left;
node* right;
Color color;

node(int val) {
    data = val;
    color = RED;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}
};

class RedBlackTree {
public:
node* root;

//Left-rotate
void leftRotate(node* x) {
    node* y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

//Right-rotate
void rightRotate(node* x) {
    node* y = x->left;
    x->left = y->right;
    if (y->right != nullptr) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    }
    else if (x->parent == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    y->right = x;
    x->parent = y;
}

//Insert fix
void insertFixup(node* z) {
    while (z->parent != nullptr && z->parent->color == RED)
        {
            if (z->parent == z->parent->parent->left) {//父节点是爷节点的左节点
                node* y = z->parent->parent->right;
                if (y != nullptr && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;//节点上移动两层，便于在后续循环中继续
                }
                else
                {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            }
            else
            {
                node* y = z->parent->parent->left;
                if (y != nullptr && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
    root->color = BLACK;
}

//Insert
void insertNode(int data) {
    node* newNode = new node(data);
    node* y = nullptr;//x的父节点
    node* x = root;
    while (x != nullptr)
        {
            y = x;
            if (newNode->data < x->data) {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }

    newNode->parent = y;
    if (y == nullptr) {
        root = newNode;
    }
    else if (newNode->data < y->data)
    {
        y->left = newNode;
    }
    else
    {
        y->right = newNode;
    }

    insertFixup(newNode);
}

//preorder
void PreOrder(node* root) {
    if (root != nullptr) {
        cout << root->data << (root->color == RED ? "(R)" : "(B)")<<" ";
        PreOrder(root->left);
        PreOrder(root->right);
    }
}

//min
node* getMinnode(node* root) {
    while (root->left!=nullptr)
        {
            root = root->left;
        }
    return root;
}

//max
node* getMaxnode(node* root) {
    while (root->right!=nullptr)
        {
            root = root->right;
        }
    return root;
}

//transplant
void transplant(node* u, node* v) {
		if (u->parent == nullptr) {
			root = v;
		}
		else if (u == u->parent->left) {
			u->parent->left = v;
		}
		else
		{
			u->parent->right = v;
		}
		if (v != nullptr) {
			v->parent = u->parent;
		}
	}

	//delete fix
	void deleteFixup(node* x) {
		while (x!=root&&(x==nullptr||x->color==BLACK))
		{
			if (x == x->parent->left) {
				node* w = x->parent->right;
				if (w->color == RED) {
					w->color = BLACK;
					x->parent->color = RED;
					leftRotate(x->parent);
					w = x->parent->right;
				}
				if((w->left==nullptr||w->left->color==BLACK)&&(w->right==nullptr||w->right->color==BLACK)){
					w->color = RED;
					x = x->parent;
				}
				else
				{
					if (w->right == nullptr || w->right->color == BLACK) {
						if (w->left != nullptr) {
							w->left->color = BLACK;
						}
						w->color = RED;
						rightRotate(w);
						w = x->parent->right;
					}
					w->color = x->parent->color;
					x->parent->color = BLACK;
					if (w->right != nullptr) {
						w->right->color = BLACK;
					}
					leftRotate(x->parent);
					x = root;
				}
			}
			else
			{
				node* w = x->parent->left;
				if (w->color == RED) {
					w->color = BLACK;
					x->parent->color = RED;
					rightRotate(x->parent);
					w = x->parent->left;
				}
				if ((w->right == nullptr || w->right->color == BLACK) &&
					(w->left == nullptr || w->left->color == BLACK)) {
					w->color = RED;
					x = x->parent;
				}
				else {
					if (w->left == nullptr || w->left->color == BLACK) {
						if (w->right != nullptr) {
							w->right->color = BLACK;
						}
						w->color = RED;
						leftRotate(w);
						w = x->parent->left;
					}
					w->color = x->parent->color;
					x->parent->color = BLACK;
					if (w->left != nullptr) {
						w->left->color = BLACK;
					}
					rightRotate(x->parent);
					x = root;
				}
			}
		}
		if (x != nullptr) {
			x->color = BLACK;
		}
	}

	//search node
	node* searchNode(int data) {
		return searchNode(root, data);
	}
	node* searchNode(node* Node, int data) {
		if (Node == nullptr || Node->data == data) {
			return Node;
		}
		if (data < Node->data) {
			return searchNode(Node->left, data);
		}
		else
		{
			return searchNode(Node->right, data);
		}
	}

	//delete node
	void deleteNode(int data) {
		node* z = searchNode(data);
		if (z == nullptr) {
			return;
		}

		node* y = z;
		node* x = nullptr;
		Color y_or = y->color;

		if (z->left == nullptr) {
			x = z->right;
			transplant(z, z->right);
		}
		else if (z->right == nullptr) {
			x = z->left;
			transplant(z, z->left);
		}
		else
		{
			y = getMinnode(z->right);
			y_or = y->color;
			x = y->right;
			if (y->parent == z) {
				if (x != nullptr) {
					x->parent = y;
				}
			}
			else
			{
				transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			transplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		if (y_or == BLACK) {
			deleteFixup(x);
		}
		delete z;
	}

public:
	RedBlackTree() {
		root = nullptr;
	}
	bool find_data(node *s, int data){
		while(s != nullptr){
			if(data < s->data){
				s = s->left;
			}
			else if(data > s->data){
				s = s->right;
			}
			else{
				return true;
			}
		}
		return false;
	}
	//creat tree
	void creatTree(int* arr, int n) {
		for (int i = 0; i < n; i++) {
			
			insertNode(arr[i]);
		}
	}

	//print Pre
	void printTree() {
		if (root != nullptr) {
			PreOrder(root);
		}
		else
		{
			cout << "NULL";
		}
	}

	void deleteNodes(int* arr, int n) {
		for (int i = 0; i < n; i++) {
			deleteNode(arr[i]);
		}
	}

	void printMaxMin() {
		node* max = getMaxnode(root);
		node* min = getMinnode(root);
		cout << min->data << " " << max->data;
	}
};

int main() {
	RedBlackTree rb;
	RedBlackTree d_rb;
	int note[10000];
    for(int i = 0; i < 10000; i++){
        note[i] = 0;
    }
    srand((int) time (NULL));
    int count = 0;
    int data[1000];
    while(1){
        if(count == 15){
            break;
        }
        int temp = rand()%20 + 1;
        if(note[temp] == 0){
            data[count] = temp;
            note[temp] = 1;
            count++;
        }
        else{
            continue;
        }
    }
	for(int i = 0; i < 15; i++){
		cout << data[i] << " ";
	}
	cout << endl;
	rb.creatTree(data, 15);
	rb.printTree();
	cout << endl;
	if(rb.find_data(rb.root,3)){
		cout << "yes";
	}
	else{
		cout << "no";
	}
	//d_rb.deleteNodes(da,m);
	//d_rb.printTree();
	//cout << "success 3" << endl;
	return 0;
}