#include "cat.h"

Cat::Cat(Cat_breed breed, std::string name, Gender gender, int age)
    : Animal(name, gender, age), _breed{breed} { }
Cat::~Cat() { }

std::string Cat::family() const {return "cat";}
std::string Cat::breed() const {return ::to_string(_breed);}

std::string to_string(const Cat_breed& breed) {
    switch(breed) {
    	case Cat_breed::PERSIAN:      return "Persian";
    	case Cat_breed::SIAMESE:      return "Siamese";
    	case Cat_breed::MAINE_COON:   return "Maine Coon";
    	case Cat_breed::RAGDOLL:      return "Ragdoll";
    	case Cat_breed::MUNCHKIN:     return "Munchkin";
    	case Cat_breed::RUSSIAN_BLUE: return "Russian Blue";
    	case Cat_breed::SPHYNX:       return "Sphynx";
    	case Cat_breed::BALINESE:     return "Balinese";
    	default:                      return "UNKNOWN";
    }
}
std::ostream& operator<<(std::ostream& ost, const Cat_breed& breed) {
    ost << ::to_string(breed);
    return ost;
}

