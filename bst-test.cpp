#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
    // Binary Search Tree tests
    /*

    BinarySearchTree<char,int> bt;
    bt.insert(std::make_pair('d',1));
    bt.insert(std::make_pair('c',1));
    bt.insert(std::make_pair('g',2));
    //bt.insert(std::make_pair('a',3));
    // bt.insert(std::make_pair('c',3));
    bt.print();
    
    
    cout << "Binary Search Tree contents:" << endl;

    
    for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    
    if(bt.find('b') != bt.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing d" << endl;
    bt.clear();
    bt.print();
    

*/
    // AVL Tree Tests
    AVLTree<char,int> at;
    at.insert(std::make_pair('d',1));
    at.insert(std::make_pair('b',2));
    //at.insert(std::make_pair('f',3));
    at.insert(std::make_pair('a',4));
    //at.insert(std::make_pair('c',5));
    //at.insert(std::make_pair('e',6));
    //at.insert(std::make_pair('g',7));
    
    
    cout << "\nAVLTree contents:" << endl;
    for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    at.print();
    
    
    /*
    if(at.find('b') != at.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    at.remove('b');
    */


    return 0;
}
