#include<iostream>
#include<cstdio>
#include<algorithm>
#include<ctime>
#include<random>
#include<windows.h>
#include<stdlib.h>
#include<limits.h>
#include<vector>
using namespace std;
template <class E>
struct BSTNode
{
    E data;
    BSTNode<E> *left, *right;
    BSTNode() : left(nullptr), right(nullptr) {}
    BSTNode(const E d, BSTNode<E> *L = nullptr, BSTNode<E> *R = nullptr) : data(d), left(L), right(R) {}
    ~BSTNode() {}
    void setData(E d) { data = d; }
    E getData() { return data; }
};

template <class E>
class BST
{
public:
    BST() : root(nullptr), size(0) {}
    BST(const BST<E> &R);
    BST(E *Eles, int sz);
    ~BST() { makeEmpty(); };
    size_t Size() { return size; }
    bool Search(const E x) const
    {
        return (Search(x, root) != nullptr) ? true : false;
    }
    BST<E> &operator=(const BST<E> &R);
    void makeEmpty()
    {
        makeEmpty(root);
        root = nullptr;
        size = 0;
    }
    void PrintTree()
    {
        int level = -1;
        PrintTree(root, level);
    };
    E Min()
    {
        if (root == nullptr)
        {
            cerr << "BST is empty." << endl;
            exit(-1);
        }
        return Min(root)->data;
    }
    E Max()
    {
        if (root == nullptr)
        {
            cerr << "BST is empty." << endl;
            exit(-1);
        }
        return Max(root)->data;
    }
    bool Insert(const E &el) { return Insert(el, root); }
    bool Remove(const E x) { return Remove(x, root); }
    E *GetSeq(); //将二叉搜索树中所有结点按升序排列，返回到seq中
private:
    size_t size;
    BSTNode<E> *root;                                     //二叉搜索树根节点                                      //输入停止标志，用于输入
    BSTNode<E> *Search(const E x, BSTNode<E> *ptr) const; //递归：搜索
    void makeEmpty(BSTNode<E> *&ptr);                     //递归：置空
    void PrintTree(BSTNode<E> *ptr, int level) const;     //递归：打印
    BSTNode<E> *Copy(const BSTNode<E> *ptr) const;        //递归：复制
    BSTNode<E> *Min(BSTNode<E> *ptr) const;               //递归：求最小
    BSTNode<E> *Max(BSTNode<E> *ptr) const;               //递归：求最大
    bool Insert(const E &el, BSTNode<E> *&ptr);           //递归：插入
    bool Remove(const E x, BSTNode<E> *&ptr);             //递归：删除
    void GetSeq(E *x, int &cnt, BSTNode<E> *&ptr);
};

//建立二叉搜索树
template <class E>
BST<E>::BST(E *Eles, int sz)
{
    //输入一个元素序列，建立一棵二叉搜索树
    E x;
    root = nullptr;
    size = 0;
    for (int i = 0; i < sz; i++)
    {
        x = Eles[i];
        Insert(x, root);
    }
}

template <class E>
BSTNode<E> *BST<E>::Search(const E x, BSTNode<E> *ptr) const
{
    //私有递归函数，在以ptr为根的二叉搜索树中搜索含x的结点。若找到，则函数返回该结点的地址，否则返回nullptr。
    if (ptr == nullptr)
        return nullptr;
    else if (x < ptr->data)
        return Search(x, ptr->left);
    else if (x > ptr->data)
        return Search(x, ptr->right);
    else
        return ptr;
}

template <class E>
bool BST<E>::Insert(const E &el, BSTNode<E> *&ptr)
{
    if (ptr == nullptr)
    {
        ptr = new BSTNode<E>(el);
        if (ptr == nullptr)
        {
            cerr << "Out of space." << endl;
            exit(-1);
        }
        size += 1;
        return true;
    }
    else if (el < ptr->data)
        return Insert(el, ptr->left);
    else if (el > ptr->data)
        return Insert(el, ptr->right);
    else
        return false; //值相等，插入失败
    return true;
}

template <class E>
bool BST<E>::Remove(const E x, BSTNode<E> *&ptr)
{
    BSTNode<E> *temp;
    if (ptr != nullptr)
    {
        if (x < ptr->data)
            Remove(x, ptr->left);
        else if (x > ptr->data)
            Remove(x, ptr->right);
        else if (ptr->left != nullptr && ptr->right != nullptr)
        {
            temp = ptr->right;
            while (temp->left != nullptr)
                temp = temp->left;
            ptr->data = temp->data;
            Remove(ptr->data, ptr->right);
        }
        else
        {
            temp = ptr;
            if (ptr->left == nullptr)
                ptr = ptr->right;
            else
                ptr = ptr->left;
            delete temp;
            size -= 1;
            return true;
        }
    }
    return false;
}

