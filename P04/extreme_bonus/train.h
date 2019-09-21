#ifndef __TRAIN_H
#define __TRAIN_H
#include "locomotive.h"
#include "coach.h"
#include <vector>
#include <string>
#include <iostream>

class Train{
    private:
        std::vector<Locomotive*> _locomotives;
        std::vector<Coach*> _coaches;   
        void add_locomotive(Locomotive& locomotive);
        void add_coach(Coach& coach); 
        std::string to_art();
    public:
        Locomotive& operator+=(Locomotive& locomotive);
        Locomotive& operator+=(Coach& coach);
        friend std::ostream& operator<<(std::ostream& ost, Train& train);
        double speed(double minutes);
};

#endif
