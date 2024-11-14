#include<iostream>
#include<time.h>
using namespace std;

const int DefaultSize = 10000000;
const int d = 7;//位数

template<class T>
struct Element { //数据表元素定义
    T key;//关键码
    char otherdata;//其他数据成员
    int link;//结点的链接指针
    Element<T>() : key(), otherdata(), link(0) {}
    Element<T>(T x, int next = 0) : key(x), link(next){}
    Element<T>& operator=(const Element<T>& x) {
        key = x.key;
        otherdata = x.otherdata;
        return *this;
    }//元素x赋值给this
    int operator==(Element<T>& x) { return key == x.key; }
    int operator<=(Element<T>& x) { return key <= x.key; }
    int operator<(Element<T>& x) { return key < x.key; }
    int operator>(Element<T>& x) { return key > x.key; }
    int operator>=(Element<T>&x) { return key >= x.key; }
    T getKey() { return key; }
    void setKey(const T x) { key = x; }
    int getLink() { return link; }
    void setLink(const int l) { link = l; }
};

template<class T>
void Swap(Element<T>& x, Element<T>& y) {
    Element<T>temp = x;
    x = y;
    y = temp;
}//交换x，y

template<class T>
struct dataList {
    Element<T>* Vector;//存储向量
    int maxSize;//最大个数
    int currentSize;//当前个数
    dataList(int sz = DefaultSize):
    maxSize(sz),currentSize(0) 
    { Vector = new Element<T>[sz]; }//构造函数
    //随机数的构造函数，并改变CurrentSize
    void randList(int num) {
        currentSize = num;
        for (int i = 0;i < currentSize;i++) {
            Vector[i].key = rand() % DefaultSize;
        }
    }
    dataList<T>& operator=(const dataList<T>& other) {
        if (this != &other) {  // 避免自赋值
            delete[] Vector;   // 释放原有内存

            maxSize = other.maxSize;
            currentSize = other.currentSize;

            // 为新的 Vector 分配内存并复制数据
            Vector = new Element<T>[currentSize];
            for (int i = 0; i < currentSize; i++) {
                Vector[i] = other.Vector[i];
            }
        }
        return *this;  // 返回对当前对象的引用
    }//赋值运算符
};

template<class T>
struct staticLinkedList {
public:
    int maxSize, currentSize;
    Element<T>* Vector;
    staticLinkedList(int sz = DefaultSize) :maxSize(sz), currentSize(0) { Vector = new  Element<T>[sz]; }
    Element<T>& operator[](int i) { return Vector[i]; }
};

template<class T>
class maxHeap {
private:
    Element<T>* heap;  //存放最大堆中元素的数组
    int currentSize;
    int maxHeapSize;
    void siftDown(int start, int m, int& compare, int& move);
public:
    maxHeap(int sz = DefaultSize) :maxHeapSize(sz), currentSize(0) { heap = new Element<T>[sz]; }
    ~maxHeap() { delete[]heap; }
    bool IsEmpty() { return currentSize == 0; }
    bool IsFull() { return currentSize == DefaultSize; }
    void HeapSort(int& compare, int& move);
    void insert(Element<T> item);
};

template<class T>   //直接插入排序
void InsertSort(dataList<T>&L, int& compare, int& move) {
    for (int i = 1;i < L.currentSize;i++) {
        Element<T>temp = L.Vector[i];
        move++;
        int j = i;//从后向前顺序比较
        while (j > 0 && (++compare, temp < L.Vector[j - 1])) {
            L.Vector[j] = L.Vector[j - 1];
            j--;
            move++;
        }
        L.Vector[j] = temp;
        move++;
    }
}

template<class T>  //希尔排序
void ShellSort(dataList<T>&L, int& compare, int& move) {
    int gap = L.currentSize / 2;//gap是子序列间隔
    while (gap) {//循环，直到gap为0
        for (int i = gap;i < L.currentSize;i++) {
            Element<T>temp = L.Vector[i];
            move++;
            int j = i;
            while (j >= gap && (++compare, temp < L.Vector[j - gap])) {
                L.Vector[j] = L.Vector[j - gap];
                j -= gap;
                compare++;
                move++;
            }
            L.Vector[j] = temp;
            move++;
        }
        gap = gap == 2 ? 1 : (int)(gap / 2.2);//修改
    }
}

