#ifndef __STOCK_H
#define __STOCK_H
#include <string>

class Stock{
    private:
        double _weight;
        vector<std::string> _art;
    public:
        virtual double weight;
        Stock();
        Stock(double weight);
        std::string ascii_art(int row);
};

#endif
