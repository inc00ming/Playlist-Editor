#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Playlist.hpp"
#include "Entry.hpp"

using namespace std;


Playlist::Playlist()
{
    srand(15);
}

int Playlist::getRandomNumber(int i, int n) const
{
    int range=n-i;
    int random = rand() % range + i;
    return random;
}

void Playlist::print()
{
    cout << "[PLAYLIST SIZE=" << entries.getSize() <<"]";
    entries.print();
}
void Playlist::printHistory()
{
    cout<<"[HISTORY]";
    history.print();
}

void Playlist::load(std::string fileName){
    ifstream inputFile;
    inputFile.open(fileName.c_str());
    string line, title, genre, year, temp;
    string delimiter = ";";
    int i = 0, current, next = -1;

    while(getline(inputFile, line)){
        do{
            current = next + 1;
            next = line.find_first_of( delimiter, current );
            temp = line.substr( current, next - current );
            if(i == 0){
                title = temp;
                i++;
            }
            else if(i == 1){
                genre = temp;
                i++;
            }
            else{
                year = temp;
                Entry e = Entry(title, genre, year);
                insertEntry(e);
                i = 0;
            }
        }
        while (next != string::npos);
    }
}

void Playlist::insertEntry(const Entry &e){
    entries.insertNode(entries.getTail(), e);
    history.push(HistoryRecord(INSERT, e));
}

void Playlist::deleteEntry(const std::string &_title){
    Node<Entry>* temp = entries.getHead();
    while(temp->getData().getTitle() != _title ){
        if(temp->getNext() == NULL){
            return;
        }
        else{
            temp = temp->getNext();
        }
    }
    history.push(HistoryRecord(DELETE, temp->getData()));
    Node<Entry>* prev = entries.findPrev(temp->getData());
    entries.deleteNode(prev);

}

void Playlist::moveLeft(const std::string &title){
    Node<Entry>* temp = entries.getHead();
    while(temp->getData().getTitle() != title ){
        if(temp->getNext() == NULL){
            return; // ENTRY DOES NOT EXIST
        }
        else{
            temp = temp->getNext();
        }
    }
    if(temp == entries.getHead()){
        return ; // HEAD NODE CANT MOVE LEFT
    }
    else if(temp == entries.getTail()){
        //cout << "YOU SHOUL READ THIS" << endl;
        Node<Entry>* firstPrev = entries.findPrev(temp->getData());
        Node<Entry>* secondPrev = entries.findPrev(firstPrev->getData());

        Node<Entry>* newTail = new Node<Entry>(firstPrev->getData());
        entries.deleteNode(secondPrev);
        secondPrev->setNext(temp);
        entries.setTail(newTail);
    }
    else{
        Node<Entry>* firstPrev = entries.findPrev(temp->getData());

        if(firstPrev == entries.getHead()){
            Node<Entry>* newHead = new Node<Entry>(temp->getData());
            Node<Entry>* tempNext = temp->getNext();
            entries.deleteNode(firstPrev);
            firstPrev->setNext(tempNext);
            entries.setHead(newHead);
        }
        else{
            Node<Entry>* secondPrev = entries.findPrev(firstPrev->getData());
            firstPrev->setNext(temp->getNext());
            temp->setNext(secondPrev->getNext());
            secondPrev->setNext(temp);
        }
    }
}

void Playlist::moveRight(const std::string &title){
    Node<Entry>* temp = entries.getHead();
    while(temp->getData().getTitle() != title ){
        if(temp->getNext() == NULL){
            return; // ENTRY DOES NOT EXIST
        }
        else{
            temp = temp->getNext();
        }
    }

    if(temp == entries.getTail()){
        return ; // TAIL NODE CANT MOVE RIGHT
    }
    else if(temp == entries.getHead()){
        Node<Entry>* headNextNext = temp->getNext()->getNext();
        Node<Entry>* newHead = new Node<Entry>(temp->getNext()->getData());
        entries.deleteNode(temp);
        temp->setNext(headNextNext);
        entries.setHead(newHead);
    }
    else{
        Node<Entry>* firstNext = temp->getNext();
        if(firstNext == entries.getTail()){
            Node<Entry>* newTail = new Node<Entry>(temp->getData());
            Node<Entry>* firstPrev = entries.findPrev(temp->getData());
            entries.deleteNode(firstPrev);
            firstPrev->setNext(firstNext);
            entries.setTail(newTail);
        }
        else{
            Node<Entry>* firstPrev = entries.findPrev(temp->getData());
            firstPrev->setNext(firstNext);
            temp->setNext(firstNext->getNext());
            firstNext->setNext(temp);
        }
    }
}

void Playlist::reverse(){
    Node<Entry>* walker = entries.getHead();
    MyStack<Entry> myStack = MyStack<Entry>();
    while(walker != NULL){
        myStack.push(walker->getData());
        walker = walker -> getNext();
    }
    entries.clear();
    while(!(myStack.isEmpty())){
        entries.insertNode(entries.getTail() ,myStack.Top()->getData()) ;
        myStack.pop();
    }
    history.push(HistoryRecord(REVERSE));

}

