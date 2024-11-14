#include<iostream>
using namespace std;

#define MAX_NUM 10000000

template<class K>
struct BSTNode {
    K key;
    BSTNode<K>* left, * right;
    BSTNode() { left = NULL;right = NULL; }
    BSTNode(K x) { key = x;left = right = NULL; }
    ~BSTNode(){}
};

template<class K>
class BST {
private:
    BSTNode<K>* root;
    void printBSTree(BSTNode<K>* t);
    void InOrder(BSTNode<K>* ptr);
public:
    BST() { root = NULL; }
    ~BST() {};
    BSTNode<K>* Search(K x, BSTNode<K>*& pr);//搜索x
    void createBSTree(K v[], int n);//创建
    void printBSTree() { printBSTree(root); }//输出
    bool Insert(K x);//插入新元素
    bool Remove(K& x);//删除含有x的结点
    void InOrder() { InOrder(root); }//中序遍历
    bool IsEmpty() { return root == NULL; }
    void clearSubtree(BSTNode<K>* node);
    void clearTree() { clearSubtree(root);root = NULL; }
};

template<class K>
void BST<K>::printBSTree(BSTNode<K>* t)
{
    if (t != NULL) {
        printBSTree(t->left);
        cout << t->key << " ";
        printBSTree(t->right);
    }
}

template<class K>
void BST<K>::InOrder(BSTNode<K>* ptr)
{
    if (ptr != NULL) {
        InOrder(ptr->left);
        cout << ptr->key << " ";
        InOrder(ptr->right);
    }
}

template<class K>
BSTNode<K>* BST<K>::Search(K x, BSTNode<K>*& pr)
{
    BSTNode<K>* p = root;
    pr = NULL;//pr是查找节点的父节点
    while (p != NULL) {
        if (p->key == x)
            return p;
        else {
            pr = p;
            if (x < p->key)
                p = p->left;
            else
                p = p->right;
        }
    }
    return p;//找到则返回找到结点的地址，pr返回它的父节点地址；否则返回NULL，pr返回x应插入节点的位置
}

template<class K>
void BST<K>::createBSTree(K v[], int n)
{
    root = NULL;
    for (int i = 0;i < n;i++)
        Insert(v[i]);
}

template<class K>
bool BST<K>::Insert(K x)
{
    BSTNode<K>* s, * p, * pr;
    p = Search(x, pr);
    if (p != NULL)
        return false;//搜索成功，不插入
    s = new BSTNode<K>(x);
    if (root == NULL)
        root = s;//空数，新节点为根节点
    else if (x < pr->key)
        pr->left = s;
    else
        pr->right = s;
    return true;
}

template<class K>
bool BST<K>::Remove(K& x)
{
    BSTNode<K>* s, * p, * pr;
    p = Search(x, pr);
    if (p == NULL)
        return false;//搜索失败，不删除
    if (p->left != NULL && p->right != NULL) {
        s = p->right;
        pr = p;
        while (s->left != NULL) {
            pr = s;
            s = s->left;
        }
        p->key = s->key;
        p = s;
    }
    if (p->right == NULL)
        s = p->left;//左子树非空，记下左子女
    else
        s = p->right;//否则记下右子女（可能空）
    if (p == root)
        root = s;//被删结点为根节点
    else if (pr->left == p)
        pr->left = s;//父节点直接连接子女节点
    else
        pr->right = s;
    delete p;//释放被删节点
    return true;
}

template<class K>
void BST<K>::clearSubtree(BSTNode<K>* node)
{
    if (node) {
        clearSubtree(node->left);
        clearSubtree(node->right);
        delete node;
    }
}

