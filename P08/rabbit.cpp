#include "rabbit.h"

Rabbit::Rabbit(Rabbit_breed breed, std::string name, Gender gender, int age)
    : Animal(name, gender, age), _breed{breed} { }
Rabbit::~Rabbit() { }

Rabbit::Rabbit(std::istream& ist) : Animal(ist){
    std::string breed_temp;
    std::getline(ist, breed_temp);
    for(std::map<Rabbit_breed, std::string>::iterator it = rabbit_breeds.begin(); it != rabbit_breeds.end(); it++){
        if(it->second == breed_temp){
            _breed = it->first;
            it = rabbit_breeds.end();
        }
    }
}

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
    Animal::save(ost);
    ost << breed() << std::endl;
}

std::string Rabbit::family() const {return "rabbit";}
std::string Rabbit::breed() const {return rabbit_breeds[_breed];}

/*
std::ostream& operator<<(std::ostream& ost, const Rabbit_breed& breed) {
    ost << ::to_string(breed);
    return ost;
}
*/