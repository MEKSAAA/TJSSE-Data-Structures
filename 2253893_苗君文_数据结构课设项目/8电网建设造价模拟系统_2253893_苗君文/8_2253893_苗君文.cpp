#include<iostream>
using namespace std;

#define maxValue 1000
#define maxEdges 100
#define DefaultSize 100
#define maxVertices 50

template<class T,class E>
struct MSTEdgeNode {  //最小生成树边结点
    int tail, head;  //两顶点位置
    E key;  //边上的权值
    MSTEdgeNode() :tail(-1), head(-1), key(0) {}  //构造函数
    bool operator<=(MSTEdgeNode<T,E>& R) { return key <= R.key; }
    bool operator>(MSTEdgeNode<T,E>& R) { return key > R.key; }

};

template<class T,class E>
class MinSpanTree {  //最小生成树的类定义
protected:
    MSTEdgeNode<T,E>edgevalue[maxEdges];  //用边值数组表示树
    int maxSize;//数组的最大元素个数
    int n;//当前个数
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
	void siftDown(int start, int m);//最小堆的下滑调整
	void siftUp(int start);//上滑调整
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
	int i = start, j = 2 * i + 1;//j是i的左子女
	MSTEdgeNode<T, E>temp = heap[i];
	while (j <= m) {
		if (j<m && heap[j]>heap[j + 1])
			j++;//让j指向两子女中的小者
		if (temp <= heap[j])
			break;//小则不做调整
		else {
			heap[i] = heap[j];
			i = j;
			j = 2 * j + 1;
		}//否则小者上移，i，j下降
	}
	heap[i] = temp;//回放temp中暂存的元素
}

template<class T, class E>
void minHeap<T, E>::siftUp(int start)
{
	int j = start, i = (j - 1) / 2;
	MSTEdgeNode<T, E>temp = heap[j];
	while (j > 0) {  //沿父节点路径向上直达根
		if (heap[i] <= temp)
			break;//父节点值小，不调整
		else {  //父节点值大，调整
			heap[j] = heap[i];
			j = i;
			i = (i - 1) / 2;
		}
	}
	heap[j] = temp;//回送
}

template<class T, class E>
bool minHeap<T, E>::Insert(const MSTEdgeNode<T, E>& x)
{
	if (IsFull()) {
		cout << "最小堆已满！" << endl;
		return false;
	}
	heap[currentSize] = x;//插入
	siftUp(currentSize);//向上调整
	currentSize++;
	return true;
}

template<class T, class E>
bool minHeap<T, E>::Remove(MSTEdgeNode<T, E>& x)
{
	if (!currentSize) {
		cout << "最小堆为空，无法删除！" << endl;
		return false;
	}
	x = heap[0];
	heap[0] = heap[currentSize - 1];//最后元素填补到根节点
	currentSize--;
	siftDown(0, currentSize - 1);//从上向下调整为堆
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
	T data;//顶点的名字
	Edge<T, E>* adj;//边链表的头指针
};

