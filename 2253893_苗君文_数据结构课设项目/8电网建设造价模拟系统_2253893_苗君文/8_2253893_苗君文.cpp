#include<iostream>
using namespace std;

#define maxValue 1000
#define maxEdges 100
#define DefaultSize 100
#define maxVertices 50

template<class T,class E>
struct MSTEdgeNode {  //��С�������߽��
    int tail, head;  //������λ��
    E key;  //���ϵ�Ȩֵ
    MSTEdgeNode() :tail(-1), head(-1), key(0) {}  //���캯��
    bool operator<=(MSTEdgeNode<T,E>& R) { return key <= R.key; }
    bool operator>(MSTEdgeNode<T,E>& R) { return key > R.key; }

};

template<class T,class E>
class MinSpanTree {  //��С���������ඨ��
protected:
    MSTEdgeNode<T,E>edgevalue[maxEdges];  //�ñ�ֵ�����ʾ��
    int maxSize;//��������Ԫ�ظ���
    int n;//��ǰ����
public:
    MinSpanTree() : maxSize(maxEdges), n(0) {}
    int Insert(MSTEdgeNode<T,E>item);
	void getEdgevalue(int i, int &tail, int &head, E &key);
	int getEdgeNum() { return n; }
};

template<class T,class E>
int MinSpanTree<T,E>::Insert(MSTEdgeNode<T,E> item)
{
    if (n < maxEdges) {
        edgevalue[n++] = item;
        return 1;
    }
    else {
        return 0;
    }
}

template<class T, class E>
void MinSpanTree<T,E>::getEdgevalue(int i, int& tail, int& head, E& key)
{
	tail = edgevalue[i].tail;
	head = edgevalue[i].head;
	key = edgevalue[i].key;
}

template<class T, class E>
struct Element {
	T key;
	E other;
	Element<T, E>& operator=(Element<T, E>& x)
	{
		key = x.key;
		other = x.other;
		return *this;
	}
	bool operator<=(Element<T, E>& x) { return key <= x.key; }
	bool operator<(Element<T, E>& x) { return key < x.key; }
	bool operator>=(Element<T, E>& x) { return key >= x.key; }
	bool operator>(Element<T, E>& x) { return key > x.key; }
};

template<class T, class E>
class minHeap {
private:
	MSTEdgeNode<T, E>* heap;
	int currentSize;
	int maxHeapSize;
	void siftDown(int start, int m);//��С�ѵ��»�����
	void siftUp(int start);//�ϻ�����
	void Swap(int u, int v)
	{
		Element<T, E>tmp = heap[u];
		heap[u] = heap[v];
		heap[v] = tmp;
	}
public:
	minHeap(int sz = DefaultSize) {
		heap = new MSTEdgeNode<T, E>[sz];
		currentSize = 0;
		maxHeapSize = sz;
	}
	~minHeap() { delete[]heap; }
	bool Insert(const MSTEdgeNode<T, E>& x);
	bool Remove(MSTEdgeNode<T, E>& x);
	bool IsEmpty() { return currentSize == 0; }
	bool IsFull() { return currentSize == maxHeapSize; }
};

template<class T, class E>
void minHeap<T, E>::siftDown(int start, int m)
{
	int i = start, j = 2 * i + 1;//j��i������Ů
	MSTEdgeNode<T, E>temp = heap[i];
	while (j <= m) {
		if (j<m && heap[j]>heap[j + 1])
			j++;//��jָ������Ů�е�С��
		if (temp <= heap[j])
			break;//С��������
		else {
			heap[i] = heap[j];
			i = j;
			j = 2 * j + 1;
		}//����С�����ƣ�i��j�½�
	}
	heap[i] = temp;//�ط�temp���ݴ��Ԫ��
}

template<class T, class E>
void minHeap<T, E>::siftUp(int start)
{
	int j = start, i = (j - 1) / 2;
	MSTEdgeNode<T, E>temp = heap[j];
	while (j > 0) {  //�ظ��ڵ�·������ֱ���
		if (heap[i] <= temp)
			break;//���ڵ�ֵС��������
		else {  //���ڵ�ֵ�󣬵���
			heap[j] = heap[i];
			j = i;
			i = (i - 1) / 2;
		}
	}
	heap[j] = temp;//����
}

template<class T, class E>
bool minHeap<T, E>::Insert(const MSTEdgeNode<T, E>& x)
{
	if (IsFull()) {
		cout << "��С��������" << endl;
		return false;
	}
	heap[currentSize] = x;//����
	siftUp(currentSize);//���ϵ���
	currentSize++;
	return true;
}

