// C++ program for B-Tree insertion 
// For simplicity, assume order m = 2 * t
#include<iostream> 
using namespace std; 

//forward declaration
template <class keyType>
class BTree; 
  
// A BTree node 
template <class keyType>
class Node 
{ 
private:
    keyType *keys;     // An array of keys 
    int t;             // m = 2 * t
    Node<keyType> **C; // An array of child pointers 
    int nKeys;         // Current number of keys 
    bool isLeaf;       // Is true when node is leaf. Otherwise false 
public: 
    Node(int _t, bool _isLeaf);   // Constructor 
  
    // Inserting a new key in the subtree rooted with 
    // this node. The node must be non-full when this 
    // function is called 
    void insertNonFull(keyType k); 
  
    // Spliting the child y of this node. i is index of y in 
    // child array C[].  The Child y must be full when this function is called 
    void splitChild(int i, Node<keyType> *y); 
  
    // Traversing all nodes in a subtree rooted with this node 
    void traverse(); 
  
    // A function to search a key in subtree rooted with this node. 
    Node *search(keyType k);   // returns NULL if k is not present. 
    
     

 
// Make BTree friend of this so that we can access private members of this 
// class in BTree functions 
   friend class BTree<keyType>; 
}; 
  
// A BTree 
template <class keyType>
class BTree 
{ 
private:
    Node<keyType> *root; // Pointer to root node 
    int t;               // Minimum degree 
public: 
    // Constructor (Initializes tree as empty) 
    BTree(int t0 ) 
    {  root = NULL;  t = t0; } 
  
    // function to traverse the tree 
    void traverse() 
    {  if (root != NULL) root->traverse(); } 
  
    // function to search a key in this tree 
    //Node<int>* search(keyType k) 
    Node<keyType>* search(keyType k) 
    {  return (root == NULL)? NULL : root->search(k); } 
  
    // The main function that inserts a new key in this B-Tree 
    //void insert(keyType k); 
    void insert(keyType k); 
}; 
  
// Constructor for Node class 
template<class keyType>
Node<keyType>::Node(int t0, bool isLeaf0) 
{ 
    // Copy the given minimum degree and leaf property 
    t = t0; 
    isLeaf = isLeaf0; 
  
    // Allocate memory for maximum number of possible keys 
    // and child pointers 
    keys = new keyType[2*t-1]; 
    C = new Node<keyType> *[2*t]; 
  
    // Initialize the number of keys as 0 
    nKeys = 0; 
} 
  
// Traverse all nodes in a subtree rooted at this node 
template<class keyType>
void Node<keyType>::traverse() 
{ 
    // Depth-first traversal
    // There are nKeys keys and nKeys+1 children, traverse through nKeys keys 
    // and first nKeys children 
    for (int i = 0; i < nKeys; i++) 
    { 
        // If this is not leaf, then before printing key[i], 
        // traverse the subtree rooted at child C[i]. 
        if (isLeaf == false) 
            C[i]->traverse(); 
        cout << " " << keys[i]; 
    } 
  
    // Print the subtree rooted with last child 
    if (isLeaf == false) 
        C[nKeys]->traverse(); 
} 
  
// Search key k in subtree rooted with this node 
template<class keyType>
Node<keyType> *Node<keyType>::search(keyType k) 
{ 
    // Find the first key >=  k 
    int i = 0; 
    while (i < nKeys && k > keys[i]) 
        i++; 
  
    // If the found key is equal to k, return this node 
    if ( i < nKeys )    // added by Tong
      if (keys[i] == k) 
        return this; 
  
    // If key is not found here and this is a Leaf node 
    if (isLeaf == true) 
        return NULL; 
  
    // Go to the appropriate child 
    return C[i]->search(k); 
} 
  
