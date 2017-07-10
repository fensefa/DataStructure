namespace abc {

template<typename DataType>
class set {
public:
    typedef typename RbTree<DataType>::Iterator iterator;
    inline iterator find(const DataType& key) {
        return _rb_tree.find(key);
    }
    inline iterator begin() {
        return _rb_tree.begin();
    }
    inline iterator end() {
        return _rb_tree.end();
    }
    inline void emplace(const DataType& key) {
        _rb_tree.insert(key);
    }
    void print() {
        _rb_tree.print();
    }
private:
    RbTree<DataType> _rb_tree;
};

}
