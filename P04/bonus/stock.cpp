#include "stock.h"
#include <cmath>

Stock::Stock() : _weight(nan("")) { }

Stock::Stock(double weight) : _weight(weight) { }

double Stock::weight(){
    return _weight;
}

std::string Stock::ascii_art(int row){
    return _art[row];
}
