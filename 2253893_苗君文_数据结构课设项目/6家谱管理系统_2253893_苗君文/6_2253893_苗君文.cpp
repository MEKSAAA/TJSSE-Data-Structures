#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

class Tree;
class TreeNode {
    friend class Tree;
private:
    string name;
    TreeNode* firstChild, * nextSibling;
    TreeNode(string n = "", TreeNode* fc = NULL, TreeNode* ns = NULL) : name(n), firstChild(fc), nextSibling(ns) {}
};

class Tree {
private:
    TreeNode* root, * current;//rootΪ���ĸ��ڵ㣬currentΪ��ǰ����Ľڵ�
public:
    Tree() { root = current = NULL; }//���캯��
    void BuildRoot(string rootName);//���ڽ������ĸ��ڵ㣬����������Ϊ��ǰ�ڵ�
    int Root();//�����ڵ�����Ϊ��ǰ�ڵ�
    int Parent();//����ǰ�������Ϊ��˫�׽ڵ�
    int FirstChild();//����ǰ�������Ϊ���һ�����ӽ��
    int NextSibling();//����ǰ�ڵ�����Ϊ����һ���ֵܽڵ�
    int FindParent(TreeNode* t, TreeNode* p);//����tΪ���������ҵ�p��˫�׽ڵ�
    int Find(string target);//�����������ҵ�����Ϊtarget�Ľڵ㣬����������Ϊ��ǰ�ڵ�
    int IsEmpty();//������Ƿ�Ϊ��
    int Find(TreeNode* p, string target);//����pΪ���������ҵ�����Ϊtarget�Ľڵ㣬����������Ϊ��ǰ���
    void DisplayChildren();//��ʾ��һ������
    void InsertChild(string childName);//����ǰ�����Ӻ���
    void DeleteSubtree(TreeNode* node);//ɾ������
    void Menu();//�˵������û�ѡ��ͬ�Ĳ���
};

void Tree::BuildRoot(string rootName) 
{
    root = current = new TreeNode(rootName, NULL, NULL);
}

int Tree::Root() 
{
    if (root == NULL) {
        current = NULL;
        return 0;//����ֵΪ0�����ʾû�и��ڵ�
    }
    else {
        current = root;
        return 1;//����ֵΪ1�����ʾ���óɹ�
    }
}

int Tree::Parent() 
{
    TreeNode* p = current, * t;
    if (current == NULL || current == root) {
        current = NULL;
        return 0;//�����ǰ���Ϊ�ջ����Ǹ��ڵ㣬���޸�ĸ������0
    }
    t = root;
    int k = FindParent(t, p);//���ú�������˫�׽ڵ�
    return k;//���ز��ҽ����1��ɹ���0��ʧ��
}

int Tree::FirstChild() 
{
    if (current != NULL && current->firstChild != NULL) {
        current = current->firstChild;
        return 1;//�ɹ�����ǰ�ڵ��Ѿ��ǵ�һ������
    }
    current = NULL;
    return 0;//ʧ�ܣ���Ϊ��ǰ�ڵ�Ϊ�ջ���û�к��ӽڵ�
}

int Tree::NextSibling() {
    if (current != NULL && current->nextSibling != NULL) {
        current = current->nextSibling;
        return 1;//�ɹ�����ǰ������ƶ�����һ���ֵܽڵ�
    }
    current = NULL;
    return 0;//ʧ��
}

int Tree::FindParent(TreeNode* t, TreeNode* p) {
    TreeNode* q = t->firstChild;//qָ����
    while (q != NULL && q != p) {
        if (int i = FindParent(q, p) != 0)
            return i;
        q = q->nextSibling;
    }
    if (q != NULL && q == p) {
        current = t;
        return 1;//�ҵ�˫�׽ڵ㣬���õ�ǰ�ڵ㣬����1
    }
    else
        return 0;//δ�ҵ�˫�׽ڵ㣬��ǰ��㲻�䣬����0
}

int Tree::Find(string target) {
    if (IsEmpty())
        return 0;//�����Ϊ�գ��򷵻�0
    return Find(root, target);
}

int Tree::IsEmpty() {
    if (root == NULL)
        return 1;
    else
        return 0;
}

