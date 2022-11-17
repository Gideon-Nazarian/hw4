#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"


struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void BAL(AVLNode<Key,Value>* ptr);
    void insertRec(const std::pair<const Key, Value> &new_item, AVLNode<Key,Value>* ptr, AVLNode<Key,Value>* ptrPar, int child);
    int Hi(AVLNode<Key,Value>* ptr);
    void rotateWithLeftChild(AVLNode<Key,Value>* ptr);
    //void doubleWithLeftChild(AVLNode<Key,Value>* ptr);
    //void rotateWithRightChild(Node<Key,Value>* ptr);
    //void doubleWithRightChild(Node<Key,Value>* ptr);

};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
 

 template<class Key, class Value>
void AVLTree<Key, Value>::rotateWithLeftChild(AVLNode<Key,Value>* ptr){
  //std::cout << "hello" << std::endl;
  
  AVLNode<Key, Value> *temp = ptr -> getLeft();
  //std::cout << temp -> getKey() << std::endl;
  /*
  ptr -> setLeft(temp -> getRight());
  temp -> setRight(ptr);
  ptr -> setBalance( std::max(Hi(ptr -> getLeft()), Hi(ptr -> getRight())) + 1);
  temp -> setBalance( std::max(Hi(temp -> getLeft()), (int)(ptr -> getBalance())) + 1);
  ptr = temp;
  */

}
/*
template<class Key, class Value>
void AVLTree<Key, Value>::doubleWithLeftChild(Node<Key,Value>* ptr){
  
  rotateWithRightChild(ptr -> getLeft());
  rotateWithLeftChild(ptr);


}
*/


template<class Key, class Value>
int AVLTree<Key, Value>::Hi(AVLNode<Key,Value>* ptr){

  return ptr == nullptr ? -1: (int)(ptr -> getBalance());

}


 template<class Key, class Value>
void AVLTree<Key, Value>:: BAL(AVLNode<Key,Value>* ptr){
  if(ptr == nullptr){
    return;
  }
  if( Hi(ptr -> getLeft()) - Hi(ptr -> getRight()) > 1 ){
    if( Hi(ptr -> getLeft() -> getLeft()) >= Hi(ptr -> getLeft() -> getRight()) ){
      rotateWithLeftChild(ptr);
    }
    else{
      // doubleWithLeftChild(ptr);
    }
  }
  else{
    if( Hi(ptr -> getRight()) - Hi(ptr -> getLeft()) > 1 ){
      if( Hi(ptr -> getRight() -> getRight()) >= Hi(ptr -> getRight() -> getLeft()) ){
      // rotateWithRightChild(ptr);
      }
      else{
      // doubleWithRightChild(ptr);
      }
    }

  }
  ptr -> setBalance( (int8_t) ( std::max(Hi(ptr -> getLeft()), Hi( ptr -> getRight() ) ) + 1) );

}


template<class Key, class Value>
void AVLTree<Key, Value>::insertRec(const std::pair<const Key, Value> &new_item, AVLNode<Key,Value>* ptr, AVLNode<Key,Value>* ptrPar, int child){
  if(ptr == nullptr){
    if(this -> root_ == nullptr){
      this -> root_ = new AVLNode<Key, Value>( new_item.first, new_item.second, nullptr);
    }
    else{
     // Node<Key, Value> *temp = new AVLNode<Key, Value>( new_item.first, new_item.second, nullptr);

     ptr = new AVLNode<Key, Value>( new_item.first, new_item.second, nullptr);
    //check child here
      if(child == 1){ //left child
        ptrPar -> setLeft(ptr);
        ptr -> setParent(ptrPar);
      }
      if(child == 2){ //right child
        ptrPar -> setRight(ptr);
        ptr -> setParent(ptrPar);
      }
  
    }
    
  }

  else if(ptr -> getKey() > new_item.first){
    insertRec(new_item, ptr -> getLeft(), ptr, 1);
  }
  else if(ptr -> getKey() < new_item.first){
    insertRec(new_item, ptr -> getRight(), ptr, 2);
  }

  //BAL(ptr);


}

