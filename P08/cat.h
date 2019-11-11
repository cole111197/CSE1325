#ifndef __CAT_H
#define __CAT_H

#include "animal.h"
#include <map>

enum class Cat_breed{
    PERSIAN,
    SIAMESE,
    MAINE_COON,
    RAGDOLL,
    MUNCHKIN,
    RUSSIAN_BLUE,
    SPHYNX,
    BALINESE
};

class Cat : public Animal {
    public:
        Cat(Cat_breed breed, std::string name, Gender gender, int age);
        virtual ~Cat();
        virtual std::string family() const override;
        virtual std::string breed() const override;

        static std::map<Cat_breed, std::string> cat_breeds;
    private:
        Cat_breed _breed;
};

#endif