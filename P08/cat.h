#ifndef __CAT_H
#define __CAT_H

#include "animal.h"

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
constexpr Cat_breed cat_breeds[] = {
    Cat_breed::PERSIAN,
    Cat_breed::SIAMESE,
    Cat_breed::MAINE_COON,
    Cat_breed::RAGDOLL,
    Cat_breed::MUNCHKIN,
    Cat_breed::RUSSIAN_BLUE,
    Cat_breed::SPHYNX,
    Cat_breed::BALINESE
};
std::string to_string(const Cat_breed& breed);
std::ostream& operator<<(std::ostream& ost, const Cat_breed& breed);

class Cat : public Animal {
    public:
        Cat(Cat_breed breed, std::string name, Gender gender, int age);
        virtual ~Cat();
        virtual std::string family() const override;
        virtual std::string breed() const override;
    private:
        Cat_breed _breed;
};

#endif