int Tree::Find(TreeNode* p, string target) {
    int result = 0;
    if (p->name == target) {
        result = 1;//�ҵ���
        current = p;//���õ�ǰ���Ϊ�ҵ��Ľ��
    }
    else {
        TreeNode* q = p->firstChild;//��ȡ���p�ĳ���
        while (q != NULL && !(result = Find(q, target)))
            q = q->nextSibling;
    }
    return result;
}

void Tree::DisplayChildren(){
    if (current->firstChild == NULL) {
        cout << current->name << "�����" << endl;
        return;
    }
    cout << current->name << "�ĵ�һ�������ǣ�";
    FirstChild();//��current�Ƶ���ǰ�ĳ���
    while (current != NULL) {
        cout << current->name << "  ";
        current = current->nextSibling;
    }
    cout << endl;
}

void Tree::InsertChild(string childName) {
    TreeNode* newNode = new TreeNode(childName);
    if (current->firstChild == NULL) {
        //�����ǰ�ڵ�û�к��ӣ����½ڵ���Ϊ��ǰ�ڵ�ĳ���
        current->firstChild = newNode;
    }
    else {
        //�����ǰ�ڵ����к��ӣ��ҵ����һ�����Ӳ����½ڵ���뵽���
        TreeNode* temp = current->firstChild;
        while (temp->nextSibling != NULL) {
            temp = temp->nextSibling;
        }
        temp->nextSibling = newNode;
    }
}

void Tree::DeleteSubtree(TreeNode* node){
    if (node == NULL)
        return;
    TreeNode* child = node->firstChild;
    while (child != NULL) {
        TreeNode* nextSibling = child->nextSibling;
        DeleteSubtree(child);//�ݹ�ɾ����ǰ���ĺ���
        delete child;
        child = nextSibling;//�ƶ�����һ������
    }
    node->firstChild = NULL;
}

