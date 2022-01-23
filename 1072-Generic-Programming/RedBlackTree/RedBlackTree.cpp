#include <iostream>
#include <queue>
using namespace std;

enum Color{red, black, double_black};

bool Delimiter = false;
void CheckDelimiter(){
    if(Delimiter)cout << '\n';
    Delimiter = true;
}

class Node{
public:
    int val;
    int color; // 0: red 1: black 
    Node *leftChild, *rightChild, *parent;
    Node(): color(0){};
    Node(int _val, int _color = 0): val(_val), color(_color), leftChild(nullptr), rightChild(nullptr), parent(nullptr){}
};

class RedBlackTree{
private:
    int getColor(Node *node);
    void setColor(Node *node, int color);

    void LeftRotate(Node *node);
    void RightRotate(Node *node);

    bool Find(Node *root, Node *node);
    Node* minElement(Node *node);
    Node* InsertNode(Node *root, Node *node);
    void fixInsertNode(Node *node);

    Node* DeleteNode(Node *root, int val);
    void fixDeleteNode(Node *node);

    void DepthFirstSearch(Node *node);
public:
    RedBlackTree();

    void Insert(int val);
    void Delete(int val);
    void BepthFirstSearch();
    void DepthFirstSearch();
private:
    Node *root;
};

RedBlackTree::RedBlackTree(){
    root = nullptr;
}

int RedBlackTree::getColor(Node *node){
    if(node == nullptr)
        return black;
    return node->color; 
}

void RedBlackTree::setColor(Node *node, int color){
    if(node == nullptr)
        return;
    node->color = color;
}

void RedBlackTree::LeftRotate(Node *node){
    Node *rightChlid = node->rightChild; 

    // update node->rightChild
    node->rightChild = rightChlid->leftChild;
    if(node->rightChild != nullptr)
        node->rightChild->parent = node;

    // update rightChild->parent
    rightChlid->parent = node->parent;
    if(node->parent == nullptr){
        root = rightChlid;
    }else if(node == node->parent->leftChild){
        node->parent->leftChild = rightChlid;
    }else{
        node->parent->rightChild = rightChlid;
    }

    rightChlid->leftChild = node;
    node->parent = rightChlid;
}

void RedBlackTree::RightRotate(Node *node){
    Node *leftChlid = node->leftChild;

    // update node->leftChild
    node->leftChild = leftChlid->rightChild;
    if(node->leftChild != nullptr)
        node->leftChild->parent = node;

    // update leftChild->parent
    leftChlid->parent = node->parent;
    if(node->parent == nullptr){
        root = leftChlid;
    }else if(node == node->parent->leftChild){
        node->parent->leftChild = leftChlid;
    }else{
        node->parent->rightChild = leftChlid;
    }

    leftChlid->rightChild = node;
    node->parent = leftChlid;
}

Node* RedBlackTree::minElement(Node *node){
    Node *tmp = node;
    while(tmp->leftChild != nullptr)
        tmp = tmp->leftChild;
    return tmp;
}

bool RedBlackTree::Find(Node *root, Node *node){
    if(root == nullptr)
        return false;
    if(root->val == node->val)
        return true;
    if(root->val > node->val)
        return Find(root->leftChild, node);
    return Find(root->rightChild, node);
}

void RedBlackTree::Insert(int val){
    Node *node = new Node(val, red);
    if(Find(root, node) == true){
        CheckDelimiter();
        cout << val << " has already been stored\n";
        return;
    }
    root = InsertNode(root, node);
    // cout << "finish Insert\n";
    fixInsertNode(node);
    // cout << "finish fix Insert\n";
}

Node* RedBlackTree::InsertNode(Node *root, Node *node){
    if(root == nullptr)return node;
    if(root->val > node->val){
        root->leftChild = InsertNode(root->leftChild, node);
        root->leftChild->parent = root;
    }else{
        root->rightChild = InsertNode(root->rightChild, node);
        root->rightChild->parent = root;
    }
    return root;
}