template<class T, class E>
bool minHeap<T, E>::Remove(MSTEdgeNode<T, E>& x)
{
	if (!currentSize) {
		cout << "��С��Ϊ�գ��޷�ɾ����" << endl;
		return false;
	}
	x = heap[0];
	heap[0] = heap[currentSize - 1];//���Ԫ��������ڵ�
	currentSize--;
	siftDown(0, currentSize - 1);//�������µ���Ϊ��
	return true;
}

template<class T, class E>
struct Edge {
	int dest;
	E cost;
	Edge<T, E>* link;
	Edge() :dest(-1), cost(0), link(NULL) {}
	Edge(int num, E weight) :dest(num), cost(weight), link(NULL) {}
	bool operator!=(Edge<T, E>& R)const {
		return (dest != R.dest) ? true : false;
	}
};

template<class T, class E>
struct Vertex {
	T data;//���������
	Edge<T, E>* adj;//�������ͷָ��
};

template<class T, class E>
class Graphlnk {
private:
	Vertex<T, E>NodeTable[maxVertices];  //��������������ͷ��㣩
	int numVertices;
	int numEdges;
public:
	Graphlnk(int sz = maxVertices);
	~Graphlnk();
	int getVertexPos(T vertex);  //ȡ����vertex�ڽ����е����
	T getValue(int i) {
		return (i >= 0 && i < numVertices) ? NodeTable[i].data : '0';
	}
	E getWeight(int v1, int v2);
	int insertVertex(T vertex);//��ͼ�в���һ������vertex
	bool insertEdge(int v1, int v2, E cost);
	int getFirstNeighbor(int v);//ȡ����v�ĵ�һ���ڽӶ���
	int getNextNeighbor(int v, int w);//ȡv���ڽӶ���w����һ���ڽӶ���
	int NumOfVertices() { return numVertices; }
	int NumOfEdges() { return numEdges; }
	bool searchVertex(T vertex);//�ҵ�
	void clear();
};

template<class T, class E>
int Graphlnk<T, E>::getVertexPos(T vertex) {
	for (int i = 0;i < numVertices;i++) {
		if (NodeTable[i].data == vertex)
			return i;
	}
	return -1;
}

template<class T, class E>
Graphlnk<T, E>::Graphlnk(int sz)
{
	numVertices = 0;
	numEdges = 0;
	for (int i = 0;i < maxVertices;i++)
		NodeTable[i].adj = NULL;
}

template<typename T, typename E>
Graphlnk<T, E>::~Graphlnk()
{
	for (int i = 0; i < numVertices; ++i) {
		Edge<T, E>* p = NodeTable[i].adj;
		while (p != NULL) {
			NodeTable[i].adj = p->link;
			delete p;
			p = NodeTable[i].adj;
		}
	}
}

template<typename T, typename E>
int Graphlnk<T, E>::getFirstNeighbor(int v) {
	if (v != -1) {
		Edge<T, E>* p = NodeTable[v].adj;
		if (p != NULL)
			return p->dest;
	}
	return -1;
}

template<typename T, typename E>
int Graphlnk<T, E>::getNextNeighbor(int v, int w) {
	if (v != -1) {
		Edge<T, E>* p = NodeTable[v].adj;
		while (p != NULL && p->dest != w) {
			p = p->link;
		}
		if (p != NULL && p->link != NULL) {
			return p->link->dest;
		}
	}
	return -1;
}

template<class T, class E>
bool Graphlnk<T, E>::searchVertex(T vertex)
{
	for (int i = 0; i < numVertices; i++) {
		if (NodeTable[i].data == vertex) {
			return true;
		}
	}
	return false;
}

template<class T, class E>
void Graphlnk<T, E>::clear()
{
	for (int i = 0; i < numVertices; ++i) {
		Edge<T, E>* p = NodeTable[i].adj;
		while (p != NULL) {
			NodeTable[i].adj = p->link;
			delete p;
			p = NodeTable[i].adj;
		}
	}
	numVertices = 0;
	numEdges = 0;
}//���ͼ�бߺ͵�

template<typename T, typename E>
E Graphlnk<T, E>::getWeight(int v1, int v2) {
	if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices) {
		Edge<T, E>* p = NodeTable[v1].adj;
		while (p != NULL && p->dest != v2) {
			p = p->link;
		}
		if (p != NULL) {
			return p->cost;
		}
	}
	return 0;//�߲���ͼ�У�����0
}

template<typename T, typename E>
int Graphlnk<T, E>::insertVertex(T vertex) {
	if (numVertices == maxVertices) {
		return -1;
	}
	for (int i = 0; i < numVertices; ++i) {
		if (NodeTable[i].data == vertex) {
			return -2;
		}
	}
	NodeTable[numVertices].data = vertex;
	NodeTable[numVertices].adj = NULL;
	numVertices++;
	return 1;
}

