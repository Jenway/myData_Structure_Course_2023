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

typedef struct contact {
    // 联系人的内容有：姓名、电话号码、班级、宿舍
    my_string name;
    my_string phone;
    my_string class_;
    my_string dormitory;
    // methods
    void input();
    void output();

    contact() = default;
    contact(my_string name, my_string phone, my_string class_, my_string dormitory);
} Contact;

class ContactList {
    // 联系人列表
private:
    Contact* contacts;
    int size = 0;
    int length = 0;

public:
    ContactList(int size);
    ContactList();
    ~ContactList();

    bool isFull() { return length == size; }

    // 插入、删除、编辑、查找（按姓名查找）
    // 键盘输入一班级，输出通讯录中该班级中所有人的信息。
    void addContact();
    void deleteContact(my_string name);
    void editContact(my_string name);
    void ifFindContact(my_string name);
    void findClass(my_string class_);

    void switchChoice(int choice);
    void runTest(int n);

    Contact* findContact(my_string name);
};

int main(void)
{
    int n;
    ContactList* contactList = new ContactList();
    cin >> n;
    contactList->runTest(n);
    delete contactList;
    return 0;
}

Contact::contact(my_string name, my_string phone, my_string class_, my_string dormitory)
    : name(name)
    , phone(phone)
    , class_(class_)
    , dormitory(dormitory)
{
}

void Contact::input()
{
    cin >> name >> phone >> class_ >> dormitory;
}
void Contact::output()
{
    cout << name << " " << phone << " " << class_ << " " << dormitory << endl;
}

ContactList::ContactList(int size_)
    : size(size_)
{
    this->size = size_;
    contacts = new Contact[this->size];
}

ContactList::ContactList()
    : size(100)
{
    contacts = new Contact[this->size];
}

ContactList::~ContactList()
{
    delete[] contacts;
}

void ContactList::runTest(int n)
{
    int choice;
    for (int i = 0; i < n; i++) {
        cin >> choice;
        switchChoice(choice);
    }
}

void ContactList::switchChoice(int choice)
{
    enum { ADD,
        DELETE,
        EDIT,
        FIND,
        FINDCLASS };
    my_string name;

    switch (choice) {
    case ADD:
        addContact();
        break;
    case DELETE:
        cin >> name;
        deleteContact(name);
        break;
    case EDIT:
        cin >> name;
        editContact(name);
        break;
    case FIND:
        cin >> name;
        ifFindContact(name);
        break;
    case FINDCLASS:
        cin >> name;
        findClass(name);
        break;
    default:
        break;
    }
}

void ContactList::addContact()
{
    Contact contact;
    contact.input();

    if (!isFull()) {
        contacts[length++] = contact;
    } else {
        cout << "通讯录已满，无法添加" << endl;
    }
}

void ContactList::deleteContact(my_string name)
{
    // no need to be efficient
    for (int i = 0; i < length; i++) {
        if (contacts[i].name == name) {
            for (int j = i; j < length - 1; j++) {
                contacts[j] = contacts[j + 1];
            }
            length--;
            return;
        }
    }
}

Contact* ContactList::findContact(my_string name)
{
    for (int i = 0; i < length; i++) {
        if (contacts[i].name == name) {
            return &contacts[i];
        }
    }
    return nullptr;
}

void ContactList::editContact(my_string name)
{
    Contact* contact = findContact(name);
    enum { CHOICE,
        PHONE,
        CLASS,
        DORMITORY,
    };
    int choice;
    cin >> choice;
    switch (choice) {
    case PHONE:
        cin >> contact->phone;
        break;
    case CLASS:
        cin >> contact->class_;
        break;
    case DORMITORY:
        cin >> contact->dormitory;
        break;
    default:
        break;
    }
}

void ContactList::ifFindContact(my_string name)
{
    // 找到相应的人时输出 1，未找到输出 0
    Contact* contact = findContact(name);
    if (contact == nullptr) {
        cout << 0 << endl;
    } else {
        cout << 1 << endl;
    }
}

// 4 班级 输出该班级的所有成员的宿舍号的异或值

void ContactList::findClass(my_string class_)
{
    int sum = 0;
    for (int i = 0; i < length; i++) {
        if (contacts[i].class_ == class_) {
            // sum ^= stoi(contacts[i].dormitory);
            sum ^= contacts[i].dormitory.toInt();
        }
    }
    cout << sum << endl;
}

// <---- below are implementation of my_string ---->

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