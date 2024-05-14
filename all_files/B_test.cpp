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
const int ORDER = 512;  // B树的阶数

// B树节点
template <typename KeyType>
class BTreeNode {
public:
    bool is_leaf_;                  // 是否是叶节点
    std::vector<KeyType> keys_;     // 节点的关键字
    std::vector<BTreeNode*> children_;  // 子节点指针

    BTreeNode(bool is_leaf) : is_leaf_(is_leaf) {}

    // 查找关键字的索引
    int FindKeyIndex(const KeyType& key) const {
        int index = 0;
        while (index < keys_.size() && keys_[index] < key)
            ++index;
        return index;
    }

    // 插入关键字和子节点指针
    void InsertKeyAndChild(const KeyType& key, BTreeNode* child) {
        int index = FindKeyIndex(key);
        keys_.insert(keys_.begin() + index, key);
        children_.insert(children_.begin() + index + 1, child);
    }

    // 删除关键字和子节点指针
    void RemoveKeyAndChild(const KeyType& key, BTreeNode* child) {
        int index = FindKeyIndex(key);
        keys_.erase(keys_.begin() + index);
        children_.erase(children_.begin() + index + 1);
    }
};

// B树
template <typename KeyType>
class BTree {
public:
    BTree() : root_(new BTreeNode<KeyType>(true)) {}

    // 插入关键字
    void Insert(const KeyType& key) {
        BTreeNode<KeyType>* root = root_;
        if (root->keys_.size() == (2 * ORDER - 1)) {
            BTreeNode<KeyType>* new_root = new BTreeNode<KeyType>(false);
            new_root->children_.push_back(root_);
            root_ = new_root;
            SplitChild(new_root, 0);
            InsertNonFull(new_root, key);
        }
        else {
            InsertNonFull(root, key);
        }
    }

    // 删除关键字
    void Remove(const KeyType& key) {
        if (!root_) {
            std::cout << "B树为空，无法删除关键字" << std::endl;
            return;
        }
        RemoveKey(root_, key);
        if (root_->keys_.empty() && !root_->is_leaf_) {
            BTreeNode<KeyType>* old_root = root_;
            root_ = root_->children_[0];
            delete old_root;
        }
    }

    // 打印B树
    void Print() const {
        PrintNode(root_, 0);
    }
    
    int B_search(int k){
        int temp = root_->FindKeyIndex(k);
        return temp;
    }
public:
    BTreeNode<KeyType>* root_;

    // 在非满节点中插入关键字
    void InsertNonFull(BTreeNode<KeyType>* node, const KeyType& key) {
        int index = node->FindKeyIndex(key);
        if (node->is_leaf_) {
            node->keys_.insert(node->keys_.begin() + index, key);
        }
        else {
            BTreeNode<KeyType>* child = node->children_[index];
            if (child->keys_.size() == (2 * ORDER - 1)) {
                SplitChild(node, index);
                if (key > node->keys_[index])
                    ++index;
            }
            InsertNonFull(node->children_[index], key);
        }
    }

    // 分裂子节点
    void SplitChild(BTreeNode<KeyType>* parent, int child_index) {
        BTreeNode<KeyType>* child = parent->children_[child_index];
        BTreeNode<KeyType>* new_child = new BTreeNode<KeyType>(child->is_leaf_);
        parent->InsertKeyAndChild(child->keys_[ORDER - 1], new_child);
        for (int i = ORDER; i < child->keys_.size(); ++i)
            new_child->keys_.push_back(child->keys_[i]);
        child->keys_.resize(ORDER - 1);
        if (!child->is_leaf_) {
            for (int i = ORDER; i < child->children_.size(); ++i)
                new_child->children_.push_back(child->children_[i]);
            child->children_.resize(ORDER);
        }
    }

