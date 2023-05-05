// priorityqueue.h
//
// This is an implementation of a priority queue using
// a  custom binary search tree. The nodes are organized
// based on their priority. Nodes with the same priority
// are allowed and are connected as a linked list.
#pragma once

#include <iostream>
#include <set>
#include <sstream>
#include <string>

using namespace std;

template <typename T>
class priorityqueue {
 private:
  struct NODE {
    int priority;  // used to build BST
    T value;       // stored data for the p-queue
    bool dup;      // marked true when there are duplicate priorities
    NODE* parent;  // links back to parent
    NODE* link;    // links to linked list of NODES with duplicate priorities
    NODE* left;    // links to left child
    NODE* right;   // links to right child
  };
  NODE* root;  // pointer to root node of the BST
  int size;    // # of elements in the pqueue
  NODE* curr;  // pointer to next item in pqueue (see begin and next)

  // Helper function to walk through the tree and add the priority
  // and value of each node to the output
  void _toString(NODE* node, stringstream& output) {
    if (node == nullptr) {
      return;
    } else {
      _toString(node->left, output);
      output << node->priority << " value: " << node->value << endl;
      if (node->dup) {
        _toStringLink(node->link, output);
      }
      _toString(node->right, output);
    }
  }
  // Helper function to walk through the linked list and add the priority
  // and value of each node to the output
  void _toStringLink(NODE* node, stringstream& output) {
    if (node == nullptr) {
      return;
    } else {
      output << node->priority << " value: " << node->value << endl;
      _toStringLink(node->link, output);
    }
  }

  // Helper function to delete nodes in tree in a post-order traversal
  void _clear(NODE* node) {
    if (node == nullptr) {
      return;
    } else {
      _clear(node->right);
      _clear(node->left);
      if (node->dup) {
        NODE* next_node = nullptr;
        while (node->link != nullptr) {
          next_node = node->link;
          delete node;
          node = next_node;
        }
      }
      delete node;
    }
  }

  // Helper function to find the smallest (further left) node
  void _goLeft(NODE* node, NODE*& cur) {
    if (node == nullptr) {
      return;
    } else {
      cur = node;
      _goLeft(node->left, cur);
    }
  }

  // Helper function to copy each node in a pre-order traversal
  void _copy(NODE*& this_node, NODE* other_node) {
    if (other_node == nullptr) {
      return;
    } else {
      NODE* n = new NODE();
      n->priority = other_node->priority;
      n->value = other_node->value;
      n->dup = other_node->dup;
      n->parent = nullptr;
      n->link = nullptr;
      n->left = nullptr;
      n->right = nullptr;
      this_node = n;
      // Copy linked list
      if (n->dup) {
        NODE* previous = nullptr;
        NODE* cur = other_node->link;
        while (cur != nullptr) {
          previous = n;
          n = new NODE();
          n->priority = cur->priority;
          n->value = cur->value;
          n->dup = cur->dup;
          n->parent = previous;
          n->link = nullptr;
          previous->link = n;
          cur = cur->link;
        }
      }
      // Copy left sub-tree
      _copy(this_node->left, other_node->left);
      // Update parent of left node
      if (this_node->left != nullptr) {
        this_node->left->parent = this_node;
      }
      // Copy right sub-tree
      _copy(this_node->right, other_node->right);
      // Update parent of left node
      if (this_node->right != nullptr) {
        this_node->right->parent = this_node;
      }
    }
  }

  // Helper function to find the next node
  bool _next(T& value, int& priority) {
    // Return false if :
    // begin() was never called
    // empty priority queue
    if (curr == nullptr) {
      return false;
    };

    value = curr->value;
    priority = curr->priority;

    if (curr->dup) {
      if (curr->link != nullptr) {
        curr = curr->link;
        return true;
      } else {
        while (curr->priority == curr->parent->priority) {
          curr = curr->parent;
          if (curr->parent == nullptr) {  // root
            break;
          }
        }
        return _next_tree();
      }
    } else {
      return _next_tree();
    }
  }
  // Helper function to go up the tree and find the next node
  bool _next_tree() {
    if (curr->right != nullptr) {
      _goLeft(curr->right, curr);
    } else if (curr->parent == nullptr) {
      return false;
    } else {
      while (curr->parent->left != curr) {
        curr = curr->parent;
        if (curr->parent == nullptr) {
          return false;
        }
      }
      curr = curr->parent;
    }
    return true;
  }

