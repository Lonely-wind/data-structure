#include<iostream>
#include<stack>
#include<vector>
#include<queue>
#include<algorithm>
#include<time.h>
#include<windows.h>
using namespace std;

struct node {
	int val;
	node* left;
	node* right;
};

int geth(node* root) {
	if (root == NULL)return 0;
	else return max(geth(root->left), geth(root->right)) + 1;
}
int bf(node* root) {
	if (root == NULL)return 0;
	else return geth(root->left) - geth(root->right);
}
node* ll(node* root) {
	node* left = root->left;
	root->left = left->right;
	left->right = root;
	return left;
}
node* rr(node* root) {
	node* right = root->right;
	root->right = right->left;
	right->left = root;
	return right;
}
node* lr(node* root) {
	root->left = rr(root->left);//此步是保留当前节点父节点操作
	return ll(root);
}
node* rl(node* root) {
	root->right = ll(root->right);
	return rr(root);
}
node* insert(node* root, int key) {
	if (root == NULL) {
		root = new node;
		root->val = key;
		root->left = root->right = NULL;
	}
	else if (root->val == key);
	else {
		if (key < root->val) {
			root->left = insert(root->left, key);
			if (bf(root) == 2) {
				if (key < root->left->val) root = ll(root);
				else root = lr(root);
			}
		}
		else {
			root->right = insert(root->right, key);
			if (bf(root) == -2) {
				if (key > root->right->val) root = rr(root);
				else root = rl(root);
			}
		}
	}
	return root;
}
void shuchu(node* root) {
	node* p;
	vector<int>num;
	queue<node*> q;//这里用队列而非栈，因为其是先入先出的
	bool flag = false, flag2 = false;

	q.push(root);
	while (!q.empty()) {
		p = q.front();
		num.push_back(p->val);
		if (p->left != NULL) {
			q.push(p->left);
			if (flag)flag2 = true;
		}
		else flag = true;
		if (p->right != NULL) {
			q.push(p->right);
			if (flag)flag2 = true;
		}
		else flag = true;
		q.pop();
	}
	for (int i = 0; i < num.size() - 1; i++)
		cout << num[i] << " ";
	cout << num[num.size() - 1] << endl;
	if (flag2)cout << "No";
	else cout << "Yes";
}//层序输出
bool remove(node* root, int key) {
	stack<node*>st;
	node* parent = NULL, * q = NULL, * p = root;//这里的root是形参
	node* ppr;
	int flag;
	while (p != NULL) {
		if (p->val == key)break;
		parent = p;
		st.push(parent);
		if (key < p->val)p = p->left;
		else if (key > p->val)p = p->right;
	}
	if (p == NULL)return false;
	if (p->right != NULL && p->left != NULL) {
		parent = p;
		st.push(parent);
		q = p->left;
		while (q->right != NULL) {
			parent = q;
			st.push(parent);
			q = q->right;
		}
		p->val = q->val;
		p = q;
	}
	if (p->left != NULL)q = p->left;
	else q = p->right;
	if (parent == NULL)root = q;
	else {
		if (parent->left == p)parent->left = q;
		else parent->right = q;
		while (!st.empty()) {
			parent = st.top();
			st.pop();
			flag = -1;
			if (!st.empty()) {
				ppr = st.top();
				if (ppr->left == parent)flag = 0;
				else flag = 1;
			}
			if (bf(parent) == 1 || bf(parent) == -1)break;
			else if (bf(parent) == 0);
			else if (bf(parent) == 2) {
				if (bf(parent->left) == 1) {
					if (flag == 1)ppr->right = ll(parent);
					else if (flag == 0)ppr->left = ll(parent);
					else if (flag == -1)root = ll(parent);
				}
				else if (bf(parent->left) == -1) {
					if (flag == 1)ppr->right = lr(parent);
					else if (flag == 0)ppr->left = lr(parent);
					else if (flag == -1)root = lr(parent);
				}
			}
			else if (bf(parent) == -2) {
				if (bf(parent->right) == -1) {
					if (flag == 1)ppr->right = rr(parent);
					else if (flag == 0) ppr->left = rr(parent);
					else if (flag == -1)root = rr(parent);
				}
				else if (bf(parent->right) == 1) {
					if (flag == 1)ppr->right = rl(parent);
					else if (flag == 0)ppr->left = rl(parent);
					else if (flag == -1)root = rl(parent);
				}
			}
		}
	}
	return true;
}
bool search(int value, node* root) {
	if (root == NULL)return false;
	node* cur = root;
	while (cur) {
		if (value < cur->val)
			cur = cur->left;
		else if (value > cur->val)
			cur = cur->right;
		else break;
	}
	if (cur == NULL)return false;
	return true;
}

