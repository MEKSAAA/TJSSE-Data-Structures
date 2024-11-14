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
	char* ch;//���Ĵ洢����
	int curLen;//���ĵ�ǰ����
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

//���ƹ��캯���������д�ob����
String::String(const String& ob)
{
	ch = new char[maxLen + 1];
	if (!ch) {
		cerr << "�洢�����" << endl;
		exit(1);
	}
	curLen = ob.curLen;
	my_strcpy(ch, ob.ch);
	fail();
}

//���ƹ��캯�����������ַ�����*init����
String::String(const char* init)
{
	ch = new char[maxLen + 1];
	if (!ch) {
		cerr << "�洢�����" << endl;
		exit(1);
	}
	curLen = strlen(init);
	my_strcpy(ch, init);
	fail();
}

//���캯��������һ���մ�
String::String()
{
	ch = new char[maxLen + 1];
	if (!ch) {
		cerr << "�洢�����" << endl;
		exit(1);
	}
	curLen = 0;
	ch[0] = '\0';
	fail();
}

//�Ӵ��е�pos��λ����������ȡlen���ַ��γ��Ӵ�����
String& String::operator()(int pos, int len)
{
	String* temp = new String;//��̬����
	if (pos < 0 || pos + len - 1 >= maxLen || len < 0) {
		temp->curLen = 0;//���ؿմ�
		temp->ch[0] = '\0';
	}
	else {	//��ȡ�Ӵ�
		if (pos + len - 1 >= curLen)
			len = curLen - pos;
		temp->curLen = len;//�Ӵ�����
		for (int i = 0, j = pos;i < len;i++, j++)
			temp->ch[i] = ch[j];//���ʹ�����
		temp->ch[len] = '\0';//�Ӵ�����
	}
	return *temp;
}

//�����ز���������ֵ
String& String::operator=(const String& ob)
{
	if (&ob != this) {	//�����������Ϊ���Ҹ�ֵ
		delete[]ch;
		ch = new char[maxLen];//���·���
		if (!ch) {
			cerr << "�洢�����" << endl;
			exit(1);
		}
		curLen = ob.curLen;
		my_strcpy(ch, ob.ch);
	}
	else {
		cout << "�ַ�������ֵ����" << endl;
	}
	return *this;
}

//�����ز�����������
String& String::operator+=(const String& ob)
{
	char* temp = ch;//�ݴ�ԭ������
	curLen += ob.curLen;//�������ۼ�
	ch = new char[maxLen + 1];
	if (!ch) {
		cerr << "�洢�����" << endl;
		exit(1);
	}
	my_strcpy(ch, temp);//����ԭ������
	my_strcat(ch, ob.ch);//����ob������
	delete[]temp;
	return *this;
}