void Tree::Menu() {
    //����
    cout << "**                  ���׹���ϵͳ                  **" << endl;
    cout << "====================================================" << endl;
    cout << "**               ��ѡ��Ҫִ�еĲ�����             **" << endl;
    cout << "**                 A --- ���Ƽ���                 **" << endl;
    cout << "**                 B --- ��Ӽ�ͥ��Ա             **" << endl;
    cout << "**                 C --- ��ɢ�ֲ���ͥ             **" << endl;
    cout << "**                 D --- ���ļ�ͥ��Ա����         **" << endl;
    cout << "**                 E --- ��ѯ��ͥ��Ա             **" << endl;
    cout << "**                 F --- �˳�����                 **" << endl;
    cout << "====================================================" << endl;

    cout << "���Ƚ���һ�����ף�" << endl;
    cout << "���������ȵ�������";
    string ancName;//��������
    cin >> ancName;
    cin.clear();
    cin.ignore(9999, '\n');
    BuildRoot(ancName);
    cout << "�˼��׵������ǣ�" << root->name << endl;

    while (1) {
        char choice;
        while (1) {
            cout << endl;
            cout << "��ѡ��Ҫִ�еĲ�����";
            cin >> choice;
            char c;
            if (cin.fail() || (choice != 'a' && choice != 'A' && choice != 'b' && choice != 'B' && choice != 'c' && choice != 'C' && choice != 'd' && choice != 'D' && choice != 'e' && choice != 'E' && choice != 'f' && choice != 'F')) {
                cout << "������Ч�����������롣" << endl;
                cin.clear();
                cin.ignore(9999, '\n');
                continue;
            }  //���ݴ���
            else if (cin.get(c) && c != '\n') {
                cout << "������Ч�����������롣" << endl;
                cin.clear();
                cin.ignore(9999, '\n');
                continue;
            }  //��������
            else
                break;
        }

        if (choice == 'A' || choice == 'a') {
            //���Ƽ���
            cout << "������Ҫ������ͥ���˵�������";
            string builderName;
            cin >> builderName;
            cin.clear();
            cin.ignore(9999, '\n');
            if (!Find(builderName)) {
                cout << builderName << "�������ڼ����У��޷�Ϊ�佨����ͥ��" << endl;
                continue;
            }  //�жϸ����Ƿ����ڼ�����
            if (current->firstChild != NULL) {
                cout << builderName << "�ѽ�������ͥ��" << endl;
                continue;
            }  //�����ѽ�������ͥ�������ٽ���
            int childNum;
            while (1) {
                cout << "������" << builderName << "�Ķ�Ů������";
                char c;  //������ȡ����һ����֮���һ���ַ�������ȡһ���ַ��ҷǻ��з�����Ϊ�������
                cin >> childNum;
                if (cin.fail() || childNum < 1 || childNum > 50) {
                    cout << "����������������롣" << endl;
                    cin.clear();
                    cin.ignore(9999, '\n');
                    continue;
                }  //���ݴ���
                else if (cin.get(c) && c != '\n') {
                    cout << "����������������롣" << endl;
                    cin.clear();
                    cin.ignore(9999, '\n');
                    continue;
                }  //��������
                else
                    break;
            }//�����Ů�������������������
            cout << "����������" << builderName << "�Ķ�Ů��������";
            for (int i = 0;i < childNum;i++) {
                string childName;
                cin >> childName;
                InsertChild(childName);
            }
            cin.clear();
            cin.ignore(9999, '\n');
            DisplayChildren();
        }
        else if (choice == 'B' || choice == 'b') {
            //��Ӽ�ͥ��Ա
            cout << "������Ҫ��Ӷ��ӣ���Ů�������˵�������";
            string adderName;
            cin >> adderName;
            cin.clear();
            cin.ignore(9999, '\n');
            if (!Find(adderName)) {
                cout << adderName << "�������ڼ����У��޷�Ϊ�������Ů��" << endl;
                continue;
            }//�жϴ����Ƿ����ڼ�����
            cout << "������Ҫ��Ӷ��ӣ���Ů������������";
            string childName;
            cin >> childName;
            cin.clear();
            cin.ignore(9999, '\n');
            InsertChild(childName);
            DisplayChildren();
        }
        else if (choice == 'C' || choice == 'c') {
            //��ɢ�ֲ���ͥ
            cout << "������Ҫ��ɢ��ͥ���˵�������";
            string disName;
            cin >> disName;
            cin.clear();
            cin.ignore(9999, '\n');
            if (!Find(disName)) {
                cout << disName << "�������ڼ����У��޷�Ϊ���ɢ��ͥ��" << endl;
                continue;
            }
            if (current->firstChild == NULL) {
                cout << disName << "����������ɢ��ͥ��" << endl;
                continue;
            }
            cout << "Ҫ��ɢ��ͥ�����ǣ�" << disName << endl;
            DisplayChildren();
            Find(disName);
            DeleteSubtree(current);
            cout << disName << "�ļ�ͥ�ѽ�ɢ��" << endl;
            DisplayChildren();
        }
        else if (choice == 'D' || choice == 'd') {
            //���ļ�ͥ��Ա����
            cout << "������Ҫ�����������˵�Ŀǰ������";
            string preName;
            cin >> preName;
            cin.clear();
            cin.ignore(9999, '\n');
            if (!Find(preName)) {
                cout << preName << "�������ڼ����У��޷����ġ�" << endl;
                continue;
            }
            cout << "��������ĺ��������";
            string postName;
            cin >> postName;
            cin.clear();
            cin.ignore(9999, '\n');
            if (postName == preName) {
                cout << "��������ԭ������ͬ��������ġ�" << endl;
                continue;
            }
            current->name = postName;
            cout << preName << "�Ѹ���Ϊ" << postName << endl;
        }
        else if (choice == 'E' || choice == 'e') {
            //��ѯ��ͥ��Ա
            cout << "������Ҫ��ѯ��ͥ��Ա���˵�������";
            string findName;
            cin >> findName;
            cin.clear();
            cin.ignore(9999, '\n');
            if (!Find(findName)) {
                cout << findName << "�������ڼ����У��޷���ѯ��" << endl;
                continue;
            }
            DisplayChildren();
        }
        else if (choice == 'F' || choice == 'f') {
            //�˳�����
            cout << "���˳�����ӭ�´�ʹ�ã�" << endl;
            break;
        }
    }

}

int main() {
    Tree myTree;
    myTree.Menu();
    return 0;
}
