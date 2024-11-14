#include<iostream>
#include<cstring>
#include<fstream>
using namespace std;

const int maxLen = 1000;
char* my_strcpy(char* destination, const char* source) {
	char* dest = destination;
	while ((*dest++ = *source++) != '\0');
	return destination;
}

char* my_strcat(char* destination, const char* source) {
	char* dest = destination;
	while (*dest != '\0') {
		dest++;
	}
	while ((*dest++ = *source++) != '\0');
	return destination;
}

class String {
private:
	char* ch;//串的存储数组
	int curLen;//串的当前长度
	int f[maxLen];
public:
	String(const String& ob);
	String(const char* init);
	String();
	~String() { delete[]ch; }
	int Length()const { return curLen; }
	String& operator()(int pos, int len);
	int operator==(const String& ob)
		const {
		return strcmp(ch, ob.ch) == 0;
	}
	int operator!=(const String& ob)
		const {
		return strcmp(ch, ob.ch) != 0;
	}
	int operator!()
		const {
		return curLen == 0;
	}
	String& operator=(const String& ob);
	String& operator+=(const String& ob);
	char& operator[](int i);
	void getline(istream& is, String& str);
	bool getlineFile(ifstream& inFile, String& str);
	void fail();
	int fastFind(String& pat)const;
	const char* getCharArray() const { return ch; }
	friend istream& operator>>(istream& is, String& str);
	bool onlyAlpha();
};

istream& operator>>(istream& is, String& str)
{
	char buffer[maxLen];
	is >> buffer;
	str = buffer;
	return is;
}

//复制构造函数：从已有串ob复制
String::String(const String& ob)
{
	ch = new char[maxLen + 1];
	if (!ch) {
		cerr << "存储分配错！" << endl;
		exit(1);
	}
	curLen = ob.curLen;
	my_strcpy(ch, ob.ch);
	fail();
}

//复制构造函数：从已有字符数组*init复制
String::String(const char* init)
{
	ch = new char[maxLen + 1];
	if (!ch) {
		cerr << "存储分配错！" << endl;
		exit(1);
	}
	curLen = strlen(init);
	my_strcpy(ch, init);
	fail();
}

//构造函数：创建一个空串
String::String()
{
	ch = new char[maxLen + 1];
	if (!ch) {
		cerr << "存储分配错！" << endl;
		exit(1);
	}
	curLen = 0;
	ch[0] = '\0';
	fail();
}

//从串中第pos个位置起连续提取len个字符形成子串返回
String& String::operator()(int pos, int len)
{
	String* temp = new String;//动态分配
	if (pos < 0 || pos + len - 1 >= maxLen || len < 0) {
		temp->curLen = 0;//返回空串
		temp->ch[0] = '\0';
	}
	else {	//提取子串
		if (pos + len - 1 >= curLen)
			len = curLen - pos;
		temp->curLen = len;//子串长度
		for (int i = 0, j = pos;i < len;i++, j++)
			temp->ch[i] = ch[j];//传送串数组
		temp->ch[len] = '\0';//子串结束
	}
	return *temp;
}

//串重载操作：串赋值
String& String::operator=(const String& ob)
{
	if (&ob != this) {	//若两个串相等为自我赋值
		delete[]ch;
		ch = new char[maxLen];//重新分配
		if (!ch) {
			cerr << "存储分配错！" << endl;
			exit(1);
		}
		curLen = ob.curLen;
		my_strcpy(ch, ob.ch);
	}
	else {
		cout << "字符串自身赋值出错！" << endl;
	}
	return *this;
}

//串重载操作：串连接
String& String::operator+=(const String& ob)
{
	char* temp = ch;//暂存原串数组
	curLen += ob.curLen;//串长度累加
	ch = new char[maxLen + 1];
	if (!ch) {
		cerr << "存储分配错！" << endl;
		exit(1);
	}
	my_strcpy(ch, temp);//复制原串数组
	my_strcat(ch, ob.ch);//连接ob串数组
	delete[]temp;
	return *this;
}

//串重载操作：取当前串*this的第i个字符
char& String::operator[](int i)
{
	curLen = strlen(ch);
	if (i < 0 || i >= curLen) {
		cout << "字符串下标超界！" << endl;
		exit(1);
	}
	return ch[i];
}

void String::getline(istream& is, String& str)
{
	char buffer[maxLen];
	is.getline(buffer, maxLen);
	str = buffer;
}

bool String::getlineFile(ifstream& inFile, String& str)
{
	char buffer[maxLen];
	if (inFile.getline(buffer, maxLen)){
		str = buffer;
		return true;
	}
	return false;
}

