#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <iostream>
#include "Node.hpp"

using namespace std;

/*....DO NOT EDIT BELOW....*/
template <class T> 
class LinkedList {
    private:
        Node<T>* head;
        Node<T>* tail;
	size_t  size; 
    public:

        LinkedList();
        LinkedList(const LinkedList<T>& ll);
        LinkedList<T>& operator=(const LinkedList<T>& ll);
        ~LinkedList();

        /* Return head of the linked-list*/
        Node<T>* getHead() const;
        /* Set head of the linked-list*/
        Node<T>* setHead(Node<T>* n);
        /* Return tail of the linked-list*/
        Node<T>* getTail() const;
        /* Set tail of the linked-list*/
        Node<T>* setTail(Node<T>* n);
        /* Get the previous node of the node that contains the data item. 
         * If the head node contains the data item, this method returns NULL.*/
        Node<T>* findPrev(const T& data) const;
        /* Get the node that stores the data item. 
         * If data is not found in the list, this function returns NULL.*/
        Node<T>* findNode(const T& data) const;
        /* Insert a new node to store the data item. 
         * The new node should be placed after the “prev” node. 
         * If prev is NULL then insert new node to the head.*/
        void insertNode(Node<T>* prev, const T& data); 
        /* This method is used to delete the node that is next to “prevNode”. 
         * PS:prevNode is not the node to be deleted. */
        void deleteNode(Node<T>* prevNode);  
        /* This method is used to clear the contents of the list.*/
        //void clear();
        /* This method returns true if the list empty, otherwise returns false.*/
        bool isEmpty() const;
        /* This method returns the current size of the list. */
        size_t getSize() const;
        /*Prints the list. This method was already implemented. Do not modify.*/
        void print() const;
};

template <class T>
void LinkedList<T>::print() const{
    const Node<T>* node = head;
    while (node) {
        std::cout << node->getData();
        node = node->getNext();
    }
    cout<<std::endl;
}

/*....DO NOT EDIT ABOVE....*/

/* TO-DO: method implementations below */
template <class T>
LinkedList<T>::LinkedList(){
	head = NULL;
	tail = NULL;
	size = 0;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& ll){
    size = 0;
    Node<T>* temp = ll.getHead();
    while(temp){
        insertNode(tail, temp->getData());
        temp = temp->getNext();
    }
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& ll){ 
	if(this == &ll){
	    return *this;
	}
	else{
	    while(getHead()){
	        deleteNode(NULL);
	    }
	    Node<T>* temp = ll.getHead();
        while(temp){
            insertNode(tail, temp->getData());
            temp = temp->getNext();
        }
        return *this;
	}
}

template <class T>
LinkedList<T>::~LinkedList(){
    while(getHead()){
	    deleteNode(NULL);
	}
}

template <class T>
Node<T>* LinkedList<T>::getHead() const{
	return head;
}

template <class T>
Node<T>* LinkedList<T>::setHead(Node<T>* n){
	if(size == 0){
		head = n;
		tail = n;
		size++;
		return head;
	}
	else{
		n->setNext(head);
		head = n;
		size++;
		return head;
	}
}

template <class T>
Node<T>* LinkedList<T>::getTail() const{
	return tail;
}

template <class T>
Node<T>* LinkedList<T>::setTail(Node<T>* n) {
	if(size == 0){
		head = n;
		tail = n;
		n->setNext(NULL);
		size++;
		return tail;
	}
	else{
		tail->setNext(n);
		tail = n;
		n->setNext(NULL);
		size++;
		return tail;
	}
}

template<class T>
Node<T>* LinkedList<T>::findPrev(const T& data) const{
	if(head->getData() == data)
		return NULL;
	else{
		Node<T>* temp = head;
		while(temp->getNext()->getData() != data && temp != tail){
			temp = temp->getNext();
		}
		if(temp == tail){
		    return NULL;
		}
		else{
		    return temp;
		}
	}
}

template<class T>
Node<T>* LinkedList<T>::findNode(const T& data) const{
	Node<T>* temp = head;
	while(temp != NULL){
	    if(temp->getData() == data){
	        return temp;
	    }
	    else{
	        temp = temp->getNext();
	    }
	}
	return NULL;
}
template<class T>
void LinkedList<T>::insertNode(Node<T>* prev, const T& data){
    if(prev == NULL){
        Node<T>* newNode = new Node<T>(data);
        setHead(newNode);
        return ;
    }
    else if(prev == tail){
        Node<T>* newNode = new Node<T>(data);
        setTail(newNode);
        return ;
    }
    else{
        Node<T>* temp = head;
        while(temp != prev){
            temp = temp -> getNext();
        }
        Node<T>* newNode = new Node<T>(data);
        newNode->setNext(temp->getNext());
        temp->setNext(newNode);
        return ;
    }
}

template<class T>
void LinkedList<T>::deleteNode(Node<T>* prevNode){
    if(prevNode == NULL){
        Node<T>* temp = head;
        head = head->getNext();
        delete temp;
        size--;
        return;
    }
    else if(prevNode == tail){
        return ;
    }
    else{
        Node<T>* temp = head;
        while(temp != prevNode){
            temp = temp->getNext();
        }
        Node<T>* old = temp->getNext();
        temp->setNext(old->getNext());
        if(old == tail){
            tail = prevNode;
            delete old;
            size--;
            return ;
        }  
    }
}

template<class T>
bool LinkedList<T>::isEmpty() const{
    return (size == 0) ? true : false;
}

template<class T>
size_t LinkedList<T>::getSize() const{
    return size;
}
/* end of your implementations*/

#endif
