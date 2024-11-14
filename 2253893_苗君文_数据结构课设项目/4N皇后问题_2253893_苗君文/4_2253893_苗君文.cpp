#include<iostream>
using namespace std;

//����ڵ�ǰλ�÷��ûʺ��Ƿ�ȫ
bool isSafe(int** board, int row, int col, int N) 
{
	if (row > N || col > N)
		return false;
	for (int i = 0;i < row;i++) {
		if (board[i][col] == 1)
			return false;//���ͬһ��

		if (col - (row - i) >= 0 && board[i][col - (row - i)] == 1)
			return false;  //������϶Խ���

		if (col + (row - i) < N && board[i][col + (row - i)] == 1)
			return false;  //������϶Խ���
	}  
	return true;
}

//�����㷨���ݹ���N�ʺ����⣬ͬʱ���ÿһ�ֽ������
void solveNQueens(int** board, int row, int N, int& solutions)
{
	//����ڷ���N���ʺ����ҵ�һ�ֽ������
	if (row == N) {
		solutions++;
		//��ӡ�������
		if (solutions == 1)
			cout << endl << "�ʺ�ڷ���" << endl << endl;
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
			board[row][i] = 1;  //���ûʺ�
			solveNQueens(board, row + 1, N, solutions);  //�ݹ����
			board[row][i] = 0;  //����
		}
	}
}

//���N�ʺ��������ں���
void NQueens(int N)
{
	//��̬���䴴�����̵Ķ�ά����
	int** board = new int* [N];
	for (int i = 0;i < N;i++) {
		board[i] = new int[N];
		//��ʼ������Ԫ��Ϊ0
		for (int j = 0;j < N;j++) {
			board[i][j] = 0;
		}
	}
	int solutions = 0;//ͳ�ƽ������������
	solveNQueens(board, 0, N, solutions);

	//����������������
	if (solutions > 0)
		cout << "����" << solutions << "�ֽⷨ��" << endl;
	else
		cout << "û�п��еĽ��������" << endl;

	//�ͷŶ�̬������ڴ�
	for (int i = 0;i < N;i++) {
		delete[] board[i];
	}
	delete[] board;
}

//�����������
void dealInputError(int& n, string str, int min = 2, int max = 100)  
{
	while (1) {
		char c;  //������ȡ����һ����֮���һ���ַ�������ȡһ���ַ��ҷǻ��з�����Ϊ�������
		cout << str;
		cin >> n;
		if (cin.fail() || n<min || n>max) {
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

int main()
{
	cout << "����N��N�����̣�����N���ʺ�Ҫ�����лʺ���ͬһ�С��к�ͬһб���ϡ�" << endl << endl;
	while (1) {
		int N;//�ʺ�ĸ���
		dealInputError(N, "������ʺ�ĸ�����2-100֮�䣩��");  //�����������
		NQueens(N);  //���ý��N�ʺ���

		//�ж��Ƿ�������г���
		char answer;
		while (1) {
			cout << endl << "�Ƿ�������иó��򣿣�y/n����";
			cin >> answer;
			char c;
			if (cin.fail() || (answer != 'y' && answer != 'n' && answer != 'Y' && answer != 'N')) {
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
		cout << endl;
		if (answer == 'y' || answer == 'Y')
			continue;
		else if (answer == 'n' || answer == 'N')
			break;
	}
	return 0;
}