template<class T>  //冒泡排序
void BubbleSort(dataList<T>&L, int& compare, int& move) {
    int pass = 1;//遍历轮数
    int exchange = 1;//交换标志
    while (pass < L.currentSize && exchange) {
        exchange = 0;//交换标志置为0，假定未交换
        for (int j = L.currentSize - 1;j >= pass;j--) {
            if (L.Vector[j - 1] > L.Vector[j]) {
                Swap(L.Vector[j - 1], L.Vector[j]);//交换
                move += 3;
                exchange = 1;  //交换标志置为1，有交换
            }
            compare++;
        }
    }
}

template<class T>
int Partition(dataList<T>& L, const int left, const int right,int &compare,int &move) {
    int pivotpos = left;
    Element<T>pivot = L.Vector[left];
    for (int i = left + 1;i <= right;i++) {
        if ((++compare, L.Vector[i] < pivot) && ++pivotpos != i) {
            Swap(L.Vector[pivotpos], L.Vector[i]);//小于基准对象的交换到区间的左侧去
            move += 3;
        }
    }
    Swap(L.Vector[left], L.Vector[pivotpos]);
    move += 3;
    return pivotpos;
}

template<class T>  //快速排序
void QuickSort(dataList<T>&L,const int left,const int right, int& compare, int& move) {
    if (left < right && left >= 0 && left < L.currentSize && right >= 0 && right < L.currentSize) {
        int pivotpos = Partition(L, left, right, compare, move);//划分
        QuickSort(L, left, pivotpos - 1, compare, move);//在左子区间递归进行快速排序
        QuickSort(L, pivotpos + 1, right, compare, move);//在右子区间递归进行快速排序
    }
}

template<class T>  //选择排序
void SelectSort(dataList<T>&L, int& compare, int& move) {
    for (int i = 0;i < L.currentSize - 1;i++) {
        int k = i;
        for (int j = i + 1;j < L.currentSize;j++) {
            if (L.Vector[j] < L.Vector[k])
                k = j;//当前具最小关键码的对象
            compare++;
        }
        if (k != i) {
            Swap(L.Vector[i], L.Vector[k]);
            move += 3;
        }
    }
}

template<class T>  //一次两路归并
void merge(dataList<T>& initList,dataList<T>& mergedList, const int l, const int m, const int n, int& compare, int& move) {
    int i = 0, j = m + 1, k = 0;
    while (i <= m && j <= n) {//两两比较
        if (initList.Vector[i] <= initList.Vector[j]) {
            mergedList.Vector[k] = initList.Vector[i];
            i++;
            k++;
        }
        else {
            mergedList.Vector[k] = initList.Vector[j];
            j++;
            k++;
        }
        compare++;
        move++;
    }
    if (i <= m) {
        for (int n1 = k, n2 = i;n1 <= n && n2 <= m;n1++, n2++) {
            mergedList.Vector[n1] = initList.Vector[n2];
        }
    }
    else {
        for (int n1 = k, n2 = j;n1 <= n && n2 <= n;n1++, n2++) {
            mergedList.Vector[n1] = initList.Vector[n2];
        }
    }
    move++;
}

template<class T>  //一趟两路归并
void MergePass(dataList<T>& initList, dataList<T>& mergedList, const int len, int& compare, int& move) {
    int i = 0;
    while (i + 2 * len <= initList.currentSize - 1) {
        merge(initList, mergedList, i, i + len - 1, i + 2 * len - 1, compare, move);
        i += 2 * len;
    }
    if (i + len <= initList.currentSize - 1) {
        merge(initList, mergedList, i, i + len - 1, initList.currentSize-1, compare, move);
    }
    else {
        for (int j = i;j <= initList.currentSize - 1;j++)
            mergedList.Vector[j] = initList.Vector[j];
    }
}

template<class T>  //归并排序
void MergeSort(dataList<T>& L, int& compare, int& move) {
    dataList<T>tempList(L.maxSize);
    int len = 1;
    while (len < L.currentSize) {
        MergePass(L, tempList, len, compare, move);
        len *= 2;
        MergePass(tempList, L, len, compare, move);
        len *= 2;
    }
}

// 获取某位上的数字
int getDigit(int num, int digit) {
    while (digit > 0) {
        num /= 10;
        digit--;
    }
    return num % 10;
}

