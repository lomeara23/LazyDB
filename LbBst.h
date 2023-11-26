#ifndef LAZYBST_H
#define LAZYBST_H

#include <iostream>
using namespace std;

template<class T>
class LazyTreeNode{
    public:
        LazyTreeNode();
        LazyTreeNode(T data);
        virtual ~LazyTreeNode();

        T key;

        LazyTreeNode<T> *left;
        LazyTreeNode<T> *right;

        int leftDepth;
        int rightDepth;

        int getLeftDepth();
        int getRightDepth();
        
};

template<class T>
LazyTreeNode<T>::LazyTreeNode(){
    left = NULL;
    right = NULL;
    key = NULL;

    leftDepth = 0;
    rightDepth = 0;
}

template<class T>
LazyTreeNode<T>::LazyTreeNode(T key){
    left = NULL;
    right = NULL;
    this->key = key;

    leftDepth = 0;
    rightDepth = 0;
}

template<class T>
LazyTreeNode<T>::~LazyTreeNode(){
    left = NULL;
    right = NULL;
}

// Recursively get depth of tree from this node
template<class T>
int LazyTreeNode<T>::getLeftDepth(){
    if(left == NULL)
        return 0;
    // Return depth of left child plus one, as that is depth of current node
    return max(left->getLeftDepth(),left->getRightDepth())+1;
}

template<class T>
int LazyTreeNode<T>::getRightDepth(){
    if(right == NULL)
        return 0;
    return max(right->getLeftDepth(),right->getRightDepth())+1;
}

template<class T>
class LazyBST{
    public:
        LazyBST();
        virtual ~LazyBST();

        void insert(T value);
        bool deleteNode(T k);
        bool contains(T value);
        bool isEmpty();

        T* find(T value);

        LazyTreeNode<T>* getSuccessor(LazyTreeNode<T>* node);

        void printTree();
        void recPrint(LazyTreeNode<T>* node);

        T* getMin();
        T* getMax(); 

        LazyTreeNode<T>* getRoot();

        bool isImbalanced();
        void rebuild();

        void recInsert(LazyTreeNode<T>* node, int top, int bottom);

        private: 
        LazyTreeNode<T> *root;
        int size;

        T **m_arr;
};

template<class T>
LazyBST<T>::LazyBST(){
    root = NULL;
    size = 0;
}

template<class T>
LazyBST<T>::~LazyBST(){
    while (root != NULL){}
    {
        deleteNode(*getMin());
    }
    
}