template<class T, class E>
class Graphlnk {
private:
	Vertex<T, E>NodeTable[maxVertices];  //顶点表（各边链表的头结点）
	int numVertices;
	int numEdges;
public:
	Graphlnk(int sz = maxVertices);
	~Graphlnk();
	int getVertexPos(T vertex);  //取顶点vertex在结点表中的序号
	T getValue(int i) {
		return (i >= 0 && i < numVertices) ? NodeTable[i].data : '0';
	}
	E getWeight(int v1, int v2);
	int insertVertex(T vertex);//在图中插入一个顶点vertex
	bool insertEdge(int v1, int v2, E cost);
	int getFirstNeighbor(int v);//取顶点v的第一个邻接顶点
	int getNextNeighbor(int v, int w);//取v的邻接顶点w的下一个邻接顶点
	int NumOfVertices() { return numVertices; }
	int NumOfEdges() { return numEdges; }
	bool searchVertex(T vertex);//找点
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
}//清除图中边和点

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
	return 0;//边不在图中，返回0
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
		}//寻找邻接顶点v2
		if (p != NULL) {
			return false;
		}//找到此边，不插入
		p = new Edge<T, E>;
		q = new Edge<T, E>;
		p->dest = v2;
		p->cost = weight;
		p->link = NodeTable[v1].adj;
		NodeTable[v1].adj = p;//链入v1边链表
		q->dest = v1;
		q->cost = weight;
		q->link = NodeTable[v2].adj;
		NodeTable[v2].adj = q;//链入v2边链表
		numEdges++;
		return true;
	}
	else {
		cout << "顶点下标越界。" << endl;
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
	bool* Vmst = new bool[n]; //最小生成树顶点集合
	for (i = 0;i < n;i++)
		Vmst[i] = false;
	Vmst[u] = true;  //u加入生成树
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
	cout << "**              电网建设造价模拟系统           **" << endl;
	cout << "================================================" << endl;
	cout << "**                A---创建电网顶点             **" << endl;
	cout << "**                B---添加电网的边             **" << endl;
	cout << "**                C---构造最小生成树           **" << endl;
	cout << "**                D---显示最小生成树           **" << endl;
	cout << "**                E---退出程序                 **" << endl;
	cout << "================================================" << endl;

	Graphlnk<char, int>G;//创建图对象
	MinSpanTree<char, int>MST;//创建最小生成树对象
    
    while (1) {
        char choice;
        while (1) {
            cout << endl;
            cout << "请选择要执行的操作：";
            cin >> choice;
            char c;
            if (cin.fail() || (choice != 'a' && choice != 'A' && choice != 'b' && choice != 'B' && choice != 'c' && choice != 'C' && choice != 'd' && choice != 'D' && choice != 'e' && choice != 'E')) {
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

        if (choice == 'A' || choice == 'a') {
            //创建电网顶点

			//输入顶点个数
			int numVertices;
			while (1) {
				cout << "请输入顶点的个数(2-50)：";
				char c;  //用来获取输入一个数之后的一个字符，若获取一个字符且非换行符则视为输入错误。
				cin >> numVertices;
				if (cin.fail() || numVertices < 2 || numVertices > maxVertices) {
					cout << "输入错误，请重新输入。" << endl;
					cin.clear();
					cin.ignore(9999999, '\n');
					continue;
				}  //内容错误
				else if (cin.get(c) && c != '\n') {
					cout << "输入错误，请重新输入。" << endl;
					cin.clear();
					cin.ignore(9999999, '\n');
					continue;
				}  //个数错误
				else
					break;
			}

			//输入各顶点名称
			char* vName = new char[numVertices];
            cout << "请依次输入各顶点的名称(小写字母)：" << endl;
			while (1) {
				bool judge = 0;//判断是否需要重新输入关键码
				G.clear();
				for (int i = 0;i < numVertices;i++) {
					cin >> vName[i];
					if (cin.fail() || vName[i] < 'a' || vName[i] >= 'z') {
						cout << "输入非法，请重新输入所有顶点名称：" << endl;
						cin.clear();
						cin.ignore(9999999, '\n');
						judge = 1;
						break;
					}
					if (G.insertVertex(vName[i]) == -2) {
						cout << "输入的顶点（" << vName[i] << "）已在电网中！" << endl;
					}
				}
				if (judge)
					continue;
				char c;
				if (cin.get(c) && c != '\n') {
					cout << "输入的顶点个数超出，请重新输入所有顶点名称：" << endl;
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
            //添加电网的边

			if (G.NumOfVertices() == 0) {
				cout << "电网内无顶点，请先创建电网顶点。" << endl;
				continue;
			}

			//输入边的个数
			int numEdges;
			while (1) {
				cout << "请输入要添加的边的个数(1-100)：";
				char c;  //用来获取输入一个数之后的一个字符，若获取一个字符且非换行符则视为输入错误。
				cin >> numEdges;
				if (cin.fail() || numEdges < 1 || numEdges > maxEdges) {
					cout << "输入错误，请重新输入。" << endl;
					cin.clear();
					cin.ignore(9999999, '\n');
					continue;
				}  //内容错误
				else if (cin.get(c) && c != '\n') {
					cout << "输入错误，请重新输入。" << endl;
					cin.clear();
					cin.ignore(9999999, '\n');
					continue;
				}  //个数错误
				else
					break;
			}

			//输入两顶点及权值
            cout << "请输入两个顶点及边的权值，如：a b 8" << endl;
			for (int i = 0;i < numEdges;i++) {
				char v1, v2;
				int weight;
				while (1) {
					bool judge = 0;  //判断是否需要重新输入
					cout << "请输入第" << i + 1 << "条边的信息：";
					cin >> v1 >> v2 >> weight;
					if (cin.fail() || !G.searchVertex(v1) || !G.searchVertex(v2) || weight<1 || weight>maxValue) {
						judge = true;
					}//输入的内容错误
					char c;  //用来获取最后的字符
					if (judge == false && cin.get(c) && c != '\n') {
						judge = true;
					}  //输入的元素个数错误
					if (judge) {
						cin.clear();
						cin.ignore(9999, '\n');
						cout << "输入错误，请重新输入。" << endl;
						continue;
					}
					else
						break;
				}
				int V1, V2;
				V1 = G.getVertexPos(v1);
				V2 = G.getVertexPos(v2);
				if (!G.insertEdge(V1, V2, weight))//把边加到图中
					cout << v1 << "->" << v2 << "的边已存在，无需插入。" << endl;
			}
			continue;
        }
        else if (choice == 'C' || choice == 'c') {
            //构造最小生成树

			if (G.NumOfVertices() == 0||G.NumOfEdges() == 0) {
				cout << "电网内无内容，请先创建电网顶点。" << endl;
				continue;
			}

			char startV;
			while (1) {
				cout << "请输入起始顶点：";
				char c;  //用来获取输入一个数之后的一个字符，若获取一个字符且非换行符则视为输入错误。
				cin >> startV;
				if (cin.fail() || !G.searchVertex(startV)) {
					cout << "输入错误，请重新输入。" << endl;
					cin.clear();
					cin.ignore(9999999, '\n');
					continue;
				}  //内容错误
				else if (cin.get(c) && c != '\n') {
					cout << "输入错误，请重新输入。" << endl;
					cin.clear();
					cin.ignore(9999999, '\n');
					continue;
				}  //个数错误
				else
					break;
			}

			Prim(G, startV, MST);
            cout << "已生成Prim最小生成树！" << endl;
			continue;
        }
        else if (choice == 'D' || choice == 'd') {
            //显示最小生成树

			if (G.NumOfVertices() == 0 || G.NumOfEdges() == 0) {
				cout << "电网内无内容，请先创建电网顶点。" << endl;
				continue;
			}
			if (MST.getEdgeNum() == 0) {
				cout << "还未生成最小生成树，请先生成最小生成树。" << endl;
				continue;
			}

            cout << "最小生成树的顶点及边为：" << endl;
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
            //退出程序
            cout << "已退出，欢迎下次使用！" << endl;
			break;
        }
    }
	return 0;
}