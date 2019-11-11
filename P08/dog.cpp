#include "dog.h"

// Constructor / Destructor - note how delegation to base class works!
Dog::Dog(Dog_breed breed, std::string name, Gender gender, int age) : Animal(name, gender, age), _breed{breed}{ }
Dog::~Dog() { }

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

// Overrides for pure virtual methods
std::string Dog::family() const {return "dog";}
std::string Dog::breed() const {return dog_breeds[_breed];}

/*
std::ostream& operator<<(std::ostream& ost, const Dog_breed& breed) {
    ost << Dog::dog_breeds[breed];
    return ost;
}
*/