#ifndef __RABBIT_H
#define __RABBIT_H

#include "animal.h"

enum class Rabbit_breed{
    HOLLAND,
    FLEMISH_GIANT,
    REX,
    AMERICAN,
    MINI,
    COTTONTAIL,
    PYGMY,
    POLISH
};
constexpr Rabbit_breed rabbit_breeds[] = {
    Rabbit_breed::HOLLAND,
    Rabbit_breed::FLEMISH_GIANT,
    Rabbit_breed::REX,
    Rabbit_breed::AMERICAN,
    Rabbit_breed::MINI,
    Rabbit_breed::COTTONTAIL,
    Rabbit_breed::PYGMY,
    Rabbit_breed::POLISH
};
std::string to_string(const Rabbit_breed& breed);
std::ostream& operator<<(std::ostream& ost, const Rabbit_breed& breed);

class Rabbit : public Animal {
    public:
        Rabbit(Rabbit_breed breed, std::string name, Gender gender, int age);
        virtual ~Rabbit();
        virtual std::string family() const override;
        virtual std::string breed() const override;
    private:
        Rabbit_breed _breed;
};

#endif