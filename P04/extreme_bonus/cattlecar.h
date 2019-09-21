#ifndef __CATTLECAR_H
#define __CATTLECAR_H
#include "stock.h"

class Cattlecar: virtual public Stock{
    private:
        int _cattle;
    public:
        Cattlecar(double weight = 16500);
        void add_cattle(int cattle);
        double weight() override;
};

#endif
