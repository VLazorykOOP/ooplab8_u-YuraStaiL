#include "example.h"
#include <string.h>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <stdexcept>
namespace Task1 {


 //using namespace std;
    using std::cout;
    using std::endl;
    using std::ostream;
    using std::istream;

    template<typename T>
    void findMinAndCount(T arr[], int size, T& minVal, int& count)
    {
        minVal = arr[0];
        count = 1;
        for (int i = 1; i < size; i++) {
            if (arr[i] < minVal) {
                minVal = arr[i];
                count = 1;
            }
            else if (arr[i] == minVal) {
                count++;
            }
        }
    }

    template<>
    void findMinAndCount<char*>(char* arr[], int size, char*& minVal, int& count)
    {
        minVal = arr[0];
        count = 1;
        for (int i = 1; i < size; i++) {
            if (strcmp(arr[i], minVal) < 0) {
                minVal = arr[i];
                count = 1;
            }
            else if (strcmp(arr[i], minVal) == 0) {
                count++;
            }
        }
    }

   
    int task1()
    {
        int intArr[] = { 5, 3, 1, 3, 2, 5, 5, 1 };
        int intMinVal, intCount;
        findMinAndCount(intArr, 8, intMinVal, intCount);
        std::cout << "minVal = " << intMinVal << ", count = " << intCount << std::endl;

        double doubleArr[] = { 5.5, 3.3, 1.1, 3.3, 2.2, 5.5, 5.5 };
        double doubleMinVal;
        int doubleCount;
        findMinAndCount(doubleArr, 7, doubleMinVal, doubleCount);
        std::cout << "minVal = " << doubleMinVal << ", count = " << doubleCount << std::endl;

        const char* strArr[] = { "bbb", "aaa", "ddd", "aaa", "ccc", "bbb", "bbb" };
        const char* strMinVal;
        int strCount;
        findMinAndCount(strArr, 7, strMinVal, strCount);
        std::cout << "minVal = " << strMinVal << ", count = " << strCount << std::endl;

        return 0;
    }
}

namespace Task2 {

    using namespace std;

    template <typename T>
    void sortArray(T arr[], int size) {
        sort(arr, arr + size);
    }

    template <typename T>
    int binarySearch(T arr[], int size, T key) {
        int low = 0, high = size - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (arr[mid] == key) {
                return mid;
            }
            else if (arr[mid] > key) {
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }
        return -1;
    }

    template <>
    int binarySearch(char* arr[], int size, char* key) {
        int low = 0, high = size - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            int cmp = strcmp(arr[mid], key);
            if (cmp == 0) {
                return mid;
            }
            else if (cmp > 0) {
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }
        return -1;
    }

    int main() {
        int arr1[] = { 5, 2, 8, 1, 9 };
        sortArray(arr1, 5);
        for (int i = 0; i < 5; i++) {
            cout << arr1[i] << " ";
        }
        cout << endl;

        const char* arr2[] = { "some", "word", "Binary", "meet", "go", "test" };
        sortArray(arr2, 6);
        for (int i = 0; i < 6; i++) {
            cout << arr2[i] << " ";
        }
        cout << endl;

        int index1 = binarySearch(arr1, 5, 8);
        cout << "Index of 8 in arr1: " << index1 << endl;

        int index2 = binarySearch(arr1, 5, 3);
        cout << "Index of 3(does not exist) in arr1: " << index2 << endl;

        int index3 = binarySearch(arr2, 6, "test");
        cout << "Index of 'test' in arr2: " << index3 << endl;

        int index4 = binarySearch(arr2, 6, "foooo");
        cout << "Index of 'foooo'(does not exist) in arr2: " << index4 << endl;

        return 0;
    }

}

