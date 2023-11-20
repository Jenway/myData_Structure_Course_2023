#include <cstddef>
#if !defined(__STRING_H__)
#define __STRING_H__
#include <iostream>
#include <istream>
#include <ostream>

using namespace std;

constexpr int BUFFER_SIZE = 1024; // set it larger if you need

class my_string {
private:
    char* data;
    size_t length;

    static int my_strlen(const char* str);
    static void my_strcpy(char* dst, const char* src);

public:
    class iterator {
    private:
        char* ptr;

    public:
        iterator(char* ptr)
            : ptr(ptr)
        {
        }
        iterator& operator++()
        {
            ptr++;
            return *this;
        }
        iterator operator++(int)
        {
            iterator temp = *this;
            ++*this;
            return temp;
        }
        iterator& operator--()
        {
            ptr--;
            return *this;
        }
        iterator operator--(int)
        {
            iterator temp = *this;
            --*this;
            return temp;
        }
        char& operator*() { return *ptr; }
        bool operator==(const iterator& it) { return ptr == it.ptr; }
        bool operator!=(const iterator& it) { return ptr != it.ptr; }
    };
    iterator begin() { return iterator(data); }
    iterator end() { return iterator(data + length); }
    iterator begin() const { return iterator(data); }
    iterator end() const { return iterator(data + length); }

    my_string(const char* str = nullptr);
    my_string& operator=(const char* str);
    my_string(char c);
    my_string& operator=(char c);

    my_string(const my_string& str);
    my_string& operator=(const my_string& str);
    my_string(my_string&& str) noexcept;
    my_string& operator=(my_string&& str) noexcept;

    ~my_string() { delete[] data; }

    int toInt();

    bool operator==(const my_string& str) const;
    char& operator[](size_t n) const;

    size_t size() const { return length; }
    const char* c_str() const { return data; }

    friend istream& operator>>(istream& is, my_string& str);
    friend ostream& operator<<(ostream& os, my_string& str);

    friend my_string operator+(const my_string& lhs, const my_string& rhs);
    my_string& operator+=(const my_string& rhs);
};

inline my_string::my_string(const char* str)
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
inline my_string::my_string(char c)
{
    length = 1;
    data = new char[length + 1];
    data[0] = c;
    data[1] = '\0';
}
inline my_string::my_string(const my_string& str)
{
    length = str.size();
    data = new char[length + 1];
    my_strcpy(data, str.c_str());
}

inline int my_string::toInt()
{
    int res = 0;
    for (size_t i = 0; i < length; i++) {
        res = res * 10 + data[i] - '0';
    }
    return res;
}

inline my_string& my_string::operator=(const my_string& str)
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

inline my_string& my_string::operator=(const char* str)
{
    if (data == str) {
        return *this;
    }
    delete[] data;
    length = my_strlen(str);
    data = new char[length + 1];
    my_strcpy(data, str);
    return *this;
}

inline my_string& my_string::operator=(char c)
{
    delete[] data;
    length = 1;
    data = new char[length + 1];
    data[0] = c;
    data[1] = '\0';
    return *this;
}
inline my_string::my_string(my_string&& str) noexcept
{
    length = str.size();
    data = str.data;
    str.data = nullptr;
    str.length = 0;
}

inline my_string& my_string::operator=(my_string&& str) noexcept
{
    if (this == &str) {
        return *this;
    }
    delete[] data;
    length = str.size();
    data = str.data;
    str.data = nullptr;
    str.length = 0;
    return *this;
}

inline bool my_string::operator==(const my_string& str) const
{
    if (length != str.size()) {
        return false;
    }
    for (size_t i = 0; i < length; i++) {
        if (data[i] != str[i]) {
            return false;
        }
    }
    return true;
}

inline char& my_string::operator[](size_t n) const
{
    if (n >= length) {
        throw "out of range";
    } else {
        return data[n];
    }
}

inline istream& operator>>(istream& is, my_string& str)
{
    char* temp = new char[BUFFER_SIZE];
    is >> temp;
    delete[] str.data;
    str.length = str.my_strlen(temp);
    str.data = new char[str.length + 1];
    str.my_strcpy(str.data, temp);
    delete[] temp;
    return is;
}

inline ostream& operator<<(ostream& os, my_string& str)
{
    os << str.c_str();
    return os;
}

inline ostream& operator<<(ostream& os, const my_string& str)
{
    os << str.c_str();
    return os;
}

inline int my_string::my_strlen(const char* str)
{
    int len = 0;
    while (*str++ != '\0') {
        len++;
    }
    return len;
}
inline void my_string::my_strcpy(char* dst, const char* src)
{
    while (*src != '\0') {
        *dst++ = *src++;
    }
    *dst = '\0';
}

inline my_string& my_string::operator+=(const my_string& rhs)
{
    char* temp = new char[length + 1];
    my_strcpy(temp, data);
    delete[] data;
    length += rhs.size();
    data = new char[length + 1];
    my_strcpy(data, temp);
    my_strcpy(data + length - rhs.size(), rhs.c_str());
    delete[] temp;
    return *this;
}

inline my_string operator+(const my_string& lhs, const my_string& rhs)
{
    my_string res;
    res.length = lhs.size() + rhs.size();
    res.data = new char[res.length + 1];
    my_string::my_strcpy(res.data, lhs.c_str());
    my_string::my_strcpy(res.data + lhs.size(), rhs.c_str());
    return res;
}

#endif // __STRING_H__