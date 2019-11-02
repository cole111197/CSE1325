#ifndef __DOG_H
#define __DOG_H

#include "dog_breed.h"
#include "gender.h"
#include <string>

class Dog : public Animal{
    public:
        Dog(Dog_breed breed, std::string name, Gender gender, int age);
        ~Dog();
        std::string family() override;
        std::string breed() override;
};

#endif