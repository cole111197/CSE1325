#include "cat.h"

Cat::Cat(Cat_breed breed, std::string name, Gender gender, int age)
    : Animal(name, gender, age), _breed{breed} { }
Cat::~Cat() { }

Cat::Cat(std::istream& ist) : Animal(ist){
    std::string breed_temp;
    std::getline(ist, breed_temp);
    for(std::map<Cat_breed, std::string>::iterator it = cat_breeds.begin(); it != cat_breeds.end(); it++){
        if(it->second == breed_temp){
            _breed = it->first;
            it = cat_breeds.end();
        }
    }
}

std::map<Cat_breed, std::string> Cat::cat_breeds = {
    {Cat_breed::PERSIAN, "Persian"},
    {Cat_breed::SIAMESE, "Siamese"},
    {Cat_breed::MAINE_COON, "Maine Coon"},
    {Cat_breed::RAGDOLL, "Ragdoll"},
    {Cat_breed::MUNCHKIN, "Munchkin"},
    {Cat_breed::RUSSIAN_BLUE, "Russian Blue"},
    {Cat_breed::SPHYNX, "Sphynx"},
    {Cat_breed::BALINESE, "Balinese"}
    };

void Cat::save(std::ostream& ost){
    ost << family() << std::endl;
    Animal::save(ost);
    ost << breed() << std::endl;
}

std::string Cat::family() const {return "cat";}
std::string Cat::breed() const {return cat_breeds[_breed];}

/*
std::ostream& operator<<(std::ostream& ost, const Cat_breed& breed) {
    ost << ::to_string(breed);
    return ost;
}
*/