//�����ز�����ȡ��ǰ��*this�ĵ�i���ַ�
char& String::operator[](int i)
{
	curLen = strlen(ch);
	if (i < 0 || i >= curLen) {
		cout << "�ַ����±곬�磡" << endl;
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

//����ʧЧ����
void String::fail()
{
	int lengthP = curLen;
	f[0] = -1;//ֱ�Ӹ���
	for (int j = 1;j < lengthP;j++) { //������f[j]
		int i = f[j - 1];
		while (*(ch + j) != *(ch + i + 1) && i >= 0)
			i = f[i];  //����
		if (*(ch + j) == *(ch + i + 1))
			f[j] = i + 1;
		else
			f[j] = -1;
	}
}

//��ʧЧ������KMPƥ���㷨
int String::fastFind(String& pat) const
{
	int posP = 0, posT = 0;// posP: ָ��ؼ���pat�ĵ�ǰλ��, posT: ָ��ǰ�ַ�����λ��
	int lengthP = pat.curLen, lengthT = curLen;// lengthP: �ؼ���pat�ĳ���, lengthT: ��ǰ�ַ����ĳ���
	pat.fail();// ����ؼ��ֵ�ʧЧ����
	int count = 0;  //����ͳ�ƹؼ��ֳ��ֵĴ���
	while (posT < lengthT) {
		if (pat.ch[posP] == ch[posT]) {
			//��ȼ����Ƚ�
			posP++;
			posT++;
			if (posP == lengthP) {
				//ƥ��ɹ����ؼ��ֳ���
				count++;
				posP = pat.f[posP - 1] + 1;// ����posP������Ѱ����һ��ƥ��
			}
		}
		else if (posP == 0) {// ��ƥ�䣬�ҹؼ��ֵĵ�һ���ַ���ƥ�䣬�ƶ���ǰ�ַ�����ָ��
			posT++;
		}
		else {// ��ƥ�䣬����ʧЧ���������ؼ��ֵ�λ��
			posP = pat.f[posP - 1] + 1;
		}
	}
	return count;
}

//�ж��ַ�����ֻ����ĸ
bool String::onlyAlpha() {
	curLen = strlen(ch);
	for (int i = 0; i < curLen; ++i) {
		if (!isalpha(ch[i])) {
			return false;  // �����������ĸ�ַ������� false
		}
	}
	return true;  // ��������ַ�������ĸ������ true
}

// �Զ���getline����
void customGetline(istream& is, string& str) {
	char ch;
	str = "";  // ����ַ���
	while (is.get(ch) && ch != '\n') {
		str += ch;
	}
}

// �Զ�����ļ���ȡһ�еĺ���
bool customGetlineFile(ifstream& inFile, string& str) {
	char ch;
	str = "";  // ����ַ���
	while (inFile.get(ch) && ch != '\n') {
		str += ch;
	}
	return inFile.good();  // �����Ƿ��ȡ�ɹ�
}

// д���ı����ļ��ĺ���
void writeToFile(const string& fileName) {
	ofstream outFile(fileName);
	string temp;
	cout << endl << "������Ӣ���ı�(���һ������һ��^���س��Խ���)��" << endl;
	
	// ʹ�� cin.ignore() ��������з�
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	// д�뵽�ļ�
	while (true) {
		customGetline(cin, temp);
		if (temp.size() > maxLen) {
			cout << "�洢�����!���������뱾�����ݣ�" << endl;
			continue;
		}

		if (temp == "^") {
			break;
		}
		outFile << temp << endl;
	}
	if (outFile.good())
		cout << "���ı��Ѿ��������ı��ļ�\"" << fileName << "\"�С�" << endl;
	outFile.close();
}

// ���ļ���ȡ�ı������������̨�ĺ���
void readAndOutputFile(const string& fileName, String& keyword) {
	ifstream inFile(fileName);
	string temp;
	int keywordCount = 0;

	cout << endl << "��ʾԴ�ļ�\"" << fileName << "\":" << endl;

	// ���ļ���ȡ�����������̨
	while (customGetlineFile(inFile, temp)) {
		cout << temp << endl;
		keywordCount += String(temp.c_str()).fastFind(keyword);
	}
	inFile.close();
	cout << endl << "�ؼ��� \"" << keyword.getCharArray() << "\" ���ı��г��ֵĴ���Ϊ: " << keywordCount << endl;
}
int main() {
	cout << "�ؼ��ּ���ϵͳ" << endl << endl;
	while (1) {
		string fileName;
		cout << "�������ļ���������� .txt ��չ������";
		cin >> fileName;
		// ����ļ����Ƿ��� .txt ��β����������������չ��
		if (fileName.length() < 4 || fileName.substr(fileName.length() - 4) != ".txt") {
			fileName += ".txt";
		}

		// д���ı����ļ�
		writeToFile(fileName);

		String keyword;
		cout << endl << "�����벻���ո�Ĺؼ���: ";
		while (1) {
			cin >> keyword;
			if (keyword.onlyAlpha())
				break;
			else {
				cout << "�������ݰ�������ĸ�ַ�������������ؼ��֡�" << endl;
				keyword = "";
				continue;
			}
		}

		// ���ļ���ȡ�ı������������̨
		readAndOutputFile(fileName, keyword);

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

/*
�������ݣ�
With over two billion pages and more being added daily, the Web is a massive collection of interrelated pages. With so much available information, locating the precise information you need can be difficult. Fortunately, a number of organizations called search services or search providers can help you locate the information you need. They maintain huge databases relating to information provided on the Web and the Internet. The information stored at the databases includes addresses, content descriptions or classifications, and keywords appearing on Web pages and other Internet informational resources.
*/