// The main function that inserts a new key in this B-Tree 
template <class keyType>
void BTree<keyType>::insert( keyType k) 
{ 
    // If tree is empty 
    if (root == NULL) 
    { 
        // Allocate memory for root 
        root = new Node<keyType>(t, true); 
        root->keys[0] = k;  // Insert key 
        root->nKeys = 1;  // Update number of keys in root 
    } 
    else // If tree is not empty 
    { 
        // If root is full, then tree grows in height 
        if (root->nKeys == 2*t-1) 
        { 
            // Allocate memory for new root 
            Node<keyType> *s = new Node<keyType>(t, false); 
  
            // Make old root as child of new root 
            s->C[0] = root; 
  
            // Split the old root and move 1 key to the new root 
            s->splitChild(0, root); 
  
            // New root has two children now.  Decide which of the 
            // two children is going to have new key 
            int i = 0; 
            if (s->keys[0] < k) 
                i++; 
            s->C[i]->insertNonFull(k); 
  
            // Change root 
            root = s; 
        } 
        else  // If root is not full, call insertNonFull for root 
            root->insertNonFull(k); 
    } 
} 
  
// A utility function to insert a new key in this node 
// The assumption is, the node must be non-full when this 
// function is called 
template <class keyType>
void Node<keyType>::insertNonFull(keyType k) 
{ 
    // Initialize index as index of rightmost element 
    int i = nKeys-1; 
  
    // If this is a Leaf node 
    if (isLeaf == true) 
    { 
        // The following loop does two things 
        // a) Finds the location of new key to be inserted 
        // b) Moves all greater keys to one place ahead 
        while (i >= 0 && keys[i] > k) 
        { 
            keys[i+1] = keys[i]; 
            i--; 
        } 
  
        // Insert the new key at found location 
        keys[i+1] = k; 
        nKeys++; 
    } 
    else // If this node is not Leaf 
    { 
        // Find the child which is going to have the new key 
        while (i >= 0 && keys[i] > k) 
            i--; 
  
        // See if the found child is full 
        if (C[i+1]->nKeys == 2*t-1) 
        { 
            // If the child is full, then split it 
            splitChild(i+1, C[i+1]); 
  
            // After split, the middle key of C[i] goes up and 
            // C[i] is splitted into two.  See which of the two 
            // is going to have the new key 
            if (keys[i+1] < k) 
                i++; 
        } 
        C[i+1]->insertNonFull(k); 
    } 
} 
  
// Spliting the child y of this node 
// Note that y must be full when this function is called 
template<class keyType>
void Node<keyType>::splitChild(int i, Node *y) 
{ 
    // Create a new node which is going to store (t-1) keys 
    // of y 
    Node *z = new Node(y->t, y->isLeaf); 
    z->nKeys = t - 1; 
  
    // Copy the last (t-1) keys of y to z 
    for (int j = 0; j < t-1; j++) 
        z->keys[j] = y->keys[j+t]; 
  
    // Copy the last t children of y to z 
    if (y->isLeaf == false) 
    { 
        for (int j = 0; j < t; j++) 
            z->C[j] = y->C[j+t]; 
    } 
  
    // Reduce the number of keys in y 
    y->nKeys = t - 1; 
  
    // Since this node is going to have a new child, 
    // create space of new child 
    for (int j = nKeys; j >= i+1; j--) 
        C[j+1] = C[j]; 
  
    // Link the new child to this node 
    C[i+1] = z; 
  
    // A key of y will move to this node. Find location of 
    // new key and move all greater keys one space ahead 
    for (int j = nKeys-1; j >= i; j--) 
        keys[j+1] = keys[j]; 
  
    // Copy the middle key of y to this node 
    keys[i] = y->keys[t-1]; 
  
    // Increment count of keys in this node 
    nKeys++;
} 
  
// Driver program to test above functions 
int main() 
{ 
    BTree<int> t(3); // A B-Tree with minium degree 3, order 6 
    t.insert(10); 
    t.insert(20); 
    t.insert(5); 
    t.insert(6); 
    t.insert(12); 
    t.insert(30); 
    t.insert(7); 
    t.insert(17); 
  
    cout << "Traversal of the constucted tree is "; 
    t.traverse(); 
  
    int k = 6; 
    (t.search(k) != NULL)? cout << "\nPresent" : cout << "\nNot Present"; 
  
    k = 15; 
    (t.search(k) != NULL)? cout << "\nPresent" : cout << "\nNot Present"; 
  
    return 0; 
}
