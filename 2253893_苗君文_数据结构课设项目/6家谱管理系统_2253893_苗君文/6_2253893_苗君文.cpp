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
    TreeNode* root, * current;//root为树的根节点，current为当前处理的节点
public:
    Tree() { root = current = NULL; }//构造函数
    void BuildRoot(string rootName);//用于建立树的根节点，并将其设置为当前节点
    int Root();//将根节点设置为当前节点
    int Parent();//将当前结点设置为其双亲节点
    int FirstChild();//将当前结点设置为其第一个孩子结点
    int NextSibling();//将当前节点设置为其下一个兄弟节点
    int FindParent(TreeNode* t, TreeNode* p);//在以t为根的树中找到p的双亲节点
    int Find(string target);//在整个树中找到姓名为target的节点，并将其设置为当前节点
    int IsEmpty();//检查树是否为空
    int Find(TreeNode* p, string target);//在以p为根的树中找到姓名为target的节点，并将其设置为当前结点
    void DisplayChildren();//显示第一代子孙
    void InsertChild(string childName);//给当前结点添加孩子
    void DeleteSubtree(TreeNode* node);//删除子树
    void Menu();//菜单，供用户选择不同的操作
};

void Tree::BuildRoot(string rootName) 
{
    root = current = new TreeNode(rootName, NULL, NULL);
}

int Tree::Root() 
{
    if (root == NULL) {
        current = NULL;
        return 0;//返回值为0，则表示没有根节点
    }
    else {
        current = root;
        return 1;//返回值为1，则表示设置成功
    }
}

int Tree::Parent() 
{
    TreeNode* p = current, * t;
    if (current == NULL || current == root) {
        current = NULL;
        return 0;//如果当前结点为空或者是根节点，则无父母，返回0
    }
    t = root;
    int k = FindParent(t, p);//调用函数查找双亲节点
    return k;//返回查找结果，1则成功，0则失败
}

int Tree::FirstChild() 
{
    if (current != NULL && current->firstChild != NULL) {
        current = current->firstChild;
        return 1;//成功，当前节点已经是第一个孩子
    }
    current = NULL;
    return 0;//失败，因为当前节点为空或者没有孩子节点
}

int Tree::NextSibling() {
    if (current != NULL && current->nextSibling != NULL) {
        current = current->nextSibling;
        return 1;//成功，当前结点已移动到下一个兄弟节点
    }
    current = NULL;
    return 0;//失败
}

int Tree::FindParent(TreeNode* t, TreeNode* p) {
    TreeNode* q = t->firstChild;//q指向长子
    while (q != NULL && q != p) {
        if (int i = FindParent(q, p) != 0)
            return i;
        q = q->nextSibling;
    }
    if (q != NULL && q == p) {
        current = t;
        return 1;//找到双亲节点，设置当前节点，返回1
    }
    else
        return 0;//未找到双亲节点，当前结点不变，返回0
}

int Tree::Find(string target) {
    if (IsEmpty())
        return 0;//如果树为空，则返回0
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
        result = 1;//找到了
        current = p;//设置当前结点为找到的结点
    }
    else {
        TreeNode* q = p->firstChild;//获取结点p的长子
        while (q != NULL && !(result = Find(q, target)))
            q = q->nextSibling;
    }
    return result;
}

void Tree::DisplayChildren(){
    if (current->firstChild == NULL) {
        cout << current->name << "无子孙。" << endl;
        return;
    }
    cout << current->name << "的第一代子孙是：";
    FirstChild();//将current移到当前的长子
    while (current != NULL) {
        cout << current->name << "  ";
        current = current->nextSibling;
    }
    cout << endl;
}

void Tree::InsertChild(string childName) {
    TreeNode* newNode = new TreeNode(childName);
    if (current->firstChild == NULL) {
        //如果当前节点没有孩子，将新节点设为当前节点的长子
        current->firstChild = newNode;
    }
    else {
        //如果当前节点已有孩子，找到最后一个孩子并将新节点插入到其后
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
        DeleteSubtree(child);//递归删除当前结点的孩子
        delete child;
        child = nextSibling;//移动到下一个孩子
    }
    node->firstChild = NULL;
}

