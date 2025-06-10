#include <iostream>

template <typename T>
class SimpleVector
{
private:
    static constexpr int DEFAULT_CAP = 10;
    T* arr;
    int currentSize;
    int currentCapacity;

public:
    SimpleVector(int cap = DEFAULT_CAP) : arr(new T[cap]), currentSize(0), currentCapacity(cap) {}
    SimpleVector(const SimpleVector& v) : arr(new T[v.currentSize]), currentSize(v.currentSize), currentCapacity(v.currentCapacity)
    {
        for (int i = 0; i < currentSize; ++i)
        {
            arr[i] = v[i];
        }
    }

    void push_back(const T& val)
    {
        if (currentSize > currentCapacity)
        {
            if (currentCapacity < DEFAULT_CAP)
                currentCapacity = DEFAULT_CAP;
            else
                currentCapacity += 5;

            T* t_arr = new T[currentCapacity];

            for (int i = 0; i < currentSize; ++i)
            {
                t_arr[i] = arr[i];
            }

            delete[] arr;
            arr = t_arr;
            t_arr = nullptr;
        }
        arr[currentSize++] = val;
    }
};

int main()
{
    std::cout << "Hello World!\n";
}
