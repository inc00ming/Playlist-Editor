#include <iostream>
#include "HistoryRecord.hpp"

using namespace std;

int main(){
	Entry e = Entry("Furkan", "OST", "2017");
	HistoryRecord hr = HistoryRecord(INSERT, e);
    cout << hr.getOperation() << endl;
    cout << hr.getEntry()<< endl;
    cout << hr << endl;
	return 0;
}
