#include<iostream>
using namespace std;

//检查在当前位置放置皇后是否安全
bool isSafe(int** board, int row, int col, int N) 
{
	if (row > N || col > N)
		return false;
	for (int i = 0;i < row;i++) {
		if (board[i][col] == 1)
			return false;//检查同一列

		if (col - (row - i) >= 0 && board[i][col - (row - i)] == 1)
			return false;  //检查左上对角线

		if (col + (row - i) < N && board[i][col + (row - i)] == 1)
			return false;  //检查右上对角线
	}  
	return true;
}

//核心算法：递归解决N皇后问题，同时输出每一种解决方法
void solveNQueens(int** board, int row, int N, int& solutions)
{
	//如果摆放了N个皇后，则找到一种解决方案
	if (row == N) {
		solutions++;
		//打印解决方案
		if (solutions == 1)
			cout << endl << "皇后摆法：" << endl << endl;
		for (int i = 0;i < N;i++) {
			for (int j = 0;j < N;j++) {
				if (board[i][j] == 0)
					cout << "0 ";
				else
					cout << "X ";
			}
			cout << endl;
		}
		cout << endl;
		return;
	}

	for (int i = 0;i < N;i++) {
		if (isSafe(board, row, i, N)) {
			board[row][i] = 1;  //放置皇后
			solveNQueens(board, row + 1, N, solutions);  //递归调用
			board[row][i] = 0;  //回溯
		}
	}
}

//解决N皇后问题的入口函数
void NQueens(int N)
{
	//动态分配创建棋盘的二维数组
	int** board = new int* [N];
	for (int i = 0;i < N;i++) {
		board[i] = new int[N];
		//初始化数组元素为0
		for (int j = 0;j < N;j++) {
			board[i][j] = 0;
		}
	}
	int solutions = 0;//统计解决方案的数量
	solveNQueens(board, 0, N, solutions);

	//输出解决方案的数量
	if (solutions > 0)
		cout << "共有" << solutions << "种解法！" << endl;
	else
		cout << "没有可行的解决方案！" << endl;

	//释放动态分配的内存
	for (int i = 0;i < N;i++) {
		delete[] board[i];
	}
	delete[] board;
}

//处理输入错误
void dealInputError(int& n, string str, int min = 2, int max = 100)  
{
	while (1) {
		char c;  //用来获取输入一个数之后的一个字符，若获取一个字符且非换行符则视为输入错误。
		cout << str;
		cin >> n;
		if (cin.fail() || n<min || n>max) {
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

int main()
{
	cout << "现有N×N的棋盘，放入N个皇后，要求所有皇后不在同一行、列和同一斜线上。" << endl << endl;
	while (1) {
		int N;//皇后的个数
		dealInputError(N, "请输入皇后的个数（2-100之间）：");  //处理输入错误
		NQueens(N);  //调用解决N皇后函数

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
				cout << "输入无效，请重新输入。" << endl;
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