//计算失效函数
void String::fail()
{
	int lengthP = curLen;
	f[0] = -1;//直接复制
	for (int j = 1;j < lengthP;j++) { //依次求f[j]
		int i = f[j - 1];
		while (*(ch + j) != *(ch + i + 1) && i >= 0)
			i = f[i];  //递推
		if (*(ch + j) == *(ch + i + 1))
			f[j] = i + 1;
		else
			f[j] = -1;
	}
}

//带失效函数的KMP匹配算法
int String::fastFind(String& pat) const
{
	int posP = 0, posT = 0;// posP: 指向关键字pat的当前位置, posT: 指向当前字符串的位置
	int lengthP = pat.curLen, lengthT = curLen;// lengthP: 关键字pat的长度, lengthT: 当前字符串的长度
	pat.fail();// 计算关键字的失效函数
	int count = 0;  //用于统计关键字出现的次数
	while (posT < lengthT) {
		if (pat.ch[posP] == ch[posT]) {
			//相等继续比较
			posP++;
			posT++;
			if (posP == lengthP) {
				//匹配成功，关键字出现
				count++;
				posP = pat.f[posP - 1] + 1;// 重置posP，继续寻找下一个匹配
			}
		}
		else if (posP == 0) {// 不匹配，且关键字的第一个字符不匹配，移动当前字符串的指针
			posT++;
		}
		else {// 不匹配，根据失效函数调整关键字的位置
			posP = pat.f[posP - 1] + 1;
		}
	}
	return count;
}

//判断字符串中只有字母
bool String::onlyAlpha() {
	curLen = strlen(ch);
	for (int i = 0; i < curLen; ++i) {
		if (!isalpha(ch[i])) {
			return false;  // 如果遇到非字母字符，返回 false
		}
	}
	return true;  // 如果所有字符都是字母，返回 true
}

// 自定义getline函数
void customGetline(istream& is, string& str) {
	char ch;
	str = "";  // 清空字符串
	while (is.get(ch) && ch != '\n') {
		str += ch;
	}
}

// 自定义从文件读取一行的函数
bool customGetlineFile(ifstream& inFile, string& str) {
	char ch;
	str = "";  // 清空字符串
	while (inFile.get(ch) && ch != '\n') {
		str += ch;
	}
	return inFile.good();  // 返回是否读取成功
}

// 写入文本到文件的函数
void writeToFile(const string& fileName) {
	ofstream outFile(fileName);
	string temp;
	cout << endl << "请输入英文文本(最后一行输入一个^并回车以结束)：" << endl;
	
	// 使用 cin.ignore() 来清除换行符
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	// 写入到文件
	while (true) {
		customGetline(cin, temp);
		if (temp.size() > maxLen) {
			cout << "存储分配错!请重新输入本段内容！" << endl;
			continue;
		}

		if (temp == "^") {
			break;
		}
		outFile << temp << endl;
	}
	if (outFile.good())
		cout << "此文本已经保存在文本文件\"" << fileName << "\"中。" << endl;
	outFile.close();
}

// 从文件读取文本并输出到控制台的函数
void readAndOutputFile(const string& fileName, String& keyword) {
	ifstream inFile(fileName);
	string temp;
	int keywordCount = 0;

	cout << endl << "显示源文件\"" << fileName << "\":" << endl;

	// 从文件读取并输出到控制台
	while (customGetlineFile(inFile, temp)) {
		cout << temp << endl;
		keywordCount += String(temp.c_str()).fastFind(keyword);
	}
	inFile.close();
	cout << endl << "关键字 \"" << keyword.getCharArray() << "\" 在文本中出现的次数为: " << keywordCount << endl;
}
int main() {
	cout << "关键字检索系统" << endl << endl;
	while (1) {
		string fileName;
		cout << "请输入文件名（请包含 .txt 扩展名）：";
		cin >> fileName;
		// 检查文件名是否以 .txt 结尾，如果不是则添加扩展名
		if (fileName.length() < 4 || fileName.substr(fileName.length() - 4) != ".txt") {
			fileName += ".txt";
		}

		// 写入文本到文件
		writeToFile(fileName);

		String keyword;
		cout << endl << "请输入不含空格的关键字: ";
		while (1) {
			cin >> keyword;
			if (keyword.onlyAlpha())
				break;
			else {
				cout << "输入内容包含非字母字符，请重新输入关键字。" << endl;
				keyword = "";
				continue;
			}
		}

		// 从文件读取文本并输出到控制台
		readAndOutputFile(fileName, keyword);

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

/*
测试数据：
With over two billion pages and more being added daily, the Web is a massive collection of interrelated pages. With so much available information, locating the precise information you need can be difficult. Fortunately, a number of organizations called search services or search providers can help you locate the information you need. They maintain huge databases relating to information provided on the Web and the Internet. The information stored at the databases includes addresses, content descriptions or classifications, and keywords appearing on Web pages and other Internet informational resources.
*/