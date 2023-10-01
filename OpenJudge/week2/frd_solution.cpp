#include <iostream>
using namespace std;

struct student // 构造联系人结构体
{
    int class_num; // 班级
    char name[20]; // 姓名
    long long phone_num; // 电话号码
    int home_num; // 宿舍号码
};

// 改变一个一维数组长度
template <class T>
void changelength(T*& a, int old_length, int new_length)
{
    T* temp = new T[new_length];
    int number = min(old_length, new_length);
    copy(a, a + number, temp);
    delete[] a;
    a = temp;
}

void strpy(char* a, const char* b) // 复制字符串
{
    int i = 0;
    while (b[i] != '\0') {
        a[i] = b[i];
        i++;
    }
    a[i] = '\0';
}

bool strcmp(char* a, const char* b) // 比较字符串
{
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i])
            break;
        i++;
    }
    if (a[i] == b[i])
        return 0; // 相等返回0
    else
        return 1; // 不相等返回1
}

// 线性表类
class Linearlist {
public:
    Linearlist(int n = 10); // 构造函数
    ~Linearlist(); // 析构函数
    void insert(const char* name, int& class_num, long long& phone_num, int& home_num); // 插入联系人
    void del(const char* name); // 删除联系人
    void edit1(const char* name, long long& phone_num); // 编辑联系人电话
    void edit2(const char* name, int& newnum, int& index); // 编辑联系人班级和宿舍号
    bool search(const char* name); // 查找联系人
    int print(int class_num); // 打印联系人

private:
    student* element; // 联系人数组
    int length; // 联系人个数
    int listsize; // 线性表长度
};

Linearlist::Linearlist(int n)
{
    element = new student[n];
    length = n;
    listsize = 0;
}

Linearlist::~Linearlist() { delete[] element; }

void Linearlist::insert(const char* name, int& class_num, long long& phone_num, int& home_num)
{ // 插入联系人
    if (listsize == length) {
        changelength(element, length, length * 2); // 如果数组已满，扩容
        length *= 2;
    }
    strpy(element[listsize].name, name);
    element[listsize].class_num = class_num;
    element[listsize].phone_num = phone_num;
    element[listsize].home_num = home_num;
    listsize++;
}

void Linearlist::del(const char* name)
{ // 删除联系人
    int i = 0;
    while (i < listsize && strcmp(element[i].name, name) != 0) // 查找联系人
        i++;
    if (i == listsize)
        cout << "没有该联系人" << endl;
    else {
        for (int j = i + 1; j < listsize; j++)
            element[j - 1] = element[j];
        // element[listsize].~student();
        listsize--;
    }
}

void Linearlist::edit1(const char* name, long long& newphone_num)
{ // 编辑联系人电话
    int i = 0;
    while (i < listsize && strcmp(element[i].name, name) != 0) // 查找联系人
        i++;
    if (i == listsize)
        cout << "没有该联系人" << endl;
    else
        element[i].phone_num = newphone_num;
}

void Linearlist::edit2(const char* name, int& newnum, int& index)
{ // 编辑联系人班级和宿舍号
    int i = 0;
    while (i < listsize && strcmp(element[i].name, name) != 0) // 查找联系人
        i++;
    if (i == listsize)
        cout << "没有该联系人" << endl;
    else if (index == 2)
        element[i].class_num = newnum;
    else if (index == 3)
        element[i].home_num = newnum;
}

bool Linearlist::search(const char* name)
{ /// 查找联系人
    int i = 0;
    while (i < listsize && strcmp(element[i].name, name) != 0) // 查找联系人
        i++;
    if (i >= listsize)
        return false;
    else
        return true;
}

int Linearlist::print(int class_num)
{ // 输出所有成员宿舍号的异或值
    int result = 0;
    for (int i = 0; i < listsize; i++)
        if (element[i].class_num == class_num)
            result ^= element[i].home_num;
    return result;
}

int main()
{
    int n;
    cin >> n;
    Linearlist list;
    for (int i = 0; i < n; i++) {
        int class_num, home_num, newnum, index;
        long long phone_num;
        char* name = new char[20];
        cin >> index;
        switch (index) {
        case 0: // 插入
            cin >> name >> phone_num >> class_num >> home_num;
            list.insert(name, class_num, phone_num, home_num);
            break;
        case 1: // 删除
            cin >> name;
            list.del(name);
            break;
        case 2: // 编辑联系人信息
            cin >> name;
            int choose;
            cin >> choose;
            if (choose == 1) {
                cin >> phone_num; // 输入电话号
                list.edit1(name, phone_num); // 编辑电话
            } else {
                cin >> newnum; // 输入班级或宿舍号
                list.edit2(name, newnum, choose); // 编辑班级或宿舍
            }
            break;
        case 3: // 查找
            cin >> name;
            cout << list.search(name) << endl;
            break;
        case 4: // 输出异或值
            cin >> class_num;
            cout << list.print(class_num) << endl;
            break;
        default:
            break;
        }
        delete[] name;
    }

    return 0;
}