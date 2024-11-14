#include<iostream>
#include<iomanip>
#include<cstring>
using namespace std;

class List;

/*链表结点类*/
class Node {
friend class List;
private:
	int examNumber;  //考号
	string name;  //姓名
	string gender;  //性别
	int age;  //年龄
	string category;  //报考类别
	Node* link;  //结点指针
public:
	Node(int num, string n, string g, int a, string cate) :examNumber(num), name(n), gender(g), age(a), category(cate), link(NULL) {} //构造函数

};

/*链表类*/
class List {
private:
	Node* first;
	Node* last;
public:
	List();   //构造函数
	void MakeEmpty();  //删去链表中除表头结点以外的所有其他结点
	~List();  //析构函数
	Node* getFirst() { return first->link; }  //获得第一个结点
	void Insert(int num, string name, string gender, int age, string category, int i);  //在链表第i个结点处插入新考生信息
	Node* FindValue(const int& fnum);  //在链表中搜索考号为fnum的结点的前一个结点
	Node* FindCurrentValue(const int& fnum);  //查找考号为fnum的结点
	void Display();  //输出所有考生信息
	void RemoveValue(int rnum);  //从链表中删除考号为rnum的结点
	void Modify(int mnum);  //修改考号为mnum的考生信息
	void display1stu(Node* p);  //展示一行考生信息
	int countTotalStudents();  //统计考生总人数
	void countGender();  //统计性别分布
	void countAge();  //统计年龄分布
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
		first->link = q->link;  //将表头结点后第一个结点从链中摘下
		delete q;  //释放
	}
	last = first;  //修改表尾指针
}

List::~List()
{
	MakeEmpty();
	delete first;  //链表置空，再删去头结点
}

void List::Insert(int num, string name, string gender, int age, string category, int i)
{
	Node* p = first;
	int k = 0;
	while (p != NULL && k < i - 1) {
		p = p->link;
		k++;
	}  //找第i-1个结点
	if (p == NULL && first != NULL) {
		cout << "无效的插入位置！" << endl;
		return;
	}
	Node* newNode = new Node(num, name, gender, age, category);  //创建新结点
	if (first == NULL || i == 0) {  //插在表前
		newNode->link = first;
		if (first == NULL)
			last = newNode;
		first = newNode;
	}
	else {  //插在表中或表尾
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
		cout << "暂无考生信息，查找无效！" << endl;
		return NULL;
	}
	Node* p = first->link, * q = first;  //p为当前结点，q为p的前一个结点
	while (p != NULL && p->examNumber != fnum) {
		p = p->link;
		q = q->link;
	}
	if (p == NULL || p->examNumber != fnum) {
		cout << "暂无该考生信息！" << endl;
		return NULL;
	}
	return q;
}

Node* List::FindCurrentValue(const int& fnum)
{
	if (first->link == NULL) {
		cout << "暂无考生信息，查找无效！" << endl;
		return NULL;
	}
	Node* current = first->link;
	while (current != NULL && current->examNumber != fnum)
		current = current->link;
	if (current == NULL || current->examNumber != fnum) {
		cout << "暂无该考生信息！" << endl;
		return NULL;
	}
	return current;
}

void List::Display()
{
	if (first->link == NULL) {
		cout << "暂无考生信息！" << endl;
		return;
	}
	Node* current = first->link;
	cout << setiosflags(ios::left);
	cout << setw(10) << "考号" << setw(10) << "姓名" << setw(10) << "性别" << setw(10) << "年龄" << setw(20) << "报考类别" << endl;
	while (current != NULL) {
		cout << setw(10) << current->examNumber << setw(10) << current->name << setw(10) << current->gender << setw(10) << current->age << setw(20) << current->category << endl;
		current = current->link;
	}
	cout << endl;
	return;
}

void List::RemoveValue(int rnum)
{
	Node* p = FindValue(rnum);  //p指向链表中考号为rnum的前一个结点
	if (p == NULL || p->link == NULL) {
		return;
	}
	Node* q = p->link;
	p->link = q->link;  //重新链接
	cout << "你删除的考生信息是：";
	cout << q->examNumber << "     " << q->name << "     " << q->gender << "     " << q->age << "     " << q->category << endl;
	if (q == last)
		last = p;
	delete q;
	return;
}

void List::Modify(int mnum)
{
	Node* p = FindValue(mnum);  //p指向链表中考号为mnum的前一个结点
	if (p == NULL || p->link == NULL) {
		return;
	}
	p = p->link;  //让p指向需要修改的结点
	cout << "请输入修改后的考生信息：" << endl;
	cin >> p->examNumber >> p->name >> p->gender >> p->age >> p->category;
	return;
}

void List::display1stu(Node* p)
{
	if (p != NULL) {
		cout << setw(10) << "考号" << setw(10) << "姓名" << setw(10) << "性别" << setw(10) << "年龄" << setw(20) << "报考类别" << endl;
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
		if (current->gender == "男")
			male++;
		else if (current->gender == "女")
			female++;
		current = current->link;
	}
	cout << "男性考生人数：" << male << endl;
	cout << "女性考生人数：" << female << endl;
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
	cout << "18岁以下考生人数：" << under18 << endl;
	cout << "18-22岁考生人数：" << from18to22 << endl;
	cout << "22岁以上人数：" << above22 << endl;
}
void dealInputError(int& n, string str, int max = INT_MAX, int min = 1)  //处理输入错误
{
	while (1) {
		char c;  //用来获取输入一个数之后的一个字符，若获取一个字符且非换行符则视为输入错误。
		cout << str;
		cin >> n;
		if (cin.fail() || n < min || n > max) {
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

int menu()
{
	int x;
	string m = "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）：";
	dealInputError(x, m, 5, 0);
	cout << endl;
	return x;
}

int main()
{
	List slist;
	cout << "欢迎来到考试报名系统！" << endl;
	cout << "首先请建立考生信息系统！" << endl;
	int stuNums;
	dealInputError(stuNums, "请输入考生人数：");
	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;
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
			cout << "退出程序！欢迎下次使用！" << endl;
			break;
		}
		else if (x == 1) {
			int pos;
			dealInputError(pos, "请输入你要插入的考生的位置：");
			cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;
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
			dealInputError(Rnum, "请输入你要删除的考生的考号：");
			cout << endl;
			slist.RemoveValue(Rnum);
			cout << endl;
			slist.Display();
		}
		else if (x == 3) {
			int Fnum;
			dealInputError(Fnum, "请输入要查找的考生考号：");
			cout << endl;
			Node* q = slist.FindCurrentValue(Fnum);
			if (q != NULL)
				slist.display1stu(q);
			cout << endl;
		}
		else if (x == 4) {
			int Mnum;
			dealInputError(Mnum, "请输入要修改的考生考号：");
			slist.Modify(Mnum);
			cout << endl;
			slist.Display();
		}
		else if (x == 5) {
			Node* current = slist.getFirst();
			if (!current) {
				cout << "暂无考生信息，请先添加！" << endl;
				continue;
			}
			cout << "所有考生信息：" << endl;
			slist.Display();
			cout << endl << "考生总人数：" << slist.countTotalStudents() << endl;
			cout << endl << "考生性别分布：" << endl;
			slist.countGender();
			cout << endl << "考生年龄分布：" << endl;
			slist.countAge();
			cout << endl;
		}
	}
	return 0;
}

/*
1 stu1 女 20 前端设计师
2 stu2 男 22 后端开发师
3 stu3 女 17 软件学徒
4 stu4 男 25 软件测试师
5 stu5 女 24 后端开发师
6 stu6 男 21 前端设计师
*/