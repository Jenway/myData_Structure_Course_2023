#include<iostream>
using namespace std;

class Arraylist; // 预先声明

class Data{
    //friend class Arraylist;
public:
    void initialize(char n[], long long t, short c,short r);
    const char* getName() { return name; }
    short getRoom() { return room_id; }
    void delStudent();
    void editTEL(long long t) { if(t>0) tel_number = t; }
    void editClass(short c) { if(c>0) class_id = c; }
    void editRoom(short r) { if(r>0) room_id = r; }
private:
    char name[20]; // 名字
    long long tel_number; // 电话
    short class_id; // 班级号
    short room_id; // 宿舍号
};

void Data::initialize(char n[], long long t, short c, short r) { // 个人信息初始化
    if(t > 0 && c > 0 && r > 0){
        for(int i=0; i<20; ++i){
            name[i] = '\0';
            name[i] = n[i];
        }
        tel_number = t;
        class_id = c;
        room_id = r;
    }

}

void Data::delStudent() {
    for(int i=0; i<20; ++i){
        name[i] = '\0';
    }
}

class Arraylist{
public:
    Arraylist(int s): steps(s){
        list = new Data[steps];
        length=0;
    }
    ~Arraylist(){ delete[] list; }
    void insert(); // 添加
    Data* search(); // 查找
    void editData();
    void delData(); // 删除
    bool compareName(const char* arr1, const char* arr2);
    void xOR(); // 异或和
private:
    int steps;
    int length;
    Data* list;
};

void Arraylist::insert() {
    if(length == steps) return;
    char n[20];
    long long t;
    short c,r;
    scanf("%s", n);
    cin >> t >> c >> r;
    list[length++].initialize(n,t,c,r);
}

void Arraylist::delData() {
    Data* temp = search();
    if(temp != nullptr)
        temp->delStudent();
}

Data* Arraylist::search(){
    char n[20];
    scanf("%s", n);
    for(int i=0; i < length; ++i){
        if( compareName(list[i].getName(), n) ) {
            return &list[i];
        }
    }
    return nullptr;
}

bool Arraylist::compareName(const char* arr1, const char* arr2) {
    const char* ptr1 = arr1;
    const char* ptr2 = arr2;
    // 逐个比较数组元素，直到遇到空字符
    while (*ptr1 != '\0' && *ptr2 != '\0') {
        if (*ptr1 != *ptr2) {
            return false;
        }
        ptr1++;
        ptr2++;
    }
    // 检查是否同时到达末尾
    if (*ptr1 != *ptr2) {
        return false;
    }
    return true;
}

void Arraylist::editData() {
    Data* temp = search();
    if(temp == nullptr)
        return;
    short operate;
    long long new_number;
    cin >> operate >> new_number;
    switch (operate) {
        case 1: temp->editTEL(new_number); break;
        case 2: temp->editClass((short)new_number); break;
        case 3: temp->editRoom((short)new_number);
    }
}

void Arraylist::xOR() {
    int room_Num;
    int points = 0;
    cin >> room_Num;
    for(int i=0; i < length; ++i){
        if( list[i].getRoom() == room_Num ) {
            points ^= room_Num;
        }
    }
    cout << points << endl ;
}


int main(){
    int steps,operate;
    cin >> steps;
    Arraylist Test(steps);
    for(int i=0; i<steps; ++i){
        cin >> operate;
        switch(operate){
            case 0: Test.insert(); break;
            case 1: Test.delData(); break;
            case 2: Test.editData(); break;
            case 3: {
                if(Test.search() != nullptr){
                    cout <<"1\n";
                } else cout <<"0\n";
                break;
            }
            case 4: Test.xOR();
        }
    }
    return 0;
};
