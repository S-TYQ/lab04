// intbst.cpp
// Implements class IntBST
// YOUR NAME(S), DATE

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() : root(0) { }

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if (n) {
	clear(n->left);
	clear(n->right);
	delete n;
    }
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    // handle special case of empty tree first
    if (root== nullptr) {
	root = new Node(value);
	return true;
    }
    // otherwise use recursive helper
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if (value == n->info)
	return false;
    if (value < n->info) {
        if (n->left)
            return insert(value, n->left);
        else {
            n->left = new Node(value);
            n->left->parent = n;
            return true;
        }
    }
    else {
        if (n->right)
            return insert(value, n->right);
        else {
            n->right = new Node(value);
            n->right->parent = n;
            return true;
        }
    }
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if (n) {
	cout << n->info << " ";
	printPreOrder(n->left);
	printPreOrder(n->right);
    }
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
    if (n) {
        printInOrder(n->left);
        cout << n->info << " ";
        printInOrder(n->right);
    }
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
    if (n) {
        printPostOrder(n->left);
        printPostOrder(n->right);
        cout << n->info << " ";
    }

}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    int total = 0;
    if (n->left) {
        total += sum(n->left);

    }
    if (n->right){
        total += sum(n->right);
    }

    return total+ n->info;
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
    int num = 0 ;
    if (n->left){
        num+= count(n->left);
    }
    if (n->right){
        num+= count(n->right);
    }
    return num+=1;

}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const {
    if (n->left) {
        if (value < n->info) {
            return getNodeFor(value, n->left);
        }
    }
    if (n->right) {
        if (value > n->info) {
            return getNodeFor(value, n->right);
        }
    }
    if (value == n->info)
        return n;
    return nullptr;

}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    if (root) {
        if (getNodeFor(value, root) != nullptr) {
            return true;
        }
        return false;
    }
    return false;


}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    Node* temp = getNodeFor(value,root);
    if (temp) {
        if (temp->left) {
            return mostright(temp->left);
        } else
            return firstsmallerpartent(temp, value);
    }
    return nullptr;
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    Node* temp = getPredecessorNode(value);
    if (temp!= nullptr){
        return temp->info;
    }
    return 0;
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    Node* temp = getNodeFor(value,root);
    if (temp) {
        if (temp->right) {
            return mostleft(temp->right);
        } else
            return firstgreaterparent(temp, value);
    }
    return nullptr;

}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
   Node * temp = getSuccessorNode(value);
   if (temp)
       return temp->info;
   else
       return 0;

}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
    if (contains(value)){
        Node* here = getNodeFor(value, root);
        if (here->left!=nullptr) {
            Node *temp = mostright(here->left);
            here->info = temp->info;
            temp->parent->right = temp->left;
            delete temp;
        }
        else
        {
            if (here->right) {
                Node *temp = here->parent;
                if (temp->right == here)
                    temp->right = here->right;
                else
                    temp->left = here->right;
                delete here;
            }
            else {
                Node *temp = here->parent;
                if (temp->right == here)
                    temp->right = nullptr;
                else
                    temp->left = nullptr;
                delete here;
            }

        }
    }
    else
        return false;
}

IntBST::Node *IntBST::mostleft(IntBST::Node *n) const{
    if (n->left) {
        return mostleft(n->left);
    } else {
        return n;
    }
}

IntBST::Node *IntBST::mostright(IntBST::Node *n) const{
    if (n->right) {
        return mostright(n->right);
    } else {
        return n;
    }
}

IntBST::Node *IntBST::firstgreaterparent(IntBST::Node *n, int value) const{
    if (n->parent){
        Node * temp = n->parent;
        if (temp->info > value)
            return temp;
        else
        {
            return firstgreaterparent(temp, value);
        }

    }
    return nullptr;
}

IntBST::Node *IntBST::firstsmallerpartent(IntBST::Node *n, int value) const {
    if (n->parent){
        Node * temp = n->parent;
        if (temp->info < value)
            return temp;
        else
        {
            return firstsmallerpartent(temp, value);
        }

    }
    return nullptr;
}