template<class T, class E>
bool Graphlnk<T, E>::insertEdge(int v1, int v2, E weight) {
	if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices) {
		Edge<T, E>* q;
		Edge<T, E>* p = NodeTable[v1].adj;
		while (p != NULL && p->dest != v2) {
			p = p->link;
		}//Ѱ���ڽӶ���v2
		if (p != NULL) {
			return false;
		}//�ҵ��˱ߣ�������
		p = new Edge<T, E>;
		q = new Edge<T, E>;
		p->dest = v2;
		p->cost = weight;
		p->link = NodeTable[v1].adj;
		NodeTable[v1].adj = p;//����v1������
		q->dest = v1;
		q->cost = weight;
		q->link = NodeTable[v2].adj;
		NodeTable[v2].adj = q;//����v2������
		numEdges++;
		return true;
	}
	else {
		cout << "�����±�Խ�硣" << endl;
		return false;
	}
}

template<class T,class E>
void Prim(Graphlnk<T, E>& G, T u0, MinSpanTree<T,E>& MST) {
	MSTEdgeNode<T,E>ed;
	int i, u, v, count;
	int n = G.NumOfVertices();
	int m = G.NumOfEdges();
	u = G.getVertexPos(u0);
	minHeap<T, E>H(m);
	bool* Vmst = new bool[n]; //��С���������㼯��
	for (i = 0;i < n;i++)
		Vmst[i] = false;
	Vmst[u] = true;  //u����������
	count = 1;
	do {
		v = G.getFirstNeighbor(u);
		while (v != -1) {
			if (Vmst[v] == false) {
				ed.head = v;
				ed.tail = u;
				ed.key = G.getWeight(u, v);
				H.Insert(ed);
			}
			v = G.getNextNeighbor(u, v);
		}
		while (!(H.IsEmpty()) && count < n) {
			H.Remove(ed);
			if (Vmst[ed.head] == false) {
				MST.Insert(ed);
				u = ed.head;
				Vmst[u] = true;
				count++;
				break;
			}
		}
	} while (count < n);	
}

