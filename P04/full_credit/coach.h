#ifndef __COACH_H
#define __COACH_H

class Coach{
    private:
        int _passengers;
    public:
        Coach(double weight = 28000);
        void add_passengers(int passengers);
        double weight() override;
};

#endif
