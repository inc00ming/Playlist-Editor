#include <iostream>
#include "Node.hpp"

using namespace std;

int main(){
	Node<int>* node5 = new Node<int>(5);
	Node<int>* node4 = new Node<int>(4);
	Node<int>* node3 = new Node<int>(3);

	node5->setNext(node4);
	node4->setNext(node3);
	Node<int>* temp = node5;
	while(temp){
		cout << *temp << endl;
		temp = temp->getNext();
	}
	
	delete node5;
	delete node4;
	delete node3;
	delete temp;
	
	return 0;
}