#ifndef __CLIENT_H
#define __CLIENT_H

#include "animal.h"
#include <string>
#include <list> 
#include <iostream>

class Client {
    public:
        Client(std::string name, std::string phone, std::string email);
        void adopt(Animal& animal);
        int num_adopted();
        const Animal& animal(int index);
        friend std::ostream& operator<<(std::ostream& ost, const Client& ct);
    private:
        std::string _name;
        std::string _phone;
        std::string _email;
        std::list<Animal*> _adopted;
};
std::ostream& operator<<(std::ostream& ost, const Client& client);

#endif