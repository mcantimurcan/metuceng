#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template <class T>
class LinkedList
{
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &rhs);
    ~LinkedList();

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

    int getSize() const;
    bool isEmpty() const;
    bool containsNode(Node<T> *node) const;
    int getIndex(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void append(const T &data);
    void prepend(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAtIndex(const T &data, int index);
    void moveToIndex(int currentIndex, int newIndex);
    void mergeNodes(int sourceIndex, int destIndex);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeNodeAtIndex(int index);
    void removeAllNodes();

    void print() const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    Node<T> *head;
    int size;
};

template<class T>
LinkedList<T>::LinkedList()
{
    head = new Node<T>(T());
    size = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &rhs)
{
    size = rhs.size;
    head = new Node<T>(T());
    Node<T> *current = rhs.head->next;
    Node<T> *newCurrent = head;
    while (current) {
        newCurrent->next = new Node<T>(current->data);
        newCurrent->next->prev = newCurrent;
        newCurrent = newCurrent->next;
        current = current->next;
    }
}

template<class T>
LinkedList<T>::~LinkedList()
{
    removeAllNodes();
    delete head;
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs)
{
    if (this != &rhs) {
        Node<T> *newHead = new Node<T>(T());
        size = rhs.size;
        Node<T> *currentNew = newHead;
        Node<T> *currentRHS = rhs.head->next;
        while (currentRHS) {
            currentNew->next = new Node<T>(currentRHS->data);
            currentNew->next->prev = currentNew;
            currentNew = currentNew->next;
            currentRHS = currentRHS->next;
        }
        Node<T> *oldCurrent = head;
        while (oldCurrent) {
            Node<T> *next = oldCurrent->next;
            delete oldCurrent;
            oldCurrent = next;
        }
        head = newHead;
    }
    return *this;
}

template<class T>
int LinkedList<T>::getSize() const
{
    return size;
}

template<class T>
bool LinkedList<T>::isEmpty() const
{
    return (size == 0);
}

template<class T>
bool LinkedList<T>::containsNode(Node<T> *node) const
{
    Node<T> *current = getFirstNode();
    while(current){
        if(current == node){
            return true;
        }
        current = current -> next;
    }
    return false;
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const
{
    if(isEmpty()){
        return NULL;
    } else {
        return head->next;
    }
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const
{
    if(isEmpty()){
        return NULL;
    }
    Node<T>* current = getFirstNode();
    while(current -> next){
        current = current -> next;
    }
    return current;
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const
{
    Node<T> *current = getFirstNode();
    while(current){
        if (current -> data == data){
            return current;
        }
        current = current -> next;
    }
    return NULL;
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const
{
    Node<T> *current = getFirstNode();
    int num = 0;
    while(current){
        if(num == index){
            return current;
        }
        current = current -> next;
        num++;
    }
    return NULL;
}

template<class T>
void LinkedList<T>::append(const T &data)
{   
    Node<T> *newNode = new Node<T>(data);
    if (size == 0) {
        newNode -> prev = head;
        head -> next = newNode;
    } else {
        Node<T> *current = getLastNode();
        newNode -> prev = current;
        current -> next = newNode;
    }
    size++;
}

template<class T>
void LinkedList<T>::prepend(const T &data)
{
    Node<T>* newNode = new Node<T>(data);
    if (head->next) {
        newNode->next = head->next;
        head->next->prev = newNode;
    }
    head->next = newNode;
    newNode->prev = head;
    size++;
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node)
{
    if(!node){
        return;
    }
    Node<T> *newNode = new Node<T>(data);
    newNode -> prev = node;
    newNode -> next = node -> next;
    if(node -> next){
        node -> next -> prev = newNode;
    }
    node -> next = newNode;
    size++;
}

template<class T>
void LinkedList<T>::insertAtIndex(const T &data, int index)
{
    int i = 0;
    Node<T> *current = getFirstNode();
    if(index < size && index >= 0){
        while(current){
            if(i == index-1){
                Node<T> *newNode = new Node<T>(data);
                newNode -> prev = current;
                newNode -> next = current -> next;
                if(current -> next){
                    current -> next -> prev = newNode;
                }
                current -> next = newNode;
            }
            i++;
            current = current -> next;
        }
    }
    size++;
}

template<class T>
int LinkedList<T>::getIndex(Node<T> *node) const
{
    Node<T> *current = getFirstNode();
    int index = 0;
    while(current){
        if(current == node){
            return index;
        }
        current = current -> next;
        index++;
    }
    return -1;
}

template<class T>
void LinkedList<T>::moveToIndex(int currentIndex, int newIndex)
{
    if (currentIndex < 0 || currentIndex >= size || newIndex < 0 || currentIndex == newIndex) {
        return;
    }
    if(newIndex >= size){
        newIndex = size - 1;
    }
    if(newIndex != currentIndex){
        if(currentIndex > newIndex && newIndex != 0){
            newIndex = newIndex - 1;
            Node<T> *currentNode = getNodeAtIndex(currentIndex);
            Node<T> *newIndexNode = getNodeAtIndex(newIndex);
            if (currentNode) {
                currentNode->prev->next = currentNode->next;
                if (currentNode->next) {
                    currentNode->next->prev = currentNode->prev;
                }
                currentNode->prev = newIndexNode;
                currentNode->next = newIndexNode->next;
                newIndexNode->next = currentNode;
                if (currentNode->next) {
                    currentNode->next->prev = currentNode;
                }
            }
        } else if (currentIndex > newIndex && newIndex == 0){
            Node<T> *currentNode = getNodeAtIndex(currentIndex);
            Node<T> *newIndexNode = head;
            if (currentNode) {
                currentNode->prev->next = currentNode->next;
                if (currentNode->next) {
                    currentNode->next->prev = currentNode->prev;
                }
                currentNode->prev = newIndexNode;
                currentNode->next = newIndexNode->next;
                newIndexNode->next = currentNode;
                if (currentNode->next) {
                    currentNode->next->prev = currentNode;
                }
            }
        } else {
            Node<T> *currentNode = getNodeAtIndex(currentIndex);
            Node<T> *newIndexNode = getNodeAtIndex(newIndex);
            if (currentNode) {
                currentNode->prev->next = currentNode->next;
                if (currentNode->next) {
                    currentNode->next->prev = currentNode->prev;
                }
                currentNode->prev = newIndexNode;
                currentNode->next = newIndexNode->next;
                newIndexNode->next = currentNode;
                if (currentNode->next) {
                    currentNode->next->prev = currentNode;
                }
            }
        }
    }
}

template<class T>
void LinkedList<T>::mergeNodes(int sourceIndex, int destIndex)
{
    if (sourceIndex < 0 || sourceIndex >= size || destIndex < 0 || destIndex >= size || sourceIndex == destIndex) {
        return;
    }
    Node<T> *firstNode = getNodeAtIndex(sourceIndex);
    Node<T> *secondNode = getNodeAtIndex(destIndex);
    secondNode -> data = secondNode -> data + firstNode -> data;
    removeNodeAtIndex(sourceIndex);
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node)
{   
    Node<T> *current = getFirstNode();
    while(current){
        if(current == node){
            if (current->prev) {
                current->prev->next = current->next;
            }
            if (current->next) {
                current->next->prev = current->prev;
            }
            delete current;
            break;
        }
        current = current -> next;
    }
    size--;
}

template<class T>
void LinkedList<T>::removeNode(const T &data)
{   
    Node<T> *current = getFirstNode();
    while(current){
        if(current -> data == data){
            if (current->prev) {
                current->prev->next = current->next;
            }
            if (current->next) {
                current->next->prev = current->prev;
            }
            Node<T> *temp = current->next;
            delete current;
            size--;
            current = temp;
        } else {
            current = current -> next;
        }
    }
}

template<class T>
void LinkedList<T>::removeNodeAtIndex(int index)
{
    if (index < 0 || index >= size) {
        return;
    }
    Node<T> *current = getFirstNode();
    while(current){
        if(getIndex(current) == index){
            if (current->prev) {
                current->prev->next = current->next;
            }
            if (current->next) {
                current->next->prev = current->prev;
            }
            delete current;
            size--;
            return;
        }
        current = current->next;
    }
}


template<class T>
void LinkedList<T>::removeAllNodes()
{
    while(head){
        Node<T> *temp = head -> next;
        delete head;
        head = temp;
    }
    size = 0;
}

template<class T>
void LinkedList<T>::print() const
{
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    Node<T> *node = this->getFirstNode();

    while(node)
    {
        std::cout << *node << std::endl;
        node = node->next;
    }

}

#endif //LINKEDLIST_H