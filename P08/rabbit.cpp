#include "rabbit.h"

Rabbit::Rabbit(Rabbit_breed breed, std::string name, Gender gender, int age)
    : Animal(name, gender, age), _breed{breed} { }
Rabbit::~Rabbit() { }

std::string Rabbit::family() const {return "rabbit";}
std::string Rabbit::breed() const {return ::to_string(_breed);}

std::string to_string(const Rabbit_breed& breed) {
    switch(breed) {
		case Rabbit_breed::HOLLAND:       return "Holland";
		case Rabbit_breed::FLEMISH_GIANT: return "Flemish Giant";
		case Rabbit_breed::REX:           return "Maine Coon";
		case Rabbit_breed::AMERICAN:      return "American";
		case Rabbit_breed::MINI:          return "Mini";
		case Rabbit_breed::COTTONTAIL:    return "Cottontail";
		case Rabbit_breed::PYGMY:         return "Pygmy";
		case Rabbit_breed::POLISH:        return "Polish";
    	default:                          return "UNKNOWN";
    }
}
std::ostream& operator<<(std::ostream& ost, const Rabbit_breed& breed) {
    ost << ::to_string(breed);
    return ost;
}

