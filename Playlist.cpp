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

void::Playlist::deleteEntry(const std::string &_title){
    Node<Entry>* temp = entries.getHead();
    while(temp->getData().getTitle() != _title ){
        if(temp->getNext() == NULL){
            return;
        }
        else{
            temp = temp->getNext();
        }
    }
    Node<Entry>* prev = entries.findPrev((const Entry&)temp->getData());
    entries.deleteNode(prev);
    history.push(HistoryRecord(DELETE, temp->getData()));
}
/* TO-DO: method implementations below */