template<class T>  //基数排序
void RadixSort(staticLinkedList<T>& L, const int d, const int radix,int &compare,int &move) {
    for (int i = 0; i < d; i++) {
        int* count = new int[radix];
        int* offset = new int[radix];
        for (int i = 0; i < radix; i++) {
            count[i] = 0;
        }
        //计数
        for (int i = 0; i < L.currentSize; i++) {
            count[getDigit(L[i].getKey(), d)]++;
        }
        //计算偏移量
        offset[0] = 0;
        for (int i = 1; i < radix; i++) {
            offset[i] = offset[i - 1] + count[i - 1];
        }
        //临时数组存放排序结果
        Element<T>* tmp = new Element<T>[L.currentSize];
        for (int i = 0; i < L.currentSize; i++) {
            int digit = getDigit(L[i].getKey(), d);
            tmp[offset[digit]++] = L[i];
            move++;
        }
        //将排序结果写回原数组
        for (int i = 0; i < L.currentSize; i++) {
            L[i] = tmp[i];
            move++;
        }
        // 释放临时数组
        delete[] tmp;
        delete[] count;
        delete[] offset;
    }
}

void dealInputError(int& n, string str, int min = 0, int max = 1)  //处理输入错误
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
    cout << "**                  排序算法比较                  **" << endl;
    cout << "====================================================" << endl;
    cout << "**                 1 --- 冒泡排序                 **" << endl;
    cout << "**                 2 --- 选择排序                 **" << endl;
    cout << "**                 3 --- 直接插入排序             **" << endl;
    cout << "**                 4 --- 希尔排序                 **" << endl;
    cout << "**                 5 --- 快速排序                 **" << endl;
    cout << "**                 6 --- 堆排序                   **" << endl;
    cout << "**                 7 --- 归并排序                 **" << endl;
    cout << "**                 8 --- 基数排序                 **" << endl;
    cout << "**                 9 --- 退出程序                 **" << endl;
    cout << "====================================================" << endl;

    int num;//随机数的个数
    dealInputError(num, "请输入要产生的随机数的个数：", 1, DefaultSize);
    dataList<int>List(num);
    List.randList(num);

    while (1) {
        int choice;
        cout << endl;
        dealInputError(choice, "请选择排序算法：          ", 1, 9);
        if (choice == 1) {
            //冒泡排序
            dataList<int>L;
            L = List;
            clock_t start_t, end_t;
            int compare = 0, move = 0;
            start_t = clock();
            BubbleSort(L, compare, move);
            end_t = clock();
            double duration = double(end_t - start_t) / CLOCKS_PER_SEC;
            cout << "冒泡排序所用时间：        " << duration << "s" << endl;
            cout << "冒泡排序比较次数：        " << compare << endl;
            cout << "冒泡排序移动次数：        " << move << endl;
            continue;
        }
        else if (choice == 2) {
            //选择排序
            dataList<int>L;
            L = List;
            clock_t start_t, end_t;
            int compare = 0, move = 0;
            start_t = clock();
            SelectSort(L, compare, move);
            end_t = clock();
            double duration = double(end_t - start_t) / CLOCKS_PER_SEC;
            cout << "选择排序所用时间：        " << duration << "s" << endl;
            cout << "选择排序比较次数：        " << compare << endl;
            cout << "选择排序移动次数：        " << move << endl;
            continue;
        }
        else if (choice == 3) {
            //直接插入排序
            dataList<int>L;
            L = List;
            clock_t start_t, end_t;
            int compare = 0, move = 0;
            start_t = clock();
            InsertSort(L, compare, move);
            end_t = clock();
            double duration = double(end_t - start_t) / CLOCKS_PER_SEC;
            cout << "直接插入排序所用时间：    " << duration << "s" << endl;
            cout << "直接插入排序比较次数：    " << compare << endl;
            cout << "直接插入排序移动次数：    " << move << endl;
            continue;
        }
        else if (choice == 4) {
            //希尔排序
            dataList<int>L;
            L = List;
            clock_t start_t, end_t;
            int compare = 0, move = 0;
            start_t = clock();
            ShellSort(L, compare, move);
            end_t = clock();
            double duration = double(end_t - start_t) / CLOCKS_PER_SEC;
            cout << "希尔排序所用时间：        " << duration << "s" << endl;
            cout << "希尔排序比较次数：        " << compare << endl;
            cout << "希尔排序移动次数：        " << move << endl;
            continue;
        }
        else if (choice == 5) {
            //快速排序
            dataList<int>L;
            L = List;
            clock_t start_t, end_t;
            int compare = 0, move = 0;
            start_t = clock();
            QuickSort(L, 0, num - 1, compare, move);
            end_t = clock();
            double duration = double(end_t - start_t) / CLOCKS_PER_SEC;
            cout << "快速排序所用时间：        " << duration << "s" << endl;
            cout << "快速排序比较次数：        " << compare << endl;
            cout << "快速排序移动次数：        " << move << endl;
            continue;
        }
        else if (choice == 6) {
            //堆排序
            dataList<int>L;
            L = List;
            maxHeap<int> Heap(num);
            // 将dataList中的元素插入到maxHeap中
            for (int i = 0; i < num; i++) {
                Heap.insert(L.Vector[i]);
            }
            clock_t start_t, end_t;
            int compare = 0, move = 0;
            start_t = clock();
            Heap.HeapSort(compare, move);
            end_t = clock();
            double duration = double(end_t - start_t) / CLOCKS_PER_SEC;
            cout << "堆排序所用时间：          " << duration << "s" << endl;
            cout << "堆排序比较次数：          " << compare << endl;
            cout << "堆排序移动次数：          " << move << endl;
            continue;
        }
        else if (choice == 7) {
            //归并排序
            dataList<int>L;
            L = List;
            clock_t start_t, end_t;
            int compare = 0, move = 0;
            start_t = clock();
            MergeSort(L, compare, move);
            end_t = clock();
            double duration = double(end_t - start_t) / CLOCKS_PER_SEC;
            cout << "归并排序所用时间：        " << duration << "s" << endl;
            cout << "归并排序比较次数：        " << compare << endl;
            cout << "归并排序移动次数：        " << move << endl;
            continue;
        }
        else if (choice == 8) {
            //基数排序
            dataList<int>L;
            L = List;
            staticLinkedList<int>LL(num);
            LL.currentSize = num;
            for (int i = 0;i < num;i++) {
                LL.Vector[i] = L.Vector[i];
            }
            clock_t start_t, end_t;
            int compare = 0, move = 0;
            start_t = clock();
            RadixSort(LL, d, 10, compare, move);
            end_t = clock();
            double duration = double(end_t - start_t) / CLOCKS_PER_SEC;
            cout << "基数排序所用时间：        " << duration << "s" << endl;
            cout << "基数排序比较次数：        " << compare << endl;
            cout << "基数排序移动次数：        " << move << endl;
            continue;
        }
        else if (choice == 9) {
            //退出程序
            cout << "已退出，欢迎下次使用！" << endl;
            break;
        }
    }
    return 0;
}

