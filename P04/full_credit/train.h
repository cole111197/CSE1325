#ifndef __TRAIN_H
#define __TRAIN_H
#include "locomotive.h"
#include "coach.h"
#include <vector>
#include <string>

class Train{
    private:
        vector<Locomotive*> _locomotives;
        vector<Coach*> _coaches;    
    public:
        void add_locomotive(Locomotive& locomotive);
        void add_coach(Coach& coach);
        double speed(double minutes);
        std::string to_art();
};

#endif
