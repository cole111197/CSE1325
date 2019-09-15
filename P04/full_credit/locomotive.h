#ifndef __LOCOMOTIVE_H
#define __LOCOMOTIVE_H

class Locomotive(){
    private:
        double _power;
    public:
        Locomotive(double weight = 80000, double power = 13500);
        double power();
};

#endif
