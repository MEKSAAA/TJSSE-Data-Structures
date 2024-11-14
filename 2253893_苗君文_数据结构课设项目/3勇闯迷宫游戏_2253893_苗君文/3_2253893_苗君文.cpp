#include<iostream>
#include<iomanip>
using namespace std;

/*
��������
7

1 1 1 1 1 1 1
1 0 1 0 0 0 1
1 0 1 0 1 1 1
1 0 0 0 1 0 1
1 0 1 0 0 0 1
1 0 1 0 1 0 1
1 1 1 1 1 1 1

1 1

5 5
*/

class Stack;
class Node {
	friend class Stack;
private:
	int x;
	int y;
	Node* link;
public:
	Node(int iX = -1, int iY = -1, Node* l = NULL) :x(iX), y(iY), link(l) {}
};

class Stack {
private:
	Node* top;  //ջ��ָ��
public:
	Stack() :top(NULL) {}
	~Stack();
	void Push(const int& i, const int& j) { top = new Node(i, j, top); }
	void Pop(int& rx, int& ry);
	Node* GetTop() { return top; }
	Node* GetTopNext();
};

Stack::~Stack()
{
	Node* p;
	while (top != NULL) {
		p = top;
		top = top->link;
		delete p;
	}
}

void Stack::Pop(int& rx, int& ry)
{
	if (top == NULL) {
		rx = -1;
		ry = -1;
		return;
	}
	Node* p = top;
	rx = p->x;
	ry = p->y;
	top = top->link;
	delete p;
	return;
}

Node* Stack::GetTopNext()
{
	if (top != NULL)
		return top->link;
	return NULL;
}

struct Intersection {
	int left;
	int forward;
	int right;
};

class Maze {
private:
	int MazeSize;  //�Թ���С
	Intersection** intsec;  //·������
	Stack path;  //��ջ��¼·��
	int entrX, entrY;  //�������
	int exitX, exitY;  //��������
	int** MazeData;  //�Թ�����
public:
	Maze(int Size);
	void printMaze();
	bool TraverseMaze(int cx, int cy);
	void displayPath();
	void setEntr(int x, int y);
	void setExit(int x, int y);
};

void Maze::setEntr(int x, int y) {
	entrX = x;
	entrY = y;
}  //��ȡ�������

void Maze::setExit(int x, int y) {
	exitX = x;
	exitY = y;
}  //��ȡ��������

Maze::Maze(int Size) {
	entrX = -1;
	entrY = -1;
	exitX = -1;
	exitY = -1;
	MazeSize = Size;
	intsec = new Intersection * [MazeSize];  //�����Թ�·������
	for (int i = 0;i < MazeSize;i++)
		intsec[i] = new Intersection[MazeSize];

	MazeData = new int* [MazeSize];
	for (int i = 0;i < MazeSize;i++)
		MazeData[i] = new int[MazeSize];  //�����Թ����ݶ�ά����
	while (1) {
		cout << "�������Թ����飨1Ϊǽ��0Ϊ�յأ���" << endl;
		bool judge = 0;  //�ж��Ƿ���Ҫ��������
		for (int i = 0;i < MazeSize;i++) {
			for (int j = 0;j < MazeSize;j++) {
				cin >> MazeData[i][j];
				if (cin.fail() || MazeData[i][j] < 0 || MazeData[i][j]>1) {
					cout << "����������������롣" << endl;
					cin.clear();
					cin.ignore(9999, '\n');
					judge = 1;
					break;
				}
			}
			if (judge)
				break;
		}
		if (judge)
			continue;
		else
			break;
	}  //����Թ�����

	for (int i = 0;i < MazeSize;i++) {
		for (int j = 0;j < MazeSize;j++) {
			intsec[i][j].left = (j > 0) ? MazeData[i][j] : 1;  //j=0ʱû����ߣ���Ϊ���Ϊǽ
			intsec[i][j].forward = (i < MazeSize - 1) ? MazeData[i][j] : 1;  //i=MazeSize-1ʱû��ǰ�棬��Ϊǽ
			intsec[i][j].right = (j < MazeSize - 1) ? MazeData[i][j] : 1;  //j=MazeSize-1ʱû���ұߣ���Ϊǽ
		}
	}  //�����Թ����ݳ�ʼ��·������
}  //���캯��

