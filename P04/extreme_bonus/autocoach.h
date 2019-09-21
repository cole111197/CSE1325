#ifndef __AUTOCOACH_H
#define __AUTOCOACH_H
#include "coach.h"
#include "locomotive.h"

class Autocoach: public Coach, public Locomotive{
    public:
        Autocoach(double weight = 70000, double power = 9500);
};

#endif