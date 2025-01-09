//
// Aral Müftüoğlu
// 22201566
// Section 3
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <ostream>

#include "Node.h"

#include <string>
using namespace std;

template <class ItemType>
class LinkedList {
private:
    Node<ItemType>* headPtr;
    int itemCount;
    Node<ItemType>* getNodeAt (int position) const;
public:
    LinkedList();
    LinkedList(const LinkedList<ItemType>& aList);
    ~LinkedList();

    bool isEmpty()const;
    int getLength()const;
    bool insert (int newPosition, const ItemType& newItem);
    bool remove (int position);
    void clear();

    ItemType getItem(int position) const;

    ItemType replace(int position, const ItemType& newItem);

    LinkedList<ItemType>& operator=(const LinkedList<ItemType>& otherList);

};

//default constructor
template<class ItemType>
LinkedList<ItemType>::LinkedList() {
    headPtr = nullptr;
    itemCount = 0;
}

//copy constructor
template<class ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType> &aList) {
    itemCount = aList.itemCount;

    Node<ItemType>* origChainPtr = aList.headPtr;

    if (origChainPtr == nullptr) {
        headPtr = nullptr;
    } else {
        headPtr = new Node<ItemType>();
        (*headPtr).setItem((*origChainPtr).getItem());

        Node<ItemType>* newChainPtr = headPtr;
        origChainPtr = (*origChainPtr).getNext();
        while (origChainPtr != nullptr) {
            ItemType nextItem = (*origChainPtr).getItem();
            Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);

            (*newChainPtr).setNext(newNodePtr);

            newChainPtr = (*newChainPtr).getNext();
            origChainPtr = (*origChainPtr).getNext();
        }

        (*newChainPtr).setNext(nullptr);
    }
}

//destructor
template<class ItemType>
LinkedList<ItemType>::~LinkedList() {
    clear();
}

//get item method
template<class ItemType>
ItemType LinkedList<ItemType>::getItem(int position) const {
    bool ableToGetItem = (position>=1)&&(position<=itemCount);

    if (ableToGetItem) {
        Node<ItemType>* nodePtr = getNodeAt(position);
        return (*nodePtr).getItem();
    }
    else {
        throw std::out_of_range("Invalid position for getItem");
    }
}

//get node method
template<class ItemType>
Node<ItemType> *LinkedList<ItemType>::getNodeAt(int position) const {

    bool ableToGet = (position>=1)&&(position<=itemCount);

    if (ableToGet) {
        Node<ItemType>* curPtr= headPtr;

        for (int i = 1; i < position; i++) {
            curPtr = (*curPtr).getNext();
        }

        return curPtr;
    }
    else {
        throw std::out_of_range("Invalid position for getNodeAt");
    }

}

//insert method
template<class ItemType>
bool LinkedList<ItemType>::insert(int newPosition, const ItemType &newItem) {
    bool ableToInsertItem = (newPosition>=1)&&(newPosition<=itemCount + 1);

    if (ableToInsertItem) {
        Node<ItemType>* newNodePtr = new Node<ItemType>(newItem);

        if(newPosition==1) {

            (*newNodePtr).setNext(headPtr);
            headPtr = newNodePtr;
        }
        else {
            Node<ItemType>* prevPtr = getNodeAt(newPosition-1);
            (*newNodePtr).setNext(prevPtr->getNext());
            (*prevPtr).setNext(newNodePtr);
        }
        itemCount++;
    }

    return ableToInsertItem;
}

//remove method
template<class ItemType>
bool LinkedList<ItemType>::remove(int position) {
    bool ableToRemoveItem = (position>=1)&&(position<=itemCount);

    if (ableToRemoveItem) {
        Node<ItemType>* curPtr = nullptr;

        if (position==1) {
            curPtr = headPtr;
            headPtr = (*headPtr).getNext();
        }
        else {
            Node<ItemType>* prevPtr = getNodeAt(position-1);

            curPtr = (*prevPtr).getNext();
            (*prevPtr).setNext((*curPtr).getNext());
        }

        (*curPtr).setNext(nullptr);
        delete curPtr;
        curPtr = nullptr;

        itemCount--;
    }
    return ableToRemoveItem;
}

//clear method
template<class ItemType>
void LinkedList<ItemType>::clear() {
    while(!isEmpty()) {
        remove(1);
    }
}

//replace method
template<class ItemType>
ItemType LinkedList<ItemType>::replace(int position, const ItemType &newItem) {
    bool ableToReplaceItem = (position>=1)&&(position<=itemCount);

    if (ableToReplaceItem) {

        Node<ItemType>* curPtr = getNodeAt(position);
        ItemType oldItem = (*curPtr).getItem();
        (*curPtr).setItem(newItem);

        return oldItem;
    }
    else {
        throw std::out_of_range("Invalid position for replace");
    }
}

//is empty method
template<class ItemType>
bool LinkedList<ItemType>::isEmpty() const {
    bool isEmpty;

    if (itemCount == 0) {
        isEmpty = true;
    }
    else {
        isEmpty = false;
    }
    return isEmpty;
}

//get length method
template<class ItemType>
int LinkedList<ItemType>::getLength() const {
    return itemCount;
}

template<class ItemType>
LinkedList<ItemType>& LinkedList<ItemType>::operator=(const LinkedList<ItemType>& otherList) {
    if (this == &otherList) {
        return *this;
    }

    clear();

    Node<ItemType>* currentNode = otherList.headPtr;
    while (currentNode != nullptr) {
        this->insert(this->getLength() + 1, currentNode->getItem());
        currentNode = currentNode->getNext();
    }

    return *this;
}

#endif //LINKEDLIST_H