template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO

   if(this -> root_ == nullptr){
  
      insertRec(new_item, nullptr, nullptr, 0);
    }
    else
    {
      AVLNode<Key, Value> *ptr = static_cast<AVLNode<Key, Value>*>(this->root_);
      insertRec(new_item, ptr, nullptr, 0);

      //std::cout << this -> root_ -> getKey() << " (should be d)" << std::endl;
      /*
      if(this -> root_ -> getParent() == nullptr){
        // std::cout << this -> root_ -> getParent() -> getKey() << " (should be d)" << std::endl;
        std::cout << "fail" <<std::endl;
      }
      */
    }


        
      //isnt 3rd arg always nullptr?


    /*
    if(this -> root_ == nullptr){
        this -> root_ = new AVLNode<Key, Value>( new_item.first, new_item.second, nullptr);
        return;
    }
    else{
        Node<Key, Value> *temp = this -> root_;
        Node<Key, Value> *tempParent = nullptr;
        bool LorR = false;

        while(temp != nullptr){
            if(temp -> getKey() < new_item.first){ // if key is larger than root key
                tempParent = temp;
                temp = temp -> getRight();
                LorR = false;
            }
            else if(temp -> getKey() > new_item.first){ // if key is smaller than root key
                tempParent = temp;
                temp = temp -> getLeft();
                LorR = true;
            }
            else if(temp -> getKey() == new_item.first){ // if key is the same as root key
                temp -> setValue(new_item.second);
                return;

            }
        }
            AVLNode<Key, Value> *tempAdd = new AVLNode<Key, Value>( new_item.first, new_item.second, nullptr);
            if(LorR){
                tempParent -> setLeft(tempAdd);
                tempAdd -> setParent(tempParent);
            }
            else if(!LorR){
                tempParent -> setRight(tempAdd);
                tempAdd -> setParent(tempParent);
            }
        
    }

    */

    

}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    Node<Key, Value> *temp = this -> internalFind(key);
    // std:: cout << temp -> getKey() << " " << temp-> getValue() << std::endl;
    if(temp == nullptr){
      return;
    }else{
      //find out how many children
      if((temp -> getRight() == nullptr) && temp -> getLeft() == nullptr){ // 0 children
        if(temp -> getParent() != nullptr){ // root basecase
          Node<Key, Value> *tempPar = temp -> getParent();
          if(tempPar -> getLeft() == temp){//left child
            tempPar ->setLeft(nullptr);
            delete temp;
          }
          else if(tempPar -> getRight() == temp){ //right child
            tempPar ->setRight(nullptr);
            delete temp;
          }
        }
        else{
        delete temp;
        this -> root_ = nullptr;
        return;
        }
      }
      else if((temp -> getRight() != nullptr) && temp -> getLeft() != nullptr){ // 2 children
    
      BinarySearchTree<Key, Value> :: nodeSwap(temp, this -> predecessor(temp));

      if((temp -> getRight() == nullptr) && temp -> getLeft() == nullptr){ // 0 children
        if(temp -> getParent() != nullptr){ // root basecase
          Node<Key, Value> *tempPar = temp -> getParent();
          if(tempPar -> getLeft() == temp){//left child
            tempPar ->setLeft(nullptr);
            delete temp;
          }
          else if(tempPar -> getRight() == temp){ //right child
            tempPar ->setRight(nullptr);
            delete temp;
          }
        }
        else{
        delete temp;
        return;
        }

      }
      else{ // 1 child garentee left
         /*
         while(temp -> getLeft() != nullptr){
           nodeSwap(temp, temp->getLeft());
         }
         nodeSwap(temp, temp->getLeft());
         */
         Node<Key, Value> *tempCH = temp -> getLeft();
         Node<Key, Value> *tempGP = temp -> getParent();
         if (temp == tempGP -> getLeft()){
           tempGP -> setLeft(tempCH);
           tempCH ->setParent(tempGP);
           delete temp;
           return;
         }
         else if(temp == tempGP -> getRight()){
           tempGP -> setRight(tempCH);
           tempCH ->setParent(tempGP);
           delete temp;
           return;
         }

        }
      }
      else{ // 1 child
      //check left or right
        if(temp -> getLeft() != nullptr){ // if has left child
          if(temp-> getParent() != nullptr){
            Node<Key, Value> *tempGP = temp -> getParent();
            Node<Key, Value> *tempCH = temp -> getLeft();
            if (temp == tempGP -> getLeft()){
              tempGP -> setLeft(tempCH);
              tempCH ->setParent(tempGP);
              delete temp;
              return;
            }
            else if(temp == tempGP -> getRight()){
              tempGP -> setRight(tempCH);
              tempCH ->setParent(tempGP);
              delete temp;
              return;
            }
          }
          else if(temp ->getParent() == nullptr){
            Node<Key, Value> *tempCH = temp -> getLeft();
            this -> root_ = tempCH;
            tempCH -> setParent(nullptr);
            delete temp;
            return;
          }

        }
        if(temp -> getRight() != nullptr){ // if has right child
          if(temp-> getParent() != nullptr){
            Node<Key, Value> *tempGP = temp -> getParent();
            Node<Key, Value> *tempCH = temp -> getRight();
            if (temp == tempGP -> getLeft()){
              tempGP -> setLeft(tempCH);
              tempCH ->setParent(tempGP);
              delete temp;
              return;
            }
            else if(temp == tempGP -> getRight()){
              tempGP -> setRight(tempCH);
              tempCH ->setParent(tempGP);
              delete temp;
              return;
            }
          }
          else if(temp ->getParent() == nullptr){
            Node<Key, Value> *tempCH = temp -> getRight();
            this -> root_ = tempCH;
            tempCH -> setParent(nullptr);
            delete temp;
            return;
          }

        }

      }

    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
