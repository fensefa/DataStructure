#ifndef _ABC_SHARED_PTR
#define _ABC_SHARED_PTR

#include <cstdlib>

namespace abc {

template<typename T>
class shared_ptr {
private:
    struct data_node_t {
        data_node_t() {
            _data = nullptr;
            _shared_count = 0;
        }
        ~data_node_t() {
            if (_data != nullptr) {
                delete _data;
            }
        }
        T* _data;
        size_t _shared_count;
    };
public:
    shared_ptr() {
        _data_node = nullptr;
    }
    shared_ptr(void *data) {
        _data_node = new data_node_t();
        _data_node->_shared_count = 1;
        _data_node->_data = (T*)data;
    }
    shared_ptr(const shared_ptr& ptr) {
        _data_node = ptr._data_node;
        ++_data_node->_shared_count;
    }
    shared_ptr(std::nullptr_t) {
        _data_node = nullptr;
    }
    ~shared_ptr() {
        if (_data_node && --_data_node->_shared_count == 0) {
            delete _data_node;
        }
    }

    shared_ptr& operator=(const shared_ptr& ptr) {
        data_node_t* tmp_node = _data_node;
        _data_node = ptr._data_node;
        if (_data_node){
            ++_data_node->_shared_count;
        }
        if (tmp_node && --tmp_node->_shared_count == 0) {
            delete tmp_node;
        }
        return *this;
    }

    inline operator bool() {
        return _data_node != nullptr;
    }
    inline T* operator->() const {
        return _data_node->_data;
    }
    inline T* data() const {
        if (_data_node == nullptr) {
            return nullptr;
        }
        return _data_node->_data;
    }
    inline T& operator*() const {
        return *_data_node->_data;
    }
    void swap(shared_ptr& ptr) {
        data_node_t tmp = _data_node;
        _data_node = ptr._data_node;
        ptr._data_node = tmp;
    }
    size_t shared_count() {
        if (_data_node == nullptr) {
            return 0;
        }
        else {
            return _data_node->_shared_count;
        }
    }
    friend inline bool operator==(const shared_ptr& ptr1, const shared_ptr& ptr2) {
        return ptr1._data_node == ptr2._data_node;
    }
    friend inline bool operator==(const shared_ptr& ptr, std::nullptr_t) {
        return ptr._data_node == nullptr;
    }
    friend inline bool operator==(std::nullptr_t, const shared_ptr& ptr) {
        return ptr._data_node == nullptr;
    }
    friend inline bool operator!=(const shared_ptr& ptr1, const shared_ptr& ptr2) {
        return ptr1._data_node != ptr2._data_node;
    }
    friend inline bool operator!=(const shared_ptr& ptr, std::nullptr_t) {
        return ptr._data_node != nullptr;
    }
    friend inline bool operator!=(std::nullptr_t, const shared_ptr& ptr) {
        return ptr._data_node != nullptr;
    }
private:
    data_node_t *_data_node;
};

}

#endif
