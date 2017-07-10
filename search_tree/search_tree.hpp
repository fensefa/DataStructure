#pragma once

template<typename DataType>
class SearchTreeNode {
public:
    DataType data;
    SearchTreeNode* left;
    SearchTreeNode* right;
    SearchTreeNode* parent;
    SearchTreeNode() : left(nullptr), right(nullptr), parent(nullptr) {
    }
    SearchTreeNode(DataType other_data) :
        data(other_data), left(nullptr), right(nullptr), parent(nullptr) {
    }
};

template<typename DataType, typename NodeType = SearchTreeNode<DataType>, typename Compare = std::less<DataType>>
class SearchTree {
public:
    SearchTree() {
        _root = nullptr;
    }
    ~SearchTree() {
        clear();
    }
    class Iterator {
    public:
        Iterator() {
            _cur_node = nullptr;
        }
        inline DataType& operator*() {
            return _cur_node->data;
        }
        inline DataType* operator->() {
            return &_cur_node->data;
        }
        Iterator operator++() {
            if (_cur_node->right) {
                _cur_node = _cur_node->right;
                while (_cur_node->left) {
                    _cur_node = _cur_node->left;
                }
            }
            else {
                while (_cur_node->parent != nullptr && _cur_node->parent->right == _cur_node) {
                    _cur_node = _cur_node->parent;
                }
                if (_cur_node->parent == nullptr) {
                    _cur_node = nullptr;
                }
                else {
                    _cur_node = _cur_node->parent;
                }
            }
            return *this;
        }
        inline Iterator operator++(int) {
            Iterator res = *this;
            ++*this;
            return res;
        }
        inline bool operator==(const Iterator& other) {
            return (_cur_node == other._cur_node);
        }
        inline bool operator!=(const Iterator& other) {
            return !(*this == other);
        }
        friend class SearchTree;
    private:
        NodeType* _cur_node;
    };
    virtual void insert(DataType data) {
        if (_root == nullptr) {
            _root = new NodeType(data);
            _root->parent = nullptr;
            adjust(_root);
            return;
        }
        NodeType* ptr = _root;
        while (true) {
            if (Compare()(data, ptr->data)) {
                if (ptr->left != nullptr) {
                    ptr = ptr->left;
                    continue;
                }
                else {
                    ptr->left = new NodeType(data);
                    ptr->left->parent = ptr;
                    ptr = ptr->left;
                    ptr->left = ptr->right = nullptr;
                    adjust(ptr);
                    return;
                }
            }
            else if (Compare()(ptr->data, data)) {
                if (ptr->right != nullptr) {
                    ptr = ptr->right;
                    continue;
                }
                else {
                    ptr->right = new NodeType(data);
                    ptr->right->parent = ptr;
                    ptr = ptr->right;
                    ptr->left = ptr->right = nullptr;
                    adjust(ptr);
                    return;
                }
            }
            else {
                ptr->data = data;
                return;
            }
        }
    }
    // TODO
    virtual void erase(Iterator& it) {
        ;
    }
    inline void clear() {
        _destroy_tree(_root);
        _root= nullptr;
    }
    Iterator find(DataType data) {
        NodeType* ptr = _root;
        while (ptr != nullptr) {
            if (Compare()(data, ptr->data)) {
                ptr = ptr->left;
            }
            else if (Compare()(ptr->data, data)) {
                ptr = ptr->right;
            }
            else {
                break;
            }
        }
        Iterator res;
        res._cur_node = ptr;
        return res;
    }
    Iterator begin() {
        NodeType* ptr = _root;
        while (ptr && ptr->left) {
            ptr = ptr->left;
        }
        Iterator res;
        res._cur_node = ptr;
        return res;
    }
    inline Iterator end() {
        Iterator res;
        return res;
    }
protected:
    virtual void adjust(NodeType* node) {
    }
    NodeType* get_uncle(NodeType* node) {
        if (node == nullptr || node->parent == nullptr || node->parent->parent == nullptr) {
            return nullptr;
        }
        if (node->parent->parent->left == node->parent) {
            return node->parent->parent->right;
        }
        else {
            return node->parent->parent->left;
        }
    }
    NodeType* right_rotate(NodeType* node) {
        NodeType* p_cur = node;
        NodeType* p_left = node->left;
        NodeType* p_parent = node->parent;
        p_cur->left = p_left->right;
        if (p_cur->left) {
            p_cur->left->parent = p_cur;
        }
        p_cur->parent = p_left;
        p_left->right = p_cur;
        p_left->parent = p_parent;
        if (p_parent && p_parent->right == p_cur) {
            p_parent->right = p_left;
        }
        else if (p_parent && p_parent->left == p_cur) {
            p_parent->left = p_left;
        }
        return p_left;
    }
    NodeType* left_rotate(NodeType* node) {
        NodeType* p_cur = node;
        NodeType* p_right = node->right;
        NodeType* p_parent = node->parent;
        p_cur->right = p_right->left;
        if (p_cur->right) {
            p_cur->right->parent = p_cur;
        }
        p_cur->parent = p_right;
        p_right->left = p_cur;
        p_right->parent = p_parent;
        if (p_parent && p_parent->left == p_cur) {
            p_parent->left = p_right;
        }
        else if (p_parent && p_parent->right == p_cur) {
            p_parent->right = p_right;
        }
        return p_right;
    }
    void _destroy_tree(NodeType* root) {
        if (root) {
            _destroy_tree(root->left);
            _destroy_tree(root->right);
            delete root;
        }
    }
    NodeType* _root;
};
