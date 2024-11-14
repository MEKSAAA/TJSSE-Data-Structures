#include<iostream>
#include<iomanip>
using namespace std;

class CircularList;
class Node {
	friend class CircularList;
private:
	int data;  //结点数据
	Node* link;  //结点链接指针
public:
	Node(int value) :data(value), link(NULL) {}
};

class CircularList {
private:
	Node* first;
	Node* last;
public:
	CircularList() :first(NULL), last(NULL) {}  //构造函数
	~CircularList();
	void insert(int value);
	void display();
	Node* getFirst() { return first; }//得到头结点
	Node* getLast() { return last; }//得到尾结点
	void playJosephusGame(CircularList& list, int n, int m, int s, int k);
};

CircularList::~CircularList()
{
	//析构函数
	if (first != NULL) {
		Node* current = first->link;
		while (current != first) {
			Node* temp = current;
			current = current->link;
			delete temp;
		}
		delete first;
	}
}

void CircularList::insert(int value)
{
	//将value值插入到最后一个位置
	Node* newNode = new Node(value);
	if (first == NULL) {
		first = newNode;
		last = newNode;
		first->link = last;
		last->link = first;
	}
	else {
		newNode->link = first;
		last->link = newNode;
		last = newNode;
	}
}

void CircularList::display()
{
	//输出链表
	if (first == NULL) {
		return;
	}
	Node* current = getFirst();
	int i = 0;
	do {
		cout << setiosflags(ios::left) << setw(7) << current->data;
		i++;
		current = current->link;
		if (i != 0 && i % 8 == 0)
			cout << endl;
	} while (current != first);
	return;
}

void CircularList::playJosephusGame(CircularList& list, int n, int m, int s, int k)
{
	Node* current = list.getFirst();
	Node* prev = list.getLast();  //prev用来保存当前结点的前一个结点
	for (int i = 1;i < s;i++) {
		prev = current;  //prev在S-1位置
		current = current->link;  //从位置S开始
	}
	for (int i = 0;i < n - k;i++) {
		for (int j = 0;j < m - 1;j++) {
			prev = current;  //prev为第M-1个
			current = current->link;  //数到的第M个
		}
		cout << "第" << i + 1 << "个死者的位置是：" << current->data << endl;
		if (current == first) {
			Node* temp = current;
			prev->link = current->link;
			current = current->link;
			first = current;
			delete temp;
		}
		else {
			Node* temp = current;
			prev->link = current->link;
			if (current == last)
				last = prev;
			current = current->link;
			delete temp;   //将数到的第M个删去
		}
	}
	cout << endl << "最后剩下：" << k << "人" << endl;
	cout << endl << "剩余的生者位置为：" << endl;
	list.display();
	return;
}

void dealInputError(int& n, string str, int max = INT_MAX)  //处理输入错误
{
	while (1) {
		char c;  //用来获取输入一个数之后的一个字符，若获取一个字符且非换行符则视为输入错误。
		cout << str;
		cin >> n;
		if (cin.fail() || n < 1 || n > max) {
			cout << "输入错误，请重新输入。" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}  //内容错误
		else if (cin.get(c) && c != '\n') {
			cout << "输入错误，请重新输入。" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}  //个数错误
		else
			break;
	}
	return;
}

void getParameters(int& n, int& s, int& m, int& k)  //输入所有需要的参数
{
	dealInputError(n, "请输入生死游戏的总人数N：");
	dealInputError(s,"请输入游戏开始的位置S：", n);
	dealInputError(m,"请输入死亡数字M：", n);
	dealInputError(k, "请输入剩余的生者人数K：", n);
	cout << endl;
	return;
}

void menu()
{
	cout << "******************************************" << endl;
	cout << "*            约瑟夫生死者游戏            *" << endl;
	cout << "*             A-----游戏简介             *" << endl;
	cout << "*             Y-----开始游戏             *" << endl;
	cout << "*             N-----退出游戏             *" << endl;
	cout << "******************************************" << endl;
	return;
}

int main()
{
	menu();
	while (1) {
		char choice;
		while (1) {
			cout << endl;
			cout << "请选择要执行的操作（A/Y/N）：";
			cin >> choice;
			char c;
			if (cin.fail() || (choice != 'a' && choice != 'A' && choice != 'y' && choice != 'Y' && choice != 'N' && choice != 'n' )) {
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
		if (choice == 'a' || choice == 'A') {
			cout << endl << "游戏简介：现有N人围城一圈，从第S个人开始依次报数，报M的人出局，" << endl;
			cout << "再由下一个人开始报数，如此循环，直至剩下K个人为止。" << endl;
			continue;
		}
		else if (choice == 'n' || choice == 'N') {
			cout << endl << "退出游戏。" << endl;
			break;
		}
		else if (choice == 'y' || choice == 'Y') {
			cout << endl;
			int n, s, m, k;
			getParameters(n, s, m, k);
			CircularList list;
			for (int i = 1;i <= n;i++)
				list.insert(i);  //形成约瑟夫环
			list.playJosephusGame(list, n, m, s, k);
			cout << endl;
			continue;
		}
		else {
			cout << endl << "无效选项，请重新操作。" << endl;
			continue;
		}
	}
	return 0;
}