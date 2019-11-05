#include "animal.h"

Animal::Animal(std::string name, Gender gender, int age) : _name{name}, _gender{gender}, _age{age} {}

Animal::~Animal() {}

std::string Animal::name(){
    return _name;
}

Gender Animal::gender(){
    return _gender;
}

int Animal::age(){
    return _age;
}

/*
//CALLS Animal::to_string()
std::ostream& operator<<(std::ostream& ost, const Animal& an){
    ost << an.to_string();
    return ost;
}
*/