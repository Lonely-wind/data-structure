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
enum Color { r, b };

class node {
public:
	int key;
	Color color;
	node* left, * right, * parent;
	node(int _key, Color c, node* l, node* r, node* p) :key(_key), color(c), right(r), left(l), parent(p) {};
};

class rbtree {
public:
	node* rbroot;
	rbtree() {
		rbroot = NULL;
	}
	void ll(node*& root) {
		node* left = root->left;
		Color temp = root->color;
		root->color = left->color;
		left->color = temp;
		root->left = left->right;
		if (left->right)
			left->right->parent = root;
		left->parent = root->parent;
		if (root->parent == NULL)
			rbroot = left;
		else if (root == root->parent->left)
			root->parent->left = left;
		else root->parent->right = left;
		left->right = root;
		root->parent = left;
	}//特殊情况涉及到根节点
	void rr(node*& root) {
		node* right = root->right;
		Color temp = root->color;
		root->color = right->color;
		right->color = temp;
		root->right = right->left;
		if (right->left)
			right->left->parent = root;
		right->parent = root->parent;
		if (root->parent == NULL)
			rbroot = right;
		else if (root == root->parent->right)
			root->parent->right = right;
		else root->parent->left = right;
		right->left = root;
		root->parent = right;
	}
	void insert(int value) {
		if (rbroot == NULL) {
			rbroot = new node(value, b, NULL, NULL, NULL);
			return;
		}
		node* cur = rbroot, * parent = NULL;
		while (cur) {
			parent = cur;
			if (value < cur->key)
				cur = cur->left;
			else if (value == cur->key)
				return;
			else cur = cur->right;
		}
		node* newnode = new node(value, r, NULL, NULL, NULL);
		if (value < parent->key)
			parent->left = newnode;
		else parent->right = newnode;
		newnode->parent = parent;
		cur = newnode;
		while ((parent = cur->parent) && parent->color == r) {
			node* ppr = parent->parent;
			if (ppr->left == parent) {
				node* uncle = ppr->right;
				if (uncle && uncle->color == r) {
					uncle->color = parent->color = b;
					ppr->color = r;
					cur = ppr;
					continue;
				}
				if (cur == parent->left) {
					ll(ppr);
					break;
				}
				else if (cur == parent->right) {
					rr(parent);
					ll(ppr);
					break;
				}
			}
			if (ppr->right == parent) {
				node* uncle = ppr->left;
				if (uncle && uncle->color == r) {
					uncle->color = parent->color = b;
					ppr->color = r;
					cur = ppr;
					continue;
				}
				if (cur == parent->right) {
					rr(ppr);
					break;
				}
				else if (cur == parent->left) {
					ll(parent);
					rr(ppr);
					break;
				}
			}
			rbroot->color = b;
		}
		rbroot->color = b;
	}
	void remove(int value) {
		node* tmp = rbroot;
		while (tmp) {
			if (value < tmp->key)
				tmp = tmp->left;
			else if (value > tmp->key)
				tmp = tmp->right;
			else break;
		}
		if (tmp == NULL)return;
		removenode(tmp);
	}
	void removenode(node* nod) {
		Color tcolor = b;
		if (nod->left && nod->right) {
			node* tmp = nod->right;
			while (tmp->left)tmp = tmp->left;
			nod->key = tmp->key;
			if (tmp->parent == nod)nod->right = tmp->right;
			else tmp->parent->left = tmp->right;
			if (tmp->right)tmp->right->parent = tmp->parent;
			tcolor = tmp->color;
			if (tcolor == b)removefix(tmp->right, tmp->parent);
			delete tmp;
			return;
		}
		else if (nod->left) {
			if (nod->parent == NULL) {
				rbroot = nod->left;
				nod->left->parent = NULL;
			}
			else {
				if (nod = nod->parent->left)nod->parent->left = nod->left;
				else nod->parent->right = nod->left;
				if (nod->left)nod->left->parent = nod->parent;
				tcolor = nod->color;
			}
			if (tcolor == b)removefix(nod->left, nod->parent);
			delete nod;
		}
		else {
			if (nod->parent == NULL) {
				rbroot = nod->right;
				if (nod->right)nod->right->parent = NULL;
			}
			else {
				if (nod == nod->parent->left)nod->parent->left = nod->right;
				else nod->parent->right = nod->right;
				if (nod->right)nod->right->parent = nod->parent;
				tcolor = nod->color;
			}
			if (tcolor == b)removefix(nod->right, nod->parent);
			delete nod;
		}
	}
	void removefix(node* nod, node* parent) {
		node* bro;
		while ((!nod || nod->color == b) && nod != rbroot) {
			if (nod == parent->left) {
				bro = parent->right;
				if (bro->color == r) {
					rr(parent);
					bro = parent->right;
				}
				if ((!bro->left || bro->left->color == b) && (!bro->right || bro->right->color == b)) {
					bro->color = r;
					nod = parent;
					parent = nod->parent;
				}
				else {
					if (!bro->right || bro->right->color == b) {
						ll(bro);
						bro = parent->right;
					}
					bro->right->color = b;
					rr(parent);
					nod = rbroot;
					break;
				}
			}
			else {
				bro = parent->left;
				if (bro->color == r) {
					ll(parent);
					bro = parent->left;
				}
				if ((!bro->left || bro->left->color == b) && (!bro->right || bro->right->color == b)) {
					bro->color = r;
					nod = parent;
					parent = nod->parent;
				}
				else {
					if (!bro->left || bro->left->color == b) {
						rr(bro);
						bro = parent->left;
					}
					bro->left->color = b;
					ll(parent);
					nod = rbroot;
					break;
				}
			}
		}
		if (nod)nod->color = b;
	}
	bool search(int value) {
		if (rbroot == NULL)return false;
		node* cur = rbroot;
		while (cur) {
			if (value < cur->key)
				cur = cur->left;
			else if (value > cur->key)
				cur = cur->right;
			else break;
		}
		if (cur == NULL)return false;
		return true;
	}
};
void preorder(node* root) {
	if (root == NULL)
		return;
	cout << root->key;
	if (root->color == r)cout << "(R) ";
	else cout << "(B) ";
	preorder(root->left);
	preorder(root->right);
}
void maxmin(node* root) {
	if (root == NULL)
		return;
	node* max = root, * pmax = NULL, * min = root, * pmin = NULL;
	while (max) {
		pmax = max;
		max = max->right;
	}
	while (min) {
		pmin = min;
		min = min->left;
	}
	cout << pmin->key << " ";
	cout << pmax->key;
}

