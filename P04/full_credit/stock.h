#ifndef __STOCK_H
#define __STOCK_H
#include <string>
#include <vector>

class Stock{
    private:
        double _weight;
        std::vector<std::string> _art;
    public:
        virtual double weight();
        Stock();
        Stock(double weight);
        std::string ascii_art(int row);
};

#endif