template<class T>
void LazyBST<T>::insert(T val){
    size++;
    // If tree empty, new node is root
    if (root == NULL) {
        root = new LazyTreeNode<T>(val);
        return;
    }

    LazyTreeNode<T> *parent = root;
    LazyTreeNode<T> *current = root;

    // Search for open space, put node there
    while(current != NULL){
        parent = current;
        if(val < current->key){
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if(val < parent->key){
        parent->left = new LazyTreeNode<T>(val);
    } else {
        parent->right = new LazyTreeNode<T>(val);
    }  

    // Check for imbalance after every insert, rebuild if necessary
    if(isImbalanced()){
        cout << "Imabalance threshold reached! Rebuilding..." << endl;
        rebuild();
    }
}

template<class T>
bool LazyBST<T>::deleteNode(T k){
    if(isEmpty()){
        return false;
    }
    LazyTreeNode<T> *current = root;
    LazyTreeNode<T> *parent = root;
    bool isLeft = true;

    while(current->key != k){
        parent = current;
        if(k < current->key){
            current = current->left;
        }else{
            isLeft = false;
            current = current->right;
        }

        if(current == NULL){
            return false;
        }
    }
    // node to delete found

    // Leaf node, no children
    if(current->left == NULL && current->right == NULL){
        if(current == root){
            root = NULL;
        } else if(isLeft){
            parent->left = NULL;
        } else{
            parent->right = NULL;
        }
    }

    // Node has left child
    else if(current->right == NULL){
        if(current == root){
            root = current->left;
        } else if(isLeft){
            parent->left = current->left;
        } else{
            parent->right = current->left;
        }

    }

    // Node has right child
    else if(current->left == NULL){
        if(current == root){
            root = current->right;
        } else if(isLeft){
            parent->left = current->right;
        } else{
            parent->right = current->right;
        }
    }

    // Node has two children
    else{
        LazyTreeNode<T> *successor = getSuccessor(current);
        if(current == root){
            root = successor;
        }
        else if(isLeft){
            parent->left = successor;
        }
        else{
            parent->right = successor;
        }
        successor->left = current->left;
        current->left = NULL;
        current->right = NULL;
    }
    size--;
}

template<class T>
bool LazyBST<T>::contains(T val){
    if(isEmpty()){
        return false;
    }
    LazyTreeNode<T> *current = root;
    while(current != NULL){
        if(current->key == val)
            return true;
        if(val < current->key){
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return false;
}

// Contains but returns node key instead of bool
template<class T>
T* LazyBST<T>::find(T val){
    if(isEmpty()){
        return NULL;
    }
    LazyTreeNode<T> *current = root;
    while(current != NULL){
        if(current->key == val)
            return &current->key;
        if(val < current->key){
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return NULL;
}

template<class T>
bool LazyBST<T>::isEmpty(){
    return (root == NULL);
}

template<class T>
LazyTreeNode<T>* LazyBST<T>::getSuccessor(LazyTreeNode<T>* node){
    LazyTreeNode<T> *sp = node;
    LazyTreeNode<T> *successor = node;
    LazyTreeNode<T> *current = node->right;
    while(current != NULL){
        sp = successor;
        successor = current;
        current = current->left;
    }
    if(successor != current->right){
        sp->left = successor->right;
        successor->right = node->right;
    }
    return successor;
}

// Recursively print from the root
template<class T>
void LazyBST<T>::printTree(){
    recPrint(root);
}

template<class T>
void LazyBST<T>::recPrint(LazyTreeNode<T>* node){
    // in-order traversal

    if(node->left != NULL){
        recPrint(node->left);
    }

    cout << node->key << endl;

    if(node->right != NULL){
        recPrint(node->right);
    }
}

// Traverse left as far as possible
template<class T>
T* LazyBST<T>::getMin(){
    LazyTreeNode<T> *current = root;
    while(current->left != NULL){
        current = current->left;
    }
    return &current->key;
}

// Traverse right as far as possible
template<class T>
T* LazyBST<T>::getMax(){
    LazyTreeNode<T> *current = root;
    while(current->right != NULL){
        current = current->right;
    }
    return &current->key;
}

template<class T>
LazyTreeNode<T>* LazyBST<T>::getRoot(){
    return root;
}

template<class T>
bool LazyBST<T>::isImbalanced(){
// Return whether or not balance factor is greater than 1.5
    if(root->getLeftDepth() == 0 || root->getRightDepth() == 0)
        return false;
    else
        return ((((root->getLeftDepth())/(double)(root->getRightDepth()))>1.5) || (((root->getRightDepth())/(double)(root->getLeftDepth()))>1.5));
}

template<class T>
void LazyBST<T>::rebuild(){
    cout << "Pre-rebuild" << endl;
    printTree();    

    int arrSize = size;
    m_arr = new T*[arrSize];

    for(int i = 0 ; i < arrSize ; i++){
        m_arr[i] = getMin();
        deleteNode(*getMin());
    }
    if(arrSize % 2 == 0)
        root = new LazyTreeNode<T>(*m_arr[(arrSize/2)-1]);
    else
        root = new LazyTreeNode<T>(*m_arr[arrSize/2]);
    
    for(int i = 0 ; i < arrSize ; i++){
        cout << "At arr pos " << i << " exists " << *m_arr[i] << endl;
    }

    recInsert(root, 0, arrSize-1);

    cout << "Post-rebuild" << endl;
    printTree();

    delete[] m_arr;
    size = arrSize;

}

// recursively builds a new tree using rules provided in MP5
template<class T>
void LazyBST<T>::recInsert(LazyTreeNode<T>* node, int bottom, int top){
    if(((((bottom)+(top))/2))-bottom > 0)
        node->left = new LazyTreeNode<T>(*m_arr[((bottom)+((((bottom)+(top))/2)-1))/2]);
    
    if((top-((((bottom)+(top))/2))))
        node->right = new LazyTreeNode<T>(*m_arr[(((((bottom)+(top))/2)+1)+(top))/2]);
        
    if(((((bottom)+(top))/2))-bottom > 1)
        recInsert(node->left,bottom,((((bottom)+(top))/2)-1));
    if(top-((((bottom)+(top))/2)) > 1)
        recInsert(node->right,((((bottom)+(top))/2)+1),top);
}

#endif