void Maze::printMaze() {
	cout << setiosflags(ios::left) << "       ";
	for (int i = 0;i < MazeSize;i++)
		cout << i << setw(6) << "��";
	cout << endl << endl;
	for (int i = 0;i < MazeSize;i++) {
		for (int j = 0;j < MazeSize;j++) {
			if (j == 0)
				cout << i << setw(6) << "��";
			if (MazeData[i][j] == 2)
				cout << setw(7) << "x";
			else if (MazeData[i][j] == 1)
				cout << setw(7) << "#";
			else
				cout << setw(7) << "0";
			if (j == MazeSize - 1)
				cout << endl;
		}
		cout << endl;
	}
	cout << endl;
}  //��ӡ�Թ���ͼ

bool Maze::TraverseMaze(int cx, int cy) {
	if (cx >= 0 && cy >= 0 && cx < MazeSize && cy < MazeSize) {
		if (cx == exitX && cy == exitY) {
			path.Push(cx, cy);
			MazeData[cx][cy] = 2;
			return true;
		}  //���ڴ���
		else if (MazeData[cx][cy] == 0) {
			MazeData[cx][cy] = 2; //����ǰλ�ñ��Ϊ�ѷ���
			if (TraverseMaze(cx - 1, cy) || TraverseMaze(cx, cy - 1) || TraverseMaze(cx + 1, cy) || TraverseMaze(cx, cy + 1)) {
				path.Push(cx, cy);
				return true;
			}
			MazeData[cx][cy] = 0; //�߲�ͨ�ָ�ԭ��״̬
		}  //�ݹ�����ǰ������Ѱ����
	}
	return false;
}

void Maze::displayPath() {
	while (path.GetTop() != NULL) {
		int i, j;
		path.Pop(i, j);
		cout << "<" << i << "," << j << "> ";
		if (path.GetTopNext() != path.GetTop())
			cout << "---> ";
	}
	return;
}  //��ӡ�Թ�·��

void dealInputError(int& n, string str, int max = 1)  //�����������
{
	while (1) {
		char c;  //������ȡ����һ����֮���һ���ַ�������ȡһ���ַ��ҷǻ��з�����Ϊ�������
		cout << str;
		cin >> n;
		if (cin.fail() || n < 1 || n > max) {
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
	}
	return;
}

void deal2Error(int& x, int& y, string str, int max)  //�����������������������
{
	while (1) {
		char c;
		cout << str;
		cin >> x >> y;
		if (cin.fail() || x<0 || x>max || y<0 || y>max) {
			cout << "����������������롣" << endl;
			cin.clear();
			cin.ignore(9999, '\n');
			continue;
		}
		else if (cin.get(c) && c != '\n') {
			cout << "����������������롣" << endl;
			cin.clear();
			cin.ignore(9999, '\n');
			continue;
		}
		else
			break;
	}
}

int main()
{
	cout << "  ��ӭ�����´��Թ���Ϸ��" << endl;
	cout << "**�����������cpp�ļ���ͷ**" << endl;
	cout << "**�����������cpp�ļ���ͷ**" << endl;
	cout << "**�����������cpp�ļ���ͷ**" << endl << endl;
	int size;
	dealInputError(size, "�������Թ��Ľ�����", 50);
	Maze myMaze(size);
	cout << endl << "��ʼ�Թ���ͼ��" << endl << endl;
	myMaze.printMaze();
	int ax, ay, bx, by;
	deal2Error(ax, ay, "�������Թ���������꣺", size - 1);
	myMaze.setEntr(ax, ay);
	deal2Error(bx, by, "�������Թ��ĳ������꣺", size - 1);
	myMaze.setExit(bx, by);
	if (myMaze.TraverseMaze(ax, ay)) {
		cout << endl << "�´��Թ���ͼ��" << endl << endl;
		myMaze.printMaze();
		cout << endl;
		cout << "�Թ�·����" << endl << endl;
		myMaze.displayPath();
		cout << endl;
	}
	else
		cout << "���Թ��޽⣡" << endl;
	cout << endl << "���س����Թر�..." << endl;
	cin.ignore();
	return 0;
}

/*
��������
7

1 1 1 1 1 1 1
1 0 1 0 0 0 1
1 0 1 0 1 1 1
1 0 0 0 1 0 1
1 0 1 0 0 0 1
1 0 1 0 1 0 1
1 1 1 1 1 1 1

1 1

5 5
*/