void dealInputError(int& n, string str, int min = 0, int max = 1)  //处理输入错误
{
    while (1) {
        char c;  //用来获取输入一个数之后的一个字符，若获取一个字符且非换行符则视为输入错误。
        cout << str;
        cin >> n;
        if (cin.fail() || n<min || n>max) {
            cout << "输入错误，请重新输入。" << endl;
            cin.clear();
            cin.ignore(9999999, '\n');
            continue;
        }  //内容错误
        else if (cin.get(c) && c != '\n') {
            cout << "输入错误，请重新输入。" << endl;
            cin.clear();
            cin.ignore(9999999, '\n');
            continue;
        }  //个数错误
        else
            break;
    }
    return;
}

int main()
{
    cout << "**                   二叉排序树                   **" << endl;
    cout << "====================================================" << endl;
    cout << "**                 1 --- 建立二叉排序树           **" << endl;
    cout << "**                 2 --- 插入元素                 **" << endl;
    cout << "**                 3 --- 查询元素                 **" << endl;
    cout << "**                 4 --- 删除元素                 **" << endl;
    cout << "**                 5 --- 退出程序                 **" << endl;
    cout << "====================================================" << endl;

    BST<int>bst;
    while (1) {
        int choice;
        cout << endl;
        dealInputError(choice, "请选择操作：", 1, 5);
        cout << endl;
        if (choice == 1) {
            //建立二叉排序树
            if (!bst.IsEmpty()) {
                cout << "二叉排序树已建立，请选择其他操作！" << endl;
                continue;
            }
            int n;
            dealInputError(n, "请输入关键码的个数：", 1, MAX_NUM);
            int* keys = new int[n];
            cout << "请输入关键码以创建二叉排序树：" << endl;
            while (1) {
                bool judge = 0;//判断是否需要重新输入关键码
                for (int i = 0;i < n;i++) {
                    cin >> keys[i];
                    if (cin.fail() || keys[i] < 0 || keys[i] >= MAX_NUM) {
                        cout << "输入非法，请重新输入所有关键码：" << endl;
                        cin.clear();
                        cin.ignore(9999999, '\n');
                        bst.clearTree();
                        judge = 1;
                        break;
                    }
                    if (!bst.Insert(keys[i])) {
                        cout << "输入的关键码（" << keys[i] << "）已在树中！" << endl;
                    }
                }
                if (judge)
                    continue;
                char c;
                if (cin.get(c) && c != '\n') {
                    cout << "输入的关键码个数超出，请重新输入所有关键码：" << endl;
                    cin.clear();
                    cin.ignore(9999999, '\n');
                    bst.clearTree();
                    continue;
                }
                else
                    break;
            }
            delete[]keys;
            cout << "当前二叉排序树为：" << endl;
            bst.printBSTree();
            cout << endl;
            continue;
        }
        else if (choice == 2) {
            //插入元素
            int key;
            dealInputError(key,"请输入将插入元素的关键码：",0, MAX_NUM);
            if (!bst.Insert(key)) {
                cout<< "输入的关键码（" << key << "）已在树中！" << endl;
            }
            else {
                cout << "插入元素成功！" << endl;
            }
            cout << "当前二叉排序树为：" << endl;
            bst.printBSTree();
            cout << endl;
            continue;
        }
        else if (choice == 3) {
            //查询元素
            int key;
            dealInputError(key, "请输入要查询的元素的关键码：", 0, MAX_NUM);
            BSTNode<int>* pr;
            BSTNode<int>* result = bst.Search(key, pr);
            if (result)
                cout << "关键码查找成功！" << endl;
            else
                cout << "关键码不存在于树中，查询失败。" << endl;
            continue;
        }
        else if (choice == 4) {
            //删除元素
            int key;
            dealInputError(key, "请输入要删除的元素的关键码：", 0, MAX_NUM);
            if (bst.Remove(key))
                cout << "删除成功！" << endl;
            else
                cout << "关键码不存在于树中，删除失败。" << endl;
            cout << "当前二叉排序树为：" << endl;
            bst.printBSTree();
            cout << endl;
            continue;
        }
        else if (choice == 5) {
            //退出程序
            cout << "已退出，欢迎下次使用！" << endl;
            break;
        }
    }
    return 0;
}