    // 删除关键字
    void RemoveKey(BTreeNode<KeyType>* node, const KeyType& key) {
        int index = node->FindKeyIndex(key);

        // 关键字在当前节点中
        if (index < node->keys_.size() && node->keys_[index] == key) {
            if (node->is_leaf_) {
                node->keys_.erase(node->keys_.begin() + index);
            }
            else {
                BTreeNode<KeyType>* pred_child = node->children_[index];
                BTreeNode<KeyType>* succ_child = node->children_[index + 1];

                // 如果前驱子节点至少包含ORDER个关键字
                if (pred_child->keys_.size() >= ORDER) {
                    KeyType pred_key = GetPredKey(pred_child, index);
                    RemoveKey(pred_child, pred_key);
                    node->keys_[index] = pred_key;
                }
                // 如果后继子节点至少包含ORDER个关键字
                else if (succ_child->keys_.size() >= ORDER) {
                    KeyType succ_key = GetSuccKey(succ_child, index);
                    RemoveKey(succ_child, succ_key);
                    node->keys_[index] = succ_key;
                }
                // 前驱子节点和后继子节点都只包含ORDER-1个关键字
                else {
                    MergeChildren(node, index);
                    RemoveKey(pred_child, key);
                }
            }
        }
        // 关键字不在当前节点中
        else {
            BTreeNode<KeyType>* child = node->children_[index];
            if (child->keys_.size() == ORDER - 1) {
                // 如果左兄弟节点至少包含ORDER个关键字
                if (index > 0 && node->children_[index - 1]->keys_.size() >= ORDER) {
                    ShiftFromRightSibling(node, index);
                }
                // 如果右兄弟节点至少包含ORDER个关键字
                else if (index < node->keys_.size() && node->children_[index + 1]->keys_.size() >= ORDER) {
                    ShiftFromLeftSibling(node, index);
                }
                // 左右兄弟节点都只包含ORDER-1个关键字
                else {
                    if (index > 0) {
                        MergeChildren(node, index - 1);
                        child = node->children_[index - 1];
                    }
                    else {
                        MergeChildren(node, index);
                    }
                }
            }
            RemoveKey(child, key);
        }
    }

    // 获取前驱关键字
    KeyType GetPredKey(BTreeNode<KeyType>* node, int child_index) const {
        BTreeNode<KeyType>* pred_child = node->children_[child_index];
        while (!pred_child->is_leaf_)
            pred_child = pred_child->children_.back();
        return pred_child->keys_.back();
    }

    // 获取后继关键字
    KeyType GetSuccKey(BTreeNode<KeyType>* node, int child_index) const {
        BTreeNode<KeyType>* succ_child = node->children_[child_index + 1];
        while (!succ_child->is_leaf_)
            succ_child = succ_child->children_.front();
        return succ_child->keys_.front();
    }

    // 从右兄弟节点移动关键字
    void ShiftFromRightSibling(BTreeNode<KeyType>* parent, int child_index) {
        BTreeNode<KeyType>* child = parent->children_[child_index];
        BTreeNode<KeyType>* right_sibling = parent->children_[child_index + 1];

        child->keys_.push_back(parent->keys_[child_index]);
        parent->keys_[child_index] = right_sibling->keys_.front();
        right_sibling->keys_.erase(right_sibling->keys_.begin());
        if (!right_sibling->is_leaf_) {
            child->children_.push_back(right_sibling->children_.front());
            right_sibling->children_.erase(right_sibling->children_.begin());
        }
    }

    // 从左兄弟节点移动关键字
    void ShiftFromLeftSibling(BTreeNode<KeyType>* parent, int child_index) {
        BTreeNode<KeyType>* child = parent->children_[child_index];
        BTreeNode<KeyType>* left_sibling = parent->children_[child_index - 1];

        child->keys_.insert(child->keys_.begin(), parent->keys_[child_index - 1]);
        parent->keys_[child_index - 1] = left_sibling->keys_.back();
        left_sibling->keys_.pop_back();
        if (!left_sibling->is_leaf_) {
            child->children_.insert(child->children_.begin(), left_sibling->children_.back());
            left_sibling->children_.pop_back();
        }
    }

