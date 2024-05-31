
#include <iostream>
#include <cstring>
#include <vector>


using namespace std;

class String {
public:
    String() : arr(nullptr), size(0) {}

    String(const char* str) {
        int n = strlen(str);
        this->resize(n);
        for (int i = 0; i < n; i++) {
            arr[i] = str[i];
        }
        arr[n] = '\0';
    }

    String(const String& other) {
        size = other.size;
        arr = new char[size + 1];
        strcpy_s(arr, size+1, other.arr);
    }

    String(String&& other) noexcept : arr(other.arr), size(other.size) {
        other.arr = nullptr;
        other.size = 0;
    }

    ~String() {
        delete[] arr;
        arr = nullptr;
    }

    String& operator=(const String& other) {
        if (this == &other)
            return *this;

        delete[] arr;
        size = other.size;
        arr = new char[size + 1];
        strcpy_s(arr, size+1, other.arr);

        return *this;
    }

    String& operator=(String&& other) noexcept {
        if (this == &other)
            return *this;

        delete[] arr;
        arr = other.arr;
        size = other.size;

        other.arr = nullptr;
        other.size = 0;

        return *this;
    }

    friend String operator+(const String& left, const String& right) {
        String res(left);
        res += right;
        return res;
    }

    void resize(int n) {
        if (size == 0) {
            arr = new char[n + 1];
            size = n;
        }
        else {
            char* tmp = arr;
            arr = new char[n + 1];
            for (int i = 0; i < size; i++) {
                arr[i] = tmp[i];
            }
            delete[] tmp;
            size = n;
        }
    }

    String& operator+=(const String& right) {
        int rightSize = strlen(right.arr);
        int leftSize = size;
        resize(rightSize + leftSize);
        for (int i = 0; i < rightSize; i++) {
            arr[leftSize + i] = right.arr[i];
        }
        arr[size] = '\0';
        return *this;
    }

    String& operator+=(const char* right) {
        int rightSize = strlen(right);
        int leftSize = size;
        resize(rightSize + leftSize);
        for (int i = 0; i < rightSize; i++) {
            arr[leftSize + i] = right[i];
        }
        arr[size] = '\0';
        return *this;
    }

    const char* getArray() const {
        return arr;
    }

    friend ostream& operator<<(ostream& os, const String& str) {
        if (str.arr) {
            os << str.arr;
        }
        return os;
    }

private:
    char* arr = nullptr;
    size_t size = 0;
};


int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout <<"You are launch without arguments or only one arguments" << endl;
        return 1;
    }
    vector<String> strings;
    for (int i = 1; i < argc; ++i) {
        strings.emplace_back(argv[i]);
    }
    vector<String> lower_strings(strings.size());
    for (size_t i = 0; i < strings.size(); ++i) {
        const char* original = strings[i].getArray();
        int length = strlen(original);
        char* lower = new char[length + 1];
        for (int j = 0; j < length; ++j) {
            lower[j] = tolower(original[j]);
        }
        lower[length] = '\0';
        lower_strings[i] = String(lower);
        delete[] lower;
    }
    for (size_t i = 0; i < lower_strings.size(); ++i) {
        for (size_t j = i + 1; j < lower_strings.size(); ++j) {
            if (strcmp(lower_strings[i].getArray(), lower_strings[j].getArray()) < 0) {
                swap(strings[i], strings[j]);
                swap(lower_strings[i], lower_strings[j]);
            }
        }
    }
    for (const auto& str : strings) {
        cout << str << endl;
    }

    return 0;
    //я собрал через g++ и потом запустил .exe всё работает
}