  // Helper function for dequeue
  void _dequeue(NODE* cur) {
    if (cur->dup) {
      NODE* succ = cur->link;
      if (succ->link == nullptr) {
        succ->dup = false;
      }
      // Check right
      if (cur->right != nullptr) {
        succ->right = cur->right;
        cur->right->parent = succ;
      }
      // Check Parent
      if (cur == root) {  // Node is root
        this->root = succ;
        succ->parent = nullptr;
      } else {
        cur->parent->left = succ;
        succ->parent = cur->parent;
      }
      delete cur;
    } else if ((cur->left == nullptr) &&
               (cur->right == nullptr)) {  // Remove leaf
      if (cur == root) {                   // Node is root
        this->root = nullptr;
      } else {
        cur->parent->left = nullptr;
      }
      delete cur;
    } else {              // Remove node with only right child
      if (cur == root) {  // Node is root
        this->root = cur->right;
        cur->right->parent = nullptr;
      } else {  // if (cur -> parent -> left == cur) {
        cur->parent->left = cur->right;
        cur->right->parent = cur->parent;
      }
      delete cur;
    }
  }

  // Helper function to compare all nodes from two diff trees
  bool _equal(NODE* this_node, NODE* other_node) const {
    if ((this_node == nullptr) && (other_node == nullptr)) {
      return true;
    } else if (this_node == nullptr) {
      return false;
    } else if (other_node == nullptr) {
      return false;
    } else {
      if ((this_node->dup == true) && (other_node->dup == true)) {
        if ((_equal(this_node->link, other_node->link)) &&
            (_equal(this_node->left, other_node->left)) &&
            (this_node->value == other_node->value) &&
            (this_node->priority == other_node->priority) &&
            (_equal(this_node->right, other_node->right))) {
          return true;
        }
      } else if ((this_node->dup == false) && (other_node->dup == false)) {
        if ((_equal(this_node->left, other_node->left)) &&
            (this_node->value == other_node->value) &&
            (this_node->priority == other_node->priority) &&
            (_equal(this_node->right, other_node->right))) {
          return true;
        }
      }
      return false;
    }
  }

 public:
  //
  // default constructor:
  //
  // Creates an empty priority queue.
  // O(1)
  //
  priorityqueue() {
    root = nullptr;
    size = 0;
    curr = nullptr;
  }

  //
  // operator=
  //
  // Clears "this" tree and then makes a copy of the "other" tree.
  // Sets all member variables appropriately.
  // O(n), where n is total number of nodes in custom BST
  //
  priorityqueue& operator=(const priorityqueue& other) {
    // special case: are we assigning to ourself?
    //
    if (this == &other) {
      return *this;
    }
    this->clear();
    this->size = other.size;

    _copy(this->root, other.root);

    return *this;
  }

  //
  // clear:
  //
  // Frees the memory associated with the priority queue but is public.
  // O(n), where n is total number of nodes in custom BST
  //
  void clear() {
    _clear(root);
    root = nullptr;
    curr = nullptr;
    size = 0;
  }

  //
  // destructor:
  //
  // Frees the memory associated with the priority queue.
  // O(n), where n is total number of nodes in custom BST
  //
  ~priorityqueue() { clear(); }

