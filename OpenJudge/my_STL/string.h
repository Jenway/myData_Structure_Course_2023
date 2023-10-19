#include <iostream>
#include <istream>
#include <ostream>

using namespace std;

class my_string {
private:
    char* data;
    size_t length;
    int my_strlen(const char* str);
    void my_strcpy(char* dst, const char* src);

public:
    my_string(const char* str = nullptr);
    my_string(const my_string& str);
    ~my_string();

    int toInt();

    my_string& operator=(const my_string& str);
    bool operator==(const my_string& str) const;
    char& operator[](int n) const;
    size_t size() const;
    const char* c_str() const;

    friend istream& operator>>(istream& is, my_string& str);
    friend ostream& operator<<(ostream& os, my_string& str);
};

my_string::my_string(const char* str)
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
my_string::my_string(const my_string& str)
{
    length = str.size();
    data = new char[length + 1];
    my_strcpy(data, str.c_str());
}
my_string::~my_string()
{
    delete[] data;
}

int my_string::toInt()
{
    int res = 0;
    for (int i = 0; i < length; i++) {
        res = res * 10 + data[i] - '0';
    }
    return res;
}

my_string& my_string::operator=(const my_string& str)
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

bool my_string::operator==(const my_string& str) const
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

char& my_string::operator[](int n) const
{
    return data[n];
}

size_t my_string::size() const { return length; }
const char* my_string::c_str() const { return data; }

istream& operator>>(istream& is, my_string& str)
{
    char temp[100];
    is >> temp;
    delete[] str.data;
    str.length = str.my_strlen(temp);
    str.data = new char[str.length + 1];
    str.my_strcpy(str.data, temp);
    return is;
}
ostream& operator<<(ostream& os, my_string& str)
{
    os << str.c_str();
    return os;
}
int my_string::my_strlen(const char* str)
{
    int len = 0;
    while (*str++ != '\0') {
        len++;
    }
    return len;
}
void my_string::my_strcpy(char* dst, const char* src)
{
    while (*src != '\0') {
        *dst++ = *src++;
    }
    *dst = '\0';
}