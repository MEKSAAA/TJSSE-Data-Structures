#include<iostream>
#include<time.h>
using namespace std;

const int DefaultSize = 10000000;
const int d = 7;//λ��

template<class T>
struct Element { //���ݱ�Ԫ�ض���
    T key;//�ؼ���
    char otherdata;//�������ݳ�Ա
    int link;//��������ָ��
    Element<T>() : key(), otherdata(), link(0) {}
    Element<T>(T x, int next = 0) : key(x), link(next){}
    Element<T>& operator=(const Element<T>& x) {
        key = x.key;
        otherdata = x.otherdata;
        return *this;
    }//Ԫ��x��ֵ��this
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
}//����x��y

template<class T>
struct dataList {
    Element<T>* Vector;//�洢����
    int maxSize;//������
    int currentSize;//��ǰ����
    dataList(int sz = DefaultSize):
    maxSize(sz),currentSize(0) 
    { Vector = new Element<T>[sz]; }//���캯��
    //������Ĺ��캯�������ı�CurrentSize
    void randList(int num) {
        currentSize = num;
        for (int i = 0;i < currentSize;i++) {
            Vector[i].key = rand() % DefaultSize;
        }
    }
    dataList<T>& operator=(const dataList<T>& other) {
        if (this != &other) {  // �����Ը�ֵ
            delete[] Vector;   // �ͷ�ԭ���ڴ�

            maxSize = other.maxSize;
            currentSize = other.currentSize;

            // Ϊ�µ� Vector �����ڴ沢��������
            Vector = new Element<T>[currentSize];
            for (int i = 0; i < currentSize; i++) {
                Vector[i] = other.Vector[i];
            }
        }
        return *this;  // ���ضԵ�ǰ���������
    }//��ֵ�����
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
    Element<T>* heap;  //���������Ԫ�ص�����
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

template<class T>   //ֱ�Ӳ�������
void InsertSort(dataList<T>&L, int& compare, int& move) {
    for (int i = 1;i < L.currentSize;i++) {
        Element<T>temp = L.Vector[i];
        move++;
        int j = i;//�Ӻ���ǰ˳��Ƚ�
        while (j > 0 && (++compare, temp < L.Vector[j - 1])) {
            L.Vector[j] = L.Vector[j - 1];
            j--;
            move++;
        }
        L.Vector[j] = temp;
        move++;
    }
}

template<class T>  //ϣ������
void ShellSort(dataList<T>&L, int& compare, int& move) {
    int gap = L.currentSize / 2;//gap�������м��
    while (gap) {//ѭ����ֱ��gapΪ0
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
        gap = gap == 2 ? 1 : (int)(gap / 2.2);//�޸�
    }
}

template<class T>  //ð������
void BubbleSort(dataList<T>&L, int& compare, int& move) {
    int pass = 1;//��������
    int exchange = 1;//������־
    while (pass < L.currentSize && exchange) {
        exchange = 0;//������־��Ϊ0���ٶ�δ����
        for (int j = L.currentSize - 1;j >= pass;j--) {
            if (L.Vector[j - 1] > L.Vector[j]) {
                Swap(L.Vector[j - 1], L.Vector[j]);//����
                move += 3;
                exchange = 1;  //������־��Ϊ1���н���
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
            Swap(L.Vector[pivotpos], L.Vector[i]);//С�ڻ�׼����Ľ�������������ȥ
            move += 3;
        }
    }
    Swap(L.Vector[left], L.Vector[pivotpos]);
    move += 3;
    return pivotpos;
}

template<class T>  //��������
void QuickSort(dataList<T>&L,const int left,const int right, int& compare, int& move) {
    if (left < right && left >= 0 && left < L.currentSize && right >= 0 && right < L.currentSize) {
        int pivotpos = Partition(L, left, right, compare, move);//����
        QuickSort(L, left, pivotpos - 1, compare, move);//����������ݹ���п�������
        QuickSort(L, pivotpos + 1, right, compare, move);//����������ݹ���п�������
    }
}

template<class T>  //ѡ������
void SelectSort(dataList<T>&L, int& compare, int& move) {
    for (int i = 0;i < L.currentSize - 1;i++) {
        int k = i;
        for (int j = i + 1;j < L.currentSize;j++) {
            if (L.Vector[j] < L.Vector[k])
                k = j;//��ǰ����С�ؼ���Ķ���
            compare++;
        }
        if (k != i) {
            Swap(L.Vector[i], L.Vector[k]);
            move += 3;
        }
    }
}

template<class T>  //һ����·�鲢
void merge(dataList<T>& initList,dataList<T>& mergedList, const int l, const int m, const int n, int& compare, int& move) {
    int i = 0, j = m + 1, k = 0;
    while (i <= m && j <= n) {//�����Ƚ�
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

template<class T>  //һ����·�鲢
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

template<class T>  //�鲢����
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

// ��ȡĳλ�ϵ�����
int getDigit(int num, int digit) {
    while (digit > 0) {
        num /= 10;
        digit--;
    }
    return num % 10;
}

template<class T>  //��������
void RadixSort(staticLinkedList<T>& L, const int d, const int radix,int &compare,int &move) {
    for (int i = 0; i < d; i++) {
        int* count = new int[radix];
        int* offset = new int[radix];
        for (int i = 0; i < radix; i++) {
            count[i] = 0;
        }
        //����
        for (int i = 0; i < L.currentSize; i++) {
            count[getDigit(L[i].getKey(), d)]++;
        }
        //����ƫ����
        offset[0] = 0;
        for (int i = 1; i < radix; i++) {
            offset[i] = offset[i - 1] + count[i - 1];
        }
        //��ʱ������������
        Element<T>* tmp = new Element<T>[L.currentSize];
        for (int i = 0; i < L.currentSize; i++) {
            int digit = getDigit(L[i].getKey(), d);
            tmp[offset[digit]++] = L[i];
            move++;
        }
        //��������д��ԭ����
        for (int i = 0; i < L.currentSize; i++) {
            L[i] = tmp[i];
            move++;
        }
        // �ͷ���ʱ����
        delete[] tmp;
        delete[] count;
        delete[] offset;
    }
}

void dealInputError(int& n, string str, int min = 0, int max = 1)  //�����������
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
    cout << "**                  �����㷨�Ƚ�                  **" << endl;
    cout << "====================================================" << endl;
    cout << "**                 1 --- ð������                 **" << endl;
    cout << "**                 2 --- ѡ������                 **" << endl;
    cout << "**                 3 --- ֱ�Ӳ�������             **" << endl;
    cout << "**                 4 --- ϣ������                 **" << endl;
    cout << "**                 5 --- ��������                 **" << endl;
    cout << "**                 6 --- ������                   **" << endl;
    cout << "**                 7 --- �鲢����                 **" << endl;
    cout << "**                 8 --- ��������                 **" << endl;
    cout << "**                 9 --- �˳�����                 **" << endl;
    cout << "====================================================" << endl;

    int num;//������ĸ���
    dealInputError(num, "������Ҫ������������ĸ�����", 1, DefaultSize);
    dataList<int>List(num);
    List.randList(num);

    while (1) {
        int choice;
        cout << endl;
        dealInputError(choice, "��ѡ�������㷨��          ", 1, 9);
        if (choice == 1) {
            //ð������
            dataList<int>L;
            L = List;
            clock_t start_t, end_t;
            int compare = 0, move = 0;
            start_t = clock();
            BubbleSort(L, compare, move);
            end_t = clock();
            double duration = double(end_t - start_t) / CLOCKS_PER_SEC;
            cout << "ð����������ʱ�䣺        " << duration << "s" << endl;
            cout << "ð������Ƚϴ�����        " << compare << endl;
            cout << "ð�������ƶ�������        " << move << endl;
            continue;
        }
        else if (choice == 2) {
            //ѡ������
            dataList<int>L;
            L = List;
            clock_t start_t, end_t;
            int compare = 0, move = 0;
            start_t = clock();
            SelectSort(L, compare, move);
            end_t = clock();
            double duration = double(end_t - start_t) / CLOCKS_PER_SEC;
            cout << "ѡ����������ʱ�䣺        " << duration << "s" << endl;
            cout << "ѡ������Ƚϴ�����        " << compare << endl;
            cout << "ѡ�������ƶ�������        " << move << endl;
            continue;
        }
        else if (choice == 3) {
            //ֱ�Ӳ�������
            dataList<int>L;
            L = List;
            clock_t start_t, end_t;
            int compare = 0, move = 0;
            start_t = clock();
            InsertSort(L, compare, move);
            end_t = clock();
            double duration = double(end_t - start_t) / CLOCKS_PER_SEC;
            cout << "ֱ�Ӳ�����������ʱ�䣺    " << duration << "s" << endl;
            cout << "ֱ�Ӳ�������Ƚϴ�����    " << compare << endl;
            cout << "ֱ�Ӳ��������ƶ�������    " << move << endl;
            continue;
        }
        else if (choice == 4) {
            //ϣ������
            dataList<int>L;
            L = List;
            clock_t start_t, end_t;
            int compare = 0, move = 0;
            start_t = clock();
            ShellSort(L, compare, move);
            end_t = clock();
            double duration = double(end_t - start_t) / CLOCKS_PER_SEC;
            cout << "ϣ����������ʱ�䣺        " << duration << "s" << endl;
            cout << "ϣ������Ƚϴ�����        " << compare << endl;
            cout << "ϣ�������ƶ�������        " << move << endl;
            continue;
        }
        else if (choice == 5) {
            //��������
            dataList<int>L;
            L = List;
            clock_t start_t, end_t;
            int compare = 0, move = 0;
            start_t = clock();
            QuickSort(L, 0, num - 1, compare, move);
            end_t = clock();
            double duration = double(end_t - start_t) / CLOCKS_PER_SEC;
            cout << "������������ʱ�䣺        " << duration << "s" << endl;
            cout << "��������Ƚϴ�����        " << compare << endl;
            cout << "���������ƶ�������        " << move << endl;
            continue;
        }
        else if (choice == 6) {
            //������
            dataList<int>L;
            L = List;
            maxHeap<int> Heap(num);
            // ��dataList�е�Ԫ�ز��뵽maxHeap��
            for (int i = 0; i < num; i++) {
                Heap.insert(L.Vector[i]);
            }
            clock_t start_t, end_t;
            int compare = 0, move = 0;
            start_t = clock();
            Heap.HeapSort(compare, move);
            end_t = clock();
            double duration = double(end_t - start_t) / CLOCKS_PER_SEC;
            cout << "����������ʱ�䣺          " << duration << "s" << endl;
            cout << "������Ƚϴ�����          " << compare << endl;
            cout << "�������ƶ�������          " << move << endl;
            continue;
        }
        else if (choice == 7) {
            //�鲢����
            dataList<int>L;
            L = List;
            clock_t start_t, end_t;
            int compare = 0, move = 0;
            start_t = clock();
            MergeSort(L, compare, move);
            end_t = clock();
            double duration = double(end_t - start_t) / CLOCKS_PER_SEC;
            cout << "�鲢��������ʱ�䣺        " << duration << "s" << endl;
            cout << "�鲢����Ƚϴ�����        " << compare << endl;
            cout << "�鲢�����ƶ�������        " << move << endl;
            continue;
        }
        else if (choice == 8) {
            //��������
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
            cout << "������������ʱ�䣺        " << duration << "s" << endl;
            cout << "��������Ƚϴ�����        " << compare << endl;
            cout << "���������ƶ�������        " << move << endl;
            continue;
        }
        else if (choice == 9) {
            //�˳�����
            cout << "���˳�����ӭ�´�ʹ�ã�" << endl;
            break;
        }
    }
    return 0;
}

template<class T>
void maxHeap<T>::siftDown(int start, int m, int& compare, int& move)
{
    int i = start;
    int j = 2 * i + 1;//j��i������Ů
    Element<T>temp = heap[i];//�ݴ��������ڵ�
    while (j <= m) {//����Ƿ����λ��
        if (j < m && heap[j] < heap[j + 1]) {
            j++;//��childָ������Ů�еĴ���
        }
        compare++;
        if (temp >= heap[j]) {
            break;//temp�����������������
        }
        else {//������Ů�еĴ�������
            heap[i] = heap[j];
            move++;
            i = j;
            j = 2 * j + 1;//i�½�����Ůλ��
        }
        compare++;
    }
    heap[i] = temp;//temp���ݴ�Ԫ�طŵ�����λ��
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
        int parent = (i - 1) / 2;  // ���ڵ������
        if (item <= heap[parent]) {
            break;  // �������Ԫ��С�ڵ��ڸ��ڵ㣬����Ҫ�����ϸ�
        }
        heap[i] = heap[parent];  // �����ڵ�����
        i = parent;  // ���µ�ǰλ��Ϊ���ڵ��λ��
    }
    heap[i] = item;  // ��Ԫ�ز��뵽��ȷ��λ��
}
