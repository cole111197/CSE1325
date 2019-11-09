#ifndef __CLIENT_H
#define __CLIENT_H

#include "client.h"
#include <string>
#include <vector> 

class Client {
    private:
        std::string _name;
        std::string _phone;
        std::string _email;
        std::vector<Animal*> _adopted;
    public:
        
};

#endif