void Tree::Menu() {
    //标语
    cout << "**                  家谱管理系统                  **" << endl;
    cout << "====================================================" << endl;
    cout << "**               请选择要执行的操作：             **" << endl;
    cout << "**                 A --- 完善家谱                 **" << endl;
    cout << "**                 B --- 添加家庭成员             **" << endl;
    cout << "**                 C --- 解散局部家庭             **" << endl;
    cout << "**                 D --- 更改家庭成员姓名         **" << endl;
    cout << "**                 E --- 查询家庭成员             **" << endl;
    cout << "**                 F --- 退出程序                 **" << endl;
    cout << "====================================================" << endl;

    cout << "首先建立一个家谱！" << endl;
    cout << "请输入祖先的姓名：";
    string ancName;//祖先姓名
    cin >> ancName;
    cin.clear();
    cin.ignore(9999, '\n');
    BuildRoot(ancName);
    cout << "此家谱的祖先是：" << root->name << endl;

    while (1) {
        char choice;
        while (1) {
            cout << endl;
            cout << "请选择要执行的操作：";
            cin >> choice;
            char c;
            if (cin.fail() || (choice != 'a' && choice != 'A' && choice != 'b' && choice != 'B' && choice != 'c' && choice != 'C' && choice != 'd' && choice != 'D' && choice != 'e' && choice != 'E' && choice != 'f' && choice != 'F')) {
                cout << "输入无效，请重新输入。" << endl;
                cin.clear();
                cin.ignore(9999, '\n');
                continue;
            }  //内容错误
            else if (cin.get(c) && c != '\n') {
                cout << "输入无效，请重新输入。" << endl;
                cin.clear();
                cin.ignore(9999, '\n');
                continue;
            }  //个数错误
            else
                break;
        }

        if (choice == 'A' || choice == 'a') {
            //完善家谱
            cout << "请输入要建立家庭的人的姓名：";
            string builderName;
            cin >> builderName;
            cin.clear();
            cin.ignore(9999, '\n');
            if (!Find(builderName)) {
                cout << builderName << "不存在于家谱中，无法为其建立家庭。" << endl;
                continue;
            }  //判断该人是否已在家谱中
            if (current->firstChild != NULL) {
                cout << builderName << "已建立过家庭。" << endl;
                continue;
            }  //此人已建立过家庭，不必再建立
            int childNum;
            while (1) {
                cout << "请输入" << builderName << "的儿女人数：";
                char c;  //用来获取输入一个数之后的一个字符，若获取一个字符且非换行符则视为输入错误。
                cin >> childNum;
                if (cin.fail() || childNum < 1 || childNum > 50) {
                    cout << "输入错误，请重新输入。" << endl;
                    cin.clear();
                    cin.ignore(9999, '\n');
                    continue;
                }  //内容错误
                else if (cin.get(c) && c != '\n') {
                    cout << "输入错误，请重新输入。" << endl;
                    cin.clear();
                    cin.ignore(9999, '\n');
                    continue;
                }  //个数错误
                else
                    break;
            }//输入儿女个数，并处理输入错误
            cout << "请依次输入" << builderName << "的儿女的姓名：";
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
            //添加家庭成员
            cout << "请输入要添加儿子（或女儿）的人的姓名：";
            string adderName;
            cin >> adderName;
            cin.clear();
            cin.ignore(9999, '\n');
            if (!Find(adderName)) {
                cout << adderName << "不存在于家谱中，无法为其添加子女。" << endl;
                continue;
            }//判断此人是否已在家谱中
            cout << "请输入要添加儿子（或女儿）的姓名：";
            string childName;
            cin >> childName;
            cin.clear();
            cin.ignore(9999, '\n');
            InsertChild(childName);
            DisplayChildren();
        }
        else if (choice == 'C' || choice == 'c') {
            //解散局部家庭
            cout << "请输入要解散家庭的人的姓名：";
            string disName;
            cin >> disName;
            cin.clear();
            cin.ignore(9999, '\n');
            if (!Find(disName)) {
                cout << disName << "不存在于家谱中，无法为其解散家庭。" << endl;
                continue;
            }
            if (current->firstChild == NULL) {
                cout << disName << "无子孙，无需解散家庭。" << endl;
                continue;
            }
            cout << "要解散家庭的人是：" << disName << endl;
            DisplayChildren();
            Find(disName);
            DeleteSubtree(current);
            cout << disName << "的家庭已解散。" << endl;
            DisplayChildren();
        }
        else if (choice == 'D' || choice == 'd') {
            //更改家庭成员姓名
            cout << "请输入要更改姓名的人的目前姓名：";
            string preName;
            cin >> preName;
            cin.clear();
            cin.ignore(9999, '\n');
            if (!Find(preName)) {
                cout << preName << "不存在于家谱中，无法更改。" << endl;
                continue;
            }
            cout << "请输入更改后的姓名：";
            string postName;
            cin >> postName;
            cin.clear();
            cin.ignore(9999, '\n');
            if (postName == preName) {
                cout << "此姓名与原姓名相同，无需更改。" << endl;
                continue;
            }
            current->name = postName;
            cout << preName << "已更名为" << postName << endl;
        }
        else if (choice == 'E' || choice == 'e') {
            //查询家庭成员
            cout << "请输入要查询家庭成员的人的姓名：";
            string findName;
            cin >> findName;
            cin.clear();
            cin.ignore(9999, '\n');
            if (!Find(findName)) {
                cout << findName << "不存在于家谱中，无法查询。" << endl;
                continue;
            }
            DisplayChildren();
        }
        else if (choice == 'F' || choice == 'f') {
            //退出程序
            cout << "已退出，欢迎下次使用！" << endl;
            break;
        }
    }

}

int main() {
    Tree myTree;
    myTree.Menu();
    return 0;
}
