//
// Created by jujun on 11/18/2020.
//

#ifndef BSTBASE_TREENODE_H
#define BSTBASE_TREENODE_H
template<typename T>
class TreeNode{
public:
    TreeNode(T value){
        this->value = value;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    T getValue(){
        return value;
    }

    void setValue(T value){
        this->value = value;
    }

    TreeNode<T>* getLeftChild(){
        return left;
    }

    void setLeftChild(TreeNode<T>* left){
        this->left = left;
    }

    TreeNode<T>* getRightChild(){
        return right;
    }

    void setRightChild(TreeNode<T>* right){
        this->right = right;
    }

    TreeNode<T>* getParentNode(){
        return parent;
    }

    void setParentNode(TreeNode<T>* parent){
        this->parent = parent;
    }

    friend bool operator<=(const TreeNode<T>& left, const
    TreeNode<T>& right) {
        return (left.value <= right.value);
    }

    friend bool operator>(const TreeNode<T>& left, const
    TreeNode<T>& right) {
        return !(left <= right);
    }

private:
    T value;
    TreeNode<T>* left;
    TreeNode<T>* right;
    TreeNode<T>* parent;
};

#endif //BSTBASE_TREENODE_H
