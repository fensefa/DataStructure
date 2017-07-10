#pragma once
#include "search_tree.hpp"

template<typename DataType>
class RbTreeNode {
public:
    enum NodeColor {
        BLACK = 0,
        RED
    };
    DataType data;
    NodeColor color;
    RbTreeNode* left;
    RbTreeNode* right;
    RbTreeNode* parent;
    RbTreeNode() : color(RED), left(nullptr), right(nullptr), parent(nullptr) {
    }
    RbTreeNode(DataType other_data) :
        data(other_data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {
    }
};
template<typename DataType, typename Compare = std::less<DataType>>
class RbTree : public SearchTree<DataType, RbTreeNode<DataType>, Compare> {
public:
    typedef RbTreeNode<DataType> NodeType;
    typedef typename SearchTree<DataType, RbTreeNode<DataType>, Compare>::Iterator Iterator;
    virtual void adjust(NodeType* node) {
        while(true) {
            if (node == nullptr) {
                return;
            }
            if (node->parent == nullptr) {
                node->color = NodeType::BLACK;
                return;
            }
            if (node->color == NodeType::BLACK) {
                return;
            }
            if (node->parent->color == NodeType::BLACK) {
                return;
            }
            NodeType* uncle = this->get_uncle(node);
            if (uncle != nullptr && uncle->color == NodeType::RED) {
                uncle->color = NodeType::BLACK;
                node->parent->color = NodeType::BLACK;
                node->parent->parent->color = NodeType::RED;
                node = node->parent->parent;
                continue;
            }
            if (uncle == nullptr || uncle->color == NodeType::BLACK) {
                NodeType* grandpa = node->parent->parent;
                if (uncle == grandpa->right && node == node->parent->right) {
                    this->left_rotate(node->parent);
                }
                if (uncle == grandpa->left && node == node->parent->left) {
                    this->right_rotate(node->parent);
                }
                if (grandpa->left == uncle) {
                    node = this->left_rotate(grandpa);
                }
                else {
                    node = this->right_rotate(grandpa);
                }
                node->color = NodeType::RED;
                node->left->color = NodeType::BLACK;
                node->right->color = NodeType::BLACK;
                if (grandpa == this->_root) {
                    this->_root = node;
                }
                continue;
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
