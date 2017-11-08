#include <iostream>
#include <cstdlib>
#include <ctime>
#include "LinkedList.hpp"
#include <sstream>
#include <string>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()
		

class tmpClass{
    public:
        tmpClass(string val1 = "", int val2 = 0): s_val(val1), i_val(val2) {};
        friend ostream &operator<<(ostream &out, const tmpClass& r){
            out << r.s_val << "-" << r.i_val<<";";
            return out;
        };
    private:
        string s_val;
        int i_val;
};


void testPrint(){
    srand (15);
    LinkedList<tmpClass> list = LinkedList<tmpClass>();
    list.print();
    for (int i = 0; i < 20; ++i){
        list.insertNode(list.getHead(),tmpClass(SSTR(rand()%10), rand()%10));
    }
    list.print();
}

void testCopy(){
    srand (17);
    LinkedList<tmpClass> list = LinkedList<tmpClass>();
    for (int i = 0; i < 5; ++i){
        list.insertNode(list.getHead(),tmpClass(SSTR(rand()%10), rand()%10));
    }
    list.print();
    LinkedList<tmpClass> list2 = list;
    list2.print();
    LinkedList<tmpClass> list3;
    list3 = list2;
    list3.print();
}


int main(int argc, char* argv[]){
     testPrint();
     cout << endl;
     testCopy();
     
     
     /*LinkedList<int> list1 = LinkedList<int>();
    
    for (int i = 0; i < 5; ++i)
        list1.insertNode(list1.getTail(),i);
    
    LinkedList<int> list2 = list1;
    
    for (int i = 5; i < 10; ++i)
        list2.insertNode(list2.getTail(),i);
   
    list1.print();
    list2.print();
    cout << list1.getSize() << "-" << list2.getSize() << endl;
    list2 = list1;
    cout << "after list1=list2" << endl;
    list1.print();
    list2.print();
    cout << list1.getSize() << "-" << list2.getSize() << endl;
    list1.insertNode(list1.getTail(),6);
    list2.insertNode(list2.getTail(),7);
    list1.print();
    list2.print();
    cout << list1.getSize() << "-" << list2.getSize() << endl;
    /*
    Node<int>* node1 = new Node<int>(1);
    Node<int>* node2 = new Node<int>(2);
    Node<int>* node3 = new Node<int>(3);
    Node<int>* node4 = new Node<int>(4);
    Node<int>* node5 = new Node<int>(5);
    LinkedList<int> list = LinkedList<int>();
    
    cout << "CHECKING EMPTY LIST: " << list.isEmpty() << endl;
    cout << "LIST SIZE:" << list.getSize() << endl;
    
    cout << "NODE-1 ADDED AFTER HEAD" << endl;
    list.insertNode(list.getHead(), 1);
    cout << "LIST HEAD:" << *list.getHead() << endl << "LIST TAIL:" << *list.getTail() << endl;
    cout << "LIST SIZE:" << list.getSize() << endl;
    cout << "LIST:";list.print();

    cout << "NODE-2 ADDED AFTER HEAD" << endl;
    list.insertNode(list.getHead(), 2);
    cout << "LIST HEAD:" << *list.getHead() << endl << "LIST TAIL:" << *list.getTail() << endl;
    cout << "LIST SIZE:"<< list.getSize() << endl;
    cout << "LIST:";list.print();
    
    cout << "NODE-3 ADDED AFTER HEAD" << endl;
    list.insertNode(list.getHead(), 3);
    cout << "LIST HEAD:" << *list.getHead() << endl << "LIST TAIL:" << *list.getTail() << endl;
    cout << "LIST SIZE:"<< list.getSize() << endl;
    cout << "LIST:";list.print();
    
    cout << "NODE-4 ADDED AFTER TAIL" << endl;
    list.insertNode(list.getTail(), 4);
    cout << "LIST HEAD:" << *list.getHead() << endl << "LIST TAIL:" << *list.getTail() << endl;
    cout << "LIST SIZE:"<< list.getSize() << endl;
    cout << "LIST:";list.print();
    
    Node<int>* temp = list.findPrev(4);
    cout << *temp->getNext() << endl;
    */
    
    //cout << endl << "TEST 2" << endl;
    //testCopy();

    return 0;
}		
