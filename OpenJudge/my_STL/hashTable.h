#include <iostream>
// #include <string>

using std::cin, std::cout, std::endl;

template <typename K>
class Hash;

// template <>
// class Hash<std::string> {
// public:
//     size_t operator()(const std::string theKey) const
//     {
//         unsigned long hashValue = 0;
//         int length = (int)theKey.length();
//         for (int i = 0; i < length; i++)
//             hashValue = 5 * hashValue + theKey.at(i);

//         return size_t(hashValue);
//     }
// };

template <>
class Hash<int> {
public:
    size_t operator()(const int theKey) const
    {
        return size_t(theKey);
    }
};

template <>
class Hash<long> {
public:
    size_t operator()(const long theKey) const
    {
        return size_t(theKey);
    }
};

template <typename T>
using hash = Hash<T>;

template <class K, class E>
struct pair {
    K first;
    E second;
    pair(const K& k = K(), const E& e = E())
        : first(k)
        , second(e)
    {
    }
};

template <class K, class E>
class hashTable {
private:
    int search(const K&) const;
    hash<K> Hash;
    int divisor;
    int dSize;
    pair<const K, E>** table;

public:
    hashTable(int theDivisor = 11);
    ~hashTable() { delete[] table; }

    bool empty() const { return dSize == 0; }
    int size() const { return dSize; }

    void insert(const pair<const K, E>&);
    pair<const K, E>* find(const K&) const;
    void erase(const K& theKey);
};

template <class K, class E>
hashTable<K, E>::hashTable(int theDivisor)
    : divisor(theDivisor)
    , dSize(0)
    , table(new pair<const K, E>* [divisor] {})
{
}

template <class K, class E>
int hashTable<K, E>::search(const K& theKey) const
{

    int i = (int)Hash(theKey) % divisor;
    int j = i;
    do {
        if (table[j] == nullptr || table[j]->first == theKey)
            return j;
        j = (j + 1) % divisor;
    } while (j != i);

    return j;
}

template <class K, class E>
pair<const K, E>* hashTable<K, E>::find(const K& theKey) const
{

    int index = search(theKey);

    if (table[index] == nullptr || table[index]->first != theKey) {
        cout << "-1" << endl;
        return nullptr;
    }

    cout << index << endl;
    return table[index];
}

template <class K, class E>
void hashTable<K, E>::insert(const pair<const K, E>& thePair)
{
    int index = search(thePair.first);

    if (table[index] == nullptr) {
        table[index] = new pair<const K, E>(thePair);
        dSize++;
        cout << index << endl;
    } else {
        if (table[index]->first == thePair.first) {
            cout << "Existed\n";
        } else {
            throw "hash table is full";
        }
    }
}

template <class K, class E>
void hashTable<K, E>::erase(const K& theKey)
{
    int index = search(theKey);
    if (table[index] == nullptr || table[index]->first != theKey) {
        cout << "Not Found\n";
        return;
    }

    delete table[index];
    dSize--;

    int pre = index, cnt = 0;

    for (int i = 1; i < dSize; i++) {
        index = (index + 1) % divisor;

        if (table[index] == nullptr) {
            break; // if next is empty, break
        } else {
            int index_key = Hash(table[index]->first) % divisor;

            if (index_key == index || (index_key < index && index < pre) || (index < pre && pre < index_key) || (pre < index_key && index_key < index)) {
                // 如果 index 在 index_key 的环形顺序之后， pre 之前
                /*
                 * - index 恰好位于 哈希映射的位置
                 * - index 排在 哈希映射位置之后，pre 之前
                 * - pre 排在 哈希映射位置之前，index 在 pre 之前
                 * - pre 在 哈希映射位置之前，index 在 哈希映射位置之后
                 */
                continue;
            } else {
                table[pre] = table[index];
                pre = index;
                cnt++;
            }
        }
    }
    table[pre] = nullptr;

    cout << cnt << endl;
}
