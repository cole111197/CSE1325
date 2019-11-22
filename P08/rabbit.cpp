#include "rabbit.h"

Rabbit::Rabbit(Rabbit_breed breed, std::string name, Gender gender, int age)
    : Animal(name, gender, age), _breed{breed} { }
Rabbit::~Rabbit() { }

std::map<Rabbit_breed, std::string> Rabbit::rabbit_breeds = {
    {Rabbit_breed::HOLLAND, "Holland"},
    {Rabbit_breed::FLEMISH_GIANT, "Flemish Giant"},
    {Rabbit_breed::REX, "Rex"},
    {Rabbit_breed::AMERICAN, "American"},
    {Rabbit_breed::MINI, "Mini"},
    {Rabbit_breed::COTTONTAIL, "Cottontail"},
    {Rabbit_breed::PYGMY, "Pygmy"},
    {Rabbit_breed::POLISH, "Polish"}
    };

void Rabbit::save(std::ostream& ost){
    ost << family() << std::endl;
    ost << breed() << std::endl;
    Animal::save(ost);
}

std::string Rabbit::family() const {return "rabbit";}
std::string Rabbit::breed() const {return rabbit_breeds[_breed];}

/*
std::ostream& operator<<(std::ostream& ost, const Rabbit_breed& breed) {
    ost << ::to_string(breed);
    return ost;
}
*/