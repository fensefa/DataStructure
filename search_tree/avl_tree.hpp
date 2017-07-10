#pragma once
#include "search_tree.hpp"

template<typename DataType>
class AvlTreeNode {
public:
    DataType data;
    int32_t height;
    AvlTreeNode* left;
    AvlTreeNode* right;
    AvlTreeNode* parent;
    AvlTreeNode() : height(0), left(nullptr), right(nullptr), parent(nullptr) {
    }
    AvlTreeNode(DataType other_data) :
        data(other_data), height(0), left(nullptr), right(nullptr), parent(nullptr) {
    }
};
template<typename DataType, typename Compare = std::less<DataType>>
class AvlTree : public SearchTree<DataType, AvlTreeNode<DataType>, Compare> {
public:
    typedef AvlTreeNode<DataType> NodeType;
    typedef typename SearchTree<DataType, AvlTreeNode<DataType>, Compare>::Iterator Iterator;
    int get_height(NodeType* node) {
        if (!node) {
            return 0;
        }
        return node->height;
    }
    virtual void adjust(NodeType* node) {
        int tmp_height = 1;
        while (node) {
            if (node->height >= tmp_height) {
                return;
            }
            node->height = tmp_height;
            int left_height = get_height(node->left);
            int right_height = get_height(node->right);
            if (left_height > right_height + 1) {
                if (get_height(node->left->left) < get_height(node->left->right)) {
                    this->left_rotate(node->left);
                }
                NodeType* res = this->right_rotate(node);
                if (this->_root == node) {
                    this->_root = res;
                }
                return;
            }
            else if (left_height < right_height - 1) {
                if (get_height(node->right->left) > get_height(node->right->right)) {
                    this->right_rotate(node->right);
                }
                NodeType* res = this->left_rotate(node);
                if (this->_root == node) {
                    this->_root = res;
                }
                return;
            }
            else {
                ++tmp_height;
                node = node->parent;
            }
        }
    }
    // TODO
    /*
    virtual void erase(Iterator& it) {
        ;
    }
    */
};
