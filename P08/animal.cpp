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

std::string Animal::to_string(){
    std::string gen;
    if(gender() == Gender::MALE){
        gen = "Male";
    } else {
        gen = "Female";
    }
    return "Name: " + name() + ", Gender: " + gen + ", Age: " + std::to_string(age());
}

std::ostream& operator<<(std::ostream& ost, const Animal& animal){
    std::string gen;
    if(animal._gender == Gender::MALE){
        gen = "Male";
    } else {
        gen = "Female";
    }
    ost << "Name: " << animal._name << ", Gender: " << gen << ", Age: " << std::to_string(animal._age);
    return ost;
}