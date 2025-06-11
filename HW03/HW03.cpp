#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>
class SimpleVector
{
private:
    static constexpr size_t DEFAULT_CAP = 10;
    T* arr;     // 배열 선언
    int currentSize;    // SimpleVector 원소 개수
    int currentCapacity;    // SimpleVector 크기

public:
    // SimpleVector 생성 시, 크기를 10으로 생성
    SimpleVector(int cap = DEFAULT_CAP) : arr(new T[cap]), currentSize(0), currentCapacity(cap) {}
    // SimpleVector를 다른 SimpleVector에 복사를 위한 생성자
    SimpleVector(const SimpleVector& v) : arr(new T[v.currentSize]), currentSize(v.currentSize), currentCapacity(v.currentCapacity)
    {
        for (int i = 0; i < currentSize; ++i)
        {
            arr[i] = v[i];
        }
    }

    // 소멸자
    ~SimpleVector()
    {
        delete[] arr;
    }

    // SimpleVector[idx]의 방식으로 접근하기 위한 operator 선언
    T& operator[](int idx) { return arr[idx];  }
    const T& operator[](int idx) const { return arr[idx]; }

    void push_back(const T& val)
    {
        // capacity가 size보다 작거나 같은 경우 공간이 부족하므로 재할당
        if (currentSize >= currentCapacity)
        {
            // 기본 크기보다 capacity가 작으면 기본 크기로
            if (currentCapacity < DEFAULT_CAP)
                currentCapacity = DEFAULT_CAP;
            // 기존 배열보다 크기를 5만큼 더 늘림
            else
                currentCapacity += 5;

            // 재할당을 위한 배열 선언
            T* t_arr = new T[currentCapacity];

            for (int i = 0; i < currentSize; ++i)
            {
                t_arr[i] = arr[i];
            }
            
            // 기존의 SimpleVector를 지우고 공간을 늘린 SimpleVector을 넣어주기
            delete[] arr;
            arr = t_arr;
        }
        // 맨 뒤에 원소 추가
        arr[currentSize++] = val;
    }

    void pop_back() { currentSize = currentSize > 0 ? currentSize - 1 : 0; }

    int size() const { return currentSize; }

    int capacity() const { return currentCapacity; }

    void sortData() { sort(arr, arr + currentSize); }

    void resize(int n, const T& val = T())
    {
        T* t_arr = new T[n];
        // 현재 크기가 resize 하려는 n보다 작으면 현재 크기로 크면 n의 크기로
        currentSize = currentSize < n ? currentSize : n;
        currentCapacity = n;

        // SimpleVector의 기존의 원소를 resize하려는 크기만큼 옮긴다
        for (int i = 0; i < currentSize; ++i)
            t_arr[i] = arr[i];

        // resize를 했을 때, 원소의 개수가 크기보다 작은 경우에만 남은 공간 초기화
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
