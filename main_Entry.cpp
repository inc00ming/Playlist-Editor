#include <iostream>
#include "Entry.hpp"

using namespace std;

int main(){
    Entry e1 = Entry();
    Entry e2 = Entry("Choros", "Instrumental", "2015");
    Entry e3 = Entry("Choros", "Instrumental", "2017");
    
    cout << e1.getTitle() << "-" << e1.getGenre() << "-" << e1.getYear() << endl;
    cout << e2.getTitle() << "-" << e2.getGenre() << "-" << e2.getYear() << endl;
    cout << e3.getTitle() << "-" << e3.getGenre() << "-" << e3.getYear() << endl;
    cout << "Testing == operator" << endl;
    if(e2 == e3){
        cout << "Entries title are same" << endl;
    }
    else{
        cout << "Entries title are not same" << endl;
    }
}
