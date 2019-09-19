#ifndef __STOCK_H
#define __STOCK_H
#include <string>
#include <vector>

class Stock{
    protected:
        std::vector<std::string> _art;
    private:
        double _weight;
    public:
        Stock();
        Stock(double weight);
        virtual double weight();
        std::string ascii_art(int row);
};

#endif
