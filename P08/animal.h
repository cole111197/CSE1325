
#ifndef __ANIMAL_H
#define __ANIMAL_H

#include "gender.h"
#include <string>

//TODO: Change age to a date (Make date class?) and have age() calculate and return current age

class Animal{
    public:
        Animal(std::string name, Gender gender, int age);
        ~Animal();
        virtual std::string family() = 0;
        virtual std::string breed() = 0;
        std::string name();
        Gender gender();
        int age();
        std::string to_string();
    protected:
        std::string _name;
        Gender _gender;
        int _age;
};

#endif