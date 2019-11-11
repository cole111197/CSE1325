#ifndef __DOG_H
#define __DOG_H

#include "animal.h"
#include <map>

// List of dog breeds, conversion to/from string and stream, and iteration
enum class Dog_breed {
    BEAGLE,
    BOXER,
    BULLDOG,
    DACHSHUND,
    LABRADOR,
    MIX,
    POINTER, 
    POODLE,
    RETRIEVER,
    ROTTWEILER,
    SHEPHERD,
    TERRIER,
};

// Class Dog with overrides for family and breed
class Dog : public Animal {
  public:
    Dog(Dog_breed breed, std::string name, Gender gender, int age);
    virtual ~Dog();
    virtual std::string family() const override;
    virtual std::string breed() const override;

    static std::map<Dog_breed, std::string> dog_breeds;
  private:
    Dog_breed _breed;
    
    
};

#endif
