#include <iostream>
#include <istream>
#include <ostream>
using namespace std;

class my_string {
private:
    char* data; // 保存内容的数据
    int length; // char内容的长度,不包括'\0'

public:
    // 构造函数
    my_string(const char* str = nullptr)
    {
        if (str == nullptr) {
            length = 0;
            data = new char[1];
            *data = '\0';
        } else {
            length = my_strlen(str);
            data = new char[length + 1];
            my_strcpy(data, str);
        }
    }
    // 复制构造函数
    my_string(const my_string& str)
    {
        length = str.size();
        data = new char[length + 1];
        my_strcpy(data, str.c_str());
    }
    // 析构函数
    ~my_string() { delete[] data; }

    // 返回data
    const char* c_str() const { return data; }
    // 返回data长度，不包括...
    int size() const { return length; }
    // 返回一个char*长度，不包括...
    int my_strlen(const char* str)
    {
        int len = 0;
        while (*str++ != '\0') {
            len++;
        }
        return len;
    }
    // 复制一个char*到另一个char*
    void my_strcpy(char* dst, const char* src)
    {
        while (*src != 0) {
            *dst++ = *src++;
        }
        *dst = '\0';
    }

    my_string& operator=(const my_string& str)
    {
        if (this == &str) {
            return *this;
        }
        delete[] data;
        length = str.size();
        data = new char[length + 1];
        my_strcpy(data, str.c_str());
        return *this;
    }
    bool operator==(const my_string& str) const
    {
        if (length != str.size()) {
            return false;
        }
        for (int i = 0; i < length; i++) {
            if (data[i] != str[i]) {
                return false;
            }
        }
        return true;
    }
    char& operator[](int n) const { return data[n]; }
    const char* operator*(my_string& str) { return str.c_str(); }

    friend istream& operator>>(istream& is, my_string& str)
    {
        char temp[100];
        is >> temp;
        delete[] str.data;
        str.length = str.my_strlen(temp);
        str.data = new char[str.length + 1];
        str.my_strcpy(str.data, temp);
        return is;
    }
    friend ostream& operator<<(ostream& os, my_string& str)
    {
        os << str.c_str();
        return os;
    }
};

template <typename T>
void my_copy(T* start, T* end, T* des)
{
    while (start <= end) {
        *des = *start;
        start += 1;
        des += 1;
    }
}

template <typename T>
class arrayList {
public:
    arrayList(int initCapacity = 1000)
    {
        arrayLength = initCapacity;
        Name = new my_string[arrayLength];
        No = new T[arrayLength];
        Class = new T[arrayLength];
        Doc = new T[arrayLength];
        listsize = 0;
    }
    ~arrayList()
    {
        delete[] Name;
        delete[] No;
        delete[] Class;
        delete[] Doc;
    }
    void insert(const my_string cName, const T cNo, const T cClass,
        const T cDoc)
    {
        Name[listsize] = cName;
        No[listsize] = cNo;
        Class[listsize] = cClass;
        Doc[listsize] = cDoc;
        listsize++;
    }
    void earse(my_string cName)
    {
        int IndexofName = 0;
        for (; IndexofName < listsize; IndexofName++) {
            if (Name[IndexofName] == cName)
                break;
        }
        if (IndexofName < listsize) {
            for (int i = IndexofName + 1; i < listsize; i++) {
                Name[i - 1] = Name[i];
            }
            my_copy(No + IndexofName + 1, No + listsize, No + IndexofName);
            my_copy(Class + IndexofName + 1, Class + listsize, Class + IndexofName);
            my_copy(Doc + IndexofName + 1, Doc + listsize, Doc + IndexofName);
            listsize--;
        }
    }
    void update(my_string cName, int project, int c)
    {
        int IndexofName = 0;
        for (; IndexofName < listsize; IndexofName++) {
            if (Name[IndexofName] == cName)
                break;
        }
        if (IndexofName < listsize) {
            switch (project) {
            case 1:
                No[IndexofName] = c;
                break;
            case 2:
                Class[IndexofName] = c;
                break;
            case 3:
                Doc[IndexofName] = c;
                break;
            default:
                break;
            }
        }
    }
    void check(my_string cName)
    {
        int checked = 0;
        for (int i = 0; i < listsize; i++) {
            if (cName == Name[i]) {
                checked = 1;
                break;
            }
        }
        ans[anssize++] = checked;
    }
    void output(T cClass)
    {
        T sum = 0;
        for (int i = 0; i < listsize; i++) {
            if (Class[i] == cClass) {
                sum ^= Doc[i];
            }
        }
        ans[anssize++] = sum;
    }
    void out()
    {
        for (int i = 0; i < anssize; i++) {
            cout << ans[i] << endl;
        }
    }

private:
    my_string* Name;
    T* No;
    T* Class;
    T* Doc;
    int arrayLength;
    int listsize;
    int ans[20000];
    int anssize = 0;
};
int main()
{
    arrayList<long long> test(20);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int ope;
        my_string cName;
        long long cNo, cClass, cDoc, project, c;
        cin >> ope;
        switch (ope) {
        case 0:
            cin >> cName >> cNo >> cClass >> cDoc;
            test.insert(cName, cNo, cClass, cDoc);
            break;
        case 1:
            cin >> cName;
            test.earse(cName);
            break;
        case 2:
            cin >> cName >> project >> c;
            test.update(cName, project, c);
            break;
        case 3:
            cin >> cName;
            test.check(cName);
            break;
        case 4:
            cin >> cClass;
            test.output(cClass);
            break;
        }
    }
    test.out();
}