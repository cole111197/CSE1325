#ifndef __TRAIN_H
#define __TRAIN_H
#include "stock.h"
#include "locomotive.h"
#include "coach.h"
#include "autocoach.h"
#include "cattlecar.h"
#include "boxcar.h"
#include <vector>
#include <string>
#include <iostream>

class Train{
    private:
        std::vector<Stock*> _cars; 
        std::string to_art();
    public:
        Locomotive& operator+=(Locomotive& locomotive);
        Locomotive& operator+=(Coach& coach);
        Locomotive& operator+=(Autocoach& autocoach);
        Locomotive& operator+=(Cattlecar& cattlecar);
        Locomotive& operator+=(Boxcar& boxcar);

        friend std::ostream& operator<<(std::ostream& ost, Train& train);
        double speed(double minutes);
};

#endif
