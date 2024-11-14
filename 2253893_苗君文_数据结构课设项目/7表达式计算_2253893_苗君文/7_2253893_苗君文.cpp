#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

template <class Type>class Stack;

template <class Type>
class StackNode {
    friend class Stack<Type>;

private:
    Type data;
    StackNode<Type>* link;

    StackNode(Type d = 0, StackNode<Type>* l = NULL) : data(d), link(l) {}
};

template <class Type>
class Stack {
private:
    StackNode<Type>* top;

public:
    Stack() : top(NULL) {}
    ~Stack();
    void Push(const Type& item);
    Type Pop();
    Type GetTop() const;
    void MakeEmpty();
    int IsEmpty() const { return top == NULL; }
};

template <class Type>
Stack<Type>::~Stack() {
    StackNode<Type>* p;
    while (top != NULL) {
        p = top;
        top = top->link;
        delete p;
    }
}

template <class Type>
void Stack<Type>::Push(const Type& item) {
    top = new StackNode<Type>(item, top);
}

template <class Type>
Type Stack<Type>::Pop() {
    if (!IsEmpty()) {
        StackNode<Type>* p = top;
        Type retvalue = p->data;
        top = top->link;
        delete p;
        return retvalue;
    }
    return Type();  // 默认构造一个 Type 类型的对象返回
}

template <class Type>
Type Stack<Type>::GetTop() const {
    if (!IsEmpty()) {
        return top->data;
    }
    return Type();  // 默认构造一个 Type 类型的对象返回
}

template <class Type>
void Stack<Type>::MakeEmpty() {
    while (!IsEmpty()) {
        Pop();
    }
}

template<class Type>class BinaryTree;

template <class Type>
class BinTreeNode {
    friend class BinaryTree<Type>;

private:
    BinTreeNode<Type>* leftChild;
    BinTreeNode<Type>* rightChild;
    Type data;

public:
    BinTreeNode() : leftChild(NULL), rightChild(NULL) {}
    BinTreeNode(Type item, BinTreeNode<Type>* left = NULL, BinTreeNode<Type>* right = NULL) : data(item), leftChild(left), rightChild(right) {}

    Type GetData() const { return data; }
    BinTreeNode<Type>* GetLeft() const { return leftChild; }
    BinTreeNode<Type>* GetRight() const { return rightChild; }

    void SetData(const Type& item) { data = item; }
    void SetLeft(BinTreeNode<Type>* L) { leftChild = L; }
    void SetRight(BinTreeNode<Type>* R) { rightChild = R; }
};

template <class Type>
class BinaryTree {
public:
    BinaryTree() : root(NULL), RefValue(0) {}
    ~BinaryTree() { Destroy(root); }

    int IsEmpty() { return root == NULL ? 1 : 0; }
    int Insert(const Type& item);
    int Find(const Type& item) const;
    Type GetData() const;
    const BinTreeNode<Type>* GetRoot() const { return root; }
    bool IsValidExpression(const char* expression) const;
    void BuildExpressionTree(const char* expression);
    void PrintExpressions() const;
    void PreOrderTraversal(BinTreeNode<Type>* current, ostream& out) const;
    void InOrderTraversal(BinTreeNode<Type>* current, ostream& out) const;
    void PostOrderTraversal(BinTreeNode<Type>* current, ostream& out) const;
private:
    BinTreeNode<Type>* root;
    Type RefValue;

    BinTreeNode<Type>* Parent(BinTreeNode<Type>* start, BinTreeNode<Type>* current);
    int Insert(BinTreeNode<Type>*& current, const Type& item);
    void Destroy(BinTreeNode<Type>* current);
    int Find(BinTreeNode<Type>* current, const Type& item) const;

    int GetPrecedence(char op) const;
    void PrintPolishExpression(BinTreeNode<Type>* current) const;
};

