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
    BSTNode<K>* Search(K x, BSTNode<K>*& pr);//����x
    void createBSTree(K v[], int n);//����
    void printBSTree() { printBSTree(root); }//���
    bool Insert(K x);//������Ԫ��
    bool Remove(K& x);//ɾ������x�Ľ��
    void InOrder() { InOrder(root); }//�������
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
    pr = NULL;//pr�ǲ��ҽڵ�ĸ��ڵ�
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
    return p;//�ҵ��򷵻��ҵ����ĵ�ַ��pr�������ĸ��ڵ��ַ�����򷵻�NULL��pr����xӦ����ڵ��λ��
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
        return false;//�����ɹ���������
    s = new BSTNode<K>(x);
    if (root == NULL)
        root = s;//�������½ڵ�Ϊ���ڵ�
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
        return false;//����ʧ�ܣ���ɾ��
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
        s = p->left;//�������ǿգ���������Ů
    else
        s = p->right;//�����������Ů�����ܿգ�
    if (p == root)
        root = s;//��ɾ���Ϊ���ڵ�
    else if (pr->left == p)
        pr->left = s;//���ڵ�ֱ��������Ů�ڵ�
    else
        pr->right = s;
    delete p;//�ͷű�ɾ�ڵ�
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

void dealInputError(int& n, string str, int min = 0, int max = 1)  //�����������
{
    while (1) {
        char c;  //������ȡ����һ����֮���һ���ַ�������ȡһ���ַ��ҷǻ��з�����Ϊ�������
        cout << str;
        cin >> n;
        if (cin.fail() || n<min || n>max) {
            cout << "����������������롣" << endl;
            cin.clear();
            cin.ignore(9999999, '\n');
            continue;
        }  //���ݴ���
        else if (cin.get(c) && c != '\n') {
            cout << "����������������롣" << endl;
            cin.clear();
            cin.ignore(9999999, '\n');
            continue;
        }  //��������
        else
            break;
    }
    return;
}

int main()
{
    cout << "**                   ����������                   **" << endl;
    cout << "====================================================" << endl;
    cout << "**                 1 --- ��������������           **" << endl;
    cout << "**                 2 --- ����Ԫ��                 **" << endl;
    cout << "**                 3 --- ��ѯԪ��                 **" << endl;
    cout << "**                 4 --- ɾ��Ԫ��                 **" << endl;
    cout << "**                 5 --- �˳�����                 **" << endl;
    cout << "====================================================" << endl;

    BST<int>bst;
    while (1) {
        int choice;
        cout << endl;
        dealInputError(choice, "��ѡ�������", 1, 5);
        cout << endl;
        if (choice == 1) {
            //��������������
            if (!bst.IsEmpty()) {
                cout << "�����������ѽ�������ѡ������������" << endl;
                continue;
            }
            int n;
            dealInputError(n, "������ؼ���ĸ�����", 1, MAX_NUM);
            int* keys = new int[n];
            cout << "������ؼ����Դ���������������" << endl;
            while (1) {
                bool judge = 0;//�ж��Ƿ���Ҫ��������ؼ���
                for (int i = 0;i < n;i++) {
                    cin >> keys[i];
                    if (cin.fail() || keys[i] < 0 || keys[i] >= MAX_NUM) {
                        cout << "����Ƿ����������������йؼ��룺" << endl;
                        cin.clear();
                        cin.ignore(9999999, '\n');
                        bst.clearTree();
                        judge = 1;
                        break;
                    }
                    if (!bst.Insert(keys[i])) {
                        cout << "����Ĺؼ��루" << keys[i] << "���������У�" << endl;
                    }
                }
                if (judge)
                    continue;
                char c;
                if (cin.get(c) && c != '\n') {
                    cout << "����Ĺؼ�������������������������йؼ��룺" << endl;
                    cin.clear();
                    cin.ignore(9999999, '\n');
                    bst.clearTree();
                    continue;
                }
                else
                    break;
            }
            delete[]keys;
            cout << "��ǰ����������Ϊ��" << endl;
            bst.printBSTree();
            cout << endl;
            continue;
        }
        else if (choice == 2) {
            //����Ԫ��
            int key;
            dealInputError(key,"�����뽫����Ԫ�صĹؼ��룺",0, MAX_NUM);
            if (!bst.Insert(key)) {
                cout<< "����Ĺؼ��루" << key << "���������У�" << endl;
            }
            else {
                cout << "����Ԫ�سɹ���" << endl;
            }
            cout << "��ǰ����������Ϊ��" << endl;
            bst.printBSTree();
            cout << endl;
            continue;
        }
        else if (choice == 3) {
            //��ѯԪ��
            int key;
            dealInputError(key, "������Ҫ��ѯ��Ԫ�صĹؼ��룺", 0, MAX_NUM);
            BSTNode<int>* pr;
            BSTNode<int>* result = bst.Search(key, pr);
            if (result)
                cout << "�ؼ�����ҳɹ���" << endl;
            else
                cout << "�ؼ��벻���������У���ѯʧ�ܡ�" << endl;
            continue;
        }
        else if (choice == 4) {
            //ɾ��Ԫ��
            int key;
            dealInputError(key, "������Ҫɾ����Ԫ�صĹؼ��룺", 0, MAX_NUM);
            if (bst.Remove(key))
                cout << "ɾ���ɹ���" << endl;
            else
                cout << "�ؼ��벻���������У�ɾ��ʧ�ܡ�" << endl;
            cout << "��ǰ����������Ϊ��" << endl;
            bst.printBSTree();
            cout << endl;
            continue;
        }
        else if (choice == 5) {
            //�˳�����
            cout << "���˳�����ӭ�´�ʹ�ã�" << endl;
            break;
        }
    }
    return 0;
}