int main()
{
	cout << "**              �����������ģ��ϵͳ           **" << endl;
	cout << "================================================" << endl;
	cout << "**                A---������������             **" << endl;
	cout << "**                B---��ӵ����ı�             **" << endl;
	cout << "**                C---������С������           **" << endl;
	cout << "**                D---��ʾ��С������           **" << endl;
	cout << "**                E---�˳�����                 **" << endl;
	cout << "================================================" << endl;

	Graphlnk<char, int>G;//����ͼ����
	MinSpanTree<char, int>MST;//������С����������
    
    while (1) {
        char choice;
        while (1) {
            cout << endl;
            cout << "��ѡ��Ҫִ�еĲ�����";
            cin >> choice;
            char c;
            if (cin.fail() || (choice != 'a' && choice != 'A' && choice != 'b' && choice != 'B' && choice != 'c' && choice != 'C' && choice != 'd' && choice != 'D' && choice != 'e' && choice != 'E')) {
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

        if (choice == 'A' || choice == 'a') {
            //������������

			//���붥�����
			int numVertices;
			while (1) {
				cout << "�����붥��ĸ���(2-50)��";
				char c;  //������ȡ����һ����֮���һ���ַ�������ȡһ���ַ��ҷǻ��з�����Ϊ�������
				cin >> numVertices;
				if (cin.fail() || numVertices < 2 || numVertices > maxVertices) {
					cout << "����������������롣" << endl;
					cin.clear();
					cin.ignore(9999999, '\n');
					continue;
				}  //���ݴ���
				else if (cin.get(c) && c != '\n') {
					cout << "����������������롣" << endl;
					cin.clear();
					cin.ignore(9999999, '\n');
					continue;
				}  //��������
				else
					break;
			}

			//�������������
			char* vName = new char[numVertices];
            cout << "��������������������(Сд��ĸ)��" << endl;
			while (1) {
				bool judge = 0;//�ж��Ƿ���Ҫ��������ؼ���
				G.clear();
				for (int i = 0;i < numVertices;i++) {
					cin >> vName[i];
					if (cin.fail() || vName[i] < 'a' || vName[i] >= 'z') {
						cout << "����Ƿ����������������ж������ƣ�" << endl;
						cin.clear();
						cin.ignore(9999999, '\n');
						judge = 1;
						break;
					}
					if (G.insertVertex(vName[i]) == -2) {
						cout << "����Ķ��㣨" << vName[i] << "�����ڵ����У�" << endl;
					}
				}
				if (judge)
					continue;
				char c;
				if (cin.get(c) && c != '\n') {
					cout << "����Ķ�������������������������ж������ƣ�" << endl;
					cin.clear();
					cin.ignore(9999999, '\n');
					continue;
				}
				else
					break;
			}
			continue;
        }
        else if (choice == 'B' || choice == 'b') {
            //��ӵ����ı�

			if (G.NumOfVertices() == 0) {
				cout << "�������޶��㣬���ȴ����������㡣" << endl;
				continue;
			}

			//����ߵĸ���
			int numEdges;
			while (1) {
				cout << "������Ҫ��ӵıߵĸ���(1-100)��";
				char c;  //������ȡ����һ����֮���һ���ַ�������ȡһ���ַ��ҷǻ��з�����Ϊ�������
				cin >> numEdges;
				if (cin.fail() || numEdges < 1 || numEdges > maxEdges) {
					cout << "����������������롣" << endl;
					cin.clear();
					cin.ignore(9999999, '\n');
					continue;
				}  //���ݴ���
				else if (cin.get(c) && c != '\n') {
					cout << "����������������롣" << endl;
					cin.clear();
					cin.ignore(9999999, '\n');
					continue;
				}  //��������
				else
					break;
			}

			//���������㼰Ȩֵ
            cout << "�������������㼰�ߵ�Ȩֵ���磺a b 8" << endl;
			for (int i = 0;i < numEdges;i++) {
				char v1, v2;
				int weight;
				while (1) {
					bool judge = 0;  //�ж��Ƿ���Ҫ��������
					cout << "�������" << i + 1 << "���ߵ���Ϣ��";
					cin >> v1 >> v2 >> weight;
					if (cin.fail() || !G.searchVertex(v1) || !G.searchVertex(v2) || weight<1 || weight>maxValue) {
						judge = true;
					}//��������ݴ���
					char c;  //������ȡ�����ַ�
					if (judge == false && cin.get(c) && c != '\n') {
						judge = true;
					}  //�����Ԫ�ظ�������
					if (judge) {
						cin.clear();
						cin.ignore(9999, '\n');
						cout << "����������������롣" << endl;
						continue;
					}
					else
						break;
				}
				int V1, V2;
				V1 = G.getVertexPos(v1);
				V2 = G.getVertexPos(v2);
				if (!G.insertEdge(V1, V2, weight))//�ѱ߼ӵ�ͼ��
					cout << v1 << "->" << v2 << "�ı��Ѵ��ڣ�������롣" << endl;
			}
			continue;
        }
        else if (choice == 'C' || choice == 'c') {
            //������С������

			if (G.NumOfVertices() == 0||G.NumOfEdges() == 0) {
				cout << "�����������ݣ����ȴ����������㡣" << endl;
				continue;
			}

			char startV;
			while (1) {
				cout << "��������ʼ���㣺";
				char c;  //������ȡ����һ����֮���һ���ַ�������ȡһ���ַ��ҷǻ��з�����Ϊ�������
				cin >> startV;
				if (cin.fail() || !G.searchVertex(startV)) {
					cout << "����������������롣" << endl;
					cin.clear();
					cin.ignore(9999999, '\n');
					continue;
				}  //���ݴ���
				else if (cin.get(c) && c != '\n') {
					cout << "����������������롣" << endl;
					cin.clear();
					cin.ignore(9999999, '\n');
					continue;
				}  //��������
				else
					break;
			}

			Prim(G, startV, MST);
            cout << "������Prim��С��������" << endl;
			continue;
        }
        else if (choice == 'D' || choice == 'd') {
            //��ʾ��С������

			if (G.NumOfVertices() == 0 || G.NumOfEdges() == 0) {
				cout << "�����������ݣ����ȴ����������㡣" << endl;
				continue;
			}
			if (MST.getEdgeNum() == 0) {
				cout << "��δ������С������������������С��������" << endl;
				continue;
			}

            cout << "��С�������Ķ��㼰��Ϊ��" << endl;
			int n = MST.getEdgeNum();
			for (int i = 0;i < n;i++) {
				int h, t, k;
				MST.getEdgevalue(i, t, h, k);
				char head, tail;
				head = G.getValue(h);
				tail = G.getValue(t);
				cout << tail << "-(" << k << ")->" << head << "       ";
				if (i % 4 == 0 && i != 0 && i != n - 1)
					cout << endl;
			}
			cout << endl;
			continue;
        }
        else if (choice == 'E' || choice == 'e') {
            //�˳�����
            cout << "���˳�����ӭ�´�ʹ�ã�" << endl;
			break;
        }
    }
	return 0;
}