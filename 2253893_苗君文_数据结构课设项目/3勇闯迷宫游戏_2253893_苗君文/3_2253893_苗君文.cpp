#include<iostream>
#include<iomanip>
using namespace std;

/*
测试数据
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
	Node* top;  //栈顶指针
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
	int MazeSize;  //迷宫大小
	Intersection** intsec;  //路口数组
	Stack path;  //用栈记录路径
	int entrX, entrY;  //入口坐标
	int exitX, exitY;  //出口坐标
	int** MazeData;  //迷宫数据
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
}  //获取入口坐标

void Maze::setExit(int x, int y) {
	exitX = x;
	exitY = y;
}  //获取出口坐标

Maze::Maze(int Size) {
	entrX = -1;
	entrY = -1;
	exitX = -1;
	exitY = -1;
	MazeSize = Size;
	intsec = new Intersection * [MazeSize];  //创建迷宫路口数组
	for (int i = 0;i < MazeSize;i++)
		intsec[i] = new Intersection[MazeSize];

	MazeData = new int* [MazeSize];
	for (int i = 0;i < MazeSize;i++)
		MazeData[i] = new int[MazeSize];  //构建迷宫数据二维数组
	while (1) {
		cout << "请输入迷宫数组（1为墙，0为空地）：" << endl;
		bool judge = 0;  //判断是否需要重新输入
		for (int i = 0;i < MazeSize;i++) {
			for (int j = 0;j < MazeSize;j++) {
				cin >> MazeData[i][j];
				if (cin.fail() || MazeData[i][j] < 0 || MazeData[i][j]>1) {
					cout << "输入错误，请重新输入。" << endl;
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
	}  //获得迷宫数据

	for (int i = 0;i < MazeSize;i++) {
		for (int j = 0;j < MazeSize;j++) {
			intsec[i][j].left = (j > 0) ? MazeData[i][j] : 1;  //j=0时没有左边，视为左边为墙
			intsec[i][j].forward = (i < MazeSize - 1) ? MazeData[i][j] : 1;  //i=MazeSize-1时没有前面，视为墙
			intsec[i][j].right = (j < MazeSize - 1) ? MazeData[i][j] : 1;  //j=MazeSize-1时没有右边，视为墙
		}
	}  //依据迷宫数据初始化路口数组
}  //构造函数

void Maze::printMaze() {
	cout << setiosflags(ios::left) << "       ";
	for (int i = 0;i < MazeSize;i++)
		cout << i << setw(6) << "列";
	cout << endl << endl;
	for (int i = 0;i < MazeSize;i++) {
		for (int j = 0;j < MazeSize;j++) {
			if (j == 0)
				cout << i << setw(6) << "行";
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
}  //打印迷宫地图

bool Maze::TraverseMaze(int cx, int cy) {
	if (cx >= 0 && cy >= 0 && cx < MazeSize && cy < MazeSize) {
		if (cx == exitX && cy == exitY) {
			path.Push(cx, cy);
			MazeData[cx][cy] = 2;
			return true;
		}  //出口处理
		else if (MazeData[cx][cy] == 0) {
			MazeData[cx][cy] = 2; //将当前位置标记为已访问
			if (TraverseMaze(cx - 1, cy) || TraverseMaze(cx, cy - 1) || TraverseMaze(cx + 1, cy) || TraverseMaze(cx, cy + 1)) {
				path.Push(cx, cy);
				return true;
			}
			MazeData[cx][cy] = 0; //走不通恢复原来状态
		}  //递归向左、前、右搜寻可行
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
}  //打印迷宫路径

void dealInputError(int& n, string str, int max = 1)  //处理输入错误
{
	while (1) {
		char c;  //用来获取输入一个数之后的一个字符，若获取一个字符且非换行符则视为输入错误。
		cout << str;
		cin >> n;
		if (cin.fail() || n < 1 || n > max) {
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
	}
	return;
}

void deal2Error(int& x, int& y, string str, int max)  //处理输入两个数的输入错误
{
	while (1) {
		char c;
		cout << str;
		cin >> x >> y;
		if (cin.fail() || x<0 || x>max || y<0 || y>max) {
			cout << "输入错误，请重新输入。" << endl;
			cin.clear();
			cin.ignore(9999, '\n');
			continue;
		}
		else if (cin.get(c) && c != '\n') {
			cout << "输入错误，请重新输入。" << endl;
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
	cout << "  欢迎进入勇闯迷宫游戏！" << endl;
	cout << "**测试数据请见cpp文件开头**" << endl;
	cout << "**测试数据请见cpp文件开头**" << endl;
	cout << "**测试数据请见cpp文件开头**" << endl << endl;
	int size;
	dealInputError(size, "请输入迷宫的阶数：", 50);
	Maze myMaze(size);
	cout << endl << "初始迷宫地图：" << endl << endl;
	myMaze.printMaze();
	int ax, ay, bx, by;
	deal2Error(ax, ay, "请输入迷宫的入口坐标：", size - 1);
	myMaze.setEntr(ax, ay);
	deal2Error(bx, by, "请输入迷宫的出口坐标：", size - 1);
	myMaze.setExit(bx, by);
	if (myMaze.TraverseMaze(ax, ay)) {
		cout << endl << "勇闯迷宫地图：" << endl << endl;
		myMaze.printMaze();
		cout << endl;
		cout << "迷宫路径：" << endl << endl;
		myMaze.displayPath();
		cout << endl;
	}
	else
		cout << "该迷宫无解！" << endl;
	cout << endl << "按回车键以关闭..." << endl;
	cin.ignore();
	return 0;
}

/*
测试数据
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