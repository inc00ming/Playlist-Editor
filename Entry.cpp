// git check
#include <cstdlib>
#include <iostream>
#include <string>
#include "Entry.hpp"

using namespace std;

std::ostream &operator<<(std::ostream &out, const Entry& t){
    out <<"{"<< t.title<<","<<t.genre<<","<<t.year<<"}";
    return out;
};

Entry::Entry(){
    title = "";
    genre = "";
    year = "";
}

Entry::Entry(std::string _title, std::string _genre, std::string _year){
    title = _title;
    genre = _genre;
    year = _year;
}

string Entry::getTitle() const{
    return title;
}

string Entry::getGenre() const{
    return genre;
}

string Entry::getYear() const{
    return year;
}

bool Entry::operator==(const Entry & rhs) const{
    return title == rhs.getTitle();
}
/* TO-DO: method implementations below */
