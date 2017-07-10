/*
 * KeyType can only be uint8_t/uint16_t/uint32_t/uint64_t
 *
 * If multiple data has the same key, the find function will return one of the values.
 */

#ifndef CMNEWS_COMMON_SORTED_MAP_HPP
#define CMNEWS_COMMON_SORTED_MAP_HPP

#include <vector>
#include <cstdlib>

#define SCOPE_PARAMETER 4

template<typename KeyType, typename ValueType>
class sorted_map {
public:
    typedef typename std::vector<std::pair<KeyType, ValueType> >::const_iterator const_iterator;
public:
    int init(char *data_ptr, size_t size) {
        std::vector<std::pair<KeyType, ValueType> > data;
        data.resize(size);
        for (size_t i = 0; i < size; ++i) {
            data[i].first = *(KeyType*)(data_ptr + i * (sizeof(KeyType) + sizeof(ValueType)));
            data[i].second = *(ValueType*)(data_ptr + i * (sizeof(KeyType) + sizeof(ValueType)) + sizeof(KeyType));
        }
        _build(data);
        return 0;
    }
    int init(std::vector<std::pair<KeyType, ValueType> > data) {
        _build(data);
        return 0;
    }
    void clear() {
        _move_bit = sizeof(KeyType) * 8 - 1;
        _data.resize(1);
        _buckets.assign(3, 1);
        _size = 0;
    }
    const ValueType& get(const KeyType& key) const {
        typename sorted_map<KeyType, ValueType>::const_iterator it = this->find(key);
        if (it != this->end()) {
            return it->value;
        }
        else {
            ValueType value;
            return value;
        }
    }
    int get(const KeyType& key, ValueType& value) const {
        typename sorted_map<KeyType, ValueType>::const_iterator it = this->find(key);
        if (it != this->end()) {
            value =  it->second;
            return 0;
        }
        else {
            return -1;
        }
    }
    size_t size() const {
        return _size;
    }
    const_iterator find(const KeyType& key) const {
        KeyType pos = (key >> _move_bit);
        KeyType low = _buckets[pos];
        KeyType high = _buckets[pos + 1] - 1;
        while (low <= high) {
            // KeyType mid = low + (high - low) / 2;
            KeyType mid = (low + high) / 2;
            if (_data[mid].first < key) {
                low = mid + 1;
                continue;
            }
            if (_data[mid].first == key) {
                return _data.cbegin() + mid;
            }
            else {
                high = mid - 1;
            }
        }
        return _data.cend();
    }
    const_iterator begin() const {
        return _data.cbegin() + 1;
    }
    const_iterator end() const {
        return _data.cend();
    }
private:
    void _get_scope(size_t n) {
        _scope = 1;
        char scope_bit = 0;
        while (_scope <= n / SCOPE_PARAMETER + 1) {
            _scope <<= 1;
            ++scope_bit;
        }
        _move_bit = sizeof(KeyType) * 8 - scope_bit;
        return;
    }
    void _build(std::vector<std::pair<KeyType, ValueType> >& data) {
        size_t size = data.size();
        _get_scope(size);
        _data.resize(size + 1);
        _size = size;
        _buckets.assign(_scope + 1, 0);
        _buckets[0] = 1;
        for (auto it = data.begin(); it != data.end(); ++it) {
            KeyType index = _get_bucket(it->first);
            ++_buckets[index];
        }
        for (auto it = _buckets.begin() + 1; it != _buckets.end(); ++it) {
            *it += *(it-1);
        }
        for (auto it = data.begin(); it != data.end(); ++it) {
            KeyType index = _get_bucket(it->first);
            KeyType pos = --_buckets[index];
            _data[pos].swap(*it);
        }
        for (auto it = _buckets.begin(); it != _buckets.end() - 1; ++it) {
            sort(_data.begin() + *it, _data.begin() + *(it + 1));
        }
    }
    KeyType _get_bucket(const KeyType& key) {
        return key >> _move_bit;
    }
private:
    std::vector<std::pair<KeyType, ValueType>> _data;
    std::vector<KeyType> _buckets;
    size_t _scope;
    char _move_bit;
    size_t _size;
};

#endif // CMNEWS_COMMON_SORTED_MAP_HPP