/*void Playlist::sort(){
    int size = entries.getSize();
    Node<Entry> entryArray[size];
    Node<Entry>* walker = entries.getHead();
    int minIndex, i = 0, j;
    Node<Entry> temp;

    while(walker != NULL){
        entryArray[i++] = walker->getData();
        walker = walker -> getNext();
    }

    for(i = 0; i < size; i++){
        minIndex = i;
        for(j = i + 1; j < size; j++){
            if(entryArray[j].getData().getTitle() < entryArray[minIndex].getData().getTitle()){
                minIndex = j;
            }
        }
        temp = entryArray[i];
        entryArray[i] = entryArray[minIndex];
        entryArray[minIndex] = temp;
    }

    entries.clear();

    for(i = 0; i < size; i++){
        entries.insertNode(entries.getTail(), entryArray[i].getData());
    }
}
/**/
void Playlist::merge(const Playlist & pl){
    Node<Entry>* walker = pl.entries.getHead();
    if(walker == NULL){
        return ; // OTHER PLAYLIST IS EMPTY
    }
    else if(entries.getHead() == NULL){
        while(walker != NULL){ //CURRENT PLAYLIST IS EMPTY
            entries.insertNode(entries.getTail(), walker->getData());
            walker = walker -> getNext();
        }
        return ;
    }
    else{
        Node<Entry>* cooper = entries.getHead();
        Node<Entry>* prev;
        while(cooper != NULL && walker != NULL){
            if(cooper->getData().getTitle() < walker->getData().getTitle()){
                cooper = cooper ->getNext();
            }
            else{
                prev = entries.findPrev(cooper->getData());
                entries.insertNode(prev, walker->getData());
                walker = walker ->getNext();
            }
        }
        if(cooper == NULL){
            while(walker != NULL){
                entries.insertNode(entries.getTail(), walker->getData());
                walker = walker -> getNext();
            }
            return;
        }
    }
}

void Playlist::shuffle(){
    Node<Entry>* walker = entries.getHead();
    int size = entries.getSize();
    Node<Entry> entryArray[size];
    for(int i = 0; i < size; i++){
        entryArray[i] = walker->getData();
        walker = walker ->getNext();
    }
    for(int i = 0; i < size - 1; i++){
        Node<Entry> temp = entryArray[i];
        int random = getRandomNumber(i, size);
        entryArray[i] = entryArray[random];
        entryArray[random] = temp;
    }
    entries.clear();
    for(int i = 0; i < size; i++){
        entries.insertNode(entries.getTail(), entryArray[i].getData());
    }
}

void Playlist::undo(){
    if(history.isEmpty())
        return ;
    Node<HistoryRecord>* op = history.Top();
    if(op->getData().getOperation() == REVERSE){
        reverse();
        history.pop();
        history.pop();
    }
    else if(op->getData().getOperation() == DELETE){
        insertEntry(op->getData().getEntry());
        history.pop();
        history.pop();
    }
    else if(op->getData().getOperation() == INSERT){
        deleteEntry(op->getData().getEntry().getTitle());
        history.pop();
        history.pop();
    }
}

void Playlist::sort(){
    Node<Entry>* walker;
    Node<Entry>* cooper;
    int i = 0, j=0;
    for(walker = entries.getHead(); walker->getNext() != NULL; walker = walker->getNext()){
        Node<Entry>* min = walker;

        //cout << walker->getData().getTitle() << endl;
        for(cooper = walker->getNext(); cooper != NULL; cooper = cooper->getNext()){
            if(cooper->getData().getTitle()<min->getData().getTitle()){
                j++;
                min = cooper;
            }
        }
        //swapping min and walker. god help me :D
        if(min == walker){
            continue; //
        }
        else{
            Node<Entry>* prevMin = entries.findPrev(min->getData());
            Node<Entry>* prevWalker = entries.findPrev(walker->getData());
            Entry minData = min->getData();
            Entry walkerData = walker->getData();
            if(prevMin == walker){
                if(prevWalker == NULL){
                    entries.deleteNode(prevMin);
                    entries.deleteNode(prevWalker);
                    entries.setHead(new Node<Entry>(minData));
                    entries.insertNode(entries.getHead(), walkerData);
                    walker = entries.getHead();
                }
                else{
                    entries.deleteNode(prevMin);
                    entries.deleteNode(prevWalker);
                    entries.insertNode(prevWalker, minData);
                    entries.insertNode(prevWalker->getNext(), walkerData);
                    walker = prevWalker->getNext();
                }
            }
            else{
                if(prevWalker == NULL){
                    entries.deleteNode(prevMin);
                    entries.deleteNode(prevWalker);
                    entries.setHead(new Node<Entry>(minData));
                    entries.insertNode(prevMin, walkerData);
                    walker = entries.getHead();
                }
                else{
                    entries.deleteNode(prevMin);
                    entries.deleteNode(prevWalker);
                    entries.insertNode(prevWalker, minData);
                    entries.insertNode(prevMin, walkerData);
                    walker = prevWalker->getNext();
                }
            }
        }
    }
}
/* TO-DO: method implementations below */