template <class Type>
BinTreeNode<Type>* BinaryTree<Type>::Parent(BinTreeNode<Type>* start, BinTreeNode<Type>* current) {
    if (start == NULL)
        return NULL;
    if (start->GetLeft() == current || start->GetRight() == current)
        return start;
    BinTreeNode<Type>* p;
    if ((p = Parent(start->GetLeft(), current)) != NULL)
        return p;
    else
        return Parent(start->GetRight(), current);
}

template <class Type>
void BinaryTree<Type>::Destroy(BinTreeNode<Type>* current) {
    if (current != NULL) {
        Destroy(current->GetLeft());
        Destroy(current->GetRight());
        delete current;
    }
}

template <class Type>
int BinaryTree<Type>::Insert(const Type& item) {
    return Insert(root, item);
}

template <class Type>
int BinaryTree<Type>::Insert(BinTreeNode<Type>*& current, const Type& item) {
    if (current == NULL) {
        current = new BinTreeNode<Type>(item);
        return 1;
    }
    if (item <= current->GetData()) {
        return Insert(current->GetLeft(), item);
    }
    else {
        return Insert(current->GetRight(), item);
    }
}

template <class Type>
int BinaryTree<Type>::Find(const Type& item) const {
    return Find(root, item);
}

template <class Type>
int BinaryTree<Type>::Find(BinTreeNode<Type>* current, const Type& item) const {
    if (current == NULL)
        return 0;
    if (item == current->GetData())
        return 1;
    if (item < current->GetData())
        return Find(current->GetLeft(), item);
    else
        return Find(current->GetRight(), item);
}

template <class Type>
Type BinaryTree<Type>::GetData() const {
    if (root != NULL)
        return root->GetData();
    return Type();  // 默认构造一个 Type 类型的对象返回
}

template <class Type>
bool BinaryTree<Type>::IsValidExpression(const char* expression) const {
    Stack<char> parenthesesStack;

    for (int i = 0; expression[i] != '\0'; ++i) {
        if (i == 0 && (expression[i] == '*' || expression[i] == '/'))
            return false;
        if (expression[i]!='\0'&&expression[i + 1] == '\0' && expression[i] != ')' && !(expression[i] >= '0' && expression[i] <= '9'))
            return false;
        if (i > 0  && expression[i] == '(' && expression[i-1] != '+' && expression[i-1] != '-' && expression[i-1] != '*' && expression[i-1] != '/'&& expression[i - 1] != '(')
            return false;
        if (expression[i+1] != '\0' && expression[i] == ')' && expression[i + 1] != '+' && expression[i + 1] != '-' && expression[i + 1] != '*' && expression[i + 1] != '/' && expression[i + 1] != ')')
            return false;
        if (expression[i]>='0'&& expression[i]<='9') {
        }
        else if (expression[i] == '(') {
            parenthesesStack.Push('(');
        }
        else if (expression[i] == ')') {
            if (parenthesesStack.IsEmpty()) {
                return false;
            }
            else {
                parenthesesStack.Pop();
            }
        }
        else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
        }
        else {
            return false;
        }
        if (i > 0 && expression[i] >= '0' && expression[i] <= '9' && expression[i - 1] >= '0' && expression[i] <= '9')
            return false;
    }

    return parenthesesStack.IsEmpty();
}

