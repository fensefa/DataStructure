namespace abc {

template<typename KeyType, typename ValueType>
class map {
private:
    struct Compare {
        inline bool operator() (const std::pair<KeyType, ValueType>& p1, const std::pair<KeyType, ValueType>& p2) {
            return p1.first < p2.first;
        }
    };
public:
    typedef typename RbTree<std::pair<KeyType, ValueType>, Compare>::Iterator iterator;
    inline iterator find(const KeyType& key) {
        std::pair<KeyType, ValueType> tmp_pair;
        tmp_pair.first = key;
        return _rb_tree.find(tmp_pair);
    }
    inline iterator begin() {
        return _rb_tree.begin();
    }
    inline iterator end() {
        return _rb_tree.end();
    }
    inline void emplace(const KeyType& key, const ValueType& value) {
        std::pair<KeyType, ValueType> tmp_pair = std::make_pair(key, value);
        _rb_tree.insert(tmp_pair);
    }
    /*
    void print() {
        _rb_tree.print();
    }
    */
private:
    RbTree<std::pair<KeyType, ValueType>, Compare> _rb_tree;
};

}