  //
  // enqueue:
  //
  // Inserts the value into the custom BST in the correct location based on
  // priority.
  // O(logn + m), where n is number of unique nodes in tree and m is number of
  // duplicate priorities
  //
  void enqueue(T value, int priority) {
    NODE* prev = nullptr;
    NODE* cur = root;
    bool found = false;

    // 1. Search for priority.
    // If duplicate exists, link nodes
    while (cur != nullptr) {
      if (priority == cur->priority) {  // duplicate
        found = true;
        break;
      }
      if (priority < cur->priority) {  // go left
        prev = cur;
        cur = cur->left;
      } else {  // go right
        prev = cur;
        cur = cur->right;
      }
    }

    // 2. Insert new node
    NODE* n = new NODE();
    n->priority = priority;
    n->value = value;
    n->left = nullptr;
    n->right = nullptr;

    if (found == false) {
      n->dup = false;
      n->parent = prev;
      n->link = nullptr;
      if (prev == nullptr) {
        root = n;
      } else if (priority < prev->priority) {
        prev->left = n;
      } else {
        prev->right = n;
      }
    } else {
      // Find last node in linked list
      while (cur->link != nullptr) {
        cur = cur->link;
      }
      n->dup = true;
      n->parent = cur;
      n->link = nullptr;
      cur->link = n;
      cur->dup = true;
    }
    size++;
  }
  //
  // dequeue:
  //
  // returns the value of the next element in the priority queue and removes
  // the element from the priority queue.
  // O(logn + m), where n is number of unique nodes in tree and m is number of
  // duplicate priorities
  //
  T dequeue() {
    NODE* cur = nullptr;
    _goLeft(root, cur);
    if (cur == nullptr) {
      return T{};
    }
    T valueOut = cur->value;
    _dequeue(cur);
    size--;
    return valueOut;
  }

  //
  // Size:
  //
  // Returns the # of elements in the priority queue, 0 if empty.
  // O(1)
  //
  int Size() { return size; }

  //
  // begin
  //
  // Resets internal state for an inorder traversal.  After the
  // call to begin(), the internal state denotes the first inorder
  // node; this ensure that first call to next() function returns
  // the first inorder node value.
  //
  // O(logn), where n is number of unique nodes in tree
  //
  // Example usage:
  //    pq.begin();
  //    while (tree.next(value, priority)) {
  //      cout << priority << " value: " << value << endl;
  //    }
  //    cout << priority << " value: " << value << endl;
  void begin() {
    curr = nullptr;
    _goLeft(root, curr);
  }

  //
  // next
  //
  // Uses the internal state to return the next inorder priority, and
  // then advances the internal state in anticipation of future
  // calls.  If a value/priority are in fact returned (via the reference
  // parameter), true is also returned.
  //
  // False is returned when the internal state has reached null,
  // meaning no more values/priorities are available.  This is the end of the
  // inorder traversal.
  //
  // O(?) - hard to say.  But approximately O(logn + m).  Definitely not O(n).
  //
  // Example usage:
  //    pq.begin();
  //    while (tree.next(value, priority)) {
  //      cout << priority << " value: " << value << endl;
  //    }
  //    cout << priority << " value: " << value << endl;
  //
  bool next(T& value, int& priority) { return _next(value, priority); }

  //
  // toString:
  //
  // Returns a string of the entire priority queue, in order.  Format:
  // "1 value: Ben
  //  2 value: Jen
  //  2 value: Sven
  //  3 value: Gwen"
  //
  string toString() {
    stringstream output;
    _toString(root, output);
    return output.str();
  }

  //
  // peek:
  //
  // returns the value of the next element in the priority queue but does not
  // remove the item from the priority queue.
  // O(logn + m), where n is number of unique nodes in tree and m is number of
  // duplicate priorities
  //
  T peek() {
    T valueOut;
    NODE* cur = nullptr;
    _goLeft(root, cur);

    if (cur == nullptr) {
      return T{};
    }
    return cur->value;
  }

  //
  // ==operator
  //
  // Returns true if this priority queue as the priority queue passed in as
  // other.  Otherwise returns false.
  // O(n), where n is total number of nodes in custom BST
  //
  bool operator==(const priorityqueue& other) const {
    if (this->size != other.size) {
      return false;
    }
    return _equal(root, other.root);
  }

  //
  // getRoot - Do not edit/change!
  //
  // Used for testing the BST.
  // return the root node for testing.
  //
  void* getRoot() { return root; }
};