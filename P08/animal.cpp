#include "animal.h"

// Constructors / Destructors
Animal::Animal(std::string name, Gender gender, int age)
    : _name{name}, _gender{gender}, _age{age} { }

Animal::Animal(std::istream& ist){
    std::getline(ist, _name);
    std::string gen;
    std::getline(ist, gen);
    _gender = ((gen == "male") ? Gender::MALE : Gender::FEMALE);
    std::string agestr;
    std::getline(ist, agestr);
    _age = std::stoi(agestr);
}

Animal::~Animal() { }

void Animal::save(std::ostream& ost){
    ost << _name << std::endl;
    ost << ::to_string(_gender) << std::endl;
    ost << _age << std::endl;
}

// Getters
std::string Animal::name() const {return _name;}
Gender Animal::gender() const {return _gender;}
int Animal::age() const {return _age;}

// Convert Animal and its derived classes to a string and stream representation
std::string Animal::to_string() const {
    return _name + " (" + ::to_string(this->gender()) + ' ' + this->breed() + ' ' + this->family()
                 + ", age " + std::to_string(this->age()) + ')';
}
std::ostream& operator<<(std::ostream& ost, const Animal& animal) {
    ost << animal.to_string();
    return ost;
}

// Convert Gender to a string and stream representation
std::string to_string(Gender gender) {return ((gender == Gender::FEMALE) ? "female" : "male");}
std::ostream& operator<<(std::ostream& ost, const Gender& gender) {
    ost << to_string(gender);
    return ost;
}
