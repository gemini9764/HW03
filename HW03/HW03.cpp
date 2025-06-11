#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>
class SimpleVector
{
private:
    static constexpr size_t DEFAULT_CAP = 10;
    T* arr;     // �迭 ����
    int currentSize;    // SimpleVector ���� ����
    int currentCapacity;    // SimpleVector ũ��

public:
    // SimpleVector ���� ��, ũ�⸦ 10���� ����
    SimpleVector(int cap = DEFAULT_CAP) : arr(new T[cap]), currentSize(0), currentCapacity(cap) {}
    // SimpleVector�� �ٸ� SimpleVector�� ���縦 ���� ������
    SimpleVector(const SimpleVector& v) : arr(new T[v.currentSize]), currentSize(v.currentSize), currentCapacity(v.currentCapacity)
    {
        for (int i = 0; i < currentSize; ++i)
        {
            arr[i] = v[i];
        }
    }

    // �Ҹ���
    ~SimpleVector()
    {
        delete[] arr;
    }

    // SimpleVector[idx]�� ������� �����ϱ� ���� operator ����
    T& operator[](int idx) { return arr[idx];  }
    const T& operator[](int idx) const { return arr[idx]; }

    void push_back(const T& val)
    {
        // capacity�� size���� �۰ų� ���� ��� ������ �����ϹǷ� ���Ҵ�
        if (currentSize >= currentCapacity)
        {
            // �⺻ ũ�⺸�� capacity�� ������ �⺻ ũ���
            if (currentCapacity < DEFAULT_CAP)
                currentCapacity = DEFAULT_CAP;
            // ���� �迭���� ũ�⸦ 5��ŭ �� �ø�
            else
                currentCapacity += 5;

            // ���Ҵ��� ���� �迭 ����
            T* t_arr = new T[currentCapacity];

            for (int i = 0; i < currentSize; ++i)
            {
                t_arr[i] = arr[i];
            }
            
            // ������ SimpleVector�� ����� ������ �ø� SimpleVector�� �־��ֱ�
            delete[] arr;
            arr = t_arr;
        }
        // �� �ڿ� ���� �߰�
        arr[currentSize++] = val;
    }

    void pop_back() { currentSize = currentSize > 0 ? currentSize - 1 : 0; }

    int size() const { return currentSize; }

    int capacity() const { return currentCapacity; }

    void sortData() { sort(arr, arr + currentSize); }

    void resize(int n, const T& val = T())
    {
        T* t_arr = new T[n];
        // ���� ũ�Ⱑ resize �Ϸ��� n���� ������ ���� ũ��� ũ�� n�� ũ���
        currentSize = currentSize < n ? currentSize : n;
        currentCapacity = n;

        // SimpleVector�� ������ ���Ҹ� resize�Ϸ��� ũ�⸸ŭ �ű��
        for (int i = 0; i < currentSize; ++i)
            t_arr[i] = arr[i];

        // resize�� ���� ��, ������ ������ ũ�⺸�� ���� ��쿡�� ���� ���� �ʱ�ȭ
        for (int i = currentSize; i < currentCapacity; ++i)
            t_arr[i] = val;

        delete[] arr;
        arr = t_arr;
        currentSize = n;
    }
};

int main()
{
    SimpleVector<int> v;
    v.push_back(7);
    v.push_back(4);
    v.push_back(1);
    v.push_back(9);
    v.push_back(3);
    v.push_back(1);
    v.push_back(4);

    cout << "v's element : ";
    for (int i = 0; i < v.size(); ++i)
        cout << v[i] << " ";

    cout << endl;

    cout << "v.size() : " << v.size() << endl;
    cout << "v.capacity : " << v.capacity() << endl;

    v.sortData();
    cout << "sort after element : ";
    
    for (int i = 0; i < v.size(); ++i)
        cout << v[i] << " ";

    cout << endl;

    v.pop_back();
    v.pop_back();
    v.pop_back();

    cout << "pop_back after : ";
    for (int i = 0; i < v.size(); ++i)
        cout << v[i] << " ";

    cout << endl;

    v.resize(4);
    cout << "resize(smaller than capacity)" << endl;
    cout << "size : " << v.size() << endl;
    cout << "capacity : " << v.capacity() << endl;

    v.resize(8);
    cout << "resize(bigger than capacity)" << endl;
    cout << "size : " << v.size() << endl;
    cout << "capacity : " << v.capacity() << endl;
}
