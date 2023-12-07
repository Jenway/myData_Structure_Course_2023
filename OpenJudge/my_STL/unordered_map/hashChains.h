#include <iostream>

using std::cin, std::cout, std::endl;

template <typename K>
class Hash;

// template <>
// class Hash<string> {
// public:
//     size_t operator()(const string theKey) const
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

template <typename K, typename E>
struct pair {
    K first;
    E second;
    pair(const K& k = K(), const E& e = E())
        : first(k)
        , second(e)
    {
    }
};

template <typename K, typename E>
class sortedChain {
private:
    struct pairNode {
        typedef pair<const K, E> pairType;
        pairType element;
        pairNode* next;

        pairNode(const pairType& thePair, pairNode* theNext = nullptr)
            : element(thePair)
            , next(theNext)
        {
        }
    }* firstNode;
    int dSize;

    pair<const K, E>* search(const K&) const;

public:
    sortedChain()
        : firstNode(nullptr)
        , dSize(0)
    {
    }
    ~sortedChain();

    bool empty() const { return dSize == 0; }
    int size() const { return dSize; }

    pair<const K, E>* find(const K&) const;
    void erase(const K&);
    void insert(const pair<const K, E>&);
};

template <typename K, typename E>
sortedChain<K, E>::~sortedChain()
{
    while (firstNode != nullptr) {
        pairNode* nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template <typename K, typename E>
pair<const K, E>* sortedChain<K, E>::search(const K& theKey) const
{
    pairNode* currentNode = firstNode;
    while (currentNode != nullptr && currentNode->element.first != theKey) {
        currentNode = currentNode->next;
    }

    if (currentNode != nullptr && currentNode->element.first == theKey) {
        return &currentNode->element;
    } else {
        return nullptr;
    }
}

template <typename K, typename E>
pair<const K, E>* sortedChain<K, E>::find(const K& theKey) const
{
    if (pair<const K, E>* p = search(theKey)) {
        cout << this->dSize << endl;
        return p;
    } else {
        cout << "Not Found" << endl;
        return nullptr;
    }
}

template <typename K, typename E>
void sortedChain<K, E>::insert(const pair<const K, E>& thePair)
{

    pairNode *curr = firstNode, *prev = nullptr;

    while (curr != nullptr && curr->element.first < thePair.first) {
        prev = curr;
        curr = curr->next;
    }

    if (curr != nullptr && curr->element.first == thePair.first) {
        cout << "Existed" << endl;
        return;
    } else {

        if (pairNode* newNode = new pairNode(thePair, curr); prev == nullptr) {
            firstNode = newNode;
        } else {
            prev->next = newNode;
        }

        dSize++;
    }
}

template <typename K, typename E>
void sortedChain<K, E>::erase(const K& theKey)
{
    pairNode *curr = firstNode, *prev = nullptr;

    while (curr != nullptr && curr->element.first < theKey) {
        prev = curr;
        curr = curr->next;
    }

    if (curr != nullptr && curr->element.first == theKey) {
        if (prev == nullptr) {
            firstNode = curr->next;
        } else {
            prev->next = curr->next;
        }
        delete curr;
        dSize--;
        cout << this->dSize << endl;
    } else {
        cout << "Delete Failed" << endl;
    }
}

template <typename K, typename E>
class hashChains {
private:
    Hash<K> hash;
    int dSize;
    int divisor;
    sortedChain<K, E>* table;

public:
    hashChains(int theDivisor = 11)
        : divisor(theDivisor)
        , dSize(0)
        , table(new sortedChain<K, E>[divisor] {})
    {
    }

    ~hashChains() { delete[] table; }

    bool empty() const { return dSize == 0; }
    int size() const { return dSize; }

    pair<const K, E>* find(const K& theKey) const
    {
        return table[hash(theKey) % divisor].find(theKey);
    }

    void insert(const pair<const K, E>& thePair)
    {
        int homeBucket = (int)hash(thePair.first) % divisor;
        int homeSize = table[homeBucket].size();
        table[homeBucket].insert(thePair);
        if (table[homeBucket].size() > homeSize) {
            dSize++;
        }
    }

    void erase(const K& theKey)
    {
        table[hash(theKey) % divisor].erase(theKey);
    }
};
