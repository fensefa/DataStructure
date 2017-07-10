#pragma once
#include "search_tree.hpp"

static uint64_t get_rand_num()
{
    uint64_t res = 0;
    for (int i = 0; i < 4; ++i) {
        res *= ((uint64_t)RAND_MAX + 1);
        res += rand();
    }
    return res;
}

template<typename DataType>
class TreapNode {
public:
    DataType data;
    uint64_t priority;
    TreapNode* left;
    TreapNode* right;
    TreapNode* parent;
    TreapNode() : priority(get_rand_num()), left(nullptr), right(nullptr), parent(nullptr) {
    }
    TreapNode(DataType other_data) :
        data(other_data), priority(get_rand_num()), left(nullptr), right(nullptr), parent(nullptr) {
    }
};
template<typename DataType, typename Compare = std::less<DataType>>
class Treap : public SearchTree<DataType, TreapNode<DataType>, Compare> {
public:
    typedef TreapNode<DataType> NodeType;
    typedef typename SearchTree<DataType, TreapNode<DataType>, Compare>::Iterator Iterator;
    virtual void adjust(NodeType* node) {
        if (node == nullptr) {
            return;
        }
        while(node->parent) {
            if (node->priority < node->parent->priority) {
                if (node == node->parent->left) {
                    this->right_rotate(node->parent);
                    continue;
                }
                else {
                    this->left_rotate(node->parent);
                    continue;
                }
            }
            else {
                return;
            }
        }
        this->_root = node;
    }
    // TODO
    /*
    virtual void erase(Iterator& it) {
        ;
    }
    */
};
