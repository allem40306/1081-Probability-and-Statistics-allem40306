#include <iostream>
using namespace std;

class Node{
public:
    int val;
    int color; // 0: red 1: black 
    Node *LeftChild, *RightChild, *Parent;
    Node(): color(0){};
    Node(int _val, int _color = 0): val(_val), color(_color), LeftChild(nullptr), RightChild(nullptr), Parent(nullptr){}
    // void SetColor
};

class RedBlackTree{
public:
    RedBlackTree():root(nullptr){}
    void Insert(int val);
    Node* InsertNode(Node *root, Node *node);
    void fixInsertNode(Node *node);
private:
    Node *root;
};

void RedBlackTree::Insert(int val){
    Node *node = new Node(val, 0);
    root = InsertNode(root, node);
    fixInsertNode(node);
}

Node* RedBlackTree::InsertNode(Node *root, Node *node){
    if(root == nullptr)return node;
    if(root->val > node->val){
        root->LeftChild = InsertNode(root->LeftChild, node);
        root->LeftChild->Parent = root;
    }else{
        root->RightChild = InsertNode(root->RightChild, node);
        root->RightChild->Parent = root;
    }
    return root;
}

void RedBlackTree::fixInsertNode(Node *node){
    Node *parent = nullptr, *grandparent = nullptr;
}

int main(){

}