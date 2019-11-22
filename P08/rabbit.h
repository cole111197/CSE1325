#ifndef __RABBIT_H
#define __RABBIT_H

#include "animal.h"
#include <map>

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

class Rabbit : public Animal {
    public:
        Rabbit(Rabbit_breed breed, std::string name, Gender gender, int age);
        Rabbit(std::istream& ist);
        virtual ~Rabbit();
        virtual std::string family() const override;
        virtual std::string breed() const override;

        virtual void save(std::ostream& ost) override;

        static std::map<Rabbit_breed, std::string> rabbit_breeds;
    private:
        Rabbit_breed _breed;
};

#endif