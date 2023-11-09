template <typename K, typename E>
struct myPair {
    K first;
    E second;
};

template <typename K, typename E>
class my_unordered_map {
    using Pair = myPair<K, E>;

private:
    int search(const K& theKey) const
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
    // std::hash<K> Hash;
    int Hash(const K& key) const { return static_cast<K>(key); };
    int divisor;
    int dSize;
    Pair** table;

public:
    // iterator
    class iterator {
    private:
        Pair* position;

    public:
        iterator(Pair* thePosition = nullptr)
            : position(thePosition)
        {
        }
        Pair& operator*() const { return *position; }
        Pair* operator->() const { return &*position; }
        iterator& operator++()
        {
            ++position;
            return *this;
        }
        iterator operator++(int)
        {
            iterator old = *this;
            ++position;
            return old;
        }
        bool operator==(const iterator right) const
        {
            return position == right.position;
        }
        bool operator!=(const iterator right) const { return !(*this == right); }
    };

    iterator begin() const { return iterator(table[0]); }
    iterator end() const { return iterator(nullptr); }

    my_unordered_map(int theDivisor = 11)
        : divisor(theDivisor)
        , dSize(0)
    {
        table = new Pair*[divisor];
        for (int i = 0; i < divisor; i++) {
            table[i] = nullptr;
        }
    }
    ~my_unordered_map()
    {
        for (int i = 0; i < divisor; i++) {
            if (table[i] != nullptr) {
                delete table[i];
            }
        }
        delete[] table;
    }
    bool empty() const { return dSize == 0; }
    int size() const { return dSize; }

    // find
    iterator find(const K& key) const
    {
        int index = search(key);
        if (table[index] == nullptr) {
            return end();
        } else {
            return iterator(table[index]);
        }
    }

    // insert
    void insert(const Pair& thePair)
    {
        int index = search(thePair.first);
        if (table[index] == nullptr) {
            table[index] = new Pair(thePair);
            dSize++;
        } else {
            table[index]->second = thePair.second;
        }
    }

    // [] operator
    E& operator[](const K& key)
    {
        int index = search(key);
        if (table[index] == nullptr) {
            table[index] = new Pair { key, E() };
            dSize++;
        }
        return table[index]->second;
    }
};