// C++ program for B-Tree insertion
// For simplicity, assume order m = 2 * t
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "BTree.h"

using namespace std;

// Driver program to test above functions
int main()
{
    BTree<string> t(3); // A B-Tree with minium degree 3, order 6

    fstream inFile("test_string.txt");

    string input;

    while (inFile >> input)
    {
        t.insert(input);
    }

    inFile.close();

    inFile.open("wordsToDelete.txt");

    while (inFile >> input)
    {
        t.remove(input);
    }

    //cout << "Traversal of the constucted tree is ";
    t.traverse();
    
    return 0;
}