void RedBlackTree::fixInsertNode(Node *node){
    Node *parent = nullptr, *grandparent = nullptr;
    bool reviseCase = false;
    while(node != root && getColor(node) == red && getColor(node->parent) == red){
        if(!reviseCase)CheckDelimiter();
        reviseCase = true;
        parent = node->parent;
        grandparent = parent->parent;
        if(parent == grandparent->leftChild){
            Node *uncle = grandparent->rightChild;
            if(getColor(uncle) == red){
                setColor(uncle, black);
                setColor(parent, black);
                setColor(grandparent, red);
                node = grandparent;
                cout << "Insert Case 2 Recolor\n";
            }else{
                if(node == parent->rightChild){
                    LeftRotate(parent);
                    node = parent;
                    parent = node->parent;
                    cout << "Insert Case 1 LR Adjustment\n";
                }else{
                    cout << "Insert Case 1 LL Adjustment\n";
                }
                RightRotate(grandparent);
                swap(parent->color, grandparent->color);
                node = parent;
            }
        }else{
            Node *uncle = grandparent->leftChild;
            if(getColor(uncle) == red){
                setColor(uncle, black);
                setColor(parent, black);
                setColor(grandparent, red);
                node = grandparent;
                cout << "Insert Case 2 Recolor\n";
            }else{
                if(node == parent->leftChild){
                    RightRotate(parent);
                    node = parent;
                    parent = node->parent;
                    cout << "Insert Case 1 RL Adjustment\n";
                }else{
                    cout << "Insert Case 1 RR Adjustment\n";
                }
                LeftRotate(grandparent);
                swap(parent->color, grandparent->color);
                node = parent;
            }
        }
        setColor(root, black);
    }
    if(reviseCase)BepthFirstSearch();
    setColor(root, black);
}

void RedBlackTree::Delete(int val){
    Node* node = DeleteNode(root, val);
    // cout << "finish find delete\n";
    // cout << node->parent->val << '\n';
    fixDeleteNode(node);
    // cout << "finish delete fix\n";
}

Node* RedBlackTree::DeleteNode(Node *root, int val){
    if(root == nullptr)
        return root;
    // cout << root->val << '\n';
    if(root->val > val)
        return DeleteNode(root->leftChild, val);
    if(root->val < val)
        return DeleteNode(root->rightChild, val);
    if(root->leftChild == nullptr || root->rightChild == nullptr)
        return root;
    
    Node *predecessor = minElement(root->rightChild);
    // cout << root->val << ' ' << predecessor->val << '\n';
    root->val = predecessor->val;
    return DeleteNode(root->rightChild, predecessor->val);
}

