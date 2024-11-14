#include<iostream>
#include<iomanip>
#include<cstring>
using namespace std;

class List;

/*��������*/
class Node {
friend class List;
private:
	int examNumber;  //����
	string name;  //����
	string gender;  //�Ա�
	int age;  //����
	string category;  //�������
	Node* link;  //���ָ��
public:
	Node(int num, string n, string g, int a, string cate) :examNumber(num), name(n), gender(g), age(a), category(cate), link(NULL) {} //���캯��

};

/*������*/
class List {
private:
	Node* first;
	Node* last;
public:
	List();   //���캯��
	void MakeEmpty();  //ɾȥ�����г���ͷ�������������������
	~List();  //��������
	Node* getFirst() { return first->link; }  //��õ�һ�����
	void Insert(int num, string name, string gender, int age, string category, int i);  //�������i����㴦�����¿�����Ϣ
	Node* FindValue(const int& fnum);  //����������������Ϊfnum�Ľ���ǰһ�����
	Node* FindCurrentValue(const int& fnum);  //���ҿ���Ϊfnum�Ľ��
	void Display();  //������п�����Ϣ
	void RemoveValue(int rnum);  //��������ɾ������Ϊrnum�Ľ��
	void Modify(int mnum);  //�޸Ŀ���Ϊmnum�Ŀ�����Ϣ
	void display1stu(Node* p);  //չʾһ�п�����Ϣ
	int countTotalStudents();  //ͳ�ƿ���������
	void countGender();  //ͳ���Ա�ֲ�
	void countAge();  //ͳ������ֲ�
};

List::List()
{
	first = new Node(0, "", "", 0, "");
	last = first;
}

void List::MakeEmpty()
{
	Node* q;
	while (first->link != NULL) {
		q = first->link;
		first->link = q->link;  //����ͷ�����һ����������ժ��
		delete q;  //�ͷ�
	}
	last = first;  //�޸ı�βָ��
}

List::~List()
{
	MakeEmpty();
	delete first;  //�����ÿգ���ɾȥͷ���
}

void List::Insert(int num, string name, string gender, int age, string category, int i)
{
	Node* p = first;
	int k = 0;
	while (p != NULL && k < i - 1) {
		p = p->link;
		k++;
	}  //�ҵ�i-1�����
	if (p == NULL && first != NULL) {
		cout << "��Ч�Ĳ���λ�ã�" << endl;
		return;
	}
	Node* newNode = new Node(num, name, gender, age, category);  //�����½��
	if (first == NULL || i == 0) {  //���ڱ�ǰ
		newNode->link = first;
		if (first == NULL)
			last = newNode;
		first = newNode;
	}
	else {  //���ڱ��л��β
		newNode->link = p->link;
		if (p->link == NULL)
			last = newNode;
		p->link = newNode;
	}
	return;
}

Node* List::FindValue(const int& fnum)
{
	if (first->link == NULL) {
		cout << "���޿�����Ϣ��������Ч��" << endl;
		return NULL;
	}
	Node* p = first->link, * q = first;  //pΪ��ǰ��㣬qΪp��ǰһ�����
	while (p != NULL && p->examNumber != fnum) {
		p = p->link;
		q = q->link;
	}
	if (p == NULL || p->examNumber != fnum) {
		cout << "���޸ÿ�����Ϣ��" << endl;
		return NULL;
	}
	return q;
}

Node* List::FindCurrentValue(const int& fnum)
{
	if (first->link == NULL) {
		cout << "���޿�����Ϣ��������Ч��" << endl;
		return NULL;
	}
	Node* current = first->link;
	while (current != NULL && current->examNumber != fnum)
		current = current->link;
	if (current == NULL || current->examNumber != fnum) {
		cout << "���޸ÿ�����Ϣ��" << endl;
		return NULL;
	}
	return current;
}

void List::Display()
{
	if (first->link == NULL) {
		cout << "���޿�����Ϣ��" << endl;
		return;
	}
	Node* current = first->link;
	cout << setiosflags(ios::left);
	cout << setw(10) << "����" << setw(10) << "����" << setw(10) << "�Ա�" << setw(10) << "����" << setw(20) << "�������" << endl;
	while (current != NULL) {
		cout << setw(10) << current->examNumber << setw(10) << current->name << setw(10) << current->gender << setw(10) << current->age << setw(20) << current->category << endl;
		current = current->link;
	}
	cout << endl;
	return;
}

void List::RemoveValue(int rnum)
{
	Node* p = FindValue(rnum);  //pָ�������п���Ϊrnum��ǰһ�����
	if (p == NULL || p->link == NULL) {
		return;
	}
	Node* q = p->link;
	p->link = q->link;  //��������
	cout << "��ɾ���Ŀ�����Ϣ�ǣ�";
	cout << q->examNumber << "     " << q->name << "     " << q->gender << "     " << q->age << "     " << q->category << endl;
	if (q == last)
		last = p;
	delete q;
	return;
}

void List::Modify(int mnum)
{
	Node* p = FindValue(mnum);  //pָ�������п���Ϊmnum��ǰһ�����
	if (p == NULL || p->link == NULL) {
		return;
	}
	p = p->link;  //��pָ����Ҫ�޸ĵĽ��
	cout << "�������޸ĺ�Ŀ�����Ϣ��" << endl;
	cin >> p->examNumber >> p->name >> p->gender >> p->age >> p->category;
	return;
}

