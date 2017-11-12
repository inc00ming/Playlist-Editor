#ifndef MYSTACK_HPP
#define MYSTACK_HPP
#include "Node.hpp"

/*You are free to add private/public members inside this template..*/
template <class T>
class MyStack{
    private:
    Node<T> *top;
    public:
    /*Default constructor*/
    MyStack();
    /*copy constructor*/
    MyStack(const MyStack<T>& rhs);
    /*destructor*/
    ~MyStack();
    /*overloaded = operator*/
    MyStack<T>& operator=(const MyStack<T>& rhs);
    /*returns true if stack is empty*/
    bool isEmpty() const;
    /*push newItem to stack*/
    void push(const T& newItem);
    /*pop item from stack*/
    void pop();
    /*return top item of the stack*/
    Node<T>* Top() const;
	/*Prints the stack entries. This method was already implemented. Do not modify.*/
    void print() const;
    void insertNode(Node<T>* prev, const T& data);
};

template <class T>
void MyStack<T>::print() const{
    const Node<T>* node = top;
    while (node) {
        std::cout << node->getData();
        node = node->getNext();
    }
    cout<<std::endl;
}

/* TO-DO: method implementations below */
template <class T>
MyStack<T>::MyStack(const MyStack<T>& rhs){
    Node<T>* temp = rhs.Top();
    top = new Node<T>(temp->getData());
    Node<T>* walker = top;
    temp = temp->getNext();
    while(temp){
        insertNode(walker, temp->getData());
        walker = walker->getNext();
        temp = temp -> getNext();
    }
}

template <class T>
MyStack<T>& MyStack<T>::operator=(const MyStack<T>& rhs){
    if(this == &rhs){
        return *this;
    }
    else{
        while(top){
	        pop();
	    }

	    Node<T>* temp = rhs.Top();
        top = new Node<T>(temp->getData());
        Node<T>* walker = top;
        temp = temp->getNext();
        while(temp){
            insertNode(walker, temp->getData());
            walker = walker->getNext();
            temp = temp -> getNext();
        }

        return *this;
    }
}

template <class T>
MyStack<T>::~MyStack(){
	while(top){
	    pop();
	}
}

template <class T>
MyStack<T>::MyStack(){
	top = NULL;
}

template <class T>
bool MyStack<T>::isEmpty() const{
    return top == NULL;
}

template <class T>
void MyStack<T>::pop(){
    if(isEmpty()){
        return ;
    }
    else{
        Node<T>* temp = top;
        top = top->getNext();
        delete temp;
        return ;
    }
}

template <class T>
void MyStack<T>::push(const T& newItem){
    if(isEmpty()){
        top = new Node<T>(newItem);
        return;
    }
    else{
        Node<T>* newNode = new Node<T>(newItem);
        newNode->setNext(top);
        top = newNode;
        return ;
    }
}

template <class T>
Node<T>* MyStack<T>::Top() const{
    return top;
}

template<class T>
void MyStack<T>::insertNode(Node<T>* prev, const T& data){
    if(prev == NULL){
        top = new Node<T>(data);
        return ;
    }
    else{
        Node<T>* temp = top;
        while(temp != prev){
            temp = temp -> getNext();
        }
        Node<T>* newNode = new Node<T>(data);
        newNode->setNext(temp->getNext());
        temp->setNext(newNode);
        return ;
    }
}

#endif /* MYSTACK_HPP */