    // 合并子节点
    void MergeChildren(BTreeNode<KeyType>* parent, int child_index) {
        BTreeNode<KeyType>* left_child = parent->children_[child_index];
        BTreeNode<KeyType>* right_child = parent->children_[child_index + 1];

        left_child->keys_.push_back(parent->keys_[child_index]);

        for (const KeyType& key : right_child->keys_)
            left_child->keys_.push_back(key);

        for (BTreeNode<KeyType>* child : right_child->children_)
            left_child->children_.push_back(child);

        parent->RemoveKeyAndChild(parent->keys_[child_index], right_child);
        delete right_child;
    }

    // 打印节点
    void PrintNode(const BTreeNode<KeyType>* node, int level) const {
        for (int i = 0; i < node->keys_.size(); ++i) {
            if (!node->is_leaf_)
                PrintNode(node->children_[i], level + 1);
            for (int j = 0; j < level; ++j)
                std::cout << "    ";
            std::cout << node->keys_[i] << std::endl;
        }
        if (!node->is_leaf_)
            PrintNode(node->children_.back(), level + 1);
    }
};
//int data[400005];
int main() {
    /*BTree<int> btree;
    for(int i = 0; i < 10000; i++){
        data[i]=i;
    }
    srand((int) time (NULL));
    random_shuffle(data,data+10000);*/
    // 插入关键字
    //cout << "请输入要插入的数字个数：";
    //cout << "请输入要插入的数字：" << std::endl;
    BTree<int> btree;
    int note[20000];
    for(int i = 0; i < 20000; i++){
        note[i] = 0;
    }
    srand((int) time (NULL));
    int count = 0;
    int data[20000];
    while(1){
        if(count == 10000){
            break;
        }
        int temp = rand()%10000 + 1;
        if(note[temp] == 0){
            data[count] = temp;
            note[temp] = 1;
            count++;
        }
        else{
            continue;
        }
    }
    /*for(int i = 0; i < 1000; i++){
        cout << data[i] << " ";
    }*/
    double time1 = 0;
	double count1s = 0;
	LARGE_INTEGER nFreq1;
	LARGE_INTEGER nBeginTime1;
	LARGE_INTEGER nEndTime1;
	QueryPerformanceFrequency(&nFreq1);
	QueryPerformanceCounter(&nBeginTime1);//开始计时

    for (int i = 0; i < 10000; i++) {
        int key = data[i];
        btree.Insert(key);
    }

    //插入B树时间

    QueryPerformanceCounter(&nEndTime1);//停止计时  
	time1 = (double)(nEndTime1.QuadPart - nBeginTime1.QuadPart) / (double)nFreq1.QuadPart;//计算程序执行时间单位为s  
	cout << "插入程序程序执行时间：" << time1 * 1000 << "ms" << endl;

    // 打印B树
    /*cout << "插入1000操作后的B树:" << std::endl;
    btree.Print();*/

    //删除操作

    double time = 0;
	double counts = 0;
	LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	LARGE_INTEGER nEndTime;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//开始计时
    for(int i = 0; i < 200; i++){
        int key = data[i];
        btree.Remove(key);
    }
    /*cout << "删除后的b树" << endl;
    btree.Print();*/

    QueryPerformanceCounter(&nEndTime);//停止计时  
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位为s  
	cout << "删除程序程序执行时间：" << time * 1000 << "ms" << endl;

    //// 删除关键字
    //int m;
    //std::cout << "请输入要删除的数字个数：";
    //std::cin >> m;
    //std::cout << "请输入要删除的数字：" << std::endl;
    //for (int i = 0; i < m; ++i) {
    //    int key;
    //    std::cin >> key;
    //    btree.Remove(key);
    //}

    //// 打印B树
    //std::cout << "删除操作后的B树：" << std::endl;
    //btree.Print();

    return 0;
}