void RedBlackTree::fixDeleteNode(Node *node){
    if(node == nullptr)
        return;
    if(node == root){
        root = nullptr;
        return;
    }
    if(getColor(node) == red || getColor(node->leftChild) == red || getColor(node->rightChild) == red){
        Node *child = ((node->leftChild != nullptr) ? (node->leftChild) : (node->rightChild));

        // connect node's child and parent
        if(node == node->parent->leftChild){
            node->parent->leftChild = child;
        }else{
            node->parent->rightChild = child;
        }
        if(child != nullptr)
            child->parent = node->parent;
        setColor(child, black);
        delete(node);
        return;
    }else{
        Node *parent = nullptr, *sibling = nullptr;
        Node *ptr = node;
        setColor(ptr, double_black);
        CheckDelimiter();
        while(ptr != root && getColor(ptr) == double_black){
            parent = ptr->parent;
            if(ptr == parent->leftChild){
                sibling = parent->rightChild;
                if(getColor(sibling) == red){
                    cout << "Remove Case 3 RR Adjustment\n";
                    setColor(sibling, black);
                    setColor(parent, red);
                    LeftRotate(parent);
                }else{
                    if(getColor(sibling->leftChild) == black && getColor(sibling->rightChild) == black){
                        cout << "Remove Case 2 Recolor\n";
                        setColor(sibling, red);
                        if(getColor(parent) == red)
                            setColor(parent, black);
                        else
                            setColor(parent,double_black);
                        ptr = parent;
                    }else{
                        if(getColor(sibling->rightChild) == black){
                            cout << "Remove Case 1 RL Adjustment\n";
                            setColor(sibling->leftChild, black);
                            setColor(sibling, red);
                            RightRotate(sibling);
                            sibling = parent->rightChild;
                        }else{
                            cout << "Remove Case 1 RR Adjustment\n";
                        }
                        setColor(sibling, getColor(parent));
                        setColor(parent, black);
                        setColor(sibling->rightChild, black);
                        LeftRotate(parent);
                        break;
                    }
                }
            }else{
                sibling = parent->leftChild;
                if(getColor(sibling) == red){
                    cout << "Remove Case 3 LL Adjustment\n";
                    setColor(sibling, black);
                    setColor(parent, red);
                    RightRotate(parent);
                }else{
                    if(getColor(sibling->leftChild) == black && getColor(sibling->rightChild) == black){
                        cout << "Remove Case 2 Recolor\n";
                        setColor(sibling, red);
                        if(getColor(parent) == red)
                            setColor(parent, black);
                        else
                            setColor(parent,double_black);
                        ptr = parent;
                    }else{
                        if(getColor(sibling->leftChild) == black){
                            cout << "Remove Case 1 LR Adjustment\n";
                            setColor(sibling->rightChild, black);
                            setColor(sibling, red);
                            LeftRotate(sibling);
                            sibling = parent->leftChild;
                        }else{
                            cout << "Remove Case 1 LL Adjustment\n";
                        }
                        setColor(sibling, getColor(parent));
                        setColor(parent, black);
                        setColor(sibling->leftChild, black);
                        RightRotate(parent);
                        break;
                    }
                }
            }
        }
        if(node == node->parent->leftChild)
            node->parent->leftChild = nullptr;
        else
            node->parent->rightChild = nullptr;
        delete(node);
        setColor(root, black);
        BepthFirstSearch();
    }
}

void RedBlackTree::BepthFirstSearch(){
    int cur_depth = 0;
    bool bfsDelimiter = false;
    queue<pair<Node*,int>>q;
    q.push({root, cur_depth});
    while(!q.empty()){
        pair<Node*,int> k = q.front(); q.pop();
        if(k.second != cur_depth){
            cout << '\n';
            ++cur_depth;
            bfsDelimiter = false;
        }
        if(bfsDelimiter)cout << ' ';
        bfsDelimiter = true;
        cout << k.first->val;
        if(k.first->color == red)cout << 'R';
        else cout << 'B';
        if(k.first->leftChild != nullptr){
            q.push({k.first->leftChild, k.second + 1});
        }
        if(k.first->rightChild != nullptr){
            q.push({k.first->rightChild, k.second + 1});
        }
    }
    cout << '\n';
}

void RedBlackTree::DepthFirstSearch(){
    DepthFirstSearch(root);
    cout << '\n';
}

void RedBlackTree::DepthFirstSearch(Node *node){
    if(node == nullptr){
        cout << "()";
        return;
    }
    cout << node->val;
    if(node->color == red)cout << 'R';
    else cout << 'B';
    cout << '(';
    DepthFirstSearch(node->leftChild);
    DepthFirstSearch(node->rightChild);
    cout << ')';
}

int main(){
    int t;
    char ch;
    RedBlackTree rbt;
    while(cin >> ch){
        if(ch == 'Q')break;
        if(ch == 'P'){
            CheckDelimiter();
            rbt.BepthFirstSearch();
            continue;
        }
        cin >> t;
        // cout << ch << ' ' << t << '\n';
        if(ch == 'I'){
            rbt.Insert(t);
        }else if(ch == 'D'){
            rbt.Delete(t);
        }
    }
}