template<typename KeyType, typename ValueType>
struct HashNode {
    HashNode() : next(nullptr) {
    }
    HashNode(const KeyType& _key, const ValueType& _value) : key(_key), value(_value), next(nullptr) {
    }
    KeyType key;
    ValueType value;
    HashNode* next;
};

template<typename KeyType, typename ValueType, typename HashFunc = std::hash<KeyType>>
class HashTable {
public:
    typedef HashNode<KeyType, ValueType> HashTableNode;
    void set(const KeyType& key, const ValueType& value) {
        HashTableNode* hash_node = _get_node(key);
        if (hash_node != nullptr) {
            hash_node->value = value;
        }
        else {
            if (_node_count >= _bucket_size) {
                size_t new_bucket_size = _bucket_size == 0 ? 1 : _bucket_size * 2;
                _rehash(new_bucket_size);
            }
            HashTableNode* bucket_node = _get_bucket(key);
            HashTableNode* new_node = new HashTableNode(key, value);
            new_node->next = bucket_node;
            _buckets[_hash_func(key) % _bucket_size] = new_node;
            ++_node_count;
        }
    }
    int get(const KeyType& key, ValueType& value) const {
        HashTableNode* hash_node = _get_node(key);
        if (hash_node == nullptr) {
            return -1;
        }
        value = hash_node->value;
        return 0;
    }
    HashTable() : _buckets(nullptr), _bucket_size(0), _node_count(0) {
    }
private:
    inline HashTableNode* _get_bucket(const KeyType& key) const {
        if (_bucket_size == 0) {
            return nullptr;
        }
        return _buckets[_hash_func(key) % _bucket_size];
    }
    HashTableNode* _get_node(const KeyType& key) const {
        HashTableNode* ret = _get_bucket(key);
        while (ret && ret->key != key) {
            ret = ret->next;
        }
        return ret;
    }
    void _rehash(size_t new_size) {
        HashTableNode** new_buckets = new HashTableNode*[new_size];
        HashFunc new_func;
        for (size_t i = 0; i < _bucket_size; ++i) {
            while (_buckets[i]) {
                HashTableNode* tmp_node = _buckets[i];
                _buckets[i] = _buckets[i]->next;
                HashTableNode*& new_bucket_node = new_buckets[new_func(tmp_node->key) % new_size];
                tmp_node->next = new_bucket_node;
                new_bucket_node = tmp_node;
            }
        }
        _hash_func = new_func;
        _bucket_size = new_size;
        if (_buckets) {
            delete []_buckets;
        }
        _buckets = new_buckets;
    }
    HashTableNode **_buckets;
    HashFunc _hash_func;
    size_t _bucket_size;
    size_t _node_count;
};