void List::display1stu(Node* p)
{
	if (p != NULL) {
		cout << setw(10) << "����" << setw(10) << "����" << setw(10) << "�Ա�" << setw(10) << "����" << setw(20) << "�������" << endl;
		cout << setw(10) << p->examNumber << setw(10) << p->name << setw(10) << p->gender << setw(10) << p->age << setw(20) << p->category << endl;
	}
	return;
}

int List::countTotalStudents()
{
	int count = 0;
	Node* current = first->link;
	while (current != NULL) {
		count++;
		current = current->link;
	}
	return count;
}

void List::countGender()
{
	int male = 0;
	int female = 0;
	Node* current = first->link;
	while (current != NULL) {
		if (current->gender == "��")
			male++;
		else if (current->gender == "Ů")
			female++;
		current = current->link;
	}
	cout << "���Կ���������" << male << endl;
	cout << "Ů�Կ���������" << female << endl;
}

void List::countAge()
{
	int under18 = 0;
	int from18to22 = 0;
	int above22 = 0;
	Node* current = first->link;
	while (current != NULL) {
		if (current->age < 18)
			under18++;
		else if (current->age >= 18 && current->age <= 22)
			from18to22++;
		else
			above22++;
		current = current->link;
	}
	cout << "18�����¿���������" << under18 << endl;
	cout << "18-22�꿼��������" << from18to22 << endl;
	cout << "22������������" << above22 << endl;
}
void dealInputError(int& n, string str, int max = INT_MAX, int min = 1)  //�����������
{
	while (1) {
		char c;  //������ȡ����һ����֮���һ���ַ�������ȡһ���ַ��ҷǻ��з�����Ϊ�������
		cout << str;
		cin >> n;
		if (cin.fail() || n < min || n > max) {
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

int menu()
{
	int x;
	string m = "��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ����������";
	dealInputError(x, m, 5, 0);
	cout << endl;
	return x;
}

int main()
{
	List slist;
	cout << "��ӭ�������Ա���ϵͳ��" << endl;
	cout << "�����뽨��������Ϣϵͳ��" << endl;
	int stuNums;
	dealInputError(stuNums, "�����뿼��������");
	cout << "���������뿼���Ŀ��ţ��������Ա����估�������" << endl;
	for (int i = 0;i < stuNums;i++) {
		int examNum_i;
		string name_i;
		string gender_i;
		int age_i;
		string cate_i;
		cin >> examNum_i >> name_i >> gender_i >> age_i >> cate_i;
		slist.Insert(examNum_i, name_i, gender_i, age_i, cate_i, i + 1);
	}
	cout << endl;
	slist.Display();
	while (1) {
		int x;
		x = menu();
		if (x == 0) {
			cout << "�˳����򣡻�ӭ�´�ʹ�ã�" << endl;
			break;
		}
		else if (x == 1) {
			int pos;
			dealInputError(pos, "��������Ҫ����Ŀ�����λ�ã�");
			cout << "���������뿼���Ŀ��ţ��������Ա����估�������" << endl;
			int examNum_i;
			string name_i;
			string gender_i;
			int age_i;
			string cate_i;
			cin >> examNum_i >> name_i >> gender_i >> age_i >> cate_i;
			slist.Insert(examNum_i, name_i, gender_i, age_i, cate_i, pos);
			cout << endl;
			slist.Display();
		}
		else if (x == 2) {
			int Rnum;
			dealInputError(Rnum, "��������Ҫɾ���Ŀ����Ŀ��ţ�");
			cout << endl;
			slist.RemoveValue(Rnum);
			cout << endl;
			slist.Display();
		}
		else if (x == 3) {
			int Fnum;
			dealInputError(Fnum, "������Ҫ���ҵĿ������ţ�");
			cout << endl;
			Node* q = slist.FindCurrentValue(Fnum);
			if (q != NULL)
				slist.display1stu(q);
			cout << endl;
		}
		else if (x == 4) {
			int Mnum;
			dealInputError(Mnum, "������Ҫ�޸ĵĿ������ţ�");
			slist.Modify(Mnum);
			cout << endl;
			slist.Display();
		}
		else if (x == 5) {
			Node* current = slist.getFirst();
			if (!current) {
				cout << "���޿�����Ϣ��������ӣ�" << endl;
				continue;
			}
			cout << "���п�����Ϣ��" << endl;
			slist.Display();
			cout << endl << "������������" << slist.countTotalStudents() << endl;
			cout << endl << "�����Ա�ֲ���" << endl;
			slist.countGender();
			cout << endl << "��������ֲ���" << endl;
			slist.countAge();
			cout << endl;
		}
	}
	return 0;
}

/*
1 stu1 Ů 20 ǰ�����ʦ
2 stu2 �� 22 ��˿���ʦ
3 stu3 Ů 17 ���ѧͽ
4 stu4 �� 25 �������ʦ
5 stu5 Ů 24 ��˿���ʦ
6 stu6 �� 21 ǰ�����ʦ
*/