template <class E>
void BST<E>::makeEmpty(BSTNode<E> *&ptr)
{
    if (ptr == nullptr)
        return;
    if (ptr->left != nullptr)
    {
        makeEmpty(ptr->left);
    }
    else if (ptr->right != nullptr)
    {
        makeEmpty(ptr->right);
    }
    delete ptr;
    ptr = nullptr;
    return;
}

template <class E>
void BST<E>::PrintTree(BSTNode<E> *ptr, int level) const
{
    if (ptr == nullptr)
    {
        return;
    }

    level++;
    PrintTree(ptr->right, level);
    level--;

    level++;
    for (int i = 0; i < level; i++)
        cout << "\t";
    cout << ptr->data << endl;
    PrintTree(ptr->left, level);
    level--;
}

template <class E>
BST<E>::BST(const BST<E> &R)
{
    if (this != &R)
    {
        this->root = R.Copy(R.root);
        this->size = R.size;
    }
}
template <class E>
BST<E> &BST<E>::operator=(const BST<E> &R)
{
    if (this != &R)
    {
        this->makeEmpty(); //防止内存泄漏，先释放原来的空间
        this->root = R.Copy(R.root);
        this->size = R.size;
    }
    return *this;
}
template <class E>
BSTNode<E> *BST<E>::Copy(const BSTNode<E> *ptr) const
{
    if (ptr == nullptr)
        return nullptr;
    BSTNode<E> *ret = new BSTNode<E>(ptr->data);
    ret->left = Copy(ptr->left);
    ret->right = Copy(ptr->right);
    return ret;
}

template <class E>
BSTNode<E> *BST<E>::Min(BSTNode<E> *ptr) const
{
    if (ptr->left != nullptr)
        return Min(ptr->left);
    return ptr;
}

template <class E>
BSTNode<E> *BST<E>::Max(BSTNode<E> *ptr) const
{
    if (ptr->right != nullptr)
        return Max(ptr->right);
    return ptr;
}

template <class E>
E *BST<E>::GetSeq()
{
    E *seq = new E(size);
    int cnt = 0;
    GetSeq(seq, cnt, root);
    return seq;
}

template <class E>
void BST<E>::GetSeq(E *x, int &cnt, BSTNode<E> *&ptr)
{
    if (ptr == nullptr || cnt >= size)
        return;
    GetSeq(x, cnt, ptr->left);
    E e = ptr->data;
    x[cnt] = e;
    cnt++;
    GetSeq(x, cnt, ptr->right);
}
int data[400005];
int main(){
    for(int i = 0; i < 80000; i++){
        data[i]=i;
    }
    srand((int) time (NULL));
    random_shuffle(data,data+80000);
    double time1 = 0;
	double count1s = 0;
	LARGE_INTEGER nFreq1;
	LARGE_INTEGER nBeginTime1;
	LARGE_INTEGER nEndTime1;
	QueryPerformanceFrequency(&nFreq1);
	QueryPerformanceCounter(&nBeginTime1);//开始计时
    
    BST<int> bst(data,80000);

    QueryPerformanceCounter(&nEndTime1);//停止计时  
	time1 = (double)(nEndTime1.QuadPart - nBeginTime1.QuadPart) / (double)nFreq1.QuadPart;//计算程序执行时间单位为s  
	cout << time1 * 1000  << endl;

    random_shuffle(data,data+80000);

    double time2 = 0;
	double count2s = 0;
	LARGE_INTEGER nFreq2;
	LARGE_INTEGER nBeginTime2;
	LARGE_INTEGER nEndTime2;
    QueryPerformanceFrequency(&nFreq2);
	QueryPerformanceCounter(&nBeginTime2);

    for(int i = 0; i < 1000; i++){
        bst.Search(data[i]);
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

	for (int i = 0; i < 1000; i++)
		bst.Remove(data[i]);
	
	/*for(int i = 999; i >= 0; i--)
		bst.Remove(data[i]);*/
    QueryPerformanceCounter(&nEndTime3);
	time3 = (double)(nEndTime3.QuadPart - nBeginTime3.QuadPart) / (double)nFreq3.QuadPart; 
	cout << time3 * 1000 << endl;



}