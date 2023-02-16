//
// Created by jujun on 11/18/2020.
//

#ifndef BSTBASE_BINARYSEARCHTREE_H
#define BSTBASE_BINARYSEARCHTREE_H
#include "TreeNode.h"
#include <vector>
#include "math.h"
using namespace std;

template<typename T>
class BinarySearchTree{
public:
    BinarySearchTree(TreeNode<T>* root){
        this->root = root;
    }

    void traverse(vector<T> &traversalVector) const {
        traverseHelper(root, traversalVector);
    }

    void addNode(TreeNode<T>* node){
        addNodeHelper(node,root);
    }


    void clearContents(){//clears all nodes of children and parent pointers
        vector<TreeNode<T>*> nodes;
        clearContentsHelper(root,nodes);
        for(int i=0;i<nodes.size();i++){
            nodes[i]->setLeftChild(nullptr);
            nodes[i]->setRightChild(nullptr);
            nodes[i]->setParentNode(nullptr);
        }
    }

    TreeNode<T>* find(int value) {
        findHelper(value,root);
    }

    TreeNode<T>* remove(int value){
        TreeNode<T>* currNode = findHelper(value,root);
        if(currNode->getLeftChild() == nullptr && currNode->getRightChild() == nullptr){//remove node if no children
            if(currNode->getParentNode()->getValue() > currNode->getValue()){
                currNode->getParentNode()->setLeftChild(nullptr);
                currNode->setParentNode(nullptr);
                return currNode;
            }
            else if(currNode->getParentNode()->getValue() <= currNode->getValue()){
                currNode->getParentNode()->setRightChild(nullptr);
                currNode->setParentNode(nullptr);
                return currNode;
            }
        }
        else if(currNode->getLeftChild() != nullptr && currNode->getRightChild() == nullptr || currNode->getLeftChild() == nullptr && currNode->getRightChild() != nullptr){//remove node if 1 child
            if(currNode->getParentNode()->getLeftChild() == currNode) {
                TreeNode<T>* parent = currNode->getParentNode();
                if(currNode->getLeftChild() != nullptr){
                    parent->setLeftChild(currNode->getLeftChild());
                    currNode->getLeftChild()->setParentNode(parent);
                    currNode->setLeftChild(nullptr);
                }
                else{
                    parent->setLeftChild(currNode->getRightChild());
                    currNode->getRightChild()->setParentNode(parent);
                    currNode->setRightChild(nullptr);
                }
                currNode->setParentNode(nullptr);
                return currNode;
            }
            else if(currNode->getParentNode()->getRightChild() == currNode){
                TreeNode<T>* parent = currNode->getParentNode();
                if(currNode->getLeftChild() != nullptr){
                    parent->setRightChild(currNode->getLeftChild());
                    currNode->getLeftChild()->setParentNode(parent);
                    currNode->setLeftChild(nullptr);
                }
                else{
                    parent->setRightChild(currNode->getRightChild());
                    currNode->getRightChild()->setParentNode(parent);
                    currNode->setRightChild(nullptr);
                }
                currNode->setParentNode(nullptr);
                return currNode;
            }
        }
        else if(currNode->getLeftChild() != nullptr && currNode->getRightChild() != nullptr){//Remove node with 2 children
            TreeNode<T>* successor = currNode->getRightChild();
            while(successor->getLeftChild() != nullptr){
                successor = successor->getLeftChild();
            }
            currNode->getLeftChild()->setParentNode(successor);
            currNode->getRightChild()->setParentNode(successor);
            if(currNode->getRightChild()->getParentNode() == currNode->getRightChild() && currNode->getParentNode() == nullptr){
                root = currNode->getRightChild();
                currNode->getRightChild()->setParentNode(nullptr);
            }
            else if(currNode->getLeftChild()->getParentNode() == currNode->getRightChild() && currNode->getParentNode() == nullptr){
                root = currNode->getRightChild();
                currNode->getLeftChild()->setParentNode(nullptr);
            }
            else if (currNode->getRightChild()->getParentNode() == currNode->getRightChild() && currNode->getParentNode() != nullptr){
                currNode->getRightChild()->setParentNode(currNode->getParentNode());
                currNode->setParentNode(nullptr);
                successor->getParentNode()->setLeftChild(currNode->getRightChild());
                currNode->setParentNode(nullptr);
            }
            else if(currNode->getLeftChild()->getParentNode() == currNode->getRightChild() && currNode->getParentNode() != nullptr){
                currNode->getLeftChild()->setParentNode(currNode->getParentNode());
                currNode->setParentNode(nullptr);
                successor->getParentNode()->setLeftChild(currNode->getRightChild());
                currNode->setParentNode(nullptr);
            }

            successor->setLeftChild(currNode->getLeftChild());

            currNode->setLeftChild(nullptr);
            currNode->setRightChild(nullptr);
            return currNode;
        }
    }


    TreeNode<T>* getRoot(){
        return root;
    }

    void rebalance(){
        vector<int> values;
        traverse(values);
        int halves = values.size();
        vector<int> middles(1);
        middles[0] = values.size()/2;
        root = new TreeNode<int>(values[values.size()/2]);

        while(halves != 0){


            halves = halves/2;
            if(halves != 0) {
                middles.resize(middles.size() + 2);
            }
        }
    }
private:
    TreeNode<T>* root;
    int size =1;

    void traverseHelper(TreeNode<T>* node,vector<T> &traversalVector) const{
        if (node != NULL) {
            traverseHelper(node->getLeftChild(),traversalVector);//traverses Left side of BST until end
            traversalVector.push_back(node->getValue());//stores nodes into array
            traverseHelper(node->getRightChild(),traversalVector);//traverses Right side of BST until end
        }
    }

    void addNodeHelper(TreeNode<T>* node,TreeNode<T>* currNode){//Iterates through BST
        if(node->getValue() > currNode->getValue() && currNode->getRightChild() != NULL){
            addNodeHelper(node,currNode->getRightChild());
        }
        else if(node->getValue() <= currNode->getValue() && currNode->getLeftChild() != NULL){
            addNodeHelper(node,currNode->getLeftChild());
        }
        else if(node->getValue() > currNode->getValue() && currNode->getRightChild() == NULL){
            currNode->setRightChild(node);
            node->setParentNode(currNode);
        }
        else if(node->getValue() <= currNode->getValue() && currNode->getLeftChild() == NULL) {
            currNode->setLeftChild(node);
            node->setParentNode(currNode);
        }
    }

    void clearContentsHelper(TreeNode<T>* node,vector<TreeNode<T>*> &nodes) const{//stores all nodes of BST into vector
        if (node != NULL) {
            clearContentsHelper(node->getLeftChild(),nodes);
            nodes.push_back(node);
            clearContentsHelper(node->getRightChild(),nodes);
        }
    }

    TreeNode<T>* findHelper(int value, TreeNode<T>* currNode){//Iterates through BST to find node
        if(value > currNode->getValue() && currNode->getRightChild() != NULL){
            findHelper(value,currNode->getRightChild());
        }
        else if(value < currNode->getValue() && currNode->getLeftChild() != NULL){
            findHelper(value,currNode->getLeftChild());
        }
        else if(value > currNode->getValue() && currNode->getRightChild() == NULL || value < currNode->getValue() && currNode->getLeftChild() == NULL){
            return nullptr;
        }
        else if(value == currNode->getValue()){
            return currNode;
        }
    }
};
#endif //BSTBASE_BINARYSEARCHTREE_H