int n;
int x[400005],bx[400005],rx[400005];
int s[1005];
int rs[1005];
int data[400005];
int main() {
	node* root = NULL;
	for(int i = 0; i < 400000; i++){
        data[i]=i;
    }
    srand((int) time (NULL));
    //random_shuffle(data,data+40000);

    cout << endl;

	double time1 = 0;
	double count1s = 0;
	LARGE_INTEGER nFreq1;
	LARGE_INTEGER nBeginTime1;
	LARGE_INTEGER nEndTime1;
	QueryPerformanceFrequency(&nFreq1);
	QueryPerformanceCounter(&nBeginTime1);

	for (int i = 0; i < 400000; i++) {
		insert(root,data[i]);
	}

	QueryPerformanceCounter(&nEndTime1); 
	time1 = (double)(nEndTime1.QuadPart - nBeginTime1.QuadPart) / (double)nFreq1.QuadPart; 
	cout << time1 * 1000 << endl;

	random_shuffle(data,data+400000);
    double time2 = 0;
	double count2s = 0;
	LARGE_INTEGER nFreq2;
	LARGE_INTEGER nBeginTime2;
	LARGE_INTEGER nEndTime2;
    QueryPerformanceFrequency(&nFreq2);
	QueryPerformanceCounter(&nBeginTime2);

	double count_search = 0;


	for (int i = 0; i < 1000; i++){
		search(data[i],root);
	}

	
    QueryPerformanceCounter(&nEndTime2);
	time2 = (double)(nEndTime2.QuadPart - nBeginTime2.QuadPart) / (double)nFreq2.QuadPart; 
	cout << time2 * 1000 << endl;
    
    /*end = clock();
	cout << "random search:" << double(end - start) << "ms" << endl;*/



	/*start = clock();
	for (int i = 1; i <= 1000; i++)
		a.remove(s[i]);
	end = clock();
	cout << "random remove:" << double(end - start) << "ms" << endl;


	sort(s + 1, s + 1001);
	for (int i = 1; i <= 1000; i++)
		a.insert(s[i]);*/
	//random_shuffle(x + 1, x + n + 1);


	/*start = clock();*/

    //删除代码

    double time3 = 0;
	double count3s = 0;
	LARGE_INTEGER nFreq3;
	LARGE_INTEGER nBeginTime3;
	LARGE_INTEGER nEndTime3;
    QueryPerformanceFrequency(&nFreq3);
	QueryPerformanceCounter(&nBeginTime3);

	/*for (int i = 0; i < 1000; i++)
		remove(root,data[i]);
	*/
	for (int i = 1000; i > 0; i--)
		remove(root,data[i]);
	

    QueryPerformanceCounter(&nEndTime3);
	time3 = (double)(nEndTime3.QuadPart - nBeginTime3.QuadPart) / (double)nFreq3.QuadPart; 
	cout << time3 * 1000 << endl;
    
	/*end = clock();
	cout << "random remove:" << double(end - start) << "ms" << endl;*/

	/*for (int i = 1; i <= n; i++) {
		insert(root, x[i]);
	}*/

	/*start = clock();
	for (int i = 1; i <= n; i++)
		remove(root, bx[i]);
	end = clock();
	cout << "back order remove:" << double(end - start) << "ms" << endl;*/

}