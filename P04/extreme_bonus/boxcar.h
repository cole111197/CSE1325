#ifndef __BOXCAR_H
#define __BOXCAR_H
#include "stock.h"

class Boxcar: virtual public Stock{
    private:
        double _cargo;
    public:
        Boxcar(double weight = 14000);
        void add_cargo(double weight);
        double weight() override;
};

#endif