namespace Task3 {
    template<typename T>
    class Matrix {
    public:
        Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
            data_ = new T * [rows_];
            for (int i = 0; i < rows_; ++i) {
                data_[i] = new T[cols_];
                for (int j = 0; j < cols_; ++j) {
                    data_[i][j] = T();
                }
            }
        }

        Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
            data_ = new T * [rows_];
            for (int i = 0; i < rows_; ++i) {
                data_[i] = new T[cols_];
                for (int j = 0; j < cols_; ++j) {
                    data_[i][j] = other.data_[i][j];
                }
            }
        }

        ~Matrix() {
            for (int i = 0; i < rows_; ++i) {
                delete[] data_[i];
            }
            delete[] data_;
        }

        Matrix& operator=(const Matrix& other) {
            if (&other != this) {
                Matrix temp(other);
                std::swap(rows_, temp.rows_);
                std::swap(cols_, temp.cols_);
                std::swap(data_, temp.data_);
            }
            return *this;
        }

        T* operator[](int row) const {
            if (row < 0 || row >= rows_) {
                throw std::out_of_range("Matrix row index out of range");
            }
            return data_[row];
        }

        Matrix operator+(const Matrix& other) const {
            if (rows_ != other.rows_ || cols_ != other.cols_) {
                throw std::invalid_argument("Matrices have different dimensions");
            }
            Matrix result(rows_, cols_);
            for (int i = 0; i < rows_; ++i) {
                for (int j = 0; j < cols_; ++j) {
                    result[i][j] = (*this)[i][j] + other[i][j];
                }
            }
            return result;
        }

        Matrix& operator+=(const Matrix& other) {
            if (rows_ != other.rows_ || cols_ != other.cols_) {
                throw std::invalid_argument("Matrices have different dimensions");
            }
            for (int i = 0; i < rows_; ++i) {
                for (int j = 0; j < cols_; ++j) {
                    (*this)[i][j] += other[i][j];
                }
            }
            return *this;
        }

    private:
        int rows_;
        int cols_;
        T** data_;
    };

    int main() {
        Matrix<int> m(3, 3);

        m[0][0] = 1;
        m[1][1] = 2;
        m[2][2] = 3;

        Matrix<int> m_copy = m;

        std::cout << "m[0][0] = 1;\n";
        std::cout << "m[1][1] = 2;\n";
        std::cout << "m[2][2] = 3;\n";

        std::cout << "Before\n\n";

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                std::cout << m[i][j] << " ";
            }
            std::cout << std::endl;
        }

        std::cout << std::endl;

   
        m += m_copy;

        std::cout << "After the copy and +=m_copy\n\n";

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                std::cout << m[i][j] << " ";
            }
            std::cout << std::endl;
        }

        std::cout << std::endl;
        std::cout << "Use m[2][2]   ->   " << m[2][2];

        return 0;
    }
}

namespace Task4 {
    template <typename T>
    class List {
    private:
        struct Node {
            T value;
            Node* next;
        };

        Node* head;
        Node* tail;
        int size;

    public:
        List() : head(nullptr), tail(nullptr), size(0) {}

        void push_front(const T& value) {
            Node* new_node = new Node{ value, head };
            head = new_node;
            if (tail == nullptr) {
                tail = new_node;
            }
            ++size;
        }

        void push_back(const T& value) {
            Node* new_node = new Node{ value, nullptr };
            if (tail == nullptr) {
                head = new_node;
                tail = new_node;
            }
            else {
                tail->next = new_node;
                tail = new_node;
            }
            ++size;
        }

        void pop_front() {
            if (head != nullptr) {
                Node* old_head = head;
                head = head->next;
                delete old_head;
                --size;
                if (head == nullptr) {
                    tail = nullptr;
                }
            }
        }

        void pop_back() {
            if (tail != nullptr) {
                if (head == tail) {
                    delete tail;
                    head = nullptr;
                    tail = nullptr;
                    --size;
                }
                else {
                    Node* curr = head;
                    while (curr->next != tail) {
                        curr = curr->next;
                    }
                    delete tail;
                    tail = curr;
                    tail->next = nullptr;
                    --size;
                }
            }
        }

        int get_size() const {
            return size;
        }

        class iterator {
        public:
            iterator(Node* node) : curr(node) {}

            T& operator*() const {
                return curr->value;
            }

            iterator& operator++() {
                curr = curr->next;
                return *this;
            }

            bool operator==(const iterator& other) const {
                return curr == other.curr;
            }

            bool operator!=(const iterator& other) const {
                return curr != other.curr;
            }

        private:
            Node* curr;
        };

        iterator begin() const {
            return iterator(head);
        }

        iterator end() const {
            return iterator(nullptr);
        }
    };

    int main() {
        List<double> my_list;
        my_list.push_back(3.14);
        my_list.push_back(2.22);
        my_list.push_back(0.9999);
        my_list.push_back(5.9999);

        for (auto it = my_list.begin(); it != my_list.end(); ++it) {
            std::cout << *it << std::endl;
        }

        return 0;
    }
}

void task1()
{
    Task1::task1();
    
}

void task2()
{
    Task2::main();
}

void task3()
{
    Task3::main();
}

void task4()
{
    Task4::main();
}