template <class Type>
void BinaryTree<Type>::BuildExpressionTree(const char* expression) {
    Stack<BinTreeNode<Type>*> nodeStack;
    Stack<char> opStack;

    for (int i = 0; expression[i] != '\0'; ++i) {
        if (isdigit(expression[i])) {
            BinTreeNode<Type>* operand = new BinTreeNode<Type>(expression[i]);
            nodeStack.Push(operand);
        }
        else if (expression[i] == '(') {
            opStack.Push('(');
        }
        else if (expression[i] == ')') {
            while (!opStack.IsEmpty() && opStack.GetTop() != '(') {
                BinTreeNode<Type>* op = new BinTreeNode<Type>(opStack.Pop());
                op->SetRight(nodeStack.Pop());
                op->SetLeft(nodeStack.Pop());
                nodeStack.Push(op);
            }
            opStack.Pop();  // Pop '('
        }
        else {  // Operator
            while (!opStack.IsEmpty() && GetPrecedence(opStack.GetTop()) >= GetPrecedence(expression[i])) {
                BinTreeNode<Type>* op = new BinTreeNode<Type>(opStack.Pop());
                op->SetRight(nodeStack.Pop());
                op->SetLeft(nodeStack.Pop());
                nodeStack.Push(op);
            }
            opStack.Push(expression[i]);
        }
    }

    while (!opStack.IsEmpty()) {
        BinTreeNode<Type>* op = new BinTreeNode<Type>(opStack.Pop());
        op->SetRight(nodeStack.Pop());
        op->SetLeft(nodeStack.Pop());
        nodeStack.Push(op);
    }

    root = nodeStack.Pop();
}

template <class Type>
void BinaryTree<Type>::PrintExpressions() const {
    cout << "中缀表达式:       ";
    InOrderTraversal(root, cout);
    cout << endl;

    cout << "逆波兰表达式:     ";
    PostOrderTraversal(root, cout);
    cout << endl;

    cout << "波兰表达式:       ";
    PreOrderTraversal(root, cout);
    cout << endl;
}

template <class Type>
void BinaryTree<Type>::PreOrderTraversal(BinTreeNode<Type>* current, ostream& out) const {
    if (current != NULL) {
        out << current->GetData() << " ";
        PreOrderTraversal(current->GetLeft(), out);
        PreOrderTraversal(current->GetRight(), out);
    }
}

template <class Type>
void BinaryTree<Type>::InOrderTraversal(BinTreeNode<Type>* current, ostream& out) const {
    if (current != NULL) {
        InOrderTraversal(current->GetLeft(), out);
        out << current->GetData() << " ";
        InOrderTraversal(current->GetRight(), out);
    }
}

template <class Type>
void BinaryTree<Type>::PostOrderTraversal(BinTreeNode<Type>* current, ostream& out) const {
    if (current != NULL) {
        PostOrderTraversal(current->GetLeft(), out);
        PostOrderTraversal(current->GetRight(), out);
        out << current->GetData() << " ";
    }
}

template <class Type>
int BinaryTree<Type>::GetPrecedence(char op) const {
    if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '*' || op == '/') {
        return 2;
    }
    return 0;  // 如果是其他字符，返回 0
}

template <class Type>
void BinaryTree<Type>::PrintPolishExpression(BinTreeNode<Type>* current) const {
    if (current != NULL) {
        cout << current->GetData() << " ";
        PrintPolishExpression(current->GetLeft());
        PrintPolishExpression(current->GetRight());
    }
}

int main() {
    while (1) {
        BinaryTree<char> expressionTree;

        // 用户输入中缀表达式
        cout << "请输入表达式(数字均为个位数): ";
        char infixExpression[100];  // 假设表达式不超过 100 个字符
        cin >> infixExpression;
        cin.clear();
        cin.ignore(9999, '\n');

        if (!expressionTree.IsValidExpression(infixExpression)) {
            cout << "表达式不合法，请重新输入。" << endl;
            continue;
        }

        // 构建表达式树
        expressionTree.BuildExpressionTree(infixExpression);

        // 输出各种表达式
        expressionTree.PrintExpressions();

        //判断是否继续运行程序
        char answer;
        while (1) {
            cout << endl << "是否继续运行该程序？（y/n）：";
            cin >> answer;
            char c;
            if (cin.fail() || (answer != 'y' && answer != 'n' && answer != 'Y' && answer != 'N')) {
                cout << "输入无效，请重新输入。" << endl;
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
        }
        cout << endl;
        if (answer == 'y' || answer == 'Y')
            continue;
        else if (answer == 'n' || answer == 'N')
            break;
    }

    return 0;
}

/*
测试数据：
1+2*(3-4)-5/6
5+3*(7-8/2)+6
*/