#include "dog.h"

// Constructor / Destructor - note how delegation to base class works!
Dog::Dog(Dog_breed breed, std::string name, Gender gender, int age) : Animal(name, gender, age), _breed{breed}{ }
Dog::~Dog() { }

Dog::Dog(std::istream& ist) : Animal(ist){
    std::string breed_temp;
    std::getline(ist, breed_temp);
    for(std::map<Dog_breed, std::string>::iterator it = dog_breeds.begin(); it != dog_breeds.end(); it++){
        if(it->second == breed_temp){
            _breed = it->first;
            it = dog_breeds.end();
        }
    }
}

std::map<Dog_breed, std::string> Dog::dog_breeds = {
      {Dog_breed::BEAGLE, "Beagle"},
      {Dog_breed::BOXER, "Boxer"},
      {Dog_breed::BULLDOG, "Bulldog"},
      {Dog_breed::DACHSHUND, "Dachshund"},
      {Dog_breed::LABRADOR, "Labrador"},
      {Dog_breed::MIX, "Mix"},
      {Dog_breed::POINTER, "Pointer"},
      {Dog_breed::POODLE, "Poodle"},
      {Dog_breed::RETRIEVER, "Retriever"},
      {Dog_breed::ROTTWEILER, "Rottweiler"},
      {Dog_breed::SHEPHERD, "Shepherd"},
      {Dog_breed::TERRIER, "Terrier"}
    };

void Dog::save(std::ostream& ost){
    ost << family() << std::endl;
    Animal::save(ost);
    ost << breed() << std::endl;
}

// Overrides for pure virtual methods
std::string Dog::family() const {return "dog";}
std::string Dog::breed() const {return dog_breeds[_breed];}

/*
std::ostream& operator<<(std::ostream& ost, const Dog_breed& breed) {
    ost << Dog::dog_breeds[breed];
    return ost;
}
*/