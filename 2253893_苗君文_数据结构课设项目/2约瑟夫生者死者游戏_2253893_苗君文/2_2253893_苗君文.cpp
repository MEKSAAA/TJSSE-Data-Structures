#include<iostream>
#include<iomanip>
using namespace std;

class CircularList;
class Node {
	friend class CircularList;
private:
	int data;  //�������
	Node* link;  //�������ָ��
public:
	Node(int value) :data(value), link(NULL) {}
};

class CircularList {
private:
	Node* first;
	Node* last;
public:
	CircularList() :first(NULL), last(NULL) {}  //���캯��
	~CircularList();
	void insert(int value);
	void display();
	Node* getFirst() { return first; }//�õ�ͷ���
	Node* getLast() { return last; }//�õ�β���
	void playJosephusGame(CircularList& list, int n, int m, int s, int k);
};

CircularList::~CircularList()
{
	//��������
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
	//��valueֵ���뵽���һ��λ��
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
	//�������
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
	Node* prev = list.getLast();  //prev�������浱ǰ����ǰһ�����
	for (int i = 1;i < s;i++) {
		prev = current;  //prev��S-1λ��
		current = current->link;  //��λ��S��ʼ
	}
	for (int i = 0;i < n - k;i++) {
		for (int j = 0;j < m - 1;j++) {
			prev = current;  //prevΪ��M-1��
			current = current->link;  //�����ĵ�M��
		}
		cout << "��" << i + 1 << "�����ߵ�λ���ǣ�" << current->data << endl;
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
			delete temp;   //�������ĵ�M��ɾȥ
		}
	}
	cout << endl << "���ʣ�£�" << k << "��" << endl;
	cout << endl << "ʣ�������λ��Ϊ��" << endl;
	list.display();
	return;
}

void dealInputError(int& n, string str, int max = INT_MAX)  //�����������
{
	while (1) {
		char c;  //������ȡ����һ����֮���һ���ַ�������ȡһ���ַ��ҷǻ��з�����Ϊ�������
		cout << str;
		cin >> n;
		if (cin.fail() || n < 1 || n > max) {
			cout << "����������������롣" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}  //���ݴ���
		else if (cin.get(c) && c != '\n') {
			cout << "����������������롣" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}  //��������
		else
			break;
	}
	return;
}

void getParameters(int& n, int& s, int& m, int& k)  //����������Ҫ�Ĳ���
{
	dealInputError(n, "������������Ϸ��������N��");
	dealInputError(s,"��������Ϸ��ʼ��λ��S��", n);
	dealInputError(m,"��������������M��", n);
	dealInputError(k, "������ʣ�����������K��", n);
	cout << endl;
	return;
}

void menu()
{
	cout << "******************************************" << endl;
	cout << "*            Լɪ����������Ϸ            *" << endl;
	cout << "*             A-----��Ϸ���             *" << endl;
	cout << "*             Y-----��ʼ��Ϸ             *" << endl;
	cout << "*             N-----�˳���Ϸ             *" << endl;
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
			cout << "��ѡ��Ҫִ�еĲ�����A/Y/N����";
			cin >> choice;
			char c;
			if (cin.fail() || (choice != 'a' && choice != 'A' && choice != 'y' && choice != 'Y' && choice != 'N' && choice != 'n' )) {
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
		if (choice == 'a' || choice == 'A') {
			cout << endl << "��Ϸ��飺����N��Χ��һȦ���ӵ�S���˿�ʼ���α�������M���˳��֣�" << endl;
			cout << "������һ���˿�ʼ���������ѭ����ֱ��ʣ��K����Ϊֹ��" << endl;
			continue;
		}
		else if (choice == 'n' || choice == 'N') {
			cout << endl << "�˳���Ϸ��" << endl;
			break;
		}
		else if (choice == 'y' || choice == 'Y') {
			cout << endl;
			int n, s, m, k;
			getParameters(n, s, m, k);
			CircularList list;
			for (int i = 1;i <= n;i++)
				list.insert(i);  //�γ�Լɪ��
			list.playJosephusGame(list, n, m, s, k);
			cout << endl;
			continue;
		}
		else {
			cout << endl << "��Чѡ������²�����" << endl;
			continue;
		}
	}
	return 0;
}