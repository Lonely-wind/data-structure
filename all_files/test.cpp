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

struct node
{
	int key;
	struct node* left;
	struct node* right;
};

//创建新节点
node* creatNode(int val) {
	node* root = new node();
	root->key = val;
	root->right = nullptr;
	root->left = nullptr;
	return root;
}

//插入
node* insertNode(node* root, int key) {
	if (root == nullptr) {
		return creatNode(key);
	}
	if (key < root->key) {
		root->left = insertNode(root->left, key);
	}
	else if (key > root->key)
	{
		root->right = insertNode(root->right, key);
	}
	return root;
}

//获取最小节点
node* getMinValue(node* root) {
	node* cur = root;
	while (cur->left != nullptr)
	{
		cur = cur->left;
	}
	return cur;
}

//删除节点
node* deleteNode(node* root, int key) {
	if (root == nullptr) {
		return root;
	}
	if (key < root->key) {
		root->left = deleteNode(root->left, key);
	}
	else if (key > root->key) {
		root->right = deleteNode(root->right, key);
	}
	else
	{
		//找到要删除的节点

		//节点只有一个字节点或者没有子节点的情况
		if (root->left == nullptr) {
			node* tem = root->right;
			delete root;
			return tem;
		}
		else if (root->right == nullptr) {
			node* temp = root->right;
			delete root;
			return temp;
		}

		//节点有两个子节点
		node* temp = getMinValue(root->right);
		root->key = temp->key;
		root->right = deleteNode(root->right, temp->key);
	}

	return root;
}

void Inorder(node* root) {
	if (root != nullptr) {
		Inorder(root->left);
		cout << root->key << " ";
		Inorder(root->right);
	}
}
int data1[4000005];
int main() {
	node* root = nullptr;
	for (int i = 0; i < 60000; i++) {
		data1[i] = i;
	}
	srand((int)time(NULL));
	//random_shuffle(data,data+400000);
	double time1 = 0;
	double count1s = 0;
	LARGE_INTEGER nFreq1;
	LARGE_INTEGER nBeginTime1;
	LARGE_INTEGER nEndTime1;
	QueryPerformanceFrequency(&nFreq1);
	QueryPerformanceCounter(&nBeginTime1);

	for (int i = 0; i < 60000; i++) {
		root = insertNode(root, data1[i]);
	}

	QueryPerformanceCounter(&nEndTime1);
	time1 = (double)(nEndTime1.QuadPart - nBeginTime1.QuadPart) / (double)nFreq1.QuadPart;
	cout << time1 * 1000 << endl;
	/*cout << "二叉树中序遍历结果：";
	Inorder(root);
	cout << endl;*/

	/*int m;
	cout << "请输入要删除的数目：";
	cin >> m;
	cout << "请输入要删除的数字：";
	for (int i = 0; i < m; i++) {
		int val;
		cin >> val;
		root = deleteNode(root, val);
	}
	cout << "删除节点后二叉树中序遍历结果：";
	Inorder(root);*/

	return 0;
}