template<class T>
void maxHeap<T>::siftDown(int start, int m, int& compare, int& move)
{
    int i = start;
    int j = 2 * i + 1;//j是i的左子女
    Element<T>temp = heap[i];//暂存子树根节点
    while (j <= m) {//检查是否到最后位置
        if (j < m && heap[j] < heap[j + 1]) {
            j++;//让child指向两子女中的大者
        }
        compare++;
        if (temp >= heap[j]) {
            break;//temp的排序码大则不作调整
        }
        else {//否则子女中的大者上移
            heap[i] = heap[j];
            move++;
            i = j;
            j = 2 * j + 1;//i下降到子女位置
        }
        compare++;
    }
    heap[i] = temp;//temp中暂存元素放到合适位置
    move++;
}

template<class T>
void maxHeap<T>::HeapSort(int& compare, int& move)
{
    for (int i = (currentSize - 2) / 2;i >= 0;i--)
        siftDown(i, currentSize - 1, compare, move);
    for (int i = currentSize - 1;i >= 0;i--) {
        Swap(heap[0], heap[i]);
        move += 3;
        siftDown(0, i - 1, compare, move);
    }
}

template<class T>
void maxHeap<T>::insert(Element<T> item)
{
    int i = currentSize++;
    while (i > 0) {
        int parent = (i - 1) / 2;  // 父节点的索引
        if (item <= heap[parent]) {
            break;  // 如果插入元素小于等于父节点，不需要继续上浮
        }
        heap[i] = heap[parent];  // 将父节点下移
        i = parent;  // 更新当前位置为父节点的位置
    }
    heap[i] = item;  // 将元素插入到正确的位置
}