int n;
int x[400005], bx[400005], rx[400005];
int s[1005];
int rs[1005];
int note[400005];
int data[400005];
int main() {
	//freopen("1.out","w",stdout);
	rbtree a;
	/*int m;
	cin >> m;
	n = m * 10000;
	cout << "RBT random:" << endl;


	FILE* fp;
	fp = freopen("random.txt", "r", stdin);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &x[i]);
	}
	fclose(fp);

	fp = freopen("random1000.txt", "r", stdin);
	for (int i = 0; i <= 1000; i++)
		scanf("%d", &s[i]);
	fclose(fp);*/

    /*for(int i = 0; i < 400000; i++){
        note[i] = 0;
    }
    srand((int) time (NULL));
    int count = 0,cnt=0,maxx=0;
    while(1){
        if(count == 400000){
            break;
        }
		if(++cnt>4000000){
			
			cout<<rand()<<" "<<maxx;
			return 0;
		}
		//cout << count << " ";
        int temp = rand()%400000 + 1;
		maxx=max(maxx,temp);
		//cout<<temp<<" "<<note[temp]<<" "<<count<<endl;
        if(note[temp] == 0){
            data[count] = temp;
            note[temp] = 1;
            count++;
        }
        else{
            continue;
        }
		
    }
	*/
	for(int i = 0; i < 400000; i++){
        data[i]=i;
    }
    srand((int) time (NULL));
	//random_shuffle(data,data+280000);
    /*for(int i = 0; i < 400000; i++){
        cout << data[i] << " ";
    }*/

	//cout << n << endl;

    double time1 = 0;
	double count1s = 0;
	LARGE_INTEGER nFreq1;
	LARGE_INTEGER nBeginTime1;
	LARGE_INTEGER nEndTime1;
	QueryPerformanceFrequency(&nFreq1);
	QueryPerformanceCounter(&nBeginTime1);

	for (int i = 0; i < 400000; i++) {
		a.insert(data[i]);
	}
 
    QueryPerformanceCounter(&nEndTime1);//停�?��?�时  
	time1 = (double)(nEndTime1.QuadPart - nBeginTime1.QuadPart) / (double)nFreq1.QuadPart;//计算程序执�?�时间单位为s  
	cout << time1 * 1000 << endl;

    //preorder(a.rbroot);
	//random_shuffle(data,data+400000);
    double time2 = 0;
	double count2s = 0;
	LARGE_INTEGER nFreq2;
	LARGE_INTEGER nBeginTime2;
	LARGE_INTEGER nEndTime2;
    QueryPerformanceFrequency(&nFreq2);
	QueryPerformanceCounter(&nBeginTime2);

	//random_shuffle(data,data+ 400000);

	for (int i = 0; i < 1000; i++){
		a.search(data[i]);
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

	/*for (int i = 0; i < 1000; i++){
		a.remove(data[i]);
	}*/
	
	for(int i = 1000; i >= 0; i--)
		a.remove(data[i]);
    QueryPerformanceCounter(&nEndTime3);
	time3 = (double)(nEndTime3.QuadPart - nBeginTime3.QuadPart) / (double)nFreq3.QuadPart; 
	cout << time3 * 1000 << endl;

	/*for (int i = n; i>=1; i--) {
		a.insert(x[i]);
	}

	start = clock();
	for (int i = 1; i <= n; i++)
		a.remove(x[i]);
	end = clock();
	cout << "backorder remove:" << double(end - start) << "ms" << endl;*/

	return 0;
}