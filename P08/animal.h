#ifndef __ANIMAL_H
#define __ANIMAL_H

#include "gender.h"
#include <string>
#include <iostream>

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
        virtual std::string to_string() = 0;
    protected:
        std::string _name;
        Gender _gender;
        int _age;
};
//std::ostream& operator<<(std::ostream& os, const Animal& an);
#endif